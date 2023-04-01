#pragma once
#include <utility>

namespace smart_ptr {

template <class T>
class unique_ptr
{
   private:
    T* ptr;

   public:
    unique_ptr() : ptr(nullptr)
    {
    }

    explicit unique_ptr(T* ptr) : ptr(ptr)
    {
    }

    ~unique_ptr()
    {
        delete ptr;
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

    T* release() noexcept
    {
        T* result = nullptr;
        std::swap(result, ptr);
        return result;
    }

    void reset() noexcept
    {
        T* tmp = release();
        delete tmp;
    }

    unique_ptr(const unique_ptr& obj) = delete;
    unique_ptr& operator=(const unique_ptr& obj) = delete;

    unique_ptr(unique_ptr&& move_obj) noexcept : ptr(nullptr)
    {
        reset();
        std::swap(ptr, move_obj.ptr);
    }

    unique_ptr& operator=(unique_ptr&& move_obj) noexcept
    {
        reset();
        std::swap(ptr, move_obj.ptr);
        return *this;
    }
};

}  // namespace smart_ptr