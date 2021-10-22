# Simulate a sports tournament
#import csv
#import sys
#import random
import cs50

def main():

	while True:
		height = cs50.get_int("Height: ")
		if height > 0 and height < 9:
			break

	for i in range(height):

		for rowlen in range(height - 1 - i):
			print(" ", end = '')

		for spacelen in range(i + 1):
			print("#", end = '')

		print("  ", end = '')

		for rowlen in range(i):
			print("#", end = '')
		print("#", end = '\n')
		

if __name__ == "__main__":
	main()
