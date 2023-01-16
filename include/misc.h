#pragma once

#include <vector>
#include <string>

std::vector<std::string> parse(const std::string& input);

bool nxstoi(const std::string& s, int& value) noexcept;