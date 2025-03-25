/* Platform dependant definition */
#ifndef BH_TWEAK_SHORT_BINT
#define BINT_SIZE   40
#define BINT_TYPE   uint32_t
#define BINT_TTYPE  uint64_t
#define BINT_BITS   32
#define BINT_MASK   0xFFFFFFFFul
#else
#define BINT_SIZE   80
#define BINT_TYPE   uint16_t
#define BINT_TTYPE  uint32_t
#define BINT_BITS   16
#define BINT_MASK   0xFFFFu
#endif


typedef struct BInt {
    int size;
    BINT_TYPE data[BINT_SIZE];
} BInt;


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


#ifndef BH_TWEAK_SHORT_BINT
static const BInt BInt1 = {1, {0x00000001ul}};
static const BInt BInt53 = {2, {0x00000000ul, 0x00200000ul}};


static const BInt powLookup[] =
{
    {1, {0x0000000Aul}},
    {1, {0x00000064ul}},
    {1, {0x00002710ul}},
    {1, {0x05F5E100ul}},
    {2, {0x6FC10000ul, 0x002386F2ul}},
    {4, {0x00000000ul, 0x85ACEF81ul, 0x2D6D415Bul, 0x000004EEul}},
    {7, {0x00000000ul, 0x00000000ul, 0xBF6A1F01ul, 0x6E38ED64ul, 0xDAA797EDul,
         0xE93FF9F4ul, 0x00184F03ul}},
    {14, {0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul, 0x2E953E01ul,
          0x03DF9909ul, 0x0F1538FDul, 0x2374E42Ful, 0xD3CFF5ECul, 0xC404DC08ul,
          0xBCCDB0DAul, 0xA6337F19ul, 0xE91F2603ul, 0x0000024Eul}},
    {27, {0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
          0x00000000ul, 0x00000000ul, 0x00000000ul, 0x982E7C01ul, 0xBED3875Bul,
          0xD8D99F72ul, 0x12152F87ul, 0x6BDE50C6ul, 0xCF4A6E70ul, 0xD595D80Ful,
          0x26B2716Eul, 0xADC666B0ul, 0x1D153624ul, 0x3C42D35Aul, 0x63FF540Eul,
          0xCC5573C0ul, 0x65F9EF17ul, 0x55BC28F2ul, 0x80DCC7F7ul, 0xF46EEDDCul,
          0x5FDCEFCEul, 0x000553F7ul}}
};


static int BIntClz(BINT_TYPE value)
{
    if (value & 0xFF000000ul)
        return clzLookup[(value >> 24) & 0xFF];
    else if (value & 0x00FF0000ul)
        return 8 + clzLookup[(value >> 16) & 0xFF];
    else if (value & 0x0000FF00ul)
        return 16 + clzLookup[(value >> 8) & 0xFF];
    else
        return 24 + clzLookup[value & 0xFF];
}
#else
static const BInt BInt1 = {1, {0x0001u}};
static const BInt BInt53 = {4, {0x0000u, 0x0000u, 0x0000u, 0x0020u}};


static const BInt powLookup[] =
{
    {1, {0x000Au}},
    {1, {0x0064u}},
    {1, {0x2710u}},
    {2, {0xE100u, 0x05F5u}},
    {4, {0x0000u, 0x6FC1u, 0x86F2u, 0x0023u}},
    {7, {0x0000u, 0x0000u, 0xEF81u, 0x85ACu, 0x415Bu, 0x2D6Du, 0x04EEu}},
    {14, {0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x1F01u, 0xBF6Au, 0xED64u,
          0x6E38u, 0x97EDu, 0xDAA7u, 0xF9F4u, 0xE93Fu, 0x4F03u, 0x0018u}},
    {27, {0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u,
          0x0000u, 0x3E01u, 0x2E95u, 0x9909u, 0x03DFu, 0x38FDu, 0x0F15u,
          0xE42Fu, 0x2374u, 0xF5ECu, 0xD3CFu, 0xDC08u, 0xC404u, 0xB0DAu,
          0xBCCDu, 0x7F19u, 0xA633u, 0x2603u, 0xE91Fu, 0x024Eu}},
    {54, {0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u,
    0x0000u,
          0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u,
          0x0000u, 0x7C01u, 0x982Eu, 0x875Bu, 0xBED3u, 0x9F72u, 0xD8D9u,
          0x2F87u, 0x1215u, 0x50C6u, 0x6BDEu, 0x6E70u, 0xCF4Au, 0xD80Fu,
          0xD595u, 0x716Eu, 0x26B2u, 0x66B0u, 0xADC6u, 0x3624u, 0x1D15u,
          0xD35Au, 0x3C42u, 0x540Eu, 0x63FFu, 0x73C0u, 0xCC55u, 0xEF17u,
          0x65F9u, 0x28F2u, 0x55BCu, 0xC7F7u, 0x80DCu, 0xEDDCu, 0xF46Eu,
          0xEFCEu, 0x5FDCu, 0x53F7u, 0x0005u}}
};


static int BIntClz(BINT_TYPE value)
{
    if (value & 0xFF00)
        return clzLookup[(value >> 8) & 0xFF];
    else
        return 8 + clzLookup[value & 0xFF];
}
#endif


static int BIntLog2(const BInt *in)
{
    /* Preconditions */
    assert(in != NULL);
    assert(in->size != 0);
    assert(in->data[in->size - 1] != 0);

    return (BINT_BITS - 1) - BIntClz(in->data[in->size - 1]) + BINT_BITS * (in->size - 1);
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
    BINT_TTYPE carry;
    int i;

    /* Preconditions */
    assert(a != NULL && b != NULL && out != NULL);
    assert(a->size + 1 <= BINT_SIZE);
    assert(b->size + 1 <= BINT_SIZE);

    /* Addition loop */
    carry = 0;
    for (i = 0; i < a->size || i < b->size; i++)
    {
        if (i < a->size)
            carry += a->data[i];
        if (i < b->size)
            carry += b->data[i];

        out->data[i] = carry & BINT_MASK;
        carry = (carry >> BINT_BITS);
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
    BINT_TTYPE carry;
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

        out->data[i] = carry & BINT_MASK;
        carry = carry >> BINT_BITS;
        carry |= (carry << BINT_BITS);
    }

    /* Trim leading zeros */
    out->size = a->size;
    BIntTrim(out);
}


static void BIntMul(const BInt *a,
                    const BInt *b,
                    BInt *out)
{
    BINT_TTYPE carry;
    int i, j;

    /* Preconditions */
    assert(a != NULL && b != NULL && out != NULL);
    assert(a->size + b->size <= BINT_SIZE);

    /* Zero out the result */
    memset(out->data, 0, sizeof(out->data));

    /* Multiplication loop */
    for (i = 0; i < a->size; i++)
    {
        carry = 0;
        for (j = 0; j < b->size; j++)
        {
            carry += out->data[i + j];
            carry += (BINT_TTYPE)a->data[i] * (BINT_TTYPE)b->data[j];
            out->data[i + j] = carry & BINT_MASK;
            carry = (carry >> BINT_BITS);
        }
        out->data[i + j] += carry;
    }

    /* Trim leading zeros */
    out->size = a->size + b->size;
    BIntTrim(out);
}


static void BIntMulDigit(const BInt *a,
                         BINT_TYPE b,
                         BInt *out)
{
    BINT_TTYPE carry;
    int i;

    /* Preconditions */
    assert(a != NULL && out != NULL);
    assert(a->size + 1 <= BINT_SIZE);

    /* Multiplication loop */
    carry = 0;
    for (i = 0; i < a->size; i++)
    {
        carry += (BINT_TTYPE)a->data[i] * b;
        out->data[i] = carry & BINT_MASK;
        carry = (carry >> BINT_BITS);
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
    BINT_TYPE low, high;

    /* Preconditions */
    assert(in != NULL && out != NULL);
    assert(amount >= 0 && in->size + (amount + BINT_BITS - 1) / BINT_BITS <= BINT_SIZE);

    blocks = amount / BINT_BITS;
    bits = amount % BINT_BITS;
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
            low = in->data[i - blocks - 1] >> (BINT_BITS - bits);
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
    BINT_TYPE low, high;

    /* Preconditions */
    assert(in != NULL && out != NULL);
    assert(amount >= 0);

    blocks = amount / BINT_BITS;
    bits = amount % BINT_BITS;

    /* Zero size input or shift is bigger then input */
    if (in->size == 0 || in->size <= blocks)
    {
        out->size = 0;
        return;
    }

    /* Shift and copy parts of two blocks */
    if (bits)
    {
        low = in->data[blocks] >> bits;
        high = 0;
        for (i = 0; i < in->size - blocks - 1; i++)
        {
            high = in->data[i + blocks + 1] << (BINT_BITS - bits);
            out->data[i] = low | high;
            low = in->data[i + blocks + 1] >> bits;
        }
        out->data[in->size - blocks - 1] = low;
    }
    else
    {
        for (i = 0; i < in->size - blocks; i++)
            out->data[i] = out->data[i + blocks];
    }

    /* Trim leading zeros */
    out->size = in->size - blocks;
    BIntTrim(out);
}


static BINT_TTYPE BIntGuess(const BInt *a,
                            const BInt *b)
{
    BINT_TTYPE tmp;

    /* Preconditions */
    assert(a != NULL && b != NULL);
    assert(a->size > 0 && b->size > 0);
    assert((a->size == b->size) || ((a->size != b->size) && a->size > 1));

    if (BIntCompare(a, b) < 0)
        return 0;

    tmp = a->data[a->size - 1];
    if (a->size != b->size)
        tmp = (tmp << BINT_BITS) | a->data[a->size - 2];

    return tmp / b->data[b->size - 1];
}


static void BIntDiv(const BInt *a,
                    const BInt *b,
                    BInt *q,
                    BInt *r,
                    BInt *tmp)
{
    BINT_TTYPE digit;
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
        BIntLsh(r, BINT_BITS, r);
        r->data[0] = tmp[0].data[--tmp[0].size];
        r->size += !r->size;
    }

    while (1)
    {
        /* Make a guess and check */
        digit = BIntGuess(r, &tmp[1]);
        while (digit > BINT_MASK)
            digit--;
        BIntMulDigit(&tmp[1], digit, &tmp[2]);
        while (BIntCompare(r, &tmp[2]) < 0)
        {
            --digit;
            BIntSub(&tmp[2], &tmp[1], &tmp[2]);
        }

        /* Store digit in quotient */
        BIntSub(r, &tmp[2], r);
        BIntLsh(q, BINT_BITS, q);
        q->data[0] = digit;
        q->size += !q->size;

        /* Fetch next digit or exit */
        if (!tmp[0].size)
            break;

        BIntLsh(r, BINT_BITS, r);
        r->data[0] = tmp[0].data[--tmp[0].size];
        if (!r->size)
            r->size = 1;
    }

    /* Normilize remainder */
    BIntRsh(r, shift, r);
}
