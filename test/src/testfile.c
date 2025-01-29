#include <bh/unit.h>
#include <bh/io.h>
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
static int check_null(void)
{
    bh_io_t *io;

    /* Check against NULL pointers */
    BH_VERIFY(bh_file_new(NULL) == NULL);
    BH_VERIFY(bh_io_classname(NULL) == NULL);
    BH_VERIFY(bh_io_open(NULL, 0) != BH_OK);
    BH_VERIFY(bh_io_close(NULL) != BH_OK);
    BH_VERIFY(bh_io_read(NULL, NULL, 0, NULL) != BH_OK);
    BH_VERIFY(bh_io_write(NULL, NULL, 0, NULL) != BH_OK);
    BH_VERIFY(bh_io_peek(NULL, NULL, 0, NULL) != BH_OK);
    BH_VERIFY(bh_io_tell(NULL, NULL) != BH_OK);
    BH_VERIFY(bh_io_seek(NULL, 0, 0) != BH_OK);
    BH_VERIFY(bh_io_flush(NULL) != BH_OK);
    BH_VERIFY(bh_io_size(NULL, NULL) != BH_OK);
    BH_VERIFY(bh_io_flags(NULL) == BH_IO_FLAG_ERROR);
    BH_VERIFY(bh_io_clear(NULL) == BH_OK);
    bh_io_free(NULL);

    /* Check against NULL pointers and valid IO object */
    BH_VERIFY((io = bh_file_new(FILENAME1)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, 0) != BH_OK);
    BH_VERIFY(bh_io_close(io) != BH_OK);
    BH_VERIFY(bh_io_read(io, NULL, 0, NULL) != BH_OK);
    BH_VERIFY(bh_io_write(io, NULL, 0, NULL) != BH_OK);
    BH_VERIFY(bh_io_peek(io, NULL, 0, NULL) != BH_OK);
    BH_VERIFY(bh_io_tell(io, NULL) != BH_OK);
    BH_VERIFY(bh_io_seek(io, 0, 0) != BH_OK);
    BH_VERIFY(bh_io_flush(io) != BH_OK);
    BH_VERIFY(bh_io_size(io, NULL) != BH_OK);
    BH_VERIFY(bh_io_flags(io) == BH_IO_FLAG_ERROR);
    BH_VERIFY(bh_io_clear(io) == BH_OK);
    bh_io_free(io);

    return 0;
}


/**
 * Check for normal mode.
 */
static int check_normal(void)
{
    int64_t position;
    char buffer[128];
    size_t actual;
    bh_io_t *io;

    /* Check operations for write only access */
    BH_VERIFY((io = bh_file_new(FILENAME1)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_WRITE) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);

    BH_VERIFY(bh_io_open(io, BH_IO_READ) != BH_OK);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(bh_io_seek(io, 10, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_write(io, "abcde", 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);

    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, 1, &actual) != BH_OK);
    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_END) == BH_OK);
    BH_VERIFY(bh_io_tell(io, &position) == BH_OK);
    BH_VERIFY(position == 20);
    bh_io_close(io);

    /* Check operations for read only access */
    BH_VERIFY(bh_io_open(io, BH_IO_READ) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_read(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);
    BH_VERIFY(memcmp(buffer, "1234567890", 10) == 0);

    BH_VERIFY(bh_io_read(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "abcde", 5) == 0);

    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, sizeof(buffer), &actual) == BH_OK);
    BH_VERIFY(actual == 20);
    BH_VERIFY(memcmp(buffer, "1234567890abcde67890", 20) == 0);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) != BH_OK);
    BH_VERIFY(bh_io_seek(io, -5, BH_IO_SEEK_CUR) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "67890", 5) == 0);
    bh_io_free(io);

    /* Check operations for read and write access */
    BH_VERIFY((io = bh_file_new(FILENAME1)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_WRITE | BH_IO_READ) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);

    BH_VERIFY(bh_io_write(io, "abcde", 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(bh_io_write(io, "1234567890abcde67890", 20, &actual) == BH_OK);
    BH_VERIFY(actual == 20);

    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "abcde", 5) == 0);

    BH_VERIFY(bh_io_read(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);
    BH_VERIFY(memcmp(buffer, "1234567890", 10) == 0);

    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, 35, &actual) == BH_OK);
    BH_VERIFY(actual == 35);
    BH_VERIFY(memcmp(buffer, "abcde12345678901234567890abcde67890", 35) == 0);
    bh_io_close(io);

    bh_io_free(io);
    return 0;
}


/**
 * Check for truncate mode.
 */
static int check_truncate(void)
{
    int64_t position;
    char buffer[128];
    size_t actual;
    bh_io_t *io;

    /* Check operations for write only access */
    BH_VERIFY((io = bh_file_new(FILENAME1)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_WRITE | BH_IO_TRUNCATE) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(bh_io_seek(io, 10, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_write(io, "abcde", 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);

    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, 1, &actual) != BH_OK);
    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_END) == BH_OK);
    BH_VERIFY(bh_io_tell(io, &position) == BH_OK);
    BH_VERIFY(position == 20);
    bh_io_close(io);

    /* Check operations for read only access without truncate */
    BH_VERIFY(bh_io_open(io, BH_IO_READ) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);
    BH_VERIFY(bh_io_read(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);
    BH_VERIFY(memcmp(buffer, "1234567890", 10) == 0);

    BH_VERIFY(bh_io_read(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "abcde", 5) == 0);

    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, sizeof(buffer), &actual) == BH_OK);
    BH_VERIFY(actual == 20);
    BH_VERIFY(memcmp(buffer, "1234567890abcde67890", 20) == 0);

    BH_VERIFY(bh_io_seek(io, -5, BH_IO_SEEK_CUR) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "67890", 5) == 0);
    bh_io_close(io);

    /* Check operations for read only access */
    BH_VERIFY(bh_io_open(io, BH_IO_READ | BH_IO_TRUNCATE) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);
    BH_VERIFY(bh_io_read(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 0);

    BH_VERIFY(bh_io_read(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 0);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) != BH_OK);
    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, sizeof(buffer), &actual) == BH_OK);
    BH_VERIFY(actual == 0);
    bh_io_free(io);

    /* Check operations for read and write access */
    BH_VERIFY((io = bh_file_new(FILENAME1)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_WRITE | BH_IO_READ | BH_IO_TRUNCATE) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);

    BH_VERIFY(bh_io_write(io, "abcde", 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(bh_io_write(io, "1234567890abcde67890", 20, &actual) == BH_OK);
    BH_VERIFY(actual == 20);

    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "abcde", 5) == 0);

    BH_VERIFY(bh_io_read(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);
    BH_VERIFY(memcmp(buffer, "1234567890", 10) == 0);

    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, 35, &actual) == BH_OK);
    BH_VERIFY(actual == 35);
    BH_VERIFY(memcmp(buffer, "abcde12345678901234567890abcde67890", 35) == 0);
    bh_io_close(io);

    BH_VERIFY(bh_io_open(io, BH_IO_WRITE | BH_IO_TRUNCATE) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);
    bh_io_close(io);

    bh_io_free(io);
    return 0;
}


/**
 * Check for exist mode.
 */
static int check_exist(void)
{
    int64_t position;
    char buffer[128];
    size_t actual;
    bh_io_t *io;

    /* Check operations for write only access */
    BH_VERIFY((io = bh_file_new(FILENAME1)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_WRITE | BH_IO_EXIST) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(bh_io_seek(io, 10, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_write(io, "abcde", 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);

    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, 1, &actual) != BH_OK);
    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_END) == BH_OK);
    BH_VERIFY(bh_io_tell(io, &position) == BH_OK);
    BH_VERIFY(position == 20);
    bh_io_close(io);

    /* Check operations for read only access */
    BH_VERIFY(bh_io_open(io, BH_IO_READ | BH_IO_EXIST) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);
    BH_VERIFY(bh_io_read(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);
    BH_VERIFY(memcmp(buffer, "1234567890", 10) == 0);

    BH_VERIFY(bh_io_read(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "abcde", 5) == 0);

    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, sizeof(buffer), &actual) == BH_OK);
    BH_VERIFY(actual == 20);
    BH_VERIFY(memcmp(buffer, "1234567890abcde67890", 20) == 0);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) != BH_OK);
    BH_VERIFY(bh_io_seek(io, -5, BH_IO_SEEK_CUR) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "67890", 5) == 0);
    bh_io_free(io);

    /* Check operations for read and write access */
    BH_VERIFY((io = bh_file_new(FILENAME1)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_WRITE | BH_IO_READ | BH_IO_EXIST) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);

    BH_VERIFY(bh_io_write(io, "abcde", 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(bh_io_write(io, "1234567890abcde67890", 20, &actual) == BH_OK);
    BH_VERIFY(actual == 20);

    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "abcde", 5) == 0);

    BH_VERIFY(bh_io_read(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);
    BH_VERIFY(memcmp(buffer, "1234567890", 10) == 0);

    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, 35, &actual) == BH_OK);
    BH_VERIFY(actual == 35);
    BH_VERIFY(memcmp(buffer, "abcde12345678901234567890abcde67890", 35) == 0);
    bh_io_close(io);
    bh_io_free(io);

    /* Check against non existing files */
    BH_VERIFY((io = bh_file_new(FILENAME2)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_WRITE | BH_IO_EXIST) != BH_OK);
    BH_VERIFY((bh_io_flags(io) & BH_IO_FLAG_OPEN) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_READ | BH_IO_EXIST) != BH_OK);
    BH_VERIFY((bh_io_flags(io) & BH_IO_FLAG_OPEN) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_WRITE | BH_IO_READ | BH_IO_EXIST) != BH_OK);
    BH_VERIFY((bh_io_flags(io) & BH_IO_FLAG_OPEN) == 0);
    bh_io_free(io);
    return 0;
}


/**
 * Check in append mode.
 */
static int check_append(void)
{
    int64_t position;
    char buffer[128];
    size_t actual;
    bh_io_t *io;

    /* Explicitly call cleanup */
    cleanup();

    /* Check operations for write only access */
    BH_VERIFY((io = bh_file_new(FILENAME1)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_WRITE | BH_IO_APPEND) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(bh_io_seek(io, 10, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_write(io, "abcde", 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);

    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, 1, &actual) != BH_OK);
    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_END) == BH_OK);
    BH_VERIFY(bh_io_tell(io, &position) == BH_OK);
    BH_VERIFY(position == 25);
    bh_io_close(io);

    /* Check operations for read only access */
    BH_VERIFY(bh_io_open(io, BH_IO_READ | BH_IO_APPEND) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_read(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);
    BH_VERIFY(memcmp(buffer, "1234567890", 10) == 0);

    BH_VERIFY(bh_io_read(io, buffer, 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);
    BH_VERIFY(memcmp(buffer, "1234567890", 10) == 0);

    BH_VERIFY(bh_io_read(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "abcde", 5) == 0);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) != BH_OK);
    BH_VERIFY(bh_io_seek(io, -5, BH_IO_SEEK_CUR) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);
    BH_VERIFY(memcmp(buffer, "abcde", 5) == 0);
    bh_io_close(io);

    /* Check operations for read and write access */
    BH_VERIFY(bh_io_open(io, BH_IO_WRITE | BH_IO_READ | BH_IO_APPEND) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);

    BH_VERIFY(bh_io_write(io, "abcde", 5, &actual) == BH_OK);
    BH_VERIFY(actual == 5);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_read(io, buffer, 40, &actual) == BH_OK);
    BH_VERIFY(actual == 40);
    BH_VERIFY(memcmp(buffer, "12345678901234567890abcdeabcde1234567890", 40) == 0);
    bh_io_close(io);

    BH_VERIFY(bh_io_open(io, BH_IO_WRITE | BH_IO_TRUNCATE) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);
    bh_io_close(io);

    bh_io_free(io);
    return 0;
}


/**
 * Check for create mode.
 */
static int check_create(void)
{
    bh_io_t *io;

    /* Check for already existing file */
    BH_VERIFY((io = bh_file_new(FILENAME1)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_WRITE | BH_IO_CREATE) != BH_OK);
    BH_VERIFY((bh_io_flags(io) & BH_IO_FLAG_OPEN) == 0);
    bh_io_free(io);

    /* Check for new file with write access */
    BH_VERIFY((io = bh_file_new(FILENAME2)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_WRITE | BH_IO_CREATE) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);
    bh_io_free(io);

    /* Check for new file with read access */
    BH_VERIFY((io = bh_file_new(FILENAME3)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_READ | BH_IO_CREATE) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);
    bh_io_free(io);

    /* Check for new file with read/write access */
    BH_VERIFY((io = bh_file_new(FILENAME4)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_WRITE | BH_IO_READ | BH_IO_CREATE) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);
    bh_io_free(io);

    return 0;
}


/**
 * Check for EOF flags.
 */
static int check_eof(void)
{
    char buffer[128];
    size_t actual;
    bh_io_t *io;

    BH_VERIFY((io = bh_file_new(FILENAME1)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_READ | BH_IO_TRUNCATE) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);

    BH_VERIFY(bh_io_read(io, buffer, 128, &actual) == BH_OK);
    BH_VERIFY(actual == 0);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_EOF);

    bh_io_close(io);
    bh_io_free(io);

    return 0;
}


/**
 * Check for error flags.
 */
static int check_error(void)
{
    size_t actual;
    bh_io_t *io;

    BH_VERIFY((io = bh_file_new(FILENAME1)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_READ) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);

    BH_VERIFY(bh_io_write(io, "12345", 5, &actual) != BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_ERROR);
    BH_VERIFY(bh_io_clear(io) == BH_OK);
    BH_VERIFY((bh_io_flags(io) & BH_IO_FLAG_ERROR) == 0);

    bh_io_close(io);
    bh_io_free(io);

    return 0;
}


/**
 * Check peek operation.
 */
static int check_peek(void)
{
    int64_t previous, current;
    char buffer[128];
    size_t actual;
    bh_io_t *io;

    BH_VERIFY((io = bh_file_new(FILENAME1)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_WRITE | BH_IO_READ | BH_IO_TRUNCATE) == BH_OK);
    BH_VERIFY(bh_io_flags(io) & BH_IO_FLAG_OPEN);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(bh_io_write(io, "1234567890", 10, &actual) == BH_OK);
    BH_VERIFY(actual == 10);

    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_tell(io, &previous) == BH_OK);
    BH_VERIFY(bh_io_peek(io, buffer, 128, &actual) == BH_OK);
    BH_VERIFY(bh_io_tell(io, &current) == BH_OK);
    BH_VERIFY(actual == 20);
    BH_VERIFY(memcmp(buffer, "12345678901234567890", 20) == 0);
    BH_VERIFY(previous == current);

    BH_VERIFY(bh_io_seek(io, 0, BH_IO_SEEK_SET) == BH_OK);
    BH_VERIFY(bh_io_tell(io, &previous) == BH_OK);
    BH_VERIFY(bh_io_peek(io, buffer, 128, &actual) == BH_OK);
    BH_VERIFY(bh_io_tell(io, &current) == BH_OK);
    BH_VERIFY(actual == 20);
    BH_VERIFY(memcmp(buffer, "12345678901234567890", 20) == 0);
    BH_VERIFY(previous == current);

    bh_io_close(io);
    bh_io_free(io);

    return 0;
}


/**
 * Check file size operation.
 */
static int check_size(void)
{
    bh_io_t *io;
    int64_t size;

    BH_VERIFY((io = bh_file_new(FILENAME1)) != NULL);
    BH_VERIFY(strcmp(bh_io_classname(io), BH_FILE_CLASSNAME) == 0);
    BH_VERIFY(bh_io_open(io, BH_IO_READ) == BH_OK);

    BH_VERIFY(bh_io_size(io, &size) == BH_OK);
    BH_VERIFY(size == 20);

    bh_io_close(io);
    bh_io_free(io);
    return 0;
}


int main(int argc,
         char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    /* Cleanup */
    cleanup();

    bh_unit_add("null", check_null);
    bh_unit_add("normal", check_normal);
    bh_unit_add("truncate", check_truncate);
    bh_unit_add("exist", check_exist);
    bh_unit_add("append", check_append);
    bh_unit_add("create", check_create);
    bh_unit_add("eof", check_eof);
    bh_unit_add("error", check_error);
    bh_unit_add("peek", check_peek);
    bh_unit_add("size", check_size);

    return bh_unit_run();
}
