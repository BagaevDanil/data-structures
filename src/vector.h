#pragma once
#include <iostream>

using namespace std;

template <class T>
class TVector
{

private:
    T* _Arr;
    int _SizeVector;
    int _SizeMemory;
    int _MagFactor = 2;

    struct Run
    {
        int indexStart;
        int length;
    };

    int GetMinrun(int n);
    void sortInsertionPart(T* arr, int indexFirst, int indexLast);
    void merge(T* arr, int firstIndexStart, int firstLenght, int secondIndexStart, int secondLenght);

public:
    TVector();
    ~TVector();

    void Add(int position, T value); //
    void AddFront(T value); //
    void AddBack(T value); //
    void Delete(int position); //
    void DeleteFront(); //
    void DeleteBack(); // 
    void Print() const; //
    std::string ToString() const;
    const int& GetSizeVector() const; //
    const int& GetSizeMemory() const; //

    void SortTimsort(); //
    void BubbleSort(); //
    void RandomMix(); //
    bool IsSort() const; //
    void ClearVector(); //
    const T& GetBack() const;
    const T& GetFront() const;
    const T& operator[] (const int index);
};


template<class T>
const T& TVector<T>::operator[](const int index)
{
    return _Arr[index];
}


template <class T>
TVector<T>::TVector() : _SizeMemory(1), _SizeVector(0)
{
    _Arr = new T[_SizeMemory];
}


template<class T>
TVector<T>::~TVector()
{
    delete[] _Arr;
}


template<class T>
void TVector<T>::Add(int position, T value)
{
    if (position < 0 || position > _SizeVector) {
        throw exception("Position outside the vector size range!");
    }

    if (_SizeMemory == _SizeVector) {
        _SizeMemory *= _MagFactor;
        T* newArr = new T[_SizeMemory];

        for (int i = 0; i < _SizeVector; i++) {
            newArr[i] = _Arr[i];
        }
        delete[] _Arr;
        _Arr = newArr;
    }

    _SizeVector++;
    for (int i = _SizeVector - 1; i > position; i--) {
        _Arr[i] = _Arr[i - 1];
    }
    _Arr[position] = value;
}

template<class T>
void TVector<T>::Print() const
{
    if (m_sizeVector == 0)
    {
        cout << "[ Empty vector ]";
        return;
    }
    cout << "[ ";
    for (int i = 0; i < m_sizeVector; i++) {
        cout << m_arr[i] << " ";
    }
    cout << "]";
}

template<class T>
void TVector<T>::AddFront(T value)
{
    Add(0, value);
}

template<class T>
void TVector<T>::AddBack(T value)
{
    Add(_SizeVector, value);
}

template<class T>
void TVector<T>::Delete(int position)
{
    if (position < 0 || position >= _SizeVector) {
        throw exception("Position outside the vector size range!");
    }

    _SizeVector--;
    if (_SizeMemory > 2 * _SizeVector * _MagFactor)
    {
        _SizeMemory /= _MagFactor;
        T* newArr = new T[_SizeMemory];

        for (int i = 0; i < _SizeVector; i++) {
            newArr[i] = _Arr[i];
        }
        delete[] _Arr;
        _Arr = newArr;
    }

    for (int i = position; i < _SizeVector; i++) {
        _Arr[i] = _Arr[i + 1];
    }
}

template<class T>
void TVector<T>::DeleteFront()
{
    Delete(0);
}

template<class T>
void TVector<T>::DeleteBack()
{
    Delete(_SizeVector - 1);
}

template<class T>
const int& TVector<T>::GetSizeVector() const
{
    return _SizeVector;
}

template<class T>
const int& TVector<T>::GetSizeMemory() const
{
    return _SizeMemory;
}

template<class T>
int TVector<T>::GetMinrun(int n)
{
    int r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

template<class T>
void TVector<T>::sortInsertionPart(T* arr, int indexFirst, int indexLast)
{
    for (int i = indexFirst + 1; i < indexLast; ++i)
    {
        T current = arr[i];
        int j = i - 1;
        while ((j >= indexFirst) && (current > arr[j])) { // ToDo sawap()
            T num = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = num;
            --j;
        }
    }
}

template<class T>
void TVector<T>::merge(T* arr, int firstIndexStart, int firstLenght, int secondIndexStart, int secondLenght)
{
    T* temporary = new T[firstLenght];

    for (int i = 0; i < firstLenght; i++) {
        temporary[i] = arr[firstIndexStart + i];
    }

    int firstIndexMerge = 0;
    int secondIndexMerge = secondIndexStart;
    int arrIndex = firstIndexStart;

    while (arrIndex < secondIndexStart + secondLenght - 1) {
        if (arr[secondIndexMerge] > temporary[firstIndexMerge]) {
            arr[arrIndex] = temporary[firstIndexMerge];
            firstIndexMerge++;
        }
        else {
            arr[arrIndex] = arr[secondIndexMerge];
            secondIndexMerge++;
        }

        if (secondIndexMerge == secondIndexStart + secondLenght) {
            if (firstIndexMerge != firstLenght) {
                for (int i = firstIndexMerge; i < firstLenght; i++) {
                    arr[i - firstIndexMerge + arrIndex + 1] = temporary[i];
                }
                arrIndex = secondIndexStart + secondLenght;
            }
        }
        if (firstIndexMerge == firstLenght) {
            arrIndex = secondIndexStart + secondLenght;
        }
        arrIndex++;
    }
    delete[] temporary;
}

template<class T>
void TVector<T>::SortTimsort() {
    int minrun = GetMinrun(_SizeVector);
    TVector<Run> queueRun; // ToDo

    int indexStart = 0;
    while (indexStart < _SizeVector - 1) {
        int indexFirst = indexStart;
        int indexLast = indexFirst + 1;

        bool nextStep = true;
        while (nextStep)
        {
            if (_Arr[indexFirst] > _Arr[indexLast]) {
                nextStep = false;
            }
            if (indexLast - indexStart < minrun) {
                nextStep = true;
            }
            if (indexLast == _SizeVector - 1) {
                nextStep = false;
            }

            if (nextStep) {
                indexFirst++;
                indexLast++;
            }
        }

        if (indexLast == _SizeVector - 2) {
            indexLast++;
        }

        sortInsertionPart(_Arr, indexStart, indexLast + 1);

        Run newRun;
        newRun.indexStart = indexStart;
        newRun.length = indexLast - indexStart;
        queueRun.AddBack(newRun);

        indexStart = indexLast;

        while (queueRun.GetSizeVector() >= 3) {
            Run x = queueRun.GetBack();
            queueRun.DeleteBack();
            Run y = queueRun.GetBack();
            queueRun.DeleteBack();
            Run z = queueRun.GetBack();
            queueRun.DeleteBack();

            if (z.length >= x.length + y.length && y.length >= x.length) {
                queueRun.AddBack(z);
                queueRun.AddBack(y);
                queueRun.AddBack(x);
                break;
            }
            else if (z.length >= x.length + y.length) {
                if (x.indexStart < y.indexStart) {
                    swap(x.indexStart, y.indexStart);
                    swap(x.length, y.length);
                }
                merge(_Arr, y.indexStart, y.length, x.indexStart, x.length);
                queueRun.AddBack(z);
                y.length = y.length + x.length;
                queueRun.AddBack(y);
            }
            else {
                if (y.indexStart < z.indexStart) {
                    swap(y.indexStart, z.indexStart);
                    swap(y.length, z.length);
                }
                merge(_Arr, z.indexStart, z.length, y.indexStart, y.length);
                z.length = z.length + y.length;
                queueRun.AddBack(z);
                queueRun.AddBack(x);
            }
        }
    }

    while (queueRun.GetSizeVector() > 1) {
        Run x = queueRun.GetFront();
        queueRun.DeleteFront();
        Run y = queueRun.GetFront();
        queueRun.DeleteFront();
        if (x.indexStart > y.indexStart) {
            swap(x.indexStart, y.indexStart);
            swap(x.length, y.length);
        }
        if (y.indexStart != x.indexStart + x.length) {
            queueRun.AddBack(y);
            queueRun.AddBack(x);
            continue;
        }
        merge(_Arr, x.indexStart, x.length, y.indexStart, y.length);
        x.length = x.length + y.length;
        queueRun.AddBack(x);
    }
}

template<class T>
void TVector<T>::BubbleSort()
{
    for (int i = 0; i < _SizeVector - 1; i++) {
        for (int j = 0; j < _SizeVector - i - 1; j++) {
            if (_Arr[j] < _Arr[j + 1]) {
                T temp = _Arr[j];
                _Arr[j] = _Arr[j + 1];
                _Arr[j + 1] = temp;
            }
        }
    }
}

template<class T>
void TVector<T>::RandomMix()
{
    for (int i = 0; i < _SizeVector; i++) {
        swap(_Arr[i], _Arr[rand() % _SizeVector]);
    }
}

template<class T>
void TVector<T>::ClearVector()
{
    _SizeMemory = 1;
    _SizeVector = 0;
    delete[] _Arr;
    _Arr = new T[1];
}

template<class T>
bool TVector<T>::IsSort() const
{
    for (int i = 0; i < _SizeVector - 1; i++) {
        if (_Arr[i] > _Arr[i + 1]) {
            return false;
        }
    }
    return true;
}

template<class T>
const T& TVector<T>::GetBack() const
{
    return _Arr[_SizeVector - 1];
}

template<class T>
const T& TVector<T>::GetFront() const
{
    return _Arr[0];
}

template<class T>
std::string TVector<T>::ToString() const {
    std::string ans;

    if (_SizeVector == 0)
    {
        return "[ Empty vector ]";
    }
    ans = "[ ";
    for (int i = 0; i < _SizeVector; i++) {
        ans += to_string(_Arr[i]) + " ";
    }
    ans += "]";
    return ans;
}
