#include <stdio.h>
#include <string.h>
#include "libs/compact.h"
#include "libs/descompact.h"

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

int main(int argc, char *argv[])
{
    FILE *ptr;
    int flag;
    if (argc > 1)
    {
        if (!strncmp(argv[1], "--compress", 10) || !strncmp(argv[1], "-c", 2))
        {
            if(argv[2] == NULL)
            {
                display_message(1);
            }
            else
            {
                printf("File for compress: %s\n", argv[2]);
                if (!compact(ptr, argv[2]))
                     display_message(2);
            }
            
        }
        else if (!strncmp(argv[1], "--decompress", 12) || !strncmp(argv[1], "-d", 2))
        {
            if (argv[2] == NULL)
            {
                display_message(1);
            }
            else
            {
                printf("File for decompress: %s\n", argv[2]);
                if(!descompact(ptr, argv[2]))
                    display_message(3);
            }
        }
        else if (!strncmp(argv[1], "--help", 6) || !strncmp(argv[1], "-h", 2))
        {
            display_help();
        }
        else if (!strncmp(argv[1], "--about", 6) || !strncmp(argv[1], "-a", 2))
        {
            display_about();
        }
        else{
            printf("Invalid option\nTry -h or --help!");
        }
    }  
    else
    {
        display_message(1);
        display_about();
        display_help();
    }
        
    return 0;
}
