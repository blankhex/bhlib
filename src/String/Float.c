#include <BH/String.h>
#include <BH/Util.h>
#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


/* Common defines */
#define MAX(a,b)    (((a)>(b))?(a):(b))
#define MIN(a,b)    (((a)<(b))?(a):(b))
#define BUFSIZE     309
#define DIGITS      80

/* Modes */
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
    long k;
    int cutoff;
};


static const BInt BInt1 = {1, {1}};
static const BInt BInt53 = {4, {0x0000, 0x0000, 0x0000, 0x0020}};


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


static const BInt powLookup[] =
{
    {1, {0x000A}},
    {1, {0x0064}},
    {1, {0x2710}},
    {2, {0xE100, 0x05F5}},
    {4, {0x0000, 0x6FC1, 0x86F2, 0x0023}},
    {7, {0x0000, 0x0000, 0xEF81, 0x85AC, 0x415B, 0x2D6D, 0x04EE}},
    {14, {0x0000, 0x0000, 0x0000, 0x0000, 0x1F01, 0xBF6A, 0xED64, 0x6E38,
          0x97ED, 0xDAA7, 0xF9F4, 0xE93F, 0x4F03, 0x0018}},
    {27, {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
          0x3E01, 0x2E95, 0x9909, 0x03DF, 0x38FD, 0x0F15, 0xE42F, 0x2374,
          0xF5EC, 0xD3CF, 0xDC08, 0xC404, 0xB0DA, 0xBCCD, 0x7F19, 0xA633,
          0x2603, 0xE91F, 0x024E}},
    {54, {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
          0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
          0x7C01, 0x982E, 0x875B, 0xBED3, 0x9F72, 0xD8D9, 0x2F87, 0x1215,
          0x50C6, 0x6BDE, 0x6E70, 0xCF4A, 0xD80F, 0xD595, 0x716E, 0x26B2,
          0x66B0, 0xADC6, 0x3624, 0x1D15, 0xD35A, 0x3C42, 0x540E, 0x63FF,
          0x73C0, 0xCC55, 0xEF17, 0x65F9, 0x28F2, 0x55BC, 0xC7F7, 0x80DC,
          0xEDDC, 0xF46E, 0xEFCE, 0x5FDC, 0x53F7, 0x0005}}
};


static int BIntClz(uint16_t value)
{
    if (value & 0xFF00)
        return clzLookup[(value >> 8) & 0xFF];
    else
        return 8 + clzLookup[value & 0xFF];
}


static int BIntLog2(const BInt *in)
{
    /* Preconditions */
    assert(in != NULL);
    assert(in->size != 0);
    assert(in->data[in->size - 1] != 0);

    return 15 - BIntClz(in->data[in->size - 1]) + 16 * (in->size - 1);
}


static void BIntTrim(BInt *in)
{
    /* Preconditions */
    assert(in != NULL);

    while (in->size && !in->data[in->size - 1])
        in->size--;
}


static int BIntCompare(const BInt *a,
                       const BInt *b)
{
    int i;

    /* Preconditions */
    assert(a != NULL && b != NULL);

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

    /* Preconditions */
    assert(a != NULL && b != NULL && out != NULL);
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

    /* Preconditions */
    assert(a != NULL && b != NULL && out != NULL);
    assert(BIntCompare(a, b) >= 0);

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

    /* Preconditions */
    assert(a != NULL && b != NULL && out != NULL);
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

    /* Preconditions */
    assert(a != NULL && out != NULL);
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


static void BIntPow10(const BInt *in,
                      int exponent,
                      BInt *out,
                      BInt *tmp)
{
    int i, current;

    /* Preconditions */
    assert(in != NULL && out != NULL && tmp != NULL);
    assert(exponent >= 0 && exponent < 512);

    tmp[0] = *in;
    for (current = 0, i = 0; exponent; i++, exponent >>= 1)
    {
        if (!(exponent & 0x1))
            continue;

        BIntMul(&tmp[current], &powLookup[i], &tmp[1 - current]);
        current = 1 - current;
    }
    *out = tmp[current];
}


static void BIntLsh(const BInt *in,
                    int amount,
                    BInt *out)
{
    int blocks, bits, i;
    uint16_t low, high;

    /* Preconditions */
    assert(in != NULL && out != NULL);
    assert(amount >= 0 && in->size + (amount + 15) / 16 <= DIGITS);

    blocks = amount / 16;
    bits = amount % 16;
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

    /* Preconditions */
    assert(in != NULL && out != NULL);
    assert(amount >= 0);

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

    /* Preconditions */
    assert(a != NULL && b != NULL);
    assert(a->size > 0 && b->size > 0);

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

    /* Preconditions */
    assert(a != NULL && b != NULL && q != NULL && r != NULL && tmp != NULL);
    assert(b->size != 0);

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
    state->k = BIntClz((f >> 48) & 0xFFFF);
    state->k += (state->k == 16) ? (BIntClz((f >> 32) & 0xFFFF)) : (0);
    state->k += (state->k == 32) ? (BIntClz((f >> 16) & 0xFFFF)) : (0);
    state->k += (state->k == 48) ? (BIntClz(f & 0xFFFF)) : (0);

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
    state.r.data[0] = f & 0xFFFF; state.r.data[1] = (f >> 16) & 0xFFFF;
    state.r.data[2] = (f >> 32) & 0xFFFF; state.r.data[3] = (f >> 48) & 0xFFFF;
    state.r.size = 4; BIntTrim(&state.r);

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
            return -INFINITY;
        return INFINITY;
    }
    else if (type == BH_FP_NAN)
        return NAN;
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
            return -INFINITY;
        return INFINITY;
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
    f = (tmp[0].data[3] & 0x1F);
    f = (f << 16) | tmp[0].data[2];
    f = (f << 16) | tmp[0].data[1];
    f = (f << 16) | tmp[0].data[0];

    result = ldexp(f, shift);
    if (sign)
        result = -result;

    return result;
}
