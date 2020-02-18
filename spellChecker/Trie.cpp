#include <iostream>
#include <string>
#include <map>
#include "Trie.h"

// constructor
Trie::Trie() {
	try {
		root = new TrieNode();
	}
	catch (std::bad_alloc &ba) {
		std::cerr << ba.what() << std::endl;
		exit(0);
	}
}

// copy constructor
Trie::Trie(const Trie&) {

}

// helper function to recursively delete all children
void deleteAllChildren(TrieNode *node) {
	if (node != 0) {
		// if the node has no children, delete the node
		if (node->children == 0) {
			delete(node);
			return;
		}
		// for each child of the node, call deleteAllChildren
		for (TrieNode* child : node->children) { //??
			deleteAllChildren(child);
		}
	}
}

// destructor
Trie::~Trie() {
	TrieNode *current = root;
	deleteAllChildren(root);

}

// insert method
void Trie::insert(std::string word) {
	TrieNode *current = root;
	
	for (int i = 0; i < (int) word.size(); ++i) {
		if (current->children[word[i] - 'a'] == 0) {
			// there is no node in the trie corresponding to the letter of word so allocate a new TrieNode
			try {
				current->children[word[i] - 'a'] = new TrieNode();
			}
			catch (std::bad_alloc &ba) {
				std::cerr << ba.what() << std::endl;
				exit(0);
			}
		}
		// move to next node
		current = current->children[word[i] - 'a'];
	}
	// mark the last node visited as the end of the word
	current->isWord = true;

}

// search function
bool Trie::search(std::string word) {
	if (isEmpty()) {
		return false;
	}
	TrieNode *current = root;
	
	for (int i = 0; i < (int)word.size(); ++i) {
		if (current->children[word[i] - 'a'] != 0) {
			// go to next node
			current = current->children[word[i] - 'a'];
		}
		else {
			return false;
		}
	}
	return true;
}

// remove function
void Trie::remove(std::string) {

}
