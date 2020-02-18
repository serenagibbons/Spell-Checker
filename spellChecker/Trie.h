#ifndef TRIE_H
#define TRIE_H

const int ALPHABET = 26;

struct TrieNode {
	TrieNode *children[ALPHABET];
	bool isWord;
};

class Trie {
private:
	TrieNode *root;
	
public:
	Trie();	// constructor
	Trie(const Trie&); // copy constructor
	~Trie();	// destructor
	inline bool const isEmpty() { return root == 0; }
	void insert(std::string);
	void remove(std::string);
	TrieNode* search(std::string);

};

#endif // !TRIE_H
