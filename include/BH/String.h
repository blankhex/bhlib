#ifndef BH_STRING_H
#define BH_STRING_H


#include "Common.h"


/**
 * Formats a double \a value into a zero terminated \a string (limited by
 * \a size) using the provided \a format and \a precision and stores \a actual
 * length (if it's provided).
 *
 * Formats supported:
 * - Scientific or fixed format ('g' or 'G')
 * - Scientific format ('e' or 'E')
 * - Fixed format ('f' or 'F')
 *
 * If precision is negative, string will contain shortest representation of the
 * double that can round-trip (i.e. converted back without information loss).
 *
 * This function follows IEEE 754 round to even to break ties during rounding.
 *
 * \param string     String
 * \param size       String size
 * \param value      Value
 * \param format     Format
 * \param precision  Precision
 * \param actual     Written size (optional)
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_StringFromDouble(char *string,
                        size_t size,
                        double value,
                        char format,
                        int precision,
                        size_t *actual);


/**
 * Formats signed 8-bit \a value into a \a string (limited by \a size) with
 * provided \a base and stores \a actual length (if it's provided).
 *
 * \param string  String
 * \param size    String size
 * \param value   Value
 * \param base    Base
 * \param actual  Written size (optional)
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_StringFromInt8s(char *string,
                       size_t size,
                       int8_t value,
                       int base,
                       size_t *actual);


/**
 * Formats signed 16-bit \a value into a \a string (limited by \a size) with
 * provided \a base and stores \a actual length (if it's provided).
 *
 * \param string  String
 * \param size    String size
 * \param value   Value
 * \param base    Base
 * \param actual  Written size (optional)
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_StringFromInt16s(char *string,
                        size_t size,
                        int16_t value,
                        int base,
                        size_t *actual);


/**
 * Formats signed 32-bit \a value into a \a string (limited by \a size) with
 * provided \a base and stores \a actual length (if it's provided).
 *
 * \param string  String
 * \param size    String size
 * \param value   Value
 * \param base    Base
 * \param actual  Written size (optional)
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_StringFromInt32s(char *string,
                        size_t size,
                        int32_t value,
                        int base,
                        size_t *actual);


/**
 * Formats signed 64-bit \a value into a \a string (limited by \a size) with
 * provided \a base and stores \a actual length (if it's provided).
 *
 * \param string  String
 * \param size    String size
 * \param value   Value
 * \param base    Base
 * \param actual  Written size (optional)
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_StringFromInt64s(char *string,
                        size_t size,
                        int64_t value,
                        int base,
                        size_t *actual);


/**
 * Formats unsigned 8-bit \a value into a \a string (limited by \a size) with
 * provides \a base and stores \a actual length (if it's provided).
 *
 * \param string  String
 * \param size    String size
 * \param value   Value
 * \param base    Base
 * \param actual  Written size (optional)
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_StringFromInt8u(char *string,
                       size_t size,
                       uint8_t value,
                       int base,
                       size_t *actual);


/**
 * Formats unsigned 16-bit \a value into a \a string (limited by \a size) with
 * provides \a base and stores \a actual length (if it's provided).
 *
 * \param string  String
 * \param size    String size
 * \param value   Value
 * \param base    Base
 * \param actual  Written size (optional)
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_StringFromInt16u(char *string,
                        size_t size,
                        uint16_t value,
                        int base,
                        size_t *actual);


/**
 * Formats unsigned 32-bit \a value into a \a string (limited by \a size) with
 * provided \a base and stores \a actual length (if it's provided).
 *
 * \param string  String
 * \param size    String size
 * \param value   Value
 * \param base    Base
 * \param actual  Written size (optional)
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_StringFromInt32u(char *string,
                        size_t size,
                        uint32_t value,
                        int base,
                        size_t *actual);


/**
 * Formats unsigned 64-bit \a value into a \a string (limited by \a size) with
 * provided \a base and stores \a actual length (if it's provided).
 *
 * \param string  String
 * \param size    String size
 * \param value   Value
 * \param base    Base
 * \param actual  Written size (optional)
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_StringFromInt64u(char *string,
                        size_t size,
                        uint64_t value,
                        int base,
                        size_t *actual);


/**
 * Reads \a string containing double value in fixed or scientific format,
 * optionally reports \a size amount of characters consumed and returns
 * the result value.
 *
 * \param string  String
 * \param size    Optional size
 *
 * \return On success, returns parsed double value.
 * \return On failure, returns zero.
 */
double BH_StringToDouble(const char *string,
                         size_t *size);


/**
 * Reads \a string containing value in specified \a base, optionally reports
 * \a size amount of characters consumed and returns the result value.
 *
 * If base is 0, function will automaticly detect input base by the prefix:
 * - Base 2 if prefix is 0b
 * - Base 8 if prefix is 0
 * - Base 16 if prefix is 0x
 * - Base 10 in other cases
 *
 * \param string  String
 * \param size    Optional size
 * \param base    Base
 *
 * \return On success, returns parsed value.
 * \return On failure, returns zero.
 */
int8_t BH_StringToInt8s(const char *string,
                        size_t *size,
                        int base);


/**
 * Reads \a string containing value in specified \a base, optionally reports
 * \a size amount of characters consumed and returns the result value.
 *
 * If base is 0, function will automaticly detect input base by the prefix:
 * - Base 2 if prefix is 0b
 * - Base 8 if prefix is 0
 * - Base 16 if prefix is 0x
 * - Base 10 in other cases
 *
 * \param string  String
 * \param size    Optional size
 * \param base    Base
 *
 * \return On success, returns parsed value.
 * \return On failure, returns zero.
 */
int16_t BH_StringToInt16s(const char *string,
                          size_t *size,
                          int base);


/**
 * Reads \a string containing value in specified \a base, optionally reports
 * \a size amount of characters consumed and returns the result value.
 *
 * If base is 0, function will automaticly detect input base by the prefix:
 * - Base 2 if prefix is 0b
 * - Base 8 if prefix is 0
 * - Base 16 if prefix is 0x
 * - Base 10 in other cases
 *
 * \param string  String
 * \param size    Optional size
 * \param base    Base
 *
 * \return On success, returns parsed value.
 * \return On failure, returns zero.
 */
int32_t BH_StringToInt32s(const char *string,
                          size_t *size,
                          int base);


/**
 * Reads \a string containing value in specified \a base, optionally reports
 * \a size amount of characters consumed and returns the result value.
 *
 * If base is 0, function will automaticly detect input base by the prefix:
 * - Base 2 if prefix is 0b
 * - Base 8 if prefix is 0
 * - Base 16 if prefix is 0x
 * - Base 10 in other cases
 *
 * \param string  String
 * \param size    Optional size
 * \param base    Base
 *
 * \return On success, returns parsed value.
 * \return On failure, returns zero.
 */
int64_t BH_StringToInt64s(const char *string,
                          size_t *size,
                          int base);


/**
 * Reads \a string containing value in specified \a base, optionally reports
 * \a size amount of characters consumed and returns the result value.
 *
 * If base is 0, function will automaticly detect input base by the prefix:
 * - Base 2 if prefix is 0b
 * - Base 8 if prefix is 0
 * - Base 16 if prefix is 0x
 * - Base 10 in other cases
 *
 * \param string  String
 * \param size    Optional size
 * \param base    Base
 *
 * \return On success, returns parsed value.
 * \return On failure, returns zero.
 */
uint8_t BH_StringToInt8u(const char *string,
                         size_t *size,
                         int base);


/**
 * Reads \a string containing value in specified \a base, optionally reports
 * \a size amount of characters consumed and returns the result value.
 *
 * If base is 0, function will automaticly detect input base by the prefix:
 * - Base 2 if prefix is 0b
 * - Base 8 if prefix is 0
 * - Base 16 if prefix is 0x
 * - Base 10 in other cases
 *
 * \param string  String
 * \param size    Optional size
 * \param base    Base
 *
 * \return On success, returns parsed value.
 * \return On failure, returns zero.
 */
uint16_t BH_StringToInt16u(const char *string,
                           size_t *size,
                           int base);


/**
 * Reads \a string containing value in specified \a base, optionally reports
 * \a size amount of characters consumed and returns the result value.
 *
 * If base is 0, function will automaticly detect input base by the prefix:
 * - Base 2 if prefix is 0b
 * - Base 8 if prefix is 0
 * - Base 16 if prefix is 0x
 * - Base 10 in other cases
 *
 * \param string  String
 * \param size    Optional size
 * \param base    Base
 *
 * \return On success, returns parsed value.
 * \return On failure, returns zero.
 */
uint32_t BH_StringToInt32u(const char *string,
                           size_t *size,
                           int base);


/**
 * Reads \a string containing value in specified \a base, optionally reports
 * \a size amount of characters consumed and returns the result value.
 *
 * If base is 0, function will automaticly detect input base by the prefix:
 * - Base 2 if prefix is 0b
 * - Base 8 if prefix is 0
 * - Base 16 if prefix is 0x
 * - Base 10 in other cases
 *
 * \param string  String
 * \param size    Optional size
 * \param base    Base
 *
 * \return On success, returns parsed value.
 * \return On failure, returns zero.
 */
uint64_t BH_StringToInt64u(const char *string,
                           size_t *size,
                           int base);


/**
 * Converts unicode \a unit codepoint to lowercase.
 *
 * \param unit  Codepoint
 *
 * \return On success, returns lowercased codepoint.
 * \return On failure, returns codepoint without a change.
 */
uint32_t BH_UnicodeLower(uint32_t unit);


/**
 * Converts unicode \a unit codepoint to uppercase.
 *
 * \param unit  Codepoint
 *
 * \return On success, returns uppercased codepoint.
 * \return On failure, returns codepoint without a change.
 */
uint32_t BH_UnicodeUpper(uint32_t unit);


/**
 * Decodes a UTF-8 sequence from a \a string (with the given \a size), storing
 * the result in a \a unit and returning the number of bytes read.
 *
 * Invalid UTF-8 sequences result in a -1 codepoint.
 *
 * \param string  String
 * \param size    Size
 * \param unit    Codepoint
 *
 * \return Returns readed amount of bytes
 * \return Returns zero if the string contains only a portion of the sequence.
 */
size_t BH_UnicodeDecodeUtf8(const char *string,
                            size_t size,
                            uint32_t *unit);


/**
 * Encodes a Unicode \a unit to UTF-8 encoded bytes (stored in a \a string)
 * and returns the number of bytes written.
 *
 * String are assumed to have 4 bytes of space.
 *
 * \param unit    Codepoint
 * \param string  String
 *
 * \return On success, returns written amount of bytes.
 * \return Of faulure, returns zero.
 */
size_t BH_UnicodeEncodeUtf8(uint32_t unit,
                            char *string);


/**
 * Decodes a UTF-16LE sequence from a \a string (with the given \a size),
 * storing the result in a \a unit and returning the number of bytes read.
 *
 * Invalid UTF-16 sequences result in a -1 codepoint.
 *
 * \param string  String
 * \param size    Size
 * \param unit    Codepoint
 *
 * \return Returns readed amount of bytes
 * \return Returns zero if the string contains only a portion of the sequence.
 */
size_t BH_UnicodeDecodeUtf16LE(const char *string,
                               size_t size,
                               uint32_t *unit);


/**
 * Decodes a UTF-16BE sequence from a \a string (with the given \a size),
 * storing the result in a \a unit and returning the number of bytes read.
 *
 * Invalid UTF-16 sequences result in a -1 codepoint.
 *
 * \param string  String
 * \param size    Size
 * \param unit    Codepoint
 *
 * \return Returns readed amount of bytes
 * \return Returns zero if the string contains only a portion of the sequence.
 */
size_t BH_UnicodeDecodeUtf16BE(const char *string,
                               size_t size,
                               uint32_t *unit);


/**
 * Encodes a Unicode \a unit to UTF-16LE encoded bytes (stored in a \a string)
 * and returns the number of bytes written.
 *
 * String are assumed to have 4 bytes of space.
 *
 * \param unit    Codepoint
 * \param string  String
 *
 * \return On success, returns written amount of bytes.
 * \return Of faulure, returns zero.
 */
size_t BH_UnicodeEncodeUtf16LE(uint32_t unit,
                               char *string);


/**
 * Encodes a Unicode \a unit to UTF-16BE encoded bytes (stored in a \a string)
 * and returns the number of bytes written.
 *
 * String are assumed to have 4 bytes of space.
 *
 * \param unit    Codepoint
 * \param string  String
 *
 * \return On success, returns written amount of bytes.
 * \return Of faulure, returns zero.
 */
size_t BH_UnicodeEncodeUtf16BE(uint32_t unit,
                               char *string);


/**
 * Decodes a UTF-32LE symbol from a \a string (with the given \a size),
 * storing the result in a \a unit and returning the number of bytes read.
 *
 * Invalid UTF-32 result in a -1 codepoint.
 *
 * \param string  String
 * \param size    Size
 * \param unit    Codepoint
 *
 * \return Returns readed amount of bytes
 * \return Returns zero if the string contains only a portion of the sequence.
 */
size_t BH_UnicodeDecodeUtf32LE(const char *string,
                               size_t size,
                               uint32_t *unit);


/**
 * Decodes a UTF-32BE symbol from a \a string (with the given \a size),
 * storing the result in a \a unit and returning the number of bytes read.
 *
 * Invalid UTF-32 result in a -1 codepoint.
 *
 * \param string  String
 * \param size    Size
 * \param unit    Codepoint
 *
 * \return Returns readed amount of bytes
 * \return Returns zero if the string contains only a portion of the sequence.
 */
size_t BH_UnicodeDecodeUtf32BE(const char *string,
                               size_t size,
                               uint32_t *unit);


/**
 * Encodes a Unicode \a unit to UTF-32LE encoded bytes (stored in a \a string)
 * and returns the number of bytes written.
 *
 * String are assumed to have 4 bytes of space.
 *
 * \param unit    Codepoint
 * \param string  String
 *
 * \return On success, returns written amount of bytes.
 * \return Of faulure, returns zero.
 */
size_t BH_UnicodeEncodeUtf32LE(uint32_t unit,
                               char *string);

/**
 * Encodes a Unicode \a unit to UTF-32LE encoded bytes (stored in a \a string)
 * and returns the number of bytes written.
 *
 * String are assumed to have 4 bytes of space.
 *
 * \param unit    Codepoint
 * \param string  String
 *
 * \return On success, returns written amount of bytes.
 * \return Of faulure, returns zero.
 */
size_t BH_UnicodeEncodeUtf32BE(uint32_t unit,
                               char *string);

#endif /* BH_STRING_H */
