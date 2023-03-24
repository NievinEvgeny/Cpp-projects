#include <soundex/soundex_map.hpp>
#include <soundex/soundex.hpp>
#include <rapidcsv.h>
#include <filesystem>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>

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
}

}  // namespace soundex