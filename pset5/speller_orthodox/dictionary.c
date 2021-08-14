// Implements a dictionary's functionality

#include "dictionary.h"

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
//converts ascii letter vals to be from 0 to 25, or 26 if it's a '
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
const unsigned int NUM_CHARS=3;
const unsigned int N = 19683;
int word_count = 0;

// Hash table
node *table[N];

void add_node(int index_in, node *table_in[], node *node_in)
{
	node_in->next = table_in[index_in];
	table_in[index_in] = node_in;
}
//
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
	// TODO
	int index = hash(word);
	bool found = false;
	node *list_used = table[index];
	if (list_used == NULL)
	{
		return false;
	}

	while (list_used->next != NULL)
	{
		found = strcasecmp(list_used->word, word);
		if (found)
		{
			return true;
		}
		list_used = list_used->next;
	}
	return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
	// TODO
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
	hash_val = hash_val % ((int) N);
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
			return false;
		}
		hash_val = hash(word_vec);
		strcpy(new_node->word, word_vec);
		new_node->next = NULL;
		add_node(hash_val, table, new_node);
		word_count++;
	}

	free(word_vec);
	return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
	// TODO
	return word_count;
}

bool free_list_recursive(node *list_in)
{
	bool success = false;
	if ((list_in->next) != NULL)
	{
		success = free_list_recursive(list_in->next);
	}

	if (success)
	{
		free(list_in);
		return true;
	}
	else
	{
		return false;
	}
}

bool free_list(node *list_in)
{
	node *cursor = malloc(sizeof(node));
	if (cursor == NULL)
	{
		printf("allocation failed");
		free(cursor);
		return false;
	}
	while (list_in->next != NULL)
	{
		//printf("%s", list_in->word);
		//cursor = list_in->next;
		//free(list_in);
		//list_in = cursor;
		list_in = list_in->next;
	}
	free(cursor);
	return true;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
	// TODO
	node *cursor = malloc(sizeof(node));
	if (cursor == NULL)
	{
		printf("allocation failed");
		free(cursor);
		return false;
	}
	node *list_in;
	for (int i = 0; i < N; i++)
	{
		//printf("%i\n", i);
		//printf("%i\n", N);
		//	free_list(table[i]);
		list_in = table[i];
		if (list_in != NULL)
		{
			while (list_in->next != NULL)
			{
				//printf("%s\n", list_in->word);
				cursor = list_in->next;
				free(list_in);
				list_in = cursor;
			}
		}
	}
	free(cursor);
	return true;
}
