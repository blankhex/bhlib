#include <BH/IO.h>
#include <string.h>
#include <stdlib.h>


#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))


typedef struct BH_Bytes
{
    BH_IO parent;
    char *data;
    size_t size;
    size_t position;
} BH_Bytes;


static int bytesInit(BH_Bytes *bytes,
                     char *data,
                     size_t size)
{
    if (!data || !size)
        return BH_ERROR;

    bytes->data = data;
    bytes->size = size;
    bytes->position = 0;

    return BH_OK;
}


static int bytesDestroy(BH_Bytes *bytes)
{
    free(bytes);
    return BH_OK;
}


static int bytesRead(BH_Bytes *bytes,
                     BH_IOReadInfo *info)
{
    size_t size;

    size = MIN(info->size, bytes->size - bytes->position);
    memmove(info->data, bytes->data + bytes->position, size);
    bytes->position += size;

    if (info->actual)
        *info->actual = size;

    return BH_OK;
}


static int bytesWrite(BH_Bytes *bytes,
                      BH_IOWriteInfo *info)
{
    size_t size;

    size = MIN(info->size, bytes->size - bytes->position);
    memmove(bytes->data + bytes->position, info->data, size);
    bytes->position += size;

    if (info->actual)
        *info->actual = size;

    return BH_OK;
}

static int bytesSeek(BH_Bytes *bytes,
                     BH_IOSeekInfo *info)
{
    int64_t offset;

    switch (info->whence)
    {
    default:
    case BH_IO_SEEK_SET:
        offset = MAX(info->offset, 0);
        offset = MIN(offset, (int64_t)bytes->size);
        break;

    case BH_IO_SEEK_CUR:
        offset = MAX((int64_t)bytes->position + info->offset, 0);
        offset = MIN(offset, (int64_t)bytes->size);
        break;

    case BH_IO_SEEK_END:
        offset = MAX((int64_t)bytes->size + info->offset, 0);
        offset = MIN(offset, (int64_t)bytes->size);
        break;
    }

    bytes->position = offset;

    return BH_OK;
}


static int bytesTell(BH_Bytes *bytes,
                     int64_t *pos)
{
    *pos = bytes->position;

    return BH_OK;
}


static int bytesSize(BH_Bytes *bytes,
                     int64_t *size)
{
    *size = bytes->size;

    return BH_OK;
}


static int bytesFlags(BH_Bytes *bytes,
                     int *flags)
{
    if (bytes->position == bytes->size)
        *flags = BH_IO_FLAG_EOF;
    else
        *flags = 0;

    return BH_OK;
}


static int bytesCap(BH_Bytes *bytes,
                    int *op)
{
    BH_UNUSED(bytes);

    /* Return operations supported by the buffer input/output device */
    switch (*op)
    {
    case BH_IO_CTL_FLAGS:
    case BH_IO_CTL_SIZE:
    case BH_IO_CTL_TELL:
    case BH_IO_CTL_SEEK:
        return BH_OK;

    default:
        return BH_NOIMPL;
    }
}


static int bytesCtl(BH_Bytes *bytes,
                   BH_IOCtlInfo *info)
{
    /* Handle supported operations */
    switch (info->op)
    {
    case BH_IO_CTL_FLAGS:
        return bytesFlags(bytes, (int *)info->arg);

    case BH_IO_CTL_SIZE:
        return bytesSize(bytes, (int64_t *)(info->arg));

    case BH_IO_CTL_TELL:
        return bytesTell(bytes, (int64_t *)(info->arg));

    case BH_IO_CTL_SEEK:
        return bytesSeek(bytes, (BH_IOSeekInfo *)(info->arg));

    default:
        return BH_NOIMPL;
    }
}


static int bytesCallback(BH_Bytes *bytes,
                         int type,
                         void *arg)
{
    /* Handle basic input/output operations */
    switch (type)
    {
    case BH_IO_OP_DESTROY:  return bytesDestroy(bytes);
    case BH_IO_OP_READ:     return bytesRead(bytes, (BH_IOReadInfo *)arg);
    case BH_IO_OP_WRITE:    return bytesWrite(bytes, (BH_IOWriteInfo *)arg);
    case BH_IO_OP_CTL:      return bytesCtl(bytes, (BH_IOCtlInfo *)arg);
    case BH_IO_OP_CAP:      return bytesCap(bytes, (int*)arg);
    default:                return BH_NOIMPL;
    }
}


BH_IO *BH_BytesNew(char *data,
                   size_t size,
                   int *result)
{
    BH_Bytes *bytes;
    int code;

    code = BH_OOM;
    /* Allocate new buffer object and initialize it */
    if ((bytes = malloc(sizeof(*bytes))))
    {
        bytes->parent.callback = (BH_IOCallback)bytesCallback;
        if ((code = bytesInit(bytes, data, size)))
        {
            free(bytes);
            bytes = NULL;
        }
    }

    /* Report error code */
    if (result)
        *result = code;

    return (BH_IO*)bytes;
}


int BH_IOIsBytes(BH_IO *device)
{
    if (!device)
        return 0;

    return device->callback == (BH_IOCallback)bytesCallback;
}

