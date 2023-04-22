#include <iostream>
#include "TreeAVL.h"
#include "Queue.h"
#include "Vertex.h"
#include "MyVector.h"
#include "Edge.h"

using namespace std;

void swapEdge(Edge& first, Edge& second)
{
    Edge defaultEdge;
    
    defaultEdge = first;
    first = second;
    second = defaultEdge;
}

void bubbleSortMyVectorEdge(MyVector<Edge>& ArrEdge)
{
    int nEdge = ArrEdge.GetSizeVector();
    for (int i = 0; i < nEdge - 1; i++)
    {
        for (int j = 0; j < nEdge - i - 1; j++)
        {
            if (ArrEdge[j].firstVertex->name > ArrEdge[j + 1].firstVertex->name)
            {
                swapEdge(ArrEdge[j], ArrEdge[j + 1]);
            }
            else if ((ArrEdge[j].firstVertex->name == ArrEdge[j + 1].firstVertex->name) && (ArrEdge[j].secondVertex->name > ArrEdge[j + 1].secondVertex->name))
            {
                swapEdge(ArrEdge[j], ArrEdge[j + 1]);
            }
        }
    }
}

void quickSort(MyVector<Edge>& ArrEdge, int First, int Last)
{
    Edge midEdge;
    int left = First, right = Last;
    midEdge = ArrEdge[(left + right) / 2]; //вычисление опорного элемента
    do
    {
        while ((ArrEdge[left].firstVertex->name < midEdge.firstVertex->name) || (ArrEdge[left].firstVertex->name == midEdge.firstVertex->name && ArrEdge[left].secondVertex->name < midEdge.secondVertex->name))
            left++;
        while ((ArrEdge[right].firstVertex->name > midEdge.firstVertex->name) || (ArrEdge[right].firstVertex->name == midEdge.firstVertex->name && ArrEdge[right].secondVertex->name > midEdge.secondVertex->name))
            right--;

        if (left <= right) //перестановка элементов
        {
            swap(ArrEdge[left], ArrEdge[right]);
            left++;
            right--;
        }
    } while (left < right);
    if (First < right) quickSort(ArrEdge, First, right);
    if (left < Last) quickSort(ArrEdge, left, Last);
}


Vertex* findMainParent(Vertex* DefaultVertex)
{
    if (DefaultVertex->parent != nullptr)
    {
        DefaultVertex->parent = findMainParent(DefaultVertex->parent);
    }
    if (DefaultVertex->parent)
        return DefaultVertex->parent;
    return DefaultVertex;
}

void mergeEdges(MyVector<Edge>& QueueEdge, MyVector<Edge>& AnswerEdge)
{
    while (QueueEdge.GetSizeVector() > 0)
    {
        Edge defaultEdge = QueueEdge.GetBack();
        Vertex* x = findMainParent(defaultEdge.firstVertex);
        Vertex* y = findMainParent(defaultEdge.secondVertex);
        if (x != y)
        {
            x->parent = y;
            y->amount += x->amount;
            AnswerEdge.AddBack(defaultEdge);
        }
        QueueEdge.DeleteBack();
    }
}

void PrintEdges(MyVector<Edge>& ArrEdge)
{
    cout << endl;
    int allWeight = 0;
    //bubbleSortMyVectorEdge(ArrEdge);
    quickSort(ArrEdge, 0, ArrEdge.GetSizeVector() - 1);

    for (int i = 0; i < ArrEdge.GetSizeVector(); i++)
    {
        Edge newEdge = ArrEdge[i];
        cout << newEdge.firstVertex->name << " " << newEdge.secondVertex->name << " " << newEdge.weight << endl;
        allWeight += newEdge.weight;
    }
    cout << "\nWeight: " << allWeight;
}

void printAdjacencyMatrix(TreeAVL<Vertex, string>& arrVertex, int n, MyVector<Edge>& ArrEdge)
{
    arrVertex.AssignKeys();

    int inf = -1;

    int adjacencyMatrixArr[50][50];
    for (int i = 0; i < 50; i++)
        for (int j = 0; j < 50; j++)
            adjacencyMatrixArr[i][j] = inf;

    for (int i = 0; i < ArrEdge.GetSizeVector(); i++)
    {
        Edge newEdge = ArrEdge[i];
        //cout << newEdge.firstVertex->name << " " << newEdge.secondVertex->name << " " << newEdge.weight << endl;
        int firstIndex = arrVertex.GetkeySerialNumber(newEdge.firstVertex->name);
        int secondIndex = arrVertex.GetkeySerialNumber(newEdge.secondVertex->name);
        adjacencyMatrixArr[firstIndex][secondIndex] = adjacencyMatrixArr[secondIndex][firstIndex] = newEdge.weight;
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

int main()
{
    TreeAVL<Vertex, string> arrVertex;
    int nEdges, nVertex = 0;
    MyVector<Edge> queueEdge;
    cout << "Num Edges: ";
    cin >> nEdges;

    for (int i = 0; i < nEdges; i++)
    {
        string keyVertexFirst, keyVertexSecond;
        int weight;

        cin >> keyVertexFirst >> keyVertexSecond >> weight;

        if (!arrVertex.Get(keyVertexFirst))
        {
            Vertex newVertex(keyVertexFirst);
            arrVertex.Insert(keyVertexFirst, newVertex);
            nVertex++;
        }
        if (!arrVertex.Get(keyVertexSecond))
        {
            Vertex newVertex(keyVertexSecond);
            arrVertex.Insert(keyVertexSecond, newVertex);
            nVertex++;
        }    

        Vertex *x = (arrVertex.Get(keyVertexFirst));
        Vertex *y = (arrVertex.Get(keyVertexSecond));

        Edge newEdge(x, y, weight);
        queueEdge.AddBack(newEdge);
        
        //arrVertex.PrintTree();
        //cout << "\n###########################################################";
    }
    

    queueEdge.SortTimsort();
    MyVector<Edge> AnswerEdge;
    mergeEdges(queueEdge, AnswerEdge);

    PrintEdges(AnswerEdge);
    //cout << "\n\n";
    //printAdjacencyMatrix(arrVertex, nVertex, AnswerEdge);


    return 0;
} 
/*


21
A B 14
C M 11
F H 20
I D 13
G C 8
J N 12
K J 4
C L 16
E G 26
B I 26
J G 18
M L 9
H N 17
I E 10
J A 17
M K 6
I H 17
B J 8
N C 2
K F 13
A M 20


*/


//int main()
//{
//    string s1 = "19", s2 = "190";
//    if (s1 > s2)
//        cout << ">";
//    else
//        cout << "<";
//}
    //queueVertex.BubbleSort();
    //arrVertex.AssignKeys();----
    //arrVertex.PrintTree();

    //int inf = -1;
    //int adjacencyMatrixArr[50][50];
    //for (int i = 0; i < 50; i++)
        //for (int j = 0; j < 50; j++)
            //adjacencyMatrixArr[i][j] = inf;
    
    /*cout << endl;
    while (queueVertex.GetSizeVector() > 0)
    {
        Edge newEdge = queueVertex.GetBack();
        Vertex* x = findMainParent(newEdge.firstVertex);
        Vertex* y = findMainParent(newEdge.secondVertex);
        //cout << newEdge.firstVertex->name << "::::" << newEdge.secondVertex->name << endl;--
        //cout << x->name << "(" << x->amount << ")" << "::::" << y->name << "(" << y->amount << ")" << endl;--
        if (x != y)
        {           
            x->parent = y;
            y->amount += x->amount;
            
            int firstIndex = arrVertex.GetkeySerialNumber(newEdge.firstVertex->name);
            int secondIndex = arrVertex.GetkeySerialNumber(newEdge.secondVertex->name);
            adjacencyMatrixArr[firstIndex][secondIndex] = adjacencyMatrixArr[secondIndex][firstIndex] = newEdge.weight;
            
            //cout << newEdge.firstVertex->name << " " << newEdge.secondVertex->name << " " << newEdge.weight << endl;
            
            AnswerEdge.AddBack(newEdge);
        }
        //queueVertex.Print();
        //arrVertex.Print();--
        //cout << "\n\n";--
        queueVertex.DeleteBack();
    }*/
    
    /*for (int i = 0; i < AnswerEdge.GetSizeVector(); i++)
    {
        Edge newEdge = AnswerEdge[i];
        cout << newEdge.firstVertex->name << " " << newEdge.secondVertex->name << " " << newEdge.weight << endl;
    }*/

    //cout << "\t";
    //for (int i = 0; i < n; i++)
    //    cout << arrVertex.GetKey(i) << "\t";
    //cout << endl;

    //for (int i = 0; i < n; i++)
    //{
    //    cout << arrVertex.GetKey(i) << "\t";
    //    for (int j = 0; j < n; j++)
    //    {
    //        adjacencyMatrixArr[i][j] == -1 ? cout << ".\t" : cout << adjacencyMatrixArr[i][j] << "\t";
    //    }
    //    cout << endl;
    //}


//1 2 0
//3 4 0
//5 6 0
//7 8 0
//9 10 0
//10 11 0

//a e 30
//a b 12
//a d 8
//a c 2
//b e 4
//b c 6
//e c 9
//e d 11
//d c 20

//a d 3
//a e 2
//c f 4
//b c 5
//a b 7
//e g 8
//f e 10
//c a 11

//1 2 0
//2 3 0
//3 4 0
//5 6 0
//6 7 0
//7 8 0
//9 1 0
//10 11 0
//11 12 0
//13 14 0
    //MyVertex a("a");
    //MyVertex b("b");
    //MyVertex c("c");
    //MyVertex d("d");
    //MyVertex e("e");
    //cout << a.name << " " << a.parent << " " << &a << endl;
    //cout << b.name << " " << b.parent << " " << &b << endl;
    //cout << c.name << " " << c.parent << " " << &c << endl;
    //cout << d.name << " " << d.parent << " " << &d << endl;
    //cout << e.name << " " << e.parent << " " << &e << endl;
    
    //TreeAVL<MyVertex, string> arrVertex;
    //arrVertex.Insert(a.name, a);
    //arrVertex.Print();
    //cout << endl;
    //arrVertex.Insert(b.name, b);
    //arrVertex.Print();
    //cout << endl;
    //arrVertex.Insert(c.name, c);
    //arrVertex.Print();
    //cout << endl;
    //arrVertex.Insert(d.name, d);
    //arrVertex.Print();
    //cout << endl;
    //arrVertex.Insert(e.name, e);
    //arrVertex.Print();
    //cout << endl;

    //Edge edge1(&a, &b, 1);
    //Edge edge2(&a, &e, 1);
    //Edge edge3(&a, &d, 1);

    //Edge edge4(&b, &c, 1);
    //Edge edge5(&b, &d, 1);

    //Edge edge6(&c, &e, 1);
    //Edge edge7(&c, &d, 1);

    //Edge edge8(&e, &d, 1);


    //cout << edge1.firstVertex->name << " " << edge1.firstVertex->parent << " " << edge1.firstVertex << endl;
    //cout << edge1.secondVertex->name << " " << edge1.secondVertex->parent << " " << edge1.secondVertex << endl;
    //cout << edge1.weight << endl << endl;

    //cout << edge2.firstVertex->name << " " << edge2.firstVertex->parent << " " << edge2.firstVertex << endl;
    //cout << edge2.secondVertex->name << " " << edge2.secondVertex->parent << " " << edge2.secondVertex << endl;
    //cout << edge2.weight << endl << endl;

    //cout << edge3.firstVertex->name << " " << edge3.firstVertex->parent << " " << edge3.firstVertex << endl;
    //cout << edge3.secondVertex->name << " " << edge3.secondVertex->parent << " " << edge3.secondVertex << endl;
    //cout << edge3.weight << endl << endl;

    //cout << edge4.firstVertex->name << " " << edge4.firstVertex->parent << " " << edge4.firstVertex << endl;
    //cout << edge4.secondVertex->name << " " << edge4.secondVertex->parent << " " << edge4.secondVertex << endl;
    //cout << edge4.weight << endl << endl;

    //cout << edge5.firstVertex->name << " " << edge5.firstVertex->parent << " " << edge5.firstVertex << endl;
    //cout << edge5.secondVertex->name << " " << edge5.secondVertex->parent << " " << edge5.secondVertex << endl;
    //cout << edge5.weight << endl << endl;
   
    //MyVector<Edge> queueVertex;
    //queueVertex.AddBack(edge1);
    //queueVertex.AddBack(edge2);
    //queueVertex.AddBack(edge3);
    //queueVertex.AddBack(edge4);
    //queueVertex.AddBack(edge5);
    //queueVertex.AddBack(edge6);
    //queueVertex.AddBack(edge7);
    //queueVertex.AddBack(edge8);

    /*for (int i = 0; i < 5; i++)
    {
        Edge newEdge = queueVertex.GetBack();
        cout << newEdge.firstVertex->name << " " << newEdge.firstVertex->parent << " " << newEdge.firstVertex << endl;
        cout << newEdge.secondVertex->name << " " << newEdge.secondVertex->parent << " " << newEdge.secondVertex << endl;
        cout << newEdge.weight << endl << endl;

        if (queueVertex.GetSizeVector() != 0)
            queueVertex.DeleteBack();
    }*/