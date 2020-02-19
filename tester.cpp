#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

#include "algo.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 5) {
    cout<<"Use the format written in README"<<endl;
    return -1;
  }
  ifstream input_file(argv[1]);
  string input_string;
  string current_row;
  while (!input_file.eof()) {
    getline(input_file, current_row);
    input_string.append(current_row);
    input_string.append("\n");
  }
  input_file.close();
  input_string.pop_back();
  vector<unsigned char> input_content;
  input_content.insert(input_content.begin(),
                       input_string.begin(), input_string.end());
  if (string(argv[4]).compare("huffman") == 0) {
    TreeNode *root;
    auto t1 = std::chrono::high_resolution_clock::now();
    vector<unsigned char> output = compressHuffman(input_content, &root);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout<<"Huffman compression time: "<<duration1<<endl;
    string output_string(output.begin(), output.end());
    ofstream output_file(argv[2]);
    output_file<<output_string;
    output_file.close();
    auto t3 = std::chrono::high_resolution_clock::now();
    vector<unsigned char> output_decompressed = decompressHuffman(output, root);
    auto t4 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>( t4 - t3 ).count();
    cout<<"Huffman decompression time: "<<duration2<<endl;
    string output_string_decompressed(output_decompressed.begin(),
                                      output_decompressed.end());
    ofstream output_decompressed_file(argv[3]);
    output_decompressed_file<<output_string_decompressed;
    output_decompressed_file.close();
    freeTree(root);
  } else if (string(argv[4]).compare("lzw") == 0) {
    auto t1 = std::chrono::high_resolution_clock::now();
    vector<int> codes = compressLZW(input_content);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout<<"LZW compression time: "<<duration1<<endl;
    ofstream output_file(argv[2]);
    for (unsigned int i = 0; i < codes.size(); i++) {
      output_file<<codes[i]<<" ";
    }
    output_file.close();
    auto t3 = std::chrono::high_resolution_clock::now();
    vector<unsigned char> decompressed_string = decompressLZW(codes);
    auto t4 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>( t4 - t3 ).count();
    cout<<"LZW decompression time: "<<duration2<<endl;
    string output_string_decompressed(decompressed_string.begin(),
                                      decompressed_string.end());
    ofstream output_decompressed_file(argv[3]);
    output_decompressed_file<<output_string_decompressed;
    output_decompressed_file.close();
  }
  return 0;
}
