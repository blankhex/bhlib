#include <BH/IO.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>


typedef struct BH_File
{
    BH_IO parent;
    int flags;
    int handle;
} BH_File;


static int fileOpenFlags(int mode)
{
    int flags = 0;

    /* Determine read/write flags */
    if ((mode & BH_FILE_READWRITE) == BH_FILE_READWRITE)
        flags |= O_RDWR;
    else if (mode & BH_FILE_WRITE)
        flags |= O_WRONLY;
    else if (mode & BH_FILE_READ)
        flags |= O_RDONLY;
    else
        return -1;

    /* Check if existing file should be opened */
    if (!(mode & BH_FILE_EXIST))
    {
        flags |= O_CREAT;

        /* Check if file should be created */
        if (mode & BH_FILE_CREATE)
            flags |= O_EXCL;
    }

    /* Check if file should be opened in append mode */
    if (mode & BH_FILE_APPEND)
        flags |= O_APPEND;

    /* Check if file should be truncated */
    if (mode & BH_FILE_TRUNCATE)
        flags |= O_TRUNC;

    return flags;
}


static int fileInit(BH_File *file,
                    const char *path,
                    int mode)
{
    static const mode_t open_mode = (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    int flags;

    /* Check if path is valid */
    if (!path)
        return BH_ERROR;

    /* Determine file open flags */
    flags = fileOpenFlags(mode);
    if (flags == -1)
        return BH_ERROR;

    /* Open the file */
    file->flags = 0;
    file->handle = open(path, flags, open_mode);
    if (file->handle == -1)
        return BH_ERROR;

    return BH_OK;
}


static int fileDestroy(BH_File *file)
{
    close(file->handle);
    free(file);

    return BH_OK;
}


static int fileRead(BH_File *file,
                    BH_IOReadInfo *info)
{
    ssize_t readed;

    /* Read data from the file */
    readed = read(file->handle, info->data, info->size);
    if (readed < 0)
        goto error;

    /* Check for EOF condition */
    if (readed > 0)
        file->flags &= ~BH_IO_FLAG_EOF;
    else
        file->flags |= BH_IO_FLAG_EOF;

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
    ssize_t written;

    /* Write data to the file */
    written = write(file->handle, info->data, info->size);
    if (written < 0)
        goto error;

    /* Check for EOF condition */
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
    /* Flush the buffers */
    fsync(file->handle);
    return BH_OK;
}


static int fileSeek(BH_File *file,
                    BH_IOSeekInfo *info)
{
    /* Seek to the specified position */
    if (lseek(file->handle, info->offset, info->whence) == -1)
        goto error;

    return BH_OK;

error:
    file->flags |= BH_IO_FLAG_ERROR;
    return BH_ERROR;
}


static int fileTell(BH_File *file,
                    int64_t *pos)
{
    /* Get current offset in the file */
    if ((*pos = lseek(file->handle, 0, SEEK_CUR)) == -1)
        goto error;

    return BH_OK;

error:
    file->flags |= BH_IO_FLAG_ERROR;
    return BH_ERROR;
}


static int fileSize(BH_File *file,
                    int64_t *size)
{
    struct stat sb;

    /* Get file size from the OS */
    if (fstat(file->handle, &sb))
        goto error;

    *size = sb.st_size;
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
        return fileFlags(file, (int *)info->arg);

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
