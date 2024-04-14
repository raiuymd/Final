#include "AccountUtils.h"
#include <filesystem>

bool AccountUtils::accountExists(const std::string& accountId) {
    std::string filename = accountId + ".txt";
    return std::filesystem::exists(filename);
}
