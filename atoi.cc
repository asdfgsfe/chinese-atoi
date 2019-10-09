#include <iostream>                                                                                              
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

const static int g_chinese = string("��").size();

static unordered_map<string, int> g_uints = {
	{ "��", 100000000 },{ "��", 10000 },{ "ǧ", 1000 },{ "��", 100 },{ "ʮ", 10 },{ "��", 1 } };

static unordered_map<string, int> g_numbers = {
	{ "��", 9 },{ "��", 8 },{ "��", 7 },{ "��", 6 },{ "��", 5 },{ "��", 4 },{ "��", 3 },{ "��", 2 },{ "һ", 1 },{ "��", 0 } };

bool g_invaildInput = false;

//˼·�ǳ��򵥾��Ǵ�������������ĵ�����,����'λ'�Ƽ�¼����,
//��'λ'�ͳ���λ�����뵽���result��.firstUnit�����һ��λ,second�������λ,
//����:��ʮ���� ʮ��secondUnit,����firsUnit
long long CvrProcess(const string& cnum, int end, bool minus)
{
	long long firstUnit = 1;                    //һ����λ
	long long secondUnit = 1;                   //������λ
	long long num = 0;
	int flag = minus ? -1 : 1;
	int i = cnum.size() - 1;
	while (i - g_chinese + 1 >= end)
	{
		string cur = cnum.substr(i - g_chinese + 1, g_chinese);
		if (g_uints.count(cur) && g_numbers.count(cur))
		{
			return 0;
		}
		//std::cout << "i=" << i << " cur=" << cur << std::endl;
		long tmpUnit = g_uints.count(cur) ? g_uints[cur] : 1;
		if (tmpUnit > firstUnit)
		{
			firstUnit = tmpUnit;
			secondUnit = 1;
		}
		else if (tmpUnit > secondUnit)
		{
			secondUnit = tmpUnit;
		}
		num += flag * firstUnit * secondUnit * (g_numbers.count(cur) ? g_numbers[cur] : 0);
		if ((minus && num < (signed int) 0x80000000) || (!minus && num > (signed int)0x7fffffff))
		{
			return 0;
		}
		i -= g_chinese;
		//std::cout << "firstUint=" << firstUnit << " secondUint=" << secondUnit
		//	<< " tmp=" << tmpUnit << " result=" << result 
		//	<< " cur=" << (firstUnit * secondUnit * (g_numbers.count(cur) ? g_numbers[cur] : 0)) << std::endl;
	}
	g_invaildInput = false;
	return num;
}

//����������λ��һ������ �����ַ���
int Atoi(const string& str)
{
	g_invaildInput = true;
	if (str.empty())
	{
		return 0;
	}
	bool minus = false;
	int i = 0;
	if (str.substr(i, g_chinese) == "��")
	{
		i += g_chinese;
		minus = true;
	}
	else if (str.substr(i, g_chinese) == "��")
	{
		i += g_chinese;
	}
	if (i != str.size())
	{
		return (int)CvrProcess(str, i, minus);
	}
	return 0;
}

int main(void)
{
	string num("����ʮ��");
	std::cout << num << " " << Atoi(num) << std::endl;
	//string num("��ʮǧ��"); //��ʮǧ����ʵ����2�� �������д���
	//std::cout << num << " " << Atoi(num) << std::endl;
	//num = "��ǧ������ʮ��";
	//std::cout << num << " " << Atoi(num) << std::endl;
	//num = "������ǧ�İٶ�ʮ����";
	//std::cout << num << " " << Atoi(num) << std::endl;

	return 0;
}