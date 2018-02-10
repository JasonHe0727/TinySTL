TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Exception.cpp \
    Test.cpp \
    ConvexHull.cpp \
    Dictionary.cpp

HEADERS += \
    Exception.h \
    List.hpp \
    Queue.hpp \
    Stack.hpp \
    Dictionary.hpp \
    Test.hpp \
    Sorting.hpp \
    Array.hpp \
    ConvexHull.hpp \
    SinglyLinkedList.hpp \
    Selection.hpp \
    Functional.hpp \
    BinaryMaxHeap.hpp \
    BinarySearchTree.hpp \
    Tuple.hpp \
    KeyValuePair.hpp \
    RedBlackBST.hpp
