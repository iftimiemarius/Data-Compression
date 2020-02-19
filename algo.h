#ifndef ALGO_H
#define ALGO_H

#include <vector>

struct TreeNode {
    char character;
    int frequency;
    TreeNode *leftNode;
    TreeNode *rightNode;
};

void freeTree(TreeNode *root);

/**
 * Compresses the data it receives using the LZW compression.
 *
 * @content: The original content of a file in bytes
 * @returns: The content of the compressed file
 */
std::vector<int> compressLZW(const std::vector<unsigned char>& content);

/**
 * Decompresses the data it receives using the LZW compression.
 *
 * @content: The compressed file in bytes
 * @returns: The content of the original file
 */
std::vector<unsigned char> decompressLZW(const std::vector<int>& content);


/**
 * Compresses the data it receives using the Huffman Coding.
 *
 * @content: The original content of a file in bytes
 * @root: Used to save the Huffman Tree
 * @returns: The content of the compressed file
 */
std::vector<unsigned char> compressHuffman(const std::vector<unsigned char>& content,
                                           TreeNode **root);

/**
 * Decompresses the data it receives using the Huffman Coding.
 *
 * @content: The compressed file in bytes
 * @root: Used to decompress using the Huffman Tree
 * @returns: The content of the original file
 */
std::vector<unsigned char> decompressHuffman(const std::vector<unsigned char>& content,
                                             TreeNode *root);


#endif
