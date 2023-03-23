#include <soundex/soundex.hpp>
#include <string>
#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        std::string name_hash = soundex::soundex_hash("mmonium");

        std::cout << name_hash << '\n';
    }
    catch (const std::exception& msg)
    {
        std::cerr << msg.what() << '\n';
        return -1;
    }
}