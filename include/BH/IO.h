#ifndef BH_IO_H
#define BH_IO_H


#include "Common.h"


#define BH_IO_OP_DESTROY        0x0000
#define BH_IO_OP_READ           0x0001
#define BH_IO_OP_WRITE          0x0002
#define BH_IO_OP_CTL            0x0003
#define BH_IO_OP_CAP            0x0004


#define BH_IO_CTL_FLAGS         0x0000
#define BH_IO_CTL_CLEAR         0x0001
#define BH_IO_CTL_PEEK          0x0002
#define BH_IO_CTL_FLUSH         0x0003
#define BH_IO_CTL_SIZE          0x0004
#define BH_IO_CTL_TELL          0x0005
#define BH_IO_CTL_SEEK          0x0006
#define BH_IO_CTL_GET_IO        0x0007
#define BH_IO_CTL_SET_IO        0x0008


#define BH_IO_SEEK_SET          0x0000
#define BH_IO_SEEK_CUR          0x0001
#define BH_IO_SEEK_END          0x0002


#define BH_IO_FLAG_OK           0x0000
#define BH_IO_FLAG_ERROR        0x0001
#define BH_IO_FLAG_EOF          0x0002


#define BH_FILE_READ            0x0001
#define BH_FILE_WRITE           0x0002
#define BH_FILE_READWRITE       0x0003
#define BH_FILE_APPEND          0x0010
#define BH_FILE_TRUNCATE        0x0020
#define BH_FILE_CREATE          0x0040
#define BH_FILE_EXIST           0x0080


typedef int (*BH_IOCallback)(void *, int, void *);


typedef struct BH_IO
{
    BH_IOCallback callback;
} BH_IO;


typedef struct BH_IOReadInfo
{
    char *data;
    size_t size;
    size_t *actual;
} BH_IOReadInfo;


typedef struct BH_IOWriteInfo
{
    const char *data;
    size_t size;
    size_t *actual;
} BH_IOWriteInfo;


typedef struct BH_IOCtlInfo
{
    int op;
    void *arg;
} BH_IOCtlInfo;


typedef struct BH_IOSeekInfo
{
    int64_t offset;
    int whence;
} BH_IOSeekInfo;


/**
 * Creates an input/output device representing a file at the given \a path.
 *
 * \param path    File path
 * \param mode    Open mode
 * \param result  Result code
 *
 * \return On success, returns IO device pointer.
 * \return On failure, returns NULL pointer.
 */
BH_IO *BH_FileNew(const char *path,
                  int mode,
                  int *result);


/**
 * Creates an input/output deivce that buffers access to other \a device.
 *
 * \param device  IO device pointer
 * \param size    Buffer size
 * \param result  Result code
 *
 * \return On success, returns IO device pointer.
 * \return On failure, returns NULL pointer.
 */
BH_IO *BH_BufferNew(BH_IO *device,
                    size_t size,
                    int *result);


/**
 * Creates an input/output devices that access memory buffer.
 *
 * \param data    Buffer pointer
 * \param size    Buffer size
 * \param result  Result code
 *
 * \return On success, returns IO device pointer.
 * \return On failure, returns NULL pointer.
 */
BH_IO *BH_BytesNew(char *data,
                   size_t size,
                   int *result);


/**
 * Destroys the input/output \a device.
 *
 * \param device  IO device pointer
 */
void BH_IOFree(BH_IO *device);


/**
 * Reads up to \a size bytes from the \a device into \a buffer.
 *
 * \param device  IO device pointer
 * \param buffer  Buffer pointer
 * \param size    Buffer size
 * \param actual  Bytes read (optional)
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IORead(BH_IO *device,
              char *buffer,
              size_t size,
              size_t *actual);


/**
 * Writes up to \a size bytes to the \a device from \a buffer.
 *
 * \param io      IO device pointer
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
 * Manupulates an input/output \a device with specific \a op and and \a arg.
 *
 * \param device  IO device pointer
 * \param op      Operation
 * \param arg     Argument
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOCtl(BH_IO *device,
             int op,
             void *arg);


/**
 * Checks if an input/output \a device supports specific \a op.
 *
 * \param device  IO device pointer
 * \param op      Operation
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOCap(BH_IO *device,
             int op);


/**
 * Peeks up to \a size bytes from the \a device into \a buffer.
 *
 * \param device  IO device pointer
 * \param buffer  Buffer pointer
 * \param size    Buffer size
 * \param actial  Bytes peeked (optional)
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOPeek(BH_IO *device,
              char *buffer,
              size_t size,
              size_t *actual);


/**
 * Tells current \a offset in the \a device.
 *
 * \param device  IO device pointer
 * \param offset  Position
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOTell(BH_IO *device,
              int64_t *offset);


/**
 * Seeks to specified \a offset and \a whence in the \a device.
 *
 * \param device  IO device pointer
 * \param offset  Position
 * \param whence  Direction
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOSeek(BH_IO *device,
              int64_t offset,
              int whence);


/**
 * Flushes the internal buffers of the \a device.
 *
 * \param device  IO device pointer
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOFlush(BH_IO *device);


/**
 * Returns total or available size of the \a device.
 *
 * \param device  IO pointer
 * \param size    Available/total size
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOSize(BH_IO *device,
              int64_t *size);


/**
 * Returns flags of the \a device.
 *
 * \param device  IO device pointer
 * \param flags   Flags
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOFlags(BH_IO *device,
               int *flags);


/**
 * Returns error flag of the \a device.
 *
 * \param device  IO device pointer
 *
 * \return Returns error flag.
 */
int BH_IOError(BH_IO *device);


/**
 * Returns end-of-file flag of the \a device.
 *
 * \param device  IO device pointer
 *
 * \return Returns end-of-file flag.
 */
int BH_IOEndOfFile(BH_IO *device);


/**
 * Clears errors of the \a device.
 *
 * \param device  IO device pointer
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_IOClear(BH_IO *device);


#endif /* BH_IO_H */
