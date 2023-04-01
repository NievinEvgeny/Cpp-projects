#pragma once
#include <utility>
#include <cstddef>

namespace smart_ptr {

template <class T>
class shared_ptr
{
   private:
    T* ptr;
    std::size_t* count;

   public:
    shared_ptr() : ptr(nullptr), count(new std::size_t(0))
    {
    }

    explicit shared_ptr(T* obj_ptr) : ptr(obj_ptr), count(new std::size_t(1))
    {
    }

    ~shared_ptr()
    {
        if (--(*count) == 0)
        {
            delete ptr;
            delete count;
        }
    }

    T& operator*() const noexcept
    {
        return *ptr;
    }

    T* operator->() const noexcept
    {
        return ptr;
    }

    T* get() const noexcept
    {
        return ptr;
    }

    std::size_t use_count() const noexcept
    {
        return *count;
    }

    void swap(shared_ptr& other) noexcept
    {
        std::swap(ptr, other.ptr);
        std::swap(count, other.count);
    }

    void reset(T* p = nullptr) noexcept
    {
        shared_ptr(p).swap(*this);
    }

    shared_ptr(const shared_ptr& copy) noexcept : ptr(copy.ptr), count(copy.count)
    {
        ++(*count);
    }

    shared_ptr& operator=(shared_ptr rhs) noexcept
    {
        rhs.swap(*this);
        return *this;
    }

    shared_ptr(shared_ptr&& move) noexcept : ptr(move.ptr), count(move.count)
    {
        move.ptr = nullptr;
        move.count = new std::size_t(1);
    }

    shared_ptr& operator=(shared_ptr&& move) noexcept
    {
        shared_ptr(std::move(move)).swap(*this);
        return *this;
    }
};

}  // namespace smart_ptr