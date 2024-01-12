#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iomanip>

class Date
{
private:
    int year;
    int month;
    int day;

public:
    Date(int _year, int _month, int _day)
        : year(_year), month(_month), day(_day) {}

    Date() : year(0), month(0), day(0) {}

    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }

    time_t toTimeT() const
    {
        struct tm timeInfo = {};
        timeInfo.tm_year = year - 1900;
        timeInfo.tm_mon = month - 1;
        timeInfo.tm_mday = day;

        return mktime(&timeInfo);
    }
};

class Person
{
protected:
    std::string name;
    std::string address;
    std::string email;

public:
    Person(const std::string &_name, const std::string &_address, const std::string &_email)
        : name(_name), address(_address), email(_email) {}

    const std::string &getName() const { return name; }
    const std::string &getAddress() const { return address; }
    const std::string &getEmail() const { return email; }
};

class Book
{
private:
    int bookID;
    std::string title;
    std::string authorFirstName;
    std::string authorLastName;
    Date dueDate;

public:
    Book(int _bookID, const std::string &_title, const std::string &_authorFirstName,
         const std::string &_authorLastName)
        : bookID(_bookID), title(_title), authorFirstName(_authorFirstName),
          authorLastName(_authorLastName), dueDate(0, 0, 0) {}

    void borrowBook(const Person &borrower, const Date &_dueDate)
    {
        std::cout << "Book " << bookID << " borrowed by " << borrower.getName() << ".\n";
        dueDate = _dueDate;
    }

    void returnBook()
    {
        std::cout << "Book " << bookID << " returned.\n";
        dueDate = Date(0, 0, 0); // Reset due date
    }

    const Date &getDueDate() const { return dueDate; }
    const std::string &getTitle() const { return title; }
};

class Member : public Person
{
private:
    int memberID;
    std::vector<int> booksBorrowed;

public:
    Member(int _memberID, const std::string &_name, const std::string &_address, const std::string &_email)
        : Person(_name, _address, _email), memberID(_memberID) {}

    int getMemberID() const { return memberID; }

    const std::vector<int> &getBooksBorrowed() const { return booksBorrowed; }

    void setBooksBorrowed(int bookID)
    {
        booksBorrowed.push_back(bookID);
    }

    void returnBook(int bookID)
    {
        auto it = std::find(booksBorrowed.begin(), booksBorrowed.end(), bookID);
        if (it != booksBorrowed.end())
        {
            booksBorrowed.erase(it);
        }
    }
};

class Librarian : public Person
{
private:
    int staffID;
    int salary;

public:
    Librarian(int _staffID, const std::string &_name, const std::string &_address, const std::string &_email,
              int _salary)
        : Person(_name, _address, _email), staffID(_staffID), salary(_salary) {}

    void issueBook(int memberID, int bookID, Member &member, Book &book)
    {
        if (book.getDueDate().toTimeT() == 0)
        {
            Date dueDate(2024, 1, 18); // Set a due date (for example, 7 days from today)
            book.borrowBook(static_cast<const Person &>(member), dueDate);
            member.setBooksBorrowed(bookID);
            std::cout << "Book issued successfully.\n";
        }
        else
        {
            std::cout << "Book is already borrowed.\n";
        }
    }

    void returnBook(int bookID, Member &member, Book &book)
    {
        auto it = std::find(member.getBooksBorrowed().begin(), member.getBooksBorrowed().end(), bookID);
        if (it != member.getBooksBorrowed().end())
        {
            book.returnBook();
            member.returnBook(bookID);
            std::cout << "Book returned successfully.\n";
        }
        else
        {
            std::cout << "Book not found in member's borrowed list.\n";
        }
    }

    void displayBorrowedBooks(const Member &member, const std::vector<Book> &books) const
    {
        std::cout << "Books borrowed by " << member.getName() << ":\n";
        for (int bookID : member.getBooksBorrowed())
        {
            const Book &book = books[bookID - 1];
            std::cout << "Book ID: " << bookID << "\n"
                      << "Title: " << book.getTitle() << "\n";
        }
    }
};

int main()
{
    std::vector<Book> books{
        {1, "The Great Gatsby", "F. Scott", "Fitzgerald"},
        {2, "To Kill a Mockingbird", "Harper", "Lee"},
        {3, "1984", "George", "Orwell"},
        {4, "Pride and Prejudice", "Jane", "Austen"},
    };

    std::vector<Member> members{
        {1, "Muhammad", "123 Main St", "muhammad@example.com"},
        {2, "Harry", "456 Oak St", "harry@example.com"},
    };

    Librarian librarian(101, "Librarian Name", "Library St", "librarian@example.com", 50000);

    librarian.issueBook(1, 1, members[0], books[0]);

    librarian.displayBorrowedBooks(members[0], books);
    librarian.displayBorrowedBooks(members[1], books);

    librarian.returnBook(1, members[0], books[0]);
    librarian.displayBorrowedBooks(members[0], books);

    return 0;
}