#include "Dictionary.hpp"

int GetHashCode(int key)
{
    return key;
}

int GetHashCode(long key)
{
    return static_cast<int>(key ^ (key >> 32));
}

int GetHashCode(const std::string& key)
{
    int hash = 0;
    for (size_t i = 0; i < key.size(); i++)
    {
        hash = key[i] + (31 * hash);
    }
    return hash;
}
