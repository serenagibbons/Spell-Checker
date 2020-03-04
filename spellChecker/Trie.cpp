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

// helper function to recursively copy all children
TrieNode * copyTrie(const TrieNode * copyNode) {
	if (0 == copyNode) {
		return 0;
	}
	TrieNode * newNode;
	// prefix traversal--process node before its children
	try {
		newNode = new TrieNode();
	}
	catch (std::bad_alloc) {
		return 0;
	}

	// for each child of the node to copy, call copyTrie
	for (int i = 0; i < ALPHABET; ++i) {
		newNode->children[i] = copyTrie(copyNode->children[i]);
	}

	return newNode;
}

// copy constructor
Trie::Trie(const Trie& otherTrie) {
	root = copyTrie(otherTrie.root);
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
		for (TrieNode* child : node->children) { 
			deleteAllChildren(child);
		}
	}
}

// destructor
Trie::~Trie() {
	deleteAllChildren(root);
	root = 0;
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
TrieNode* Trie::search(std::string word) {
	if (isEmpty()) {
		return 0;
	}
	TrieNode *current = root;
	
	for (int i = 0; i < (int)word.size(); ++i) {
		if (current->children[word[i] - 'a'] != 0) {
			// go to next node
			current = current->children[word[i] - 'a'];
		}
		else {
			return 0;
		}
	}
	return current;
}

// check if a node has children
bool hasChildren(TrieNode* node) {
	for (int i = 0; i < ALPHABET; ++i) {
		if (node->children[i]) {
			// if the node has any children return true
			return true;
		}
	}
	// else return false
	return false;
}

// remove function
TrieNode* Trie::remove(std::string word) {
	TrieNode *node = search(word);

	if (node == 0) {
		std::cerr << word << " not found in trie.\n";
		return 0;
	}

	// set isWord to false
	if (node->isWord) {
		node->isWord = false;
	}

	// if the node not is a prefix of another word (has not children)
	if (!hasChildren(node)) {
		delete (node);
		node = NULL;
	}
	else {

	}

	return node;

}