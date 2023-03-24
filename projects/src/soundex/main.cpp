#include <soundex/soundex.hpp>
#include <soundex/soundex_map.hpp>
#include <string>
#include <iostream>
#include <stdexcept>

#include <nlohmann/json.hpp>
#include <fstream>

int main()
{
    try
    {
        const std::string filename = "names.csv";
        soundex::SoundexMapBuilder soundex_map(filename);

        nlohmann::json j = soundex_map.get_map();
        std::ofstream file;
        file.open("names.csv");
        file << std::setw(4) << j;
        file.close();
    }
    catch (const std::exception& msg)
    {
        std::cerr << msg.what() << '\n';
        return -1;
    }
}