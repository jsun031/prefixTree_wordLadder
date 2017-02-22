#include "Trie.h"

// --- private ---
//construct all the neighbors of s in the trie except the origin string with character avoid
void Trie::dfs(const string& s, int position, string& cur, TrieNode* tmp, vector<string>& ans, char avoid) const {
	if (position == s.size()) {
		ans.push_back(cur);
		return;
	}
	if (s.at(position) != '.') {
		if (tmp->next[s.at(position) - 'a'] != NULL) {
			cur += s.at(position);
			dfs(s, position + 1, cur, tmp->next[s.at(position) - 'a'], ans, avoid);
			cur.pop_back();
		}
	} else {
		for (int i = 0; i < 26; i++) {
			if (i != avoid - 'a' && tmp->next[i] != NULL) {
				cur += 'a' + i;
				dfs(s, position + 1, cur, tmp->next[i], ans, avoid);
				cur.pop_back();
			}
		}
	}
}
//give a string with 1 '.' find all the string that matches it in trie except the original one
bool Trie::findAllWord(const string& s, vector<string>& ans, char avoid) const {
	string cur;
	TrieNode* tmp = root;
	dfs(s, 0, cur, tmp, ans, avoid);
	if (ans.empty()) {
		return false;
	} else {
		return true;
	}
}

// --- public ---
Trie::Trie() {
	root = new TrieNode();
}
Trie::~Trie() {
	if (root != NULL) {
		delete root;
	}
}

// --- constant methods ---
int Trie::size() const {
	return length;
}
bool Trie::empty() const {
	return length == 0;
}
//return the first word alphabetally
string Trie::front() const {
	TrieNode* tmp = root;
	bool goOn = true;
	string ans;
	while (goOn) {
		goOn = false;
		for (int i = 0; i < 26; i++) {
			if (tmp->next[i] != NULL) {
				ans += 'a' + i;
				tmp = tmp->next[i];
				goOn = true;
				break;
			}
		}
	}
	return ans;
}
//If a string exists in trie, return the path of TrieNode; else return an empty path
vector<TrieNode*> Trie::findWord(const string& s) const {
	vector<TrieNode*> ans;
	TrieNode* cur = root;
	ans.push_back(cur);
	bool exist = true;
	for (int i = 0; i < s.size(); i++) {
		if (cur->next[s.at(i) - 'a'] == NULL) {
			exist = false;
			break;
		} else {
			cur = cur->next[s.at(i) - 'a'];
			ans.push_back(cur);
		}
	}
	return exist && cur->end ? ans : vector<TrieNode*>();
}
//give a string find all the string that differs from it only 1 character in trie
vector<string> Trie::findNeighbor(string& s) const {
	vector<string> ans;
	for (int i = 0; i < s.size(); i++) {
		char a = s.at(i);
		s[i] = '.';
		findAllWord(s, ans, a);
		s[i] = a;
	}
	return ans;
}
//given a string return the word it maps to
vector<string> Trie::mapWord(const string& s) const {
	TrieNode* tmp = root;
	for (int i = 0; i < s.size(); i++) {
		tmp = tmp->next[s[i] - 'a'];
	}
	string t = s;
	vector<string> ans;
	for (int i = 0; i < tmp->mapWord.size(); i++) {
		t[tmp->mapWord[i].first] = tmp->mapWord[i].second;
		ans.push_back(t);
		t[tmp->mapWord[i].first] = s[tmp->mapWord[i].first];
	}
	return ans;
}

// --- Modifers ---
//insert a word in trie
void Trie::addWord(const string& word) {
	TrieNode* cur = root;
	bool newone = false;
	for (int i = 0; i < word.size(); i++) {
		if (cur->next[word[i] - 'a'] == NULL) {
			cur->next[word[i] - 'a'] = new TrieNode();
			newone = true;
		}
		cur = cur->next[word[i] - 'a'];
	}
	if (newone) {
		length++;
	}
	cur->end = true;
}
//delete a word in trie
void Trie::removeWord(const string& s) {
	vector<TrieNode*> path = findWord(s);
	if (path.empty()) {
		return;
	} else {
		length--;
		int last = 0;
		path.back()->end = false;
		for (int j = 0; j < 26; j++) {
			if (path.back()->next[j] != NULL) {
				last++;
				break;
			}
		}
		for (int i = path.size() - 1; i > 0 && last == 0 && path.at(i)->end == false; i--) {
			if (last == 0) {
				delete(path.at(i));
				path.at(i - 1)->next[s.at(i - 1) - 'a'] = NULL;
			}
			int counter = 0;
			for (int j = 0; j < 26; j++) {
				if (path.at(i - 1)->next[j] != NULL) {
					counter++;
					break;
				}
			}
			last = counter;
		}
	}
}
//add a neighbor word to s for string map
void Trie::markNeighbor(const string& s, const vector<string>& words) {
	for (int i = 0; i < words.size(); i++) {
		int j = 0;
		while (j < s.size() && words.at(i).at(j) == s.at(j)) {
			j++;
		}
		pair<int, char> possibleNeighbor = make_pair(j, s.at(j));
		vector<TrieNode*> wordPath = findWord(words.at(i));
		wordPath.back()->mapWord.push_back(possibleNeighbor);
	}
}
