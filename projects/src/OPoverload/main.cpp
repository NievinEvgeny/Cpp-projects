#include <OPoverload/time.hpp>
#include <iostream>

int main()
{
    using namespace timelib::literals;

    try
    {
        const std::size_t num1 = 432000;
        const std::size_t num2 = 86401;

        timelib::Time time(num1);
        timelib::TimeSpan time_span(num2);

        std::cout << time - time_span << '\n';

        const auto pepe = 500000_d;

        if (time < pepe)
        {
            std::cout << "pepega1\n";
        }
        if (time > time_span)
        {
            std::cout << "pepega2\n";
        }
        if (time_span == time_span)
        {
            std::cout << "pepega3\n";
        }
        if (time + time_span != time_span)
        {
            std::cout << "pepega4\n";
        }
    }
    catch (const std::exception& msg)
    {
        std::cerr << msg.what() << '\n';
        return -1;
    }
}