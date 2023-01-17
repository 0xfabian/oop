#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <rlutil.h>

std::vector<std::string> parse(const std::string& input);

bool nxstoi(const std::string& s, int& value) noexcept;

class app_error: public std::runtime_error
{
    using std::runtime_error::runtime_error;

public:

    void print(std::ostream& os = std::cerr) const
    {
        rlutil::saveDefaultColor();

        rlutil::setColor(rlutil::LIGHTRED);
        os << "error: ";

        rlutil::resetColor();
        os << what() << std::endl;
    }
};