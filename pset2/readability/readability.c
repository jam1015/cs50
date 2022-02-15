#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string sentence);
int count_words(string sentence);
int count_sentences(string sentence);

int main(void)
{
	string text_in = get_string("Text: ");
	int letter_count = count_letters(text_in);
	int word_count = count_words(text_in);
	int sentence_count = count_sentences(text_in);

	float L = (letter_count * 100.0) / word_count;
	float S = (sentence_count * 100.0) / word_count;
	float index = 0.0588 * L - 0.296 * S - 15.8;
	index = round(index);

	if (index < 1)
	{
		printf("Before Grade 1\n");
	}
	else if (index >= 16)
	{
		printf("Grade 16+\n");
	}
	else
	{
		printf("Grade %.0f\n", index);
	}
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

int count_words(string text_used)
{
	int space_count = 0;

	for (int i = 0, n = strlen(text_used); i < n; i++)
	{
		char char_used = text_used[i];

		if (isspace(char_used))
		{
			space_count++;
		}
	}
	int word_count = space_count + 1;

	return word_count;
}

int count_sentences(string text_used)
{
	int sentence_count = 0;

	for (int i = 0, n = strlen(text_used); i < n; i++)
	{
		char char_used = text_used[i];

		if (char_used == '.' || char_used == '?' || char_used == '!')
		{
			sentence_count++;
		}
	}

	return sentence_count;
}
