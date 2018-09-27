#include "utils.h"

int comparing(void *item_a, unsigned char item_b)
{
    return (*((unsigned char *)item_a) == item_b);
}

int is_bit_i_set(unsigned char c, int i) //imprime os bits do respectivo char
{
    unsigned char mask = 1 << i;
    return mask & c;
}
unsigned char set_bit(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask | c;
}
void print_un_char(unsigned char c) //imprime um character
{
    int i;
    for (i = 0; i < 8; i++)
    {
        if (is_bit_i_set(c, 7 - i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\n");
}
void print_freq_list(int freq[])
{
    int i;
    for (i = 0; i < 256; i++)
    {
        if (freq[i] != 0)
        {
            printf("(%d) %c -> [%d]\n", i, (char)i, freq[i]);
        }
    }
}

