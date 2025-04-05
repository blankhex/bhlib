#include <BH/IO.h>
#include <stdlib.h>


#define BUFFER_SIZE (sizeof(char *))


struct BH_IO
{
    BH_IOCallback cb;
};


BH_IO *BH_IONew(BH_IOCallback cb,
                void *data)
{
    size_t requested;
    BH_IO *io;

    /* Get information about IO device size */
    if (cb(NULL, BH_IO_INFO_CB, &requested, NULL))
        return NULL;

    /* Allocate space for the IO device */
    io = malloc(sizeof(*io) + requested);
    if (!io)
        return NULL;

    /* Initialize IO device */
    io->cb = cb;
    if (cb(io + 1, BH_IO_INIT_CB, data, NULL))
    {
        free(io);
        return NULL;
    }

    return io;
}


void BH_IOFree(BH_IO *io)
{
    /* Prevent working with NULL io */
    if (!io)
        return;

    /* Call the IO device destruction handler */
    io->cb(io + 1, BH_IO_DESTROY_CB, NULL, NULL);

    /* Deallocate object */
    free(io);
}


const char *BH_IOClassname(BH_IO *io)
{
    const char *name;

    if (!io)
        goto error;

    if (io->cb(io + 1, BH_IO_INFO_CB, NULL, &name) != BH_OK)
        goto error;

    return name;

error:
    return NULL;
}


int BH_IOOpen(BH_IO *io,
              int mode)
{
    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device open handler with specified mode */
    return io->cb(io + 1, BH_IO_OPEN_CB, &mode, NULL);
}


int BH_IOClose(BH_IO *io)
{
    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device close handler */
    return io->cb(io + 1, BH_IO_CLOSE_CB, NULL, NULL);
}


int BH_IORead(BH_IO *io,
              char *buffer,
              size_t size,
              size_t *actual)
{
    int code;

    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device read handler */
    code = io->cb(io + 1, BH_IO_READ_CB, buffer, &size);

    /* If caller wants to know actual read size - report it back */
    if (actual)
        *actual = size;

    return code;
}


int BH_IOWrite(BH_IO *io,
               const char *buffer,
               size_t size,
               size_t *actual)
{
    int code;

    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device write handler */
    code = io->cb(io + 1, BH_IO_WRITE_CB, (void *)buffer, &size);

    /* If caller wants to know actual written size - report it back */
    if (actual)
        *actual = size;

    return code;
}

int BH_IOPeek(BH_IO *io,
              char *buffer,
              size_t size,
              size_t *actual)
{
    int code;

    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device peek handler */
    code = io->cb(io + 1, BH_IO_PEEK_CB, (void *)buffer, &size);

    /* If caller wants to know actual written size - report it back */
    if (actual)
        *actual = size;

    return code;
}


int BH_IOTell(BH_IO *io,
              int64_t *position)
{
    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device tell handler */
    return io->cb(io + 1, BH_IO_TELL_CB, position, NULL);
}


int BH_IOSeek(BH_IO *io,
              int64_t position,
              int direction)
{
    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device seek handler */
    return io->cb(io + 1, BH_IO_SEEK_CB, &position, &direction);
}


int BH_IOFlush(BH_IO *io)
{
    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device flush handler */
    return io->cb(io + 1, BH_IO_FLUSH_CB, NULL, NULL);
}


int BH_IOSize(BH_IO *io,
              int64_t *size)
{
    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device size handler */
    return io->cb(io + 1, BH_IO_SIZE_CB, size, NULL);
}


int BH_IOFlags(BH_IO *io)
{
    /* Prevent working with NULL io */
    if (!io)
        return BH_IO_FLAG_ERROR;

    /* Call the IO device flags handler */
    return io->cb(io + 1, BH_IO_FLAGS_CB, NULL, NULL);
}


int BH_IOClear(BH_IO *io)
{
    /* Prevent working with NULL io */
    if (!io)
        return BH_OK;

    /* Call the IO device clear error handler */
    return io->cb(io + 1, BH_IO_CLEAR_CB, NULL, NULL);
}



BH_IO *BH_BufferNew(BH_IO *io)
{
    (void)io;
    return NULL;
}
