#pragma warning(disable:4996)
#include<iostream>
#include<stdio.h>
#include<fstream>
using namespace std;

string Key_word[] =
{
				   "auto","break","case","char","const","continue","default","do",
				   "double","else","enum","extern","float","for","goto","if"
				   "int","long","register","return","short","signed","sizeof","stastic"
				   "struct","switch","typedef","union","unsigned","void","volatile","while"
};

string Text;
int Total_num = 0;
int Switch_num = 0;
int Case_num = 0;
int If_else_num = 0;
int If_else_if_else_num = 0;

void Search_and_Outfile(string s)
{
	for (int i = 0; i <= 32; i++)
	{
		if (s == Key_word[i])
		{
			Total_num++;
			break;
		}
	}
	return;
}
void String_trim()
{
	return;
}

int main()
{
	int Find_type;
	string File_p;
	cin >> File_p >> Find_type;
	ifstream finput(File_p);
	while(finput >> Text)
	{
		String_trim();
		cout << Text << endl;
		Search_and_Outfile(Text);
	}
	finput.close();
	
	return 0;
}


