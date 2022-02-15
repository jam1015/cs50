// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav headers
const int HEADER_SIZE = 44;
typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
	// Check command-line arguments
	if (argc != 4)
	{
		printf("Usage: ./volume input.wav output.wav factor\n");
		return 1;
	}

	// Open files and determine scaling factor
	FILE* input = fopen(argv[1], "r");
	if (input == NULL)
	{
		printf("Could not open file.\n");
		return 1;
	}

	FILE* output = fopen(argv[2], "w");
	if (output == NULL)
	{
		printf("Could not open file.\n");
		return 1;
	}

	float factor = atof(argv[3]);

	int j = sizeof(BYTE);
	int *haha = malloc(sizeof(int));
	float *heap_array = malloc(44 * sizeof(BYTE));	 // heap array is on the stack; points to heap
	free(heap_array);

	FILE *ptr = fopen("file1.txt", "r");
	FILE *ptr2 = fopen("file2.txt", "w");
	fclose(ptr);
	if (ptr == NULL)
	{
		return 1;
	}

	char ch = fgetc(ptr);  // gets the next character

	char lele;
	while ((ch = fgetc(ptr)) != EOF) printf("%c", ch);
	fputc(ch, ptr2);

	// fread(buffer, size, qty, file_pointer)
	int arr[10];
	fread(arr, sizeof(int), 10, ptr);

	// or

	double* arr2 = malloc(sizeof(double) * 80);
	fread(arr2, sizeof(double), 80, ptr);
//	<buffer>, <size>, <qty>, <file pointer>

	// TODO: Copy header from input file to output file

	// TODO: Read samples from input file and write updated data to output file

	// Close files
	fclose(input);
	fclose(output);
}
