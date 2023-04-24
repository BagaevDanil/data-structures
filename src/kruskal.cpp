#include "kruskal.h"
using namespace std;

template <class T>
void MyAlgorithms::bubbleSort(TVector<T>& arrEdge)
{
    int nEdge = arrEdge.GetSizeVector();
    for (int i = 0; i < nEdge - 1; i++) {
        for (int j = 0; j < nEdge - i - 1; j++) {
            if (arrEdge[j].FirstVertex()->Name() > arrEdge[j + 1].FirstVertex()->Name()) {
                swap(arrEdge[j], arrEdge[j + 1]);
            }
            else if (
                arrEdge[j].FirstVertex()->Name() == arrEdge[j + 1].FirstVertex()->Name() &&
                arrEdge[j].SecondVertex()->Name() > arrEdge[j + 1].SecondVertex()->Name()
            ) {
                swap(arrEdge[j], arrEdge[j + 1]);
            }
        }
    }
}

template <class T>
void MyAlgorithms::quickSort(TVector<T>& arrEdge, int first, int last)
{
    int left = first, right = last;
    T midEdge = ArrEdge[(left + right) / 2];
    do {
        while (
            arrEdge[left].FirstVertex().Name() == midEdge.FirstVertex().Name() &&
            arrEdge[left].SecondVertex().Name() < midEdge.SecondVertex().Name() ||
            arrEdge[left].FirstVertex().Name() < midEdge.FirstVertex().Name()
        ) {
            left++;
        }

        while (
            arrEdge[right].FirstVertex().Name() == midEdge.FirstVertex().Name() &&
            arrEdge[right].SecondVertex().Name() > midEdge.SecondVertex().Name() ||
            arrEdge[right].FirstVertex().Name() > midEdge.FirstVertex().Name()
        ) {
            right--;
        }

        if (left <= right) {
            swap(arrEdge[left++], arrEdge[right--]);
        }
    } while (left < right);

    if (first < right) {
        quickSort(arrEdge, first, right);
    }
    if (left < last) {
        quickSort(arrEdge, left, last);
    }
}


TVertex* MyAlgorithms::findMainParent(TVertex* defaultVertex)
{
    if (defaultVertex->Parent() != nullptr) {
        defaultVertex->Parent() = findMainParent(defaultVertex->Parent());
    }

    if (defaultVertex->Parent()) {
        return defaultVertex->Parent();
    }
    return defaultVertex;
}

void MyAlgorithms::mergeEdges(TVector<TEdge>& queueEdge, TVector<TEdge>& answerEdge)
{
    while (queueEdge.GetSizeVector() > 0) {
        TEdge defaultEdge = queueEdge.GetBack();
        TVertex* x = findMainParent(&defaultEdge.FirstVertex());
        TVertex* y = findMainParent(&defaultEdge.SecondVertex());
        if (x != y) {
            x->Parent() = y;
            answerEdge.AddBack(defaultEdge);
        }
        queueEdge.DeleteBack();
    }
}

TVector<TEdge> MyAlgorithms::kruskal(TVector<TEdge> arrEdges)
{
    TTreeAVL<TVertex, string> arrVertex;
    int nEdges = arrEdges.GetSizeVector();

    for (int i = 0; i < nEdges; i++) {
        string keyVertexFirst = arrEdges[i].FirstVertex().Name();
        string keyVertexSecond = arrEdges[i].SecondVertex().Name();
        int weight = arrEdges[i].Weight();

        if (!arrVertex.Contains(keyVertexFirst)) {
            arrVertex.Insert(keyVertexFirst, TVertex(keyVertexFirst));
        }
        if (!arrVertex.Contains(keyVertexSecond)) {
            arrVertex.Insert(keyVertexSecond, TVertex(keyVertexSecond));
        }
    }

    arrEdges.SortTimsort();
    TVector<TEdge> AnswerEdge;
    mergeEdges(arrEdges, AnswerEdge);
    return AnswerEdge;
}
