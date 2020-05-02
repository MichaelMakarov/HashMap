#pragma once
#include <functional>
#include <vector>
#include <iterator>
#include <utility>
#include <iostream>


#define E_NUMBER 100	// размер таблицы



template<class KeyType, class ValueType, class HashType = std::hash<KeyType>>
class HashMap
{
	using Pair = std::pair<KeyType, ValueType>;
private:
	// массив 
	std::vector<Pair> Table;
	// функция хеширования
	HashType Function;
	// количество элементов в таблице
	size_t Count = 0;

	// возвращает значение по указанному ключу
	bool Get(const KeyType& key, ValueType& value)
	{
		size_t hesh = Function(key);
		for (std::pair<KeyType, ValueType>& pair : Table)
		{
			if (pair.first == key)
			{
				value = pair.second;
				return true;
			}
			if (Function(pair.first) > hesh)
				break;
		}
		return false;
	}

public:
	// конструктор по-умолчанию
	HashMap() {
		HashType function;
		Function = function;
	}
	// конструктор с хешером
	HashMap(const HashType& hasher) {
		Function = hasher;
	}

	// конструктор на основе итераторов vector
	template<class SeqIterator>
	HashMap(
		SeqIterator begin,
		SeqIterator end)
	{
		HashType function;
		Function = function;

		for (auto iter = begin; iter != end; ++iter)
		{
			if (Empty())
			{
				Table.push_back(*iter);
				Count++;
			}
			else
				Insert(*iter);
		}
	}
	// конструктор на основе итераторов vector
	template<class SeqIterator>
	HashMap(
		SeqIterator begin,
		SeqIterator end,
		const HashType& hasher)
	{
		Function = hasher;

		for (auto iter = begin; iter != end; ++iter)
		{
			if (Empty())
			{
				Table.push_back(*iter);
				Count++;
			}
			else
				Insert(*iter);
		}
	}

	// конструктор на основе std::initializer_list
	HashMap(
		std::initializer_list<Pair>& list)
	{
		HashType function;
		Function = function;

		for (auto iter = list.begin(); iter != list.end(); ++iter)
		{
			if (Empty())
			{
				Table.push_back(*iter);
				Count++;
			}
			else
				Insert(*iter);
		}
	}
	// конструктор на основе std::initializer_list с хешером
	HashMap(
		std::initializer_list<Pair>& list,
		const HashType& hasher)
	{
		Function = hasher;

		for (auto iter = list.begin(); iter != list.end(); ++iter)
		{
			if (Empty())
			{
				Table.push_back(*iter);
				Count++;
			}
			else
				Insert(*iter);
		}
	}

	// деструктор
	~HashMap() { Clear(); }
	// очищение таблицы
	void Clear()
	{
		Table.clear();
		Count = 0;
		Invalidate();
	}

	// возвращает количество элементов в таблице
	size_t Size()
	{
		return Count;
	}
	// возвращает значение, является ли таблица пустой
	bool Empty()
	{
		return Count > 0 ? false : true;
	}
	// возвращает используемую функцию хеширования
	const HashType HashFunction()
	{
		return Function;
	}

	// добавление нового элемента в таблицу
	void Insert(const Pair& pair)
	{
		size_t hesh = Function(pair.first);
		for (auto iter = Table.begin(); iter != Table.end(); ++iter)
		{
			if (iter->first == pair.first)
				return;;
			if (Function(iter->first) > hesh)
			{
				Table.insert(iter, pair);
				Count++;
				Invalidate();
				return;
			}
		}
		Table.push_back(pair);
		Count++;
		Invalidate();
	}

	// удаление элемента по ключу
	void Erase(const KeyType& key)
	{
		size_t hesh = Function(key);

		for (auto iter = Table.begin(); iter != Table.end(); ++iter)
		{
			if (iter->first == key)
			{
				Table.erase(iter);
				Count--;
				Invalidate();
				return;
			}
			if (Function(iter->first) > hesh)
				break;
		}
	}

	// возвращает значение по указанному ключу
	const ValueType& At(const KeyType& key)
	{
		ValueType value;
		if (Get(key, value))
			return value;
		else
			throw std::out_of_range("Such key does not exist!");
	}

	// перегрузка индексирующего оператора
	ValueType& operator[] (const KeyType& key)
	{
		ValueType value;
		if (Get(key, value))
			return value;
		else {
			std::pair<KeyType, ValueType> pair(key, value);
			Insert(pair);
		}
	}

	//--------------------------------
	class Iterator : public std::iterator<std::bidirectional_iterator_tag, Pair>
	{
	private:

		Pair* Item;

	public:
		Iterator() :Item(nullptr) {}
		Iterator(Pair* item) : Item(item) {}
		Iterator(const Iterator& self) : Item(self.Item) {}
		bool operator != (const Iterator const& other) { return Item != other.Item; }
		bool operator == (const Iterator const& other) { return Item == other.Item; }

		Pair& operator * () { return *Item; }
		Pair* operator -> () { return Item; }

		Iterator operator = (const Iterator& self) { Item = self.Item; return *this; }

		Iterator& operator ++ () { ++Item; return *this; }
		Iterator& operator -- () { --Item; return *this; }

		Iterator& operator + (const size_t shift) {
			for (size_t i = 0; i < shift; ++i) ++Item;
			return *this;
		}
		Iterator& operator - (const size_t shift) {
			for (size_t i = 0; i < shift; ++i) --Item;
			return *this;
		}
	};
	class ConstIterator : public std::iterator<std::bidirectional_iterator_tag, Pair>
	{
	private:

		Pair* Item;

	public:
		ConstIterator() : Item(nullptr) {}
		ConstIterator(Pair* item) : Item(item) {}
		ConstIterator(const ConstIterator& self) : Item(self.Item) { }

		bool operator != (const ConstIterator const& other) { return Item != other.Item; }
		bool operator == (const ConstIterator const& other) { return Item == other.Item; }

		const Pair& operator * () { return *Item; }
		const Pair* operator -> () { return Item; }

		ConstIterator operator = (const ConstIterator& self) { Item = self.Item; return *this; }

		ConstIterator& operator ++ () { ++Item; return *this; }
		ConstIterator& operator -- () { --Item; return *this; }

		ConstIterator& operator + (const size_t shift) {
			for (size_t i = 0; i < shift; ++i) ++Item;
			return *this;
		}
		ConstIterator& operator - (const size_t shift) {
			for (size_t i = 0; i < shift; ++i) --Item;
			return *this;
		}
	};

private:
	Iterator Front;
	Iterator Back;
	ConstIterator CFront;
	ConstIterator CBack;

	void Invalidate()
	{
		Front = Iterator(
			reinterpret_cast<Pair*>(
				Table.data()
				));
		Back = Begin() + Count;
		CFront = ConstIterator(
			reinterpret_cast<Pair*>(
				Table.data()
				));
		CBack = CBegin() + Count;
	}

public:
	// итератор на первый элемент
	Iterator Begin()
	{
		return Front;
	}
	// итератор на конец
	Iterator End()
	{
		return Back;
	}
	// итератор на первый элемент
	ConstIterator CBegin()
	{
		return CFront;
	}
	// итератор на конец
	ConstIterator CEnd()
	{
		return CBack;
	}
	// возвращение итератора по ключу
	Iterator Find(const KeyType& key)
	{
		for (auto iter = Begin(); iter != End(); ++iter)
		{
			if ((*iter).first == key)
				return iter;
		}
		return End();
	}
	// возвращение конст. итератора по ключу
	ConstIterator CFind(const KeyType& key)
	{
		for (auto iter = CBegin(); iter != CEnd(); ++iter)
		{
			if ((*iter).first == key)
				return iter;
		}
		return CEnd();
	}

};

