#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include "Exception.hpp"
#include "KeyValuePair.hpp"
template <typename TKey, typename TValue>
class BinarySearchTree;
template <typename TKey, typename TValue>
class BSTNode;

template <typename TKey, typename TValue>
class BinarySearchTree
{
public:
    BinarySearchTree();
    ~BinarySearchTree();
    void Insert(TKey key, TValue value);
    TValue& At(TKey key);
    KeyValuePair<TKey, TValue> Floor(TKey key);
    void DeleteMin();
    void Delete(TKey key);
    KeyValuePair<TKey, TValue> Max();
    KeyValuePair<TKey, TValue> Min();

private:
    BSTNode<TKey, TValue>* root;
    BSTNode<TKey, TValue>* Insert(BSTNode<TKey, TValue>* node, TKey& key,
                                  TValue& value);
    BSTNode<TKey, TValue>* Floor(BSTNode<TKey, TValue>* node, TKey& key);
    BSTNode<TKey, TValue>* DeleteMin(BSTNode<TKey, TValue>* node);
    BSTNode<TKey, TValue>* Delete(BSTNode<TKey, TValue>* node, TKey& key);
    BSTNode<TKey, TValue>* Min(BSTNode<TKey, TValue>* node);
};
template <typename TKey, typename TValue>
class BSTNode
{
public:
    friend class BinarySearchTree<TKey, TValue>;

private:
    BSTNode(TKey key, TValue value, BSTNode<TKey, TValue>* left,
            BSTNode<TKey, TValue>* right);
    ~BSTNode();
    TKey key;
    TValue value;
    BSTNode<TKey, TValue>* left;
    BSTNode<TKey, TValue>* right;
};
template <typename TKey, typename TValue>
BinarySearchTree<TKey, TValue>::BinarySearchTree()
    : root{nullptr}
{
}

template <typename TKey, typename TValue>
BinarySearchTree<TKey, TValue>::~BinarySearchTree()
{
    if (root)
    {
        delete root;
    }
}

template <typename TKey, typename TValue>
void BinarySearchTree<TKey, TValue>::Insert(TKey key, TValue value)
{
    root = Insert(root, key, value);
}

template <typename TKey, typename TValue>
TValue& BinarySearchTree<TKey, TValue>::At(TKey key)
{
    BSTNode<TKey, TValue>* current = root;
    while (current != nullptr)
    {
        if (key < current->key)
        {
            current = current->left;
        }
        else if (key > current->key)
        {
            current = current->right;
        }
        else
        {
            return current->value;
        }
    }
    throw KeyNotFoundException();
}

template <typename TKey, typename TValue>
KeyValuePair<TKey, TValue> BinarySearchTree<TKey, TValue>::Floor(TKey key)
{
    BSTNode<TKey, TValue>* result = Floor(root, key);
    if (result == nullptr)
    {
        throw ArgumentException(L"There is no key that smaller than given key");
    }
    else
    {
        return KeyValuePair<TKey, TValue>(result->key, result->value);
    }
}

template <typename TKey, typename TValue>
void BinarySearchTree<TKey, TValue>::DeleteMin()
{
    root = DeleteMin(root);
}

template <typename TKey, typename TValue>
void BinarySearchTree<TKey, TValue>::Delete(TKey key)
{
    root = Delete(root, key);
}

template <typename TKey, typename TValue>
KeyValuePair<TKey, TValue> BinarySearchTree<TKey, TValue>::Max()
{
    BSTNode<TKey, TValue>* current = root;
    while (current->right != nullptr)
    {
        current = current->right;
    }
    return KeyValuePair<TKey, TValue>(current->key, current->value);
}

template <typename TKey, typename TValue>
KeyValuePair<TKey, TValue> BinarySearchTree<TKey, TValue>::Min()
{
    BSTNode<TKey, TValue>* current = root;
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return KeyValuePair<TKey, TValue>(current->key, current->value);
}

template <typename TKey, typename TValue>
BSTNode<TKey, TValue>*
    BinarySearchTree<TKey, TValue>::Insert(BSTNode<TKey, TValue>* node,
                                           TKey& key, TValue& value)
{
    if (node == nullptr)
    {
        return new BSTNode<TKey, TValue>(key, value, nullptr, nullptr);
    }
    else
    {
        if (key < node->key)
        {
            node->left = Insert(node->left, key, value);
            return node;
        }
        else if (key > node->key)
        {
            node->right = Insert(node->right, key, value);
            return node;
        }
        else
        {
            throw ArgumentException(L"The key already exists");
        }
    }
}

template <typename TKey, typename TValue>
BSTNode<TKey, TValue>*
    BinarySearchTree<TKey, TValue>::Floor(BSTNode<TKey, TValue>* node,
                                          TKey& key)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else
    {
        if (key == node->key)
        {
            return node;
        }
        else if (key < node->key)
        {
            return Floor(node->left, key);
        }
        else
        {
            BSTNode<TKey, TValue>* result = Floor(node->left, key);
            if (result != nullptr)
            {
                return result;
            }
            else
            {
                return node;
            }
        }
    }
}

template <typename TKey, typename TValue>
BSTNode<TKey, TValue>*
    BinarySearchTree<TKey, TValue>::DeleteMin(BSTNode<TKey, TValue>* node)
{
    if (node->left == nullptr)
    {
        return node->right;
    }
    else
    {
        node->left = DeleteMin(node->left);
        return node;
    }
}

template <typename TKey, typename TValue>
BSTNode<TKey, TValue>*
    BinarySearchTree<TKey, TValue>::Delete(BSTNode<TKey, TValue>* node,
                                           TKey& key)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else if (key < node->key)
    {
        node->left = Delete(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = Delete(node->right, key);
    }
    else
    {
        if (node->right == nullptr)
        {
            return node->left;
        }
        else
        {
            BSTNode<TKey, TValue>* t = node;
            node = Min(t->right);
            node->right = DeleteMin(t->right);
            node->left = t->left;
            return node;
        }
    }
}

template <typename TKey, typename TValue>
BSTNode<TKey, TValue>*
    BinarySearchTree<TKey, TValue>::Min(BSTNode<TKey, TValue>* node)
{
    BSTNode<TKey, TValue>* current = node;
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

template <typename TKey, typename TValue>
BSTNode<TKey, TValue>::BSTNode(TKey key, TValue value,
                               BSTNode<TKey, TValue>* left,
                               BSTNode<TKey, TValue>* right)
    : key{key}
    , value{value}
    , left{left}
    , right{right}
{
}

template <typename TKey, typename TValue>
BSTNode<TKey, TValue>::~BSTNode()
{
    if (left)
    {
        delete left;
    }
    if (right)
    {
        delete right;
    }
}

#endif // BINARYSEARCHTREE_HPP
