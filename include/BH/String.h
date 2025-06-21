#ifndef BH_STRING_H
#define BH_STRING_H


#include "Common.h"



int BH_StringFromDouble(char *string,
                        size_t size,
                        double value,
                        char format,
                        int precision,
                        size_t *actual);



int BH_StringFromInt8s(char *string,
                       size_t size,
                       int8_t value,
                       int base,
                       size_t *actual);



int BH_StringFromInt16s(char *string,
                        size_t size,
                        int16_t value,
                        int base,
                        size_t *actual);



int BH_StringFromInt32s(char *string,
                        size_t size,
                        int32_t value,
                        int base,
                        size_t *actual);



int BH_StringFromInt64s(char *string,
                        size_t size,
                        int64_t value,
                        int base,
                        size_t *actual);



int BH_StringFromInt8u(char *string,
                       size_t size,
                       uint8_t value,
                       int base,
                       size_t *actual);



int BH_StringFromInt16u(char *string,
                        size_t size,
                        uint16_t value,
                        int base,
                        size_t *actual);



int BH_StringFromInt32u(char *string,
                        size_t size,
                        uint32_t value,
                        int base,
                        size_t *actual);



int BH_StringFromInt64u(char *string,
                        size_t size,
                        uint64_t value,
                        int base,
                        size_t *actual);



double BH_StringToDouble(const char *string,
                         size_t *size);



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
