#ifndef BH_STRING_H
#define BH_STRING_H


#include "Common.h"


/**
 * Frees dynamically allocated \a string.
 *
 * \param string  String pointer
 */
void BH_StringFree(char *string);


/**
 * Creates a copy of the input \a string.
 *
 * \param string  String pointer
 *
 * \return On success, returns new string pointer.
 * \return On failure, returns NULL pointer.
 */
char *BH_StringCopy(const char *string);


/**
 * Formats a double \a value into a string using the provided \a format and
 * \a precision.
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
 * \param value      Value
 * \param format     Format
 * \param precision  Precision
 *
 * \return On success, returns new string pointer.
 * \return On failure, returns NULL pointer.
 */
char *BH_StringFromDouble(double value,
                          char format,
                          int precision);


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
 * Formats signed 8bit \a value into string with the specified \a base.
 *
 * \param value   Value
 * \param base    Base
 *
 * \return On success, returns new string pointer.
 * \return On failure, returns NULL pointer.
 */
char *BH_StringFromInt8s(int8_t value,
                         int base);


/**
 * Formats signed 16bit \a value into string with the specified \a base.
 *
 * \param value   Value
 * \param base    Base
 *
 * \return On success, returns new string pointer.
 * \return On failure, returns NULL pointer.
 */
char *BH_StringFromInt16s(int16_t value,
                          int base);


/**
 * Formats signed 32bit \a value into string with the specified \a base.
 *
 * \param value   Value
 * \param base    Base
 *
 * \return On success, returns new string pointer.
 * \return On failure, returns NULL pointer.
 */
char *BH_StringFromInt32s(int32_t value,
                          int base);

/**
 * Formats signed 64bit \a value into string with the specified \a base.
 *
 * \param value   Value
 * \param base    Base
 *
 * \return On success, returns new string pointer.
 * \return On failure, returns NULL pointer.
 */
char *BH_StringFromInt64s(int64_t value,
                          int base);


/**
 * Formats unsigned 8bit \a value into string with the specified \a base.
 *
 * \param value   Value
 * \param base    Base
 *
 * \return On success, returns new string pointer.
 * \return On failure, returns NULL pointer.
 */
char *BH_StringFromInt8u(uint8_t value,
                         int base);


/**
 * Formats unsigned 16bit \a value into string with the specified \a base.
 *
 * \param value   Value
 * \param base    Base
 *
 * \return On success, returns new string pointer.
 * \return On failure, returns NULL pointer.
 */
char *BH_StringFromInt16u(uint16_t value,
                          int base);


/**
 * Formats unsigned 32bit \a value into string with the specified \a base.
 *
 * \param value   Value
 * \param base    Base
 *
 * \return On success, returns new string pointer.
 * \return On failure, returns NULL pointer.
 */
char *BH_StringFromInt32u(uint32_t value,
                          int base);


/**
 * Formats unsigned 64bit \a value into string with the specified \a base.
 *
 * \param value   Value
 * \param base    Base
 *
 * \return On success, returns new string pointer.
 * \return On failure, returns NULL pointer.
 */
char *BH_StringFromInt64u(uint64_t value,
                          int base);


/**
 * Reads \a string containing value in specified \a base, optionally reports
 * \a size amount of characters consumed and returns the result value.
 *
 * If base is 0, function will automaticly detect input base by the prefix:
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


#endif /* BH_STRING_H */
