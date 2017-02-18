#include <iostream>
#include <string>
#include <vector>
using namespace std;
//a node for Trie
struct TrieNode {
	TrieNode* next[26];
	bool end = false;
	vector<pair<int, char>> mapWord;
	TrieNode();
	~TrieNode();
};