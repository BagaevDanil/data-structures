#pragma once
#include <iostream>
using namespace std;

template <class T, class KeyT>
class TreeAVL
{
private:
	//

	template <class T, class KeyT>
	class Node
	{
	public:
		KeyT key;
		int keySerialNumber;
		T value;
		unsigned int height;
		Node<T, KeyT>* left;
		Node<T, KeyT>* right;

		Node(KeyT Key, T Value)
		{
			this->key = Key;
			this->value = Value;
			left = right = nullptr;
			height = 1; //--------------------------------------------
		}
	};

	Node<T, KeyT>* m_head;
	unsigned int GetHeight(Node<T, KeyT>* Unit);
	int GetBalanceFactor(Node<T, KeyT>* p);
	void FixHeight(Node<T, KeyT>* p);
	Node<T, KeyT>* RotateRight(Node<T, KeyT>* p);
	Node<T, KeyT>* RotateLeft(Node<T, KeyT>* q);
	Node<T, KeyT>* Balance(Node<T, KeyT>* p);
	Node<T, KeyT>* InsertPrivate(Node<T, KeyT>* Unit, KeyT Key, T Value);
	void PrintTreePrivate(Node<T, KeyT>* Unit);
	Node<T, KeyT>* PrintPrivate(Node<T, KeyT>* Unit);

	Node<T, KeyT>* FindMin(Node<T, KeyT>* p);
	Node<T, KeyT>* RemoveMin(Node<T, KeyT>* p);
	Node<T, KeyT>* RemovePrivate(Node<T, KeyT>* p, KeyT k);

	T* GetPrivate(Node<T, KeyT>* p, KeyT k);
	int GetkeySerialNumberPrivate(Node<T, KeyT>* p, KeyT k);
	KeyT GetkeyPrivate(Node<T, KeyT>* p, int Key);

	int AssignKeysPrivate(Node<T, KeyT>* Unit, int KeyMeaning);

public:
	void AssignKeys();
	TreeAVL(KeyT Key, T Value);
	TreeAVL();
	void Insert(KeyT Key, T Value);
	void Remove(KeyT k);
	void PrintTree();
	void Print();
	
	T* Get(KeyT k);
	int GetkeySerialNumber(KeyT k);
	KeyT GetKey(int Key);
};

//-------------------------------------------------------------------------------\\

template <class T, class KeyT>
inline TreeAVL<T, KeyT>::TreeAVL(KeyT Key, T Value)
{
	m_head = new Node<T, KeyT>(Key, Value);
}

template <class T, class KeyT>
inline TreeAVL<T, KeyT>::TreeAVL()
{
	m_head = nullptr;
}

template <class T, class KeyT>
inline unsigned int TreeAVL<T, KeyT>::GetHeight(Node<T, KeyT>* Unit)
{
	return (Unit ? (Unit->height) : (0));
}

template <class T, class KeyT>
inline int TreeAVL<T, KeyT>::GetBalanceFactor(Node<T, KeyT>* Unit)
{
	return (GetHeight(Unit->right) - GetHeight(Unit->left));
}

template <class T, class KeyT>
inline void TreeAVL<T, KeyT>::FixHeight(Node<T, KeyT>* Unit)
{
	unsigned int InitChildLeft = GetHeight(Unit->left);
	unsigned int InitChildRight = GetHeight(Unit->right);
	Unit->height = ((InitChildLeft > InitChildRight) ? (InitChildLeft) : (InitChildRight)) + 1;
}

template <class T, class KeyT>
inline TreeAVL<T, KeyT>::Node<T, KeyT>* TreeAVL<T, KeyT>::RotateRight(Node<T, KeyT>* Unit)
{
	Node<T, KeyT>* UnitLeftChild = Unit->left;

    Unit->left = UnitLeftChild->right;
	UnitLeftChild->right = Unit;
	FixHeight(Unit);
	FixHeight(UnitLeftChild);
	return(UnitLeftChild);
}

template <class T, class KeyT>
inline TreeAVL<T, KeyT>::Node<T, KeyT>* TreeAVL<T, KeyT>::RotateLeft(Node<T, KeyT>* Unit)
{
	Node<T, KeyT>* UnitRightChild = Unit->right;

	Unit->right = UnitRightChild->left;
	UnitRightChild->left = Unit;
	FixHeight(Unit);
	FixHeight(UnitRightChild);
	return(UnitRightChild);
}

template <class T, class KeyT>
inline TreeAVL<T, KeyT>::Node<T, KeyT>* TreeAVL<T, KeyT>::Balance(Node<T, KeyT>* Unit)
{
	FixHeight(Unit); //--
	int BalanceFactor = GetBalanceFactor(Unit);

	if (BalanceFactor == 2) //RotateLeft
	{
		if (GetBalanceFactor(Unit->right) < 0) //BigRotateLeft
			Unit->right = RotateRight(Unit->right);
		Unit = RotateLeft(Unit);
	}
	else if (BalanceFactor == -2) //RotateRight
	{
		if (GetBalanceFactor(Unit->left) > 0) //BigRotateRight
			Unit->left = RotateLeft(Unit->left);
		Unit = RotateRight(Unit);
	}
	return Unit;
}

template <class T, class KeyT>
inline TreeAVL<T, KeyT>::Node<T, KeyT>* TreeAVL<T, KeyT>::InsertPrivate(Node<T, KeyT>* Unit, KeyT Key, T Value)
{
	if (!Unit)
		return (new Node<T, KeyT>(Key, Value));

	if (Key < Unit->key)
		Unit->left = InsertPrivate(Unit->left, Key, Value);
	else if (Key > Unit->key)
		Unit->right = InsertPrivate(Unit->right, Key, Value);
	else
		exit(666666);
	//PrintTree();
	//cout << "----------------------------------------" << endl;
	return (Balance(Unit));
}

template <class T, class KeyT>
inline void TreeAVL<T, KeyT>::Insert(KeyT Key, T Value)
{
	m_head = TreeAVL<T, KeyT>::InsertPrivate(m_head, Key, Value);
}

template <class T, class KeyT>
inline void TreeAVL<T, KeyT>::PrintTreePrivate(Node<T, KeyT>* Unit)
{
	if (!Unit)
		return;
	cout << "\n\n\n[" << Unit->key << "," << Unit->keySerialNumber << "]" << Unit->value;
	cout << "\n|\t\\\n";
	if (!Unit->left)
		cout << "[null]";
	else
		cout << "[" << Unit->left->key << "," << Unit->left->keySerialNumber << "]" << Unit->left->value;
	if (!Unit->right)
		cout << "\t[null]";
	else
		cout << "\t[" << Unit->right->key << "," << Unit->right->keySerialNumber << "]" << Unit->right->value;

	PrintTreePrivate(Unit->right);
	PrintTreePrivate(Unit->left);
}

template <class T, class KeyT>
inline void TreeAVL<T, KeyT>::PrintTree()
{
	Node<T, KeyT>* demo = m_head;
	TreeAVL<T, KeyT>::PrintTreePrivate(demo);
}

template <class T, class KeyT>
inline TreeAVL<T, KeyT>::Node<T, KeyT>* TreeAVL<T, KeyT>::FindMin(Node<T, KeyT>* Unit)
{
	return (Unit->left) ? (FindMin(Unit->left)) : (Unit);
}

template <class T, class KeyT>
inline TreeAVL<T, KeyT>::Node<T, KeyT>* TreeAVL<T, KeyT>::RemoveMin(Node<T, KeyT>* Unit)
{
	if (Unit->left == 0)
		return Unit->right;

	Unit->left = RemoveMin(Unit->left);
	return Balance(Unit);
}

template <class T, class KeyT>
inline TreeAVL<T, KeyT>::Node<T, KeyT>* TreeAVL<T, KeyT>::RemovePrivate(Node<T, KeyT>* Unit, KeyT Key)
{
	if (!Unit)
		exit(666666);

	if (Key < Unit->key)
		Unit->left = RemovePrivate(Unit->left, Key);
	else if (Key > Unit->key)
		Unit->right = RemovePrivate(Unit->right, Key);
	else
	{
		Node<T>* UnitLeftChild = Unit->left;
		Node<T>* UnitRightChild = Unit->right;
		delete Unit;
		if (!UnitRightChild)
			return UnitLeftChild;

		Node<T>* minNode = FindMin(UnitRightChild);
		minNode->right = RemoveMin(UnitRightChild);
		minNode->left = UnitLeftChild;
		return Balance(minNode);
	}
	return Balance(Unit);
}

template <class T, class KeyT>
inline void TreeAVL<T, KeyT>::Remove(KeyT Key)
{
	m_head = RemovePrivate(m_head, Key);
}

template <class T, class KeyT>
inline void TreeAVL<T, KeyT>::Print()
{
	Node<T, KeyT>* demo = m_head;
	PrintPrivate(demo);
}

template <class T, class KeyT>
inline TreeAVL<T, KeyT>::Node<T, KeyT>* TreeAVL<T, KeyT>::PrintPrivate(Node<T, KeyT>* Unit)
{
	if (Unit == 0)
		return Unit;

	//cout << "[" << Unit->key << "] " << Unit->value << " "; 

	Unit->left = PrintPrivate(Unit->left);
	//if (Unit->left)
		//cout << "[" << Unit->left->key << "] " << Unit->left->value << " ";
	
	
	//cout << "[" << Unit->key << "]=>" << Unit->value << "  ";------------------------------------------------------------------------------
	cout << "[" << Unit->key << "]=>" << Unit->value << "  ";

	Unit->right = PrintPrivate(Unit->right);
	//if (Unit->right)
		//cout << "[" << Unit->right->key << "] " << Unit->right->value << " ";

	return(Unit);
}

template <class T, class KeyT>
inline T* TreeAVL<T, KeyT>::GetPrivate(Node<T, KeyT>* Unit, KeyT Key)
{
	if (!Unit)
		return nullptr;

	if (Key < Unit->key)
		return(GetPrivate(Unit->left, Key));
	else if (Key > Unit->key)
		return(GetPrivate(Unit->right, Key));
	else
		return &Unit->value;
}

template <class T, class KeyT>
inline T* TreeAVL<T, KeyT>::Get(KeyT Key)
{
	Node<T, KeyT>* demo = m_head;
	return GetPrivate(demo, Key);
}

template<class T, class KeyT>
inline void TreeAVL<T, KeyT>::AssignKeys()
{
	AssignKeysPrivate(m_head, 0);
}

template<class T, class KeyT>
inline int TreeAVL<T, KeyT>::AssignKeysPrivate(Node<T, KeyT>* Unit, int Key)
{
	if (!Unit)
		return Key;
	
	Unit->keySerialNumber = AssignKeysPrivate(Unit->left, Key);

	return AssignKeysPrivate(Unit->right, Unit->keySerialNumber + 1);
}

template <class T, class KeyT>
inline int TreeAVL<T, KeyT>::GetkeySerialNumberPrivate(Node<T, KeyT>* Unit, KeyT Key)
{
	if (!Unit)
		exit(666666);

	if (Key < Unit->key)
		return(GetkeySerialNumberPrivate(Unit->left, Key));
	else if (Key > Unit->key)
		return(GetkeySerialNumberPrivate(Unit->right, Key));
	else
		return Unit->keySerialNumber;
}

template <class T, class KeyT>
inline int TreeAVL<T, KeyT>::GetkeySerialNumber(KeyT Key)
{
	Node<T, KeyT>* demo = m_head;
	return GetkeySerialNumberPrivate(demo, Key);
}

template<class T, class KeyT>
inline KeyT TreeAVL<T, KeyT>::GetkeyPrivate(Node<T, KeyT>* Unit, int Key)
{
	if (!Unit)
		exit(666666);

	if (Key < Unit->keySerialNumber)
		return(GetkeyPrivate(Unit->left, Key));
	else if (Key > Unit->keySerialNumber)
		return(GetkeyPrivate(Unit->right, Key));
	else
		return Unit->key;
}

template<class T, class KeyT>
inline KeyT TreeAVL<T, KeyT>::GetKey(int Key)
{
	Node<T, KeyT>* demo = m_head;
	return GetkeyPrivate(demo, Key);
}