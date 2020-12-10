#include <iostream>
#include <windows.h>
#include <cmath>
#include <limits>

using namespace std;

float getValue(float b, char c[] , float d = 0)
{
	while (true) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
	{
		std::cout << "Введите " << c << " ";
		float a;
		std::cin >> a;

		if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
		{
			std::cout << "Ошибка ввода\n ";
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
		}
		else if (a > b || a < d)
		{
			std::cout << d << " <= " << c << " <= " << b << "\n";
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
		}
		else // если всё хорошо, то возвращаем a
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
		char Rad[] = "R(радиус шара) в метрах";
		char Ro[] = "p(плотность материи шара) в кг/метр^3";
		R = getValue(FLT_MAX, Rad);
		p = getValue(FLT_MAX, Ro);
		float mass = 0;
		__asm
		{
			finit
			xor eax, eax
			start :
			fld R //загружаем радиус
				fst st(1)		//возводим в 3-ю степень 
				fmul st, st(1)
				fmul st, st(1)
				fmul st, st(1)
				fstp st(1)
				fldpi	 //загружаем число pi
				mov eax, 3 //загружаем 3 и 4 для вычисления 4/3
				push eax
				fild dword ptr[esp]
				pop eax
				mov eax, 4
				push eax
				fild dword ptr[esp]
				pop eax
				fdiv st, st(1)	// вычисление 4/3
				fstp st(1)		 //очищаем st1
				fmul st, st(1)	 //умножаем на pi
				fstp st(1)	 //очищаем st1
				fmul st, st(1)	// умножаем на радиус получая объем шара V = 4/3 * pi * R^3
				fstp st(1)	  //очищаем st1
				fld p	//загружаем плотность
				fmul st, st(1) //вычисляем массу как m = p*V
				fstp st(1) //очищаем st1
				fstp mass // выводим массу
		}
		cout << mass << " кг";
	}
}


