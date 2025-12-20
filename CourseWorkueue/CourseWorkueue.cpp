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
	char* mark, *comfortability;
	// Поля цены и расхода топлива на 100 км
	double price, fconsumption;
	// Поле надёжности авто, измеряемое количеством лет
	int reliability;
	// Функция ввода данных для нового автомобиля
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
	// Конструктор по умолчанию
	Auto()
	{
		this->mark = NULL;
		this->comfortability = NULL;
		this->price = NULL;
		this->fconsumption = NULL;
		this->reliability = NULL;
	}
	// Конструктор с переданными параметрами
	Auto(char markNew[], char comfortabilityNew[], double priceNew, double fconsumptionNew, int reliabilityNew)
	{
		this->mark = markNew;
		this->comfortability = comfortabilityNew;
		this->price = priceNew;
		this->fconsumption = fconsumptionNew;
		this->reliability = reliabilityNew;
	}
};
// Структура элемента списка
struct Node
{
	// Поле с данными этого элемента (структура автомобиль)
	Auto data;
	// Указатели на предыдущий и на следующий элемент в списке 
	Node* prev, * next;
	// Конструктор элемента
	Node(Auto data)
	{
		this->data = data;
		this->prev = this->next = NULL;
	}		
};
// Структура для динамического списка
class List
{
public:
	// Переменная для хранения кол-ва записей в списке
	int count = 0;
	// Указатели на первый и крайний элементы списка
	Node* head, * tail;
	// Конструктор списка по умолчанию
	List()
	{
		this->head = this->tail = NULL;
	}
	// Функция добавления нового элемента в начало списка
	Node* push_front(Auto data)
	{						
		// Выделяем место в памяти под новый элемент и записываем в указатель (ptr)
		Node* ptr = (Node*)malloc(sizeof(Node));
		//Записываем данные        
		ptr->data = data;
		// Помещаем в указатель на предыдущий элемент указатель на крайний элемент списка 
		ptr->next = head;
		// Если в списке есть первый элемент
		if (head != NULL)
			// То указываем что предыдущий для него элемент — это новая машина (указатель на новую машину(ptr))
			head->prev = ptr;
		// Если последнего элемента в списке нет, то им становится вновь созданная машина
		if (tail == NULL)
			tail = ptr;
		// Указываем что новый элемент является первым в списке
		head = ptr;
		// Возвращаем указатель на новый элемент
		return ptr;
	}
	// Функция добавления нового элемента в конец списка
	Node* push_back(Auto data)
	{
		// Выделяем место в памяти под новый элемент и записываем в указатель (ptr)
		Node* ptr = (Node*)malloc(sizeof(Node));
		//Записываем данные        
		ptr->data = data;
		// Помещаем в указатель на предыдущий элемент указатель на крайний элемент списка 
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
	//Удаление первого элемента списка
	void pop_front()
	{
		if (head == NULL) return;
		// Создаём указатель на второй элемент
		Node* ptr = head->next;
		// Если такой имеется
		if (ptr != NULL)
			// То убираем из него указатель на предыдущий элемент
			ptr->prev = NULL;
		else
			tail = NULL;
		// Очищаем текущий первый элемент
		free(head);
		// Записываем на его место "второй"
		head = ptr;
		// Уменьшаем общее кол-во элементов списка
		count--;
	}
	//Удаление последнего элемента списка
	void pop_back()
	{
		if (tail == NULL) return;
		// Создаём указатель на предпоследний элемент
		Node* ptr = tail->prev;
		// Если такой имеется
		if (ptr != NULL)
			// То убираем из него указатель на следующий элемент
			ptr->next = NULL;
		else
			head = NULL;
		// Очищаем текущий крайний элемент
		free(tail);
		// Записываем на его "предпоследний" второй
		tail = ptr;
		// Уменьшаем общее кол-во элементов списка
		count--;
	}
	//Удаление элемента по индексу
	void erase(int index)
	{
		// Получаем указатель на удаляемый элемент
		Node* ptr = getAt(index);
		// Выходим если такого нет
		if (ptr == NULL)
			return;
		// Если это первый элемент, то удаляем спереди
		if (ptr->prev == NULL)
		{
			pop_front();
			return;
		}
		// Если последний, то сзади
		if (ptr->next == NULL)
		{
			pop_back();
			return;
		}
		// Создаём указатели на смежные к удалённому элементы
		Node* left = ptr->prev;
		Node* right = ptr->next;
		left->next = right;
		right->prev = left;
		// Освобождаем память элемента (удаляем)
		free(ptr);
		this->count--;
	}
	//Очистка списка
	void ClearList()
	{
		while (head != NULL)
			pop_front();
		count = 0;
	}
	//Вывод списка на экран	
	void Show()
	{
		// Переменная для нумерации элементов
		int i = 1;
		// Очистка консоли
		cout << "\033[2J\033[1;1H";
		// Указание ширины выводимых данных
		cout.width(4);
		// Заполнение пустого места пробелами
		cout.fill(' ');
		cout << "#";
		cout.width(20);
		cout.fill(' ');
		cout << "Марка автомобиля";
		cout.width(18);
		cout.fill(' ');
		cout << "Комфортность";
		cout.width(10);
		cout.fill(' ');
		cout << "Надёжность";
		cout.width(15);
		cout.fill(' ');
		cout << "Расход топлива";	
		cout.width(15);
		cout.fill(' ');
		cout << "Стоимость" << "\n";
		// Поэлементно проходимся по списку
		for (Node* ptr = this->head; ptr != NULL; ptr = ptr->next)
		{
			cout.width(4);
			cout.fill(' ');
			cout << i << ')';
			cout.width(20);
			cout.fill(' ');			
			cout << ptr->data.mark;
			cout.width(18);
			cout.fill(' ');			
			cout << ptr->data.comfortability;
			cout.width(10);
			cout.fill(' ');			
			cout << ptr->data.reliability;
			cout.width(15);
			cout.fill(' ');			
			cout << ptr->data.fconsumption;			
			cout.width(15);
			cout.fill(' ');			
			cout << fixed << setprecision(2) << ptr->data.price << "\n";
			i++;
		}
	}
	// Получение элемента списка по индексу
	Node* getAt(int index)
	{
		// Создаём указатель для искомого элемента
		Node* ptr;
		// Переменная для хранения индекса массива относительно итераций цикла
		int i = 0;
		// Если искомый элемент во второй половине списка то поиск начнётся с конца, на случай большого кол-ва записей
		if (index > this->count / 2)
		{
			// Начинаем с конца
			i = this->count - 1;
			ptr = tail;
			// Пока не нашли
			while (i != index)
			{
				if (ptr == NULL)
					return ptr;
				ptr = ptr->prev;
				i--;
			}
		}
		else
		{
			// Начинаем с начала
			ptr = head;
			while (i != index)
			{
				if (ptr == NULL)
					return ptr;
				ptr = ptr->next;
				i++;
			}
		}
		return ptr;
	}
	// Получение элемента списка по индексу через оператор []
	Node* operator [] (int index) 
	{
		return getAt(index);
	}
	// Добавление элемента по индексу
	Node* insert(int index, Auto data)
	{
		// Записываем элемент, находящийся на месте нового 
		Node* right = getAt(index);
		// Если такого нет, 
		if (right == NULL)
			// то всавляем в конец списка
			return push_back(data);
		// Записываем элемент перед текущим
		Node* left = right->prev;
		// Если такого нет, 
		if (left == NULL)
			// то вставляем в начало списка
			return push_front(data);
		// Выделяем память под новый элемент и записываем указатель на эту память
		Node* ptr = (Node*)malloc(sizeof(Node));
		// Передаём данные в новую запись
		ptr->data = data;		
		// Меняем местами указатели
		ptr->prev = left;
		ptr->next = right;
		left->next = ptr;
		right->prev = ptr;
		// Возвращаем новый элемент
		return ptr;
	}
	// Функция для рокировки элементов
	void swap(Node* first, Node* second)
	{
		// Выделяем память под временный элемент и записываем указатель на эту память		
		Node* temp = (Node*)(malloc(sizeof(Node)));
		// Передаём в него данные
		temp->data = first->data;
		// Меняем их местави
		first->data = second->data;	
		second->data = temp->data;
		// Освобождаем ранее выделенную память
		free(temp);
	}
};
//Поиск по марке автомобиля
List search(List& list, string s)
{
	// Инициализируем список для вывода результатов поиска
	List result;
	int i = 0;
	// Поэлементно проходим список
	for (Node* ptr = list.head; ptr != NULL; ptr = ptr->next)
	{
		// Сравниваем результаты выполнения функции поиска из библиотеки для работы со строками
		if (((((string)(ptr->data.mark))).find(s) != string::npos))
		{
			result.push_back(list[i]->data);
		}
		i++;
	}
	return result;
}
//Фильтр по комфортности автомобиля
List search(List& list, int flag)
{
	// Инициализируем список для вывода результатов поиска
	List result;
	int i = 0;
	// Выбираем по какой степени комфортности фильтровать
	switch (flag)
	{
		// Отличная		(49 = 1)
	case 49:
	{
		// Поэлементно проходим список
		for (Node* ptr = list.head; ptr != NULL; ptr = ptr->next)
		{
			// Сравниваем результаты выполнения функции поиска из библиотеки для работы со строками
			if (((((string)(ptr->data.mark))).find("Отличная") != string::npos))
			{
				result.push_back(list[i]->data);
			}
			i++;
		}
		break;
	}
		// Хорошая		(50 = 2)
	case 50:
	{
		// Поэлементно проходим список
		for (Node* ptr = list.head; ptr != NULL; ptr = ptr->next)
		{
			// Сравниваем результаты выполнения функции поиска из библиотеки для работы со строками
			if (((((string)(ptr->data.mark))).find("Хорошая") != string::npos))
			{
				result.push_back(list[i]->data);
			}
			i++;
		}
		break;
	}
		// Удовлетворительная		(51 = 3)
	case 51:
	{
		// Поэлементно проходим список
		for (Node* ptr = list.head; ptr != NULL; ptr = ptr->next)
		{
			// Сравниваем результаты выполнения функции поиска из библиотеки для работы со строками
			if (((((string)(ptr->data.mark))).find("Удовлетворительная") != string::npos))
			{
				result.push_back(list[i]->data);
			}
			i++;
		}
		break;
	}
	}	
	return result;
}
// Поиск по численным полям
List search(List& list, float input)
{
	// Инициализируем список для вывода результатов поиска
	List result;
	int i = 0;
	// Поэлементно проходим список
	for (Node* ptr = list.head; ptr != NULL; ptr = ptr->next)
	{
		// Сравниваем данные текущего элемента с введёнными
		if ((ptr->data.fconsumption) == input || ptr->data.price== input || ptr->data.reliability== input)
		{
			result.push_back(list[i]->data);
		}
		i++;
	}
	return result;
}
// Фильтр по числовым полям
List filter(List& list, bool(*func)(Node*, Node*), float item)
{
	// Инициализируем список для вывода результатов поиска
	List result;
	int i = 0;
	Node* temp = (Node*)(malloc(sizeof(Node)));
	temp->data = { NULL,NULL, item,item,item };
	// Поэлементно проходим список
	for (Node* ptr = list.head; ptr != NULL; ptr = ptr->next)
	{
		// Для сравнения с искомыми данными используем функции сравнения определённых полей
		if (func(ptr, temp))
		{
			result.push_back(list[i]->data);
		}
		i++;
	}
	free(temp);
	return result;
}

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
