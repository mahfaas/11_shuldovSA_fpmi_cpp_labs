#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>


std::ifstream openFile(const std::string& fileName)
{
    if (fileName.empty())
    {
        throw std::invalid_argument("File name is empty.");
    }

    std::ifstream in(fileName);
    if (!in.is_open())
    {
        throw std::runtime_error("Failed to open file: " + fileName);
    }
    return in;
}


std::vector<std::string> readLines(std::istream& in)
{
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(in, line))
    {
        lines.push_back(line);
    }

    if (lines.empty())
    {
        throw std::runtime_error("File is empty: no lines to process.");
    }

    return lines;
}

bool isLatin(unsigned char ch)
{
    return (ch >= static_cast<unsigned char>('A') && ch <= static_cast<unsigned char>('Z')) ||
           (ch >= static_cast<unsigned char>('a') && ch <= static_cast<unsigned char>('z'));
}

char toLowerLatin(unsigned char ch)
{
    if (ch >= static_cast<unsigned char>('A') && ch <= static_cast<unsigned char>('Z'))
    {
        return static_cast<char>(ch - static_cast<unsigned char>('A') + static_cast<unsigned char>('a'));
    }
    return static_cast<char>(ch);
}

std::pair<std::size_t, std::size_t> findBest(const std::string& line)
{
    std::size_t bestLen = 0;
    std::size_t bestStart = 0;

    std::size_t i = 0;
    while (i < line.size())
    {
        const unsigned char ch = static_cast<unsigned char>(line[i]);
        if (!isLatin(ch))
        {
            ++i;
            continue;
        }

        const char letter = toLowerLatin(ch);
        const std::size_t start = i;

        std::size_t len = 1;
        ++i;

        while (i < line.size())
        {
            const unsigned char next = static_cast<unsigned char>(line[i]);
            if (!isLatin(next))
            {
                break;
            }
            if (toLowerLatin(next) != letter)
            {
                break;
            }
            ++len;
            ++i;
        }

        if (len > bestLen)
        {
            bestLen = len;
            bestStart = start;
        }
    }

    return {bestLen, bestStart};
}

std::vector<std::pair<std::size_t, std::size_t>> computeRuns(const std::vector<std::string>& lines)
{
    std::vector<std::pair<std::size_t, std::size_t>> runs;
    runs.reserve(lines.size());
 
    for (const std::string& line : lines)
    {
        runs.push_back(findBest(line));
    }

    return runs;
}

std::size_t getMaxLen(const std::vector<std::pair<std::size_t, std::size_t>>& runs)
{
    std::size_t mx = 0;
    for (const auto& r : runs)
    {
        if (r.first > mx)
        {
            mx = r.first;
        }
    }
    return mx;
}

std::vector<std::size_t> collectIndices(const std::vector<std::pair<std::size_t, std::size_t>>& runs, std::size_t maxLen)
{
    std::vector<std::size_t> idx;
    for (std::size_t i = 0; i < runs.size(); ++i)
    {
        if (runs[i].first == maxLen)
        {
            idx.push_back(i);
        }
    }
    return idx;
}

std::vector<std::size_t> takeFirst(const std::vector<std::size_t>& indices, std::size_t n)
{
    std::vector<std::size_t> out;
    const std::size_t cnt = (indices.size() < n) ? indices.size() : n;
    out.reserve(cnt);

    for (std::size_t i = 0; i < cnt; ++i)
    {
        out.push_back(indices[i]);
    }
    return out;
}

void printOne(std::ostream& out, std::size_t lineNumber1Based, const std::string& line, std::size_t start)
{
    out << "Line " << lineNumber1Based << ":\n";
    out << line << "\n";
    out << "Substring start index: " << start << "\n";
    out << "-------------------------------------------------------\n";
}

int main()
{
    try
    {
        const std::string fileName = "input.txt";
        std::ifstream in = openFile(fileName);

        const std::vector<std::string> lines = readLines(in);
        const auto runs = computeRuns(lines);

        const std::size_t maxLen = getMaxLen(runs);
        if (maxLen == 0)
        {
            throw std::runtime_error("No Latin letter substrings found in the file.");
        }

        const std::vector<std::size_t> indices = collectIndices(runs, maxLen);
        const std::vector<std::size_t> firstTen = takeFirst(indices, 10);

        std::cout << "Max substring length: " << maxLen << "\n";
        std::cout << "Lines with that max: " << indices.size() << "\n";

        for (std::size_t k = 0; k < firstTen.size(); ++k)
        {
            const std::size_t i = firstTen[k];
            const std::size_t len = runs[i].first;
            const std::size_t start = runs[i].second;
            printOne(std::cout, i + 1, lines[i], start);
        }

        return 0;
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
    catch (const std::length_error& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
