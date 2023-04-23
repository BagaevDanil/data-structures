#pragma once
#include <iostream>
using namespace std;

template <class ValT, class KeyT>
class TTreeAVL
{
private:

	template <class ValT, class KeyT>
	struct Node
	{
		KeyT Key;
		int KeySerialNumber;
		ValT Value;
		unsigned int Height;
		Node<ValT, KeyT>* Left;
		Node<ValT, KeyT>* Right;

		Node(KeyT key, ValT value) : Key(key), Value(value), Left(nullptr), Right(nullptr), Height(1) {}
	};

private:
	Node<ValT, KeyT>* _Head;
	int _Size = 0;

private:
	unsigned int GetHeight(Node<ValT, KeyT>* unit);
	int GetBalanceFactor(Node<ValT, KeyT>* node);
	void FixHeight(Node<ValT, KeyT>* node);
	Node<ValT, KeyT>* RotateRight(Node<ValT, KeyT>* node);
	Node<ValT, KeyT>* RotateLeft(Node<ValT, KeyT>* node);
	Node<ValT, KeyT>* Balance(Node<ValT, KeyT>* node);
	Node<ValT, KeyT>* InsertPrivate(Node<ValT, KeyT>* unit, KeyT key, ValT value);
	void PrintTreePrivate(Node<ValT, KeyT>* unit);
	Node<ValT, KeyT>* PrintPrivate(Node<ValT, KeyT>* unit);

	Node<ValT, KeyT>* FindMin(Node<ValT, KeyT>* node);
	Node<ValT, KeyT>* RemoveMin(Node<ValT, KeyT>* node);
	Node<ValT, KeyT>* RemovePrivate(Node<ValT, KeyT>* node, KeyT key);

	ValT* GetPrivate(Node<ValT, KeyT>* node, KeyT key);
	int GetkeySerialNumberPrivate(Node<ValT, KeyT>* node, KeyT key);
	KeyT GetkeyPrivate(Node<ValT, KeyT>* node, int Key);

	int AssignKeysPrivate(Node<ValT, KeyT>* unit, int keyMeaning);

public:
	void AssignKeys();
	TTreeAVL(KeyT key, ValT value);
	TTreeAVL();
	void Insert(KeyT key, ValT value);
	void Remove(KeyT key);
	void PrintTree();
	void Print();
	
	ValT* Get(KeyT k);
	const ValT& GetValue(KeyT k);
	int GetkeySerialNumber(KeyT key);
	KeyT GetKey(int key);
	bool Contains(KeyT key);

	int GetHeightTree();
	const int& GetSize();
};

template <class ValT, class KeyT>
const int& TTreeAVL<ValT, KeyT>::GetSize()
{
	return _Size;
}

template <class ValT, class KeyT>
int TTreeAVL<ValT, KeyT>::GetHeightTree() 
{
	if (!_Head) {
		return 0;
	}

	return max(GetHeight(_Head->Right), GetHeight(_Head->Left));
}

template <class ValT, class KeyT>
TTreeAVL<ValT, KeyT>::TTreeAVL(KeyT key, ValT value)
{
	_Head = new Node<T, KeyT>(key, value);
}

template <class ValT, class KeyT>
TTreeAVL<ValT, KeyT>::TTreeAVL() : _Head(nullptr) {}

template <class ValT, class KeyT>
unsigned int TTreeAVL<ValT, KeyT>::GetHeight(Node<ValT, KeyT>* unit)
{
	return unit ? unit->Height : 0;
}

template <class ValT, class KeyT>
int TTreeAVL<ValT, KeyT>::GetBalanceFactor(Node<ValT, KeyT>* unit)
{
	return GetHeight(unit->Right) - GetHeight(unit->Left);
}

template <class ValT, class KeyT>
void TTreeAVL<ValT, KeyT>::FixHeight(Node<ValT, KeyT>* unit)
{
	unsigned int InitChildLeft = GetHeight(unit->Left);
	unsigned int InitChildRight = GetHeight(unit->Right);
	unit->Height = (InitChildLeft > InitChildRight ? InitChildLeft : InitChildRight) + 1;
}

template <class ValT, class KeyT>
TTreeAVL<ValT, KeyT>::Node<ValT, KeyT>* TTreeAVL<ValT, KeyT>::RotateRight(Node<ValT, KeyT>* unit)
{
	Node<ValT, KeyT>* UnitLeftChild = unit->Left;

	unit->Left = UnitLeftChild->Right;
	UnitLeftChild->Right = unit;
	FixHeight(unit);
	FixHeight(UnitLeftChild);
	return(UnitLeftChild);
}

template <class ValT, class KeyT>
TTreeAVL<ValT, KeyT>::Node<ValT, KeyT>* TTreeAVL<ValT, KeyT>::RotateLeft(Node<ValT, KeyT>* unit)
{
	Node<ValT, KeyT>* UnitRightChild = unit->Right;

	unit->Right = UnitRightChild->Left;
	UnitRightChild->Left = unit;
	FixHeight(unit);
	FixHeight(UnitRightChild);
	return(UnitRightChild);
}

template <class ValT, class KeyT>
TTreeAVL<ValT, KeyT>::Node<ValT, KeyT>* TTreeAVL<ValT, KeyT>::Balance(Node<ValT, KeyT>* unit)
{
	FixHeight(unit);
	int BalanceFactor = GetBalanceFactor(unit);

	if (BalanceFactor == 2) { //RotateLeft
		if (GetBalanceFactor(unit->Right) < 0) { //BigRotateLeft
			unit->Right = RotateRight(unit->Right);
		}
			
		unit = RotateLeft(unit);
	}
	else if (BalanceFactor == -2) { //RotateRight
		if (GetBalanceFactor(unit->Left) > 0) { //BigRotateRight
			unit->Left = RotateLeft(unit->Left);
		}
		unit = RotateRight(unit);
	}
	return unit;
}

template <class ValT, class KeyT>
TTreeAVL<ValT, KeyT>::Node<ValT, KeyT>* TTreeAVL<ValT, KeyT>::InsertPrivate(Node<ValT, KeyT>* unit, KeyT key, ValT value)
{
	if (!unit) {
		return new Node<ValT, KeyT>(key, value);
	}

	if (key < unit->Key) {
		unit->Left = InsertPrivate(unit->Left, key, value);
	}
	else if (key > unit->Key) {
		unit->Right = InsertPrivate(unit->Right, key, value);
	}
	else {
		throw exception("A node with such a key already exists!");
	}

	return Balance(unit);
}

template <class ValT, class KeyT>
void TTreeAVL<ValT, KeyT>::Insert(KeyT key, ValT value)
{
	_Head = TTreeAVL<ValT, KeyT>::InsertPrivate(_Head, key, value);
	_Size++;
}

template <class ValT, class KeyT>
void TTreeAVL<ValT, KeyT>::PrintTreePrivate(Node<ValT, KeyT>* unit)
{
	if (!unit)
		return;
	cout << "\n\n\n[" << unit->Key << "," << unit->KeySerialNumber << "]" << unit->Value;
	cout << "\n|\t\\\n";
	if (!unit->Left)
		cout << "[null]";
	else
		cout << "[" << unit->Left->Key << "," << unit->Left->KeySerialNumber << "]" << unit->Left->Value;
	if (!unit->Right)
		cout << "\t[null]";
	else
		cout << "\t[" << unit->Right->Key << "," << unit->Right->KeySerialNumber << "]" << unit->Right->Value;

	PrintTreePrivate(unit->Right);
	PrintTreePrivate(unit->Left);
}

template <class ValT, class KeyT>
void TTreeAVL<ValT, KeyT>::PrintTree()
{
	Node<ValT, KeyT>* demo = _Head;
	PrintTreePrivate(demo);
}

template <class ValT, class KeyT>
TTreeAVL<ValT, KeyT>::Node<ValT, KeyT>* TTreeAVL<ValT, KeyT>::FindMin(Node<ValT, KeyT>* unit)
{
	return unit->Left ? FindMin(unit->Left) : unit;
}

template <class ValT, class KeyT>
TTreeAVL<ValT, KeyT>::Node<ValT, KeyT>* TTreeAVL<ValT, KeyT>::RemoveMin(Node<ValT, KeyT>* unit)
{
	if (unit->Left == 0) {
		return unit->Right;
	}

	unit->Left = RemoveMin(unit->Left);
	return Balance(unit);
}

template <class ValT, class KeyT>
TTreeAVL<ValT, KeyT>::Node<ValT, KeyT>* TTreeAVL<ValT, KeyT>::RemovePrivate(Node<ValT, KeyT>* unit, KeyT key)
{
	if (!unit) {
		throw exception("A node with such a key was not found!");
	}

	if (key < unit->Key) {
		unit->Left = RemovePrivate(unit->Left, key);
	}
	else if (key > unit->Key) {
		unit->Right = RemovePrivate(unit->Right, key);
	}
	else {
		auto* UnitLeftChild = unit->Left;
		auto* UnitRightChild = unit->Right;
		delete unit;

		if (!UnitRightChild)
			return UnitLeftChild;

		auto* minNode = FindMin(UnitRightChild);
		minNode->Right = RemoveMin(UnitRightChild);
		minNode->Left = UnitLeftChild;
		return Balance(minNode);
	}
	return Balance(unit);
}

template <class ValT, class KeyT>
void TTreeAVL<ValT, KeyT>::Remove(KeyT key)
{
	_Head = RemovePrivate(_Head, key);
	_Size--;
}

template <class ValT, class KeyT>
void TTreeAVL<ValT, KeyT>::Print()
{
	Node<ValT, KeyT>* demo = _Head;
	PrintPrivate(demo);
}

template <class ValT, class KeyT>
TTreeAVL<ValT, KeyT>::Node<ValT, KeyT>* TTreeAVL<ValT, KeyT>::PrintPrivate(Node<ValT, KeyT>* unit)
{
	if (unit == 0) {
		return unit;
	}

	unit->Left = PrintPrivate(unit->Left);
	cout << "[" << unit->Key << "]=>" << unit->Value << "  ";
	unit->Right = PrintPrivate(unit->Right);

	return(unit);
}

template <class ValT, class KeyT>
ValT* TTreeAVL<ValT, KeyT>::GetPrivate(Node<ValT, KeyT>* unit, KeyT key)
{
	if (!unit) {
		return nullptr;
	}

	if (key < unit->Key) {
		return GetPrivate(unit->Left, key);
	}
	else if (key > unit->Key) {
		return GetPrivate(unit->Right, key);
	}

	return &unit->Value;
}

template <class ValT, class KeyT>
ValT* TTreeAVL<ValT, KeyT>::Get(KeyT key)
{
	Node<ValT, KeyT>* demo = _Head;
	return GetPrivate(demo, key);
}

template <class ValT, class KeyT>
bool TTreeAVL<ValT, KeyT>::Contains(KeyT key)
{
	Node<ValT, KeyT>* demo = _Head;
	ValT* ans = GetPrivate(demo, key);
	if (!ans) {
		return false;
	}
	return true;
}

template <class ValT, class KeyT>
const ValT& TTreeAVL<ValT, KeyT>::GetValue(KeyT key)
{
	Node<ValT, KeyT>* demo = _Head;
	ValT* ans = GetPrivate(demo, key);
	if (!ans) {
		throw exception("A node with such a key was not found!");
	}
	return *ans;
}

template<class ValT, class KeyT>
void TTreeAVL<ValT, KeyT>::AssignKeys()
{
	AssignKeysPrivate(_Head, 0);
}

template<class ValT, class KeyT>
int TTreeAVL<ValT, KeyT>::AssignKeysPrivate(Node<ValT, KeyT>* unit, int key)
{
	if (!unit) {
		return key;
	}
	
	unit->KeySerialNumber = AssignKeysPrivate(unit->Left, key);
	return AssignKeysPrivate(unit->Right, unit->KeySerialNumber + 1);
}

template <class ValT, class KeyT>
int TTreeAVL<ValT, KeyT>::GetkeySerialNumberPrivate(Node<ValT, KeyT>* unit, KeyT key)
{
	if (!unit) {
		throw exception("A node with such a key was not found!");
	}

	if (key < unit->Key) {
		return(GetkeySerialNumberPrivate(unit->Left, key));
	}
	else if (key > unit->Key) {
		return(GetkeySerialNumberPrivate(unit->Right, key));
	}

	return unit->KeySerialNumber;
}

template <class ValT, class KeyT>
int TTreeAVL<ValT, KeyT>::GetkeySerialNumber(KeyT key)
{
	Node<ValT, KeyT>* demo = _Head;
	return GetkeySerialNumberPrivate(demo, key);
}

template<class ValT, class KeyT>
KeyT TTreeAVL<ValT, KeyT>::GetkeyPrivate(Node<ValT, KeyT>* unit, int key)
{
	if (!unit) {
		throw exception("A node with such a key was not found!");
	}

	if (key < unit->KeySerialNumber) {
		return(GetkeyPrivate(unit->Left, key));
	}
	else if (key > unit->KeySerialNumber) {
		return(GetkeyPrivate(unit->Right, key));
	}

	return unit->Key;
}

template<class ValT, class KeyT>
KeyT TTreeAVL<ValT, KeyT>::GetKey(int key)
{
	Node<ValT, KeyT>* demo = _Head;
	return GetkeyPrivate(demo, key);
}