#include <BH/IO.h>

typedef struct BH_File
{
    int implement;
    int me;
} BH_File;


static int BH_FileInfo(BH_File *file,
                       size_t *size,
                       const char **name);


static int BH_FileInit(BH_File *file,
                       const char *path);


static int BH_FileDestroy(BH_File *file);


static int BH_FileOpen(BH_File *file,
                       int *mode);


static int BH_FileClose(BH_File *file);


static int BH_FileRead(BH_File *file,
                       char *data,
                       size_t *size);


static int BH_FileWrite(BH_File *file,
                        const char *data,
                        size_t *size);


static int BH_FilePeek(BH_File* file,
                       char *data,
                       size_t *size);


static int BH_FileFlush(BH_File *file);


static int BH_FileSeek(BH_File *file,
                       int64_t *pos,
                       int *dir);


static int BH_FileTell(BH_File *file,
                       int64_t *pos);


static int BH_FileSize(BH_File *file,
                       int64_t *size);


static int BH_FileFlags(BH_File *file);


static int BH_FileClear(BH_File *file);


static int BH_FileInfo(BH_File *file,
                       size_t *size,
                       const char **name)
{
    static const char classname[] = BH_FILE_CLASSNAME;

    if (size)
        *size = sizeof(*file);
    if (name)
        *name = classname;

    return BH_NOIMPL;
}


static int BH_FileInit(BH_File *file,
                       const char *path)
{
    return BH_NOIMPL;
}


static int BH_FileDestroy(BH_File *file)
{
    return BH_NOIMPL;
}


static int BH_FileOpen(BH_File *file,
                       int *mode)
{
    return BH_NOIMPL;
}


static int BH_FileClose(BH_File *file)
{
    return BH_NOIMPL;
}


static int BH_FileRead(BH_File *file,
                       char *data,
                       size_t *size)
{
    return BH_NOIMPL;
}


static int BH_FileWrite(BH_File *file,
                        const char *data,
                        size_t *size)
{
    return BH_NOIMPL;
}


static int BH_FilePeek(BH_File *file,
                       char *data,
                       size_t *size)
{
    return BH_NOIMPL;
}


static int BH_FileFlush(BH_File *file)
{
    return BH_NOIMPL;
}


static int BH_FileSeek(BH_File *file,
                       int64_t *pos,
                       int *dir)
{
    return BH_NOIMPL;
}


static int BH_FileTell(BH_File *file,
                       int64_t *pos)
{
    return BH_NOIMPL;
}


static int BH_FileSize(BH_File *file,
                       int64_t *size)
{
    return BH_NOIMPL;
}


static int BH_FileFlags(BH_File *file)
{
    return BH_IO_FLAG_ERROR;
}


static int BH_FileClear(BH_File *file)
{
    return BH_NOIMPL;
}


static int BH_FileCallback(BH_File *file,
                           int type,
                           void *arg1,
                           void *arg2)
{
    switch (type)
    {
    case BH_IO_INFO_CB:     return BH_FileInfo(file, (size_t *)arg1, (const char **)arg2);
    case BH_IO_INIT_CB:     return BH_FileInit(file, (const char *)arg1);
    case BH_IO_DESTROY_CB:  return BH_FileDestroy(file);
    case BH_IO_OPEN_CB:     return BH_FileOpen(file, (int *)arg1);
    case BH_IO_CLOSE_CB:    return BH_FileClose(file);
    case BH_IO_READ_CB:     return BH_FileRead(file, (char *)arg1, (size_t *)arg2);
    case BH_IO_WRITE_CB:    return BH_FileWrite(file, (const char *)arg1, (size_t *)arg2);
    case BH_IO_PEEK_CB:     return BH_FilePeek(file, (char *)arg1, (size_t *)arg2);
    case BH_IO_FLUSH_CB:    return BH_FileFlush(file);
    case BH_IO_SEEK_CB:     return BH_FileSeek(file, (int64_t *)arg1, (int *)arg2);
    case BH_IO_TELL_CB:     return BH_FileTell(file, (int64_t *)arg1);
    case BH_IO_SIZE_CB:     return BH_FileSize(file, (int64_t *)arg1);
    case BH_IO_FLAGS_CB:    return BH_FileFlags(file);
    case BH_IO_CLEAR_CB:    return BH_FileClear(file);
    default:                return BH_NOIMPL;
    }
}


BH_IO *BH_FileNew(const char *path)
{
    return BH_IONew((BH_IOCallback)BH_FileCallback, (void *)path);
}
