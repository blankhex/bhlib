#include <BH/IO.h>
#include <BH/String.h>
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

    inFile = BH_FileNew(argv[1]);
    outFile = BH_FileNew(argv[2]);

    if (!inFile || BH_IOOpen(inFile, BH_IO_READ | BH_IO_EXIST))
        return -1;

    if (!outFile || BH_IOOpen(outFile, BH_IO_WRITE | BH_IO_TRUNCATE))
        return -1;

    inSize = 0;
    while (!(BH_IOFlags(inFile) & BH_IO_FLAG_EOF))
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
