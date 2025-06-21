# HowTo: Transcoding UTF-8 to UTF-8

## Prerequisites

We want to implement a simple command-line utility that can transcode a UTF-8
file into UTF-8 file (or in other words replace any incorrect UTF-8 sequences).

To do this we would run the following command:

```sh
./Utf8Test UTF-8-test.txt UTF-8-out.txt
```

## Includes

To implement this utility, we are going to need to include the following headers:

- `BH/IO.h` to work with files (or input/output devices)
- `BH/Unicode.h` to work with UTF-8 sequences

## Working with Files

Working with files in BHLib is based around the IO device (called `BH_IO`).
Firstly, you need to create an IO file device with the `BH_FileNew` function.
While doing so, you can specify in which mode it will work: reading
(`BH_FILE_READ`) or writing (`BH_FILE_WRITE`). Additionally, we can specify
whether the file should exist before opening (`BH_IO_EXIST`), be truncated
before opening (`BH_IO_TRUNCATE`), should it be created (`BH_IO_CREATE`), or
opened in append mode (`BH_IO_APPEND`).

Here is an example for opening an existing file in read-only mode:

```c
BH_IO *io = BH_FileNew("coolfile.dat", BH_FILE_READ | BH_FILE_EXISTS, NULL);
if (!io)
{
    printf("Can't open file 'coolfile.dat'\n", config.file);
    return -1;
}
```


## Working with UTF-8

Reading UTF-8/UTF-16/UTF-32 is based around simple loop:

1. Read bytes from input (IO or memory) to some buffer.
2. Call `BH_UnicodeDecodeUtf*`. If return value is 0 - we don't have enough
   data, so go to step 1. Otherwise remove result bytes from the front of the
   buffer.
3. If readed codepoint equals -1 - we encountered an error, so replace it with
   the code 0xFFFD.

Writing UTF-8/UTF-16/UTF-32 is straight forward:

1. Call `BH_UnicodeEncodeUtf*`. If return value is 0 - we can't encode codepoint
   (either codepoint is surrogate pair or outside valid range).
2. Write data (to IO or memory).

BH_UnicodeDecodeUtf8(inBuffer, inSize, &unit)

```c

while (...)
{
    /* Read one byte and try to decode */
    if (!inSize || !(outSize = BH_UnicodeDecodeUtf8(inBuffer, inSize, &unit)))
    {
        BH_IORead(inFile, inBuffer + inSize, 1, &outSize);
        inSize += outSize;
        continue;
    }

    /* Remove readed amount */
    for (i = 0; i < inSize - outSize; i++)
        inBuffer[i] = inBuffer[i + outSize];
    inSize -= outSize;

    /* Change unit if incorrect and write to output */
    if (unit == -1)
        unit = 0xFFFD;
    outSize = BH_UnicodeEncodeUtf8(unit, outBuffer);
    BH_IOWrite(outFile, outBuffer, outSize, NULL);
}
```

## Putting Everything Together

```c
#include <BH/IO.h>
#include <BH/Unicode.h>
#include <stdlib.h>
#include <stdio.h>


void printUsage(void)
{
    printf("Utf8Test <input> <output>\n");
    exit(1);
}


int main(int argc, char **argv)
{
    BH_IO *inFile, *outFile;
    char inBuffer[8], outBuffer[8];
    uint32_t unit;
    size_t i, inSize, outSize;

    if (argc < 2)
        printUsage();

    inFile = BH_FileNew(argv[1], BH_FILE_READ | BH_FILE_EXIST, NULL);
    outFile = BH_FileNew(argv[2], BH_FILE_WRITE | BH_FILE_TRUNCATE, NULL);

    if (!inFile || !outFile)
        return -1;

    inSize = 0;
    while (1)
    {
        /* Read one byte and try to decode */
        if (!inSize || !(outSize = BH_UnicodeDecodeUtf8(inBuffer, inSize, &unit)))
        {
            BH_IOPeek(inFile, inBuffer + inSize, 1, &outSize);
            BH_IORead(inFile, inBuffer + inSize, 1, &outSize);
            inSize += outSize;

            if (!outSize)
                break;

            continue;
        }

        /* Remove readed amount */
        for (i = 0; i < inSize - outSize; i++)
            inBuffer[i] = inBuffer[i + outSize];
        inSize -= outSize;

        /* Change unit if incorrect and write to output */
        if (unit == -1)
            unit = 0xFFFD;
        outSize = BH_UnicodeEncodeUtf8(unit, outBuffer);
        BH_IOWrite(outFile, outBuffer, outSize, NULL);
    }

    /* Incomplete UTF-8 sequence */
    if (inSize)
    {
        outSize = BH_UnicodeEncodeUtf8(0xFFFD, outBuffer);
        BH_IOWrite(outFile, outBuffer, outSize, NULL);
    }

    BH_IOFree(inFile);
    BH_IOFree(outFile);
    return 0;
}
```
