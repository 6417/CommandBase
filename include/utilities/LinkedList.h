#ifndef TDDTEST_LINKEDLIST_H
#define TDDTEST_LINKEDLIST_H

template<typename T>
struct Element
{
    T value;
    Element<T>* next = nullptr;

    Element() = default;

    Element(const Element<T>& e);

    Element(Element<T>&& e);

    Element& operator=(const Element<T>& e);

    Element& operator=(Element<T>&& e) noexcept;

    ~Element();
};

template<typename T>
class Iterator;

template<typename T>
class LinkedList
{
private:
    unsigned int size = 0;
    Element<T>* firstElement = nullptr;

    void pushEmptyElement();

    Element<T>& getElementAt(int index);

    const Element<T>& getElementAt(int index) const;

    Element<T>& getLastElement();

    const Element<T>& getLastElement() const;

public:
    using iterator = Iterator<T>;

    unsigned int getSize() const;

    void push(T element);

    LinkedList() = default;

    LinkedList(unsigned int initialSize);

    T pop();

    T& operator[](int index);

    const T& operator[](int index) const;

    void reserve(unsigned int size);

    iterator begin();

    iterator end();

    LinkedList(const LinkedList<T>& l);

    LinkedList(LinkedList<T>&& l);

    ~LinkedList();

    void clear();

    void erase(iterator it);

    LinkedList<T>& operator=(LinkedList<T>&& l);

    LinkedList<T>& operator=(const LinkedList<T>& l);
};

template<typename T>
class Iterator
{
public:
    friend LinkedList<T>;

    Iterator(Element<T>* start)
    {
        m_ptr = start;
    }

    const T& operator*() const { return m_ptr->value; }

    T& operator*() { return m_ptr->value; }

    T* operator->() { return &(m_ptr->value); }

    const T* operator->() const { return &(m_ptr)->value; }

    // Prefix increment
    Iterator& operator++()
    {
        m_ptr = m_ptr->next;
        return *this;
    }

    // Postfix increment
    Iterator operator++(int)
    {
        Iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };

    friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

private:

    Element<T>* m_ptr;
};


template<typename T>
unsigned int LinkedList<T>::getSize() const
{
    return size;
}

template<typename T>
void LinkedList<T>::push(T value)
{
    pushEmptyElement();
    getLastElement().value = value;
}

template<typename T>
Element<T>& LinkedList<T>::getLastElement()
{
    return getElementAt(size - 1);
}

template<typename T>
T LinkedList<T>::pop()
{
    T retVal = getLastElement().value;
    delete getLastElement();
    size--;
    return retVal;
}

template<typename T>
T& LinkedList<T>::operator[](int index)
{
    return getElementAt(index).value;
}

template<typename T>
Element<T>& LinkedList<T>::getElementAt(int index)
{
    Element<T>* next = firstElement;
    for (int i = 0; i < index; i++)
        next = next->next;
    return *next;
}

template<typename T>
const T& LinkedList<T>::operator[](int index) const
{
    return getElementAt(index).value;
}

template<typename T>
const Element<T>& LinkedList<T>::getElementAt(int index) const
{
    const Element<T>* next = firstElement;
    for (int i = 0; i < index; i++)
        next = next->next;
    return *next;
}

template<typename T>
const Element<T>& LinkedList<T>::getLastElement() const
{
    return getLastElement();
}

template<typename T>
void LinkedList<T>::reserve(unsigned int reservedSize)
{
    for (int i = 0; i < reservedSize; i++)
        pushEmptyElement();
}

template<typename T>
void LinkedList<T>::pushEmptyElement()
{
    if (!size)
        firstElement = new Element<T>;
    else
        getLastElement().next = new Element<T>;
    size++;
}

template<typename T>
LinkedList<T>::LinkedList(unsigned int initialSize)
{
    for (unsigned int i = 0; i < initialSize; i++)
        pushEmptyElement();
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin()
{
    return LinkedList<T>::iterator(firstElement);
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::end()
{
    return LinkedList<T>::iterator(nullptr);
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& l)
{
    size = l.getSize();
    firstElement = l.firstElement;
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& l)
{
    size = l.getSize();
    firstElement = (Element<T>&&) l.firstElement;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& l)
{
    size = l.getSize();
    firstElement = l.firstElement;
    l.firstElement = nullptr;
    return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& l)
{
    size = l.getSize();
    firstElement = l.firstElement;
    return *this;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
    delete firstElement;
}

template<typename T>
void LinkedList<T>::clear()
{
    delete firstElement;
    firstElement = nullptr;
    size = 0;
}

template<typename T>
void LinkedList<T>::erase(LinkedList::iterator it)
{
    if (!size)
        return;
    if (it == iterator{firstElement})
    {
        delete firstElement;
        firstElement = nullptr;
        size--;
        return;
    }
    iterator before = nullptr;
    for (auto e = begin(); e != end();)
    {
        auto tmp = e++;
        if (tmp == it)
        {
            before = tmp;
            break;
        }
    }
    if (before == iterator{nullptr})
        return;
    before.m_ptr->next = it.m_ptr->next;
    delete it.m_ptr;
    size--;
}

template<typename T>
Element<T>::~Element()
{
    delete next;
}

template<typename T>
Element<T>& Element<T>::operator=(const Element<T>& e)
{
    value = e.value;
    delete next;
    next = new Element<T>;
    *next = *e.next;
    return *this;
}

template<typename T>
Element<T>::Element(const Element<T>& e)
{
    value = e.value;
    delete next;
    next = new Element<T>;
    *next = *e.next;
}

template<typename T>
Element<T>::Element(Element<T>&& e)
{
    value = e.value;
    delete next;
    next = e.next;
    e.next = nullptr;
}

template<typename T>
Element<T>& Element<T>::operator=(Element<T>&& e) noexcept
{
    value = e.value;
    delete next;
    next = e.next;
    e.next = nullptr;
    return *this;
}

#endif //TDDTEST_LINKEDLIST_H
