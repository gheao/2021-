#pragma warning(disable:4996)
#include<iostream>
#include<stdio.h>
#include<vector>
#include<fstream>
using namespace std;

string Key_word[32] =
{
					  "auto","break","case","char","const","continue","default","do",
					  "double","else","enum","extern","float","for","goto","if","int",
					  "long","register","return","short","signed","sizeof","stastic",
					  "struct","switch","typedef","union","unsigned","void","volatile","while"
};

string Text;
int Total_num = 0;
int Switch_num = 0;
int Single_case_num = 0;
vector<int> Case_num;
int If_else_num = 0;
int If_else_if_else_num = 0;

void Search_and_Outfile(string s)
{
	for (int i = 0; i <= 31; i++)
	{
		if (s == Key_word[i])
		{
			if (s == "switch")
			{
				Case_num.push_back(Single_case_num);
				Switch_num++;
				Single_case_num = 0;
			}
			if (s == "case")
			{
				Single_case_num++;
			}
			Total_num++;
			break;
		}
	}
	return;
}
void String_trim()
{
	int n = Text.size();
	string change;
	for (int i = 0; i < n; i++) {
		if (Text[i] <= 'z' && Text[i] >= 'A')
		{
			change = change + Text[i];
		}
		else
		{
			break;
		}
	}
	Text = change;
	return;
}

int main()
{
	int Find_type;
	string File_p;
	cin >> File_p;
	cin >> Find_type;
	ifstream finput(File_p);

	while (finput >> Text)
	{
		String_trim();
		Search_and_Outfile(Text);

	}
	cout << "Total_num = " << Total_num << endl;
	if (Find_type >= 2)
	{
		cout << "Switch_num = " << Switch_num << endl;
		Case_num.push_back(Single_case_num);
		cout << "Case_num = ";
		for (int i = 1; i <= Switch_num; i++)
		{
			cout << Case_num[i] << " ";

		}
		cout << endl;
	}
	if (Find_type >= 3)
	{
		cout << "if_else_num = " << If_else_num << endl;
	}
	finput.close();
	return 0;
}