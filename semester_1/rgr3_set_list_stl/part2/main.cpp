#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

struct Author
{
    std::string surname;
    std::string name;
    std::string patronymic;

    bool operator<(const Author &other) const
    {
        if (surname != other.surname)
            return surname < other.surname;
        if (name != other.name)
            return name < other.name;
        return patronymic < other.patronymic;
    }

    bool operator==(const Author &other) const
    {
        return surname == other.surname &&
               name == other.name &&
               patronymic == other.patronymic;
    }
};

struct Book
{
    int udk = 0;
    std::string title;
    int year = 0;
    std::list<Author> authors;

    void addAuthor(const Author &a)
    {
        std::list<Author>::iterator it = authors.begin();
        while (it != authors.end() && !(a < *it))
        {
            ++it;
        }
        authors.insert(it, a);
    }

    bool removeAuthor(const Author &a)
    {
        for (std::list<Author>::iterator it = authors.begin(); it != authors.end(); ++it)
        {
            if (*it == a)
            {
                authors.erase(it);
                return true;
            }
        }
        return false;
    }
};

class Library
{
private:
    std::list<Book> books_;

public:
    void addBook(const Book &b)
    {
        std::list<Book>::iterator it = books_.begin();
        while (it != books_.end() && it->title <= b.title)
        {
            ++it;
        }
        books_.insert(it, b);
    }

    void deleteBookByTitle(const std::string &title)
    {
        std::list<Book>::iterator it = books_.begin();
        while (it != books_.end())
        {
            if (it->title == title)
            {
                it = books_.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void searchByTitle(const std::string &title) const
    {
        bool found = false;
        for (std::list<Book>::const_iterator it = books_.begin(); it != books_.end(); ++it)
        {
            if (it->title == title)
            {
                printBook(*it);
                found = true;
            }
        }
        if (!found)
        {
            std::cout << "Nothing has found(\n";
        }
    }

    void searchByAuthor(const Author &a) const
    {
        bool found = false;
        for (std::list<Book>::const_iterator it = books_.begin(); it != books_.end(); ++it)
        {
            for (std::list<Author>::const_iterator ia = it->authors.begin(); ia != it->authors.end(); ++ia)
            {
                if (*ia == a)
                {
                    printBook(*it);
                    found = true;
                    break;
                }
            }
        }
        if (!found)
        {
            std::cout << "Nothing has found(\n";
        }
    }

    void addAuthorToBook(const std::string &title, const Author &a)
    {
        Book *b = findFirstByTitle_(title);
        if (b == nullptr)
        {
            throw std::runtime_error("Nothing has found(");
        }
        b->addAuthor(a);
    }

    void deleteAuthorFromBook(const std::string &title, const Author &a)
    {
        Book *b = findFirstByTitle_(title);
        if (b == nullptr)
        {
            throw std::runtime_error("Nothing has found(");
        }
        b->removeAuthor(a);
    }

    void loadFromFile(const std::string &filename)
    {
        std::ifstream in(filename.c_str());
        if (!in)
        {
            throw std::runtime_error("Can't open the file");
        }

        int n = 0;
        in >> n;

        for (int i = 0; i < n; ++i)
        {
            Book b;

            in >> b.udk >> b.title >> b.year;

            int m = 0;
            in >> m;

            for (int j = 0; j < m; ++j)
            {
                Author a;
                in >> a.surname >> a.name >> a.patronymic;
                b.addAuthor(a);
            }

            addBook(b);
        }
    }

    void printAll() const
    {
        if (books_.empty())
        {
            std::cout << "Library is empty\n";
            return;
        }
        for (std::list<Book>::const_iterator it = books_.begin(); it != books_.end(); ++it)
        {
            printBook(*it);
        }
    }

private:
    static void printBook(const Book &b)
    {
        std::cout << "---------------------------------\n";
        std::cout << "Title: " << b.title << "\n";
        std::cout << "UDK: " << b.udk << "\n";
        std::cout << "Year: " << b.year << "\n";
        std::cout << "Authors:\n";
        for (std::list<Author>::const_iterator it = b.authors.begin(); it != b.authors.end(); ++it)
        {
            std::cout << "  " << it->surname << " " << it->name << " " << it->patronymic << "\n";
        }
    }

    Book *findFirstByTitle_(const std::string &title)
    {
        for (std::list<Book>::iterator it = books_.begin(); it != books_.end(); ++it)
        {
            if (it->title == title)
            {
                return &(*it);
            }
        }
        return nullptr;
    }
};

static Author readAuthorFromConsole()
{
    Author a;
    std::cout << "Surname Name Patronymic: ";
    std::cin >> a.surname >> a.name >> a.patronymic;
    return a;
}

static Book readBookFromConsole()
{
    Book b;
    std::cout << "UDK Title Year AuthorsCount: ";
    int m = 0;
    std::cin >> b.udk >> b.title >> b.year >> m;

    for (int i = 0; i < m; ++i)
    {
        std::cout << "Author " << (i + 1) << " (Surname Name Patronymic): ";
        Author a = readAuthorFromConsole();
        b.addAuthor(a);
    }
    return b;
}

int main()
{
    try
    {
        Library lib;

        std::cout << "Enter filename (or 0 to skip): ";
        std::string filename;
        std::cin >> filename;
        if (filename != "0")
        {
            lib.loadFromFile(filename);
        }

        while (true)
        {
            std::cout << "\nMenu:\n";
            std::cout << "1) Print all books\n";
            std::cout << "2) Search book by title\n";
            std::cout << "3) Search books by author\n";
            std::cout << "4) Add book\n";
            std::cout << "5) Delete book by title\n";
            std::cout << "6) Add author to book\n";
            std::cout << "7) Delete author from book\n";
            std::cout << "0) Exit\n";
            std::cout << "Choice: ";

            int cmd = 0;
            std::cin >> cmd;

            if (cmd == 0)
                break;

            if (cmd == 1)
            {
                lib.printAll();
            }
            else if (cmd == 2)
            {
                std::cout << "Title: ";
                std::string t;
                std::cin >> t;
                lib.searchByTitle(t);
            }
            else if (cmd == 3)
            {
                Author a = readAuthorFromConsole();
                lib.searchByAuthor(a);
            }
            else if (cmd == 4)
            {
                Book b = readBookFromConsole();
                lib.addBook(b);
            }
            else if (cmd == 5)
            {
                std::cout << "Title: ";
                std::string t;
                std::cin >> t;
                lib.deleteBookByTitle(t);
            }
            else if (cmd == 6)
            {
                std::cout << "Book title: ";
                std::string t;
                std::cin >> t;
                Author a = readAuthorFromConsole();
                lib.addAuthorToBook(t, a);
            }
            else if (cmd == 7)
            {
                std::cout << "Book title: ";
                std::string t;
                std::cin >> t;
                Author a = readAuthorFromConsole();
                lib.deleteAuthorFromBook(t, a);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }

    return 0;
}
