#include "compact.h"

FILE *compact(FILE *original_file, char filename[])
{
    //integers
    int *frequency, count = 0;
    short final, trash, tree;

    //chars
    char compacted_byte[256];
    unsigned char current_byte, compact = 0;

    //data structures
    node *root = NULL;
    queue *queue = create_queue();
    hash_table *hash = create_hash_table();
    
    //file pointers
    FILE *compacted_file;
    
    original_file = fopen(filename, "rb");
    frequency = save_frequency(original_file);

    rewind(original_file);

    printf("Compressing ...\n");

    frequency_enqueue(frequency, queue);
    root = merge_nodes(queue);
    generate_huffman_tree(root, 0, hash, compacted_byte);
    
    filename = strtok(filename, ".");
    filename = strcat(filename, ".zap");

    compacted_file = fopen(filename, "wb");

    trash = trash_size(hash, frequency);
    tree = tree_size(root);

    trash = trash << 13;

    final = trash | tree;

    //writing first byte
    current_byte = final >> 8;
    fprintf(compacted_file, "%c", current_byte);
    //writing second byte
    current_byte = final;
    fprintf(compacted_file, "%c", current_byte);

    fprint_tree(root, compacted_file);
    fseek(compacted_file, 2+tree, SEEK_SET);

    while (!feof(original_file))
    {
        current_byte = fgetc(original_file);

        int i;
        for (i = 0; i < hash->table[(int)current_byte]->n; ++i)
        {
            if (hash->table[(int)current_byte]->str[i] == '1')
                compact = set_bit(compact, 7 - count);

            count++;
            if (count == 8)
            {
                fprintf(compacted_file, "%c", compact);
                compact = 0;
                count = 0;
            }
        }
    }
    

    fclose(original_file);
    fclose(compacted_file);
    
    return compacted_file;
}

int generate_huffman_tree(node *root, int count, hash_table *ht, char string[])
{
    if (root->left == NULL && root->right == NULL)
    {
        add_hash(ht, root->item, string, count);
    }
    else
    {
        string[count] = '0';
        generate_huffman_tree(root->left, count + 1, ht, string);
        string[count] = '1';
        generate_huffman_tree(root->right, count + 1, ht, string);
    }
}
int *save_frequency(FILE *file)
{
    int *frequency = (int *)calloc(256, sizeof(int));
    unsigned char c;
    
    while(!feof(file))
    {
        c = fgetc(file);
        frequency[(int)c]++;
    }

    return frequency;
}

int trash_size(hash_table *hash, int *frequency)
{
    int i = 0, sum = 0;

    while (i < 256)
    {
        if (frequency[i] != 0)
            sum += (hash->table[i]->n) * frequency[i];
        i++;
    }
    return 8 - (sum % 8);
}
