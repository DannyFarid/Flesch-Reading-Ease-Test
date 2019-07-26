#include <iostream>
#include <string>
using namespace std;

int count_words(string phrase);
bool is_vowel(string letter);
int count_syllables_word(string word);
bool is_punctuation(string letter);
int count_syllables_phrase(string phrase);
int count_sentences(string phrase);
int readability_index(string phrase);

int main() {
	string phrase;
	cout << "Input text: ";
	getline (cin, phrase);
	//phrase = "Hello my name is Danny. I like to play basketball.";
	cout << "\n\nSyllables: " << count_syllables_phrase(phrase) 
		<< "\nWords: " << count_words(phrase) 
		<< "\nSentences: " << count_sentences(phrase) 
		<< "\nReadability Index: " << readability_index(phrase) << "\n";
	return 0;
}


int count_words(string phrase) {

	int spaces_count = 0;

	for (int i = 0; i < phrase.length(); i++) {
		if (phrase.substr(i, 1) == " ")
			spaces_count++;
	}
	return spaces_count + 1;
}

bool is_vowel(string letter) {

	if (letter == "a" || letter == "e" || letter == "i" || letter == "o" || letter == "u" || letter == "y" || letter == "A" || letter == "E" || letter == "I" || letter == "O" || letter == "U" || letter == "Y") {
		return true;
	}
	else
		return false;
}

int count_syllables_word(string word) {

	int syllable_count = 0;

	for (int i = 0; i < word.length(); i++) 
	{
		if (is_vowel(word.substr(i, 1)) && !is_vowel(word.substr(i + 1, 1)))
			syllable_count++;
	}

	if (word.substr(word.length() - 1, 1) == "e") 
		//the above loop will erroneously count an "e" at the end of a word as
		//a separate syllable, so if this is the case, take one syllable away
		syllable_count--;

	if (syllable_count == 0)
		syllable_count = 1;

	return syllable_count;
}

int count_syllables_phrase(string phrase) {

	/*int syllable_count = 0;

	for (int i = 0; i < phrase.length(); i++)
	{
		if (is_vowel(phrase.substr(i, 1)) && !is_vowel(phrase.substr(i + 1, 1)))
			syllable_count++;
	}

	if (phrase.substr(phrase.length() - 1, 1) == "e")
		//the above loop will erroneously count an "e" at the end of a word as
		//a separate syllable, so if this is the case, take one syllable away
		syllable_count--;

	if (syllable_count == 0)
		syllable_count = 1;

	return syllable_count;*/

	int start_word = 0, end_word = 0, syllable_count = 0;
	string word;

	phrase = " " + phrase; 
	//add a space at the front of the word so that the first if statement in the for loop
	//doesn't try to take substring starting at -1 (0-1), and for loop starts at i=1, which will be the beginning
	//of the word because of the added space
	
	for (int i = 1; i < phrase.length(); i++) {
		if (!is_punctuation(phrase.substr(i, 1)) && phrase.substr(i, 1) != " " && phrase.substr(i - 1, 1) == " ") {
			start_word = i;
			//this if statement checks: not punctuation, not a space, and the character before is a space
			//(or else every letter in a word would count as the beginning of the word)
		}
		else if (((is_punctuation(phrase.substr(i, 1)) || phrase.substr(i, 1) == " ")) && !is_punctuation(phrase.substr(i-1, 1)) && phrase.substr(i-1, 1) != " ")
			end_word = i;
			//this if statement checks: is punctuation or a space and that the character before is neither
			//punctuation or a space (a period followed by a space would result in end_word being defined twice)
		

		if (end_word != 0) { 
			//only run this if end_word is some value, or else it would run this command every
			//iteration of the for loop (which is bad)
			word = phrase.substr(start_word, end_word - start_word);
			syllable_count += count_syllables_word(word);
			end_word = 0;//reset end_word and start_word to 0
		}
	}
	return syllable_count;
}

bool is_punctuation(string letter) {
	if (letter == "." || letter == "!" || letter == "?" || letter == ";" || letter == ":")
		return true;
	else
		return false;
}

int count_sentences(string phrase) {

	int sentence_count = 0;

	for (int i = 0; i < phrase.length(); i++) {
		if (is_punctuation(phrase.substr(i, 1)))
			sentence_count++;
	}
	return sentence_count;
}

int readability_index(string phrase) {
	int syllables = count_syllables_phrase(phrase);
	int words = count_words(phrase);
	int sentences = count_sentences(phrase);
	int readability_index = 206.835 - 84.6 * (syllables / words) - 1.015 * (words / sentences);
	return readability_index;
}

