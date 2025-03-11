#include <BH/Args.h>
#include <BH/IO.h>
#include <BH/Util.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/* PAK header and entry structures and some constants */
#define HEADER_SIZE  12
#define ENTRY_SIZE   64


typedef struct PakHeader
{
    char id[4];
    uint32_t offset;
    uint32_t size;
} PakHeader;


typedef struct PakEntry
{
    char name[56];
    uint32_t offset;
    uint32_t size;
} PakEntry;


static int ParseHeader(BH_IO *io,
                       PakHeader *header)
{
    char buffer[HEADER_SIZE];
    size_t actual;

    if (BH_IORead(io, buffer, HEADER_SIZE, &actual) || actual != HEADER_SIZE)
        return BH_ERROR;

    if (memcmp(buffer, "PACK", 4))
        return BH_ERROR;

    memcpy(header->id, buffer, 4);
    header->offset = BH_Read32LEu(buffer + 4);
    header->size = BH_Read32LEu(buffer + 8);

    return BH_OK;
}


static int ParseEntry(BH_IO *io,
                      PakEntry *entry)
{
    char buffer[ENTRY_SIZE];
    size_t actual;

    if (BH_IORead(io, buffer, ENTRY_SIZE, &actual) || actual != ENTRY_SIZE)
        return BH_ERROR;

    memcpy(entry->name, buffer, 56);
    entry->offset = BH_Read32LEu(buffer + 56);
    entry->size = BH_Read32LEu(buffer + 60);
    entry->name[55] = 0;

    return BH_OK;
}


/* Configuration and options  */
typedef struct Config
{
    char *file;
    char *input;
    char *output;
    int list;
} Config;


static BH_ArgsOption options[] = {
    {'h', "help", 0, "Display this help"},
    {'l', "list", 0, "List files in the archive instead of reading"},
    {'i', "input", BH_ARGS_VALUE, "Input file in archive"},
    {'o', "output", BH_ARGS_VALUE, "Output file"},
    {0, NULL, 0, NULL}
};


static void PrintHelp(void)
{
    printf("Usage: PakReader [options...] <file>\n");
    BH_ArgsHelp(options, 0);
}


static int OptionsCallback(int key,
                           char *arg,
                           void *data)
{
    Config *config = (Config *)data;

    switch (key)
    {
    case BH_ARGS_UNKNOWN: break;
    case BH_ARGS_ARGUMENT: if (!config->file) config->file = arg; break;
    case 'h': PrintHelp(); exit(0);
    case 'l': config->list = 1; break;
    case 'i': config->input = arg; break;
    case 'o': config->output = arg; break;
    }

    return BH_OK;
}


/* Copy data between two IO */
static int CopyData(BH_IO *from,
                    BH_IO *to,
                    size_t size)
{
    size_t i, length, actual;
    char tmp[512];

    for (i = 0; i < size; i += sizeof(tmp))
    {
        length = size - i;
        if (length > 512)
            length = 512;

        if (BH_IORead(from, tmp, length, &actual) || length != actual)
            return BH_ERROR;

        if (BH_IOWrite(to, tmp, length, &actual) || length != actual)
            return BH_ERROR;
    }

    return BH_OK;
}


/* Process pack (list files or extract file) */
static int ProcessPack(Config *config,
                       BH_IO *io)
{
    PakHeader header;
    PakEntry entry;
    BH_IO *output;
    size_t i;

    /* Read header and seek to begging of the file table */
    if (ParseHeader(io, &header))
        return BH_ERROR;

    if (BH_IOSeek(io, header.offset, BH_IO_SEEK_SET))
        return BH_ERROR;

    /* Parse and output entries */
    for (i = header.size / 64; i; i--)
    {
        if (ParseEntry(io, &entry))
            return BH_ERROR;

        if (config->list)
            printf("%s %d\n", entry.name, entry.size);
        else
        {
            if (strcmp(entry.name, config->input))
                continue;

            output = BH_FileNew(config->output);
            if (BH_IOOpen(output, BH_IO_WRITE) ||
                BH_IOSeek(io, entry.offset, BH_IO_SEEK_SET) ||
                CopyData(io, output, entry.size))
            {
                BH_IOFree(output);
                return BH_ERROR;
            }

            BH_IOFree(output);
            return BH_OK;
        }
    }

    if (config->list)
        return BH_OK;
    return BH_ERROR;
}


/* Main entry */
int main(int argc, char **argv)
{
    Config config;
    BH_IO *io;
    int result;

    /* Parse arguments */
    memset(&config, 0, sizeof(config));
    if (BH_ArgsParse(argc, argv, options, OptionsCallback, &config) || !config.file)
    {
        PrintHelp();
        return -1;
    }

    /* Check required arguments */
    if (!config.list && (!config.input || !config.output))
    {
        printf("Specify input and output files\n");
        PrintHelp();
        return -1;
    }

    /* Read and write */
    io = BH_FileNew(config.file);
    if (BH_IOOpen(io, BH_IO_READ | BH_IO_EXIST))
    {
        printf("Can't open file %s\n", config.file);
        BH_IOFree(io);
        return -1;
    }

    result = ProcessPack(&config, io);
    BH_IOFree(io);

    return result;
}
