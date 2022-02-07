char *mx_strncpy(char *dst, const char *src, int len)
{
    char *s = dst;
    int index = 0;
    while (*src && (index < len))
    {
        *dst = *src;
        index++;
        dst++;
        src++;
    }
    *dst = '\0';
    return &s[0];
}
