#include <iostream>
#include <gtest/gtest.h>
#include "../src/vector.h"
#include "../src/queue.h"

using namespace std;

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