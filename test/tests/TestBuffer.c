#include <BH/IO.h>
#include <BH/Unit.h>
#include <string.h>
#include <stdio.h>


BH_UNIT_TEST(Null)
{
    BH_VERIFY(BH_BufferNew(NULL, 0, NULL) == NULL);
    BH_VERIFY(BH_IOIsBuffer(NULL) == 0);
    return 0;
}


BH_UNIT_TEST(Write)
{
    BH_IO *buffer, *io;
    char data[16];
    int64_t offset;
    size_t size;

    memset(data, 0, 16);
    BH_VERIFY((io = BH_BytesNew(data, 16, NULL)) != NULL);
    BH_VERIFY((buffer = BH_BufferNew(io, 4, NULL)) != NULL);
    BH_VERIFY(BH_IOIsBuffer(buffer));

    BH_VERIFY(BH_IOWrite(buffer, "1234567", 7, &size) == BH_OK);
    BH_VERIFY(size == 7);

    BH_VERIFY(BH_IOWrite(buffer, "8901234", 7, &size) == BH_OK);
    BH_VERIFY(size == 7);

    BH_VERIFY(BH_IOWrite(buffer, "5", 1, &size) == BH_OK);
    BH_VERIFY(size == 1);
    BH_VERIFY(memcmp(data, "123456789012", 13) == 0);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(offset == 12);

    BH_VERIFY(BH_IOFlush(buffer) == BH_OK);
    BH_VERIFY(memcmp(data, "123456789012345", 15) == 0);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(offset == 15);

    BH_VERIFY(BH_IOWrite(buffer, "678", 3, &size) == BH_OK);
    BH_VERIFY(size == 3);
    BH_VERIFY(BH_IOFlush(buffer) != BH_OK);
    BH_VERIFY(memcmp(data, "1234567890123456", 16) == 0);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(offset == 16);

    BH_IOFree(buffer);
    BH_IOFree(io);
    return 0;
}


BH_UNIT_TEST(Read)
{
    BH_IO *buffer, *io;
    char data[16];
    char tmp[4];
    size_t size;

    memset(data, '1', 16);
    BH_VERIFY((io = BH_BytesNew(data, 16, NULL)) != NULL);
    BH_VERIFY((buffer = BH_BufferNew(io, 4, NULL)) != NULL);

    BH_VERIFY(BH_IORead(buffer, tmp, 2, &size) == BH_OK);
    BH_VERIFY(size == 2);
    BH_VERIFY(memcmp(tmp, "11", 2) == 0);
    memset(data, '2', 16);

    BH_VERIFY(BH_IORead(buffer, tmp, 2, &size) == BH_OK);
    BH_VERIFY(size == 2);
    BH_VERIFY(memcmp(tmp, "11", 2) == 0);

    BH_VERIFY(BH_IORead(buffer, tmp, 2, &size) == BH_OK);
    BH_VERIFY(size == 2);
    BH_VERIFY(memcmp(tmp, "22", 2) == 0);

    BH_IOFree(buffer);
    BH_IOFree(io);
    return 0;
}


BH_UNIT_TEST(Reset)
{
    BH_IO *buffer, *io, *previous;
    char data[16];
    char tmp[4];
    size_t size;

    memset(data, '1', 16);
    BH_VERIFY((io = BH_BytesNew(data, 16, NULL)) != NULL);
    BH_VERIFY((buffer = BH_BufferNew(io, 4, NULL)) != NULL);

    BH_VERIFY(BH_IORead(buffer, tmp, 2, &size) == BH_OK);
    BH_VERIFY(size == 2);
    BH_VERIFY(memcmp(tmp, "11", 2) == 0);
    memset(data, '2', 16);

    BH_VERIFY(BH_IOCtl(buffer, BH_IO_CTL_GET_IO, &previous) == BH_OK);
    BH_VERIFY(previous == io);
    BH_VERIFY(BH_IOCtl(buffer, BH_IO_CTL_SET_IO, io) == BH_OK);
    BH_VERIFY(BH_IORead(buffer, tmp, 2, &size) == BH_OK);
    BH_VERIFY(size == 2);
    BH_VERIFY(memcmp(tmp, "22", 2) == 0);

    BH_IOFree(buffer);
    BH_IOFree(io);
    return 0;
}


int main(int argc,
         char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_UNIT_ADD(Null);
    BH_UNIT_ADD(Write);
    BH_UNIT_ADD(Read);
    BH_UNIT_ADD(Reset);

    return BH_UnitRun();
}
