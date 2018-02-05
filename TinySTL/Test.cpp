#include "Test.hpp"
#include "Dictionary.hpp"
#include "Exception.h"
#include "List.hpp"
#include "Queue.hpp"
#include "Sorting.hpp"
#include "Stack.hpp"
#include <iostream>
#include <string>
using namespace std;
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
