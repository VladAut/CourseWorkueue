// CourseWorkueue.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <stdlib.h> // For malloc()
#include <conio.h> // For _getch()
#include <stdio.h> 
#include <fstream> // For files
#include <string>
#include <algorithm> // Для std::transform
#include <cctype>    // Для std::tolower
#include <new> // Обязательно для placement new

using namespace std;
bool tryInputNumber(int& result)
{
	string input = "";
	char ch;
	while (true)
	{
		ch = _getch();

		if (ch == 27)
			return false;

		if (ch == 13)
		{ // 13 — это код клавиши Enter
			if (input.empty())
				continue; // Не даем нажать Enter на пустой строке
			cout << endl;
			result = stoi(input); // Преобразуем накопленную строку в число
			return true;
		}

		if (ch == 8)
		{ // 8 — это Backspace
			if (!input.empty())
			{
				input.pop_back();
				cout << "\b \b"; // Удаляем символ из консоли визуально
			}
		}
		else if (isdigit(ch))
		{ // Проверяем, что нажата цифра
			input += ch;
			cout << ch; // Выводим цифру на экран
		}
	}
}
bool tryInputDouble(double& result) 
{
	string input = "";
	char ch;
	bool dotPointed = false; // Флаг: была ли уже поставлена точка

	while (true) 
	{
		ch = _getch();

		// 1. Выход по Esc
		if (ch == 27) return false;

		// 2. Завершение по Enter
		if (ch == 13) 
		{
			if (input.empty() || input == "." || input == "-") 
				continue;
			cout << endl;
			result = atof(input.c_str()); // Преобразуем строку в double
			return true;
		}

		// 3. Удаление (Backspace)
		if (ch == 8) 
		{
			if (!input.empty()) 
			{
				if (input.back() == '.') dotPointed = false; // Если удалили точку, разрешаем её снова
				input.pop_back();
				cout << "\b \b";
			}
		}

		// 5. Дробная часть (точка или запятая)
		else if ((ch == '.' || ch == ',') && !dotPointed) 
		{
			// Разрешаем точку, только если её еще нет
			// (в C++ stod понимает только точку, поэтому всегда записываем её)
			input += ',';
			dotPointed = true;
			cout << (char)ch; // Выводим то, что нажал пользователь
		}

		// 6. Цифры
		else if (isdigit(ch)) 
		{
			input += ch;
			cout << ch;
		}
	}
}
bool tryInputCharArray(char* result, int maxSize) {
	int currentLen = 0;
	int ch;

	// Очищаем массив перед началом ввода
	result[0] = '\0';

	while (true) {
		ch = _getch(); // Читаем код клавиши

		// 1. Обработка Esc
		if (ch == 27) {
			return false;
		}

		// 2. Обработка Enter
		if (ch == 13) {
			if (currentLen == 0) continue; // Не пускаем пустую строку
			cout << endl;
			result[currentLen] = '\0'; // Завершаем строку нуль-терминатором
			return true;
		}

		// 3. Обработка Backspace
		if (ch == 8) {
			if (currentLen > 0) {
				currentLen--;
				result[currentLen] = '\0';
				cout << "\b \b"; // Затираем в консоли
			}
		}
		// 4. Обработка спец. клавиш (стрелки и т.д.)
		else if (ch == 0 || ch == 224) {
			_getch(); // Пропускаем второй код
		}
		// 5. Печатаемые символы (с проверкой на размер массива)
		else if (ch >= 32) {
			// Проверяем, осталось ли место в массиве (учитываем 1 байт под '\0')
			if (currentLen < maxSize - 1) {
				result[currentLen] = (char)ch;
				currentLen++;
				cout << (char)ch;
			}
		}
	}
}
// Структура "автомобиль"
struct Auto
{
	// Поля марки и комфортности авто
	char mark[20], comfortability[20];
	// Поля цены и расхода топлива на 100 км
	double price, fconsumption;
	// Поле надёжности авто, измеряемое количеством лет
	int reliability;
	// Функция ввода данных для нового автомобиля
	bool AutoInput()
	{
		int exit = 1;
		do
		{
			switch (exit)
			{
			case 1:
			{
				cout << "\033[2J\033[1;1H";
				cout << "Введите следующую информацию:\n";
				cout << "Цена автомобиля\n";
				if (!tryInputDouble(this->price))
					return false;
				exit++;
			}
			case 2:
			{
				cout << "\033[2J\033[1;1H";
				cout << "Введите следующую информацию:\n";
				cout << "Марка автомобиля\n";
				if (!tryInputCharArray(this->mark, 20))
				{
					exit--;
					break;
				}
				exit++;
			}
			case 3:
			{
				cout << "\033[2J\033[1;1H";
				cout << "Введите следующую информацию:\n";
				cout << "Количество лет безотказной работы (надёжность автомобиля)\n";
				if (!tryInputNumber(this->reliability))
				{
					exit--;
					break;
				}
				exit++;
			}
			case 4:
			{
				cout << "\033[2J\033[1;1H";
				cout << "Укажите степень комфортности данного автомобиля:\n";
				cout << "1.Отличная\n";
				cout << "2.Хорошая\n";
				cout << "3.Удовлетворительная\n";
				int choice;				
				if (tryInputNumber(choice))
				{
					if (choice == 1)
					{
						strncpy_s(this->comfortability, "Отличная", 18);						
					}
					else if (choice == 2)
					{
						strncpy_s(this->comfortability, "Хорошая", 18);						
					}
					else if (choice == 3)
					{
						strncpy_s(this->comfortability, "Удовлетворительная", 18);						
					}
					else
						break;
				}
				else
				{
					exit--;
					break;
				}
				exit++;
			}
			case 5:
			{
				cout << "\033[2J\033[1;1H";
				cout << "Введите следующую информацию:\n";
				cout << "Расход топлима на 100 км\n";
				if (!tryInputDouble(this->fconsumption))
				{
					exit--;
					break;
				}
				exit++;
			}
			}
		} while (exit < 6);
		return true;
	}
	// Конструктор по умолчанию
	Auto()
	{
		this->price = 0.0;
		this->fconsumption = 0.0;
		this->reliability = 0;
	}
	Auto(double priceNew, double fconsumptionNew, int reliabilityNew)
	{
		this->price = priceNew;
		this->fconsumption = fconsumptionNew;
		this->reliability = reliabilityNew;
	}
	// Конструктор с переданными параметрами
	Auto(string markNew, string comfortabilityNew, double priceNew, double fconsumptionNew, int reliabilityNew)
	{
		// strncpy_s(куда, откуда, сколько байт максимум)
		strncpy_s(this->mark, markNew.c_str(), 20);		
		strncpy_s(this->comfortability, comfortabilityNew.c_str(), 18);		
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
	// Указатели на предыдущий и на следующ ий элемент в списке 
	Node* prev, * next;
	// Конструктор элемента
	Node(const Auto& data)
	{
		this->data = data;
		this->prev = NULL;
		this->next = NULL;
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
		this->head = NULL;
		this->tail = NULL;
	}
	// Функция добавления нового элемента в начало списка
	Node* push_front(Auto data)
	{
		// Выделяем место в памяти под новый элемент и записываем в указатель (ptr)
		Node* ptr = (Node*)malloc(sizeof(Node));
		if (ptr != NULL) {
			// 2. Вызываем конструктор вручную в выделенной памяти (placement new)
			// Это инициализирует строки mark и comfortability корректно
			new (ptr) Node(data);
		}
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
		if (ptr != NULL) {
			// 2. Вызываем конструктор вручную в выделенной памяти (placement new)
			// Это инициализирует строки mark и comfortability корректно
			new (ptr) Node(data);
		}
		ptr->next = NULL;
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
		// Увеличиваем счётчик кол-ва записей в списке
		this->count++;
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
		// Очистка консоли
		cout << "\033[2J\033[1;1H";

		// Настройка шапки таблицы
		cout << setfill('-') << setw(85) << "" << endl; // Разделительная линия
		cout << setfill(' ');

		cout << left << setw(5) << " №"
			<< setw(20) << "Марка"
			<< setw(18) << "Комфорт"
			<<right<< setw(12) << "Надежность"
			<< setw(15) << "Расход (л)"
			<< setw(12) << "Цена ($)" << endl;

		cout << setfill('-') << setw(85) << "" << endl;
		cout << setfill(' ');

		int i = 1;
		for (Node* ptr = this->head; ptr != NULL; ptr = ptr->next)
		{
			cout << left << setw(2) << i << ") " // Номер
				<< setw(20) << ptr->data.mark
				<< setw(18) << ptr->data.comfortability;

			// Числа лучше выравнивать по правому краю внутри их колонок, 
			// но для простоты оставим left, если колонки широкие
			cout<<right << setw(12) << ptr->data.reliability
				<< setw(15) << fixed << setprecision(1) << ptr->data.fconsumption
				<< setw(12) << fixed << setprecision(3) << ptr->data.price << endl;
			cout << setfill('-') << setw(85) << "" << endl;
			cout << setfill(' ');
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
		if (ptr != NULL) {
			// 2. Вызываем конструктор вручную в выделенной памяти (placement new)
			// Это инициализирует строки mark и comfortability корректно
			new (ptr) Node(data);
		}
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
		if (temp != NULL) {
			// 2. Вызываем конструктор вручную в выделенной памяти (placement new)
			// Это инициализирует строки mark и comfortability корректно
			new (temp) Node(first->data);
		}	
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
		if ((ptr->data.fconsumption) == input || ptr->data.price == input || ptr->data.reliability == input)
		{
			result.push_back(list[i]->data);
		}
		i++;
	}
	return result;
}
// Фильтр по числовым полям
List filter(List& list, bool(*func)(Node*, Node*), double item)
{
	// Инициализируем список для вывода результатов поиска
	List result;
	int i = 0;
	Node* temp = (Node*)(malloc(sizeof(Node)));
	temp->data = { item,item,(int)item };
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
//Чтение структуры из файла
void readStruct(List& list)
{
	Node* car = (Node*)malloc(sizeof(Node));
	// Переменная для работы с файлом
	FILE* file;
	// Переменная для обозначения конца файла
	long i = 0, fEnd;
	// Открываем бинарный файл для чтения 							
	fopen_s(&file, "data.bin", "rb");
	if (file != NULL)
	{
		// Перемещаем курсор в конец файла.
		fseek(file, 0, SEEK_END);
		// Функция выдаст конечное положнние курсора относительно начала файла в байтах.				
		fEnd = ftell(file);
		while (i < fEnd)
		{
			// Перемещаемся от начала (SEEK_SET) файла на i длинн структуры
			fseek(file, i, SEEK_SET);
			// Считываем из файла 1 структуру размера Auto			
			fread(car, sizeof(Auto), 1, file);
			// Добавляем в список прочитанную структуру
			list.push_back(car->data);
			i += sizeof(Auto);
		}
		// Закрываем файл
		fclose(file);
		free(car);
	}
}
//Запись структуры в файл
void writeStruct(List list)
{
	// Переменная для работы с файлом
	FILE* f;
	fopen_s(&f, "data.bin", "wb");
	for (Node* ptr = list.head; ptr != NULL; ptr = ptr->next)
	{
		// Записываем в файл		
		fwrite(ptr, sizeof(Auto), 1, f);
	}
	// Закрываем файл						
	fclose(f);
}
// Сравнение определённых полей структуры для сортровки по возрастанию
bool AscByMark(Node* a, Node* b)
{
	string strA = a->data.mark;
	string strB = b->data.mark;
	transform(strA.begin(), strA.end(), strA.begin(), tolower);
	transform(strB.begin(), strB.end(), strB.begin(), tolower);
	return strA < strB;
}
bool AscByComfort(Node* a, Node* b)
{
	string strA = a->data.comfortability;
	string strB = b->data.comfortability;
	transform(strA.begin(), strA.end(), strA.begin(), tolower);
	transform(strB.begin(), strB.end(), strB.begin(), tolower);
	return strA < strB;
}
bool AscByFuel(Node* a, Node* b)
{
	return a->data.fconsumption <= b->data.fconsumption;
}
bool AscByPrice(Node* a, Node* b)
{
	return a->data.price <= b->data.price;
}
bool AscByReliability(Node* a, Node* b)
{
	return a->data.reliability <= b->data.reliability;
}
// Сравнение определённых полей структуры для сортровки по убыванию
bool DescByMark(Node* a, Node* b)
{
	string strA = a->data.mark;
	string strB = b->data.mark;
	transform(strA.begin(), strA.end(), strA.begin(), tolower);
	transform(strB.begin(), strB.end(), strB.begin(), tolower);
	return strA > strB;
}
bool DescByComfort(Node* a, Node* b)
{
	string strA = a->data.comfortability;
	string strB = b->data.comfortability;
	transform(strA.begin(), strA.end(), strA.begin(), tolower);
	transform(strB.begin(), strB.end(), strB.begin(), tolower);
	return strA > strB;
}
bool DescByFuel(Node* a, Node* b)
{
	return a->data.fconsumption >= b->data.fconsumption;
}
bool DescByPrice(Node* a, Node* b)
{
	return a->data.price >= b->data.price;
}
bool DescByReliability(Node* a, Node* b)
{
	return a->data.reliability >= b->data.reliability;
}
// Функция сортировки элементов до обозначенного
int partition(List list, int first, int last, bool(*func)(Node*, Node*))
{
	// Выбираем крайнюю запись в качестве опорной точки
	Node* pivot = list[last];

	// Переменная для наибольшего элемента
	int i = (first - 1);

	// Проходим записи списка
	// Сравнимаем при помощи функций с крайней записью
	for (int j = first; j < last; j++)
	{
		if (func(list[j], pivot))
		{

			// Если найден элемент меньше
			// То меняем его с наибольшим, записанным в i
			i++;

			// Меняем записи по индексам i и j местами
			list.swap(list[i], list[j]);
		}
	}

	// Меняем точку опоры с наибольшим элементом в i
	list.swap(list[i + 1], list[last]);

	// Возвращаем точку раздела
	return (i + 1);
}
// Функция сортировки
void quickSort(List& list, int first, int last, bool(*func)(Node*, Node*))
{
	// Проверка на заполненность списка
	if (first < last)
	{
		// pi это точка разделения списка		
		int pi = partition(list, first, last, func);

		// Отдельно сортируем элементы до и после
		// разделителя pi
		quickSort(list, first, pi - 1, func);
		quickSort(list, pi + 1, last, func);
	}
}
int main()
{
	setlocale(LC_ALL, ".1251");
	// Инициализируем список
	List list;
	// Инициализируем переменную для переходов по меню
	int menu;
	menu = NULL;
	// Инициализируем переменную для записи компьютеров
	Auto car;
	// Попытка считать данные с файла
	readStruct(list);
	// Цикл для меню
	while (menu != 27)
	{
		// Проверка на существование записей в списке
		if (list.count == 0)
		{
			while (true)
			{
				cout << "\033[2J\033[1;1H";
				cout << "База данных не найдена!\n\n";
				cout << "1.Добавить машину\n";
				cout << "2.Выйти\n";
				menu = _getch();
				if (menu == 50)
				{
					exit(0);
				}
				else if (menu == 49)
				{
					menu = 50;
					break;
				}
			}
		}
		if (menu != 50)
		{
			// Выводим главное меню
			cout << "\033[2J\033[1;1H"; // Очистка консоли
			cout << "Выберите действие!\n\n";
			cout << "1.Список машин\n";
			cout << "2.Добавить\n";
			cout << "3.Изменить\n";
			cout << "4.Удалить\n";
			cout << "5.Вывести перечень авто согласно требованиям\n\n";
			cout << "Нажмите Esc чтобы сохранить и выйти\n";
			// Считываем нажатую клавишу
			menu = _getch();
		}
		switch (menu)
		{
			// SHOW LIST			
		case 49:
		{

			while (menu != 2)
			{
				menu = NULL;
				cout << "\033[2J\033[1;1H"; // Очистка консоли
				list.Show();
				cout << '\n';
				cout << "Выберите действие!\n\n";
				cout << "1.Поиск\n";
				cout << "2.Сортировка\n";
				cout << "3.Фильтр\n";
				switch (menu = _getch())
				{
					// SEARCH
				case 49:
				{
					menu = NULL;
					cout << "\033[2J\033[1;1H"; // Очистка консоли					
					cout << "Выберите действие!\n\n";
					cout << "1. Искать по марке/комфортности\n";
					cout << "2. Искать по характеристикам\n";
					switch (_getch())
					{
						// Поиск по марке
					case 49:
					{
						string s;
						// Очистка консоли									
						cout << "\033[2J\033[1;1H";
						cout << "Введите искомое значение: ";
						cin >> s;
						List result = search(list, s);
						if (result.count != 0)
							result.Show();
						else
						{
							cout << "\033[2J\033[1;1H";
							cout << "Таких машин не найдено!\n\n";
						}
						_getch();
						result.ClearList();
					}
					break;
					// Поиск по числам
					case 50:
					{
						List result;
						float s;
						cout << "\033[2J\033[1;1H";
						cout << "Введите искомое значение: ";
						if (cin >> s)
							result = search(list, s);
						if (result.count != 0)
							result.Show();
						else
						{
							cout << "\033[2J\033[1;1H";
							cout << "Машин с такими характеристиками не найдено\n\n";
						}
						_getch();
						result.ClearList();
					}
					break;
					}
					break;
				}
				// SORT
				case 50:
				{
					menu = NULL;
					// Флаг для определения в каком порядке сортировать
					int flag = 0;
					while (menu != 1)
					{
						list.Show();
						cout << '\n';
						cout << "Сортировать по ...\n\n";
						cout << "1.Марке\n";
						cout << "2.Комфортности\n";
						cout << "3.Расходу топлива\n";
						cout << "4.Надёжности\n";
						cout << "5.Цене\n";
						switch (menu = _getch())
						{
							// сортировка по марке
						case 49:
						{
							menu = NULL;
							if (flag == 0)
							{
								quickSort(list, 0, list.count - 1, AscByMark);
								flag++;
							}
							else
							{
								quickSort(list, 0, list.count - 1, DescByMark);
								flag = 0;
							}
							break;
						}
						// сортировка по комфортности
						case 50:
						{

							menu = NULL;
							if (flag == 0)
							{
								quickSort(list, 0, list.count - 1, AscByComfort);
								flag++;
							}
							else
							{
								quickSort(list, 0, list.count - 1, DescByComfort);
								flag = 0;
							}
							break;
						}
						// сортировка по расходу топлива
						case 51:
						{

							menu = NULL;
							if (flag == 0)
							{
								quickSort(list, 0, list.count - 1, AscByFuel);
								flag++;
							}
							else
							{
								quickSort(list, 0, list.count - 1, DescByFuel);
								flag = 0;
							}
							break;
						}
						// сортировка по надёжности
						case 52:
						{

							menu = NULL;
							if (flag == 0)
							{
								quickSort(list, 0, list.count - 1, AscByReliability);
								flag++;
							}
							else
							{
								quickSort(list, 0, list.count - 1, DescByReliability);
								flag = 0;
							}
							break;
						}
						// сортировка по цене
						case 53:
						{

							menu = NULL;
							if (flag == 0)
							{
								quickSort(list, 0, list.count - 1, AscByPrice);
								flag++;
							}
							else
							{
								quickSort(list, 0, list.count - 1, DescByPrice);
								flag = 0;
							}
							break;
						}
						// Выход в предыдущее меню (27 — Esc)
						case 27:
							menu = 1;
							break;
						}
					}
					break;
				}
				// FILTER
				case 51:
				{
					menu = NULL;
					List result;
					result.ClearList();
					result = list;
					while (menu != 1)
					{
						result.Show();
						cout << '\n';
						cout << "Фильтровать по ...\n\n";
						cout << "1.Марке/Комфортности\n";
						cout << "2.Расходу топлива\n";
						cout << "3.Надёжности\n";
						cout << "4.Цене\n";
						switch (menu = _getch())
						{
							// фильтр по текстовым полям
						case 49:
						{
							string input;
							result.Show();
							cout << '\n';
							cout << "Введите текст:\n\n";
							cin >> input;
							result = search(result, input);
							if (result.count != 0)
								menu = NULL;
							else
							{
								cout << "\033[2J\033[1;1H";
								cout << "Машины не найдены!\n\n";
								_getch();
								menu = 1;
							}
							break;
						}
						// фильтр по расходу топлива
						case 50:
						{
							while (menu != 2)
							{
								float input = NULL;
								result.Show();
								cout << '\n';
								cout << "Расход топлива на 100 км должен быть:\n\n";
								cout << "1.Меньше чем:\n";
								cout << "2.Больше чем:\n";
								switch (_getch())
								{
								case 49:
								{
									result.Show();
									cout << '\n';
									cout << "Расход топлива на 100 км должен быть:\n\n";
									cout << "Меньше чем: ";
									if (cin >> input)
										result = filter(result, AscByFuel, input);
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Машины не найдены!\n\n";
										_getch();
										menu = 1;
									}
									if (result.count != 0)
										menu = NULL;
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Машины не найдены!\n\n";
										_getch();
										menu = 1;
									}
								}
								break;
								case 50:
								{
									result.Show();
									cout << '\n';
									cout << "Расход топлива на 100 км должен быть:\n\n";
									cout << "Больше чем: ";
									if (cin >> input)
										result = filter(result, DescByFuel, input);
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Машины не найдены!\n\n";
										_getch();
										menu = 1;
									}
									if (result.count != 0)
										menu = NULL;
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Машины не найдены!\n\n";
										_getch();
										menu = 1;
									}
								}
								break;
								// Выход в предыдущее меню (27 — Esc)
								case 27:
								{
									menu = 2;
									break;
								}
								}
								cin.clear();
								cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
								if (menu == 1)
									break;
							}
						}
						// filter by reliability
						case 51:
						{
							while (menu != 2)
							{
								float input = NULL;
								result.Show();
								cout << '\n';
								cout << "Надёжность должна быть\n\n";
								cout << "1.Меньше чем:\n";
								cout << "2.Больше чем:\n";
								switch (_getch())
								{
								case 49:
								{
									result.Show();
									cout << '\n';
									cout << "Надёжность должна быть:\n\n";
									cout << "Меньше чем: ";
									if (cin >> input)
										result = filter(result, AscByReliability, input);
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Машины не найдены!\n\n";
										_getch();
										menu = 1;
									}
									if (result.count != 0)
										menu = NULL;
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Машины не найдены!\n\n";
										_getch();
										menu = 1;
									}
								}
								break;
								case 50:
								{
									result.Show();
									cout << '\n';
									cout << "Надёжность должна быть:\n\n";
									cout << "Больше чем: ";
									if (cin >> input)
										result = filter(result, DescByReliability, input);
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Машины не найдены!\n\n";
										_getch();
										menu = 1;
									}
									if (result.count != 0)
										menu = NULL;
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Машины не найдены!\n\n";
										_getch();
										menu = 1;
									}
								}
								break;
								case 27:
								{
									menu = 2;
									break;
								}
								}
								cin.clear();
								cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
								if (menu == 1)
									break;
							}
						}
						// filter by Price
						case 53:
						{
							while (menu != 2)
							{
								float input = NULL;
								result.Show();
								cout << '\n';
								cout << "Стоимость авто должна быть:\n\n";
								cout << "1. Меньше чем:\n";
								cout << "2. Больше чем:\n";
								switch (_getch())
								{
								case 49:
								{
									result.Show();
									cout << '\n';
									cout << "Стоимость авто должна быть:\n\n";
									cout << "Меньше чем: ";
									if (cin >> input)
										result = filter(result, AscByPrice, input);
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Машины не найдены!\n\n";
										_getch();
										menu = 1;
									}
									if (result.count != 0)
										menu = NULL;
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Машины не найдены!\n\n";
										_getch();
										menu = 1;
									}
								}
								break;
								case 50:
								{
									result.Show();
									cout << '\n';
									cout << "Стоимость авто должна быть:\n\n";
									cout << "Больше чем: ";
									if (cin >> input)
										result = filter(result, DescByPrice, input);
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Машины не найдены!\n\n";
										_getch();
										menu = 1;
									}
									if (result.count != 0)
										menu = NULL;
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Машины не найдены!\n\n";
										_getch();
										menu = 1;
									}
								}
								break;
								case 27:
								{
									menu = 2;
									break;
								}
								}
								cin.clear();
								cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
								if (menu == 1)
									break;
							}
						}
						// Выход в предыдущее меню (27 — Esc)
						case 27:
						{
							menu = 1;
							break;
						}
						}
					}
					break;
				}
				// Выход в предыдущее меню (27 — Esc)
				case 27:
				{
					menu = 2;
					break;
				}
				}
			}
			break;
		}
		// ADD
		case 50:
		{
			// Вызываем функцию добавления и вручную вводим все данные
			if (car.AutoInput())
				// Записанный пк добавляем в список
				list.push_back(car);
			// Возвращаемся в главное меню
			menu = 2;
			break;
		}
		// EDIT
		case 51:
		{
			menu = NULL;
			// Цикл для проверки ввода
			while (true)
			{
				list.Show();
				cout << "Введите порядковый номер записи, которую вы хотите изменить:\n";
				// Проверка на корректность введённых данных
				if (!tryInputNumber(menu))
				{
					menu = 27;
					break;
				}
				else if (menu <= list.count && menu > 0)
				{
					break;
				}
				else
				{
					cout << "\033[2J\033[1;1H" << "Неккоректные данные! Введите снова";
					_getch();
					cin.clear();
					cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				}
			}
			if (menu != 27)
			{
				// Вводим новые данные для выбранной записи
				if (car.AutoInput())
				{

					// Удаляем выбранную запись
					list.erase(menu - 1);
				// Вставляем на её место новую
				list.insert(menu - 1, car);
				cout << "Для продолжения нажмите любуе клавишу";
				_getch();
				}
			}
				menu = NULL;
			break;
		}
		// DELETE
		case 52:
		{
			// Цикл для проверки вводимых значений
			while (true)
			{
				list.Show();
				cout << "Введите порядковый номер записи, которую вы хотите удалить:\n";
				if (!tryInputNumber(menu))
				{
					menu = 27;
					break;
				}
				else if ( menu <= list.count && menu > 0)
				{
					break;
				}
				else
				{
					cout << "\033[2J\033[1;1H" << "Неккоректные данные! Введите снова";
					_getch();
					cin.clear();
					cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				}
			}
			if (menu != 27)
			{
				list.erase(menu - 1);
				menu = NULL;
				cout << "\033[2J\033[1;1H"; // Очистка консоли
				cout << "Для продолжения нажмите любую клавишу";
				_getch();
			}
			menu = NULL;
			break;
		}
		// Выход из приложения (27 — Esc)
		case 27:
		{
			// Сохранение внесённых изменений (запись текущего списка в файл)
			writeStruct(list);
			// Очистка списка
			list.ClearList();
			exit(0);
			break;
		}
		}
	}
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
