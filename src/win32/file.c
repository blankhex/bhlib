#include <bh/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


typedef struct BH_File
{
    char *path;
    int mode;
    int flags;
    HANDLE handle;
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

    return BH_OK;
}


static int BH_FileInit(BH_File *file,
                       const char *path)
{
    /* Check if path is valid */
    if (!path)
        return BH_ERROR;

    /* Duplicate path string and initialize the file struct */
    file->path = strdup(path);
    file->mode = 0;
    file->handle = INVALID_HANDLE_VALUE;
    file->flags = 0;

    return BH_OK;
}


static int BH_FileDestroy(BH_File *file)
{
    /* Close the file handle on destruction */
    if (file->handle != INVALID_HANDLE_VALUE)
        BH_FileClose(file);

    /* Free path string */
    free(file->path);

    return BH_OK;
}


static int BH_FileOpen(BH_File *file,
                       int *mode)
{
    DWORD access = 0, how = 0;

    /* Check if file is already openned */
    if (file->handle != INVALID_HANDLE_VALUE)
        return BH_ERROR;

    /* Determine read/write access flags */
    if (*mode & BH_IO_READ)
        access |= GENERIC_READ;
    if (*mode & BH_IO_WRITE)
        access |= GENERIC_WRITE;

    if (!access)
        return BH_ERROR;

    /* Determine open mode flags */
    if (*mode & BH_IO_TRUNCATE)
    {
        switch (*mode & (BH_IO_CREATE | BH_IO_EXIST))
        {
        case 0:            how = CREATE_ALWAYS;     break;
        case BH_IO_CREATE: how = CREATE_NEW;        break;
        case BH_IO_EXIST:  how = TRUNCATE_EXISTING; break;
        default:           return BH_ERROR;
        }
    }
    else
    {
        switch (*mode & (BH_IO_CREATE | BH_IO_EXIST))
        {
        case 0:            how = OPEN_ALWAYS;   break;
        case BH_IO_CREATE: how = CREATE_NEW;    break;
        case BH_IO_EXIST:  how = OPEN_EXISTING; break;
        default:           return BH_ERROR;
        }
    }

    /* Save mode that we are in and open file */
    file->mode = *mode;
    file->handle = CreateFileA(file->path, access, FILE_SHARE_READ, NULL, how, FILE_ATTRIBUTE_NORMAL, NULL);

    if (file->handle == INVALID_HANDLE_VALUE)
        return BH_ERROR;

    /* Truncate file if needed */
    if (*mode & BH_IO_TRUNCATE)
        SetEndOfFile(file->handle);

    return BH_OK;
}


static int BH_FileClose(BH_File *file)
{
    /* If file is opened - close it */
    if (file->handle == INVALID_HANDLE_VALUE)
        return BH_ERROR;

    /* Reset handle and mode values */
    CloseHandle(file->handle);
    file->handle = INVALID_HANDLE_VALUE;
    file->mode = 0;
    return BH_OK;
}


static int BH_FileRead(BH_File *file,
                       char *data,
                       size_t *size)
{
    DWORD readed;

    /* Check if file is opened */
    if (file->handle == INVALID_HANDLE_VALUE)
        goto error;

    /* Read data from the file */
    if (!ReadFile(file->handle, data, (DWORD)*size, &readed, NULL))
        goto error;

    /* Check if we reached end of file */
    if (!readed)
        file->flags |= BH_IO_FLAG_EOF;
    else
        file->flags &= ~BH_IO_FLAG_EOF;

    *size = readed;
    return BH_OK;

error:
    file->flags |= BH_IO_FLAG_ERROR;
    return BH_ERROR;
}


static int BH_FileWrite(BH_File *file,
                        const char *data,
                        size_t *size)
{
    DWORD written;

    /* Check if file is opened */
    if (file->handle == INVALID_HANDLE_VALUE)
        goto error;

    /* Adjust current position in the file to the end */
    if (file->mode & BH_IO_APPEND)
    {
        LARGE_INTEGER position;

        position.QuadPart = 0;
        if (!SetFilePointerEx(file->handle, position, NULL, FILE_END))
            goto error;
    }

    /* Write data to the file */
    if (!WriteFile(file->handle, data, (DWORD)*size, &written, NULL))
        goto error;

    /* Check for end of file */
    if (!written)
        file->flags |= BH_IO_FLAG_EOF;
    else
        file->flags &= ~BH_IO_FLAG_EOF;

    *size = written;
    return BH_OK;

error:
    file->flags |= BH_IO_FLAG_ERROR;
    return BH_ERROR;
}


static int BH_FilePeek(BH_File *file,
                       char *data,
                       size_t *size)
{
    int64_t position;
    int direction;

    /* Read data from the file */
    if (BH_FileRead(file, data, size))
        return BH_ERROR;

    /* Backtrack by the read amount */
    position = -((int64_t)*size);
    direction = BH_IO_SEEK_CUR;
    if (BH_FileSeek(file, &position, &direction))
        return BH_ERROR;

    return BH_OK;
}


static int BH_FileFlush(BH_File *file)
{
    /* Check if file is opened */
    if (file->handle == INVALID_HANDLE_VALUE)
        goto error;

    /* Flush OS buffers */
    FlushFileBuffers(file->handle);
    return BH_OK;

error:
    file->flags |= BH_IO_FLAG_ERROR;
    return BH_ERROR;
}


static int BH_FileSeek(BH_File *file,
                       int64_t *pos,
                       int *dir)
{
    LARGE_INTEGER position;

    /* Check if file is opened */
    if (file->handle == INVALID_HANDLE_VALUE)
        goto error;

    /* Set read/write position in the file */
    position.QuadPart = *pos;
    if (!SetFilePointerEx(file->handle, position, NULL, *dir))
        goto error;

    return BH_OK;

error:
    file->flags |= BH_IO_FLAG_ERROR;
    return BH_ERROR;
}


static int BH_FileTell(BH_File *file,
                       int64_t *pos)
{
    LARGE_INTEGER dummy, position;

    /* Check if file is opened */
    if (file->handle == INVALID_HANDLE_VALUE)
        goto error;

    /* Readback current position in the file */
    dummy.QuadPart = 0;
    if (!SetFilePointerEx(file->handle, dummy, &position, BH_IO_SEEK_CUR))
        goto error;

    *pos = position.QuadPart;
    return BH_OK;

error:
    file->flags |= BH_IO_FLAG_ERROR;
    return BH_ERROR;
}


static int BH_FileSize(BH_File *file,
                       int64_t *size)
{
    LARGE_INTEGER dummy;

    /* Check if file is opened */
    if (file->handle == INVALID_HANDLE_VALUE)
        goto error;

    /* Get current file size */
    if (!GetFileSizeEx(file->handle, &dummy))
        goto error;

    *size = dummy.QuadPart;
    return BH_OK;

error:
    file->flags |= BH_IO_FLAG_ERROR;
    return BH_ERROR;
}


static int BH_FileFlags(BH_File *file)
{
    /* If file handle is valid - append IO_OPEN flag */
    if (file->handle != INVALID_HANDLE_VALUE)
        return file->flags | BH_IO_FLAG_OPEN;
    return file->flags;
}


static int BH_FileClear(BH_File *file)
{
    /* Clear IO_ERROR flag */
    file->flags &= ~BH_IO_FLAG_ERROR;
    return BH_OK;
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
