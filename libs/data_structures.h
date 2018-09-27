#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#define SLASH 92

#include "utils.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node node;
typedef struct queue queue;
typedef struct element element;
typedef struct hash_table hash_table;

struct node
{
    int frequency;
    void *item;
    node *left;
    node *right;
    node *next;
};

struct queue
{
    node *head;
};

struct element
{
    char str[50];
    int n;
};
struct hash_table
{
    element *table[256];
};

/*
 * Creates and returns an empty queue
 */
queue *create_queue();

/*
 * Receives a queue.
 * Returns a logical value informing whether the queue is empty
 */
int is_empty(queue *queue);
/*
 * Receives the root of a tree.
 * No return, prints the tree inorder.
 */
void print_tree(node *root);

/*
 * Creates and returns an empty hash table
 */
hash_table *create_hash_table();

/*
 * Creates and returns an empty hash table's element 
 */
element *create_element();

/*
 * Receives a queue, a void pointer, and the frequency of the byte we're enqueueing.
 * No return, modifications are made directly into the queue.
 */
void enqueue(queue *pq, void *i, int p);

/*
 * Receives a node and a queue.
 * No return, modifications are made directly into the queue.
 */
void enqueue_node(node *new_node, queue *pq);

/*
 * Receives a queue. Removes its first node.
 * Returns removed node.
 */
node *dequeue(queue *pq);

/*
 * Receives a queue. Turns the queue into a Huffman tree.
 * Returns the Huffman tree.
 */
node *merge_nodes(queue *queue);

/*
 * Receives a hash table, a void pointer, the Huffman code, and the huffman code's number
 * of bits. Adds a new element to the hash, with its Huffman code.
 * No return, modifications are made directly into the hash table.
 */
void add_hash(hash_table *ht, void *character, char bit[], int n);

/*
 * Receives the frequencies and a queue. Creates the priority queue based in frequency.
 * No return.
 */
void frequency_enqueue(int *frequency, queue *queue);

/*
 * Receives the root of a tree.
 * Returns its size.
 */
int tree_size(node *root);

/*
 * Receives a Huffman tree and a file pointer which points to the compressed file.
 * No return, modifications are made directly into the compressed file.
 */
void fprint_tree(node *root, FILE *compact_file);

void print_q(queue *queue); //função que imprime fila
void print_hash(hash_table *ht); //printa a hash, ou seja, os elementos e suas respectivas frequências
#endif
