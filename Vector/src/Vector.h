#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm> // std::random_access_iterator_tag
#include <cstddef> // size_t
#include <stdexcept> // std::out_of_range
#include <type_traits> // std::is_same

template <class T>
class Vector {
public:
    class iterator;

private:
    T* array;
    size_t _capacity, _size;

    // You may want to write a function that grows the vector
    void grow() { /* TODO */
    if(_capacity == 0)
    {
        _capacity = _capacity + 1;
    }
    else
    {
        _capacity = _capacity * 2;
    }
    T* newArray = new T[_capacity]();

    for(int i = 0 ; i < _size ; i++)
    {
        newArray[i] = std::move(array[i]);
    }
    delete [] array;
    array = newArray;
}

public:
    Vector() noexcept 
    { /* TODO */ 
        array = nullptr;
        _size = 0;
        _capacity = 0;
    }
    Vector(size_t count, const T& value) 
    { /* TODO */ 
        array = new T[count]();
        _size = count;
        _capacity = count;

        for(int i = 0 ; i < _size ; i++)
        {
            array[i] = value;
        }
    }

    explicit Vector(size_t count) 
    { /* TODO */ 
        array = new T[count]();
        _size = count;
        _capacity = count;
    }
    Vector(const Vector& other) { /* TODO */                        // copy constructor
        array = new T[other._size]();
        _size = other._size;
        _capacity = other._capacity;

        for(int i = 0 ; i < _size ; i++)
        {
            array[i] = other[i];
        } 
    }

    Vector(Vector&& other) noexcept                                   // move constructor
    { /* TODO */ 
        _size = other._size;
        _capacity = other._capacity;
        array = other.array;
        other._size = 0;
        other._capacity = 0;
        other.array = nullptr;
    }                  

    ~Vector() 
    { /* TODO */
        delete[] array;
        array = nullptr;
        _size = 0;
        _capacity = 0;
    }

    Vector& operator=(const Vector& other)                  // copy operator
    { /* TODO */
        if(this == &other)
        {
            return *this;
        }
        delete[] array; 
        _size = other._size;
        _capacity = other._capacity;
        array = new T[other._size]();

        for(int i = 0 ; i < _size ; i++)
        {
            array[i] = other.array[i];
        } 
        return *this;
    }
    Vector& operator=(Vector&& other) noexcept                  // move operator
    { /* TODO */ 
        if(array == other.array)
        {
            return *this;
        }

        delete[] array;
        _size = other._size;
        _capacity = other._capacity;
        array = std::move(other.array);
        other.array = nullptr;

        return *this;

        // array = std::move(other.array);
        // delete[] other.array;
        // other.array = nullptr;

        // return *this;
    }

    iterator begin() noexcept { /* TODO */ return iterator(array); }
    iterator end() noexcept { /* TODO */ return iterator(array + _size); }

    [[nodiscard]] bool empty() const noexcept { /* TODO */ if(_size == 0) return true; else return false;}
    size_t size() const noexcept { /* TODO */ return _size;}
    size_t capacity() const noexcept { /* TODO */ return _capacity;}

    T& at(size_t pos) { /* TODO */ 
    if(pos >= _size) 
    throw std::out_of_range("Error");
    
    return array[pos];
    }

    const T& at(size_t pos) const { /* TODO */  if(pos >= _size) 
    throw std::out_of_range("Error");
    
    return array[pos];
    }

    T& operator[](size_t pos) { /* TODO */ return array[pos]; }
    const T& operator[](size_t pos) const { /* TODO */ return array[pos];}
    T& front() { /* TODO */ return array[0];}
    const T& front() const { /* TODO */ return array[0];}
    T& back() { /* TODO */ return array[_size-1];}
    const T& back() const { /* TODO */ return array[_size-1]; }

    void push_back(const T& value) { /* TODO */ 
    if(_size == _capacity)
    {
        grow();
    }
    _size = _size + 1;
    array[_size-1] = value;}

    void push_back(T&& value) 
    { /* TODO */ 
        if(_size == _capacity)
        {
            grow();
        }
        _size = _size + 1;
        array[_size-1] = std::move(value); 
    }
    void pop_back() { /* TODO */ _size = _size - 1;}

    iterator insert(iterator pos, const T& value) 
    { 
        /* TODO */
        ptrdiff_t insert_index = pos - begin();
        if(_size == _capacity)
        grow();
        for(ptrdiff_t index = _size ; index > insert_index ; index--)
        {
            array[index] = std::move(array[index-1]);           // shifts everything
        }
        array[insert_index] = value;
        ++_size;
        return begin() + insert_index;
     }

    iterator insert(iterator pos, T&& value) 
    { 
        /* TODO */
        ptrdiff_t insert_index = pos - begin();
        if(_size == _capacity)
        grow();
        for(ptrdiff_t index = _size ; index > insert_index ; index--)
        {
            array[index] = std::move(array[index-1]);
        }
        array[insert_index] = std::move(value);
        ++_size;
        return begin() + insert_index; }

    iterator insert(iterator pos, size_t count, const T& value) 
    { 
        /* TODO */ 
        if(count == 0)
        {
            return pos;
        }

        ptrdiff_t insert_index = pos - begin();

        while(_size + count > _capacity)
        {
            grow();
        }

        for(ptrdiff_t index = _size + count - 1 ; index > insert_index + count - 1 ; --index)
        {
            array[index] = std::move(array[index-count]);
        }

        for(size_t index = insert_index ; index < insert_index + count ; index++)
        {
            array[index] = value;
        }

        _size = _size + count;

        return begin() + insert_index;
    }

    iterator erase(iterator pos) 
    { /* TODO */ 
        ptrdiff_t var = pos - begin();

        while(_size - 1 > var)
        {
            array[var] = std::move(array[var+1]);
            var++;
        }
        _size--;

        return pos;
    }
    iterator erase(iterator first, iterator last) 
    { /* TODO */ 
        ptrdiff_t lmf = last - first;
        ptrdiff_t fmb = first -  begin();

        for(int i = fmb ; i < _size - lmf ; i++)
        {
            array[i] = std::move(array[i + lmf]);
        }

        _size = _size - lmf;

        return first;
    }

    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
    private:
        // Add your own data members here
        pointer ptr;
        // HINT: For random_access_iterator, the data member is a pointer 99.9% of the time
    public:

        iterator() 
            { /* TODO */
                ptr = nullptr;
            }

        iterator(pointer p)
        {
            ptr = p;
        } 
        // Add any constructors that you may need

        // This assignment operator is done for you, please do not add more
        iterator& operator=(const iterator&) noexcept = default;

        [[nodiscard]] reference operator*() const noexcept { /* TODO */ return *ptr; }
        [[nodiscard]] pointer operator->() const noexcept { /* TODO */ return ptr;}

        // Prefix Increment: ++a
        iterator& operator++() noexcept { /* TODO */ ++ptr; return *this;}
        // Postfix Increment: a++
        iterator operator++(int) noexcept { /* TODO */ iterator x = *this; operator++(); return x; }
        // Prefix Decrement: --a
        iterator& operator--() noexcept { /* TODO */ --ptr; return *this; }
        // Postfix Decrement: a--
        iterator operator--(int) noexcept { /* TODO */ iterator x = *this; operator--(); return x;}

        iterator& operator+=(difference_type offset) noexcept { /* TODO */ ptr += offset; return *this; }
        [[nodiscard]] iterator operator+(difference_type offset) const noexcept { /* TODO */ iterator x (ptr+offset); return x;}
        
        iterator& operator-=(difference_type offset) noexcept { /* TODO */ ptr -= offset; *this;}
        [[nodiscard]] iterator operator-(difference_type offset) const noexcept { /* TODO */ iterator x (ptr-offset); return x;}

        [[nodiscard]] difference_type operator-(const iterator& rhs) const noexcept { /* TODO */ return ptr - rhs.ptr;}

        [[nodiscard]] reference operator[](difference_type offset) const noexcept { /* TODO */ return ptr[offset];}

        [[nodiscard]] bool operator==(const iterator& rhs) const noexcept { /* TODO */  return ptr == rhs.ptr; }
        [[nodiscard]] bool operator!=(const iterator& rhs) const noexcept { /* TODO */ return ptr != rhs.ptr; }
        [[nodiscard]] bool operator<(const iterator& rhs) const noexcept { /* TODO */ return ptr < rhs.ptr;}
        [[nodiscard]] bool operator>(const iterator& rhs) const noexcept { /* TODO */ return ptr > rhs.ptr;}
        [[nodiscard]] bool operator<=(const iterator& rhs) const noexcept { /* TODO */ return ptr <= rhs.ptr;}
        [[nodiscard]] bool operator>=(const iterator& rhs) const noexcept { /* TODO */ return ptr >= rhs.ptr;}
    };


    void clear() noexcept 
    { /* TODO */ 

       _size = 0;
    }
};

// This ensures at compile time that the deduced argument _Iterator is a Vector<T>::iterator
// There is no way we know of to back-substitute template <typename T> for external functions
// because it leads to a non-deduced context
namespace {
    template <typename _Iterator>
    using is_vector_iterator = std::is_same<typename Vector<typename _Iterator::value_type>::iterator, _Iterator>;
}

template <typename _Iterator, bool _enable = is_vector_iterator<_Iterator>::value>
[[nodiscard]] _Iterator operator+(typename _Iterator::difference_type offset, _Iterator const& iterator) noexcept { /* TODO */ return (iterator + offset);}

#endif
