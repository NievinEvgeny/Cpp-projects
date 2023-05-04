#include <list/list.hpp>
#include <iostream>
#include <string>

int main()
{
    list::List<std::string> test;
    test.push_back("test_str_1");
    test.push_front("test_str_2");
    test.pop_front();
    list::List<std::string> test1 = test;
    std::cout << test1.get_size() << '\n';
    list::List<std::string> test2 = std::move(test1);
    std::cout << test2.get_size() << '\n';
    list::List<std::string> test3{std::move(test2)};
    std::cout << test3.get_size() << '\n';
    list::List<std::string> test4{test3};
    std::cout << test4.get_size() << '\n';
}