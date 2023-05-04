#include <smartptr/unique_ptr.hpp>
#include <smartptr/shared_ptr.hpp>
#include <string>
#include <iostream>

int main()
{
    bool ptr_type = true;

    if (!ptr_type)
    {
        auto* str_ptr = new std::string("this is a string");
        smart_ptr::unique_ptr<std::string> u_ptr(str_ptr);

        std::cout << "check constructor\n\n" << *u_ptr << '\n';
        std::cout << u_ptr.get() << "\n\n";

        auto* str_ptr2 = new std::string("new string");
        smart_ptr::unique_ptr<std::string> u_ptr2(str_ptr2);

        std::cout << *u_ptr2 << '\n';
        std::cout << u_ptr2.get() << "\n\n";

        u_ptr2 = std::move(u_ptr);

        std::cout << "check move assignment ptr2 <- ptr\n\n" << *u_ptr2 << '\n';
        std::cout << u_ptr2.get() << "\n\n";

        smart_ptr::unique_ptr<std::string> u_ptr3(std::move(u_ptr2));

        std::cout << "check move constructor ptr3 <- ptr2\n\n" << *u_ptr3 << '\n';
        std::cout << u_ptr3.get() << '\n';
    }
    else
    {
        auto* string1 = new std::string("shared string");
        smart_ptr::shared_ptr<std::string> s_ptr1(string1);

        std::cout << *s_ptr1 << ' ' << s_ptr1.get() << ' ' << s_ptr1.use_count() << "\n\n";

        smart_ptr::shared_ptr<std::string>& s_ptr2(s_ptr1);

        std::cout << *s_ptr1 << ' ' << s_ptr1.get() << ' ' << s_ptr1.use_count() << '\n';
        std::cout << *s_ptr2 << ' ' << s_ptr2.get() << ' ' << s_ptr2.use_count() << "\n\n";

        smart_ptr::shared_ptr<std::string> s_ptr3 = s_ptr2;

        std::cout << *s_ptr1 << ' ' << s_ptr1.get() << ' ' << s_ptr1.use_count() << '\n';
        std::cout << *s_ptr2 << ' ' << s_ptr2.get() << ' ' << s_ptr2.use_count() << '\n';
        std::cout << *s_ptr3 << ' ' << s_ptr3.get() << ' ' << s_ptr3.use_count() << "\n\n";

        smart_ptr::shared_ptr<std::string> s_ptr4(std::move(s_ptr3));

        std::cout << *s_ptr1 << ' ' << s_ptr1.get() << ' ' << s_ptr1.use_count() << '\n';
        std::cout << *s_ptr2 << ' ' << s_ptr2.get() << ' ' << s_ptr2.use_count() << '\n';
        std::cout << *s_ptr4 << ' ' << s_ptr4.get() << ' ' << s_ptr4.use_count() << "\n\n";

        smart_ptr::shared_ptr<std::string> s_ptr5 = std::move(s_ptr4);

        std::cout << *s_ptr1 << ' ' << s_ptr1.get() << ' ' << s_ptr1.use_count() << '\n';
        std::cout << *s_ptr2 << ' ' << s_ptr2.get() << ' ' << s_ptr2.use_count() << '\n';
        std::cout << *s_ptr5 << ' ' << s_ptr5.get() << ' ' << s_ptr5.use_count() << "\n\n";
    }
}