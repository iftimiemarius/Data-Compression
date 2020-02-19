#include <string>
#include <unordered_map>
#include <queue>

#include "algo.h"

using namespace std;

void freeTree(TreeNode *root) {
  if (root == NULL) {
    return;
  }
  freeTree(root->leftNode);
  freeTree(root->rightNode);
  free(root);
}

TreeNode* createNode(char character, int frequency,
                     TreeNode *leftNode, TreeNode *rightNode) {
  TreeNode *newNode = (TreeNode*) malloc (sizeof(TreeNode));
  newNode->character = character;
  newNode->frequency = frequency;
  newNode->leftNode = leftNode;
  newNode->rightNode = rightNode;
  return newNode;
}

void encodeHuffman(TreeNode *root, string codes,
        unordered_map<char, string> &huffmanCodes) {
  if (root == NULL) {
    return;
  }
  if (!(root->leftNode || root->rightNode)) {
    huffmanCodes[root->character] = codes;
  }
  encodeHuffman(root->leftNode, codes + "0", huffmanCodes);
  encodeHuffman(root->rightNode, codes + "1", huffmanCodes);
}

void decodeHuffman(TreeNode *root, int &index, vector<unsigned char> codes,
                   vector<unsigned char> &output) {
  if (root == NULL) {
    return;
  }
  if (!(root->leftNode || root->rightNode)) {
    output.push_back(root->character);
  } else {
    index++;
    if (codes[index] == '0') {
      decodeHuffman(root->leftNode, index, codes, output);
    } else {
      decodeHuffman(root->rightNode, index, codes, output);
    }
  }
}

TreeNode* buildHuffmanTree(vector<unsigned char> text) {
  unordered_map<char, int> frequencies;
  for (char letter : text) {
    frequencies[letter]++;
  }
  auto compare = [] (TreeNode *leftNode, TreeNode *rightNode) {
    return (leftNode->frequency > rightNode->frequency);
  };
  priority_queue<TreeNode*, vector<TreeNode*>, decltype(compare)> pqueue(compare);
  for (auto pair : frequencies) {
    pqueue.push(createNode(pair.first, pair.second, NULL, NULL));
  }
  while (pqueue.size() != 1) {
    TreeNode *leftNode = pqueue.top();
    pqueue.pop();
    TreeNode *rightNode = pqueue.top();
    pqueue.pop();
    int sum = leftNode->frequency + rightNode->frequency;
    pqueue.push(createNode('\0', sum, leftNode, rightNode));
  }
  TreeNode *root = pqueue.top();
  return root;
}

vector<unsigned char> compressHuffman(const vector<unsigned char>& content,
                                      TreeNode **root) {
  *root = buildHuffmanTree(content);
  unordered_map<char, string> huffmanCodes;
  encodeHuffman(*root, "", huffmanCodes);
  vector<unsigned char> result;
  for (char character : content) {
    result.insert(result.end(), huffmanCodes[character].begin(),
                  huffmanCodes[character].end());
  }
  return result;
}

vector<unsigned char> decompressHuffman(const vector<unsigned char>& content,
                                        TreeNode *root) {
  int index = -1;
  vector<unsigned char> result;
  while (index < (int) content.size() - 1) {
    decodeHuffman(root, index, content, result);
  }
  return result;
}
