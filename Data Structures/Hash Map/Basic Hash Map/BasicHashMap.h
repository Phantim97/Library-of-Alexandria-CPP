//
// Created by Timothy Coelho on 8/3/24.
//

#ifndef DS_BASICHASHMAP_H
#define DS_BASICHASHMAP_H
#include <string>
#include <iostream>

template <typename K, typename V>
class HashNode
{
private:
	//Key-value order
	K _key;
	V _value;

	//next bucket with same key
	HashNode* _next;
public:
	HashNode(const K& key, const V& value)
	{
		_key = key;
		_value = value;
		_next = nullptr;
	}

	K getKey() const
	{
		return _key;
	}

	V getValue() const
	{
		return _value;
	}

	void setValue(V value)
	{
		_value = value;
	}

	HashNode* getNext() const
	{
		return _next;
	}

	void setNext(HashNode* next)
	{
		_next = next;
	}
};

static constexpr size_t TABLE_SIZE = 10;

// Default hash function class
template <typename K>
struct KeyHash {
	unsigned long operator()(const K& key) const
	{
		return reinterpret_cast<unsigned long>(key) % TABLE_SIZE;
	}
};

// Hash map class template
template <typename K, typename V, typename F = KeyHash<K>>
class HashMap
{
private:
	// hash table
	HashNode<K, V>** _table;
	F _hashFunc;
public:
	HashMap()
	{
		// construct zero initialized hash table of size
		_table = new HashNode<K, V> * [TABLE_SIZE]();
	}

	~HashMap()
	{
		// destroy all buckets one by one
		for (int i = 0; i < TABLE_SIZE; ++i)
		{
			HashNode<K, V>* entry = _table[i];
			while (entry != NULL)
			{
				HashNode<K, V>* prev = entry;
				entry = entry->getNext();
				delete prev;
			}
			_table[i] = NULL;
		}
		// destroy the hash table
		delete[] _table;
	}

	bool get(const K& key, V& value)
	{
		unsigned long hashValue = _hashFunc(key);
		HashNode<K, V>* entry = _table[hashValue];

		while (entry != NULL)
		{
			if (entry->getKey() == key)
			{
				value = entry->getValue();
				return true;
			}
			entry = entry->getNext();
		}
		return false;
	}

	void put(const K& key, const V& value)
	{
		unsigned long hashValue = _hashFunc(key);
		HashNode<K, V>* prev = NULL;
		HashNode<K, V>* entry = _table[hashValue];

		while (entry != NULL && entry->getKey() != key)
		{
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == NULL)
		{
			entry = new HashNode<K, V>(key, value);
			if (prev == NULL)
			{
				// insert as first bucket
				_table[hashValue] = entry;
			}
			else
			{
				prev->setNext(entry);
			}
		}
		else
		{
			// just update the value
			entry->setValue(value);
		}
	}

	void remove(const K& key)
	{
		unsigned long hashValue = _hashFunc(key);
		HashNode<K, V>* prev = NULL;
		HashNode<K, V>* entry = _table[hashValue];

		while (entry != NULL && entry->getKey() != key)
		{
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == nullptr)
		{
			// key not found
			return;
		}
		else
		{
			if (prev == nullptr)
			{
				// remove first bucket of the list
				_table[hashValue] = entry->getNext();
			}
			else
			{
				prev->setNext(entry->getNext());
			}

			delete entry;
		}
	}
};

struct MyKeyHash
{
	unsigned long operator()(const int& k) const
	{
		return k % 10;
	}
};
#endif //DS_BASICHASHMAP_H
