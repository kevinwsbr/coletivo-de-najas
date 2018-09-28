#include <stdio.h>
#include <string.h>
#include "libs/compact.h"
#include "libs/descompact.h"

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
