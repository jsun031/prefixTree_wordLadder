#include "TrieNode.h"

TrieNode::TrieNode() {
	memset(next, NULL, 26 * sizeof(TrieNode*));
}

TrieNode::~TrieNode() {
	for (int i = 0; i < 26; i++) {
		if (next[i] != NULL) {
			delete(next[i]);
		}
	}
}