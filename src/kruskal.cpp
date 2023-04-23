#include <iostream>
#include "treeAVL.h"
#include "queue.h"
#include "vertex.h"
#include "vector.h"
#include "edge.h"

using namespace std;

void swapEdge(TEdge& first, TEdge& second) // ToDo swap
{
    TEdge defaultEdge;
    
    defaultEdge = first;
    first = second;
    second = defaultEdge;
}

void bubbleSortMyVectorEdge(TVector<TEdge>& arrEdge)
{
    int nEdge = arrEdge.GetSizeVector();
    for (int i = 0; i < nEdge - 1; i++)
    {
        for (int j = 0; j < nEdge - i - 1; j++)
        {
            if (arrEdge[j].FirstVertex()->Name() > arrEdge[j + 1].FirstVertex()->Name()) {
                swapEdge(arrEdge[j], arrEdge[j + 1]);
            }
            else if (
                (arrEdge[j].FirstVertex()->Name() == arrEdge[j + 1].FirstVertex()->Name()) &&
                (arrEdge[j].SecondVertex()->Name() > arrEdge[j + 1].SecondVertex()->Name())
            ) {
                swapEdge(arrEdge[j], arrEdge[j + 1]);
            }
        }
    }
}

void quickSort(TVector<TEdge>& ArrEdge, int first, int last)
{
    int left = first, right = last;
    TEdge midEdge = ArrEdge[(left + right) / 2];
    do
    {
        while (
            (ArrEdge[left].FirstVertex()->Name() < midEdge.FirstVertex()->Name()) ||
            (ArrEdge[left].FirstVertex()->Name() == midEdge.FirstVertex()->Name() && ArrEdge[left].SecondVertex()->Name() < midEdge.SecondVertex()->Name())
        ) {
            left++;
        }
            
        while (
            (ArrEdge[right].FirstVertex()->Name() > midEdge.FirstVertex()->Name()) ||
            (ArrEdge[right].FirstVertex()->Name() == midEdge.FirstVertex()->Name() && ArrEdge[right].SecondVertex()->Name() > midEdge.SecondVertex()->Name())
        ) {
            right--;
        }
            
        if (left <= right) {
            swap(ArrEdge[left], ArrEdge[right]); // ToDo inline
            left++;
            right--;
        }
    } while (left < right);

    if (first < right) quickSort(ArrEdge, first, right);
    if (left < last) quickSort(ArrEdge, left, last);
}


TVertex* findMainParent(TVertex* DefaultVertex)
{
    if (DefaultVertex->Parent() != nullptr) {
        DefaultVertex->Parent() = findMainParent(DefaultVertex->Parent());
    }

    if (DefaultVertex->Parent()) {
        return DefaultVertex->Parent();
    }
    return DefaultVertex;
}

void mergeEdges(TVector<TEdge>& QueueEdge, TVector<TEdge>& AnswerEdge)
{
    while (QueueEdge.GetSizeVector() > 0)
    {
        TEdge defaultEdge = QueueEdge.GetBack();
        TVertex* x = findMainParent(defaultEdge.FirstVertex());
        TVertex* y = findMainParent(defaultEdge.SecondVertex());
        if (x != y) {
            x->Parent() = y;
            // y->amount += x->amount;
            AnswerEdge.AddBack(defaultEdge);
        }
        QueueEdge.DeleteBack();
    }
}

void PrintEdges(TVector<TEdge>& ArrEdge)
{
    std::cout << endl;
    int allWeight = 0;
    quickSort(ArrEdge, 0, ArrEdge.GetSizeVector() - 1);

    for (int i = 0; i < ArrEdge.GetSizeVector(); i++)
    {
        TEdge newEdge = ArrEdge[i];
        std::cout << newEdge.FirstVertex()->Name() << " " << newEdge.SecondVertex()->Name() << " " << newEdge.Weight() << endl;
        allWeight += newEdge.Weight();
    }
    std::cout << "\nWeight: " << allWeight;
}

void printAdjacencyMatrix(TTreeAVL<TVertex, string>& arrVertex, int n, TVector<TEdge>& ArrEdge)
{
    arrVertex.AssignKeys();

    int inf = -1;

    int adjacencyMatrixArr[50][50];
    for (int i = 0; i < 50; i++)
        for (int j = 0; j < 50; j++)
            adjacencyMatrixArr[i][j] = inf;

    for (int i = 0; i < ArrEdge.GetSizeVector(); i++)
    {
        TEdge newEdge = ArrEdge[i];
        int firstIndex = arrVertex.GetkeySerialNumber(newEdge.FirstVertex()->Name());
        int secondIndex = arrVertex.GetkeySerialNumber(newEdge.SecondVertex()->Name());
        adjacencyMatrixArr[firstIndex][secondIndex] = adjacencyMatrixArr[secondIndex][firstIndex] = newEdge.Weight();
    }

    cout << "\t";
    for (int i = 0; i < n; i++)
        cout << arrVertex.GetKey(i) << "\t";
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        cout << arrVertex.GetKey(i) << "\t";
        for (int j = 0; j < n; j++)
        {
            adjacencyMatrixArr[i][j] == -1 ? cout << ".\t" : cout << adjacencyMatrixArr[i][j] << "\t";
        }
        cout << endl;
    }
}

TVector<TEdge>* Kruskal(TVector<TEdge>& inputEdges)
{
    TTreeAVL<TVertex, string> arrVertex;
    TVector<TEdge> queueEdge;
    int nVertex = 0, nEdges = inputEdges.GetSizeVector();

    for (int i = 0; i < nEdges; i++) {
        string keyVertexFirst = inputEdges[i].FirstVertex()->Name();
        string keyVertexSecond = inputEdges[i].SecondVertex()->Name();
        int weight = inputEdges[i].Weight();

        if (!arrVertex.Contains(keyVertexFirst)) {
            arrVertex.Insert(keyVertexFirst, TVertex(keyVertexFirst));
            nVertex++;
        }
        if (!arrVertex.Contains(keyVertexSecond)) {
            arrVertex.Insert(keyVertexSecond, TVertex(keyVertexSecond));
            nVertex++;
        }
        
        TVertex* fisrt = arrVertex.Get(keyVertexFirst);
        TVertex* second = arrVertex.Get(keyVertexSecond);
        queueEdge.AddBack(TEdge(fisrt, second, weight));
    }

    queueEdge.SortTimsort();
    TVector<TEdge> *AnswerEdge = new TVector<TEdge>;
    mergeEdges(queueEdge, *AnswerEdge);
    return AnswerEdge;
}


int main()
{
    TVector<TEdge> arr;
    int nEdges;
    cout << "Num Edges: ";
    cin >> nEdges;

    for (int i = 0; i < nEdges; i++) {
        string keyVertexFirst, keyVertexSecond;
        int weight;

        cin >> keyVertexFirst >> keyVertexSecond >> weight;
        arr.AddBack(TEdge(new TVertex(keyVertexFirst), new TVertex(keyVertexSecond), weight));
    }

    auto* ans = Kruskal(arr);
    PrintEdges(*ans);

    return 0;
} 

/*
    6
    1 2 4
    2 3 9
    3 5 3
    4 1 7
    1 5 1
    3 4 2

    TTreeAVL<TVertex, string> arrVertex;
    int nEdges, nVertex = 0;
    TVector<TEdge> queueEdge;
    cout << "Num Edges: ";
    cin >> nEdges;

    for (int i = 0; i < nEdges; i++)
    {
        string keyVertexFirst, keyVertexSecond;
        int weight;

        cin >> keyVertexFirst >> keyVertexSecond >> weight;

        if (!arrVertex.Get(keyVertexFirst))
        {
            TVertex newVertex(keyVertexFirst);
            arrVertex.Insert(keyVertexFirst, newVertex);
            nVertex++;
        }
        if (!arrVertex.Get(keyVertexSecond))
        {
            TVertex newVertex(keyVertexSecond);
            arrVertex.Insert(keyVertexSecond, newVertex);
            nVertex++;
        }

        TVertex *x = (arrVertex.Get(keyVertexFirst));
        TVertex *y = (arrVertex.Get(keyVertexSecond));

        TEdge newEdge(x, y, weight);
        queueEdge.AddBack(newEdge);
    }


    queueEdge.SortTimsort();
    TVector<TEdge> AnswerEdge;
    mergeEdges(queueEdge, AnswerEdge);

    PrintEdges(AnswerEdge);
    //cout << "\n\n";
    printAdjacencyMatrix(arrVertex, nVertex, AnswerEdge);


    return 0;
*/