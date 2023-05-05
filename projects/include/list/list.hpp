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

    void pop_front()
    {
        head = head->get_next();
        --size;
    }

    void create_cycle(std::size_t elem_index)
    {
        if ((size >= 2) && (elem_index <= size - 2))
        {
            std::shared_ptr<Node<T>> curr = head;

            for (std::size_t index = 0; index < elem_index; index++)
            {
                curr = curr->get_next();
            }

            tail->set_next(curr);
        }
    }

    void delete_cycle()
    {
        if (head)
        {
            tail->set_next(nullptr);
        }
    }

    bool cycle_search()
    {
        Iterator turtle_iter(head, 1);
        Iterator bunny_iter(head, 2);

        for (std::size_t index = 0; index < size; index++)
        {
            ++turtle_iter;
            ++bunny_iter;

            if ((turtle_iter == bunny_iter) && (turtle_iter != end()) && (bunny_iter != end()))
            {
                return true;
            }
        }

        return !(turtle_iter == end() && (bunny_iter == end()));
    }

    class Iterator
    {
        std::shared_ptr<Node<T>> node;
        std::size_t step = 1;

       public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator() : node(nullptr)
        {
        }

        explicit Iterator(std::shared_ptr<Node<T>> new_node, std::size_t new_step = 1)
            : node(std::move(new_node)), step(new_step)
        {
        }

        bool operator==(const Iterator& other) const noexcept
        {
            return node == other.node;
        }

        bool operator!=(const Iterator& other) const noexcept
        {
            return !(node == other.node);
        }

        Iterator& operator++() noexcept
        {
            for (std::size_t iter = 0; iter < step; iter++)
            {
                if (this->node != nullptr)
                {
                    this->node = this->node->get_next();
                    continue;
                }
                break;
            }
            return *this;
        }

        Iterator operator++(int) noexcept
        {
            auto old = *this;
            operator++();
            return old;
        }

        T operator*() const noexcept
        {
            return node->get_data();
        }

        T* operator->() const noexcept
        {
            return node->get_data();
        }
    };

    Iterator begin()
    {
        return Iterator(head);
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }
};

}  // namespace list
