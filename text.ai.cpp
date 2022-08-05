#include <iostream>
#include <stdlib.h>
#include <cstring>
using namespace std;

double antiPlagiarism(string text, string fragment);
int nextWordIndex(string text, int index);
bool isSeparator(char symbol);
int isMatchShingle(string text, string shingle);
string getShingle(string fragment, int index);
string lowerCase(string text);

string deletePrepositions(string text);
string getWord(string fragment, int index);
string deleteWord(string text, int startIndex, int endIndex);
int strLen(string str);
string removeDuplicateWords(string text);

int main()
{
	string text = "Hello Do you want to go for a walk with me? Yes. We can go to the luna-park. Take tickets to the ferris wheel, take a ride once. And we can buy cotton candy";
	string fragment = "man hello without hello";
 
	text = lowerCase(text);
	text = deletePrepositions(text);
	fragment = lowerCase(fragment);
	fragment = deletePrepositions(fragment);

	fragment = removeDuplicateWords(fragment);
	cout << text << endl;
	cout << fragment << endl;
	cout << antiPlagiarism(text, fragment);
	return 0;
}

string removeDuplicateWords(string text)
{
	string word1;
	string word2;
	int startIndex = 0;
	int startIndex2 = 0;
	int endIndex = 0;
	do {
		word1 = getWord(text, startIndex2);
		startIndex2 = nextWordIndex(text, startIndex2);
		word2 = getWord(text, startIndex2);
		endIndex = nextWordIndex(text, endIndex);

		//cout << "========" << endl << word1 << " - " << word2 << endl;
		
		if (word1 == word2) {
			text = deleteWord(text, startIndex2, endIndex);
			if (endIndex == -1)
				break;
			endIndex = startIndex2;
			startIndex2 = startIndex;
		}
		startIndex = startIndex2;
	} while (endIndex != -1);
	return text;
}
string deletePrepositions(string text) // ������� ��������
{
	string word;
	int endIndex = 0;
	int startIndex = 0;
	string prepositions[] = { "with", "without", "ago", "apart", "aside", "away", "hence", "notwithstanding", "onto",
						  "through", "withal", "next", "beside", "under", "above", "across", "into", "towards",
						  "from", "since", "for", "past", "till", "until", "along", "amid", "among", "around",
						  "behind", "below", "beneath", "besides", "between", "but", "concerning", "considering",
						  "despite", "down", "during", "following", "inside", "outside", "opposite", "regarding",
						  "via", "versus", "underneath", "unlike", "under", "over", "regarding", "before" };

	do {
		word = getWord(text, endIndex);
		if (endIndex >= strLen(text))
			break;
		endIndex = nextWordIndex(text, endIndex);
		//cout << word << endl;
		for (int i = 0; i < 52; i++)
		{
			if (word == prepositions[i]) {
				text = deleteWord(text, startIndex, endIndex);
				endIndex = startIndex;
			}
		}
		startIndex = endIndex;
	} while (endIndex != -1);

	return text;
}

string getWord(string fragment, int index)
{
	string word;
	int i = 0;

	for (i = index; fragment[i] != '\0'; i++) {
		if (!isSeparator(fragment[i])) {
			word += fragment[i];
			if(isSeparator(fragment[i+1]) or fragment[i+1] == '\0') {
				//word += '\0';
				break;
			}
		}
	}
	return word;
}

string deleteWord(string text, int startIndex, int endIndex)
{
	int i = 0;
	if (endIndex == -1)
		endIndex = strLen(text);
	while (endIndex != startIndex) {
		for (i = startIndex; i < strLen(text); i++)
			text[i] = text[i + 1];
		endIndex--;
		text[i - 1] = '\0';
	}
	return text;
}

string lowerCase(string text)
{
	for (int i = 0; text[i] != '\0'; i++) {
		if (text[i] >= 65 and text[i] <= 90)
			text[i] += 32;
	}
	return text;
}

int strLen(string str) {
	int i = 0;
	for (i = 0; str[i] != '\0'; i++)
		;
	return i;
}

double antiPlagiarism(string text, string fragment) {
	double matchSelections = 0;
	double allSelections = 0;
	double persent = 0.0;
	int index = 0;
	string shingle;

	text = lowerCase(text);
	fragment = lowerCase(fragment);
	fragment = deletePrepositions(fragment);
	while (index >= 0) {
		shingle = getShingle(fragment, index);
		if (shingle != "0") {
			matchSelections += isMatchShingle(text, shingle);
			allSelections++;
			index = nextWordIndex(fragment, index);
		}
		else break;
	}

	persent = matchSelections / allSelections;
	return persent * 100;
}

string getShingle(string fragment, int index) {
	const int SHINGLE_SIZE = 3;
	int size = 0;
	int i = 0;
	string shingle;
	for (i = index; size < SHINGLE_SIZE; i++) {
		if (fragment[i] == '\0') {
			shingle += '\0';
			size++;
			break;
		}

		if ((isSeparator(fragment[i]) and !isSeparator(fragment[i + 1]))) {
			size++;
		}
		shingle += fragment[i];

	}
	if (size < SHINGLE_SIZE) {
		return "0";
	}
	return shingle;
}

int isMatchShingle(string text, string shingle) {
	int index = 0;

	while (true) {
		bool notMatch = false;
		for (int is = 0; shingle[is] != '\0'; is++) {
			if (shingle[is] != text[index]) {
				notMatch = true;
				break;
			}
			index++;
		}
		index = nextWordIndex(text, index);
		if (notMatch and index < 0) {
			return 0;
		}
		else if (!notMatch) return 1;
	}
}

int nextWordIndex(string text, int index) {
	for (int i = index; text[i] != '\0'; i++) {
		if (isSeparator(text[i]) and !isSeparator(text[i + 1]) and text[i + 1])
			return i + 1;
	}
	return -1;
}

bool isSeparator(char symbol) {
	char separator[] = " {,;.!-?:&_%$@^<>()�[]\\*`~+|{}#}";

	for (int i = 0; separator[i] != '\0'; i++) {
		if (separator[i] == symbol)
			return true;
	}
	return false;
}
