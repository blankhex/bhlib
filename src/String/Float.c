#include <BH/String.h>
#include <BH/Util.h>
#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#include "BInt.h"


/* Common defines */
#define MAX(a,b)    (((a)>(b))?(a):(b))
#define MIN(a,b)    (((a)<(b))?(a):(b))
#define BUFSIZE     309

/* Modes */
#define NORMAL      0
#define ABSOLUTE    1
#define RELATIVE    2


struct DragonState
{
    BInt r;
    BInt s;
    BInt mm;
    BInt mp;
    BInt tmp[5];
    long k;
    int cutoff;
};


static void dragonFixup(struct DragonState *state,
                        int precision,
                        int mode,
                        uint64_t f,
                        int exp)
{
    /* Preconditions */
    assert(state != NULL);
    assert(mode == NORMAL || mode == ABSOLUTE || mode == RELATIVE);
    assert(precision >= 0);

    /* Account for unqual gaps */
    if (f == (((uint64_t)1) << 52))
    {
        BIntLsh(&state->mp, 1, &state->mp);
        BIntLsh(&state->r, 1, &state->r);
        BIntLsh(&state->s, 1, &state->s);
    }
    state->k = 0;

    /* Burger/Dybvig approach */
    #ifndef BH_TWEAK_SHORT_BINT
    state->k = BIntClz((f >> 32) & BINT_MASK);
    state->k += (state->k == 32) ? (BIntClz(f & BINT_MASK)) : (0);
    #else
    state->k = BIntClz((f >> 48) & BINT_MASK);
    state->k += (state->k == 16) ? (BIntClz((f >> 32) & BINT_MASK)) : (0);
    state->k += (state->k == 32) ? (BIntClz((f >> 16) & BINT_MASK)) : (0);
    state->k += (state->k == 48) ? (BIntClz(f & BINT_MASK)) : (0);
    #endif

    /* 77 / 256 is an approximation for Log(2) or 0.30102999 */
    state->k = (63 - state->k + exp - 54) * 77;
    if (state->k < 0)
        state->k = (state->k / 256);
    else
        state->k = (state->k / 256) + ((state->k & 0xFF) > 0);

    /* Scale numbers accordinaly */
    if (state->k < 0)
    {
        BIntPow10(&state->r, -state->k, &state->r, state->tmp);
        BIntPow10(&state->mm, -state->k, &state->mm, state->tmp);
        BIntPow10(&state->mp, -state->k, &state->mp, state->tmp);
    }
    else if (state->k > 0)
        BIntPow10(&state->s, state->k, &state->s, state->tmp);

    /* Scale S if we underestimated */
    if (BIntCompare(&state->r, &state->s) >= 0)
    {
        state->k += 1;
        BIntMulDigit(&state->s, 10, &state->s);
    }

    /* Find cutoff */
    if (mode == NORMAL)
        state->cutoff = state->k - BUFSIZE;
    else if (mode == RELATIVE)
        state->cutoff = state->k - precision;
    else
        state->cutoff = -precision;
}


static void dragonRound(struct DragonState *state,
                        char *buffer,
                        int *k,
                        int *size,
                        int high,
                        int low,
                        char s)
{
    int i;

    /* Preconditions */
    assert(state != NULL && buffer != NULL && k != NULL && size != NULL);
    assert(s >= '0' && s <= '9');

    /* Check if rounding up required */
    if (high == low)
    {
        BIntLsh(&state->r, 1, &state->tmp[0]);
        i = BIntCompare(&state->tmp[0], &state->s);
        if (i < 0) { low = 1; high = 0; }
        else if (i > 0) { low = 0; high = 1; }
        else low = (((s - '0') & 0x1) == 0);
    }

    /* Perform rounding up */
    if (!low)
    {
        for (i = *size; i && buffer[i - 1] == '9'; i--)
            buffer[i - 1] = '0';

        if (i > 0)
            buffer[i - 1]++;
        else
        {
            buffer[0] = '1';
            (*k)++;
        }
    }
}


static void dragon(double value,
                   int precision,
                   int mode,
                   char *buffer,
                   int *size,
                   int *k)
{
    struct DragonState state;
    int low, high, e;
    uint64_t f;
    char s;

    /* Preconditions */
    assert(buffer != NULL && size != NULL && k != NULL);
    assert(mode == NORMAL || mode == ABSOLUTE || mode == RELATIVE);
    assert(precision >= 0);

    *k = 0;
    *size = low = high = 0;

    /* If value is zero - do nothing */
    if (!value)
    {
        buffer[(*size)++] = '0';
        return;
    }

    /* Prepare dragon */
    f = frexp(value, &e) * ((uint64_t)1 << 53);
    #ifndef BH_TWEAK_SHORT_BINT
    state.r.data[0] = f & BINT_MASK;
    state.r.data[1] = (f >> 32) & BINT_MASK;
    state.r.size = 2;
    #else
    state.r.data[0] = f & BINT_MASK;
    state.r.data[1] = (f >> 16) & BINT_MASK;
    state.r.data[2] = (f >> 32) & BINT_MASK;
    state.r.data[3] = (f >> 48) & BINT_MASK;
    state.r.size = 4;
    #endif
    BIntTrim(&state.r);

    BIntLsh(&state.r, MAX(e - 53, 0), &state.r);
    BIntLsh(&BInt1, MAX(0, -(e - 53)), &state.s);
    BIntLsh(&BInt1, MAX(e - 53, 0), &state.mm);
    BIntLsh(&BInt1, MAX(e - 53, 0), &state.mp);
    dragonFixup(&state, precision, mode, f, e);

    /* Main digit generation loop */
    *k = state.k - 1;
    while(1)
    {
        state.k -= 1;
        BIntMulDigit(&state.r, 10, &state.r);
        BIntDiv(&state.r, &state.s, &state.tmp[0], &state.r, &state.tmp[1]);

        s = '0';
        if (state.tmp[0].size)
            s += state.tmp[0].data[0];
        buffer[(*size)++] = s;

        if (mode == NORMAL)
        {
            BIntMulDigit(&state.mm, 10, &state.mm);
            BIntMulDigit(&state.mp, 10, &state.mp);
            BIntLsh(&state.r, 1, &state.tmp[1]);
            BIntLsh(&state.s, 1, &state.tmp[2]);
            BIntAdd(&state.tmp[1], &state.mp, &state.tmp[3]);
            low = BIntCompare(&state.tmp[1], &state.mm) < 0;
            high = BIntCompare(&state.tmp[3], &state.tmp[2]) > 0;
            if (low || high || state.k == state.cutoff || *size >= BUFSIZE)
                break;
        }
        else
        {
            if (!state.r.size || state.k == state.cutoff || *size >= BUFSIZE)
                break;
        }
    }

    /* Round digits if required */
    dragonRound(&state, buffer, k, size, high, low, s);
}


static char *formatF(char *buffer,
                     int precision,
                     int sign,
                     int k,
                     int size)
{
    char *result, *current;
    int i;

    /* Preconditions */
    assert(buffer != NULL);
    assert(size < BUFSIZE);

    result = malloc(MAX(0, k) + 5 + sign + precision);
    current = result;
    if (!result)
        return NULL;

    /* Add sign */
    if (sign)
        *(current++) = '-';

    /* Pad if exponent is small */
    if (k < 0)
    {
        *(current++) = '0';

        if (precision > 0)
            *(current++) = '.';

        for (i = 0; i < MIN(-k - 1, precision); i++)
            *(current++) = '0';
    }

    /* Add digits */
    for (i = 0; k >= -precision; i++, k--)
    {
        if (i < size)
            *(current++) = buffer[i];
        else
            *(current++) = '0';

        if (k == 0 && precision > 0)
            *(current++) = '.';
    }

    *(current++) = 0;
    return result;
}


static char *formatE(char *buffer,
                     int precision,
                     int sign,
                     int k,
                     int size,
                     int upper)
{
    char *result, *current;
    int i;

    /* Preconditions */
    assert(buffer != NULL);
    assert(size < BUFSIZE);
    assert(sign == 0 || sign == 1);
    assert(upper == 0 || upper == 1);

    result = malloc(9 + sign + precision);
    current = result;
    if (!result)
        return NULL;

    /* Add sign and digits */
    if (sign)
        *(current++) = '-';

    for (i = 0; i < size; i++)
    {
        *(current++) = buffer[i];
        if (i == 0 && precision > 0)
            *(current++) = '.';
    }

    /* Pad to specified precision */
    for (; i < precision + 1; i++)
        *(current++) = '0';

    /* Add exponent symbol and sign */
    *(current++) = "eE"[upper];
    if (k < 0)
    {
        *(current++) = '-';
        k = -k;
    }
    else
        *(current++) = '+';

    /* Convert exponent to digits and add them */
    for (size = 0; k || size < 2; size++)
    {
        buffer[size] = '0' + k % 10;
        k = k / 10;
    }
    for (; size; size--)
        *(current++) = buffer[size - 1];

   *(current++) = 0;
    return result;
}


static char *generateF(double value,
                       int precision,
                       int sign)
{
    char buffer[BUFSIZE];
    int size, k;

    /* Call Dragon4 and format the digits */
    if (precision < 0)
        dragon(value, 0, NORMAL, buffer, &size, &k);
    else
        dragon(value, precision, ABSOLUTE, buffer, &size, &k);

    if (precision < 0)
        precision = MAX(0, size - k - 1);

    return formatF(buffer, precision, sign, k, size);
}


static char *generateE(double value,
                       int precision,
                       int upper,
                       int sign)
{
    char buffer[BUFSIZE];
    int size, k;

    /* Adjust precision and call Dragon4 to generate digits */
    if (precision < 0)
        dragon(value, 0, NORMAL, buffer, &size, &k);
    else
        dragon(value, (precision + 1), RELATIVE, buffer, &size, &k);

    if (precision < 0)
        precision = size - 1;

    return formatE(buffer, precision, sign, k, size, upper);
}


static char *generateG(double value,
                       int precision,
                       int upper,
                       int sign)
{
    char buffer[BUFSIZE];
    int size, k, fixed;

    if (precision == 0)
        precision = 1;

    /* Call Dragon4 to generate digits */
    if (precision < 0)
    {
        dragon(value, 0, NORMAL, buffer, &size, &k);
        fixed = k >= -4 && k <= (size - 1);
    }
    else
    {
        dragon(value, precision, RELATIVE, buffer, &size, &k);
        fixed = k >= -4 && k < precision;

        /* Remove trailing zeros and adjust precision */
        for (; size && precision > 0 && buffer[size - 1] == '0'; size--, precision--);
    }

    if (fixed)
    {
        precision = MAX(0, size - k - 1);
        return formatF(buffer, precision, sign, k, size);
    }
    else
    {
        precision = MAX(0, size - 1);
        return formatE(buffer, precision, sign, k, size, upper);
    }
}


char *BH_StringFromDouble(double value,
                          char format,
                          int precision)
{
    static const char *infStrings[] = { "inf", "-inf", "INF", "-INF" };
    static const char *nanStrings[] = { "nan", "NAN" };
    int sign, type, upper;

    type = BH_ClassifyDouble(value);
    upper = isupper(format) > 0;
    sign = (type & BH_FP_NEGATIVE) != 0;

    if (sign)
        value = fabs(value);

    /* Handle NaN and Inf */
    if (type == BH_FP_INFINITE)
        return BH_StringCopy(infStrings[upper * 2 + sign]);
    else if (type == BH_FP_NAN)
        return BH_StringCopy(nanStrings[upper]);

    if (format == 'g' || format == 'G')
        return generateG(value, precision, upper, sign);
    else if (format == 'e' || format == 'E')
        return generateE(value, precision, upper, sign);
    else
        return generateF(value, precision, sign);
}


static int caselessCompare(const char *src,
                           const char *ref)
{
    /* Preconditions */
    assert(src != NULL && ref != NULL);

    for (; *src && *ref && tolower(*src) == tolower(*ref); src++, ref++);

    if (*ref == 0)
        return 0;

    return *src - *ref;
}


static int parseFormat(const char *string,
                       size_t *size,
                       char *buffer,
                       int *sign,
                       int *e,
                       int *type)
{
    const char *current;
    int esign, dot, count;

    /* Preconditions */
    assert(string != NULL && buffer != NULL && sign != NULL && e != NULL && type != NULL);

    *sign = *e = esign = count = dot = 0;
    *type = BH_FP_ZERO;
    current = string;

    /* Skip whitespace */
    while (isspace(*current))
        current++;

    /* Check for NaN */
    if (caselessCompare(current, "nan") == 0)
    {
        *type = BH_FP_NAN; current += 3;
        goto done;
    }

    /* Leading sign */
    if (*current == '+' || *current == '-')
    {
        if (*current == '-')
            *sign = 1;
        current++;
    }

    /* Check for infinity */
    if (caselessCompare(current, "infinity") == 0)
    {
        *type = BH_FP_INFINITE; current += 8;
        goto done;
    }
    else if (caselessCompare(current, "inf") == 0)
    {
        *type = BH_FP_INFINITE; current += 3;
        goto done;
    }

    /* Read integer part of the float */
    for (; isdigit(*current); current++)
    {
        *type = BH_FP_NORMAL;
        if (count < 20 && (count || *current != '0'))
            buffer[count++] = *current;
        else if (count >= 20)
            dot--;
    }

    /* Read fract part of the float */
    if (*current == '.')
        current++;

    for (; isdigit(*current); current++)
    {
        *type = BH_FP_NORMAL;
        if ((count < 20))
        {
            dot++;
            if ((count || *current != '0'))
                buffer[count++] = *current;
        }
    }

    /* Read exp part of the float */
    if (*current == 'e' || *current == 'E')
    {
        current++;
        if (*current == '+' || *current == '-')
        {
            if (*current == '-')
                esign = 1;
            current++;
        }

        for (; isdigit(*current); current++)
            *e = *e * 10 + *current - '0';
    }

    if (esign)
        *e = -*e;
    *e -= dot;

done:
    if (size)
        *size = current - string;

    return count;
}


double BH_StringToDouble(const char *string,
                         size_t *size)
{
    int type, e, sign, i, count, shift;
    BInt r, s, tmp[5];
    char buffer[20];
    double result;
    uint64_t f;

    /* Preconditions */
    assert(string != NULL);

    /* Parse from string format */
    count = parseFormat(string, size, buffer, &sign, &e, &type);

    /* Handle special values */
    if (type == BH_FP_INFINITE)
    {
        if (sign)
            return -1.0 / 0.0;
        return 1.0 / 0.0;
    }
    else if (type == BH_FP_NAN)
        return 0.0 / 0.0;
    else if (type == BH_FP_ZERO)
    {
        /* Hacky solution to indicate we haven't seen any digit */
        if (size)
            *size = 0;
        return 0.0;
    }

    /* Handle zero input */
    if (count == 0)
    {
        if (sign)
            return -0.0;
        return 0.0;
    }

    /* Exponent too low */
    if (e < -329)
    {
        if (sign)
            return -0.0;
        return 0.0;
    }

    /* Exponent too high */
    if (e > 292)
    {
        if (sign)
            return -1.0 / 0.0;
        return 1.0 / 0.0;
    }

    /* Convert character buffer into integers */
    tmp[0].size = 1;
    r.size = 0;
    s = BInt1;
    for (i = 0; i < count; i++)
    {
        tmp[0].data[0] = buffer[i] - '0';
        BIntMulDigit(&r, 10, &r);
        BIntAdd(&r, &tmp[0], &r);
    }

    if (e >= 0)
        BIntPow10(&r, e, &r, &tmp[0]);
    else
        BIntPow10(&s, -e, &s, &tmp[0]);

    /* Calculate required shift */
    shift = -52;
    if (BIntCompare(&r, &s) >= 0)
    {
        BIntDiv(&r, &s, &tmp[0], &tmp[1], &tmp[2]);
        shift += BIntLog2(&tmp[0]);
    }
    else
    {
        BIntDiv(&s, &r, &tmp[0], &tmp[1], &tmp[2]);
        shift += -(BIntLog2(&tmp[0]) + 1);
    }

    /* Shift */
    if (shift > 0)
        BIntLsh(&s, shift, &s);
    else if (shift < 0)
        BIntLsh(&r, -shift, &r);

    /* Calculate final exponent and 53 bit integer */
    BIntDiv(&r, &s, &tmp[0], &tmp[1], &tmp[2]);
    BIntRsh(&s, 1, &s);
    if (BIntCompare(&tmp[1], &s) > 0 || (BIntCompare(&tmp[1], &s) == 0 && (tmp[0].data[0] & 0x1)))
    {
        BIntAdd(&tmp[0], &BInt1, &tmp[0]);
        if (BIntCompare(&tmp[0], &BInt53) >= 0)
        {
            BIntRsh(&tmp[0], 1, &tmp[0]);
            shift++;
        }
    }

    /* Create double from integer and exponent */
    #ifndef BH_TWEAK_SHORT_BINT
    f = (tmp[0].data[1] & 0x001FFFFFul);
    f = (f << 32) | tmp[0].data[0];
    #else
    f = (tmp[0].data[3] & 0x1F);
    f = (f << 16) | tmp[0].data[2];
    f = (f << 16) | tmp[0].data[1];
    f = (f << 16) | tmp[0].data[0];
    #endif

    result = ldexp(f, shift);
    if (sign)
        result = -result;

    return result;
}
