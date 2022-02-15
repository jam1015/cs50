#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
int count_letters(string sentence);
bool verify_unique(string key);
string encode(string key_in, string word_in);

int main(int argc, string argv[])
{
	if (argc != 2)
	{
		printf("GIVE A SINGLE SUBSTITUTION KEY AS INPUT");
		return (1);
	}
	string text_in = argv[1];
	bool twenty_six_long = strlen(text_in) == 26;
	bool twenty_six_letters = count_letters(text_in) == 26;

	if (!(twenty_six_long && twenty_six_letters))
	{
		printf("Has to be 26 long");
		return (1);
	}

	bool all_unique = verify_unique(text_in);
	if (!all_unique)
	{
		return (1);
	}
	string word_in = get_string("plaintext: ");
	string word_out = encode(text_in, word_in);
	printf("ciphertext: %s\n", word_out);
}

bool verify_unique(string text_in)
{
	for (int c = 'A'; c <= 'Z'; c++)
	{
		int count = 0;
		for (int i = 0, n = strlen(text_in); i < n; i++)
		{
			char upper_char = toupper(text_in[i]);
			if (upper_char == c)
			{
				count++;
				if (count > 1)
				{
					return (0);
				}
			}
		}

		if (count == 0)
		{
			return (0);
		}
	}
	return (1);
}

int count_letters(string text_used)
{
	int letter_count = 0;

	for (int i = 0, n = strlen(text_used); i < n; i++)
	{
		char char_used = text_used[i];

		if (isalpha(char_used))
		{
			letter_count++;
		}
	}
	return letter_count;
}

string encode(string key_in, string word_in)
{
	char char_used;
	string word_out = word_in;
	for (int j = 0, n = strlen(word_in); j < n; j++)
	{
		char_used = word_in[j];
		if (isalpha(char_used))
		{
			int index = toupper(char_used) - 'A';
			char to_sub = key_in[index];
			if (isupper(char_used))
			{
				to_sub = toupper(to_sub);
			}
			else
			{
				to_sub = tolower(to_sub);
			}
			word_out[j] = to_sub;
		}
	}
	return (word_out);
}
