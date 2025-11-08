#include <BH/IO.h>
#include <BH/Unit.h>
#include <string.h>


BH_UNIT_TEST(Null)
{
    char data;

    BH_VERIFY(BH_BytesNew(NULL, 0, NULL) == NULL);
    BH_VERIFY(BH_BytesNew(&data, 0, NULL) == NULL);
    BH_VERIFY(BH_BytesNew(NULL, 1234, NULL) == NULL);
    BH_VERIFY(BH_IOIsBytes(NULL) == 0);

    return 0;
}


BH_UNIT_TEST(Read)
{
    BH_IO *io;
    char buffer1[14] = "Hello, world!";
    char buffer2[14];
    size_t size;

    BH_VERIFY((io = BH_BytesNew(buffer1, 14, NULL)) != NULL);
    BH_VERIFY(BH_IOIsBytes(io));
    BH_VERIFY(BH_IORead(io, buffer2, 14, &size) == BH_OK);
    BH_VERIFY(size == 14);
    BH_VERIFY(memcmp(buffer1, buffer2, 14) == 0);
    BH_VERIFY(BH_IOEndOfFile(io));

    BH_VERIFY(BH_IORead(io, buffer2, 14, &size) == BH_OK);
    BH_VERIFY(size == 0);
    BH_VERIFY(BH_IOEndOfFile(io));
    BH_IOFree(io);

    return 0;
}


BH_UNIT_TEST(Write)
{
    BH_IO *io;
    char buffer[14];
    size_t size;

    BH_VERIFY((io = BH_BytesNew(buffer, 14, NULL)) != NULL);
    BH_VERIFY(BH_IOWrite(io, "Hello, world!", 14, &size) == BH_OK);
    BH_VERIFY(size == 14);
    BH_VERIFY(memcmp(buffer, "Hello, world!", 14) == 0);

    BH_VERIFY(BH_IOWrite(io, "Something", 10, &size) == BH_OK);
    BH_VERIFY(size == 0);
    BH_VERIFY(memcmp(buffer, "Hello, world!", 14) == 0);
    BH_IOFree(io);

    return 0;
}


BH_UNIT_TEST(SeekTell)
{
    BH_IO *io;
    char buffer[14] = "Hello, world!";
    char symbol;
    int64_t offset;
    size_t size;

    BH_VERIFY((io = BH_BytesNew(buffer, 14, NULL)) != NULL);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(offset == 0);
    BH_VERIFY(BH_IORead(io, &symbol, 1, &size) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(size == 1);
    BH_VERIFY(symbol == 'H');
    BH_VERIFY(offset == 1);

    BH_VERIFY(BH_IOSeek(io, 8, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(offset == 8);
    BH_VERIFY(BH_IORead(io, &symbol, 1, &size) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(size == 1);
    BH_VERIFY(symbol == 'o');
    BH_VERIFY(offset == 9);

    BH_VERIFY(BH_IOSeek(io, -1, BH_IO_SEEK_CUR) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(offset == 8);
    BH_VERIFY(BH_IORead(io, &symbol, 1, &size) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(size == 1);
    BH_VERIFY(symbol == 'o');
    BH_VERIFY(offset == 9);

    BH_VERIFY(BH_IOSeek(io, -123456, BH_IO_SEEK_CUR) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(offset == 0);
    BH_VERIFY(BH_IORead(io, &symbol, 1, &size) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(size == 1);
    BH_VERIFY(symbol == 'H');
    BH_VERIFY(offset == 1);

    BH_VERIFY(BH_IOSeek(io, 123456, BH_IO_SEEK_CUR) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(offset == 14);
    BH_VERIFY(BH_IORead(io, &symbol, 1, &size) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(size == 0);
    BH_VERIFY(offset == 14);

    BH_VERIFY(BH_IOSeek(io, -1, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(offset == 0);

    BH_VERIFY(BH_IOSeek(io, 123456, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(offset == 14);

    BH_VERIFY(BH_IOSeek(io, 123456, BH_IO_SEEK_END) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(offset == 14);

    BH_VERIFY(BH_IOSeek(io, -123456, BH_IO_SEEK_END) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(offset == 0);

    BH_VERIFY(BH_IOSeek(io, -2, BH_IO_SEEK_END) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &offset) == BH_OK);
    BH_VERIFY(offset == 12);
    BH_VERIFY(BH_IORead(io, &symbol, 1, &size) == BH_OK);
    BH_VERIFY(size == 1);
    BH_VERIFY(symbol == '!');

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
    BH_UNIT_ADD(SeekTell);


    return BH_UnitRun();
}
