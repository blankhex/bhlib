#include <BH/IO.h>
#include <stdlib.h>


#define BUFFER_SIZE (sizeof(char *))


void BH_IOFree(BH_IO *device)
{
    /* Prevent working with NULL io */
    if (!device)
        return;

    /* Call the IO device destruction handler and deallocate */
    device->callback(device, BH_IO_OP_DESTROY, NULL);
}


int BH_IORead(BH_IO *device,
              char *buffer,
              size_t size,
              size_t *actual)
{
    BH_IOReadInfo info;

    /* Prevent working with NULL io */
    if (!device)
        return BH_ERROR;

    info.data = buffer;
    info.size = size;
    info.actual = actual;
    return device->callback(device, BH_IO_OP_READ, &info);
}


int BH_IOWrite(BH_IO *device,
               const char *buffer,
               size_t size,
               size_t *actual)
{
    BH_IOWriteInfo info;

    /* Prevent working with NULL io */
    if (!device)
        return BH_ERROR;

    info.data = buffer;
    info.size = size;
    info.actual = actual;

    return device->callback(device, BH_IO_OP_WRITE, &info);
}


int BH_IOCtl(BH_IO *device,
             int op,
             void *arg)
{
    BH_IOCtlInfo info;

    if (!device)
        return BH_ERROR;

    info.op = op;
    info.arg = arg;
    return device->callback(device, BH_IO_OP_CTL, &info);
}


int BH_IOCap(BH_IO *device,
             int op)
{
    if (!device)
        return BH_ERROR;

    return device->callback(device, BH_IO_OP_CAP, &op);
}


int BH_IOPeek(BH_IO *device,
              char *buffer,
              size_t size,
              size_t *actual)
{
    BH_IOReadInfo readInfo;
    BH_IOSeekInfo posInfo;
    size_t readed;

    readInfo.data = buffer;
    readInfo.size = size;
    readInfo.actual = actual;

    if (BH_IOCap(device, BH_IO_CTL_PEEK))
    {
        if (BH_IOCap(device, BH_IO_CTL_SEEK))
            return BH_NOIMPL;

        if (BH_IORead(device, buffer, size, &readed))
            return BH_ERROR;

        posInfo.whence = BH_IO_SEEK_CUR;
        posInfo.offset = -(int64_t)readed;
        if (BH_IOCtl(device, BH_IO_CTL_SEEK, &posInfo))
            return BH_ERROR;

        if (actual)
            *actual = readed;

        return BH_OK;
    }

    return BH_IOCtl(device, BH_IO_CTL_PEEK, &readInfo);
}


int BH_IOTell(BH_IO *device,
              int64_t *offset)
{
    return BH_IOCtl(device, BH_IO_CTL_TELL, offset);
}


int BH_IOSeek(BH_IO *device,
              int64_t offset,
              int whence)
{
    BH_IOSeekInfo info;

    info.offset = offset;
    info.whence = whence;
    return BH_IOCtl(device, BH_IO_CTL_SEEK, &info);
}


int BH_IOFlush(BH_IO *device)
{
    return BH_IOCtl(device, BH_IO_CTL_FLUSH, NULL);
}


int BH_IOSize(BH_IO *device,
              int64_t *size)
{
    return BH_IOCtl(device, BH_IO_CTL_SIZE, size);
}


int BH_IOFlags(BH_IO *device, int *flags)
{
    return BH_IOCtl(device, BH_IO_CTL_FLAGS, flags);
}


int BH_IOClear(BH_IO *device)
{
    return BH_IOCtl(device, BH_IO_CTL_CLEAR, NULL);
}


int BH_IOError(BH_IO *device)
{
    int flags;

    if (BH_IOFlags(device, &flags))
        return BH_ERROR;

    return flags & BH_IO_FLAG_ERROR;
}


int BH_IOEndOfFile(BH_IO *device)
{
    int flags;

    if (BH_IOFlags(device, &flags))
        return BH_ERROR;

    return flags & BH_IO_FLAG_EOF;
}


char *BH_IOReadLine(BH_IO *device,
                    char *str,
                    size_t size)
{
    size_t i, actual;

    if (size < 1)
        return NULL;

    i = 0;
    while (i < size - 1)
    {
        if (BH_IORead(device, str + i, 1, &actual) || actual != 1)
            break;

        if (str[i++] == '\n')
            break;
    }
    str[i] = 0;
    return i ? str : NULL;
}


char *BH_IOReadLineFull(BH_IO *device,
                        char *str,
                        size_t size)
{
    size_t i, actual;
    char data;

    if (size < 1)
        return NULL;

    i = 0;
    while (1)
    {
        if (BH_IORead(device, &data, 1, &actual) || actual != 1)
            break;

        if (i < size - 1)
            str[i++] = data;

        if (data == '\n')
            break;
    }
    str[i] = 0;
    return i ? str : NULL;
}
