#include <iostream>
#include "defineAnddeclare.h"
using namespace std;

int main()
{
	init();//��ʼ�����롢�������
	//cout << text.pC;
	//Text t= readText("test.txt");
	while (!getSymbol()) {

	}
	writeSymbolTable();
	writeBinSymbolTable();
	end();//�ر���������
	system("pause");
}