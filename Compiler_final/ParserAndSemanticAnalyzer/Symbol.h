#pragma once
#include "structDefine.h"
using namespace std;
class Symbol
{
public:
	int sym_type;
	string content;
	int row;//����Ƿ��ս������row���ڹ�Լ����������Ŀ�е����һ��
	Symbol(int type,string content,int row);
	virtual ~Symbol();
};

