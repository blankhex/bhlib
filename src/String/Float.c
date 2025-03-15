#include <BH/String.h>
#include <BH/Util.h>
#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


#define MAX(a,b)    (((a)>(b))?(a):(b))
#define MIN(a,b)    (((a)<(b))?(a):(b))
#define BUFSIZE     309
#define DIGITS      70
#define NORMAL      0
#define ABSOLUTE    1
#define RELATIVE    2


typedef struct BInt {
    int size;
    uint16_t data[DIGITS];
} BInt;


struct DragonState
{
    BInt r;
    BInt s;
    BInt mm;
    BInt mp;
    BInt tmp[5];
    int cutoff;
    int k;
};


static const BInt BInt1 = {1, {1}};
static const BInt BInt10 = {1, {10}};


static const uint8_t clzLookup[256] =
{
    8, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static int BIntClz(uint16_t value)
{
    if (value & 0xFF00)
        return clzLookup[(value >> 8) & 0xFF];
    else
        return 8 + clzLookup[value & 0xFF];
}


static void BIntTrim(BInt *in)
{
    while (in->size && !in->data[in->size - 1])
        in->size--;
}


static int BIntCompare(const BInt *a,
                       const BInt *b)
{
    int i;

    /* Compare by lengths */
    i = a->size - b->size;
    if (a->size - b->size)
        return a->size - b->size;

    /* Compare by blocks */
    for (i = a->size; i; i--)
    {
        if (a->data[i - 1] < b->data[i - 1])
            return -1;
        else if (a->data[i - 1] > b->data[i - 1])
            return 1;
    }

    return 0;
}


static void BIntAdd(const BInt *a,
                    const BInt *b,
                    BInt *out)
{
    uint32_t carry;
    int i;

    assert(a->size + 1 <= DIGITS);
    assert(b->size + 1 <= DIGITS);

    /* Addition loop */
    carry = 0;
    for (i = 0; i < a->size || i < b->size; i++)
    {
        if (i < a->size)
            carry += a->data[i];
        if (i < b->size)
            carry += b->data[i];
        
        out->data[i] = carry & 0xFFFF;
        carry = (carry >> 16);
    }

    /* Handle new digit */
    if (carry)
        out->data[i++] = carry;

    out->size = i;
}


static void BIntSub(const BInt *a,
                    const BInt *b,
                    BInt *out)
{
    uint32_t carry;
    int i;

    /* Main subtraction loop */
    carry = 0;
    for (i = 0; i < a->size || i < b->size; i++)
    {
        if (i < a->size)
            carry += a->data[i];
        if (i < b->size)
            carry -= b->data[i];
        
        out->data[i] = carry & 0xFFFF;
        carry = (carry & 0xFFFF0000) | (carry >> 16);
    }

    /* Trim leading zeros */
    out->size = a->size;
    BIntTrim(out);
}


static void BIntMul(const BInt *a,
                    const BInt *b,
                    BInt *out)
{
    uint32_t carry;
    int i, j;

    assert(a->size + b->size <= DIGITS);

    /* Zero out the result */
    memset(out->data, 0, sizeof(out->data));
    for (i = 0; i < DIGITS; i++)
        out->data[i] = 0;

    /* Multiplication loop */
    for (i = 0; i < a->size; i++)
    {
        carry = 0;
        for (j = 0; j < b->size; j++)
        {
            carry += out->data[i + j];
            carry += (uint32_t)a->data[i] * (uint32_t)b->data[j];
            out->data[i + j] = carry & 0xFFFF;
            carry = (carry >> 16);
        }
        out->data[i + j] += carry;
    }

    /* Trim leading zeros */
    out->size = a->size + b->size;
    BIntTrim(out);
}


static void BIntMulDigit(const BInt *a,
                         uint16_t b,
                         BInt *out)
{
    uint32_t carry;
    int i;

    assert(a->size + 1 <= DIGITS);

    /* Multiplication loop */
    carry = 0;
    for (i = 0; i < a->size; i++)
    {
        carry += (uint32_t)a->data[i] * b;
        out->data[i] = carry & 0xFFFF;
        carry = (carry >> 16);
    }
    out->data[i] = carry;

    /* Trim leading zeros */
    out->size = a->size + 1;
    BIntTrim(out);
}


static void BIntLsh(const BInt *in,
                    int amount,
                    BInt *out)
{
    int blocks, bits, i;
    uint16_t low, high;

    blocks = amount / 16;
    bits = amount % 16;

    assert(in->size + blocks + (bits > 0) <= DIGITS);

    if (!in->size)
    {
        out->size = 0;
        return;
    }

    /* Main shift loop */
    if (bits)
    {
        high = 0;
        for (i = in->size + blocks; i > blocks; i--)
        {
            low = in->data[i - blocks - 1] >> (16 - bits);
            out->data[i] = low | high;
            high = in->data[i - blocks - 1] << bits;
        }
        out->data[i] = high;
        out->size = in->size + blocks + 1;
    } 
    else
    {
        for (i = in->size; i; i--)
            out->data[i - 1 + blocks] = in->data[i - 1];
        out->size = in->size + blocks;
    }
    
    /* Trim leading zeros and zero out lower blocks */
    BIntTrim(out);
    for (i = blocks; i; i--)
        out->data[i - 1] = 0;
}


static void BIntRsh(const BInt *in,
                    int amount,
                    BInt *out)
{
    int blocks, bits, i;
    uint16_t low, high;

    blocks = amount / 16;
    bits = amount % 16;

    /* Zero size input or shift is bigger then input */
    if (in->size == 0 || in->size <= blocks)
    {
        out->size = 0;
        return;
    }

    /* Shift and copy parts of two blocks */
    low = in->data[blocks] >> bits;
    high = 0;
    for (i = 0; i < in->size - blocks - 1; i++)
    {
        high = in->data[i + blocks + 1] << (16 - bits);
        out->data[i] = low | high;
        low = in->data[i + blocks + 1] >> bits;
    }
    out->data[in->size - blocks - 1] = low;

    /* Trim leading zeros */
    out->size = in->size - blocks;
    BIntTrim(out);
}


static uint16_t BIntGuess(const BInt *a,
                          const BInt *b)
{
    uint32_t tmp;

    if (BIntCompare(a, b) < 0)
        return 0;

    tmp = a->data[a->size - 1];
    if (a->size != b->size)
        tmp = tmp << 16 | a->data[a->size - 2];

    return tmp / b->data[b->size - 1];
}


static void BIntDiv(const BInt *a,
                    const BInt *b,
                    BInt *q,
                    BInt *r,
                    BInt *tmp)
{
    uint16_t digit;
    int shift;

    /* Handle case where a is less then b */
    if (BIntCompare(a, b) < 0)
    {
        *r = *a;
        q->size = 0;
        return;
    }

    /* Normilize input to reduce tries */
    shift = BIntClz(b->data[b->size - 1]);
    BIntLsh(a, shift, &tmp[0]);
    BIntLsh(b, shift, &tmp[1]);
    
    /* Prepare first step of the division */
    q->size = 0;
    r->size = 0;
    while (BIntCompare(r, &tmp[1]) < 0)
    {
        BIntLsh(r, 16, r);
        r->data[0] = tmp[0].data[--tmp[0].size];
        r->size += !r->size;
    }

    while (1)
    {
        /* Make a guess and check */
        digit = BIntGuess(r, &tmp[1]);
        BIntMulDigit(&tmp[1], digit, &tmp[2]);
        while (BIntCompare(r, &tmp[2]) < 0)
        {
            --digit;
            BIntSub(&tmp[2], &tmp[1], &tmp[2]);
        }

        /* Store digit in quotient */
        BIntSub(r, &tmp[2], r);
        BIntLsh(q, 16, q);
        q->data[0] = digit;
        q->size += !q->size;

        /* Fetch next digit or exit */
        if (!tmp[0].size)
            break;

        BIntLsh(r, 16, r);
        r->data[0] = tmp[0].data[--tmp[0].size];
        if (!r->size)
            r->size = 1;
    }

    /* Normilize remainder */
    BIntRsh(r, shift, r);
}


static void dragonFixup(struct DragonState *state,
                        int precision,
                        int mode,
                        uint64_t f)
{
    if (f == (((uint64_t)1) << 52))
    {
        BIntLsh(&state->mp, 1, &state->mp);
        BIntLsh(&state->r, 1, &state->r);
        BIntLsh(&state->s, 1, &state->s);
    }
    state->k = 0;

    BIntDiv(&state->s, &BInt10, &state->tmp[0], &state->tmp[1], state->tmp + 2);
    if (state->tmp[1].size)
        BIntAdd(&state->tmp[0], &BInt1, &state->tmp[0]);

    while (BIntCompare(&state->r, &state->tmp[0]) < 0)
    {
        state->k -= 1;
        BIntMulDigit(&state->r, 10, &state->r);
        BIntMulDigit(&state->mm, 10, &state->mm);
        BIntMulDigit(&state->mp, 10, &state->mp);
        BIntDiv(&state->s, &BInt10, &state->tmp[0], &state->tmp[1], state->tmp + 2);
        if (state->tmp[1].size)
            BIntAdd(&state->tmp[0], &BInt1, &state->tmp[0]);
    }

    BIntLsh(&state->r, 1, &state->tmp[0]);
    BIntAdd(&state->tmp[0], &state->mp, &state->tmp[0]);
    BIntLsh(&state->s, 1, &state->tmp[1]);
    while (BIntCompare(&state->tmp[0], &state->tmp[1]) >= 0)
    {
        state->k += 1;
        BIntMulDigit(&state->s, 10, &state->s);
        BIntLsh(&state->s, 1, &state->tmp[1]);
    }

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
    state.r.data[0] = f & 0xFFFF; state.r.data[1] = (f >> 16) & 0xFFFF;
    state.r.data[2] = (f >> 32) & 0xFFFF; state.r.data[3] = (f >> 48) & 0xFFFF;
    state.r.size = 4; BIntTrim(&state.r);

    BIntLsh(&state.r, MAX(e - 53, 0), &state.r);
    BIntLsh(&BInt1, MAX(0, -(e - 53)), &state.s);
    BIntLsh(&BInt1, MAX(e - 53, 0), &state.mm);
    BIntLsh(&BInt1, MAX(e - 53, 0), &state.mp);
    dragonFixup(&state, precision, mode, f);

    /* Main digit generation loop */
    *k = state.k - 1;
    while(1) 
    {
        state.k -= 1;
        BIntMulDigit(&state.r, 10, &state.r);
        BIntDiv(&state.r, &state.s, &state.tmp[0], &state.r, state.tmp + 1);
        
        s = '0';
        if (state.tmp[0].size)
            s += state.tmp[0].data[0];
        buffer[(*size)++] = s;

        if (mode == NORMAL)
        {
            BIntLsh(&state.r, 1, &state.tmp[1]);
            BIntLsh(&state.s, 1, &state.tmp[2]);
            BIntSub(&state.tmp[2], &state.mp, &state.tmp[2]);
            BIntMulDigit(&state.mm, 10, &state.mm);
            BIntMulDigit(&state.mp, 10, &state.mp);
            low = BIntCompare(&state.tmp[1], &state.mm) < 0;
            high = BIntCompare(&state.tmp[1], &state.tmp[2]) > 0;
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


static char *formatF(char buffer[BUFSIZE],
                     int precision,
                     int sign,
                     int k,
                     int size)
{
    char *result, *current;
    int i;
    
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


static char *formatE(char buffer[BUFSIZE],
                     int precision,
                     int sign,
                     int k,
                     int size,
                     int upper)
{
    char *result, *current;
    int i;

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


double BH_StringToDouble(const char *string,
                         size_t *size)
{
    int nsign, esign, e, dot;
    const char *current;
    char buffer[4];
    size_t count;

    nsign = 0; esign = 0; e = 0; count = 0; dot = 0;
    current = string;
    
    /* Skip whitespace */
    while (isspace(*current))
        current++;
    
    /* Leading sign */
    if (*current == '+' || *current == '-')
    {
        if (*current == '-')
            nsign = 1;
        current++;
    }
    
    /* Read integer part of the float */
    for (; isdigit(*current); current++)
    {
        if (count < sizeof(buffer) && (count || *current != '0'))
            buffer[count++] = *current;
        else if (count >= sizeof(buffer))
            dot--;
    }

    /* Read fract part of the float */
    if (*current == '.')
        current++;
    
    for (; isdigit(*current); current++)
    {
        if ((count < sizeof(buffer)))
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
            e = e * 10 + *current - '0';
    }

    if (esign)
        e = -e;
    e -= dot;

    if (size)
        *size = current - string;
    
    BH_UNUSED(nsign);
    BH_UNUSED(BIntMul);
    return 0.0;
}
