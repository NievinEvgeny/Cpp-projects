#include <smartptr/unique_ptr.hpp>
#include <smartptr/shared_ptr.hpp>
#include <gtest/gtest.h>

TEST(unique_ptr, dereferencing_check)
{
    auto* str_ptr = new std::string("this is a string");
    smart_ptr::unique_ptr<std::string> u_ptr(str_ptr);
    ASSERT_EQ(*u_ptr, "this is a string");
}

TEST(unique_ptr, move_assignment)
{
    auto* str_ptr = new std::string("this is a string");
    smart_ptr::unique_ptr<std::string> u_ptr(str_ptr);

    auto* str_ptr2 = new std::string("new string");
    smart_ptr::unique_ptr<std::string> u_ptr2(str_ptr2);

    u_ptr = std::move(u_ptr2);

    ASSERT_EQ(*u_ptr, *str_ptr2);
    ASSERT_EQ(u_ptr.get(), str_ptr2);
}

TEST(unique_ptr, move_constructor)
{
    auto* str_ptr = new std::string("this is a string");
    smart_ptr::unique_ptr<std::string> u_ptr(str_ptr);
    smart_ptr::unique_ptr<std::string> u_ptr2(std::move(u_ptr));

    ASSERT_EQ(*u_ptr2, *str_ptr);
    ASSERT_EQ(u_ptr2.get(), str_ptr);
}

TEST(shared_ptr, dereferencing_check)
{
    auto* str_ptr = new std::string("this is a string");
    smart_ptr::shared_ptr<std::string> s_ptr(str_ptr);
    ASSERT_EQ(*s_ptr, *str_ptr);
}

TEST(shared_ptr, copy_assignment)
{
    auto* str_ptr = new std::string("this is a string");
    smart_ptr::shared_ptr<std::string> s_ptr(str_ptr);
    ASSERT_EQ(s_ptr.use_count(), 1);
    smart_ptr::shared_ptr<std::string> s_ptr2 = s_ptr;
    ASSERT_EQ(*s_ptr2, *str_ptr);
    ASSERT_EQ(s_ptr2.use_count(), 2);
}

TEST(shared_ptr, copy_constructor)
{
    auto* str_ptr = new std::string("this is a string");
    smart_ptr::shared_ptr<std::string> s_ptr(str_ptr);
    ASSERT_EQ(s_ptr.use_count(), 1);
    smart_ptr::shared_ptr<std::string> s_ptr2(s_ptr);
    ASSERT_EQ(*s_ptr2, *str_ptr);
    ASSERT_EQ(s_ptr2.use_count(), 2);
}

TEST(shared_ptr, move_assignment)
{
    auto* str_ptr = new std::string("this is a string");
    smart_ptr::shared_ptr<std::string> s_ptr(str_ptr);
    ASSERT_EQ(s_ptr.use_count(), 1);
    smart_ptr::shared_ptr<std::string> s_ptr2 = std::move(s_ptr);
    ASSERT_EQ(*s_ptr2, *str_ptr);
    ASSERT_EQ(s_ptr2.use_count(), 1);
}

TEST(shared_ptr, move_constructor)
{
    auto* str_ptr = new std::string("this is a string");
    smart_ptr::shared_ptr<std::string> s_ptr(str_ptr);
    ASSERT_EQ(s_ptr.use_count(), 1);
    smart_ptr::shared_ptr<std::string> s_ptr2(std::move(s_ptr));
    ASSERT_EQ(*s_ptr2, *str_ptr);
    ASSERT_EQ(s_ptr2.use_count(), 1);
}