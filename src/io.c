#include <bh/io.h>
#include <malloc.h>


#define BUFFER_SIZE (sizeof(char *))


struct bh_io_s
{
    bh_io_func_t func;
};


bh_io_t *bh_io_new(bh_io_func_t func,
                   void *data)
{
    size_t requested;
    bh_io_t *io;

    /* Get information about IO device size */
    if (func(NULL, BH_IO_INFO_CB, &requested, NULL))
        return NULL;

    /* Allocate space for the IO device */
    io = malloc(sizeof(*io) + requested);
    if (!io)
        return NULL;

    /* Initialize IO device */
    io->func = func;
    if (func(io + 1, BH_IO_INIT_CB, data, NULL))
    {
        free(io);
        return NULL;
    }

    return io;
}


void bh_io_free(bh_io_t *io)
{
    /* Prevent working with NULL io */
    if (!io)
        return;

    /* Call the IO device destruction handler */
    io->func(io + 1, BH_IO_DESTROY_CB, NULL, NULL);
}


const char *bh_io_classname(bh_io_t *io)
{
    const char *name;

    if (!io)
        goto error;

    if (io->func(io + 1, BH_IO_INFO_CB, NULL, &name) != BH_OK)
        goto error;

    return name;

error:
    return NULL;
}


int bh_io_open(bh_io_t *io,
               int mode)
{
    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device open handler with specified mode */
    return io->func(io + 1, BH_IO_OPEN_CB, &mode, NULL);
}


int bh_io_close(bh_io_t *io)
{
    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device close handler */
    return io->func(io + 1, BH_IO_CLOSE_CB, NULL, NULL);
}


int bh_io_read(bh_io_t *io,
               char *buffer,
               size_t size,
               size_t *actual)
{
    int code;

    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device read handler */
    code = io->func(io + 1, BH_IO_READ_CB, buffer, &size);

    /* If caller wants to know actual read size - report it back */
    if (actual)
        *actual = size;

    return code;
}


int bh_io_write(bh_io_t *io,
                const char *buffer,
                size_t size,
                size_t *actual)
{
    int code;

    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device write handler */
    code = io->func(io + 1, BH_IO_WRITE_CB, (void *)buffer, &size);

    /* If caller wants to know actual written size - report it back */
    if (actual)
        *actual = size;

    return code;
}

int bh_io_peek(bh_io_t *io,
               char *buffer,
               size_t size,
               size_t *actual)
{
    int code;

    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device peek handler */
    code = io->func(io + 1, BH_IO_PEEK_CB, (void *)buffer, &size);

    /* If caller wants to know actual written size - report it back */
    if (actual)
        *actual = size;

    return code;
}


int bh_io_tell(bh_io_t *io,
               int64_t *position)
{
    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device tell handler */
    return io->func(io + 1, BH_IO_TELL_CB, position, NULL);
}


int bh_io_seek(bh_io_t *io,
               int64_t position,
               int direction)
{
    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device seek handler */
    return io->func(io + 1, BH_IO_SEEK_CB, &position, &direction);
}


int bh_io_flush(bh_io_t *io)
{
    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device flush handler */
    return io->func(io + 1, BH_IO_FLUSH_CB, NULL, NULL);
}


int bh_io_size(bh_io_t *io,
               int64_t *size)
{
    /* Prevent working with NULL io */
    if (!io)
        return BH_ERROR;

    /* Call the IO device size handler */
    return io->func(io + 1, BH_IO_SIZE_CB, size, NULL);
}


int bh_io_flags(bh_io_t *io)
{
    /* Prevent working with NULL io */
    if (!io)
        return BH_IO_FLAG_ERROR;

    /* Call the IO device flags handler */
    return io->func(io + 1, BH_IO_FLAGS_CB, NULL, NULL);
}


int bh_io_clear(bh_io_t *io)
{
    /* Prevent working with NULL io */
    if (!io)
        return BH_OK;

    /* Call the IO device clear error handler */
    return io->func(io + 1, BH_IO_CLEAR_CB, NULL, NULL);
}
