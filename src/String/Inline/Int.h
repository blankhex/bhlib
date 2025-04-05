int sign, flag = 0;
signed char sym;

/* Check for valid base and zero out read size */
result = 0;
if (size)
    *size = 0;
if (base != 0 && (base < 2 || base > 36))
    return 0;

/* Handle space, sign and base */
skipSpace(&string, size);
handleSign(&string, size, &sign);
guessBase(&string, size, &base);

/* Read digits */
while(*string)
{
    sym = *(string++);
    sym = lookup[(unsigned int)sym];
    if (sym >= base || sym == -1)
        break;

    if (size)
        (*size)++;
    result = result * base + sym;
    flag = 1;
}

/* Zero out size on error */
if (!result && !flag && size)
    *size = 0;

return result * sign;
