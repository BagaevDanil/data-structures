#pragma once
#include <iostream>
#include <gtest/gtest.h>
#include "../src/vector.h"
#include "../src/queue.h"
#include "../src/treeAVL.h"
#include "../src/kruskal.h"
#include "../src/vertex.h"
#include "../src/edge.h"

using namespace std;

TEST(Kruskal, test) {
    TVector<TEdge> arr;
    int nEdges = 6;
    string keyVertexFirstArr[] = { "1", "2", "3", "4", "1", "3" };
    string keyVertexSecondArr[] = { "2", "3", "5", "1", "5", "4" };
    int weightArr[] = { 4, 9, 3, 7, 1, 2 };
    int ans = 26;

    for (int i = 0; i < nEdges; i++) {
        string keyVertexFirst = keyVertexFirstArr[i], keyVertexSecond = keyVertexSecondArr[i];
        int weight = weightArr[i];

        arr.AddBack(TEdge(TVertex(keyVertexFirst), TVertex(keyVertexSecond), weight));
    }
    auto ansEdge = MyAlgorithms::kruskal(arr);
    int prediction = 0;
    for (int i = 0; i < nEdges; i++) {
        prediction += ansEdge[i].Weight();
    }

    ASSERT_EQ(prediction, ans);
}

TEST(TreeAVL, Insert1) {
    TTreeAVL<int, int> tree;
    int arr[] = { 8, 11, 4, 1, 10, 7, 3, 15, 12, 5, 2, 6, 13, 9, 14 };
    int size = 15;

    for (int i = 0; i < size; i++) {
        tree.Insert(arr[i], i * arr[i]);
    }

    ASSERT_EQ(tree.GetSize(), size);
    ASSERT_TRUE(tree.GetHeightTree() <= 4);
}

TEST(TreeAVL, Insert2) {
    TTreeAVL<int, int> tree;
    int arr[] = { 8, 11, 4, 1, 10, 7, 3, 15, 12, 5, 2, 6, 13, 9, 14 };
    int size = 15;

    for (int i = 0; i < size; i++) {
        tree.Insert(arr[i], i * arr[i]);
    }

    ASSERT_THROW(tree.Insert(1, 0), exception);
}

TEST(TreeAVL, Remove1) {
    TTreeAVL<int, int> tree;
    int arr[] = { 16, 8, 11, 4, 1, 10, 7, 3, 15, 12, 5, 2, 6, 13, 17, 18, 9, 14 };
    int size = 18;

    for (int i = 0; i < size; i++) {
        tree.Insert(arr[i], i * arr[i]);
    }

    tree.Remove(1);
    tree.Remove(7);
    tree.Remove(4);
    tree.Remove(13);

    ASSERT_EQ(tree.GetSize(), size - 4);
    ASSERT_TRUE(tree.GetHeightTree() <= 4);
    ASSERT_THROW(tree.GetValue(7), exception);
    ASSERT_EQ(tree.GetValue(16), 0);
}

TEST(TreeAVL, Remove2) {
    TTreeAVL<int, int> tree;
    int arr[] = { 16, 8, 11, 4, 1, 10, 7, 3, 15, 12, 5, 2, 6, 13, 17, 18, 9, 14 };
    int size = 18;

    for (int i = 0; i < size; i++) {
        tree.Insert(arr[i], i * arr[i]);
    }

    ASSERT_THROW(tree.Remove(200), exception);
}

TEST(TreeAVL, GetValue) {
    TTreeAVL<int, int> tree;
    int arr[] = { 16, 8, 11, 4, 1, 10, 7, 3, 15, 12, 5, 2, 6, 13, 17, 18, 9, 14 };
    int size = 18;

    for (int i = 0; i < size; i++) {
        tree.Insert(arr[i], i * arr[i]);
    }

    for (int i = 0; i < size; i++) {
        ASSERT_EQ(tree.GetValue(arr[i]), i * arr[i]);
    }
}

TEST(Vector, AddBack) {
    int arr[] = { 41, 467, 334, 500, 169, 724, 478 };
    TVector<int> vec;
    int size = 7;

    for (int i = 0; i < size; i++) {
        vec.AddBack(arr[i]);
    }

    ASSERT_EQ(vec.GetSizeVector(), size);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(vec[i], arr[i]);
    }
}

TEST(Vector, AddFront) {
    int arr[] = { 41, 467, 334, 500, 169, 724, 478 };
    TVector<int> vec;
    int size = 7;

    for (int i = 0; i < size; i++) {
        vec.AddFront(arr[i]);
    }

    ASSERT_EQ(vec.GetSizeVector(), size);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(vec[i], arr[size-1-i]);
    }
}

TEST(Vector, Add) {
    int arr[] = { 41, 467, 334, 500, 169, 724, 478 };
    TVector<int> vec;
    int size = 7;
    int a = -37, b = 99;
    int ai = 2, bi = 5;

    for (int i = 0; i < size; i++) {
        vec.AddBack(arr[i]);
    }
    vec.Add(ai, a);
    vec.Add(bi, b);

    ASSERT_EQ(vec.GetSizeVector(), size + 2);
    ASSERT_EQ(vec[ai], a);
    ASSERT_EQ(vec[bi], b);
}

TEST(Vector, DeleteBack) {
    int arr[] = { 41, 467, -334, 500, 169, 724, 478, -267, 11 };
    int size = 9;
    TVector<int> vec;

    for (int i = 0; i < size; i++) {
        vec.AddBack(arr[i]);
    }
    vec.DeleteBack();
    vec.DeleteBack();

    ASSERT_EQ(vec.GetSizeVector(), size - 2);
    for (int i = 0; i < size - 2; i++) {
        ASSERT_EQ(vec[i], arr[i]);
    }
}

TEST(Vector, DeleteFront) {
    int arr[] = { 41, 467, -334, 500, 169, 724, 478, -267, 11 };
    int size = 9;
    TVector<int> vec;

    for (int i = 0; i < size; i++) {
        vec.AddBack(arr[i]);
    }
    vec.DeleteFront();
    vec.DeleteFront();

    ASSERT_EQ(vec.GetSizeVector(), size - 2);
    for (int i = 2; i < size; i++) {
        ASSERT_EQ(vec[i - 2], arr[i]);
    }
}

TEST(Vector, Delete) {
    int arr[] = { 41, 467, -334, 500, 169, 724, 478, -267, 11 };
    int size = 9;
    TVector<int> vec;
    int ai = 3, bi = 7;
    int j = 0;

    for (int i = 0; i < size; i++) {
        if (i == ai || i == bi) {
            vec.AddBack(0);
        }
        vec.AddBack(arr[j++]);
    }
    vec.Delete(ai);
    vec.Delete(bi);

    ASSERT_EQ(vec.GetSizeVector(), size);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(vec[i], arr[i]);
    }
}

TEST(Vector, ToString) {
    int arr[] = { 41, 467, -334, 500, 169 };
    std::string ansStr = "[ 41 467 -334 500 169 ]";
    int size = 5;
    TVector<int> vec;

    for (int i = 0; i < size; i++) {
        vec.AddBack(arr[i]);
    }

    ASSERT_EQ(vec.ToString(), ansStr);
}

TEST(Vector, SortTimsort) {
    int arr[] = { 41, 467, -334, 500, 0, 169, 724, 478, -267, 11 };
    int arrSort[] = { 724, 500, 478, 467, 169, 41, 11, 0, -267, -334 };
    int size = 10;
    TVector<int> vec;

    for (int i = 0; i < size; i++) {
        vec.AddBack(arr[i]);
    }
    vec.SortTimsort();

    ASSERT_EQ(vec.GetSizeVector(), size);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(vec[i], arrSort[i]);
    }
}

TEST(Vector, BubbleSort) {
    int arr[] = { 41, 467, -334, 500, 0, 169, 724, 478, -267, 11 };
    int arrSort[] = { 724, 500, 478, 467, 169, 41, 11, 0, -267, -334 };
    int size = 10;
    TVector<int> vec;

    for (int i = 0; i < size; i++) {
        vec.AddBack(arr[i]);
    }
    vec.BubbleSort();

    ASSERT_EQ(vec.GetSizeVector(), size);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(vec[i], arrSort[i]);
    }
}

TEST(Vector, IsSort) {
    int arrSort[] = { -334, -267, 0, 11, 41, 169, 467, 478, 500, 724 };
    int size = 10;
    TVector<int> vec;

    for (int i = 0; i < size; i++) {
        vec.AddBack(arrSort[i]);
    }
    ASSERT_TRUE(vec.IsSort());
}

TEST(Vector, GetBack) {
    int arr[] = { 41, 467, -334, 500, 0, 169, 724, 478, -267, 11 };
    int size = 10;
    TVector<int> vec;

    for (int i = 0; i < size; i++) {
        vec.AddBack(arr[i]);
    }
    ASSERT_EQ(vec.GetBack(), arr[size - 1]);
}

TEST(Vector, GetFront) {
    int arr[] = { 41, 467, -334, 500, 0, 169, 724, 478, -267, 11 };
    int size = 10;
    TVector<int> vec;

    for (int i = 0; i < size; i++) {
        vec.AddBack(arr[i]);
    }
    ASSERT_EQ(vec.GetFront(), arr[0]);
}

TEST(Queue, PushBack) {
    int arr[] = { 41, 467, -334, 500, 0, 169, 724, 478, -267, 11 };
    int size = 10;
    TQueue<int> que;

    for (int i = 0; i < size; i++) {
        que.PushBack(arr[i]);
    }

    ASSERT_EQ(que.Size(), size);
}

TEST(Queue, Pop) {
    int arr[] = { 41, 467, -334, 500, 0, 169, 724, 478, -267, 11 };
    int size = 10;
    TQueue<int> que;

    for (int i = 0; i < size; i++) {
        que.PushBack(arr[i]);
    }
    que.PopBack();
    que.PopBack();
    que.PopBack();

    ASSERT_EQ(que.Size(), size - 3);
}

TEST(Queue, PopFront) {
    int arr[] = { 41, 467, -334, 500, 0, 169, 724, 478, -267, 11 };
    int size = 10;
    TQueue<int> que;

    for (int i = 0; i < size; i++) {
        que.PushBack(arr[i]);
    }
    int a = que.Front();
    que.PopFront();
    int b = que.Front();
    que.PopFront();

    ASSERT_EQ(a, arr[0]);
    ASSERT_EQ(b, arr[1]);
}

TEST(Queue, IsEmpty) {
    int arr[] = { 41, 467, -334, 500, 0, 169, 724, 478, -267, 11 };
    int size = 10;
    TQueue<int> que;
    TQueue<int> queEmpty;

    for (int i = 0; i < size; i++) {
        que.PushBack(arr[i]);
    }
    que.PopBack();
    que.PopBack();

    ASSERT_FALSE(que.IsEmpty());
    ASSERT_TRUE(queEmpty.IsEmpty());
}