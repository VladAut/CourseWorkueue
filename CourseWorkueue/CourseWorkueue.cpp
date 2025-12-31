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
#include <map>
#include <cwctype> // Для iswprint
#include <windows.h>

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
	wint_t ch; // Используем широкий тип для поддержки кириллицы

	result[0] = '\0';

	while (true) {
		ch = _getwch(); // Читаем широкий символ (работает с RU/EN)

		// 1. Обработка Esc
		if (ch == 27) return false;

		// 2. Обработка Enter
		if (ch == 13) {
			if (currentLen == 0) continue;
			cout << endl;
			result[currentLen] = '\0';
			return true;
		}

		// 3. Обработка Backspace
		if (ch == 8) {
			if (currentLen > 0) {
				currentLen--;
				result[currentLen] = '\0';
				cout << "\b \b";
			}
		}
		// 4. Игнорируем функциональные клавиши (стрелки и т.д.)
		else if (ch == 0 || ch == 224 || ch == 0xE0) {
			_getwch(); // Пропускаем второй код
		}
		// 5. Печатаемые символы
		else if (iswprint(ch)) {
			if (currentLen < maxSize - 1) {
				// Преобразуем широкий символ обратно в char для записи в массив
				// В Windows с русской локалью это сработает корректно
				result[currentLen] = (char)ch;
				currentLen++;

				// Чтобы символ отобразился корректно, выводим его через wcout или printf
				printf("%c", (char)ch);
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
		head->~Node();
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
		tail->~Node();
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
		ptr->~Node();
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
			<< right << setw(12) << "Надежность"
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
			cout << right << setw(12) << ptr->data.reliability
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
		temp->~Node();
		free(temp);
	}
};
//Поиск по марке автомобиля
List search(List& list, string s)
{
	List result;

	// 1. Приводим поисковый запрос (s) к нижнему регистру один раз
	string query = s;
	transform(query.begin(), query.end(), query.begin(), ::tolower);

	int i = 0;
	for (Node* ptr = list.head; ptr != NULL; ptr = ptr->next)
	{
		// 2. Копируем марку во временную строку и тоже приводим к нижнему регистру
		string markStr = ptr->data.mark;
		transform(markStr.begin(), markStr.end(), markStr.begin(), ::tolower);

		// 3. Ищем вхождение подстроки
		if (markStr.find(query) != string::npos)
		{
			result.push_back(ptr->data);
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
	string s;
	if (flag == 1)
		s = "Отличная";
	else if (flag == 2)
		s = "Хорошая";
	else if (flag == 3)
		s = "Удовлетворительная";
	// Поэлементно проходим список
	for (Node* ptr = list.head; ptr != NULL; ptr = ptr->next)
	{
		// Сравниваем результаты выполнения функции поиска из библиотеки для работы со строками
		if (((((string)(ptr->data.comfortability))).find(s) != string::npos))
		{
			result.push_back(list[i]->data);
		}
		i++;
	}
	return result;
}
// Поиск по численным полям
List search(List& list, double input)
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
	temp->~Node();
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
		car->~Node();
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
void FilterMenu(List& list)
{
	int mainMenuKey = 0;
	List result = list;

	while (mainMenuKey != 27)
	{ // 27 - Esc (выход из фильтрации)
		result.Show();
		cout << "\nФИЛЬТРАЦИЯ (Esc - вернуться назад)\n";
		cout << "1. По комфортности\n";
		cout << "2. По расходу топлива\n";
		cout << "3. По надёжности\n";
		cout << "4. По цене\n";
		cout << "0. Сбросить фильтры\n";

		mainMenuKey = _getch();

		switch (mainMenuKey)
		{
		case '1': { // Фильтр по комфортности
			int comfortType = 0;
			cout << "\nВыберите комфортность: 1-Отличная, 2-Хорошая, 3-Удовл.: ";
			char key = _getch();
			if (key >= '1' && key <= '3')
			{
				comfortType = key - '0'; // Превращаем символ в число
				result = search(result, comfortType);
			}
			break;
		}

		case '2':
		{ // Фильтр по расходу
			cout << "\n1. Меньше чем\n2. Больше чем\n";
			char subKey = _getch();
			double val = 0;

			cout << "Введите значение: ";
			if (tryInputDouble(val))
			{
				if (subKey == '1')
					result = filter(result, AscByFuel, val);
				else if (subKey == '2')
					result = filter(result, DescByFuel, val);
			}
			break;
		}
		case '3':
		{ // Фильтр по надёжности
			cout << "\n1. Меньше чем\n2. Больше чем\n";
			char subKey = _getch();
			int val = 0;

			cout << "Введите значение: ";
			if (tryInputNumber(val))
			{
				if (subKey == '1')
					result = filter(result, AscByReliability, val);
				else if (subKey == '2')
					result = filter(result, DescByReliability, val);
			}
			break;
		}
		case '4':
		{ // Фильтр по wtyt
			cout << "\n1. Меньше чем\n2. Больше чем\n";
			char subKey = _getch();
			double val = 0;

			// Используем вашу функцию tryInputDouble, чтобы Esc работал и здесь
			cout << "Введите значение: ";
			if (tryInputDouble(val))
			{
				if (subKey == '1')
					result = filter(result, AscByPrice, val);
				else if (subKey == '2')
					result = filter(result, DescByPrice, val);
			}
			break;
		}

		case '0':
		{ // Сброс
			result = list;
			cout << "\nФильтры сброшены!";
			_getch();
			break;
		}

		case 27: // Esc
			return;
		}

		// Проверка на пустой результат после фильтрации
		if (result.count == 0) {
			system("cls");
			cout << "Машины не найдены! Фильтр будет сброшен.\n";
			_getch();
			result = list;
		}
	}
}
void SortMenu(List& list)
{
	// Храним текущее состояние сортировки для каждого поля.
	// true = по возрастанию (Asc), false = по убыванию (Desc).
	map<int, bool> sortState;
	// Инициализируем все критерии как Ascending по умолчанию
	sortState[1] = true; // Mark
	sortState[2] = true; // Comfort
	sortState[3] = true; // Reliability
	sortState[4] = true; // Fuel
	sortState[5] = true; // Price

	while (true)
	{ // Бесконечный цикл, выход по Esc/0
		system("cls");
		list.Show(); // Показываем текущий список
		cout << "\n--- МЕНЮ СОРТИРОВКИ --- (Esc/0 - Назад)\n";
		cout << "Выберите поле для сортировки (повторное нажатие меняет порядок):\n";

		// Отображаем текущий порядок сортировки рядом с пунктом
		cout << "1. Марка         (" << (sortState[1] ? "А-Я" : "Я-А") << ")\n";
		cout << "2. Комфортность  (" << (sortState[2] ? "А-Я" : "Я-А") << ")\n";
		cout << "3. Надёжность    (" << (sortState[3] ? "min" : "max") << ")\n";
		cout << "4. Расход        (" << (sortState[4] ? "min" : "max") << ")\n";
		cout << "5. Цена          (" << (sortState[5] ? "min" : "max") << ")\n";
		cout << "--------------------------------\n";

		char choice = _getch();

		if (choice == '0' || choice == 27)
		{
			return; // Выход из функции меню
		}

		// Проверяем, является ли выбор валидной цифрой 1-5
		if (choice >= '1' && choice <= '5')
		{
			int key = choice - '0'; // Преобразуем '1' в 1

			// 1. Меняем состояние флага для выбранного пункта
			sortState[key] = !sortState[key];
			bool isAscending = sortState[key];

			// 2. Вызываем quickSort с соответствующим критерием
			switch (key)
			{
			case 1:
				quickSort(list, 0, list.count - 1, isAscending ? AscByMark : DescByMark);
				break;
			case 2:
				quickSort(list, 0, list.count - 1, isAscending ? AscByComfort : DescByComfort);
				break;
			case 3:
				quickSort(list, 0, list.count - 1, isAscending ? AscByReliability : DescByReliability);
				break;
			case 4:
				quickSort(list, 0, list.count - 1, isAscending ? AscByFuel : DescByFuel);
				break;
			case 5:
				quickSort(list, 0, list.count - 1, isAscending ? AscByPrice : DescByPrice);
				break;
			}
			// Цикл сразу начинается заново и показывает отсортированный список
		}
		// Если нажата другая клавиша, она просто игнорируется
	}
}
void SearchMenu(List& list)
{
	while (true)
	{
		system("cls");
		cout << "========= МЕНЮ ПОИСКА =========" << endl;
		cout << "1. Искать по марке" << endl;
		cout << "2. Искать по числовым характеристикам" << endl;
		cout << "-------------------------------" << endl;
		cout << "0. Назад (или Esc)" << endl;
		cout << "===============================" << endl;
		cout << "Ваш выбор: ";

		char choice = _getch();

		if (choice == '0' || choice == 27)
			return; // Выход в главное меню

		switch (choice)
		{
		case '1':
		{ // Поиск по марке (текст)
			char searchStr[20];
			system("cls");
			cout << "ПОИСК ПО МАРКЕ\n";
			cout << "Введите название (Esc для отмены): ";

			// Используем нашу безопасную функцию ввода char[]
			if (tryInputCharArray(searchStr, 20))
			{
				List result = search(list, searchStr);

				system("cls");
				if (result.count != 0)
				{
					cout << "Результаты поиска по запросу [" << searchStr << "]:\n";
					result.Show();
				}
				else
				{
					cout << "Машин марки '" << searchStr << "' не найдено.\n";
				}
				cout << "\nНажмите любую клавишу...";
				_getch();
			}
			break;
		}

		case '2':
		{ // Поиск по числам (цена, расход и т.д.)
			double val = 0;
			system("cls");
			cout << "ПОИСК ПО ХАРАКТЕРИСТИКАМ\n";
			cout << "Введите числовое значение для поиска: ";

			// Используем нашу безопасную функцию ввода double
			if (tryInputDouble(val))
			{
				List result = search(list, val);

				system("cls");
				if (result.count != 0)
				{
					cout << "Результаты поиска по значению [" << val << "]:\n";
					result.Show();
				}
				else {
					cout << "Машин с такими характеристиками не найдено.\n";
				}
				cout << "\nНажмите любую клавишу...";
				_getch();
			}
			break;
		}
		}
	}
}
void ComplexSearch(List& list)
{
	// Начинаем с копии всего списка
	List result = list;
	double inputNum = 0;
	// ШАГ 1: Поиск по марке
	system("cls");
	cout << "ШАГ 1: Введите желаемую марку (Esc - пропустить): " << flush;
	char searchMark[20]; // массив для ввода
	if (tryInputCharArray(searchMark, 20))
	{
		result = search(result, string(searchMark));
	}
	// ШАГ 2: Фильтр по комфортности
	if (result.count > 0) {
		system("cls");
		cout << "ШАГ 2: Выберите желаемую комфортность:\n";
		cout << "1. Отличная\n2. Хорошая\n3. Удовлетворительная\nEsc - пропустить\n";
		while (true)
		{
			int key = _getch();
			if (key == 27) break; // Пропустить по Esc
			if (key >= '1' && key <= '3')
			{
				result = search(result, key - '0');
				break;
			}
		}
	}
	// ШАГ 3: Фильтр по надёжности
	if (result.count > 0)
	{
		system("cls");
		cout << "ШАГ 3: Введите минимальную надёжность (лет) (Esc - пропустить): ";
		if (tryInputDouble(inputNum))
			result = search(result, inputNum);
	}
	// ШАГ 4: Фильтр по стоимости
	if (result.count > 0)
	{
		system("cls");
		cout << "ШАГ 4: Введите максимальную стоимость (Esc - пропустить): ";
		if (tryInputDouble(inputNum))
			result = search(result, inputNum);
	}
	// ШАГ 5: Фильтр по расходу топлива (ВОТ ОН)
	if (result.count > 0)
	{
		system("cls");
		cout << "ШАГ 5: Введите максимально допустимый расход (л/100км) (Esc - пропустить): ";
		if (tryInputDouble(inputNum))
		{
			result = search(result, inputNum);
		}
	}
	// ИТОГОВЫЙ ВЫВОД
	system("cls");
	if (result.count != 0)
	{
		cout << "РЕЗУЛЬТАТЫ ПОДБОРА (найдено " << result.count << " авто):\n";
		result.Show();
	}
	else
	{
		cout << "\n[!] К сожалению, по вашим требованиям ничего не найдено.\n";
	}
	cout << "\nНажмите любую клавишу для возврата в меню...";
	_getch();
	// Очистка временного списка result произойдет автоматически при выходе из области видимости
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
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
	while (true) // Основной бесконечный цикл приложения
	{
		system("cls");

		// 1. ПРОВЕРКА НА ПУСТОТУ БАЗЫ
		if (list.count == 0)
		{
			cout << "========================================" << endl;
			cout << "       СИСТЕМА УЧЕТА АВТОМОБИЛЕЙ        " << endl;
			cout << "========================================" << endl;
			cout << "\n [!] Внимание: База данных пуста.\n" << endl;
			cout << " 1. Добавить первую запись" << endl;
			cout << " 2. Выйти из программы" << endl;
			cout << "========================================" << endl;
			cout << " Выберите действие: ";

			char emptyChoice = _getch();
			if (emptyChoice == '2' || emptyChoice == 27)
				exit(0);
			if (emptyChoice == '1')
			{
				if (car.AutoInput())
					list.push_back(car);
				continue; // Возвращаемся в начало, чтобы перерисовать полноценное меню
			}
			continue;
		}
		// 2. ГЛАВНОЕ МЕНЮ
		cout << "========================================" << endl;
		cout << "            ГЛАВНОЕ МЕНЮ                " << endl;
		cout << "========================================" << endl;
		cout << " 1. [ Список автомобилей ]" << endl;
		cout << " 2. [ Добавить новую запись ]" << endl;
		cout << " 3. [ Изменить существующую запись]" << endl;
		cout << " 4. [ Удалить запись ]" << endl;
		cout << " 5. [ Подобрать авто по параметрам ]" << endl;
		cout << "----------------------------------------" << endl;
		cout << " Esc. Сохранить изменения и выйти" << endl;
		cout << "========================================" << endl;
		cout << " Ваш выбор: ";
		char mainMenuChoice = _getch();
		switch (mainMenuChoice)
		{
		case '1': // РАБОТА СО СПИСКОМ
		{
			while (true)
			{
				system("cls");
				list.Show();
				cout << "\n---------- ДЕЙСТВИЯ СО СПИСКОМ ----------" << endl;
				cout << " 1. Поиск | 2. Сортировка | 3. Фильтр | Esc. Назад" << endl;

				char subAction = _getch();
				if (subAction == 27)
					break; // Возврат в главное меню

				if (subAction == '1')
					SearchMenu(list);
				else if (subAction == '2')
					SortMenu(list);
				else if (subAction == '3')
					FilterMenu(list);
			}
			break;
		}

		case '2': // ДОБАВИТЬ
			system("cls");
			cout << "--- Регистрация нового автомобиля ---" << endl;
			if (car.AutoInput())
			{
				list.push_back(car);
				cout << "\nЗапись успешно добавлена!";
			}
			else
			{
				cout << "\nВвод отменен.";
			}
			_getch();
			break;

		case '3': // ИЗМЕНИТЬ
			// (Ваш откорректированный код редактирования)
		{
			int targetIdx = 0;
			while (true)
			{
				system("cls");
				list.Show();
				cout << "\nВведите номер записи для ИЗМЕНЕНИЯ (Esc - отмена): ";
				int inputVal = 0;
				if (!tryInputNumber(inputVal))
				{
					targetIdx = 27;
					break;
				}
				if (inputVal > 0 && inputVal <= list.count)
				{
					targetIdx = inputVal;
					break;
				}
				cout << "\n[Ошибка] Номер неверный!";
				_getch();
			}
			if (targetIdx != 27)
			{
				Auto newCar;
				system("cls");
				if (newCar.AutoInput())
				{
					list.erase(targetIdx - 1);
					list.insert(targetIdx - 1, newCar);
					cout << "\nОбновлено!";
				}
				_getch();
			}
		}
		break;

		case '4': // УДАЛИТЬ
			// (Ваш откорректированный код удаления)
		{
			system("cls");
			list.Show();
			cout << "\nВведите номер записи для УДАЛЕНИЯ (Esc - отмена): ";
			int delVal = 0;
			if (tryInputNumber(delVal) && delVal > 0 && delVal <= list.count)
			{
				list.erase(delVal - 1);
				cout << "\nЗапись удалена!";
			}
			else
			{
				cout << "\nОтмена или неверный номер.";
			}
			_getch();
		}
		break;

		case '5': // КОМПЛЕКСНЫЙ ПОИСК
			ComplexSearch(list);
			break;

		case 27: // ВЫХОД И СОХРАНЕНИЕ
			system("cls");
			cout << "Сохранение данных в файл..." << endl;
			writeStruct(list);
			list.ClearList();
			cout << "Готово." << endl;
			_getch();
			exit(0);
			break;
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
