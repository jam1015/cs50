
#include <cs50.h>
#include <stdio.h>
int main(void)
{
	long ccn;
	do
	{
		ccn = get_long("Input CCN: ");
	} while (ccn < 1  );

	int iteration = 0;
	int checksum = 0;
	int sixteenth;
	int fifteenth;
	int fourteenth;
	int thirteenth;
	long remainder;
	long prev_quotient = ccn;
	int parity;
	int to_add;
    int intermediate;


	while(iteration < 16 && prev_quotient != 0 ){
		iteration++;

		remainder = prev_quotient % 10;
		prev_quotient /= 10 ;


		parity = iteration % 2;

		printf("====================\n");
		if (parity == 0){
			intermediate = 2 * remainder;
			to_add =   (intermediate) % 10 +   (intermediate) / 10;
		} else {
			to_add = remainder;
		}
checksum = checksum + to_add;

		//("Iteration %i\n",iteration);
		////("Prev quotient %li\n",prev_quotient);
		//("Remainder %li\n",remainder);
		//("Parity %i\n",parity);
		//("to_add %i\n", to_add);
        //("checksum %i\n", checksum);


		switch (iteration){
			case 13 :
				thirteenth = remainder;
				break;
			case 14 :
				fourteenth = remainder;
				break;
			case 15:
				fifteenth = remainder;
				break;
			case 16:
				sixteenth = remainder;
				break;
		}
	}

		//("Checksum %i\n",checksum);
		//("iteration %i\n",iteration);
	if(checksum % 10 == 0)
	{
		if(iteration == 16)
		{
			if(sixteenth == 4)
			{
				printf("VISA\n");

			} else if (sixteenth == 5 && (fifteenth == 1 || fifteenth == 2 || fifteenth == 3 || fifteenth == 4 || fifteenth == 5)) {
				printf("MASTERCARD\n");
			} else {
             printf("INVALID\n");

			}
		} else if(iteration == 13 && thirteenth == 4) {
			printf("VISA\n");
		} else if( iteration == 15 && fifteenth == 3 && (fourteenth == 4 || fourteenth == 7)) {

			printf("AMEX\n");
		} else {
		printf("INVALID\n");
		}
	}  else {
		printf("INVALID\n");

	}
}
