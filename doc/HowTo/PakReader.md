# HowTo: Reading PACK (pak) Archives

## Overview

In this guide, we will be creating a program called `PakReader`, which will be
able to read PAK archives (list all files within the archive or extract a
specific file from the archive).

## Prerequisites

We want to implement a simple command-line utility that can:

- List the contents of the archive
- Extract a specific file from the archive

To extract the `Text.txt` file from the `sample.pak` archive to `output.txt`, we
would run the following command:

```sh
./PakReader -i Text.txt -o output.txt sample.pak
```

To list files in the `sample.pak` archive, we would run the following command:

```sh
./PakReader -l sample.pak
```

## PACK Archive Format

PACK archives are extremely simple. A PACK archive consists of three parts:

- Header at the beginning of the file
- File table with the name and size of the file
- File data

Header has the following structure:

| Name   | Type          | Information                         |
|--------|---------------|-------------------------------------|
| id     | 4 byte string | Always contains the word "PACK"     |
| offset | uint32        | Offset of the file table (in bytes) |
| size   | uint32        | Size of the file table (in bytes)   |

File table entry has the following structure:

| Name   | Type           | Information                         |
|--------|----------------|-------------------------------------|
| name   | 54 byte string | Full file path (null-terminated)    |
| offset | uint32         | Offset in the file (in bytes)       |
| size   | uint32         | Size of the file (in bytes)         |

## Includes

To implement this utility, we are going to need to include the following headers:

- `BH/IO.h` to work with files (or input/output devices)
- `BH/Util.h` to read integers with specific width and endianness
- `BH/Args.h` to work with command-line arguments

## Working with Files

Working with files in BHLib is based around the IO device (called `BH_IO`).
Firstly, you need to create an IO file device with the `BH_FileNew` function.
While doing so, you can specify in which mode it will work: reading
(`BH_FILE_READ`) or writing (`BH_FILE_WRITE`). Additionally, we can specify
whether the file should exist before opening (`BH_IO_EXIST`), be truncated
before opening (`BH_IO_TRUNCATE`), should it be created (`BH_IO_CREATE`), or
opened in append mode (`BH_IO_APPEND`).

Here is an example for opening an existing file in read-only mode:

```c
BH_IO *io = BH_FileNew("coolfile.dat", BH_FILE_READ | BH_FILE_EXISTS, NULL);
if (!io)
{
    printf("Can't open file 'coolfile.dat'\n", config.file);
    return -1;
}
```

## Reading Data from the File

In general, it's best to read some data into a temporary buffer, then parse the
data into variables/structure fields. This makes sure you will not run into
issues caused by misalignment (slowdowns or exceptions/crashes).

For reading or writing integers, it's recommended to use `BH_Read*` and
`BH_Write*`, respectively. Suffixes `16`, `32`, `64` denote integers' width in
bits. Suffixes `LE` and `BE` denote endianness (LittleEndian and BigEndian).
Suffixes `u` and `s` denote unsigned or signed integers.

For example, the function `BH_Read32LEs` reads a signed 32-bit integer that is
stored in LittleEndian format.

Below is an example for reading header data into the structure `header`:

```c
char buffer[HEADER_SIZE];
size_t actual;

if (BH_IORead(io, buffer, HEADER_SIZE, &actual) || actual != HEADER_SIZE)
    return BH_ERROR;

if (memcmp(buffer, "PACK", 4))
    return BH_ERROR;

memcpy(header->id, buffer, 4);
header->offset = BH_Read32LEu(buffer + 4);
header->size = BH_Read32LEu(buffer + 8);
```

## Working with Command-Line Arguments

Working (or parsing) with CMD arguments is somewhat similar to POSIX
`getopt_long` function. Firstly, you need to define what options (or switches)
are present in your program. To do this, create an array of `BH_ArgsOption`,
filled with option definitions and one empty element at the end of the array.

Each element consists of the following:

- Key
- Name
- Flags
- Description or documentation string

`Key` is used to identify options while processing them. Key value can be an
ASCII character or an integer. If key is an ASCII character, it becomes an
option's short name (key 'd' becomes `-d`).

`Name` is used to represent 'long' option names (name 'hello-world' becomes
`--hello-world`). You can omit `Name`.

`Flags` are used to specify whether an option requires a value (or if they are
optional).

`Description` is used in pair with the function `BH_ArgsHelp` to display
information about the option.

Then you need to define a `callback` function that will do something in response
to the option being parsed.

Array of options, option callback, and ARGC/ARGV is then passed to the function
`BH_ArgsParse`.

Here is the example of using the options:

```c
static BH_ArgsOption options[] = {
    {'h', "help", 0, "Display this help"},
    {'l', "list", 0, "List files in the archive instead of reading"},
    {'i', "input", BH_ARGS_VALUE, "Input file in archive"},
    {'o', "output", BH_ARGS_VALUE, "Output file"},
    {0, NULL, 0, NULL}
};

static int callback(int key, char *arg, void *data)
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

int main(int argc, char **argv)
{
    Config config;

    /* Parse arguments */
    memset(&config, 0, sizeof(config));
    if (BH_ArgsParse(argc, argv, options, callback, &config) || !config.file)
    {
        PrintHelp();
        return -1;
    }

    /* ... */
    return 0;
}
```

## Putting Everything Together

Now, let's put everything together and implement `PakReader`.

```c
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

            output = BH_FileNew(config->output, BH_FILE_WRITE | BH_FILE_TRUNCATE, NULL);
            if (!output || BH_IOSeek(io, entry.offset, BH_IO_SEEK_SET) ||
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
    if ((io = BH_FileNew(config.file, BH_FILE_READ | BH_FILE_EXIST, NULL)) == NULL)
    {
        printf("Can't open file %s\n", config.file);
        BH_IOFree(io);
        return -1;
    }

    result = ProcessPack(&config, io);
    BH_IOFree(io);

    return result;
}
```
