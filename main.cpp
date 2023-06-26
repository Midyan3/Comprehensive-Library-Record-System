#include "Book.hpp"
#include "LibraryRecord.hpp"
#include "Manual.hpp"
#include "Novel.hpp"
#include "Textbook.hpp"


int main(){
    Novel n1("The Great Gatsby", "F. Scott Fitzgerald", 180, "Fiction", false, false);
    Textbook t1("Introduction to Algorithms", "Thomas H. Cormen", 1312, "Computer Science", true);
    Manual m1("How to Change a Tire", "John Doe", 32, "Automotive", true, "www.tirechange.com", true);
    LibraryRecord *lr = new LibraryRecord("dataset.csv"); 
    m1.display();
    return 0;
}