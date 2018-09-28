
# Coletivo de Najas

THis is a file compression program that uses the **Huffman's algorithm** to perform compression/decompression of any type of file. It was developed as a conclusion work for the discipline of data structures (Estrutura de Dados/Programação II) of the Federal University of Alagoas.

## Well, what's Huffman's Algorithm?
*as seen on [Wikipedia](https://en.wikipedia.org/wiki/Huffman_coding)*:

In computer science and information theory, a Huffman code is a particular type of optimal prefix code that is commonly used for lossless data compression. The process of finding and/or using such a code proceeds by means of Huffman coding, an algorithm developed by David A. Huffman while he was a Sc.D. student at MIT, and published in the 1952 paper "A Method for the Construction of Minimum-Redundancy Codes".

The output from Huffman's algorithm can be viewed as a variable-length code table for encoding a source symbol (such as a character in a file). The algorithm derives this table from the estimated probability or frequency of occurrence (weight) for each possible value of the source symbol. As in other entropy encoding methods, more common symbols are generally represented using fewer bits than less common symbols. Huffman's method can be efficiently implemented, finding a code in time linear to the number of input weights if these weights are sorted. However, although optimal among methods encoding symbols separately, Huffman coding is not always optimal among all compression methods.

## Build
    gcc -o najas najas.c libs/utils.c libs/data_structures.c libs/compact.c libs/descompact.c
## Usage
    .\najas <options>

## Authors
* João Arthur (@jagra26)
* Kevin Washington (@kevinws_br)
* Roberto José (@betow)
* Sofia Lopes (@soficastro)
