Trie is a better substitue for map<string, *>, hashtable<string>, which saves space and runs faster. It is stored alphabetal order, but amazingly, even when the order has no influence, Trie is still better than vector<string>, stack<strign>, or queue<string>.

class Trie has 2 private fields. root is the entrance and length indicate the word number that trie stores.

For public methods:

1. Constant methods:

size(), empty() is used to get trie status. 
front() returns the first word alphabetally. 
findWord() return the path of TrieNode if a string exists in trie; otherwise returns an empty path.
mapWord(string s) is designed to return the strings in trie that s maps to.

2. Modifers:
addWord() and removeWord() is easily to understood.
markNeighbor() is used to input the string map.

class Solution is the answer to leetcode 126. It uses a bfs to get the shortest path. In order to save search time, the small one between next and nextEnd is chosen for next iteration. The answer is 100 ms and very fast. In fact, if we remove all the delete and leaves the memory recycle to the system, it only takes 46 ms. It seems a trict, but it is a bad idea due to memory leak.
