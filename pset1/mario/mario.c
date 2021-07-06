#include <cs50.h>
#include <stdio.h>
int main(void)
{
	int height;
	do 
	{
		height = get_int("Start size: ");
	} while (height > 8 || height < 1);

	for (int row = 0; row < height; row++) 
	{
		int n_leading_spaces = height - (row + 1);
		for (int space = 0; space < n_leading_spaces; space++) 
		{
			printf(" ");
		}

		for (int hash = 0; hash < row + 1 ; hash++) 
		{
			printf("#");
		}
		
		printf("  ");

		for (int hash = 0; hash < row + 1 ; hash++) 
		{
			printf("#");
		}

		printf("\n");
	}

}

