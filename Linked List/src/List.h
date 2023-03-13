#pragma once

#include <cstddef> // size_t
#include <iterator> // std::bidirectional_iterator_tag
#include <type_traits> // std::is_same, std::enable_if

template <class T>
class List {
    private:
    struct Node {
        Node *next, *prev;
        T data;
        explicit Node(Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev} {}
        explicit Node(const T& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{data} {}
        explicit Node(T&& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{std::move(data)} {}
    };

    template <typename pointer_type, typename reference_type>
    class basic_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = pointer_type;
        using reference         = reference_type;
    private:
        friend class List<value_type>;
        using Node = typename List<value_type>::Node;

        Node* node;

        explicit basic_iterator(Node* ptr) noexcept : node{ptr} {}
        explicit basic_iterator(const Node* ptr) noexcept : node{const_cast<Node*>(ptr)} {}

    public:
        basic_iterator() { /* TODO */ node = nullptr;}
        basic_iterator(const basic_iterator&) = default;
        basic_iterator(basic_iterator&&) = default;
        ~basic_iterator() = default;
        basic_iterator& operator=(const basic_iterator&) = default;
        basic_iterator& operator=(basic_iterator&&) = default;

        reference operator*() const { return this->node->data;
            // TODO
        }
        pointer operator->() const { return &(this->node->data);
            // TODO
        }

        // Prefix Increment: ++a
        basic_iterator& operator++() 
        { 
            if(node == nullptr)
            {
                return *this;
            }
            node = node->next;   
            return *this;

            // TODO
        }
        // Postfix Increment: a++
        basic_iterator operator++(int) { 
            if(node == nullptr)
            {
                return *this;
            }
            basic_iterator iter = *this;
            node = node->next;   
            return iter;
            // TODO
        }
        // Prefix Decrement: --a
        basic_iterator& operator--() {
             if(node == nullptr)
            {
                return *this;
            }
            node = node->prev;   
            return *this;
            // TODO
        }
        // Postfix Decrement: a--
        basic_iterator operator--(int) {
            if(node == nullptr)
            {
                return *this;
            }
            basic_iterator iter = *this;
            node = node->prev;   
            return iter;
            // TODO
        }

        bool operator==(const basic_iterator& other) const noexcept {return node == other.node;
            // TODO
        }
        bool operator!=(const basic_iterator& other) const noexcept {return (node!= other.node);        // Error???
            // TODO
        }
    };

public:
    using value_type      = T;
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator        = basic_iterator<pointer, reference>;
    using const_iterator  = basic_iterator<const_pointer, const_reference>;

private:
    Node head, tail;
    T* linkList;
    size_type _size;

public:
    List() 
    {
        head.next = &tail;
        tail.prev = &head;
        _size = 0;
        // TODO - Don't forget the list initialier
        
    }

   List(size_type count, const T& value) 
   {
        head.next = &tail;
        tail.prev = &head;
        _size = 0;
        for (size_type i = 0; i < count; ++i) 
        {
            insert(iterator(&tail), value);
        }
    }
    
    explicit List( size_type count ) {
        // TODO - Don't forget the list initialier
        head.next = &tail;
        tail.prev = &head;
        _size = 0;
        for (size_type i = 0; i < count; ++i) 
        {
            insert(iterator(&tail), T());
        }
    }
    List(const List& other )                   // copy
    {
        // TODO - Don't forget the list initialier
        Node* newNode;

        head.next = &tail;
        tail.prev = &head;
        _size = 0 ;

        newNode = other.head.next;
        for(size_t i = 0 ; i < other._size ; i++)
        {
            push_back(newNode->data);
            newNode = newNode->next;
        }
    }
  
    List(List&& other) {                    // move

        head.next = &tail;
        tail.prev = &head;
        _size = 0 ;

        if(other.empty())
        {
            return;
        }
        else
        {
            head.next = other.head.next;
            tail.prev = other.tail.prev;
        
            head.next->prev = &head;
            tail.prev->next = &tail;

            other.head.next = &(other.tail);
            other.tail.prev = &(other.head);

            _size = other.size();
            other._size = 0;
        }
        
    }
   ~List() {
        clear();
    }

    List& operator=( const List& other )        // operator copy
    {
        if (this != &other) 
        {  clear();

            Node* newNode;

            head.next = &tail;
            tail.prev = &head;
            _size = 0 ;

            newNode = other.head.next;
            for(size_t i = 0 ; i < other._size ; i++)
            {
                push_back(newNode->data);
                newNode = newNode->next;
            }
        }
        return *this;
    }
       
    

    List& operator=( List&& other ) noexcept                // operator move
    {
        if (this != &other) 
        {  clear();
            head.next = &tail;
            tail.prev = &head;
            _size = 0 ;

        if(other.empty())
        {
            return *this;
        }
        else
        {
            head.next = other.head.next;
            tail.prev = other.tail.prev;
        
            head.next->prev = &head;
            tail.prev->next = &tail;

            other.head.next = &(other.tail);
            other.tail.prev = &(other.head);

            _size = other.size();
            other._size = 0;
        }
        }
            return *this;
        }
              


    reference front() {return head.next->data;
        // TODO
    }
    const_reference front() const {return head.next->data;
        // TODO
    }
	
    reference back() {return tail.prev->data;
        // TODO
    }
    const_reference back() const {return tail.prev->data;
        // TODO
    }
	
    iterator begin() noexcept {
        iterator hNext{head.next};
        return hNext;

        // TODO
    }
    const_iterator begin() const noexcept {
        const_iterator hNext{head.next};
        return hNext;
        // TODO
    }
    const_iterator cbegin() const noexcept {
        const_iterator hNext{head.next};
        return hNext;
        // TODO
    }

    iterator end() noexcept {
        iterator tailItr{&tail};
        return tailItr;
        // TODO
    }
    const_iterator end() const noexcept {
        const_iterator tailItr{&tail};
        return tailItr;
        // TODO
    }
    const_iterator cend() const noexcept {
        const_iterator tailItr{&tail};
        return tailItr;
        // TODO
    }

    bool empty() const noexcept {
        return (_size == 0);
        // TODO
    }

    size_type size() const noexcept {return _size;
        // TODO
    }

    void clear() noexcept {
        // TODO
        Node* prevNode = head.next;
        Node* node = head.next;

        for(size_t i = 0 ; i < _size ; i++)
        {
            prevNode = node;
            node = node->next;
            delete prevNode;
        }
        head.next = &tail;
        tail.prev = &head;
        _size = 0;

    }

    iterator insert( const_iterator pos, const T& value) 
    {
        // TODO
        Node* newNode = new Node(value);

        if(_size == 0)
        {
            newNode->prev = &head;
            newNode->next = &tail;
            head.next = newNode;
            tail.prev = newNode;
            _size = 1;
            return iterator(newNode);
        }

        newNode->next = pos.node;
        newNode->prev = pos.node->prev;
        newNode->prev->next = newNode;
        newNode->next->prev = newNode;
        
        _size = _size + 1;

        return iterator(newNode);
    }
    iterator insert( const_iterator pos, T&& value) {
        // TODO
        Node* newNode = new Node(std::move(value));

        newNode->next = pos.node;
        newNode->prev = pos.node->prev;
        newNode->prev->next = newNode;
        newNode->next->prev = newNode;
        
        _size = _size + 1;

        return iterator(newNode);
    }

    iterator erase(const_iterator pos ) {
        // TODO

        iterator delNode{pos.node->prev->next = pos.node->next};
        pos.node->next->prev = pos.node->prev;

        delete pos.node;

        _size = _size - 1;

        return delNode;
    }

    void push_back( const T& value ) 
    {
        Node* newNode = new Node(value, tail.prev, &tail);
        tail.prev->next = newNode;
        tail.prev = newNode;
        _size++;
        // TODO
    }
    void push_back( T&& value ) 
    {
        Node* newNode = new Node(std::move(value), tail.prev, &tail);
        tail.prev->next = newNode;
        tail.prev = newNode;
        _size++;
        // TODO
    }

    void pop_back() {
        
        iterator del{tail.prev};
        erase(del);
        // TODO
    }
	
    void push_front( const T& value ) {
        Node* newNode = new Node(value, head.next, &head);
        head.next->prev = newNode;
        newNode->next = head.next;
        head.next = newNode;
        _size++;
        // TODO
    }
	void push_front( T&& value ) {
        // TODO
        Node* newNode = new Node(std::move(value), head.next, &head);
        head.next->prev = newNode;
        newNode->next = head.next;
        head.next = newNode;
        _size++;
    }

    void pop_front() {

        erase(cbegin());
        
        // TODO
    }

    /*
      You do not need to modify these methods!
      
      These method provide the non-const complement 
      for the const_iterator methods provided above.
    */
    iterator insert( iterator pos, const T & value) { 
        return insert((const_iterator &) (pos), value);
    }

    iterator insert( iterator pos, T && value ) {
        return insert((const_iterator &) (pos), std::move(value));
    }

    iterator erase( iterator pos ) {
        return erase((const_iterator&)(pos));
    }
};


/*
    You do not need to modify these methods!

    These method provide a overload to compare const and 
    non-const iterators safely.
*/
 
namespace {
    template<typename Iter, typename ConstIter, typename T>
    using enable_for_list_iters = typename std::enable_if<
        std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::iterator, 
            Iter
        >{} && std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::const_iterator,
            ConstIter
        >{}, T>::type;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) == rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) == lhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) != rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) != lhs;
}