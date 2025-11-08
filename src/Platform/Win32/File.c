#include <BH/IO.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


typedef struct BH_File
{
    BH_IO parent;
    int flags;
    int mode;
    HANDLE handle;
} BH_File;


static int fileInit(BH_File *file,
                    const char *path,
                    int mode)
{
    DWORD access = 0, how = 0;

    /* Check if path is valid */
    if (!path)
        return BH_ERROR;

    /* Determine read/write access flags */
    if (mode & BH_FILE_READ)
        access |= GENERIC_READ;
    if (mode & BH_FILE_WRITE)
        access |= GENERIC_WRITE;

    if (!access)
        return BH_ERROR;

    /* Determine open mode flags */
    if (mode & BH_FILE_TRUNCATE)
    {
        switch (mode & (BH_FILE_CREATE | BH_FILE_EXIST))
        {
        case 0:              how = CREATE_ALWAYS;     break;
        case BH_FILE_CREATE: how = CREATE_NEW;        break;
        case BH_FILE_EXIST:  how = TRUNCATE_EXISTING; break;
        default:             return BH_ERROR;
        }
    }
    else
    {
        switch (mode & (BH_FILE_CREATE | BH_FILE_EXIST))
        {
        case 0:              how = OPEN_ALWAYS;   break;
        case BH_FILE_CREATE: how = CREATE_NEW;    break;
        case BH_FILE_EXIST:  how = OPEN_EXISTING; break;
        default:             return BH_ERROR;
        }
    }

    /* Save mode that we are in and open file */
    file->flags = 0;
    file->mode = mode;
    file->handle = CreateFileA(path, access, FILE_SHARE_READ, NULL, how, FILE_ATTRIBUTE_NORMAL, NULL);

    if (file->handle == INVALID_HANDLE_VALUE)
        return BH_ERROR;

    /* Truncate file if needed */
    if (mode & BH_FILE_TRUNCATE)
        SetEndOfFile(file->handle);

    return BH_OK;
}


static int fileDestroy(BH_File *file)
{
    /* Close the file handle on destruction */
    CloseHandle(file->handle);
    free(file);

    return BH_OK;
}


static int fileRead(BH_File *file,
                    BH_IOReadInfo *info)
{
    DWORD readed;

    /* Read data from the file */
    if (!ReadFile(file->handle, info->data, (DWORD)info->size, &readed, NULL))
        goto error;

    /* Check if we reached end of file */
    if (!readed)
        file->flags |= BH_IO_FLAG_EOF;
    else
        file->flags &= ~BH_IO_FLAG_EOF;

    if (info->actual)
        *info->actual = readed;

    return BH_OK;

error:
    file->flags |= BH_IO_FLAG_ERROR;
    return BH_ERROR;
}


static int fileWrite(BH_File *file,
                     BH_IOWriteInfo *info)
{
    DWORD written;
    LARGE_INTEGER position;

    /* Adjust current position in the file to the end */
    if (file->mode & BH_FILE_APPEND)
    {
        position.QuadPart = 0;
        if (!SetFilePointerEx(file->handle, position, NULL, FILE_END))
            goto error;
    }

    /* Write data to the file */
    if (!WriteFile(file->handle, info->data, (DWORD)info->size, &written, NULL))
        goto error;

    /* Check for end of file */
    if (!written)
        file->flags |= BH_IO_FLAG_EOF;
    else
        file->flags &= ~BH_IO_FLAG_EOF;

    if (info->actual)
        *info->actual = written;

    return BH_OK;

error:
    file->flags |= BH_IO_FLAG_ERROR;
    return BH_ERROR;
}


static int fileFlush(BH_File *file)
{
    /* Flush OS buffers */
    FlushFileBuffers(file->handle);
    return BH_OK;
}


static int fileSeek(BH_File *file,
                    BH_IOSeekInfo *info)
{
    LARGE_INTEGER position;

    /* Set read/write position in the file */
    position.QuadPart = info->offset;
    if (!SetFilePointerEx(file->handle, position, NULL, info->whence))
        goto error;

    return BH_OK;

error:
    file->flags |= BH_IO_FLAG_ERROR;
    return BH_ERROR;
}


static int fileTell(BH_File *file,
                    int64_t *pos)
{
    LARGE_INTEGER dummy, position;

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


static int fileSize(BH_File *file,
                    int64_t *size)
{
    LARGE_INTEGER dummy;

    /* Get current file size */
    if (!GetFileSizeEx(file->handle, &dummy))
        goto error;

    *size = dummy.QuadPart;
    return BH_OK;

error:
    file->flags |= BH_IO_FLAG_ERROR;
    return BH_ERROR;
}


static int fileFlags(BH_File *file,
                     int *flags)
{
    *flags = file->flags;
    return BH_OK;
}


static int fileClear(BH_File *file)
{
    /* Clear BH_IO_FLAG_ERROR flag */
    file->flags &= ~BH_IO_FLAG_ERROR;
    return BH_OK;
}


static int fileCap(BH_File *file,
                   int *op)
{
    BH_UNUSED(file);

    /* Return operations supported by the file input/output device */
    switch (*op)
    {
    case BH_IO_CTL_FLAGS:
    case BH_IO_CTL_CLEAR:
    case BH_IO_CTL_FLUSH:
    case BH_IO_CTL_SIZE:
    case BH_IO_CTL_TELL:
    case BH_IO_CTL_SEEK:
        return BH_OK;

    default:
        return BH_NOIMPL;
    }
}


static int fileCtl(BH_File *file,
                   BH_IOCtlInfo *info)
{
    /* Handle supported operations */
    switch (info->op)
    {
    case BH_IO_CTL_FLAGS:
        return fileFlags(file, (int *)(info->arg));

    case BH_IO_CTL_CLEAR:
        return fileClear(file);

    case BH_IO_CTL_FLUSH:
        return fileFlush(file);

    case BH_IO_CTL_SIZE:
        return fileSize(file, (int64_t *)(info->arg));

    case BH_IO_CTL_TELL:
        return fileTell(file, (int64_t *)(info->arg));

    case BH_IO_CTL_SEEK:
        return fileSeek(file, (BH_IOSeekInfo *)(info->arg));

    default:
        return BH_NOIMPL;
    }
}


static int fileCallback(BH_File *file,
                        int type,
                        void *arg)
{
    /* Handle basic input/output operations */
    switch (type)
    {
    case BH_IO_OP_DESTROY:  return fileDestroy(file);
    case BH_IO_OP_READ:     return fileRead(file, (BH_IOReadInfo *)arg);
    case BH_IO_OP_WRITE:    return fileWrite(file, (BH_IOWriteInfo *)arg);
    case BH_IO_OP_CTL:      return fileCtl(file, (BH_IOCtlInfo *)arg);
    case BH_IO_OP_CAP:      return fileCap(file, (int*)arg);
    default:                return BH_NOIMPL;
    }
}


BH_IO *BH_FileNew(const char *path,
                  int mode,
                  int *result)
{
    BH_File *file;
    int code;

    code = BH_OOM;

    /* Allocate new file object and initialize it */
    if ((file = malloc(sizeof(*file))))
    {
        file->parent.callback = (BH_IOCallback)fileCallback;
        if ((code = fileInit(file, path, mode)))
        {
            free(file);
            file = NULL;
        }
    }

    /* Report error code */
    if (result)
        *result = code;

    return (BH_IO*)file;
}


int BH_IOIsFile(BH_IO *device)
{
    if (!device)
        return 0;

    return device->callback == (BH_IOCallback)fileCallback;
}
