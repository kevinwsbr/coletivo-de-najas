#include "descompact.h"

int descompact(FILE *compacted_file, char filename[])
{
    int file_size = 0;
    short trash_s, tree_s = 8191;

    char output_name[50];
    unsigned char firstbyte, secondbyte;

    node *root = NULL;
    FILE *descompacted_file;


    printf("Insert output file name: ");
    scanf("%[^\n]s", output_name);

    compacted_file = fopen(filename, "rb");
    descompacted_file = fopen(output_name, "wb");

    fseek(compacted_file, 0, SEEK_END);

    file_size = ftell(compacted_file);

    rewind(compacted_file);
    
    printf("Decompressing ...\n");
    
    firstbyte = fgetc(compacted_file);
    secondbyte = fgetc(compacted_file);
    trash_s = firstbyte >> 5;
    tree_s = ((firstbyte << 8) | secondbyte) & tree_s;

    root = create_tree_read(compacted_file);

    fseek(compacted_file, tree_s + 2, SEEK_SET);
    print_byte(compacted_file, descompacted_file, tree_s, trash_s, root, file_size);

    fclose(compacted_file);
    fclose(descompacted_file);

    return 0;
}

node *create_tree_read(FILE *compacted_file)
{
    unsigned char current;
    node *new_node;

    current = fgetc(compacted_file);

    if (current == '*')
    {
        new_node = create_node(current);
        new_node->left = create_tree_read(compacted_file);
        new_node->right = create_tree_read(compacted_file);
    }
    else if (current == (char)SLASH)
    {
        current = fgetc(compacted_file);
        new_node = create_node(current);
    }
    else
    {
        new_node = create_node(current);
    }
    return new_node;
}

node *create_node(unsigned char character)
{
    unsigned char *aux = (unsigned char *)malloc(sizeof(unsigned char));
    
    *aux = character;
    node *new_node = (node *)malloc(sizeof(node));
    new_node->item = aux;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->next = NULL;
    new_node->frequency = 0;

    return new_node;
}

void print_byte(FILE* compacted_file, FILE* descompacted_file, short tree_s, short trash_s, node* root, int file_size)
{
    long i, j;
    unsigned char c;
    node *current = root;
    
    for (j = tree_s + 2; j < file_size; j++)
    {
        c = fgetc(compacted_file);
        
        if (j == file_size - 1)
        {
            for (i = 0; i < 8 - trash_s; i++)
            {
                if (is_bit_i_set(c, 7 - i))
                {
                    current = current->right;
                }
                else
                {
                    current = current->left;
                }

                if (current->left == NULL && current->right == NULL)
                {
                    fprintf(descompacted_file, "%c", *(unsigned char*)current->item);
                    current = root;
                }
            }
        }
        else
        {
            for (i = 0; i < 8; i++)
            {
                if (is_bit_i_set(c, 7 - i))
                {
                    current = current->right;
                }
                else
                {
                    current = current->left;
                }

                if (current->left == NULL && current->right == NULL)
                {
                    fprintf(descompacted_file, "%c", *(unsigned char*)current->item);
                    current = root;
                }
            }
        }
    }
}
