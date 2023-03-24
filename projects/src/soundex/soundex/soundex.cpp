#include <soundex/soundex.hpp>
#include <algorithm>
#include <string_view>
#include <string>
#include <stdexcept>
#include <unordered_map>

namespace soundex {

static void str_toupper(std::string& s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::toupper(c); });
}

static bool check_name_correctness(std::string_view name)
{
    return std::all_of(name.begin(), name.end(), [](const unsigned char symbol) { return std::isalpha(symbol); });
}

static void remove_hw(std::string& hash)
{
    hash.erase(
        std::remove_if(
            hash.begin() + 1, hash.end(), [](const char letter) { return (letter == 'H' || letter == 'W'); }),
        hash.end());
}

static void convert_letter(char& letter)
{
    static const std::unordered_map<char, char> сonsonants_to_num
        = {{'B', '1'},
           {'F', '1'},
           {'P', '1'},
           {'V', '1'},
           {'C', '2'},
           {'G', '2'},
           {'J', '2'},
           {'K', '2'},
           {'Q', '2'},
           {'S', '2'},
           {'X', '2'},
           {'Z', '2'},
           {'D', '3'},
           {'T', '3'},
           {'L', '4'},
           {'M', '5'},
           {'N', '5'},
           {'R', '6'}};

    if (сonsonants_to_num.find(letter) != сonsonants_to_num.end())
    {
        letter = сonsonants_to_num.at(letter);
    }
}

static void letters_to_nums(std::string& hash)
{
    std::for_each(hash.begin(), hash.end(), convert_letter);
}

static bool comparison_nums(char num1, char num2)
{
    return isdigit(num1) ? num1 == num2 : false;
}

static void unique_nums(std::string& hash)
{
    hash.erase(std::unique(hash.begin(), hash.end(), comparison_nums), hash.end());
}

static void remove_vowels(std::string& hash)
{
    constexpr std::string_view vowels = "AEIOUY";

    hash.erase(
        remove_if(hash.begin() + 1, hash.end(), [&](char letter) { return vowels.find(letter) != std::string::npos; }),
        hash.end());
}

std::string soundex_hash(std::string_view name)
{
    if (!check_name_correctness(name))
    {
        throw std::runtime_error{"Name contains unexpected symbols"};
    }

    std::string name_hash{name};
    str_toupper(name_hash);

    const char first_letter = name_hash.front();

    remove_hw(name_hash);
    letters_to_nums(name_hash);
    unique_nums(name_hash);
    remove_vowels(name_hash);

    constexpr short hash_length = 4;
    name_hash.resize(hash_length, '0');

    name_hash.at(0) = first_letter;

    return name_hash;
}

}  // namespace soundex
