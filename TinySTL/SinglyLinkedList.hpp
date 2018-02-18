#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H
template <typename T>
class SinglyLinkedList;
template <typename T>
class SinglyLinkedListNode;
template <typename T>
class SinglyLinkedListIterator;

template <typename T>
class SinglyLinkedList
{
public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    friend class SinglyLinkedListNode<T>;

private:
    SinglyLinkedListNode<T>* head;
    SinglyLinkedListNode<T>* tail;
};

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList()
    : head{nullptr}
    , tail{nullptr}
{
}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    SinglyLinkedListNode<T>* current = head;
    while (current != nullptr)
    {
        SinglyLinkedListNode<T>* next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
class SinglyLinkedListNode
{
private:
    T value;
    SinglyLinkedListNode<T>* previous;
    SinglyLinkedListNode<T>* next;
    SinglyLinkedListNode(T value, SinglyLinkedListNode<T>& previous,
                         SinglyLinkedListNode<T>* next);
};

template <typename T>
SinglyLinkedListNode<T>::SinglyLinkedListNode(T value,
                                              SinglyLinkedListNode<T>& previous,
                                              SinglyLinkedListNode<T>* next)
    : value{value}
    , previous{previous}
    , next{next}
{
}

#endif // SINGLYLINKEDLIST_H
