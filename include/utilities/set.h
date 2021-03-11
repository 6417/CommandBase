#ifndef COMMANDBASE_SET_H
#define COMMANDBASE_SET_H

#include "utilities/LinkedList.h"

template<typename T>
class set
{
private:
    LinkedList<T> elements;
public:
    using iterator = typename LinkedList<T>::iterator;

    set() = default;

    iterator begin();

    iterator end();

    iterator find(T element);

    void insert(T element);

    void erase(T element);

    void clear();

    const LinkedList<T>& getElementList() const;

    unsigned int getSize();
};

template<typename T>
bool operator==(typename set<T>::iterator& a, typename set<T>::iterator& b);

template<typename T>
bool operator!=(typename set<T>::iterator& a, typename set<T>::iterator& b);

template<typename T>
typename set<T>::iterator set<T>::begin()
{
    return elements.begin();
}

template<typename T>
typename set<T>::iterator set<T>::end()
{
    return elements.end();
}

template<typename T>
typename set<T>::iterator set<T>::find(T element)
{
    for (auto it = elements.begin(); it != elements.end(); it++)
        if (*it == element)
            return it;
    return elements.end();
}

template<typename T>
void set<T>::insert(T element)
{
    if (find(element) == elements.end())
        elements.push(element);
}

template<typename T>
void set<T>::erase(T element)
{
    elements.erase(find(element));
}

template<typename T>
void set<T>::clear()
{
    elements.clear();
}

template<typename T>
const LinkedList<T>& set<T>::getElementList() const
{
    return elements;
}

template<typename T>
unsigned int set<T>::getSize()
{
    return elements.getSize();
}

#endif //COMMANDBASE_SET_H

