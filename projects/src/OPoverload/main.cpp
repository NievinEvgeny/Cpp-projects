#include <OPoverload/time.hpp>
#include <iostream>

int main()
{
    try
    {
        const std::size_t num2 = 432000;
        const std::size_t num1 = 86401;

        timelib::Time time(num1);
        timelib::TimeSpan time_span(num2);

        std::cout << time - time_span << '\n';
    }
    catch (const std::exception& msg)
    {
        std::cerr << msg.what() << '\n';
        return -1;
    }
}