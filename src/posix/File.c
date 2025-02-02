#include <BH/IO.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>


typedef struct BH_File
{
    char *path;
    int mode;
    int flags;
    int handle;
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
    file->handle = -1;
    file->flags = 0;

    return BH_OK;
}


static int BH_FileDestroy(BH_File *file)
{
    /* Close the file handle on destruction */
    if (file->handle != -1)
        BH_FileClose(file);

    /* Free path string */
    free(file->path);

    return BH_OK;
}


static int BH_FileOpenFlags(int mode)
{
    int flags = 0;

    /* Determine read/write flags */
    if ((mode & BH_IO_READWRITE) == BH_IO_READWRITE)
        flags |= O_RDWR;
    else if (mode & BH_IO_WRITE)
        flags |= O_WRONLY;
    else if (mode & BH_IO_READ)
        flags |= O_RDONLY;
    else
        return -1;

    /* Check if existing file should be opened */
    if (!(mode & BH_IO_EXIST))
    {
        flags |= O_CREAT;

        /* Check if file should be created */
        if (mode & BH_IO_CREATE)
            flags |= O_EXCL;
    }

    /* Check if file should be opened in append mode */
    if (mode & BH_IO_APPEND)
        flags |= O_APPEND;

    /* Check if file should be truncated */
    if (mode & BH_IO_TRUNCATE)
        flags |= O_TRUNC;

    return flags;
}


static int BH_FileOpen(BH_File *file,
                       int *mode)
{
    static const mode_t open_mode = (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    int flags;

    /* If file is already opened - report error */
    if (file->handle != -1)
        return BH_ERROR;

    /* Determine file open flags */
    flags = BH_FileOpenFlags(*mode);
    if (flags == -1)
        return BH_ERROR;

    /* Open the file */
    file->handle = open(file->path, flags, open_mode);
    if (file->handle == -1)
        return BH_ERROR;

    return BH_OK;
}


static int BH_FileClose(BH_File *file)
{
    /* If file is closed - report error */
    if (file->handle == -1)
        return BH_ERROR;

    /* Close and reset the file handle */
    close(file->handle);
    file->handle = -1;

    return BH_OK;
}


static int BH_FileRead(BH_File *file,
                       char *data,
                       size_t *size)
{
    ssize_t readed;

    /* Check if file is open */
    if (file->handle == -1)
        goto error;

    /* Read data from the file */
    readed = read(file->handle, data, *size);
    if (readed < 0)
        goto error;

    /* Check for EOF condition */
    if (readed > 0)
        file->flags &= ~BH_IO_FLAG_EOF;
    else
        file->flags |= BH_IO_FLAG_EOF;

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
    ssize_t written;

    /* Check if file is open */
    if (file->handle == -1)
        goto error;

    /* Write data to the file */
    written = write(file->handle, data, *size);
    if (written < 0)
        goto error;

    /* Check for EOF condition */
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

    /* Check if file is open */
    if (file->handle == -1)
        goto error;

    /* Read data from the file */
    if (BH_FileRead(file, data, size))
        goto error;

    /* Backtrack by the read amount */
    position = -((int64_t)*size);
    direction = BH_IO_SEEK_CUR;
    if (BH_FileSeek(file, &position, &direction))
        goto error;

    return BH_OK;

error:
    file->flags |= BH_IO_FLAG_ERROR;
    return BH_ERROR;
}


static int BH_FileFlush(BH_File *file)
{
    /* Check if file is open */
    if (file->handle == -1)
    {
        file->flags |= BH_IO_FLAG_ERROR;
        return BH_ERROR;
    }

    /* Flush the buffers */
    fsync(file->handle);
    return BH_OK;
}


static int BH_FileSeek(BH_File *file,
                       int64_t *pos,
                       int *dir)
{
    /* Check if file is open */
    if (file->handle == -1)
        goto error;

    /* Seek to the specified position */
    if (lseek(file->handle, *pos, *dir) == -1)
        goto error;

    return BH_OK;

error:
    file->flags |= BH_IO_FLAG_ERROR;
    return BH_ERROR;
}


static int BH_FileTell(BH_File *file,
                       int64_t *pos)
{
    /* Check if file is open */
    if (file->handle == -1)
        goto error;

    /* Get current offset in the file */
    if ((*pos = lseek(file->handle, 0, SEEK_CUR)) == -1)
        goto error;

    return BH_OK;

error:
    file->flags |= BH_IO_FLAG_ERROR;
    return BH_ERROR;
}


static int BH_FileSize(BH_File *file,
                       int64_t *size)
{
    struct stat sb;

    /* Check if file is open */
    if (file->handle == -1)
        goto error;

    /* Get file size from the OS */
    if (fstat(file->handle, &sb))
        goto error;

    *size = sb.st_size;
    return BH_OK;

error:
    file->flags |= BH_IO_FLAG_ERROR;
    return BH_ERROR;
}


static int BH_FileFlags(BH_File *file)
{
    /* If file handle is valid - append IO_OPEN flag */
    if (file->handle != -1)
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
