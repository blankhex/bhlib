#ifndef BH_UTIL_H
#define BH_UTIL_H


#include "Common.h"


/**
 * Reads 16-bit unsigned integer from the \a buffer in little-endian format.
 *
 * \param buffer  Buffer pointer
 *
 * \return Returns 16-bit unsigned integer value.
 */
uint16_t BH_Read16LEu(const char *buffer);


/**
 * Reads 16-bit signed integer from the \a buffer in little-endian format.
 *
 * \param buffer  Buffer pointer
 *
 * \return Returns 16-bit signed integer value.
 */
int16_t BH_Read16LEs(const char *buffer);


/**
 * Reads 32-bit unsigned integer from the \a buffer in little-endian format.
 *
 * \param buffer  Buffer pointer
 *
 * \return Returns 32-bit unsigned integer value.
 */
uint32_t BH_Read32LEu(const char *buffer);


/**
 * Reads 32-bit signed integer from the \a buffer in little-endian format.
 *
 * \param buffer  Buffer pointer
 *
 * \return Returns 32-bit signed integer value.
 */
int32_t BH_Read32LEs(const char *buffer);


/**
 * Reads 64-bit unsigned integer from the \a buffer in little-endian format.
 *
 * \param buffer  Buffer pointer
 *
 * \return Returns 64-bit unsigned integer value.
 */
uint64_t BH_Read64LEu(const char *buffer);


/**
 * Reads 64-bit signed integer from the \a buffer in little-endian format.
 *
 * \param buffer  Buffer pointer
 *
 * \return Returns 64-bit signed integer value.
 */
int64_t BH_Read64LEs(const char *buffer);


/**
 * Reads 16-bit unsigned integer from the \a buffer in big-endian format.
 *
 * \param buffer  Buffer pointer
 *
 * \return Returns 16-bit unsigned integer value.
 */
uint16_t BH_Read16BEu(const char *buffer);


/**
 * Reads 16-bit signed integer from the \a buffer in big-endian format.
 *
 * \param buffer  Buffer pointer
 *
 * \return Returns 16-bit signed integer value.
 */
int16_t BH_Read16BEs(const char *buffer);


/**
 * Reads 32-bit unsigned integer from the \a buffer in big-endian format.
 *
 * \param buffer  Buffer pointer
 *
 * \return Returns 32-bit unsigned integer value.
 */
uint32_t BH_Read32BEu(const char *buffer);


/**
 * Reads 32-bit signed integer from the \a buffer in big-endian format.
 *
 * \param buffer  Buffer pointer
 *
 * \return Returns 32-bit signed integer value.
 */
int32_t BH_Read32BEs(const char *buffer);



/**
 * Reads 64-bit unsigned integer from the \a buffer in big-endian format.
 *
 * \param buffer  Buffer pointer
 *
 * \return Returns 64-bit unsigned integer value.
 */
uint64_t BH_Read64BEu(const char *buffer);


/**
 * Reads 64-bit signed integer from the \a buffer in big-endian format.
 *
 * \param buffer  Buffer pointer
 *
 * \return Returns 64-bit signed integer value.
 */
int64_t BH_Read64BEs(const char *buffer);


/**
 * Writes 16-bit unsigned integer to the \a buffer in little-endian format.
 *
 * \param buffer  Buffer pointer
 * \param value   Value
 */
void BH_Write16LEu(char *buffer,
                   uint16_t value);



/**
 * Writes 16-bit signed integer to the \a buffer in little-endian format.
 *
 * \param buffer  Buffer pointer
 * \param value   Value
 */
void BH_Write16LEs(char *buffer,
                   int16_t value);


/**
 * Writes 32-bit unsigned integer to the \a buffer in little-endian format.
 *
 * \param buffer  Buffer pointer\param buffer  Buffer pointer
 * \param value   Value
 */
void BH_Write32LEu(char *buffer,
                   uint32_t value);


/**
 * Writes 32-bit signed integer to the \a buffer in little-endian format.
 *
 * \param buffer  Buffer pointer
 * \param value   Value
 */
void BH_Write32LEs(char *buffer,
                   int32_t value);


/**
 * Writes 64-bit unsigned integer to the \a buffer in little-endian format.
 *
 * \param buffer  Buffer pointer
 * \param value   Value
 */
void BH_Write64LEu(char *buffer,
                   uint64_t value);



/**
 * Writes 64-bit signed integer to the \a buffer in little-endian format.
 *
 * \param buffer  Buffer pointer
 * \param value   Value
 */
void BH_Write64LEs(char *buffer,
                   int64_t value);


/**
 * Writes 16-bit unsigned integer to the \a buffer in big-endian format.
 *
 * \param buffer  Buffer pointer
 * \param value   Value
 */
void BH_Write16BEu(char *buffer,
                   uint16_t value);


/**
 * Writes 16-bit signed integer to the \a buffer in big-endian format.
 *
 * \param buffer  Buffer pointer
 * \param value   Value
 */
void BH_Write16BEs(char *buffer,
                   int16_t value);



/**
 * Writes 32-bit unsigned integer to the \a buffer in big-endian format.
 *
 * \param buffer  Buffer pointer
 * \param value   Value
 */
void BH_Write32BEu(char *buffer,
                   uint32_t value);


/**
 * Writes 32-bit signed integer to the \a buffer in big-endian format.
 *
 * \param buffer  Buffer pointer
 * \param value   Value
 */
void BH_Write32BEs(char *buffer,
                   int32_t value);


/**
 * Writes 64-bit unsigned integer to the \a buffer in big-endian format.
 *
 * \param buffer  Buffer pointer
 * \param value   Value
 */
void BH_Write64BEu(char *buffer,
                   uint64_t value);


/**
 * Writes 64-bit signed integer to the \a buffer in big-endian format.
 *
 * \param buffer  Buffer pointer
 * \param value   Value
 */
void BH_Write64BEs(char *buffer,
                   int64_t value);


#endif /* BH_UTIL_H */
