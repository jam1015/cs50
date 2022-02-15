// Modifies the volume of an audio file
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

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

	 //TODO: Copy header from input file to output file
	 //doing it dynamically
	 uint8_t* header = malloc(sizeof(uint8_t) * HEADER_SIZE);
	 fread(header, sizeof(uint8_t), HEADER_SIZE, input);
	 fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);
	 free(header);

	// doing it statically
	uint8_t header2[HEADER_SIZE];
	fread(header2, sizeof(uint8_t), HEADER_SIZE, input);
	fwrite(header2, sizeof(uint8_t), HEADER_SIZE, output);

	//int16_t* sample = malloc(sizeof(int16_t));
	//while (fread(sample, sizeof(int16_t), 1, input))
	//{
	//  	*sample *= factor;
	//  	fwrite(sample, sizeof(int16_t), 1, output);
	//}
	//free(sample);

	 int16_t sample[1];
	 while (fread(sample, sizeof(int16_t), 1, input))
	 {
	   *sample *= factor;
	   fwrite(sample, sizeof(int16_t), 1, output);
	 }

	fclose(input);
	fclose(output);

	int *a;
	a = malloc(sizeof(int));
	*a = 3;
	printf("%i\n", *a);
	free(a);

}
