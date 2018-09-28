#ifndef UTILS_H
#define UTILS_H

#include<stdio.h>

int comparing(void *item_a, unsigned char item_b);
int is_bit_i_set(unsigned char c, int i); //imprime os bits do respectivo char
unsigned char set_bit(unsigned char c, int i);
void print_un_char(unsigned char c); //imprime um character
void print_freq_list(int freq[]);
void display_about();
void display_message(int code);
void display_help();

#endif
