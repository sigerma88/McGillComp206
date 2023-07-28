#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * This is a C program that takes two words as an input and detects if they are anagrams.
 * It is assumed that the there will only be 2 words with letters in the 26 english alphabet.
 * The program is case insensitive.
 *
 * @param WORD1 - The first word for the anagram detection
 * @param WORD2 - The second word for the anagram detection
 * @return 0 - It is an anagram
 *         1 - It is not an anagram
 *         2 - Usage error
 * @author Siger Ma
 *         Department: McGill, Faculty of Engineering, ECSE, Software Engineering
 *         McGill ID: 261051828
 *         Email: siger.ma@mail.mcgill.ca
 */

int main (int argc, char *argv[]) {
	// Input validation
	if (argc != 3) {
		printf("usage: ./anagram WORD1 WORD2\n");
		return 2;
	}

	// If both words not of same length, not an anagram
	if (strlen(argv[1]) != strlen(argv[2])) {
		printf("Not an anagram\n");
		return 1;
	}

	// Convert words to lower case
	char wordOne[strlen(argv[1]) + 1];
	strcpy(wordOne, argv[1]);
	for (int i = 0; i < strlen(wordOne); i++) {
		wordOne[i] = tolower(wordOne[i]);
	}
	char wordTwo[strlen(argv[2]) + 1];
	strcpy(wordTwo, argv[2]);
	for (int i = 0; i < strlen(wordTwo); i++) {
		wordTwo[i] = tolower(wordTwo[i]);
	}

	// Array to store frequency of characters
        int charFrequency[26] = {0};

        // Iterate over words
        for (int i = 0; i < strlen(wordOne); i++) {
		// Increment character frequency when encountered in word one
                charFrequency[wordOne[i] - 'a']++;
		// Decrement character frequency when encountered in word two
                charFrequency[wordTwo[i] - 'a']--;
        }

        // If frequency of all characters is zero, it is an anagram
        for (int i = 0; i < 26; i++) {
                if (charFrequency[i] != 0) {
                        printf("Not an anagram\n");
                        return 1;
                }
        }

        printf("Anagram\n");
        return 0;
}

