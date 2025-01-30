#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

[[noreturn]] void exitWithError(const std::string& s) noexcept {
    std::cerr << "[ERROR] " << s << "\n";
    std::exit(EXIT_FAILURE);
}
