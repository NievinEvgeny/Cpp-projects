#include <soundex/soundex.hpp>
#include <soundex/soundex_map.hpp>
#include <string>
#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        const std::string filename = "names.csv";
        const std::string file_to_write = "json_names.csv";
        soundex::SoundexMapBuilder soundex_map(filename);
        soundex_map.serialize_map(file_to_write);
    }
    catch (const std::exception& msg)
    {
        std::cerr << msg.what() << '\n';
        return -1;
    }
}