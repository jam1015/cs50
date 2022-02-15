// Implements a dictionary's functionality

#include "dictionary.h"

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
// converts ascii letter vals to be from 0 to 25, or 26 if it's a '
char convert_ascii(char char_in)
{
	if (char_in == 27)
	{
		return 26;
	}
	else if (char_in <= 90 && char_in >= 65)
	{
		return char_in - 65;
	}
	else if (char_in <= 122 && char_in >= 97)
	{
		return char_in - 97;
	}
	return 'a';
}

// Represents a node in a hash table
typedef struct node
{
	char word[LENGTH + 1];
	struct node *next;
} node;

// Number of buckets in hash table
const unsigned int NUM_CHARS = 3;
const unsigned int N = 19683;
int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
	// TODO
	// printf("checking %s ||| ", word);
	int index = hash(word);
	// printf("hashed to %i |||", index);
	bool found = false;
	node *list_used = table[index];
	if (list_used == NULL)
	{
		// printf("MISSING\n");
		return false;
	}

	while (list_used != NULL)
	{
		////printf(" ca %s |||", list_used->word);
		found = strcasecmp(list_used->word, word) == 0;
		if (found)
		{
			// printf(" FOUND\n");
			return true;
		}
		list_used = list_used->next;
	}
	// printf(" MISSING\n");
	return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
	// TODO
	// printf("hashing %s ||| ", word);
	int counter = 0;
	char letter;
	int hash_val = 0;
	do
	{
		letter = *(word + counter);
		if (letter != '\0')
		{
			hash_val += ((int)pow(27, counter)) * convert_ascii(letter);
			counter++;
		}

	} while (counter < NUM_CHARS && letter != '\0');
	hash_val = hash_val % ((int)N);
	return hash_val;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
	// TODO
	FILE *dict_file = fopen(dictionary, "r");
	if (dict_file == NULL)
	{
		return false;
	}

	char *word_vec = malloc((LENGTH + 1) * sizeof(char));
	if (word_vec == NULL)
	{
		free(word_vec);
		return false;
	}

	int hash_val;
	while (fscanf(dict_file, "%s", word_vec) != EOF)
	{
		node *new_node = malloc(sizeof(node));
		if (new_node == NULL)
		{
			free(new_node);
			free(word_vec);
			return false;
		}

		// printf("loading %s ||| ", word_vec);
		hash_val = hash(word_vec);
		// printf("hashed to %i\n", hash_val);

		strcpy(new_node->word, word_vec);
		new_node->next = table[hash_val];
		table[hash_val] = new_node;
		word_count++;
	}

	fclose(dict_file);
	free(word_vec);
	return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
	// TODO
	return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
	// TODO
	node *cursor = NULL;

	node *list_in;
	for (int i = 0; i < N; i++)
	{
		list_in = table[i];

		while (list_in != NULL)
		{
			// printf("Unloading index %i	", i);
			// printf("Unloading node: %s\n", list_in->word);
			cursor = list_in->next;
			free(list_in);
			list_in = cursor;
		}
	}
	return true;
}
