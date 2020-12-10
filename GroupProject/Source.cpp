#include <iostream>
#include <windows.h>
#include <cmath>
#include <limits>

using namespace std;

float getValue(float b, char c[] , float d = 0)
{
	while (true) // ���� ������������ �� ��� ���, ���� ������������ �� ������ ���������� ��������
	{
		std::cout << "������� " << c << " ";
		float a;
		std::cin >> a;

		if (cin.fail()) // ���� ���������� ���������� ��������� ���������,
		{
			std::cout << "������ �����\n ";
			std::cin.clear(); // �� ���������� cin � '�������' ����� ������
			std::cin.ignore(32767, '\n'); // � ������� �������� ����������� ����� �� �������� ������
		}
		else if (a > b || a < d)
		{
			std::cout << d << " <= " << c << " <= " << b << "\n";
			std::cin.clear(); // �� ���������� cin � '�������' ����� ������
			std::cin.ignore(32767, '\n'); // � ������� �������� ����������� ����� �� �������� ������
		}
		else // ���� �� ������, �� ���������� a
			return a;
	}
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while(true)
	{
		float R = 0;
		float p = 0;
		char Rad[] = "R(������ ����) � ������";
		char Ro[] = "p(��������� ������� ����) � ��/����^3";
		R = getValue(FLT_MAX, Rad);
		p = getValue(FLT_MAX, Ro);
		float mass = 0;
		__asm
		{
			finit
			xor eax, eax
			start :
			fld R //��������� ������
				fst st(1)		//�������� � 3-� ������� 
				fmul st, st(1)
				fmul st, st(1)
				fmul st, st(1)
				fstp st(1)
				fldpi	 //��������� ����� pi
				mov eax, 3 //��������� 3 � 4 ��� ���������� 4/3
				push eax
				fild dword ptr[esp]
				pop eax
				mov eax, 4
				push eax
				fild dword ptr[esp]
				pop eax
				fdiv st, st(1)	// ���������� 4/3
				fstp st(1)		 //������� st1
				fmul st, st(1)	 //�������� �� pi
				fstp st(1)	 //������� st1
				fmul st, st(1)	// �������� �� ������ ������� ����� ���� V = 4/3 * pi * R^3
				fstp st(1)	  //������� st1
				fld p	//��������� ���������
				fmul st, st(1) //��������� ����� ��� m = p*V
				fstp st(1) //������� st1
				fstp mass // ������� �����
		}
		cout << mass << " ��";
	}
}


