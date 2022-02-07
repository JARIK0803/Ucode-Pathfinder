#include "../inc/libmx.h"

int mx_digit_count(int number)
{
    int counter = 0;

    do
    {
        number /= 10;
        ++counter;
    } while (number != 0);

    return counter;
}

void reverse(char *str)
{
    char tmp;
    for (int i = 0, j = mx_strlen(str) - 1; i < j; i++, j--)
    {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}

char *mx_itoa(int number)
{
    char *result = mx_strnew(mx_digit_count(number));
    int sign;
    
    if ((sign = number) < 0)
    {
        number = -number;
    }

    int i = 0;
    do {
        result[i++] = number % 10 + 48; 
    
    } while ((number /= 10) > 0);
    
    if (sign < 0)
    {
        result[i++] = '-';
    }
    
    result[i] = '\0';

    reverse(result);
    
    return result;
}
