#include <soundex/soundex_map.hpp>
#include <soundex/soundex.hpp>
#include <rapidcsv.h>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

namespace soundex {

void SoundexMapBuilder::parse_csv(const std::string& filename)
{
    const std::filesystem::path doc_names(filename);

    if (!std::filesystem::exists(doc_names))
    {
        throw std::runtime_error{'"' + filename + '"' + " not found"};
    }

    rapidcsv::Document csv_doc(filename, rapidcsv::LabelParams(-1, -1), rapidcsv::SeparatorParams(','));

    constexpr short name_column_id = 0;

    const std::vector<std::string> names = csv_doc.GetColumn<std::string>(name_column_id);

    std::for_each(names.begin(), names.end(), [this](const std::string& name) {
        return hash_to_names[soundex::soundex_hash(name)].push_back(name);
    });

    std::for_each(hash_to_names.begin(), hash_to_names.end(), [](auto& pair) {
        return std::sort(pair.second.begin(), pair.second.end());
    });
}

void SoundexMapBuilder::serialize_map(const std::string& path_to_write)
{
    nlohmann::json j = hash_to_names;
    std::ofstream file;
    file.open(path_to_write);
    file << std::setw(4) << j;
    file.close();
}

}  // namespace soundex