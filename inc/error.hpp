#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

[[noreturn]] void exit_with_error(const std::string& s) noexcept {
    std::cerr << "[ERROR] " << s << "\n";
    std::exit(EXIT_FAILURE);
}
