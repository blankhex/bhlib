#ifndef BH_STRING_STRING_H
#define BH_STRING_STRING_H


#include <BH/String.h>


#define BH_INT1120_DIGITS 70


typedef struct BH_Int1120
{
    int size;
    uint16_t digits[BH_INT1120_DIGITS];
} BH_Int1120;


/**
 * Counts the number of leading zero bits.
 *
 * \param value  Value
 *
 * \return Count of leading zeros.
 */
int BH_Int1120Clz(const uint16_t value);


/**
 * Compares big integers \a a and \a b.
 *
 * \param a  A integer
 * \param b  B integer
 *
 * \return Negative if \a a is less than \a b
 * \return Positive if \a a is greater than \a b
 * \return Zero if \a a and \a b are equal.
 */
int BH_Int1120Compare(const BH_Int1120 *a,
                      const BH_Int1120 *b);


/**
 * Adds two big integers \a a and \a b and stores result into \a out.
 *
 * \param a    A integer
 * \param b    B integer
 * \param out  Result integer
 */
void BH_Int1120Add(const BH_Int1120 *a,
                   const BH_Int1120 *b,
                   BH_Int1120 *out);


/**
 * Subtracts two big integers \a a and \a b and stores result into \a out.
 *
 * \param a    A integer
 * \param b    B integer
 * \param out  Result integer
 */
void BH_Int1120Sub(const BH_Int1120 *a,
                   const BH_Int1120 *b,
                   BH_Int1120 *out);


/**
 * Multiplies two big integers \a a and \a b and stores result into \a out.
 *
 * \param a    A integer
 * \param b    B integer
 * \param out  Result integer
 */
void BH_Int1120Mul(const BH_Int1120 *a,
                   const BH_Int1120 *b,
                   BH_Int1120 *out);


/**
 * Multiplies big integer \a a by \a digit and stores result into \a out.
 *
 * \param in     Input integer
 * \param digit  Digit
 * \param out    Result integer
 */
void BH_Int1120MulDigit(const BH_Int1120 *in,
                        uint16_t digit,
                        BH_Int1120 *out);


/**
 * Divides two big integers \a a and \a b and stores quotient into \a q and
 * remainder into \a r.
 *
 * \param a  A integer
 * \param b  B integer
 * \param q  Output quotient integer
 * \param r  Output remainder integer
 */
void BH_Int1120Div(const BH_Int1120 *a,
                   const BH_Int1120 *b,
                   BH_Int1120 *q,
                   BH_Int1120 *r);


/**
 * Computes 10 to the power of \a exponent.
 *
 * \param exponent  Exponent
 * \param out       Result integer
 */
void BH_Int1120Pow10(int exponent,
                     BH_Int1120 *out);


/**
 * Multiplies a big integer \a in by 10 to the power of \a exponent.
 *
 * \param in        Input integer
 * \param exponent  Exponent
 * \param out       Result integer
 */
void BH_Int1120MulPow10(const BH_Int1120 *in,
                        int exponent,
                        BH_Int1120 *out);


/**
 * Computes 2 to the power of \a exponent.
 *
 * \param exponent  Exponent
 * \param out       Result integer
 */
void BH_Int1120Pow2(int exponent,
                    BH_Int1120 *out);


/**
 * Left shifts big integer \a in by \a amount places and stores result into
 * \a out.
 *
 * \param in      Input integer
 * \param amount  Shift amount
 * \param out     Result integer
 */
void BH_Int1120Lsh(const BH_Int1120 *in,
                   int amount,
                   BH_Int1120 *out);


/**
 * Right shifts big integer \a in by \a amount places and stores result into
 * \a out.
 *
 * \param in      Input integer
 * \param amount  Shift amount
 * \param out     Result integer
 */
void BH_Int1120Rsh(const BH_Int1120 *in,
                   int amount,
                   BH_Int1120 *out);


#endif /* BH_STRING_STRING_H */
