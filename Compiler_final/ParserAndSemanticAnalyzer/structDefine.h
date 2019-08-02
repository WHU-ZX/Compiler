#pragma once
#include <string>
#include <map>
#include <stdint.h>
class Symbol;
using namespace std;
class ID;
struct symbol//�ʷ�������õķ���
{
	int type;
	string content;
	int row;
};
struct DicIndex//no need
{
	int state;
	string sym;
	friend bool operator < (const struct DicIndex& d1, const struct DicIndex& d2);
};
struct VarIndex
{
	string name;
	int level;
	friend bool operator < (const struct VarIndex& v1, const struct VarIndex& v2);
};
enum Behavior { S_, r, GOTO, acc, ERROR };
struct todo
{
	Behavior behavior;
	int aim = -1;//��behavior��S����goto,���ʾĿ��״̬����behavior��r�����ʾ����ʽ���
};
void getSymbolFromLexer();
void error(int row,int flag);
void error(int row, int flag, string detail);
Symbol* popSymbol();
void pushSym_State(Symbol* s, int state);
todo getWhatToDo(symbol sym);
ID* getHighestLevelVar(string name);
void clearVarTableAtLevel(int level);
