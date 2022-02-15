#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates

int main(void)
{
	int max = 6;
	int base = 0;
	for (int i = 0; i < max - 1; i++)
	{
		base += i + 1  ;
		for (int j = i + 1; j < max; j++)
		{
			int index = ((i  ) * max) + (j ) - base;
			printf("i = %i :: j = %i :: base = %i :: %i\n", i, j, base, index);
		}
	}
}
