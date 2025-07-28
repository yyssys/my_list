#pragma once

template <class T>
struct Node
{
    T data;
    Node *next;
    Node *prev;

    explicit Node(const T &p = T()) : data(p), next(nullptr), prev(nullptr) {}
};

template <class T>
class List;

template <class T>
class Iterator
{
public:
    explicit Iterator(Node<T> *p = nullptr) : ptr(p) {}

    T *operator->() const
    {
        return &(ptr->data);
    }
    T &operator*() const
    {
        return ptr->data;
    }
    Iterator &operator++()
    {
        if (ptr)
            ptr = ptr->next;
        return *this;
    }
    Iterator operator++(int)
    {
        Iterator tmp = *this;
        ++(*this);
        return tmp;
    }
    Iterator &operator--()
    {
        if (ptr)
            ptr = ptr->prev;
        return *this;
    }
    Iterator operator--(int)
    {
        Iterator tmp = *this;
        --(*this);
        return tmp;
    }
    bool operator==(const Iterator &other)
    {
        return ptr == other.ptr;
    }
    bool operator!=(const Iterator &other)
    {
        return ptr != other.ptr;
    }

private:
    Node<T> *ptr = nullptr;
    friend class List<T>;
};

template <class T>
class List
{
public:
    List()
    {
        head = new Node<T>();
        tail = new Node<T>();
        head->next = tail;
        tail->prev = head;
    }
    ~List()
    {
        clear();
        delete head;
        delete tail;
    }
    void clear()
    {
        Node<T> *cur = head->next;
        while (cur != tail)
        {
            Node<T> *next = cur->next;
            delete cur;
            cur = next;
        }
        head->next = tail;
        tail->prev = head;
    }
    List(const List &) = delete;
    List(List &&) = delete;
    List &operator=(const List &) = delete;
    List &operator=(List &&) = delete;

    Iterator<T> insert(Iterator<T> pos, const T &value)
    {
        Node<T> *new_node = new Node<T>(value);
        Node<T> *prev_node = pos.ptr->prev;

        new_node->next = pos.ptr;
        pos.ptr->prev = new_node;

        prev_node->next = new_node;
        new_node->prev = prev_node;

        return Iterator<T>(new_node);
    }
    Iterator<T> erase(Iterator<T> pos)
    {
        Node<T> *cur_node = pos.ptr;
        if (cur_node == head || cur_node == tail)
            return Iterator<T>(tail);

        Node<T> *next_node = cur_node->next;
        cur_node->prev->next = next_node;
        next_node->prev = cur_node->prev;
        delete cur_node;
        return Iterator<T>(next_node);
    }
    void push_back(const T &value)
    {
        insert(end(), value);
    }
    void push_front(const T &value)
    {
        insert(begin(), value);
    }
    Iterator<T> begin() const
    {
        return Iterator<T>(head->next);
    }
    Iterator<T> end() const
    {
        return Iterator<T>(tail);
    }
    void pop_front()
    {
        if (!empty())
            erase(begin());
    }
    void pop_back()
    {
        if (!empty())
            erase(--end());
    }
    void remove(const T &value)
    {
        for (auto it = begin(); it != end();)
        {
            if (*it == value)
            {
                it = erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
    size_t size() const
    {
        size_t num = 0;
        for (auto it = begin(); it != end(); ++it)
            ++num;
        return num;
    }
    bool empty() const
    {
        return head->next == tail;
    }
    T &front()
    {
        return head->next->data;
    }
    T &back()
    {
        return tail->prev->data;
    }

private:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
};