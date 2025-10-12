#include <BH/IO.h>
#include <BH/Unit.h>
#include <string.h>


#define FILENAME1 "bhfile1.dat"
#define FILENAME2 "bhfile2.dat"
#define FILENAME3 "bhfile3.dat"
#define FILENAME4 "bhfile4.dat"


/**
 * Cleanup any files, that could be left from previous test runs.
 */
static void cleanup(void)
{
    remove(FILENAME1);
    remove(FILENAME2);
    remove(FILENAME3);
    remove(FILENAME4);
}


/**
 * Check for invalid arguments.
 */
static int checkNull(void)
{
    /* Check against NULL pointers */
    BH_VERIFY(BH_IORead(NULL, NULL, 0, NULL) != BH_OK);
    BH_VERIFY(BH_IOWrite(NULL, NULL, 0, NULL) != BH_OK);
    BH_VERIFY(BH_IOPeek(NULL, NULL, 0, NULL) != BH_OK);
    BH_VERIFY(BH_IOTell(NULL, NULL) != BH_OK);
    BH_VERIFY(BH_IOSeek(NULL, 0, 0) != BH_OK);
    BH_VERIFY(BH_IOFlush(NULL) != BH_OK);
    BH_VERIFY(BH_IOSize(NULL, NULL) != BH_OK);
    BH_VERIFY(BH_IOFlags(NULL, NULL) != BH_OK);
    BH_VERIFY(BH_IOClear(NULL) != BH_OK);
    BH_VERIFY(BH_IOCtl(NULL, 0, NULL) != BH_OK);
    BH_VERIFY(BH_IOCap(NULL, 0) != BH_OK);
    BH_VERIFY(BH_IOEndOfFile(NULL) != BH_OK);
    BH_VERIFY(BH_IOError(NULL) != BH_OK);
    BH_IOFree(NULL);

    return 0;
}


/**
 * Check for normal mode.
 */
static int checkNormal(void)
{
    int64_t position;
    char buffer[128];
    size_t actual;
    BH_IO *io;

    /* Check operations for write only access */
    BH_VERIFY((io = BH_FileNew(FILENAME1, BH_FILE_WRITE, NULL)) != NULL);
    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(BH_IOSeek(io, 10, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IOWrite(io, "abcde", 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);

    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, 1, &actual) != BH_OK);
    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_END) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &position) == BH_OK);
    BH_VERIFY(position == 20);
    BH_IOFree(io);

    /* Check operations for read only access */
    BH_VERIFY((io = BH_FileNew(FILENAME1, BH_FILE_READ, NULL)) != NULL);
    BH_VERIFY(BH_IORead(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);
    BH_VERIFY(memcmp(buffer, "1234567890", 10) == 0);

    BH_VERIFY(BH_IORead(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "abcde", 5) == 0);

    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, sizeof(buffer), &actual) == BH_OK);
    BH_VERIFY(actual == 20);
    BH_VERIFY(memcmp(buffer, "1234567890abcde67890", 20) == 0);

    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) != BH_OK);
    BH_VERIFY(BH_IOSeek(io, -5, BH_IO_SEEK_CUR) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "67890", 5) == 0);
    BH_IOFree(io);

    /* Check operations for read and write access */
    BH_VERIFY((io = BH_FileNew(FILENAME1, BH_FILE_READWRITE, NULL)) != NULL);

    BH_VERIFY(BH_IOWrite(io, "abcde", 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);

    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(BH_IOWrite(io, "1234567890abcde67890", 20, &actual) == BH_OK);
    BH_VERIFY(actual == 20);

    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "abcde", 5) == 0);

    BH_VERIFY(BH_IORead(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);
    BH_VERIFY(memcmp(buffer, "1234567890", 10) == 0);

    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, 35, &actual) == BH_OK);
    BH_VERIFY(actual == 35);
    BH_VERIFY(memcmp(buffer, "abcde12345678901234567890abcde67890", 35) == 0);
    BH_IOFree(io);
    return 0;
}


/**
 * Check for truncate mode.
 */
static int checkTruncate(void)
{
    int64_t position;
    char buffer[128];
    size_t actual;
    BH_IO *io;

    /* Check operations for write only access */
    BH_VERIFY((io = BH_FileNew(FILENAME1, BH_FILE_WRITE | BH_FILE_TRUNCATE, NULL)) != NULL);
    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(BH_IOSeek(io, 10, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IOWrite(io, "abcde", 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);

    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, 1, &actual) != BH_OK);
    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_END) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &position) == BH_OK);
    BH_VERIFY(position == 20);
    BH_IOFree(io);

    /* Check operations for read only access without truncate */
    BH_VERIFY((io = BH_FileNew(FILENAME1, BH_FILE_READ, NULL)) != NULL);
    BH_VERIFY(BH_IORead(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);
    BH_VERIFY(memcmp(buffer, "1234567890", 10) == 0);

    BH_VERIFY(BH_IORead(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "abcde", 5) == 0);

    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, sizeof(buffer), &actual) == BH_OK);
    BH_VERIFY(actual == 20);
    BH_VERIFY(memcmp(buffer, "1234567890abcde67890", 20) == 0);

    BH_VERIFY(BH_IOSeek(io, -5, BH_IO_SEEK_CUR) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "67890", 5) == 0);
    BH_IOFree(io);

    /* Check operations for read only access */
    BH_VERIFY((io = BH_FileNew(FILENAME1, BH_FILE_READ | BH_FILE_TRUNCATE, NULL)) != NULL);
    BH_VERIFY(BH_IORead(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 0);

    BH_VERIFY(BH_IORead(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 0);

    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) != BH_OK);
    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, sizeof(buffer), &actual) == BH_OK);
    BH_VERIFY(actual == 0);
    BH_IOFree(io);

    /* Check operations for read and write access */
    BH_VERIFY((io = BH_FileNew(FILENAME1, BH_FILE_READWRITE | BH_FILE_TRUNCATE, NULL)) != NULL);
    BH_VERIFY(BH_IOWrite(io, "abcde", 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);

    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(BH_IOWrite(io, "1234567890abcde67890", 20, &actual) == BH_OK);
    BH_VERIFY(actual == 20);

    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "abcde", 5) == 0);

    BH_VERIFY(BH_IORead(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);
    BH_VERIFY(memcmp(buffer, "1234567890", 10) == 0);

    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, 35, &actual) == BH_OK);
    BH_VERIFY(actual == 35);
    BH_VERIFY(memcmp(buffer, "abcde12345678901234567890abcde67890", 35) == 0);
    BH_IOFree(io);

    BH_VERIFY((io = BH_FileNew(FILENAME1, BH_FILE_WRITE | BH_FILE_TRUNCATE, NULL)) != NULL);
    BH_IOFree(io);

    return 0;
}


/**
 * Check for exist mode.
 */
static int checkExist(void)
{
    int64_t position;
    char buffer[128];
    size_t actual;
    BH_IO *io;

    /* Check operations for write only access */
    BH_VERIFY((io = BH_FileNew(FILENAME1, BH_FILE_WRITE | BH_FILE_EXIST, NULL)) != NULL);

    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(BH_IOSeek(io, 10, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IOWrite(io, "abcde", 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);

    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, 1, &actual) != BH_OK);
    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_END) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &position) == BH_OK);
    BH_VERIFY(position == 20);
    BH_IOFree(io);

    /* Check operations for read only access */
    BH_VERIFY((io = BH_FileNew(FILENAME1,  BH_FILE_READ | BH_FILE_EXIST, NULL)) != NULL);

    BH_VERIFY(BH_IORead(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);
    BH_VERIFY(memcmp(buffer, "1234567890", 10) == 0);

    BH_VERIFY(BH_IORead(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "abcde", 5) == 0);

    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, sizeof(buffer), &actual) == BH_OK);
    BH_VERIFY(actual == 20);
    BH_VERIFY(memcmp(buffer, "1234567890abcde67890", 20) == 0);

    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) != BH_OK);
    BH_VERIFY(BH_IOSeek(io, -5, BH_IO_SEEK_CUR) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "67890", 5) == 0);
    BH_IOFree(io);

    /* Check operations for read and write access */
    BH_VERIFY((io = BH_FileNew(FILENAME1, BH_FILE_WRITE | BH_FILE_READ | BH_FILE_EXIST, NULL)) != NULL);

    BH_VERIFY(BH_IOWrite(io, "abcde", 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);

    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(BH_IOWrite(io, "1234567890abcde67890", 20, &actual) == BH_OK);
    BH_VERIFY(actual == 20);

    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "abcde", 5) == 0);

    BH_VERIFY(BH_IORead(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);
    BH_VERIFY(memcmp(buffer, "1234567890", 10) == 0);

    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, 35, &actual) == BH_OK);
    BH_VERIFY(actual == 35);
    BH_VERIFY(memcmp(buffer, "abcde12345678901234567890abcde67890", 35) == 0);
    BH_IOFree(io);

    /* Check against non existing files */
    BH_VERIFY(BH_FileNew(FILENAME2, BH_FILE_WRITE | BH_FILE_EXIST, NULL) == NULL);
    BH_VERIFY(BH_FileNew(FILENAME2, BH_FILE_READ | BH_FILE_EXIST, NULL) == NULL);
    BH_VERIFY(BH_FileNew(FILENAME2, BH_FILE_READWRITE | BH_FILE_EXIST, NULL) == NULL);
    return 0;
}


/**
 * Check in append mode.
 */
static int checkAppend(void)
{
    int64_t position;
    char buffer[128];
    size_t actual;
    BH_IO *io;

    /* Explicitly call cleanup */
    cleanup();

    /* Check operations for write only access */
    BH_VERIFY((io = BH_FileNew(FILENAME1,  BH_FILE_WRITE | BH_FILE_APPEND, NULL)) != NULL);

    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(BH_IOSeek(io, 10, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IOWrite(io, "abcde", 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);

    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, 1, &actual) != BH_OK);
    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_END) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &position) == BH_OK);
    BH_VERIFY(position == 25);
    BH_IOFree(io);

    /* Check operations for read only access */
    BH_VERIFY((io = BH_FileNew(FILENAME1,  BH_FILE_READ | BH_FILE_APPEND, NULL)) != NULL);

    BH_VERIFY(BH_IORead(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);
    BH_VERIFY(memcmp(buffer, "1234567890", 10) == 0);

    BH_VERIFY(BH_IORead(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);
    BH_VERIFY(memcmp(buffer, "1234567890", 10) == 0);

    BH_VERIFY(BH_IORead(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "abcde", 5) == 0);

    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) != BH_OK);
    BH_VERIFY(BH_IOSeek(io, -5, BH_IO_SEEK_CUR) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "abcde", 5) == 0);
    BH_IOFree(io);

    /* Check operations for read and write access */
    BH_VERIFY((io = BH_FileNew(FILENAME1,  BH_FILE_READWRITE | BH_FILE_APPEND, NULL)) != NULL);

    BH_VERIFY(BH_IOWrite(io, "abcde", 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);

    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IORead(io, buffer, 40, &actual) == BH_OK);
    BH_VERIFY(actual == 40);
    BH_VERIFY(memcmp(buffer, "12345678901234567890abcdeabcde1234567890", 40) == 0);
    BH_IOFree(io);

    BH_VERIFY((io = BH_FileNew(FILENAME1,  BH_FILE_WRITE | BH_FILE_TRUNCATE, NULL)) != NULL);

    BH_IOFree(io);

    return 0;
}


/**
 * Check for create mode.
 */
static int checkCreate(void)
{
    BH_IO *io;

    /* Check for already existing file */
    BH_VERIFY(BH_FileNew(FILENAME1, BH_FILE_WRITE | BH_FILE_CREATE, NULL) == NULL);

    /* Check for new file with write access */
    BH_VERIFY((io = BH_FileNew(FILENAME2,  BH_FILE_WRITE | BH_FILE_CREATE, NULL)) != NULL);
    BH_IOFree(io);

    /* Check for new file with read access */
    BH_VERIFY((io = BH_FileNew(FILENAME3,  BH_FILE_READ | BH_FILE_CREATE, NULL)) != NULL);
    BH_IOFree(io);

    /* Check for new file with read/write access */
    BH_VERIFY((io = BH_FileNew(FILENAME4,  BH_FILE_READWRITE | BH_FILE_CREATE, NULL)) != NULL);
    BH_IOFree(io);

    return 0;
}


/**
 * Check for EOF flags.
 */
static int checkEOF(void)
{
    char buffer[128];
    size_t actual;
    BH_IO *io;

    BH_VERIFY((io = BH_FileNew(FILENAME1,  BH_FILE_READ | BH_FILE_TRUNCATE, NULL)) != NULL);

    BH_VERIFY(BH_IORead(io, buffer, 128, &actual) == BH_OK);
    BH_VERIFY(actual == 0);
    BH_VERIFY(BH_IOEndOfFile(io));

    BH_IOFree(io);

    return 0;
}


/**
 * Check for error flags.
 */
static int checkError(void)
{
    size_t actual;
    BH_IO *io;

    BH_VERIFY((io = BH_FileNew(FILENAME1,  BH_FILE_READ, NULL)) != NULL);

    BH_VERIFY(BH_IOWrite(io, "12345", 5, &actual) != BH_OK);
    BH_VERIFY(BH_IOError(io) != BH_OK);
    BH_VERIFY(BH_IOClear(io) == BH_OK);
    BH_VERIFY(BH_IOError(io) == BH_OK);

    BH_IOFree(io);

    return 0;
}


/**
 * Check peek operation.
 */
static int checkPeek(void)
{
    int64_t previous, current;
    char buffer[128];
    size_t actual;
    BH_IO *io;

    BH_VERIFY((io = BH_FileNew(FILENAME1,  BH_FILE_READWRITE | BH_FILE_TRUNCATE, NULL)) != NULL);

    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(BH_IOWrite(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &previous) == BH_OK);
    BH_VERIFY(BH_IOPeek(io, buffer, 128, &actual) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &current) == BH_OK);
    BH_VERIFY(actual == 20);
    BH_VERIFY(memcmp(buffer, "12345678901234567890", 20) == 0);
    BH_VERIFY(previous == current);

    BH_VERIFY(BH_IOSeek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &previous) == BH_OK);
    BH_VERIFY(BH_IOPeek(io, buffer, 128, &actual) == BH_OK);
    BH_VERIFY(BH_IOTell(io, &current) == BH_OK);
    BH_VERIFY(actual == 20);
    BH_VERIFY(memcmp(buffer, "12345678901234567890", 20) == 0);
    BH_VERIFY(previous == current);

    BH_IOFree(io);

    return 0;
}


/**
 * Check file size operation.
 */
static int checkSize(void)
{
    BH_IO *io;
    int64_t size;

    BH_VERIFY((io = BH_FileNew(FILENAME1,  BH_FILE_READ, NULL)) != NULL);

    BH_VERIFY(BH_IOSize(io, &size) == BH_OK);
    BH_VERIFY(size == 20);

    BH_IOFree(io);
    return 0;
}


int main(int argc,
         char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    /* Cleanup */
    cleanup();

    BH_UnitAdd("Null", checkNull);
    BH_UnitAdd("Normal", checkNormal);
    BH_UnitAdd("Truncate", checkTruncate);
    BH_UnitAdd("Exist", checkExist);
    BH_UnitAdd("Append", checkAppend);
    BH_UnitAdd("Create", checkCreate);
    BH_UnitAdd("EOF", checkEOF);
    BH_UnitAdd("Error", checkError);
    BH_UnitAdd("Peek", checkPeek);
    BH_UnitAdd("Size", checkSize);

    return BH_UnitRun();
}
