﻿#pragma once
#include <iostream>
#include "treeAVL.h"
#include "queue.h"
#include "vertex.h"
#include "vector.h"
#include "edge.h"

using namespace std;

namespace MyAlgorithms {

    template <class T>
    void bubbleSort(TVector<T>& arrEdge);

    template <class T>
    void quickSort(TVector<T>& ArrEdge, int first, int last);

    TVertex* findMainParent(TVertex* defaultVertex);

    void mergeEdges(TVector<TEdge>& queueEdge, TVector<TEdge>& answerEdge);

    TVector<TEdge> kruskal(TVector<TEdge> arrEdges);
}