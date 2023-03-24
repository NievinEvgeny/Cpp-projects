#include <soundex/soundex.hpp>
#include <soundex/soundex_map.hpp>
#include <cxxopts.hpp>
#include <string>
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[])
{
    cxxopts::Options options("Soundex");

    // clang-format off
    options.add_options()
        ("w,file_to_write", "Path for file to write", cxxopts::value<std::string>()->default_value("soundex.csv"))
        ("c,csv_file", "Path for *.csv file", cxxopts::value<std::string>()->default_value("names.csv"))
        ("h,help", "Print usage");
    // clang-format on

    try
    {
        const auto parse_cmd_line = options.parse(argc, argv);

        if (parse_cmd_line.count("help"))
        {
            std::cout << options.help() << '\n';
            return 0;
        }

        const std::string csv_file = parse_cmd_line["csv_file"].as<std::string>();
        const std::string file_to_write = parse_cmd_line["file_to_write"].as<std::string>();

        soundex::SoundexMapBuilder soundex_map(csv_file);
        soundex_map.serialize_map(file_to_write);
    }
    catch (const std::exception& msg)
    {
        std::cerr << msg.what() << '\n';
        return -1;
    }
}