#pragma once
#include <string_view>
#include <string>

namespace soundex {

std::string soundex_hash(std::string_view name);

}  // namespace soundex