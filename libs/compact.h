#ifndef COMPACT_H
#define COMPACT_H

#include "data_structures.h"
#include "utils.h"

/*
 * Receives an empty file pointer and the original file's name. This funtions calls all
 * functions necessary to compress.
 * Returns a logical value informing whether or not the compression worked.
 */
FILE *compact(FILE *original_file, char filename[]);

/*
 * Receives a file pointer which points to the original file.
 * Returns an int pointer with the frequencies which the bytes appears on the original file.
 */
int *save_frequency(FILE *file);

/*
 * Receives a Huffman tree, a int counter, a hash table, and a string for the Huffman code.
 */
int generate_huffman_tree(node *root, int count, hash_table *ht, char string[]);

/*
 * Receives an int pointer with the frequencies and a queue.
 * No return, modifications are made directly into the queue.
 */
//void frequency_enqueue(int *frequency, queue *queue);

/*
 * Receives a hash table and an int pointer with the frequencies.
 * Returns the size of the trash.
 */
int trash_size(hash_table *hash, int *frequency);

#endif
