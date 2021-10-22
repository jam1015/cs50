# Simulate a sports tournament
#import csv
#import sys
#import random
import re
import cs50

def main():
	number = cs50.get_string("Number: ")
	evens = [twice_dig_sum(i) for i in number[~1::-2]]
	odds = [int(i) for i in number[~0::-2]]
	checksum = sum(evens) + sum(odds)

	if checksum % 10 != 0:
		print("INVALID\n")
		return("")
	elif len(number) == 15 and (re.compile("^3[47]").match(number)):
		print("AMEX\n")
		return("")
	elif len(number) == 16 and (re.compile("^5[1-5]").match(number)):
		print("MASTERCARD\n")
		return("")
	elif (len(number) == 13 or len(number) == 16) and number[0] == "4":
		print("VISA\n")
		return("")
	else:
		print("INVALID\n")
		return("")



def twice_dig_sum(dig_in):
	dig_in_double_int = str(2 * int(dig_in))
	if(len(dig_in_double_int) > 1):
		first = int(dig_in_double_int[0])
		second = int(dig_in_double_int[1])
		return(first + second)
	else:
		return(int(dig_in_double_int))


if __name__ == "__main__":
	main()
