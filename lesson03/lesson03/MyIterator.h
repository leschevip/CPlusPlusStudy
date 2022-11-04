#pragma once
//#include <iterator>

using namespace std;

template <typename T>
class MyIterator //: std::iterator<std::input_iterator_tag, T>
{
private:
    T* value;
public:
    MyIterator(T* v) : value(v) 
    {
    }

    MyIterator(const MyIterator& iter) : value(iter.value)
    {
    }

    bool operator!=(MyIterator<T> const& it) const;
    typename T& operator*() const;
    MyIterator& operator++();

};

template <typename T>
bool MyIterator<T>::operator!=(MyIterator<T> const& it) const
{
    return it.value != value;
}

template <typename T>
typename T& MyIterator<T>::operator*() const
{
    return *value;
}

template <typename T>
MyIterator<T>& MyIterator<T>::operator++()
{
    value++;
    return *this;
}