#include "Test.hpp"
#include "Array.hpp"
#include "BinaryMaxHeap.hpp"
#include "BinarySearchTree.hpp"
#include "Dictionary.hpp"
#include "Exception.h"
#include "Functional.hpp"
#include "List.hpp"
#include "Queue.hpp"
#include "Selection.hpp"
#include "Sorting.hpp"
#include "Stack.hpp"
#include <iostream>
#include <string>
using namespace std;
void TestArray()
{
    Array<int> array = {1, 2, 3, 4, 5};
    for (int item : array)
	{
        cout << item << endl;
	}
    for (int i = 0; i < array.Length(); i++)
	{
        cout << array.At(i) << endl;
	}
	Array<int> emptyArray(10);
    for (int item : emptyArray)
	{
        cout << item << endl;
	}
}
void TestDictionary()
{
    Dictionary<int, string> dic(7);
    dic.Add(14, "n14");
    dic.Add(28, "n28");
    dic.Add(7, "n7");
    dic.Add(21, "n21");
    dic.Add(1, "n1");
    dic.Add(8, "n8");
    dic.Add(24, "n24");
    dic.Add(10, "n10");

    dic.Add(18, "n18");
    dic.Add(13, "n13");
    dic.Add(27, "n27");

    for (const auto& item : dic)
    {
        cout << "[" << item.Key() << ", " << item.Value() << "]" << endl;
    }
    cout << "remove 27" << endl;
    dic.Remove(27);
    for (const auto& item : dic)
    {
        cout << "[" << item.Key() << ", " << item.Value() << "]" << endl;
    }
}

void TestSelectionSort()
{
    List<int> a = {10, 30, 4, 58, 9};
    for (auto& item : a)
    {
        cout << item << endl;
    }
    SelectionSort(a);
    cout << "-------------" << endl;
    for (auto& item : a)
    {
        cout << item << endl;
    }
}

void TestMergeSort()
{
    List<int> a = {10, 30, 4, 58, 9};
    ForEach(a, [](int& item) { cout << item << " "; });
    cout << endl;
    MergeSort<List<int>, int>(a);
    ForEach(a, [](int& item) { cout << item << " "; });
    cout << endl;
}

void TestBotoomUpMergeSort()
{
    List<int> a = {10, 30, 4, 58, 9};
    ForEach(a, [](int& item) { cout << item << " "; });
    cout << endl;
    BottomUpMergeSort<List<int>, int>(a);
    ForEach(a, [](int& item) { cout << item << " "; });
    cout << endl;
}

void TestSelectTopK()
{
    List<int> a = {10, 30, 4, 58, 9};
    ForEach(a, [](int& item) { cout << item << " "; });
    cout << endl;
    int result = QuickSelect<List<int>, int>(a, 1);
    ForEach(a, [](int& item) { cout << item << " "; });
    cout << endl;
    cout << "top k: " << result << endl;
}

void TestBinaryMaxHeap()
{
    cout << "test binary max heap" << endl;
    BinaryMaxHeap<int, string> heap;
    auto f = [&heap]() {
        ForEach(heap.GetHeap(), [](KeyValuePair<int, string>& item) {
            cout << item.Key() << " ";
        });
        cout << endl;
    };
    heap.Insert(90, "");
    f();
    heap.Insert(89, "");
    f();
    heap.Insert(75, "");
    f();
    heap.Insert(70, "");
    f();
    heap.Insert(65, "");
    f();
    heap.Insert(63, "");
    f();
    heap.Insert(36, "");
    f();
    heap.Insert(21, "");
    f();
    heap.Insert(18, "");
    f();
    heap.Insert(15, "");
    f();
    heap.DeleteMax();
    f();
    heap.DeleteMax();
    f();
}

void TestBinarySearchTree()
{
    cout << "test binary search tree" << endl;
    BinarySearchTree<int, string> tree;
    tree.Insert(90, "");
    tree.Insert(89, "");
    tree.Insert(75, "");
    tree.Insert(70, "");
    tree.Insert(65, "");
    tree.Insert(63, "");
    tree.Insert(36, "");
    tree.Insert(21, "");
    tree.Insert(18, "");
    tree.Insert(15, "");
}
