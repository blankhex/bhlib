char tmp[sizeof(value) * CHAR_BIT + 1];
char *current, *end;
end = tmp + sizeof(tmp);
current = end;

/* Fill buffer from the end */
*(--current) = 0;
while (value)
{
    *(--current) = digits[value % base];
    value /= base;
}

/* Check that string have space for the result */
if (size < (size_t)(end - current))
    return BH_ERROR;

/* Copy data */
memcpy(string, current, end - current);
if (actual)
    *actual = end - current;

return BH_OK;
