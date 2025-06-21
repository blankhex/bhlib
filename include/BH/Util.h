#ifndef BH_UTIL_H
#define BH_UTIL_H


#include "Common.h"


#define BH_FP_NORMAL    0x0000
#define BH_FP_INFINITE  0x0001
#define BH_FP_NAN       0x0002
#define BH_FP_ZERO      0x0010
#define BH_FP_NEGATIVE  0x0020



int BH_ClassifyDouble(double value);



uint16_t BH_Read16LEu(const char *buffer);



int16_t BH_Read16LEs(const char *buffer);



uint32_t BH_Read32LEu(const char *buffer);



int32_t BH_Read32LEs(const char *buffer);



uint64_t BH_Read64LEu(const char *buffer);



int64_t BH_Read64LEs(const char *buffer);



uint16_t BH_Read16BEu(const char *buffer);



int16_t BH_Read16BEs(const char *buffer);



uint32_t BH_Read32BEu(const char *buffer);



int32_t BH_Read32BEs(const char *buffer);



uint64_t BH_Read64BEu(const char *buffer);



int64_t BH_Read64BEs(const char *buffer);



void BH_Write16LEu(char *buffer,
                   uint16_t value);



void BH_Write16LEs(char *buffer,
                   int16_t value);



void BH_Write32LEu(char *buffer,
                   uint32_t value);



void BH_Write32LEs(char *buffer,
                   int32_t value);



void BH_Write64LEu(char *buffer,
                   uint64_t value);



void BH_Write64LEs(char *buffer,
                   int64_t value);



void BH_Write16BEu(char *buffer,
                   uint16_t value);



void BH_Write16BEs(char *buffer,
                   int16_t value);



void BH_Write32BEu(char *buffer,
                   uint32_t value);



void BH_Write32BEs(char *buffer,
                   int32_t value);



void BH_Write64BEu(char *buffer,
                   uint64_t value);



void BH_Write64BEs(char *buffer,
                   int64_t value);


#endif /* BH_UTIL_H */