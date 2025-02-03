#ifndef BH_IO_H
#define BH_IO_H


#include "Common.h"


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

#define BH_FILE_CLASSNAME   "BH_File"


typedef struct BH_IO BH_IO;
typedef int (*BH_IOCallback)(void *, int ,void *, void *);


/**
 * Creates the IO that represents file with the given \a path.
 *
 * \param path  File path
 *
 * \return On success, returns IO pointer.
 * \return On failure, returns NULL pointer.
 */
BH_IO *BH_FileNew(const char *path);


/**
 * Creates the IO that buffers access to other \a io.
 *
 * \param io  IO pointer
 *
 * \return On success, returns IO pointer.
 * \return On failure, returns NULL pointer.
 */
BH_IO *BH_BufferNew(BH_IO *io);


/**
 * Creates the IO with specified callback \a cb and \a data.
 *
 * \param cb    Callback
 * \param data  Initialization data
 *
 * \return On success, returns IO pointer.
 * \return On failure, returns NULL pointer.
 */
BH_IO *BH_IONew(BH_IOCallback cb,
                void *data);


/**
 * Destroys the \a io.
 *
 * \param io  IO pointer
 */
void BH_IOFree(BH_IO *io);


/**
 * Returns the \a io classname.
 *
 * \param io  IO pointer
 *
 * \return On success, returns pointer to constant string.
 * \return On failure, returns NULL pointer
 */
const char *BH_IOClassname(BH_IO* io);


/**
 * Opens the \a io in specified \a mode of operation.
 *
 * \param io    IO pointer
 * \param mode  Mode of operation
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOOpen(BH_IO *io,
              int mode);


/**
 * Closes the \a io.
 *
 * \param io  IO pointer
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOClose(BH_IO *io);


/**
 * Reads up to \a size bytes from the \a io into \a buffer.
 *
 * \param io      IO pointer
 * \param buffer  Buffer pointer
 * \param size    Buffer size
 * \param actual  Bytes read (optional)
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IORead(BH_IO *io,
              char *buffer,
              size_t size,
              size_t *actual);


/**
 * Writes up to \a size bytes to the \a io from \a buffer.
 *
 * \param io      IO pointer
 * \param buffer  Buffer pointer
 * \param size    Buffer size
 * \param actual  Bytes written (optional)
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOWrite(BH_IO *io,
               const char *buffer,
               size_t size,
               size_t *actual);


/**
 * Peeks up to \a size bytes from \a io into \a buffer.
 *
 * \param io      IO pointer
 * \param buffer  Buffer pointer
 * \param size    Buffer size
 * \param actial  Bytes peeked (optional)
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOPeek(BH_IO *io,
              char *buffer,
              size_t size,
              size_t *actual);


/**
 * Tells current \a position in the \a io.
 *
 * \param io        IO pointer
 * \param position  Position
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOTell(BH_IO *io,
              int64_t *position);


/**
 * Seeks to specified \a position and \a direction in the \a io.
 *
 * \param io         IO pointer
 * \param position   Position
 * \param direction  Direction
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOSeek(BH_IO *io,
              int64_t position,
              int direction);


/**
 * Flushes the internal buffers of the \a io.
 *
 * \param io  IO pointer
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOFlush(BH_IO *io);


/**
 * Returns total or available size of the \a io.
 *
 * \param io    IO pointer
 * \param size  Available/total size
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOSize(BH_IO *io,
              int64_t *size);


/**
 * Returns flags of the \a io.
 *
 * \param io  IO pointer
 *
 * \return Flags of the IO
 */
int BH_IOFlags(BH_IO *io);


/**
 * Clears errors of the \a io.
 *
 * \param io  IO pointer
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOClear(BH_IO *io);


#endif /* BH_IO_H */
