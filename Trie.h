#include "TrieNode.h"

//Trie is a better substitue for map<string, *>, hashtable<string>.
//It applies to alphabetal order.
//Even when the order has no influence, Trie is better than vector<string>, stack<strign>, or queue<string>.
class Trie {
	TrieNode* root;
	int length = 0;	
	//construct all the neighbors of s in the trie except the origin string with character avoid
	void dfs(const string& s, int position, string& cur, TrieNode* tmp, vector<string>& ans, char avoid) const;
	//give a string with 1 '.' find all the string that matches it in trie except the original one
	bool findAllWord(const string& s, vector<string>& ans, char avoid) const;
public:
	Trie();
	~Trie();

	// --- constant methods ---
	int size() const;
	bool empty() const;
	//return the first word alphabetally
	string front() const;
	//If a string exists in trie, return the path of TrieNode; else return an empty path
	vector<TrieNode*> findWord(const string& s) const;
	//give a string find all the string that differs from it only 1 character in trie
	vector<string> findNeighbor(string& s) const;
	//given a string return the word it maps to
	vector<string> mapWord(const string& s) const;

	// --- Modifers ---
	//insert a word in trie
	void addWord(const string& word);
	//delete a word in trie
	void removeWord(const string& s);
	//add a neighbor word to s for string map
	void markNeighbor(const string& s, const vector<string>& words);
};