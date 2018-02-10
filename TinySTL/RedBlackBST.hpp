#ifndef REDBLACKBST_HPP
#define REDBLACKBST_HPP
template <typename TKey, typename TValue>
class RedBlackBST;
template <typename TKey, typename TValue>
class RBNode;
enum class NodeColor
{
    Red,
    Black
};
template <typename TKey, typename TValue>
class RedBlackBST
{
private:
    bool IsRed(RBNode<TKey, TValue>* node);
    RBNode<TKey, TValue>* RotateLeft(RBNode<TKey, TValue>* y);
    RBNode<TKey, TValue>* RotateRight(RBNode<TKey, TValue>* y);
    void FlipColors(RBNode<TKey, TValue>* y);
    void Insert(RBNode<TKey, TValue>* y, TKey key, TValue value);
};
template <typename TKey, typename TValue>
class RBNode
{
public:
    RBNode(TKey key, TValue value, RBNode<TKey, TValue>* left,
           RBNode<TKey, TValue>* right, NodeColor color);
    friend class RBTree<TKey, TValue>;

private:
    TKey key;
    TValue value;
    RBNode<TKey, TValue>* left;
    RBNode<TKey, TValue>* right;
    NodeColor color;
};
template <typename TKey, typename TValue>
RBNode<TKey, TValue>::RBNode(TKey key, TValue value, RBNode<TKey, TValue>* left,
                             RBNode<TKey, TValue>* right, NodeColor color)
    : key{key}, value{value}, left{left}, right{right}, color{color}
{
}

template <typename TKey, typename TValue>
RBNode<TKey, TValue>*
    RedBlackBST<TKey, TValue>::RotateLeft(RBNode<TKey, TValue>* y)
{
    /*
     y
   /  \
       x
*/
    RBNode<TKey, TValue>* x = y->right;
    y->right = x->left;
    x->left = y;
    x->color = y->color;
    y->color = NodeColor::Red;
    return x;
}

template <typename TKey, typename TValue>
RBNode<TKey, TValue>*
    RedBlackBST<TKey, TValue>::RotateRight(RBNode<TKey, TValue>* y)
{
    RBNode<TKey, TValue>* x = y->left;
    y->left = x->right;
    x->right = y;
    x->color = y->color;
    y->color = NodeColor::Red;
    return x;
}

template <typename TKey, typename TValue>
void RedBlackBST<TKey, TValue>::FlipColors(RBNode<TKey, TValue>* y)
{
    y->color = NodeColor::Red;
    y->left->color = NodeColor::Black;
    y->right->color = NodeColor::Black;
}

template <typename TKey, typename TValue>
void RedBlackBST<TKey, TValue>::Insert(RBNode<TKey, TValue>* y, TKey key,
                                       TValue value)
{
    if (y == nullptr)
    {
        return new RBNode<TKey, TValue>(key, value, NodeColor::Red);
    }
    else if (key < y->key)
    {
        y->left = Insert(y->left, key, value);
    }
    else if (key > y->key)
    {
        y->right = Insert(y->right, key, value);
    }
    else
    {
        throw "duplicative key";
    }

    if (IsRed(y->right) && !IsRed(y->left))
    {
        y = RotateLeft(y);
    }
    if (IsRed(y->left) && IsRed(y->left->left))
    {
        y = RotateRight(y);
    }
    if (IsRed(y->left) && IsRed(y->right))
    {
        FilpColors(y);
    }
    return y;
}

template <typename TKey, typename TValue>
bool RedBlackBST<TKey, TValue>::IsRed(RBNode<TKey, TValue>* node)
{
    if (node == nullptr)
    {
        return false; // null links are block
    }
    else
    {
        return node->color == NodeColor::Red;
    }
}
#endif // REDBLACKBST_HPP
