#ifndef DESCOMPACT_H
#define DESCOMPACT_H

#include "data_structures.h"
#include "utils.h"

/*
 * Receives an file pointer to the compressed file and the compressed file's name. This funtions calls all
 * functions necessary to decompress.
 * Returns a logical value informing whether or not the decompression worked.
 */
int descompact(FILE *compact_file, char filename[]);

/*
 * Receives an file pointer to the compressed file. This funtion reads the file's header and generates the Huffman tree
 * Returns the Huffman tree.
 */
node *create_tree_read(FILE *compact_file);

/*
 * Receives an unsigned char which represents the byte that is going into the Huffman tree.
 * Returns a node.
 */
node *create_node(unsigned char character);

/*
 * Receives an file pointer to the output file and another to the compressed file, the Huffman tree, and the sizes of the tree, trash and compressed file.
 * No return. This function prints the decompressed bytes into the output file according to the Huffman tree.
 */
void print_byte(FILE *compact_file, FILE *descompact_file, short tree_s, short trash_s, node *root, int file_size);

#endif
