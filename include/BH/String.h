#ifndef BH_STRING_H
#define BH_STRING_H


#include "Common.h"


void BH_StringFree(char *string);


char *BH_StringCopy(const char *string);


char *BH_StringFromDouble(double value,
                          char format,
                          int precision);


double BH_StringToDouble(const char *string,
                         size_t *size);


char *BH_StringFromInt8s(int8_t value,
                         int base);


char *BH_StringFromInt32s(int32_t value,
                          int base);

char *BH_StringFromInt64s(int64_t value,
                          int base);

char *BH_StringFromInt16s(int16_t value,
                          int base);

char *BH_StringFromInt8u(uint8_t value,
                         int base);


char *BH_StringFromInt16u(uint16_t value,
                          int base);


char *BH_StringFromInt32u(uint32_t value,
                          int base);


char *BH_StringFromInt64u(uint64_t value,
                          int base);


int8_t BH_StringToInt8s(const char *string,
                        size_t *size,
                        int base);


int16_t BH_StringToInt16s(const char *string,
                          size_t *size,
                          int base);


int32_t BH_StringToInt32s(const char *string,
                          size_t *size,
                          int base);


int64_t BH_StringToInt64s(const char *string,
                          size_t *size,
                          int base);


uint8_t BH_StringToInt8u(const char *string,
                         size_t *size,
                         int base);


uint16_t BH_StringToInt16u(const char *string,
                           size_t *size,
                           int base);


uint32_t BH_StringToInt32u(const char *string,
                           size_t *size,
                           int base);


uint64_t BH_StringToInt64u(const char *string,
                           size_t *size,
                           int base);


#endif /* BH_STRING_H */
