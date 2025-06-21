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


BH_IO *BH_FileNew(const char *path,
                  int mode,
                  int *result);


BH_IO *BH_BufferNew(BH_IO *device,
                    size_t size,
                    int *result);


BH_IO *BH_BytesNew(char *data,
                   size_t size,
                   int *result);


void BH_IOFree(BH_IO *device);


int BH_IORead(BH_IO *device,
              char *buffer,
              size_t size,
              size_t *actual);


int BH_IOWrite(BH_IO *io,
               const char *buffer,
               size_t size,
               size_t *actual);


int BH_IOCtl(BH_IO *device,
             int op,
             void *arg);


int BH_IOCap(BH_IO *device,
             int op);


int BH_IOPeek(BH_IO *device,
              char *buffer,
              size_t size,
              size_t *actual);


int BH_IOTell(BH_IO *device,
              int64_t *offset);


int BH_IOSeek(BH_IO *device,
              int64_t offset,
              int whence);


int BH_IOFlush(BH_IO *device);


int BH_IOSize(BH_IO *device,
              int64_t *size);


int BH_IOFlags(BH_IO *device,
               int *flags);


int BH_IOError(BH_IO *device);


int BH_IOEndOfFile(BH_IO *device);


int BH_IOClear(BH_IO *device);


#endif /* BH_IO_H */
