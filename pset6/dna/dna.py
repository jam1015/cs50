# Simulate a sports tournament
#import csv
#import sys
#import random
import re
import cs50
import sys
import csv

def main():
	if len(sys.argv) != 3:
		print("Give two command line args")
		return()
	people = []
	with open(sys.argv[1]) as file:
		reader = csv.DictReader(file)
		for row in reader:
			people.append(row)
	

	with open(sys.argv[2]) as file:
		sequence = file.read()
	
	#count_dict = [apply_find_seq(person, sequence) for person in people]

	count_dict = apply_find_seq(people[0], sequence)
	#print(count_dict)
	
	for person in people:
		#print(person["name"])
		found_match = True
		for key in count_dict.keys():
			#print(key)
			#print("In sequence: " + count_dict[key] + " person: " + person[key])
			found_match = count_dict[key] == person[key]
			if not found_match:
				break
		 
		if found_match:
			print(person["name"])
			return()

	print("No match")
	return()

def find_seq(seq_in, query_in):
	query_repeats = 1

	while True:
		query_regex = re.compile(query_in * query_repeats)
		num_in_seq = len(query_regex.findall(seq_in))
		if num_in_seq == 0:
			return(str(query_repeats - 1))
		else:
			query_repeats += 1

def apply_find_seq(dictionary_in, seq_in):
	dict_out = {query : (find_seq(seq_in, query) ) for (query,count) in dictionary_in.items() if query != 'name'}
	return(dict_out)

if __name__ == "__main__":
	main()
