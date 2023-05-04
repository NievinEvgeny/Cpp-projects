#pragma once
#include <iostream>
#include <memory>
#include <utility>

namespace list {

template <typename T>
class Node
{
    T data;
    std::shared_ptr<Node> next;

   public:
    Node(const T& new_data, std::shared_ptr<Node> next_node) : data(std::move(new_data)), next(std::move(next_node))
    {
    }

    const T& get_data() const noexcept
    {
        return data;
    }

    std::shared_ptr<Node> get_next() noexcept
    {
        return next;
    }

    void set_data(const T& new_data) noexcept
    {
        data = new_data;
    }

    void set_data(T&& new_data) noexcept
    {
        data = std::move(new_data);
    }

    void set_next(std::shared_ptr<Node> new_next) noexcept
    {
        next = new_next;
    }
};

template <typename T>
class List
{
    std::shared_ptr<Node<T>> head, tail;
    std::size_t size = 0;

   public:
    explicit List() : head(nullptr), tail(nullptr)
    {
    }

    ~List()
    {
        while (head)
        {
            pop_front();
        }
    }

    void swap(List<T>& other) noexcept
    {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size, other.size);
    }

    List(const List<T>& other) noexcept : head(other.head), tail(other.tail), size(other.size)
    {
    }

    List& operator=(List<T> other) noexcept
    {
        other.swap(*this);
        return *this;
    }

    List(List<T>&& other) noexcept
        : head(std::exchange(other.head, nullptr)),
          tail(std::exchange(other.tail, nullptr)),
          size(std::exchange(other.size, 0))
    {
    }

    std::size_t get_size() const noexcept
    {
        return size;
    }

    void pop_front()
    {
        head = head->get_next();
        --size;
    }

    void push_front(T data)
    {
        std::shared_ptr<Node<T>> new_node = std::make_shared<Node<T>>(data, head);

        if (!head)
        {
            tail = new_node;
        }

        head = new_node;
        ++size;
    }

    void push_back(T data)
    {
        std::shared_ptr<Node<T>> new_node = std::make_shared<Node<T>>(data, nullptr);

        if (head)
        {
            tail->set_next(new_node);
        }
        else
        {
            head = new_node;
        }

        tail = new_node;
        size++;
    }
};

}  // namespace list
