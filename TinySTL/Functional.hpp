#ifndef FUNCTIONAL_HPP
#define FUNCTIONAL_HPP
template <typename TCollection, typename TAction>
void ForEach(TCollection& collection, const TAction& action);

template <typename TCollection, typename TAction>
void ForEach(TCollection& collection, const TAction& action)
{
    for (auto& item : collection)
    {
        action(item);
    }
}
#endif // FUNCTIONAL_HPP
