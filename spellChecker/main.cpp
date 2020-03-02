#include <iostream>
#include <fstream>
#include <string>
#include "Trie.h"

// function prototype
void spellCheck(Trie trie, std::string file);

int main() {

	// instantiate trie
	Trie trie;

	// create trie with words file
	std::string file = "Words.txt";
	std::ifstream input;
	input.open(file);
	std::string str;
	if (input) {
		std::cout << "Building dictionary trie...\n";
		while (std::getline(input, str))
		{
			// if line contains string of length > 0, insert it into the trie
			if (str.size() > 0)
				trie.insert(str);
		}
	}
	else {
		std::cout << "Could not open the file " << file << std::endl;
		return 0;
	}
	input.close();

	// declare variables
	std::string word;
	TrieNode *found;
	int exit = 0;

	do {
		// prompt user to enter a word
		std::cout << "Enter a text file name to check its spellling (-1 to quit): ";
		//std::cout << "Enter a word to check its spelling, or enter -1 to quit: ";
		std::cin >> word;

		try {
			exit = std::stoi(word);
		}
		catch (std::exception) {
			exit = 0;
		}

		if (exit == -1) {
			std::cout << "exiting spell checker\n";
		}
		else {
			spellCheck(trie, word);
			/*
			// search for word in the trie
			found = trie.search(word);
			if (found != 0) {
				std::cout << word << " is spelled correctly.\n";
			}
			else {
				std::cout << word << " is spelled incorrectly, or was not found in the trie.\n";
			}*/
		}

	} while (exit != -1);

	system("pause");
	return 0;
}

void spellCheck(Trie trie, std::string file) {
	std::ifstream input;
	input.open(file);
	std::string str;

	if (!input) {
		std::cout << "Could not open the file " << file << std::endl;
		return;
	}
	
	int count = 0;
	while (std::getline(input, str, ' '))
	{
		TrieNode* node = 0;
		// if line contains string of length > 0, insert it into the trie
		if (str.size() > 0) {
			node = trie.search(str);
			if (node == 0) {
				++count; // increment count

			}
		}
	}

	if (count == 0) {
		std::cout << "Spelling check is complete. All words spelled correctly.";
		return;
	}

	std::cout << count << " word(s) spelled incorrectly.\n";

}