int sign, flag = 0;
signed char sym;

/* Check for valid base and zero out read size */
result = 0;
if (actual)
    *actual = 0;
if (base != 0 && (base < 2 || base > 36))
    return 0;

/* Handle space, sign and base */
skipSpace(&string, actual);
handleSign(&string, actual, &sign);
guessBase(&string, actual, &base);

/* Read digits */
while(*string)
{
    sym = *(string++);
    sym = lookup[(unsigned int)sym];
    if (sym >= base || sym == -1)
        break;

    if (actual)
        (*actual)++;
    result = result * base + sym;
    flag = 1;
}

/* Zero out size on error */
if (!result && !flag && actual)
    *actual = 0;

return result * sign;
