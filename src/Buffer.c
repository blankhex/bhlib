#include <BH/IO.h>
#include <stdlib.h>
#include <string.h>


typedef struct BH_BufferData
{
    char *data;
    size_t size;
    size_t capacity;
    size_t offset;
} BH_BufferData;


typedef struct BH_Buffer
{
    BH_IO parent;
    BH_IO *device;
    BH_BufferData in;
    BH_BufferData out;
    int flags;
} BH_Buffer;


#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))


static int bufferInit(BH_Buffer *buffer,
                      BH_IO *device,
                      size_t size)
{
    if (!size)
        size = 4096;

    if (!device)
        return BH_ERROR;

    buffer->device = device;

    /* Allocate input buffer */
    buffer->in.data = malloc(size);
    buffer->in.capacity = size;
    buffer->in.size = buffer->in.offset = 0;
    if (!buffer->in.data)
        return BH_OOM;

    /* Allocate output buffer */
    buffer->out.data = malloc(size);
    buffer->out.capacity = size;
    buffer->out.size = buffer->out.offset = 0;
    if (!buffer->out.data)
    {
        free(buffer->out.data);
        return BH_OOM;
    }

    return BH_OK;
}


static int bufferDestroy(BH_Buffer *buffer)
{
    /* Free buffers on destruction */
    free(buffer->in.data);
    if (buffer->in.data != buffer->out.data)
        free(buffer->out.data);

    free(buffer);
    return BH_OK;
}


static int bufferRefill(BH_Buffer *buffer)
{
    size_t size;
    int result;

    /* Shift existing data towards begining */
    memmove(buffer->in.data, buffer->in.data + buffer->in.offset, buffer->in.size);
    buffer->in.offset = 0;

    /* Read data from the device */
    size = buffer->in.capacity - buffer->in.size;
    if ((result = BH_IORead(buffer->device, buffer->in.data + buffer->in.size, size, &size)))
        goto done;
    buffer->in.size += size;

done:
    return result;
}


static int bufferFlush(BH_Buffer *buffer)
{
    size_t size;
    int result;

    /* Flush data to underlying input/output device */
    result = BH_IOWrite(buffer->device, buffer->out.data, buffer->out.size, &size);
    if (!result)
    {
        /* Move remaining data  */
        buffer->out.offset += size;
        buffer->out.size -= size;
        memmove(buffer->out.data, buffer->out.data + buffer->out.offset, buffer->out.size);
        buffer->out.offset = 0;

        if (buffer->out.size)
            return BH_SHORT;
    }

    return result;
}


static int bufferRead(BH_Buffer *buffer,
                      BH_IOReadInfo *info)
{
    size_t readed, size;
    int result;

    result = BH_OK;
    for (readed = 0; readed < info->size; )
    {
        /* Refill input buffer if needed */
        if (!buffer->in.size && ((result = bufferRefill(buffer)) || !buffer->in.size))
            break;

        /* Copy data from buffer into user buffer */
        size = MIN(info->size - readed, buffer->in.size);
        memcpy(info->data + readed, buffer->in.data + buffer->in.offset, size);
        buffer->in.offset += size;
        buffer->in.size -= size;
        readed += size;
    }

    /* Report readed size */
    if (info->actual)
        *info->actual = readed;
    return result;
}


static int bufferWrite(BH_Buffer *buffer,
                       BH_IOWriteInfo *info)
{
    size_t written, size;
    int result;

    result = BH_OK;
    for (written = 0; written < info->size; )
    {
        /* Write data into output buffer */
        size = MIN(info->size - written, buffer->out.capacity - buffer->out.size);
        memcpy(buffer->out.data + buffer->out.size, info->data + written, size);
        buffer->out.size += size;
        written += size;

        /* Flush output buffer if needed */
        if (buffer->out.size == buffer->out.capacity && (result = bufferFlush(buffer)))
            break;
    }

    /* Report written size */
    if (info->actual)
        *info->actual = written;
    return result;
}


int bufferPeek(BH_Buffer *buffer,
               BH_IOReadInfo *info)
{
    size_t size;
    int result;

    /* Requested size can't be bigger then buffer capacity */
    if (info->size > buffer->in.capacity)
        return BH_FULL;

    /* Try to refill the buffer if we dont have enough data */
    if (info->size > buffer->in.size && (result = bufferRefill(buffer)))
        return result;

    /* Copy data */
    size = MIN(info->size, buffer->in.size);
    memcpy(info->data, buffer->in.data + buffer->in.offset, size);

    if (info->actual)
        *info->actual = size;
    return BH_OK;
}


static int bufferGetIO(BH_Buffer *buffer,
                       BH_IO **io)
{
    *io = buffer->device;
    return BH_OK;
}


static int bufferSetIO(BH_Buffer *buffer,
                       BH_IO *io)
{
    /* Reset buffer states and change input/output deivce */
    buffer->in.offset = 0;
    buffer->in.size = 0;
    buffer->out.offset = 0;
    buffer->out.size = 0;
    buffer->device = io;

    return BH_OK;
}


static int bufferCap(BH_Buffer *buffer,
                     int *op)
{
    BH_UNUSED(buffer);

    /* Return operations supported by the buffer input/output device */
    switch (*op)
    {
    case BH_IO_CTL_FLUSH:
    case BH_IO_CTL_PEEK:
    case BH_IO_CTL_GET_IO:
    case BH_IO_CTL_SET_IO:
        return BH_OK;

    default:
        return BH_NOIMPL;
    }
}


static int bufferCtl(BH_Buffer *buffer,
                     BH_IOCtlInfo *info)
{
    /* Handle supported operations */
    switch (info->op)
    {
    case BH_IO_CTL_FLUSH:
        return bufferFlush(buffer);

    case BH_IO_CTL_PEEK:
        return bufferPeek(buffer, (BH_IOReadInfo *)info->arg);

    case BH_IO_CTL_GET_IO:
        return bufferGetIO(buffer, (BH_IO **)info->arg);

    case BH_IO_CTL_SET_IO:
        return bufferSetIO(buffer, (BH_IO *)info->arg);

    default:
        return BH_NOIMPL;
    }
}


static int bufferCallback(BH_Buffer *buffer,
                          int type,
                          void *arg)
{
    /* Handle basic input/output operations */
    switch (type)
    {
    case BH_IO_OP_DESTROY:  return bufferDestroy(buffer);
    case BH_IO_OP_READ:     return bufferRead(buffer, (BH_IOReadInfo *)arg);
    case BH_IO_OP_WRITE:    return bufferWrite(buffer, (BH_IOWriteInfo *)arg);
    case BH_IO_OP_CTL:      return bufferCtl(buffer, (BH_IOCtlInfo *)arg);
    case BH_IO_OP_CAP:      return bufferCap(buffer, (int*)arg);
    default:                return BH_NOIMPL;
    }
}


BH_IO *BH_BufferNew(BH_IO *device,
                    size_t size,
                    int *result)
{
    BH_Buffer *buffer;
    int code;

    code = BH_OOM;

    /* Allocate new buffer object and initialize it */
    if ((buffer = malloc(sizeof(*buffer))))
    {
        buffer->parent.callback = (BH_IOCallback)bufferCallback;
        if ((code = bufferInit(buffer, device, size)))
        {
            free(buffer);
            buffer = NULL;
        }
    }

    /* Report error code */
    if (result)
        *result = code;

    return (BH_IO*)buffer;
}


int BH_IOIsBuffer(BH_IO *device)
{
    if (!device)
        return 0;

    return device->callback == (BH_IOCallback)bufferCallback;
}
