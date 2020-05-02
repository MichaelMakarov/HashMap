#include <iostream>
#include "HashMap.h"
#include <string>

int main()
{
	std::hash<const char*> hasher;

	auto list = {
		std::pair<const char*, int>("sdfsdf", 100),
		std::pair<const char*, int>("aaaaa", 200),
		std::pair<const char*, int>("sdqpqp", -145968),
		std::pair<const char*, int>("10200", 0),
		std::pair<const char*, int>("ooooprty", -132),
		std::pair<const char*, int>("iii", 10)
	};

	// инициализация через список
	HashMap<const char*, int> map(list);
	// вывод количества элементов
	std::cout << "Size: " << map.Size() << std::endl;
	// вставляем новые элементы
	std::pair<const char*, int> p("first", 123);
	map.Insert(p);
	std::pair<const char*, int> b("second", -45);
	map.Insert(b);

	// вывод значений по ключу
	std::cout << "First: " << map["first"] << std::endl;
	std::cout << "Second: " << map.At("second") << std::endl;
	std::cout << "Third:";
	try {
		std::cout << map.At("third") << std::endl;
	}
	catch (std::out_of_range ex)
	{
		std::cout << ex.what() << std::endl;
	}
	// создаём новый элемент в таблице по ключу со значением по-умолчанию 
	// (значение зависит от конструктора класса значения)
	map["third"];

	// выводим начения в консоль при помощи конст. итератора в обратном порядке
	std::cout << "\nBackward printing:" << std::endl;
	for (auto iter = map.CEnd() - 1; iter != map.CBegin() - 1; --iter)
	{
		std::cout << (*iter).first << std::ends << (*iter).second << std::endl;
	}

	// удаляем элемент по ключу
	map.Erase("iii");
	std::cout << "\nForward printing:\n";
	// выводим в консоль в прямом порядке
	for (auto iter = map.CBegin(); iter != map.CEnd(); ++iter)
	{
		std::cout << (*iter).first << std::ends << (*iter).second << std::endl;
	}

	// поиск по ключу для конст.итератора и вывод значения в консоль
	std::cout << "\nThird: " << (*map.CFind("third")).second << std::endl;

	// очистка и вывод в консоль
	std::cout << "\nClearing.\nPrinting:\n";
	map.Clear();
	for (auto iter = map.Begin(); iter != map.End(); ++iter)
	{
		std::cout << (*iter).first << std::ends << (*iter).second << std::endl;
	}
	
	std::vector<std::pair<const char*, double>> array = {
		std::pair<const char*, double>("q", 0.000000001),
		std::pair<const char*, double>("qq", 0.00000001),
		std::pair<const char*, double>("qqq", 0.0000001),
		std::pair<const char*, double>("qqqq", 0.000001),
		std::pair<const char*, double>("qqqqq", 0.00001),
		std::pair<const char*, double>("qqqqqq", 0.0001),
		std::pair<const char*, double>("qqqqqqq", 0.001),
		std::pair<const char*, double>("qqqqqqqq", 0.01),
		std::pair<const char*, double>("qqqqqqqqq", 0.1),
		std::pair<const char*, double>("qqqqqqqqqq", 1.0)
	};
	// инициализация через итераторы вектора
	HashMap<const char*, double> table(array.begin(), array.end(), hasher);

	std::cout << "\n------------------------\nPrinting:\n";
	for (auto iter = table.CBegin(); iter != table.CEnd(); ++iter)
		std::cout << (*iter).first << std::ends << (*iter).second << std::endl;

	return 0;
}