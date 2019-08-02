#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
//#include <string.h>
#include <vector>
#include "defineAnddeclare.h"
using namespace std;
/*extern Text text;
extern vector<symbol> symTable;
extern const string reservedCharacter[];
extern const int reservedCharacterCount;
extern const char * symTabPath;*/
const char * symTabPath = "symbolTable.txt";
const char* binSymTabPath = "binSymbolTable.dat";
const string reservedCharacter[] = { "var","const","true","false","int","real","bool","main","if","else","while","void" };//������
const int reservedCharacterCount = 12;//��������Ŀ
vector<symbol> symList;
Text text;
int row = 1;
Text readText(const char * fileName) {
	fstream in;
	in.open(fileName, ios::in);
	in.seekg(0, ios::end);//�ƶ���ĩβ
	int length = in.tellg();//��ó���
	in.seekg(0, ios::beg);//�ƶ�����ͷ
	char* buffer = new char[length];
	in.read(buffer, length);
	in.close();
	//cout << buffer;
	//*(buffer + length) = '\0';
	/*for (int i = 0; i < length+1;i++) {
		if (*buffer == '\0') {
			cout << "E";
		}
		else {
			cout << *buffer;
			buffer++;
		}
	}*/
	Text ret;
	ret.length = length;
	ret.pC = buffer;
	return ret;
}
void init() {
	text = readText("test.txt");
	text.pC--;
	//......
}
void end() {

}
bool isBlank(char c) {//   \n�Ӳ��ӽ�ȥ��������
	return c == ' ' || c == '\t' || c == '\n';
}
void error() {

}
void error(int row) {
	cout << "wrong at row " << row << endl;
	system("pause");
	exit(1);
}
bool inReservedCharacter(string s) {
	for (int i = 0; i < reservedCharacterCount; i++) {
		if (reservedCharacter[i].compare(s) == 0) {
			return true;
		}
	}
	return false;
}
char read() {
	text.pC++;
	return *text.pC;
}
void retrail() {
	text.pC--;
}
bool getSymbol() {//�����Ƿ񵽴�ײ�
	char c = read();
	string s = "";
	char c1;
	while (isBlank(c)) {//c�ǿո��table��\n
		if (c == '\n') {
			row++;
		}
		c = read();
	}
	symbol sym;
	switch (c)
	{
	case ';'://                          ���޷�
		sym.type = 5;
		sym.content = ";";
		sym.row = row;
		symList.push_back(sym);
		return false;
	case '{':
		sym.type = 5;
		sym.content = "{";
		sym.row = row;
		symList.push_back(sym);
		return false;
	case '}':
		sym.type = 5;
		sym.content = "}";
		sym.row = row;
		symList.push_back(sym);
		return false;
	case ':':
		sym.type = 5;
		sym.content = ":";
		sym.row = row;
		symList.push_back(sym);
		return false;
	case '+'://                              �����
		c = read();
		if (c == '+') {//++
			sym.type = 6;
			sym.content = "++";
			sym.row = row;
			symList.push_back(sym);
		}
		else {//+
			retrail();
			sym.type = 6;
			sym.content = "+";
			sym.row = row;
			symList.push_back(sym);
		}
		return false;
	case '-'://    -     --
		c = read();
		if (c == '-') {//--
			sym.type = 6;
			sym.content = "--";
			sym.row = row;
			symList.push_back(sym);
		}
		else if (c == '0')
		{
			c = read();
			if (c != '.') {//����0
				retrail();
				sym.type = 1;
				sym.content = "0";
				sym.row = row;
				symList.push_back(sym);
			}
			else {
				s += "-0.";
				c = read();
				if (c < '0' || c > '9') {//0.x
					error(row);
				}
				else
				{
					while (c >= '0'&& c <= '9') {
						s += c;
						c = read();
					}
					retrail();
					sym.type = 2;
					sym.content = s;
					sym.row = row;
					symList.push_back(sym);
				}
			}
		}
		else if (c >= '1' && c <= '9')
		{
			s += '-';
			while (c >= '0'&&c <= '9')
			{
				s += c;
				c = read();
			}
			if (c == '.') {//������
				s += '.';
				c = read();
				if (c < '0' || c > '9') {//number.char
					error(row);
				}
				else {
					while (c >= '0'&& c <= '9') {
						s += c;
						c = read();
					}
					retrail();
					sym.type = 2;
					sym.content = s;
					sym.row = row;
					symList.push_back(sym);
				}
			}
			else {//��0����
				retrail();
				sym.type = 1;
				sym.content = s;
				sym.row = row;
				symList.push_back(sym);
			}
		}
		else {//-
			retrail();
			sym.type = 6;
			sym.content = "-";
			sym.row = row;
			symList.push_back(sym);
		}
		return false;
	case '*':
		sym.type = 6;
		sym.content = "*";
		sym.row = row;
		symList.push_back(sym);
		return false;
	case '/'://  /   //    /*...*/
		c = read();
		if (c == '/') {//
			while (c != '\n') {
				c = read();
			}
			row++;
		}
		else if (c == '*') {//     /*...*/
			bool ok = false;
			while (!ok) {
				while (c != '*') {
					if (c == '\n') {
						row++;
					}
					c = read();
				}
				c = read();
				if (c == '/') {
					ok = true;
				}
			}
		}
		else {//   /
			retrail();
			sym.type = 6;
			sym.content = "/";
			sym.row = row;
			symList.push_back(sym);
		}
		return false;
	case '%':
		sym.type = 6;
		sym.content = "%";
		sym.row = row;
		symList.push_back(sym);
		return false;
	case '^':
		sym.type = 6;
		sym.content = "^";
		sym.row = row;
		symList.push_back(sym);
		return false;
	case '&':// &   &&
		c = read();
		if (c == '&') {//&&
			sym.type = 6;
			sym.content = "&&";
			sym.row = row;
			symList.push_back(sym);
		}
		else {// &
			retrail();
			sym.type = 6;
			sym.content = "&";
			sym.row = row;
			symList.push_back(sym);
		}
		return false;
	case '|'://   |    ||
		c = read();
		if (c == '|') {//||
			sym.type = 6;
			sym.content = "||";
			sym.row = row;
			symList.push_back(sym);
		}
		else {// |
			retrail();
			sym.type = 6;
			sym.content = "|";
			sym.row = row;
			symList.push_back(sym);
		}
		return false;
	case '!'://  !=
		c = read();
		if (c == '=') {//!=
			sym.type = 6;
			sym.content = "!=";
			sym.row = row;
			symList.push_back(sym);
		}
		else {// =
			retrail();
			sym.type = 6;
			sym.content = "=";
			sym.row = row;
			symList.push_back(sym);
		}
		return false;
	case '<'://  <   <=  <<
		c = read();
		if (c == '=') {//<=
			sym.type = 6;
			sym.content = "<=";
			sym.row = row;
			symList.push_back(sym);
		}
		else if (c == '<') {// <<
			sym.type = 6;
			sym.content = "<<";
			sym.row = row;
			symList.push_back(sym);
		}
		else {//  <
			retrail();
			sym.type = 6;
			sym.content = "<";
			sym.row = row;
			symList.push_back(sym);
		}
		return false;
	case '>'://  >   >=   >>
		c = read();
		if (c == '=') {//>=
			sym.type = 6;
			sym.content = ">=";
			sym.row = row;
			symList.push_back(sym);
		}
		else if (c == '>') {// >>
			sym.type = 6;
			sym.content = ">>";
			sym.row = row;
			symList.push_back(sym);
		}
		else {//  >
			retrail();
			sym.type = 6;
			sym.content = ">";
			sym.row = row;
			symList.push_back(sym);
		}
		return false;
	case '='://   =    ==
		c = read();
		if (c == '=') {//==
			sym.type = 6;
			sym.content = "==";
			sym.row = row;
			symList.push_back(sym);
		}
		else {//=
			retrail();
			sym.type = 6;
			sym.content = "=";
			sym.row = row;
			symList.push_back(sym);
		}
		return false;
	case '[':
		sym.type = 6;
		sym.content = "[";
		sym.row = row;
		symList.push_back(sym);
		return false;
	case ']':
		sym.type = 6;
		sym.content = "]";
		sym.row = row;
		symList.push_back(sym);
		return false;
	case '(':
		sym.type = 6;
		sym.content = "(";
		sym.row = row;
		symList.push_back(sym);
		return false;
	case ')':
		sym.type = 6;
		sym.content = ")";
		sym.row = row;
		symList.push_back(sym);
		return false;
	case ',':
		sym.type = 6;
		sym.content = ",";
		sym.row = row;
		symList.push_back(sym);
		return false;
	case '\''://�ַ�����		
		c1 = read();//rowҪ++��
		c = read();
		if (c == '\'') {//��ȷ���ַ�����
			s += c1;
			sym.type = 3;
			sym.content = s;
			sym.row = row;
			symList.push_back(sym);
		}
		else {
			error();//����
		}
		return false;
	case '\"'://  �ַ�������
		c = read();
		while (c != '\"' && c != '$') {
			s += c;
			if (c == '\n') {
				row++;
			}
			c = read();
		}
		if (c == '\"') {//��ȷ���ַ���
			sym.type = 4;
			sym.content = s;
			symList.push_back(sym);
		}
		else {//����
			error(row);
		}
		return false;
	default://    ��ʶ��  ��������  ����������  
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {//��ʶ��������
			s += c;
			c = read();
			while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0'&&c <= '9')) {
				s += c;
				c = read();
			}
			retrail();
			sym.content = s;
			sym.row = row;
			if (inReservedCharacter(s)) {//������
				sym.type = 7;
			}
			else {//��ʶ��
				sym.type = 0;
			}
			symList.push_back(sym);
		}
		else if (c == '0') {
			c = read();
			if (c != '.') {//����0
				retrail();
				sym.type = 1;
				sym.content = "0";
				sym.row = row;
				symList.push_back(sym);
			}
			else {
				s += "0.";
				c = read();
				if (c < '0' || c > '9') {//0.x
					error(row);
				}
				else
				{
					while (c >= '0'&& c <= '9') {
						s += c;
						c = read();
					}
					retrail();
					sym.type = 2;
					sym.content = s;
					sym.row = row;
					symList.push_back(sym);
				}
			}
		}
		else if (c >= '1'&&c <= '9')
		{
			while (c >= '0'&&c <= '9')
			{
				s += c;
				c = read();
			}
			if (c == '.') {//������
				s += '.';
				c = read();
				if (c < '0' || c > '9') {//number.char
					error();
				}
				else {
					while (c >= '0'&& c <= '9') {
						s += c;
						c = read();
					}
					retrail();
					sym.type = 2;
					sym.content = s;
					sym.row = row;
					symList.push_back(sym);
				}
			}
			else {//��0����
				retrail();
				sym.type = 1;
				sym.content = s;
				sym.row = row;
				symList.push_back(sym);
			}
		}
		else if (c == '$') {
			return true;
		}
		else if (c == '\0') {//������
			error(row);
		}
		return false;
	}
	return false;
}
void writeSymbolTable() {
	ofstream out;
	out.open(symTabPath, ios::out);
	for (int i = 0; i < symList.size(); i++) {
		out << "code:" << symList[i].type << "\tcontent:" << symList[i].content 
			<<"\trow:"<< symList[i] .row<< '\n';
	}
	out.close();
}
void writeBinSymbolTable() {
	ofstream out;
	out.open(binSymTabPath, ios::out||ios::binary);
	int size = symList.size();
	out.write((char*) (&size), sizeof(int));
	for (int i = 0; i < symList.size(); i++) {
		out.write((char*)& symList[i], sizeof(symList[i]));
		//out << "code:" << symTable[i].type << "\tcontent:" << symTable[i].content << '\n';
	}
	out.close();
}