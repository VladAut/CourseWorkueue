// CourseWorkueue.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <stdlib.h> // For malloc()
#include <conio.h> // For _getch()
#include <stdio.h> 
#include <fstream> // For files
#include <string>
using namespace std;
// Структура "автомобиль"
struct Auto
{
	// Поля марки и комфортности авто
	char mark[20], comfortability[18];
	// Поля цены и расхода топлива на 100 км
	double price, fconsumption;
	// Поле надёжности авто, измеряемое количеством лет
	int reliability;
	// Указатели на предыдущую и на следующую машину в списке 
	Auto* prev, * next;
	void AutoInput()
	{
		// Цикл для проверки корректности вводимых значений
		while (true)
		{
			cout << "\033[2J\033[1;1H";
			cout << "Введите следующую информацию:\n";
			cout << "Цена автомобиля\n";
			if (cin >> this->price)
				break;
			else
			{
				cout << "\033[2J\033[1;1H" << "Введены некорректные значения, введите ещё раз";
				_getch();
				// Очистка поля ввода данных
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			}
		}
		// Очистка поля ввода данных
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		// Цикл для проверки корректности вводимых значений
		while (true)
		{
			cout << "\033[2J\033[1;1H";
			cout << "Введите следующую информацию:\n";
			cout << "Марка автомобиля\n";
			if (cin.getline(this->mark, 20))
			{
				break;
			}
			else
			{
				cout << "\033[2J\033[1;1H" << "Введены некорректные значения, введите ещё раз";
				_getch();
				cin.clear();
			}
		}
		// Цикл для проверки корректности вводимых значений
		while (true)
		{
			cout << "\033[2J\033[1;1H";
			cout << "Введите следующую информацию:\n";
			cout << "Количество лет безотказной работы (надёжность автомобиля)\n";
			if (cin >> this->reliability)
				break;
			else
			{
				cout << "\033[2J\033[1;1H" << "Введены некорректные значения, введите ещё раз";
				_getch();
				// Очистка поля ввода данных
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			}
		}
		// Очистка поля ввода данных
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		// Цикл для проверки корректности вводимых значений
		while (true)
		{
			cout << "\033[2J\033[1;1H";
			cout << "Укажите степень комфортности данного автомобиля:\n";
			cout << "1.Отличная\n";
			cout << "2.Хорошая\n";
			cout << "3.Удовлетворительная\n";
			switch (_getch())
			{

			case 49:
			{
				strcmp(this->comfortability, "Отличная");
				break;
			}
			case 50:
			{
				strcmp(this->comfortability, "Хорошая");
				break;
			}
			case 51:
			{
				strcmp(this->comfortability, "Удовлетворительная");
				break;
			}
			}
		}
		cin.clear();
		// Цикл для проверки корректности вводимых значений
		while (true)
		{
			cout << "\033[2J\033[1;1H";
			cout << "Введите следующую информацию:\n";
			cout << "Расход топлима на 100 км\n";
			if (cin >> this->fconsumption)
				break;
			else
			{
				cout << "\033[2J\033[1;1H" << "Введены некорректные значения, введите ещё раз";
				_getch();
				// Очистка поля ввода данных
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			}
		}
		cin.clear();	
	}
};
// Структура для динамического списка
struct List
{
	// Указатели на первый и крайний элементы списка
	Auto* head, * tail;
	// Конструктор спискаe
	List()
	{
		this->head = this->tail = NULL;
	}
	// Функция добавления новой машины
	Auto* addAuto(Auto data)
	{
		// Выделяем место в памяти под новую машину и записываем в указатель (ptr)
		Auto* ptr = (Auto*)malloc(sizeof(Auto));
		//Записываем данные        
		strcmp(ptr->mark, data.mark);
		strcmp(ptr->comfortability, data.comfortability);
		ptr->price = data.price;
		ptr->fconsumption = data.fconsumption;
		ptr->reliability = data.reliability;
		// Помещаем в указатель на предыдущюу машину указатель на крайний элемент списка 
		ptr->prev = tail;
		// Если в списке есть крайний элемент
		if (tail != NULL)
			// То указываем что следующий для него элемент — это новая машина (указатель на новую машину(ptr))
			tail->next = ptr;
		// Если первого элемента в списке нет, то им становится вновь созданная машина
		if (head == NULL)
			head = ptr;
		// Указываем что новый элемент является крайним в списке
		tail = ptr;
		// Возвращаем указатель на новый элемент
		return ptr;
	}
};


int main()
{
	int a, b;
	cout << "Hello World!\n";

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
