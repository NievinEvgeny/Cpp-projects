#pragma once
#include <map>
#include <vector>
#include <string>

namespace soundex {

class SoundexMapBuilder
{
    std::map<std::string, std::vector<std::string>> hash_to_names;

    void parse_csv(const std::string& filename);

   public:
    explicit SoundexMapBuilder(const std::string& filename)
    {
        parse_csv(filename);
    }

    const std::map<std::string, std::vector<std::string>>& get_map()
    {
        return hash_to_names;
    }

    // TODO write
};

}  // namespace soundex