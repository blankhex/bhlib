#ifndef BH_UNICODE_H
#define BH_UNICODE_H


#include "Common.h"


uint32_t BH_UnicodeLower(uint32_t unit);


uint32_t BH_UnicodeUpper(uint32_t unit);


size_t BH_UnicodeDecodeUtf8(const char *string,
                            size_t size,
                            uint32_t *unit);


size_t BH_UnicodeEncodeUtf8(uint32_t unit,
                            char *string);


size_t BH_UnicodeDecodeUtf16LE(const char *string,
                               size_t size,
                               uint32_t *unit);


size_t BH_UnicodeDecodeUtf16BE(const char *string,
                               size_t size,
                               uint32_t *unit);


size_t BH_UnicodeEncodeUtf16LE(uint32_t unit,
                               char *string);


size_t BH_UnicodeEncodeUtf16BE(uint32_t unit,
                               char *string);


size_t BH_UnicodeDecodeUtf32LE(const char *string,
                               size_t size,
                               uint32_t *unit);


size_t BH_UnicodeDecodeUtf32BE(const char *string,
                               size_t size,
                               uint32_t *unit);


size_t BH_UnicodeEncodeUtf32LE(uint32_t unit,
                               char *string);


size_t BH_UnicodeEncodeUtf32BE(uint32_t unit,
                               char *string);


#endif /* BH_UNICODE_H */
