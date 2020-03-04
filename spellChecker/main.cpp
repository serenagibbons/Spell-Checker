#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
	std::string fileInput;
	TrieNode *found;
	int exit = 0;

	do {
		// prompt user to enter a file
		std::cout << "Enter a text file name to check its spelling (-1 to quit): ";
		std::cin >> fileInput;

		try {
			exit = std::stoi(fileInput);
		}
		catch (std::exception) {
			exit = 0;
		}

		if (exit == -1) {
			std::cout << "exiting spell checker\n";
		}
		else {
			spellCheck(trie, fileInput);
		}

	} while (exit != -1);

	system("pause");
	return 0;
}

// check spelling of the input file
void spellCheck(Trie trie, std::string file) {
	std::ifstream input;
	input.open(file);
	std::string str;

	if (!input) {
		std::cout << "Could not open the file " << file << std::endl;
		return;
	}
	
	int count = 0; // incorrectly spelled words count
	std::vector<std::string> incorrectWords;

	while (std::getline(input, str, ' '))
	{
		TrieNode* node = 0;
		// if line contains string of length > 0, search for it in the trie
		if (str.size() > 0) {
			node = trie.search(str);
			// if search returns null
			if (node == 0) {
				++count; // increment count of incorrect words
				incorrectWords.push_back(str);
			}
		}
	}

	if (count == 0) {
		std::cout << "Spelling check is complete. All words spelled correctly.\n\n";
		return;
	}

	std::cout << count << " word(s) spelled incorrectly.\n";
	// output incorrectly spelled words
	for (std::string s : incorrectWords) {
		std::cout << s << std::endl;
	}
	std::cout << std::endl;

}