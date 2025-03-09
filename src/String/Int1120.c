#include "String.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>


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


static const uint16_t pow10Data[] =
{
    0x0001, 0x000A, 0x0064, 0x2710, 0xE100, 0x05F5, 0x0000, 0x6FC1,
    0x86F2, 0x0023, 0x0000, 0x0000, 0xEF81, 0x85AC, 0x415B, 0x2D6D,
    0x04EE, 0x0000, 0x0000, 0x0000, 0x0000, 0x1F01, 0xBF6A, 0xED64,
    0x6E38, 0x97ED, 0xDAA7, 0xF9F4, 0xE93F, 0x4F03, 0x0018, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3E01,
    0x2E95, 0x9909, 0x03DF, 0x38FD, 0x0F15, 0xE42F, 0x2374, 0xF5EC,
    0xD3CF, 0xDC08, 0xC404, 0xB0DA, 0xBCCD, 0x7F19, 0xA633, 0x2603,
    0xE91F, 0x024E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x7C01, 0x982E, 0x875B, 0xBED3, 0x9F72, 0xD8D9,
    0x2F87, 0x1215, 0x50C6, 0x6BDE, 0x6E70, 0xCF4A, 0xD80F, 0xD595,
    0x716E, 0x26B2, 0x66B0, 0xADC6, 0x3624, 0x1D15, 0xD35A, 0x3C42,
    0x540E, 0x63FF, 0x73C0, 0xCC55, 0xEF17, 0x65F9, 0x28F2, 0x55BC,
    0xC7F7, 0x80DC, 0xEDDC, 0xF46E, 0xEFCE, 0x5FDC, 0x53F7, 0x0005,
};


static const int pow10Index[] =
{
    0, 1, 2, 3, 4, 6, 10, 17, 31, 58,
};


static const int pow10Size[] =
{
    1, 1, 1, 1, 2, 4, 7, 14, 27, 54,
};


static void pow10Set(int index,
                     BH_Int1120 *out)
{
    out->size = pow10Size[index];
    memcpy(out->digits, pow10Data + pow10Index[index], out->size * sizeof(uint16_t));
}


int BH_Int1120Clz(const uint16_t value)
{


    if (value & 0xFF00)
        return clzLookup[(value >> 8) & 0xFF];
    else
        return 8 + clzLookup[value & 0xFF];
}


int BH_Int1120Compare(const BH_Int1120 *a,
                      const BH_Int1120 *b)
{
    int i, result;

    /* Compare by lengths */
    result = a->size - b->size;
    if (result)
        return result;

    /* Compare by blocks */
    for (i = a->size; i; i--)
    {
        if (a->digits[i - 1] < b->digits[i - 1])
            return -1;
        else if (a->digits[i - 1] > b->digits[i - 1])
            return 1;
    }

    return 0;
}


void BH_Int1120Add(const BH_Int1120 *a,
                   const BH_Int1120 *b,
                   BH_Int1120 *out)
{
    const BH_Int1120 *small, *big;
    uint32_t carry, tmp;
    int i;

    small = b;
    big = a;

    assert(a->size + 1 <= BH_INT1120_DIGITS);
    assert(b->size + 1 <= BH_INT1120_DIGITS);

    /* Find smaller interger */
    if (a->size < b->size)
    {
        small = a;
        big = b;
    }

    /* Main addition loop */
    carry = 0;
    for (i = 0; i < small->size; i++)
    {
        tmp = (uint32_t)small->digits[i] + (uint32_t)big->digits[i] + carry;
        carry = (tmp >> 16) & 0xFFFF;
        out->digits[i] = tmp & 0xFFFF;
    }

    /* Carry propogation */
    for (; i < big->size; i++)
    {
        tmp = (uint32_t)big->digits[i] + carry;
        carry = (tmp >> 16) & 0xFFFF;
        out->digits[i] = tmp & 0xFFFF;
    }

    /* Handle carry */
    if (carry)
        out->digits[i++] = carry;

    out->size = i;
}


void BH_Int1120Sub(const BH_Int1120 *a,
                   const BH_Int1120 *b,
                   BH_Int1120 *out)
{
    uint32_t carry, tmp;
    int i;

    /* Main subtraction loop */
    carry = 0;
    for (i = 0; i < b->size; i++)
    {
        tmp = (uint32_t)a->digits[i] - (uint32_t)b->digits[i] - carry;
        carry = (tmp >> 31) & 0x1;
        out->digits[i] = tmp & 0xFFFF;
    }

    /* Carry propogation */
    for (; i < a->size; i++)
    {
        tmp = (uint32_t)a->digits[i] - carry;
        carry = (tmp >> 31) & 0x1;
        out->digits[i] = tmp & 0xFFFF;
    }

    /* Truncate length on empty blocks */
    out->size = a->size;
    while(out->size && !out->digits[out->size - 1])
        out->size--;
}


void BH_Int1120Mul(const BH_Int1120 *a,
                   const BH_Int1120 *b,
                   BH_Int1120 *out)
{
    int i, j;
    uint32_t tmp, carry;

    assert(a->size + b->size <= BH_INT1120_DIGITS);

    for (i = 0; i < BH_INT1120_DIGITS; i++)
        out->digits[i] = 0;

    for (i = 0; i < a->size; i++)
    {
        carry = 0;

        /* Multiplication loop */
        for (j = 0; j < b->size; j++)
        {
            carry += (uint32_t)out->digits[i + j];
            tmp = (uint32_t)a->digits[i] * (uint32_t)b->digits[j] + carry;
            carry = (tmp >> 16) & 0xFFFF;
            out->digits[i + j] = tmp & 0xFFFF;
        }

        /* Carry propagation */
        if (carry)
        {
            tmp = (uint32_t)out->digits[i + j] + carry;
            out->digits[i + j] = tmp & 0xFFFF;
        }
    }

    out->size = a->size + b->size;
    if (!out->digits[out->size - 1])
        out->size--;
}


void BH_Int1120MulDigit(const BH_Int1120 *in,
                        uint16_t digit,
                        BH_Int1120 *out)
{
    int i;
    uint32_t tmp, carry;

    assert(in->size + 1 <= BH_INT1120_DIGITS);

    for (i = 0; i < BH_INT1120_DIGITS; i++)
        out->digits[i] = 0;

    /* Multiplication loop */
    carry = 0;
    for (i = 0; i < in->size; i++)
    {
        carry += (uint32_t)out->digits[i];
        tmp = (uint32_t)in->digits[i] * digit + carry;
        carry = (tmp >> 16) & 0xFFFF;
        out->digits[i] = tmp & 0xFFFF;
    }

    /* Carry propagation */
    if (carry)
    {
        tmp = (uint32_t)out->digits[i] + carry;
        out->digits[i] = tmp & 0xFFFF;
    }

    out->size = in->size + 1;
    if (!out->digits[out->size - 1])
        out->size--;
}


static uint16_t BH_Int1120DivGuess(const BH_Int1120 *a,
                                   const BH_Int1120 *b)
{
    uint32_t tmp;

    /* Compare two values */
    if (BH_Int1120Compare(a, b) < 0)
        return 0;

    /* Make a guess */
    tmp = a->digits[a->size - 1];
    if (a->size != b->size)
        tmp = tmp << 16 | a->digits[a->size - 2];

    return tmp / b->digits[b->size - 1];
}


void BH_Int1120Div(const BH_Int1120 *a,
                   const BH_Int1120 *b,
                   BH_Int1120 *q,
                   BH_Int1120 *r)
{
    BH_Int1120 left, right, tmp;
    uint16_t guess;
    int shift;

    assert(a->size >= b->size);
    assert(b->size > 0);

    /* Normilize input to reduce tries */
    shift = BH_Int1120Clz(b->digits[b->size - 1]);
    BH_Int1120Lsh(a, shift, &left);
    BH_Int1120Lsh(b, shift, &right);

    /* Prepare first step of the division */
    q->size = 0;
    r->size = 0;
    while (BH_Int1120Compare(r, &right) < 0)
    {
        BH_Int1120Lsh(r, 16, r);
        r->digits[0] = left.digits[--left.size];

        if (!r->size)
            r->size = 1;
    }

    while (1)
    {
        /* Make a guess and check */
        guess = BH_Int1120DivGuess(r, &right);
        BH_Int1120MulDigit(&right, guess, &tmp);

        /* If the guess was wrong - decrement guess and try again */
        while (BH_Int1120Compare(r, &tmp) < 0)
            BH_Int1120MulDigit(&right, --guess, &tmp);

        /* Store digit in quotient */
        BH_Int1120Lsh(q, 16, q);
        q->digits[0] = guess;
        if (!q->size)
            q->size = 1;

        /* Adjust remainder */
        BH_Int1120Sub(r, &tmp, r);

        /* Fetch next digit or exit */
        if (!left.size)
            break;

        BH_Int1120Lsh(r, 16, r);
        r->digits[0] = left.digits[--left.size];
        if (!r->size)
            r->size = 1;
    }

    /* Normilize remainder */
    BH_Int1120Rsh(r, shift, r);
}


void BH_Int1120Pow10(int exponent,
                     BH_Int1120 *out)
{
    BH_Int1120 one;

    one.digits[0] = 1;
    one.size = 1;
    BH_Int1120MulPow10(&one, exponent, out);
}


void BH_Int1120MulPow10(const BH_Int1120 *in,
                        int exponent,
                        BH_Int1120 *out)
{
    BH_Int1120 *current, *next, *swap;
    BH_Int1120 tmp[2], factor;
    int index;

    /* Make sure exponent is low, otherwise we get an overflow */
    assert(exponent < 512);

    /* Prepare variables and temporaries */
    current = tmp;
    next = tmp + 1;
    index = 0;
    *current = *in;

    /* Main multiply loop */
    while (exponent)
    {
        if (exponent & 0x1)
        {
            pow10Set(index, &factor);
            BH_Int1120Mul(current, &factor, next);
            swap = current;
            current = next;
            next = swap;
        }
        index++;
        exponent >>= 1;
    }
    *out = *current;
}


void BH_Int1120Pow2(int exponent,
                    BH_Int1120 *out)
{
    int blocks, bits, i;

    assert(exponent < 1120);
    blocks = exponent / 16;
    bits = exponent % 16;

    /* Zero out blocks and set one bit */
    for (i = 0; i < blocks; i++)
        out->digits[i] = 0;

    out->digits[blocks] = (1 << bits);
    out->size = blocks;
}


void BH_Int1120Lsh(const BH_Int1120 *in,
                   int amount,
                   BH_Int1120 *out)
{
    int blocks, bits, i;
    uint16_t low, high;

    /* No input - no output */
    if (in->size == 0)
        return;

    blocks = amount / 16;
    bits = amount % 16;

    assert(in->size + blocks + (bits > 0) <= BH_INT1120_DIGITS);

    if (bits)
    {
        /* Shift and copy parts of two blocks */
        low = 0;
        high = in->digits[in->size - 1] >> (16 - bits);
        for (i = in->size; i > 1; i--)
        {
            out->digits[i + blocks] = high | low;
            low = in->digits[i - 1] << bits;
            high = in->digits[i - 2] >> (16 - bits);
        }
        out->digits[blocks + 1] = high | low;
        out->digits[blocks] = in->digits[0] << bits;
        out->size = in->size + blocks + 1;
    }
    else
    {
        /* Copy whole blocks */
        for (i = in->size; i; i--)
            out->digits[i - 1 + blocks] = in->digits[i - 1];
        out->size = in->size + blocks;
    }

    /* Check upper block */
    if (!out->digits[out->size - 1])
        out->size--;

    /* Zero out lower blocks */
    for (i = blocks; i; i--)
        out->digits[i - 1] = 0;
}


void BH_Int1120Rsh(const BH_Int1120 *in,
                   int amount,
                   BH_Int1120 *out)
{
    int blocks, bits, i;
    uint16_t low, high;

    /* No input - no output */
    if (in->size == 0)
        return;

    blocks = amount / 16;
    bits = amount % 16;

    if (bits)
    {
        /* Shift and copy parts of two blocks */
        low = in->digits[blocks] >> bits;
        high = in->digits[blocks + 1] << (16 - bits);

        for (i = 0; i < in->size - blocks - 2; i++)
        {
            out->digits[i] = low | high;
            low = in->digits[i + blocks + 1] >> bits;
            high = in->digits[i + blocks + 2] << (16 - bits);
        }

        out->digits[in->size - blocks - 2] = low | high;
        out->digits[in->size - blocks - 1] = in->digits[in->size - 1] >> bits;
    }
    else
    {
        /* Copy whole blocks */
        for (i = 0; i < in->size - blocks; i++)
            out->digits[i] = in->digits[i + blocks];
    }

    /* Check upper block */
    out->size = in->size - blocks;
    if (!out->digits[out->size - 1])
        out->size--;
}
