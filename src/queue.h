#pragma once
#include <iostream>
#include "vector.h"

using namespace std;

template <class T>
class TQueue : private TVector<T>
{
public:
	void PushBack(T value);
	void PushFront(T value);
	void PopBack();
	void PopFront();
	bool IsEmpty() const;
	const int& Size() const;
	const T& Front() const;
	const T& Back() const;
};

template <class T>
void TQueue<T>::PushBack(T value)
{
	TVector<T>::AddBack(value);
}

template <class T>
void TQueue<T>::PushFront(T value)
{
	TVector<T>::AddFront(value);
}

template <class T>
void TQueue<T>::PopBack()
{
	TVector<T>::DeleteBack();
}

template <class T>
void TQueue<T>::PopFront()
{
	TVector<T>::DeleteFront();
}

template <class T>
bool TQueue<T>::IsEmpty() const
{
	return TVector<T>::IsEmpty();
}

template <class T>
const int& TQueue<T>::Size() const
{
	return TVector<T>::GetSizeVector();
}

template <class T>
const T& TQueue<T>::Back() const
{
	return TVector<T>::GetBack();
}

template <class T>
const T& TQueue<T>::Front() const
{
	return TVector<T>::GetFront();
}