template <class Key, class Item>
class Dictionary::Node
{
public:
	Node(Key key, Item item)
	{
		this->item = item;
		this->key = key;
	}
	~Node()
	{
		delete nextPtr;
	}
	Node(const Node& arg)
	{
		key = arg.key;
		item = arg.item;
		if (arg.nextPtr != nullptr)
			nextPtr = new Node(*(arg.nextPtr));
	}
	Node(Node &&) = delete;
	Node & operator =(Node &&) = delete;

	static Item * lookupRec(Key key, Node* node)
	{
		if (!node)
		{
			return nullptr;
		}
		else if (key == node->key)
		{
			return &node->item;
		}
		else
		{
			return lookupRec(key, node->nextPtr);
		}
	}
	static void insertRec(Key key, Item item, Node* node)
	{
		if (!node)
		{
			node = new Node(key, item);
		}
		else if(node->key == key)
		{
			node->item = item;
		}
		else
		{
			insertRec(key, item, node->nextPtr);
		}
	}
	static void removeRec(Key key, Node* node)
	{
		if (node->key == key)
		{
			Node* tmp = node->nextPtr;
			delete node;
			node = tmp;
		} 
		else
		{
			removeRec(key, node->nextPtr);
		}
	}
private:
	Key key;
	Item item;
	Node* nextPtr;
};


template <class Key, class Item>
Dictionary::Dictionary()
{
}


template <class Key, class Item>
Dictionary::~Dictionary()
{
}


template <class Key, class Item>
Dictionary::Dictionary(Dictionary& arg)
{
	root = new Node(*(arg.root));
}


template <class Key, class Item>
Dictionary::Dictionary(Dictionary&& arg)
{
	root = arg.root;
	arg.root = nullptr;
}

template <class Key, class Item>
Dictionary & Dictionary::operator=(const Dictionary &copy)
{
	if (this != &copy)
	{
		delete root;
		if (copy.root == nullptr)
		{
			root = nullptr;
		}
		else
		{
			root = new Node(*(copy.root));
		}
	}
	return *this;
}

template <class Key, class Item>
Dictionary & Dictionary::operator=(Dictionary && t2)
{
	root = t2.root;
	t2.root = nullptr;
	return *this;
}

template <class Key, class Item>
void Dictionary::insert(Key key, Item item)
{
	Node::insertRec(key, item, root);
}

template <class Key, class Item>
Dictionary::Item * Dictionary::lookup(Key key)
{
	return Node::lookupRec(key, root);
}

template <class Key, class Item>
void Dictionary::remove(Key key)
{
	Node::removeRec(key, root);
}
