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

    void serialize_map(const std::string& path_to_write);

    const std::map<std::string, std::vector<std::string>>& get_map()
    {
        return hash_to_names;
    }
};

}  // namespace soundex