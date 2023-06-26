/*
Author Name: Midyan Elghazali
File Name: LibraryRecord.cpp
Date Created/Modified: 3/22/2023
*/

#include "LibraryRecord.hpp"


/** default constructor**/
LibraryRecord::LibraryRecord() : ArrayBag<Book*>()
{
}
/**
 * @brief Turns a string into a grade level
 * 
 * @param grade_level 
 * @return grade_level 
 */
grade_level  LibraryRecord::grade_level_convertor(std::string grade_level){
  if(grade_level == "NONE"){
    return NONE;
  }
  if(grade_level == "ELEMENTARY"){
    return ELEMENTARY;
  }
  if(grade_level == "JUNIOR_HIGH"){
    return JUNIOR_HIGH;
  }
  if(grade_level == "HIGH_SCHOOL"){
    return HIGH_SCHOOL;
  }
  if(grade_level == "COLLEGE"){
    return COLLEGE;
  }
  return NONE;
}
 int LibraryRecord::string_to_int(std::string convert_me){
  for(int i =0; i < convert_me.length(); i++){
    if(!std::isdigit(convert_me[i])){
      return 0;
    }
  }
  int num = 0;
  for(int i = 0; i < convert_me.length(); i++){
    num = num * 10 + (convert_me[i] - '0');
  }
  return num;
 }

 /**
  * @brief Construct a new Library Record:: Library Record object
  * 
  * @param csv_file_name 
  */
LibraryRecord::LibraryRecord(std::string csv_file_name){
   std::ifstream file;
  file.open(csv_file_name); 
  bool firts_line = true;
  std::string collector = "";
  std::string title = "";
  std::string author = "";
  int page_count = 0; 
  bool is_digital = false;
  std::string genre = "";
  std::string subject = "";
  grade_level grade_level = NONE;
  bool has_film_adaptation = false;
  bool has_review_questions = false;
  std::string device_model = "";
  std::string website = "";
  int book_type = 0;
  std::string temp = "";

  while(getline(file, collector)){
    if(firts_line){
      firts_line = false;
      continue;
    }
    std::stringstream ss(collector);

    getline(ss, title, ',');
    getline(ss, author, ',');
    getline(ss, temp, ',');
    page_count = string_to_int(temp);
    getline(ss, temp, ',');
    is_digital = (temp == "1");
    getline(ss, genre, ',');
    getline(ss, subject, ',');
    getline(ss, temp, ',');
    grade_level = grade_level_convertor(temp);
    getline(ss, temp, ',');
    has_film_adaptation = (temp == "1");
    getline(ss, temp, ',');
    has_review_questions = (temp == "1");
    getline(ss, device_model, ',');
    getline(ss, website, ',');
    getline(ss, temp, '\n');
    book_type = string_to_int(temp);
    if(book_type == 1){
      Book* novel = new Novel(title, author, page_count, genre, is_digital, has_film_adaptation);
      checkIn(novel);
    }
    else if(book_type == 2){
      Book* textbook = new Textbook(title, author, page_count, subject , is_digital, grade_level, has_review_questions);
      checkIn(textbook);
    }
    else if(book_type == 3){
        Book* manual = new Manual(title, author, page_count, device_model, is_digital, website, false);
      checkIn(manual);
    }
  } 
}
/**
 * @brief Tests all the books in the LibraryRecord
 * 
 */
void LibraryRecord::tester(){
  for(int i= 0; i < item_count_; i++){
    items_[i]->display();
  }
}
/** @param:   A reference to a Book object to be checked in
    @return:  returns true if a book was successfully added to items, false otherwise
    @post:    adds book to items.
 **/
bool LibraryRecord::checkIn(Book* new_entry)
{
  bool has_room = (item_count_ < DEFAULT_CAPACITY);
  if (has_room)
  {
    items_[item_count_] = new_entry;
    item_count_++;
    return true;
  } // end if

  return false;
}

/** @param:   A reference to a Book object to be checked out   
    @return:  returns true if a book was successfully removed from items_, false otherwise
    @post:    removes the book from the LibraryRecord and if remove was successful, it adds the book to the check_out_history_ vector.
 **/
bool LibraryRecord::checkOut(Book* an_entry)
{
  int found_index = getIndexOf(an_entry);
  bool can_remove = !isEmpty() && (found_index > -1);
  if (can_remove)
  {
    item_count_--;
    items_[found_index] = items_[item_count_];
    check_out_history_.push_back(an_entry);
  }

  return can_remove;
}

/**
    @post:    Outputs the names of the Books in the LibraryRecord and the number of times each Book has been checked out

      For each Book in the LibraryRecord you will output:
             [title_] is written by [author_]. Page Count: [page_count_]. [it is / is not] available digitally.\n
             It has been checked out [_] times.
**/
void LibraryRecord::display()
{
  for (int i = 0; i < item_count_; i++)
  {
    int count = getCheckOutHistory(items_[i]);
    items_[i]->display();
    std::cout << "It has been checked out " << count << " times." << std::endl;
  }
}

/**
  @post:    Prints the title of each Book in the LibraryRecord
  Example:
  "title1, title2, title3, title4!" Note the commas and exclamation mark.
*/
void LibraryRecord::displayTitles()
{
  for (int i = 0; i < item_count_; i++)
  {
    if (i < item_count_ - 1)
    {
      std::cout << items_[i]->getTitle() << ", ";
    }
    else
    {
      std::cout << items_[i]->getTitle() << "!\n";
    }
  }
}

/**
  @param:   A reference to a Book object
  @return:  The number of times (int) the referenced Book has been checked out
*/
int LibraryRecord::getCheckOutHistory(Book* an_entry)
{
  int count = 0;

  for (int j = 0; j < check_out_history_.size(); j++)
  {
    if (check_out_history_[j] == an_entry)
    {
      count++;
    }
  }
  return count;
}



/** @param:   A reference to another ArrayBag object
      @post:    Combines the contents from both ArrayBag objects, EXCLUDING duplicates.
      Example: [book1, book2, book3] /= [book1, book4] will produce [book1, book2, book3, book4]

      IMPORTANT: We are carrying over the amount of times a book has been checked out.
      If book4 is in LibraryRecord2 and has been checked out 2 times then it should still be checked out 2 times in LibraryRecord2
      Hint: use getCheckOutHistory and your checkOutHistory_ vector
    */
void LibraryRecord::operator/=(LibraryRecord& a_library_record)
{
  int index = 0;
  int itemsToAdd = a_library_record.item_count_;
  while (itemsToAdd > 0)
  {
    if (this->item_count_ == DEFAULT_CAPACITY)
    {
      break;
    }
    if (contains(a_library_record.items_[index]))
    {
      break;
    }
    this->checkIn(a_library_record.items_[index]);
    int counter = a_library_record.getCheckOutHistory(a_library_record.items_[index]);
    for (int i = 0; i < counter; i++)
    {
      check_out_history_.push_back(a_library_record.items_[index]);
    }
    index++;
    itemsToAdd--;
  }
}




 /**
        @param:   A reference to another LibraryRecord object
        @post:    Combines the contents from both LibraryRecord objects, including duplicates.
        Example: [book1, book2, book3] += [book1, book4] will produce [book1, book2, book3, book1, book4]

        IMPORTANT: We are carrying over the amount of times a book has been checked out.
        If book4 is in LibraryRecord2 and has been checked out 2 times then it should still be checked out 2 times in LibraryRecord2
        Hint: use getCheckOutHistory and your checkOutHistory_ vector
    */
void LibraryRecord::operator+=(LibraryRecord& a_library_record)
{
  int index = 0;
  int itemsToAdd = a_library_record.item_count_;
  while (itemsToAdd > 0)
  {
    if (this->item_count_ == DEFAULT_CAPACITY)
    {
      break;
    }
    this->checkIn(a_library_record.items_[index]);
    int counter = a_library_record.getCheckOutHistory(a_library_record.items_[index]);
    for (int i = 0; i < counter; i++)
    {
      check_out_history_.push_back(a_library_record.items_[index]);
    }
    index++;
    itemsToAdd--;
  }
}


 /**
        @param:   A reference to another LibraryRecord object
        @post:    Combines the contents from both LibraryRecord objects, including duplicates.
        Example: [book1, book2, book3] += [book1, book4] will produce [book1, book2, book3, book1, book4]

        IMPORTANT: We are carrying over the amount of times a book has been checked out.
        If book4 is in LibraryRecord2 and has been checked out 2 times then it should still be checked out 2 times in LibraryRecord2
        Hint: use getCheckOutHistory and your checkOutHistory_ vector
    */
std::vector<Book*> LibraryRecord::toVector()
{
  std::vector<Book*> bag_contents;
  for (int i = 0; i < item_count_; i++)
    bag_contents.push_back(items_[i]);

  return bag_contents;
}

/**
  @return:    Returns true if the LibraryRecord was successfully duplicated, false otherwise (there is nothing to duplicate or duplicating would exceed DEFAULT_CAPACITY).
  @post:      Duplicates all the items in the LibraryRecord
  Example: we originally have [book1, book2] and after duplication we have [book1, book2, book1, book2]
*/
bool LibraryRecord::duplicateStock()
{
  if (item_count_ * 2 > DEFAULT_CAPACITY)
  {
    return false;
  }

  for (int i = 0; i < item_count_; i++)
  {
    items_[i + item_count_] = items_[i];
  }
  item_count_ = item_count_ * 2;
  return true;
}

/**
  @param:   A reference to a book
  @return: True or false depending on whether or not an item was removed
  @post: remove all elements of that book
*/
bool LibraryRecord::removeStock(Book* an_entry)
{
  bool res = false;
  while (contains(an_entry))
  {
    int found_index = getIndexOf(an_entry);
    item_count_--;
    for (int i = found_index; i < item_count_; i++)
    {
      items_[i] = items_[i + 1];
    }
    res = true;
  }
  return res;
}

/**
  @param:   A reference to another LibraryRecord
  @return:  Returns true if the 2 library records have the contents, regardless of their order. 
            For example, if the current holdings of the LibraryRecord are [book1, book2, book3]
            and those of the referenced LibraryRecord are [book3, book1, book2], it will return true
*/
bool LibraryRecord::equivalentRecords(LibraryRecord& a_library_record)
{
  bool result = true;

  //copy contents to count duplicates by marking them as empty
  // use copy because should not modify items_
  std::vector<Book*> library_copy = toVector();
  std::vector<Book*> other_copy = a_library_record.toVector();
  Book* empty = nullptr; 

  for (int i = 0; i < library_copy.size(); i++)
  {
    for (int j = 0; j < other_copy.size(); j++)
    {
      if (other_copy[j] != empty && other_copy[j] == library_copy[i])
      {
        library_copy[i] = empty;
        other_copy[j] = empty;
      }
    }
  }
  //check that all entries have been accounted for
  // i.e. there are no non-empty left
  for (int i = 0; i < item_count_; i++)
  {
    if (library_copy[i] != empty)
    {
      result = false;
    }
  }
  //check that all entries have been accounted for
  // i.e. there are no non-empty left
  for (int i = 0; i < a_library_record.item_count_; i++)
  {
    if (other_copy[i] != empty)
    {
      result = false;
    }
  }
  return result;
}
/**
 * @brief Displays all the books in the library record
 * 
 * @param key 
 */

void LibraryRecord::displayFilter(std::string key){
  for (int i = 0; i < item_count_; i++)
  {
    items_[i]->displayFilter(key);
  }
}

