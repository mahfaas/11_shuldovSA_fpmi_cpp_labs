#include <iostream>
#include <string>
#include <algorithm>

bool isVowel(char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

std::string vowToBig(const std::string &input)
{
    std::string result = input;
    for(size_t i = 0; i < result.size(); ++i)
    {
        if(isVowel(result[i]))
        {
            result[i] = (char)toupper(result[i]);
        }
    }
    return result;
}

std::string spaceToPlus(const std::string &input)
{
    std::string result = input;
    for(size_t i = 0; i < result.size(); ++i)
    {
        if(result[i] == ' ')
        {
            result[i] = '+';
        }
    }
    return result;
}

int splitByPlus(const std::string &input, std::string* words, int maxCount)
{
    int count = 0;
    std::string temp = "";
    for(size_t i = 0; i < input.size(); ++i)
    {
        if(input[i] == '+')
        {
            if(!temp.empty() && count < maxCount)
            {
                *(words + count) = temp;
                count++;
                temp.clear();
            }
        }
        else
        {
            temp += input[i];
        }
    }
    if(!temp.empty() && count < maxCount)
    {
        *(words + count) = temp;
        count++;
    }
    return count;
}

void sortWords(std::string* words, int count)
{
    for(int i = 0; i < count - 1; ++i)
    {
        for(int j = i + 1; j < count; ++j)
        {
            if(*(words + j) < *(words + i))
            {
                std::string temp = *(words + i);
                *(words + i) = *(words + j);
                *(words + j) = temp;
            }
        }
    }
}

std::string joinWithPlus(std::string* words, int count)
{
    std::string result = "";
    for(int i = 0; i < count; ++i)
    {
        result += *(words + i);
        if(i != count - 1)
        {
            result += '+';
        }
    }
    return result;
}

std::string sortWords(const std::string &input)
{
    const int MAX_WORDS = 100;
    std::string words[MAX_WORDS];
    int count = splitByPlus(input, words, MAX_WORDS);
    sortWords(words, count);
    return joinWithPlus(words, count);
}

int main()
{
    std::string text;
    std::getline(std::cin, text);

    std::string noSpaces = spaceToPlus(text);
    std::string modified = vowToBig(noSpaces);
    std::string sorted = sortWords(modified);

    std::cout << sorted << std::endl;
    return 0;
}
