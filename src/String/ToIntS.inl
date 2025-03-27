char tmp[sizeof(value) * CHAR_BIT + 2];
char *current, *end;
int sign;

end = tmp + sizeof(tmp);
current = end;
sign = 0;

/* Check for sign */
if (value < 0)
{
    sign = 1;
    value = -value;
}

/* Fill buffer from the end */
*(--current) = 0;
while (value)
{
    *(--current) = digits[value % base];
    value /= base;
}

/* Append sign */
if (sign)
    *(--current) = '-';

/* Check that string have space for the result */
if (size < (size_t)(end - current))
    return BH_ERROR;

/* Copy data */
memcpy(string, current, end - current);
if (actual)
    *actual = end - current;

return BH_OK;
