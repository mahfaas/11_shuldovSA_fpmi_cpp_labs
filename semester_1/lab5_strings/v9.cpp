#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cctype>

bool isVowel(char ch)
{
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'y';
}

void transformString(std::string &s)
{
    for (char &ch : s)
    {
        if (isVowel(ch))
        {
            ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
        }
        else if (ch == ' ')
        {
            ch = '+';
        }
    }
}

std::vector<std::string> split(const std::string &s, char delimiter)
{
    std::vector<std::string> words;
    std::string current;

    for (char ch : s)
    {
        if (ch == delimiter)
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

std::string join(const std::vector<std::string> &words, char delimiter)
{
    std::string result;

    for (std::size_t i = 0; i < words.size(); ++i)
    {
        if (i > 0)
        {
            result.push_back(delimiter);
        }
        result += words[i];
    }

    return result;
}

std::string sortWords(const std::string& line)
{
    std::vector<std::string> words = split(line, '+');

    if (words.empty())
    {
        throw std::logic_error("No words found after transformation");
    }

    std::sort(words.begin(), words.end());
    return join(words, '+');
}

std::string transform(const std::string &line)
{
    if (line.empty())
    {
        throw std::invalid_argument("Input string is empty");
    }

    std::string transformed = line;

    transformString(transformed);

    return transformed;
}

std::string readLine()
{
    std::string line;
    if (!std::getline(std::cin, line))
    {
        throw std::runtime_error("Failed to read input line");
    }
    return line;
}

int main()
{
    try
    {
        std::string line = readLine();
        std::string result = transform(line);
        result = sortWords(result);
        std::cout << "Result: " << result << '\n';
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Invalid argument: " << e.what() << '\n';
        return 1;
    }
    catch (const std::logic_error &e)
    {
        std::cerr << "Logic error: " << e.what() << '\n';
        return 1;
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Runtime error: " << e.what() << '\n';
        return 1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
