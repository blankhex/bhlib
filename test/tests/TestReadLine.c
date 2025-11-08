#include <BH/Unit.h>
#include <BH/IO.h>
#include <string.h>


static const char testInput[] =
    "this is a very long line that exceeds the buffer\n"
    "short\n"
    "another line\n";


BH_UNIT_TEST(ReadLine)
{
    char buffer[32], *result;
    BH_IO *io;

    BH_VERIFY((io = BH_BytesNew((char*)testInput, strlen(testInput), NULL)));

    /* Check splited read */
    BH_VERIFY((result = BH_IOReadLine(io, buffer, sizeof(buffer))));
    BH_VERIFY_STR_EQ(buffer, "this is a very long line that e");

    BH_VERIFY((result = BH_IOReadLine(io, buffer, sizeof(buffer))));
    BH_VERIFY_STR_EQ(buffer, "xceeds the buffer\n");

    /* Check smaller reads */
    BH_VERIFY((result = BH_IOReadLine(io, buffer, sizeof(buffer))));
    BH_VERIFY_STR_EQ(buffer, "short\n");

    BH_VERIFY((result = BH_IOReadLine(io, buffer, sizeof(buffer))));
    BH_VERIFY_STR_EQ(buffer, "another line\n");

    /* Check EOF */
    BH_VERIFY(!(result = BH_IOReadLine(io, buffer, sizeof(buffer))));
    BH_IOFree(io);

    return 0;
}


BH_UNIT_TEST(ReadLineFull)
{
    char buffer[32], *result;
    BH_IO *io;

    BH_VERIFY((io = BH_BytesNew((char*)testInput, strlen(testInput), NULL)));

    /* Check truncated read */
    BH_VERIFY((result = BH_IOReadLineFull(io, buffer, sizeof(buffer))));
    BH_VERIFY_STR_EQ(buffer, "this is a very long line that e");

    /* Check smaller reads */
    BH_VERIFY((result = BH_IOReadLineFull(io, buffer, sizeof(buffer))));
    BH_VERIFY_STR_EQ(buffer, "short\n");

    BH_VERIFY((result = BH_IOReadLineFull(io, buffer, sizeof(buffer))));
    BH_VERIFY_STR_EQ(buffer, "another line\n");

    /* Check EOF */
    BH_VERIFY(!(result = BH_IOReadLineFull(io, buffer, sizeof(buffer))));
    BH_IOFree(io);

    return 0;
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_UNIT_ADD(ReadLine);
    BH_UNIT_ADD(ReadLineFull);

    return BH_UnitRun();
}
