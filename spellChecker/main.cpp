#include <iostream>
#include <fstream>
#include <string>
#include "Trie.h"

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
		std::cout << "Enter a word to check its spelling, or enter -1 to quit: ";
		std::cin >> word;

		try {
			exit = std::stoi(word);
		}
		catch (std::exception) {
			// do nothing
		}

		if (exit == -1) {
			std::cout << "exiting spell checker\n";
		}
		else {
			// search for word in the trie
			found = trie.search(word);
			if (found != 0) {
				std::cout << word << " is spelled correctly.\n";
			}
			else {
				std::cout << word << " is spelled incorrectly, or was not found in the trie.\n";
			}
		}

	} while (exit != -1);

	system("pause");
	return 0;
}