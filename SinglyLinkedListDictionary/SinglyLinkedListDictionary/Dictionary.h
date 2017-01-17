#ifndef SLL_DICTIONARY_H
#define SLL_DICTIONARY_H

#include <string>

template <class Key, class Item>
class Dictionary
{
public:
	Dictionary() = default;
	~Dictionary();
	Dictionary(Dictionary&);
	Dictionary(Dictionary &&);
	Dictionary & operator =(const Dictionary &);
	Dictionary & operator = (Dictionary &&);
	void insert(Key, Item);
	Item * lookup(Key);
	void remove(Key);

private:
	class Node;
	Node* root = nullptr;
};

#include "Dictionary.cpp"
#endif