# Library Record Management System

## About the Project

C++ class named `LibraryRecord` to manage a collection of books. It supports operations such as checking in and out of books, duplicating stock, filtering books, and more. The system is designed to be a part of a larger library management application and can be easily integrated into various contexts.

## Class Definition

`class LibraryRecord` extends `ArrayBag<Book*>`.

### Public Methods

#### Constructors

- `LibraryRecord()`: Default constructor.
- `LibraryRecord(std::string csv_file_name)`: Initializes the LibraryRecord with Book objects from a CSV file.

#### Book Management

- `bool checkIn(Book* new_entry)`: Adds a book to items. Returns true if successful, false otherwise.
- `bool checkOut(Book* an_entry)`: Removes a book from the LibraryRecord and adds it to the check-out history if successful. Returns true if successful, false otherwise.
- `int getCheckOutHistory(Book* an_entry)`: Returns the number of times the referenced Book has been checked out.
- `std::vector<Book*> toVector()`: Converts the LibraryRecord to a vector.
- `void display()`: Outputs the names of the Books in the LibraryRecord and the number of times each Book has been checked out.
- `void displayTitles()`: Prints the titles of each Book in the LibraryRecord.
- `bool duplicateStock()`: Duplicates all the items in the LibraryRecord. Returns true if successful, false otherwise.
- `bool removeStock(Book* an_entry)`: Removes all elements of the specified book. Returns true if successful, false otherwise.
- `bool equivalentRecords(LibraryRecord& a_library_record)`: Compares two library records. Returns true if equivalent, false otherwise.
- `void operator/=(LibraryRecord& a_library_record)`: Combines the contents from both LibraryRecord objects, excluding duplicates.
- `void operator+=(LibraryRecord& a_library_record)`: Combines the contents from both LibraryRecord objects, including duplicates.

#### Utility Methods

- `grade_level grade_level_converter(std::string grade_level)`: Converts a string to a grade level.
- `int string_to_int(std::string convert_me)`: Converts a string to an int.
- `void tester()`: Tests the LibraryRecord class.
- `void displayFilter(std::string key)`: Displays all the books that match the key.

### Protected Members

- `std::vector<Book*> check_out_history_`: A list of all the items that have been checked out.
### Features

- **Book Management**: Add, remove, duplicate, and filter books.
- **Check-In/Check-Out History**: Keep track of how many times a book has been checked out.
- **Flexible Integration**: Designed to be used in various library management contexts.
- **File Handling**: Initialize the library record from a CSV file.


## Usage

Below is a basic example of how to use the `LibraryRecord` class.

```cpp
#include "LibraryRecord.hpp"

int main() {
  LibraryRecord myLibrary;
  Book* newBook = new Novel("Title", "Author", 200, false, "Fiction");
  myLibrary.checkIn(newBook);
  myLibrary.displayTitles();
  // More operations here...
  return 0;
}
```
## Requirements

- **Compiler**: C++11 or higher.
- **Dependencies**: Include the required header files (`ArrayBag.hpp`, `Book.hpp`, `Manual.hpp`, `Novel.hpp`, `Textbook.hpp`).
