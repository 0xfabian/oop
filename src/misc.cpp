#include "misc.h"

std::vector<std::string> parse(const std::string& input)
{
    std::vector<std::string> ret;

    std::string word;
    bool in_word = false;
    bool in_quotes = false;

    for (const char& c : input)
    {
        if (isspace(c))
        {
            if (in_quotes)
            {
                in_word = true;
                word.push_back(c);
            }
            else if (in_word)
            {
                in_word = false;
                ret.push_back(word);
                word.clear();
            }
        }
        else
        {
            if (c == '"')
                in_quotes = !in_quotes;
            else
            {
                in_word = true;
                word.push_back(c);
            }
        }
    }

    if (in_word)
        ret.push_back(word);

    return ret;
}

bool nxstoi(const std::string& s, int& value) noexcept
{
    try
    {
        value = std::stoi(s);
    }
    catch (...)
    {
        return false;
    }

    return true;
}