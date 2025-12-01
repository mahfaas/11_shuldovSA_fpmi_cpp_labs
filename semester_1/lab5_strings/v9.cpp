#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cctype>

bool IsLatinVowelLower(char ch)
{
    return ch == 'a' || ch == 'e' || ch == 'i' ||
           ch == 'o' || ch == 'u' || ch == 'y';
}

void ReplaceVowelsAndSpaces(std::string &s)
{
    for (char &ch : s)
    {
        if (IsLatinVowelLower(ch))
        {
            ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
        }
        else if (ch == ' ')
        {
            ch = '+';
        }
    }
}

std::vector<std::string> SplitIntoWords(const std::string &s)
{
    std::vector<std::string> words;
    std::string current;

    for (char ch : s)
    {
        if (ch == '+')
        {
            if (!current.empty())
            {
                words.push_back(current);
                current.clear();
            }
        }
        else
        {
            current.push_back(ch);
        }
    }

    if (!current.empty())
    {
        words.push_back(current);
    }

    return words;
}

std::string JoinWords(const std::vector<std::string> &words)
{
    std::string result;

    for (std::size_t i = 0; i < words.size(); ++i)
    {
        if (i > 0)
        {
            result.push_back('+');
        }
        result += words[i];
    }

    return result;
}

std::string TransformAndSort(const std::string &line)
{
    if (line.empty())
    {
        throw std::runtime_error("Error: input string is empty!");
    }

    std::string s = line;

    ReplaceVowelsAndSpaces(s);

    std::vector<std::string> words = SplitIntoWords(s);

    if (words.empty())
    {
        throw std::runtime_error("Error: no words found in the string!");
    }

    std::sort(words.begin(), words.end());

    return JoinWords(words);
}

int main()
{
    try
    {
        std::cout << "Enter a string:\n";

        std::string line;
        if (!std::getline(std::cin, line))
        {
            throw std::runtime_error("Error: failed to read input line!");
        }

        std::string result = TransformAndSort(line);

        std::cout << "Result: " << result << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
