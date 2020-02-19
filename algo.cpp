#include <string>
#include <unordered_map>

#include "algo.h"

using namespace std;

vector<int> compressLZW(const vector<unsigned char>& content) {
  string input(content.begin(), content.end());
  unordered_map<string, int> table;
  for (int i = 0; i < 256; i++) {
    string character = "";
    character += char(i);
    table[character] = i;
  }
  string P = "";
  string C = "";
  P += input[0];
  int code = 256;
  vector<int> output_code;
  for (int i = 0; i < input.length(); i++) {
    if (i != input.length() - 1) {
      C += input[i + 1];
    }
    if (table.find(P + C) != table.end()) {
      P = P + C;
    } else {
      output_code.push_back(table[P]);
      table[P + C] = code;
      code++;
      P = C;
    }
    C = "";
  }
  output_code.push_back(table[P]);
  return output_code;
}

vector<unsigned char> decompressLZW(const vector<int>& content) {
  string output_string;
  unordered_map<int, string> table;
  for (int i = 0; i < 256; i++) {
    string character = "";
    character += char(i);
    table[i] = character;
  }
  int n;
  int old = content[0];
  string S = table[old];
  string C = "";
  output_string.append(S);
  int count = 256;
  for (int i = 0; i < content.size() - 1; i++) {
    n = content[i + 1];
    if (table.find(n) == table.end()) {
      S = table[old];
      S += C;
    } else {
      S = table[n];
    }
    output_string.append(S);
    C = "";
    C += S[0];
    table[count] = table[old] + C;
    count++;
    old = n;
  }
  vector<unsigned char> result;
  result.insert(result.begin(), output_string.begin(), output_string.end());
  return result;
}
