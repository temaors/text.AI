#include <iostream>
#include <windows.h>

using namespace std;

char separator[] = "!, ?.-";
const int N = 1024;

bool isSeparator(char sym);
double antiPlagiarism(string text, string fragment);
int getWord(string text, char word[], int ptr);
int getSelection(string text, char word1[], char word2[], char word3[], int ptr);
int strLen(string str);
int strCmp(char s1[], char s2[]);
bool isMatch(string text, char fragmentWord1[], char fragmentWord2[], char fragmentWord3[]);

int main()
{
	string text = "Hello! Do you want to go for a walk with me? Yes. We can go to the luna-park. Take tickets to the ferris wheel, take a ride once. And we can buy cotton candy";
	string fragment;
	
	cout << "Enter fragment: ";
	getline(cin, fragment);
	
	cout << endl << "TEXT:" << endl;
	cout << text << endl;
	cout << antiPlagiarism(text, fragment);
}

double antiPlagiarism(string text, string fragment)
{
	double originality = 0.0;
	double selection = 0;
	double matchSelection = 0;
	int fragmentPtr = 0;
	char fragmentWord1[N];
	char fragmentWord2[N];
	char fragmentWord3[N];
	
	do{
		fragmentPtr = getSelection(fragment, fragmentWord1, fragmentWord2, fragmentWord3, fragmentPtr);
		if(isMatch(text, fragmentWord1, fragmentWord2, fragmentWord3)){
			matchSelection++;
		}
		selection++;
	} while(fragmentPtr != -1);
	originality = matchSelection / selection * 100;
	return originality;
}

bool isSeparator(char sym)
{
	for (int i = 0; separator[i] != '\0'; i++) {
		if (separator[i] == sym)
			return true;
	}
	return false;
}

int getWord(string text, char word[], int ptr)
{
	int i = 0;
	int iw = 0;
	
	for (i = ptr; text[i] != '\0'; i++) {
		if(!isSeparator(text[i])) {
			word[iw] = text[i];
			iw++;
			if (isSeparator(text[i+1]) or text[i+1] == '\0') {
				word[iw] = '\0';
				i++;
				break;
			}
		}
	}
	return i;
}

bool isMatch(string text, char fragmentWord1[], char fragmentWord2[], char fragmentWord3[])
{
	const int N = 1024;
	char word1[N];
	char word2[N];
	char word3[N];
	int ptr = 0;
	do{
		ptr = getSelection(text, word1, word2, word3, ptr);
		if(strCmp(word1, fragmentWord1) == 0 and strCmp(word2, fragmentWord2) == 0 and strCmp(word3, fragmentWord3) == 0){
			cout << fragmentWord1 << "*" << fragmentWord2 << "*" << fragmentWord3 << endl;
			cout << word1 << "*" << word2 << "*" << word3 << endl;                                                             
			cout << "---------------------------------------------------" << endl;		
			return true;
		}
	} while(ptr != -1);
	
	return false;
}

int getSelection(string text, char w1[], char w2[], char w3[], int ptr)
{
	int newPtr = 0;
	ptr = getWord(text, w1, ptr);
	newPtr = ptr;
	ptr = getWord(text, w2, ptr);
	ptr = getWord(text, w3, ptr);
	if (ptr == strLen(text))
		return -1;
	return newPtr;
}

int strLen(string str)
{
	int i = 0;
	for (i = 0; str[i] != '\0'; i++)
		;
	return i;
}

int strCmp(char s1[], char s2[])
{
	for(int i = 0; s1[i] != '\0' or  s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return s1[i] - s2[i];
	}
	return 0;
}
