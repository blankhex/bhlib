#include <bh/io.h>

typedef struct bh_file_s
{
    int implement;
    int me;
} bh_file_t;

static int file_info(bh_file_t *file,
                     size_t *size,
                     const char **name);

static int file_init(bh_file_t *file,
                     const char *path);

static int file_destroy(bh_file_t *file);

static int file_open(bh_file_t *file,
                     int *mode);

static int file_close(bh_file_t *file);

static int file_read(bh_file_t *file,
                     char *data,
                     size_t *size);

static int file_write(bh_file_t *file,
                      const char *data,
                      size_t *size);

static int file_peek(bh_file_t* file,
                     char *data,
                     size_t *size);

static int file_flush(bh_file_t *file);

static int file_seek(bh_file_t *file,
                     int64_t *pos,
                     int *dir);

static int file_tell(bh_file_t *file,
                     int64_t *pos);

static int file_size(bh_file_t *file,
                     int64_t *size);

static int file_flags(bh_file_t *file);

static int file_clear(bh_file_t *file);

static int file_info(bh_file_t *file,
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

static int file_init(bh_file_t *file,
                     const char *path)
{
    return BH_NOIMPL;
}

static int file_destroy(bh_file_t *file)
{
    return BH_NOIMPL;
}

static int file_open(bh_file_t *file,
                     int *mode)
{
    return BH_NOIMPL;
}

static int file_close(bh_file_t *file)
{
    return BH_NOIMPL;
}

static int file_read(bh_file_t *file,
                     char *data,
                     size_t *size)
{
    return BH_NOIMPL;
}

static int file_write(bh_file_t *file,
                      const char *data,
                      size_t *size)
{
    return BH_NOIMPL;
}

static int file_peek(bh_file_t *file,
                     char *data,
                     size_t *size)
{
    return BH_NOIMPL;
}

static int file_flush(bh_file_t *file)
{
    return BH_NOIMPL;
}

static int file_seek(bh_file_t *file,
                     int64_t *pos,
                     int *dir)
{
    return BH_NOIMPL;
}

static int file_tell(bh_file_t *file,
                     int64_t *pos)
{
    return BH_NOIMPL;
}

static int file_size(bh_file_t *file,
                     int64_t *size)
{
    return BH_NOIMPL;
}

static int file_flags(bh_file_t *file)
{
    return BH_IO_FLAG_ERROR;
}

static int file_clear(bh_file_t *file)
{
    return BH_NOIMPL;
}

static int file_proc(bh_file_t *file,
                     int type,
                     void *arg1,
                     void *arg2)
{
    switch (type)
    {
    case BH_IO_INFO_CB:     return file_info(file, (size_t *)arg1, (const char **)arg2);
    case BH_IO_INIT_CB:     return file_init(file, (const char *)arg1);
    case BH_IO_DESTROY_CB:  return file_destroy(file);
    case BH_IO_OPEN_CB:     return file_open(file, (int *)arg1);
    case BH_IO_CLOSE_CB:    return file_close(file);
    case BH_IO_READ_CB:     return file_read(file, (char *)arg1, (size_t *)arg2);
    case BH_IO_WRITE_CB:    return file_write(file, (const char *)arg1, (size_t *)arg2);
    case BH_IO_PEEK_CB:     return file_peek(file, (char *)arg1, (size_t *)arg2);
    case BH_IO_FLUSH_CB:    return file_flush(file);
    case BH_IO_SEEK_CB:     return file_seek(file, (int64_t *)arg1, (int *)arg2);
    case BH_IO_TELL_CB:     return file_tell(file, (int64_t *)arg1);
    case BH_IO_SIZE_CB:     return file_size(file, (int64_t *)arg1);
    case BH_IO_FLAGS_CB:    return file_flags(file);
    case BH_IO_CLEAR_CB:    return file_clear(file);
    default:                return BH_NOIMPL;
    }
}

bh_io_t *bh_file_new(const char *path)
{
    return bh_io_new((bh_io_func_t)file_proc, (void *)path);
}
