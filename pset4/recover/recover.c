#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

/*

 start writing to file when we find a jpeg, close when we find another, start
 reading/writing again read 512 at a time
 */

const int BLOCK_LEN = 512;
typedef uint8_t BYTE;
const int BYTE_SIZE = sizeof(BYTE);
const int BLOCK_SIZE = BLOCK_LEN * BYTE_SIZE;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: ./recover image\n");	 //lkjkl
		return 1;
	}

	FILE *input = fopen(argv[1], "r");
	if (input == NULL)
	{
		printf("Could not open file.\n");
		return 2;
	}

	BYTE *block = malloc(BLOCK_SIZE);

	char *file_string = malloc((sizeof(char)) * 7 + 1);
	if (file_string == NULL)
	{
		return 1;
	}

	int file_no = 0;
	bool first_found = false;

	FILE *output = NULL;

	while (fread(block,  sizeof(BYTE), BLOCK_SIZE, input) == 512)
	{
		bool first_matches = *block == 0xff;
		bool second_matches = *(block + 1) == 0xd8;
		bool third_matches = *(block + 2) == 0xff;
		bool fourth_matches = (*(block + 3) & 0xf0) == 0xe0;

		if (first_matches && second_matches && third_matches && fourth_matches)
		{
			first_found = true;
			if (file_no != 0)
			{
				fclose(output);
			}

			sprintf(file_string, "%03i.jpg", file_no);

			output = fopen(file_string, "w");
			if (output == NULL)
			{
				printf("couldn't open output file");
				return (1);
			}
			//printf("File number %i\n", file_no);
			file_no++;
		}
		// buffer[0] == 0xff;
		if (first_found)
		{
			fwrite(block,  sizeof(BYTE), BLOCK_SIZE, output);  // check that fread returns number
		}
	}

	fclose(output);
	free(block);
	free(file_string);
	fclose(input);

	/*
			FILE* output = fopen(argv[2], "w");
			if (output == NULL)
			{
					printf("Could not open file.\n");
					return 1;
			}
	*/

	// doing it statically
	// 	// buffer[3] & 0xf0) == 0xe0
	// sprintf(filename, "%03i.jpg", n)
	// filename should be long enough
	// FILE *img = fopen(filename, "w");
	// fwrite(data, size, number, outptr);
}
