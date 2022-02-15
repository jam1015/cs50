import cs50
import re

def main():
	text = cs50.get_string("Text: ")
	sentence_re = re.compile("[.?!]")
	letter_re = re.compile("[a-zA-Z]")
	word_re = re.compile(" ")
	
	num_sentences = len(sentence_re.findall(text))
	num_letters = len(letter_re.findall(text))
	num_words = len(word_re.findall(text)) + 1
	
	coleman_liau = (100 * (.0588 * num_letters - 0.296 * num_sentences)/num_words - 15.8)
	
	if (coleman_liau >= 16):
		print("Grade 16+")
		return()
	
	if (coleman_liau < 1):
		print("Before Grade 1")
		return()

	print("Grade " + str(round(coleman_liau)))



if __name__ == "__main__":
	main()
