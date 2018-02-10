#ifndef TUPLE_H
#define TUPLE_H
template <typename T1, typename T2>
class Tuple;
template <typename T1, typename T2>
class Tuple
{
public:
    Tuple(T1 item1, T2 item2);
    const T1& Item1() const;
    const T2& Item2() const;

private:
    T1 item1;
    T2 item2;
};
template <typename T1, typename T2>
Tuple::Tuple(T1 item1, T2 item2) : item1{item1}, item2{item2}
{
}

template <typename T1, typename T2>
const T1& Tuple::Item1() const
{
    return item1;
}

template <typename T1, typename T2>
const T2& Tuple::Item2() const
{
    return item2;
}
#endif // TUPLE_H
