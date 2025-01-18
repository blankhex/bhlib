#ifndef BH_IO_H
#define BH_IO_H


#include "common.h"


#define BH_IO_INFO_CB       0x0000
#define BH_IO_INIT_CB       0x0001
#define BH_IO_DESTROY_CB    0x0002
#define BH_IO_OPEN_CB       0x0003
#define BH_IO_CLOSE_CB      0x0004
#define BH_IO_READ_CB       0x0005
#define BH_IO_WRITE_CB      0x0006
#define BH_IO_PEEK_CB       0x0007
#define BH_IO_TELL_CB       0x0008
#define BH_IO_SEEK_CB       0x0009
#define BH_IO_FLUSH_CB      0x000A
#define BH_IO_SIZE_CB       0x000B
#define BH_IO_FLAGS_CB      0x000C
#define BH_IO_CLEAR_CB      0x000D


#define BH_IO_READ          0x0001
#define BH_IO_WRITE         0x0002
#define BH_IO_READWRITE     0x0003
#define BH_IO_APPEND        0x0010
#define BH_IO_TRUNCATE      0x0020
#define BH_IO_CREATE        0x0040
#define BH_IO_EXIST         0x0080


#define BH_IO_SEEK_SET      0x0000
#define BH_IO_SEEK_CUR      0x0001
#define BH_IO_SEEK_END      0x0002


#define BH_IO_FLAG_OK       0x0000
#define BH_IO_FLAG_ERROR    0x0001
#define BH_IO_FLAG_EOF      0x0002
#define BH_IO_FLAG_OPEN     0x0004

#define BH_FILE_CLASSNAME   "bh_file"

typedef struct bh_io_s bh_io_t;
typedef int (*bh_io_func_t)(void *, int, void *, void *);


/**
 * Creates the IO handle that represents file.
 *
 * \param path  Path to the file
 *
 * \return On success, returns IO handle.
 * \return On failure, returns NULL pointer.
 */
bh_io_t *bh_file_new(const char *path);


/**
 * Creates the IO handle that represents buffered IO.
 *
 * \param io  IO handle
 *
 * \return On success, returns IO handle.
 * \return On failure, returns NULL pointer.
 */
bh_io_t *bh_buffer_new(bh_io_t *io);


/**
 * Creates the IO handle with specified handler and context.
 *
 * \param func  IO actions handler
 * \param data  Initialization data
 *
 * \return On success, returns IO handle.
 * \return On failure, returns NULL pointer.
 */
bh_io_t *bh_io_new(bh_io_func_t func,
                   void *data);


/**
 * Destroys the IO.
 *
 * \param io  IO handle
 */
void bh_io_free(bh_io_t *io);


/**
 * Returns the IO instance classname.
 *
 * \param io  IO handle
 *
 * \return On success, returns pointer to constant string.
 * \return On failure, returns NULL pointer
 */
const char *bh_io_classname(bh_io_t *io);


/**
 * Opens the IO in specified mode of operation.
 *
 * \param io    IO handle
 * \param mode  Mode of operation
 *
 * \return On success, returns zero value.
 * \return On failure, returns error code.
 */
int bh_io_open(bh_io_t *io,
               int mode);


/**
 * Closes the IO.
 *
 * \param io  IO handle
 *
 * \return On success, returns zero value.
 * \return On failure, returns error code.
 */
int bh_io_close(bh_io_t *io);


/**
 * Reads up to specified amount of bytes from the IO into memory buffer.
 *
 * \param io      IO handle
 * \param buffer  Pointer to the buffer
 * \param size    Bytes to read
 * \param actual  Bytes read
 *
 * \return On success, returns zero value.
 * \return On failure, returns error code.
 */
int bh_io_read(bh_io_t *io,
               char *buffer,
               size_t size,
               size_t *actual);


/**
 * Writes up to specified amount of bytes into the IO from the memory buffer.
 *
 * \param io      IO handle
 * \param buffer  Pointer to the buffer
 * \param size    Bytes to write
 * \param actual  Bytes written
 *
 * \return On success, returns zero value.
 * \return On failure, returns error code.
 */
int bh_io_write(bh_io_t *io,
                const char *buffer,
                size_t size,
                size_t *actual);


/**
 * Peeks up to specified amount of bytes from the IO handle.
 *
 * \param io  IO handle
 * \param buffer  Pointer to the buffer
 * \param size    Bytes to peek
 * \param actial  Bytes peeked
 *
 * \return On success, returns zero value.
 * \return On failure, returns error code.
 */
int bh_io_peek(bh_io_t *io,
               char *buffer,
               size_t size,
               size_t *actual);


/**
 * Tells current offset in the IO.
 *
 * \param io        IO handle
 * \param position  Offset
 *
 * \return On success, returns zero value.
 * \return On failure, returns error code.
 */
int bh_io_tell(bh_io_t *io,
               int64_t *position);


/**
 * Seeks to specified offset in the IO.
 *
 * \param io         IO handle
 * \param position   Offset
 * \param direction  Direction
 *
 * \return On success, returns zero value.
 * \return On failure, returns error code.
 */
int bh_io_seek(bh_io_t *io,
               int64_t position,
               int direction);


/**
 * Flushes the internal buffers of the IO.
 *
 * \param io  IO handle
 *
 * \return On success, returns zero value.
 * \return On failure, returns error code.
 */
int bh_io_flush(bh_io_t *io);


/**
 * Returns the size of the IO (either total or available size).
 *
 * \param io    IO handle
 * \param size  Available/total size
 *
 * \return On success, returns zero value.
 * \return On failure, returns error code.
 */
int bh_io_size(bh_io_t *io,
               int64_t *size);


/**
 * Returns flags of the IO.
 *
 * \param io  IO handle
 *
 * \return Flags of the IO
 */
int bh_io_flags(bh_io_t *io);


/**
 * Clears errors of the IO.
 *
 * \param io  IO handle
 *
 * \return On success, returns zero value.
 * \return On failure, returns error code.
 */
int bh_io_clear(bh_io_t *io);


#endif /* BH_IO_H */
