#include "ID.h"
ID::ID(string name, int level, int row):Symbol(-1,"ID",row)
{
	this->name = name;
	this->level = level;
	this->type = "";
	this->changable = true;//Ĭ��Ϊ����
	this->value = "";
}
ID::~ID()
{
}
