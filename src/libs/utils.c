#include "utils.h"

int comparing(void *item_a, unsigned char item_b)
{
    return (*((unsigned char *)item_a) == item_b);
}


void display_about()
{
    printf("ABOUT:\nThis is a file compression program that uses the Huffman's algorithm to perform compression/decompression of any type of file. It was developed as a conclusion work for the discipline of data structures (Estrutura de Dados/Programacao II) of the Federal University of Alagoas.\n\n");
    printf("AUTHORS:\n  * Joao Arthur (@jagra26)\n  * Kevin Washington (@kevinws_br)\n  * Roberto Jose (@betow)\n  * Sofia Lopes (@soficastro)\n");
}

void display_message(int code)
{
    switch (code)
    {
        case 1:
            printf("No file found! Please specify a valid file to be opened.\n");
            break;
        case 2:
            printf("File compressed successfully!\n");
            break;
        case 3:
            printf("File decompressed successfully!\n");
            break;
        default:
            break;
    }
}

void display_help()
{
    printf("Usage: .\\compacta-zap <options>\n\nAvailable options:\n\t-h,--help                   display this help\n\t-c,--compress [file]        compress a file passed in command line\n\t-d,--decompress [file]      decompress a file passed in command line\n\t-a,--about                  display info about the authors\n");
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

