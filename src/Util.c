#include <BH/Util.h>
#include <string.h>


union I16
{
    uint16_t u;
    int16_t s;
};


union I32
{
    uint32_t u;
    int32_t s;
};


union I64
{
    uint64_t u;
    int64_t s;
};


union F64
{
    double f;
    uint64_t u64;
};


int BH_ClassifyDouble(double value)
{
    union F64 tmp;
    uint64_t fract;
    int exp, negative;

    tmp.f = value;
    exp = (tmp.u64 >> 52) & 0x7FF;
    fract = (tmp.u64 & (((uint64_t)1 << 52) - 1));
    negative = (tmp.u64 >> 63) ? (BH_FP_NEGATIVE) : (0);

    if (exp == 0 && fract == 0)
        return BH_FP_ZERO | negative;

    if (exp == 2047 && fract == 0)
        return BH_FP_INFINITE | negative;

    if (exp == 2047 && fract)
        return BH_FP_NAN;

    return BH_FP_NORMAL | negative;
}


uint16_t BH_Read16LEu(const char *buffer)
{
    union I16 tmp;
    tmp.u  = (uint16_t)((unsigned char)buffer[0]);
    tmp.u |= (uint16_t)((unsigned char)buffer[1]) << 8;
    return tmp.u;
}


int16_t BH_Read16LEs(const char *buffer)
{
    union I16 tmp;
    tmp.u  = (uint16_t)((unsigned char)buffer[0]);
    tmp.u |= (uint16_t)((unsigned char)buffer[1]) << 8;
    return tmp.s;
}


uint32_t BH_Read32LEu(const char *buffer)
{
    union I32 tmp;
    tmp.u  = (uint32_t)((unsigned char)buffer[0]);
    tmp.u |= (uint32_t)((unsigned char)buffer[1]) << 8;
    tmp.u |= (uint32_t)((unsigned char)buffer[2]) << 16;
    tmp.u |= (uint32_t)((unsigned char)buffer[3]) << 24;
    return tmp.u;
}


int32_t BH_Read32LEs(const char *buffer)
{
    union I32 tmp;
    tmp.u  = (uint32_t)((unsigned char)buffer[0]);
    tmp.u |= (uint32_t)((unsigned char)buffer[1]) << 8;
    tmp.u |= (uint32_t)((unsigned char)buffer[2]) << 16;
    tmp.u |= (uint32_t)((unsigned char)buffer[3]) << 24;
    return tmp.s;
}


uint64_t BH_Read64LEu(const char *buffer)
{
    union I64 tmp;
    tmp.u  = (uint64_t)((unsigned char)buffer[0]);
    tmp.u |= (uint64_t)((unsigned char)buffer[1]) << 8;
    tmp.u |= (uint64_t)((unsigned char)buffer[2]) << 16;
    tmp.u |= (uint64_t)((unsigned char)buffer[3]) << 24;
    tmp.u |= (uint64_t)((unsigned char)buffer[4]) << 32;
    tmp.u |= (uint64_t)((unsigned char)buffer[5]) << 40;
    tmp.u |= (uint64_t)((unsigned char)buffer[6]) << 48;
    tmp.u |= (uint64_t)((unsigned char)buffer[7]) << 56;
    return tmp.u;
}


int64_t BH_Read64LEs(const char *buffer)
{
    union I64 tmp;
    tmp.u  = (uint64_t)((unsigned char)buffer[0]);
    tmp.u |= (uint64_t)((unsigned char)buffer[1]) << 8;
    tmp.u |= (uint64_t)((unsigned char)buffer[2]) << 16;
    tmp.u |= (uint64_t)((unsigned char)buffer[3]) << 24;
    tmp.u |= (uint64_t)((unsigned char)buffer[4]) << 32;
    tmp.u |= (uint64_t)((unsigned char)buffer[5]) << 40;
    tmp.u |= (uint64_t)((unsigned char)buffer[6]) << 48;
    tmp.u |= (uint64_t)((unsigned char)buffer[7]) << 56;
    return tmp.s;
}


uint16_t BH_Read16BEu(const char *buffer)
{
    union I16 tmp;
    tmp.u  = (uint16_t)((unsigned char)buffer[0]) << 8;
    tmp.u |= (uint16_t)((unsigned char)buffer[1]);
    return tmp.u;
}


int16_t BH_Read16BEs(const char *buffer)
{
    union I16 tmp;
    tmp.u  = (uint16_t)((unsigned char)buffer[0]) << 8;
    tmp.u |= (uint16_t)((unsigned char)buffer[1]);
    return tmp.s;
}


uint32_t BH_Read32BEu(const char *buffer)
{
    union I32 tmp;
    tmp.u  = (uint32_t)((unsigned char)buffer[0]) << 24;
    tmp.u |= (uint32_t)((unsigned char)buffer[1]) << 16;
    tmp.u |= (uint32_t)((unsigned char)buffer[2]) << 8;
    tmp.u |= (uint32_t)((unsigned char)buffer[3]);
    return tmp.u;
}


int32_t BH_Read32BEs(const char *buffer)
{
    union I32 tmp;
    tmp.u  = (uint32_t)((unsigned char)buffer[0]) << 24;
    tmp.u |= (uint32_t)((unsigned char)buffer[1]) << 16;
    tmp.u |= (uint32_t)((unsigned char)buffer[2]) << 8;
    tmp.u |= (uint32_t)((unsigned char)buffer[3]);
    return tmp.s;
}


uint64_t BH_Read64BEu(const char *buffer)
{
    union I64 tmp;
    tmp.u  = (uint64_t)((unsigned char)buffer[0]) << 56;
    tmp.u |= (uint64_t)((unsigned char)buffer[1]) << 48;
    tmp.u |= (uint64_t)((unsigned char)buffer[2]) << 40;
    tmp.u |= (uint64_t)((unsigned char)buffer[3]) << 32;
    tmp.u |= (uint64_t)((unsigned char)buffer[4]) << 24;
    tmp.u |= (uint64_t)((unsigned char)buffer[5]) << 16;
    tmp.u |= (uint64_t)((unsigned char)buffer[6]) << 8;
    tmp.u |= (uint64_t)((unsigned char)buffer[7]);
    return tmp.u;
}


int64_t BH_Read64BEs(const char *buffer)
{
    union I64 tmp;
    tmp.u  = (uint64_t)((unsigned char)buffer[0]) << 56;
    tmp.u |= (uint64_t)((unsigned char)buffer[1]) << 48;
    tmp.u |= (uint64_t)((unsigned char)buffer[2]) << 40;
    tmp.u |= (uint64_t)((unsigned char)buffer[3]) << 32;
    tmp.u |= (uint64_t)((unsigned char)buffer[4]) << 24;
    tmp.u |= (uint64_t)((unsigned char)buffer[5]) << 16;
    tmp.u |= (uint64_t)((unsigned char)buffer[6]) << 8;
    tmp.u |= (uint64_t)((unsigned char)buffer[7]);
    return tmp.s;
}


void BH_Write16LEu(char *buffer,
                   uint16_t value)
{
    union I16 tmp;
    tmp.u = value;

    ((unsigned char *)buffer)[0] = (tmp.u) & 0xFF;
    ((unsigned char *)buffer)[1] = (tmp.u >> 8) & 0xFF;
}


void BH_Write16LEs(char *buffer,
                   int16_t value)
{
    union I16 tmp;
    tmp.s = value;

    ((unsigned char *)buffer)[0] = (tmp.u) & 0xFF;
    ((unsigned char *)buffer)[1] = (tmp.u >> 8) & 0xFF;
}


void BH_Write32LEu(char *buffer,
                   uint32_t value)
{
    union I32 tmp;
    tmp.u = value;

    ((unsigned char *)buffer)[0] = (tmp.u) & 0xFF;
    ((unsigned char *)buffer)[1] = (tmp.u >> 8) & 0xFF;
    ((unsigned char *)buffer)[2] = (tmp.u >> 16) & 0xFF;
    ((unsigned char *)buffer)[3] = (tmp.u >> 24) & 0xFF;
}


void BH_Write32LEs(char *buffer,
                   int32_t value)
{
    union I32 tmp;
    tmp.s = value;

    ((unsigned char *)buffer)[0] = (tmp.u) & 0xFF;
    ((unsigned char *)buffer)[1] = (tmp.u >> 8) & 0xFF;
    ((unsigned char *)buffer)[2] = (tmp.u >> 16) & 0xFF;
    ((unsigned char *)buffer)[3] = (tmp.u >> 24) & 0xFF;
}


void BH_Write64LEu(char *buffer,
                   uint64_t value)
{
    union I64 tmp;
    tmp.u = value;

    ((unsigned char *)buffer)[0] = (tmp.u) & 0xFF;
    ((unsigned char *)buffer)[1] = (tmp.u >> 8) & 0xFF;
    ((unsigned char *)buffer)[2] = (tmp.u >> 16) & 0xFF;
    ((unsigned char *)buffer)[3] = (tmp.u >> 24) & 0xFF;
    ((unsigned char *)buffer)[4] = (tmp.u >> 32) & 0xFF;
    ((unsigned char *)buffer)[5] = (tmp.u >> 40) & 0xFF;
    ((unsigned char *)buffer)[6] = (tmp.u >> 48) & 0xFF;
    ((unsigned char *)buffer)[7] = (tmp.u >> 56) & 0xFF;
}


void BH_Write64LEs(char *buffer,
                   int64_t value)
{
    union I64 tmp;
    tmp.s = value;

    ((unsigned char *)buffer)[0] = (tmp.u) & 0xFF;
    ((unsigned char *)buffer)[1] = (tmp.u >> 8) & 0xFF;
    ((unsigned char *)buffer)[2] = (tmp.u >> 16) & 0xFF;
    ((unsigned char *)buffer)[3] = (tmp.u >> 24) & 0xFF;
    ((unsigned char *)buffer)[4] = (tmp.u >> 32) & 0xFF;
    ((unsigned char *)buffer)[5] = (tmp.u >> 40) & 0xFF;
    ((unsigned char *)buffer)[6] = (tmp.u >> 48) & 0xFF;
    ((unsigned char *)buffer)[7] = (tmp.u >> 56) & 0xFF;
}


void BH_Write16BEu(char *buffer,
                   uint16_t value)
{
    union I16 tmp;
    tmp.u = value;

    ((unsigned char *)buffer)[0] = (tmp.u >> 8) & 0xFF;
    ((unsigned char *)buffer)[1] = (tmp.u) & 0xFF;
}


void BH_Write16BEs(char *buffer,
                   int16_t value)
{
    union I16 tmp;
    tmp.s = value;

    ((unsigned char *)buffer)[0] = (tmp.u >> 8) & 0xFF;
    ((unsigned char *)buffer)[1] = (tmp.u) & 0xFF;
}


void BH_Write32BEu(char *buffer,
                   uint32_t value)
{
    union I32 tmp;
    tmp.u = value;

    ((unsigned char *)buffer)[0] = (tmp.u >> 24) & 0xFF;
    ((unsigned char *)buffer)[1] = (tmp.u >> 16) & 0xFF;
    ((unsigned char *)buffer)[2] = (tmp.u >> 8) & 0xFF;
    ((unsigned char *)buffer)[3] = (tmp.u) & 0xFF;
}


void BH_Write32BEs(char *buffer,
                   int32_t value)
{
    union I32 tmp;
    tmp.s = value;

    ((unsigned char *)buffer)[0] = (tmp.u >> 24) & 0xFF;
    ((unsigned char *)buffer)[1] = (tmp.u >> 16) & 0xFF;
    ((unsigned char *)buffer)[2] = (tmp.u >> 8) & 0xFF;
    ((unsigned char *)buffer)[3] = (tmp.u) & 0xFF;
}


void BH_Write64BEu(char *buffer,
                   uint64_t value)
{
    union I64 tmp;
    tmp.u = value;

    ((unsigned char *)buffer)[0] = (tmp.u >> 56) & 0xFF;
    ((unsigned char *)buffer)[1] = (tmp.u >> 48) & 0xFF;
    ((unsigned char *)buffer)[2] = (tmp.u >> 40) & 0xFF;
    ((unsigned char *)buffer)[3] = (tmp.u >> 32) & 0xFF;
    ((unsigned char *)buffer)[4] = (tmp.u >> 24) & 0xFF;
    ((unsigned char *)buffer)[5] = (tmp.u >> 16) & 0xFF;
    ((unsigned char *)buffer)[6] = (tmp.u >> 8) & 0xFF;
    ((unsigned char *)buffer)[7] = (tmp.u) & 0xFF;
}


void BH_Write64BEs(char *buffer,
                   int64_t value)
{
    union I64 tmp;
    tmp.s = value;

    ((unsigned char *)buffer)[0] = (tmp.u >> 56) & 0xFF;
    ((unsigned char *)buffer)[1] = (tmp.u >> 48) & 0xFF;
    ((unsigned char *)buffer)[2] = (tmp.u >> 40) & 0xFF;
    ((unsigned char *)buffer)[3] = (tmp.u >> 32) & 0xFF;
    ((unsigned char *)buffer)[4] = (tmp.u >> 24) & 0xFF;
    ((unsigned char *)buffer)[5] = (tmp.u >> 16) & 0xFF;
    ((unsigned char *)buffer)[6] = (tmp.u >> 8) & 0xFF;
    ((unsigned char *)buffer)[7] = (tmp.u) & 0xFF;
}
