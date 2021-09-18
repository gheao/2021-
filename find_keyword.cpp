#pragma warning(disable:4996)
#include<iostream>
#include<stdio.h>
#include<vector>
#include<fstream>
#include<stack>
using namespace std;

string Key_word[32] =
{
					  "auto","break","case","char","const","continue","default","do",
					  "double","else","enum","extern","float","for","goto","if","int",
					  "long","register","return","short","signed","sizeof","stastic",
					  "struct","switch","typedef","union","unsigned","void","volatile","while"
};

vector<int> Case_num;
stack<int> if_else_stack;
stack<char> if_else_char_stack;
string Text;
string tmp;
int else_flag = 0;
int divide_if_flag = 0;
int if_else_level = 0;
int Total_num = 0;
int Switch_num = 0;
int Single_case_num = 0;
int If_else_num = 0;
int If_else_if_else_num = 0;

void Search_and_Outfile(string s)
{	
	int l = s.size();
	if (l <= 1)
	{
		return;
	}
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

void if_else_judge(string s,int level)
{
	int if_top = 0;
	char if_char_top = 'i';
	int if_else_if_else_flag = 0;
	if (s == "if") {
		if_else_char_stack.push('i');
		if_else_stack.push(level);
	}
	else if (s == "else_if")
	{
		if_else_char_stack.push('c');
		if_else_stack.push(level);
	}
	else if (s == "else")
	{
		if_top = if_else_stack.top();
		while (!if_else_char_stack.empty()&&if_else_char_stack.top() != 'i')
		{
			if_else_if_else_flag = 1;
			if_else_char_stack.pop();
			if_else_stack.pop();
		}
		while (!if_else_stack.empty() && if_top == if_else_stack.top())
		{
			if_else_stack.pop();
			if_else_char_stack.pop();
		}
		if (if_else_if_else_flag == 1)
		{
			If_else_if_else_num++;
		}
		else
		{
			If_else_num++;
		}
	}
}

void String_trim()
{
	int n = Text.size();
	string change;
	string otherchange;
	int first_change_flag=0;
	int level = if_else_level;
	int l_flag = else_flag;
	for (int i = 0; i < n; i++) {
		if (Text[i] <= 'z' && Text[i] >= 'A')
		{
			change = change + Text[i];
		}
		else
		{
			if (Text[i] == '{' || Text[i] == '(')
			{
				if (Text[i] == '{')
			{
					if_else_level++;
			}
					else_flag = 1;
			}
			else if (Text[i] == '}'||Text[i]==')')
			{
				if (Text[i] == '}')
				{
				if_else_level--;
				}
					else_flag = 1;
			}
			if (first_change_flag == 0)
			{
				otherchange = change;
				first_change_flag = 1;
			}
			
			change = "\0";
		}
	}
	if (change == "else" ||change == "if")
	{
		Text = change;
	}
	if (otherchange == "else" || otherchange == "if")
	{
		Text = otherchange;
	}
	if (Text == "else")
	{
		//cout << l_flag << " " << tmp << "---------------e" << endl;
		if (tmp != "else")
		{
			tmp = "else";
			else_flag = 0;
		}
		else if (l_flag == 1)
		{
			if_else_judge("else",0);
			tmp = "else";
			if (Text[n - 1] == 'e')
			{
				else_flag = 0;
			}
		}
	}
	else if (Text == "if")
	{
		//cout << l_flag << " " << tmp << "---------------i" << endl;
		if (l_flag == 1 && tmp == "else")
		{
			
			if_else_judge("else",level);
			tmp = "\0";
			else_flag = 0;
			if_else_judge("if",level);
		}
		else if (l_flag == 0 && tmp == "else")
		{
			if_else_judge("else_if",level);
			tmp = "\0";
			else_flag = 0;
		}
		else
		{
			if_else_judge("if",level);
		}
	}
	Search_and_Outfile(otherchange);
	Search_and_Outfile(change);
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

	}
	if (tmp == "else")
	{
		if_else_judge("else",0);
		tmp = "\0";
		else_flag = 0;
	}
	cout << "Total_num = " << Total_num << endl;
	if (Find_type >= 2)
	{
		cout << "Switch_num = " << Switch_num << endl;
		if (!Case_num.empty())
		{
			Case_num.push_back(Single_case_num);
		}
		else
		{
			Case_num.push_back(0);
		}
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
	if (Find_type >= 4)
	{
		cout << "if_else_if_num = " << If_else_if_else_num << endl;
	}
	finput.close();
	return 0;
}