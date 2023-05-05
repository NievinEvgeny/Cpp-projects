#include <list/list.hpp>
#include <gtest/gtest.h>

#include <vector>

TEST(list, add_remove)
{
    list::List<int> list;

    list.push_back(6);
    list.push_back(7);
    list.push_front(8);
    list.push_front(9);

    const std::vector<int> expected_result1 = {9, 8, 6, 7};

    auto iter = list.begin();
    for (std::size_t index = 0; index < list.get_size(); index++)
    {
        EXPECT_EQ(expected_result1.at(index), *iter);
        ++iter;
    }

    list.pop_front();
    list.pop_front();
    list.pop_front();

    constexpr int expected_result2 = 7;
    EXPECT_EQ(*list.begin(), expected_result2);
}

TEST(list, move_assignment)
{
    list::List<int> list_orig;
    list_orig.push_back(0);
    list_orig.push_back(1);
    list_orig.push_back(2);

    list::List<int> list_moved = std::move(list_orig);

    int expect = 0;

    for (const auto& num : list_moved)
    {
        EXPECT_EQ(num, expect);
        ++expect;
    }
}

TEST(list, move_constructor)
{
    list::List<int> list_orig;
    list_orig.push_back(0);
    list_orig.push_back(1);
    list_orig.push_back(2);

    list::List<int> list_moved{std::move(list_orig)};

    int expect = 0;

    for (const auto& num : list_moved)
    {
        EXPECT_EQ(num, expect);
        ++expect;
    }
}

TEST(list, copy_assignment)
{
    list::List<int> list_orig;
    list_orig.push_back(0);
    list_orig.push_back(1);
    list_orig.push_back(2);

    list::List<int> list_moved = list_orig;

    int expect = 0;

    for (const auto& num : list_moved)
    {
        EXPECT_EQ(num, expect);
        ++expect;
    }
}

TEST(list, copy_constructor)
{
    list::List<int> list_orig;
    list_orig.push_back(0);
    list_orig.push_back(1);
    list_orig.push_back(2);

    list::List<int> list_moved{list_orig};

    int expect = 0;

    for (const auto& num : list_moved)
    {
        EXPECT_EQ(num, expect);
        ++expect;
    }
}

TEST(iterator, no_loop)
{
    list::List<int> list;

    for (int index = 0; index < 5; index++)
    {
        list.push_back(index);
    }

    EXPECT_EQ(list.cycle_search(), false);
}

TEST(iterator, bad_index)
{
    list::List<int> list;

    for (int index = 0; index < 5; index++)
    {
        list.push_back(index);
    }

    list.create_cycle(10);

    EXPECT_EQ(list.cycle_search(), false);
}

TEST(iterator, cycle_impossible)
{
    list::List<int> list;

    for (int index = 0; index < 1; index++)
    {
        list.push_back(index);
    }

    list.create_cycle(0);

    EXPECT_EQ(list.cycle_search(), false);
}

TEST(iterator, cycle_created_and_deleted)
{
    list::List<int> list;

    for (int index = 0; index < 5; index++)
    {
        list.push_back(index);
    }

    list.create_cycle(3);

    EXPECT_EQ(list.cycle_search(), true);

    list.delete_cycle();

    EXPECT_EQ(list.cycle_search(), false);
}
