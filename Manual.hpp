/*
Author Name: Midyan Elghazali
File Name: Manual.hpp
Date Created/Modified: 3/22/2023
*/
#ifndef MANUAL_HPP_
#define MANUAL_HPP_
#include "Book.hpp"
#include <regex>

class Manual : public Book
{
  public:


/**
  Default constructor.
  Default-initializes all private members. 
  Booleans are default-initialized to False
*/
Manual();


     /**
    Parameterized constructor.
    @param     : The title of the book (a string)
    @param     : The author of the book (a string)
    @param     : The number of pages in the book (a positive integer)
    @param     : A flag indicating whether the book is in digital form 
                 with DEFAULT VALUE False (a Boolean)
    @param     : The name of the device (a string)
    @param     : The URL that is in the format 
                 'https://www.something.something' 
                 or 'http://www.something.something' 
                 with the last 'something' being at least 2 characters 
                 with DEFAULT VALUE empty string (a string)
    @param     : A Boolean indicating the presence of a visual aid 
                 with DEFAULT VALUE False
    @post      : The private members are set to the values of the 
                 corresponding parameters. 
                 If a URL is provided, the website flag is set to True.
                 If the URL is ill-formatted, the website is set to 
                 empty string and the website flag is set to False.
    */
    Manual(std::string name, std::string author, int page_count, std::string model, bool is_digital = false, std::string url = "", bool aid = false);

      /**
    @param  : a reference to a string representing the device
    @post   : sets the private member variable to the value of the parameter
    **/
    void setDevice(const std::string& model);


    /**
    @return  : the variable indicating the device the manual is for
    **/
    std::string getDevice() const; 

      /**
    @param   : a reference to a website link (string) that is in the format 
              'https://www.something.something' 
              or 'http://www.something.something' 
              with the last 'something' being at least 2 characters
    @return  : has_website_ flag (a boolean)
    @post    : If the link is not correctly formatted, 
              store "Broken Link" in the link member variable (see <regex>) 
              and either way set the has website flag to True
    **/
    bool setWebsite(const std::string& site);


    /**
    @return  : the url for the website
    **/
    std::string getWebsite() const; 
    

     /**
    @return  : the visual aid flag
    **/
    void setVisualAid(const bool& aid); 


    /**
    @param  : a boolean
    @post   : sets the private member variable indicating the presence 
            of a visual aid to the value of the parameter
    **/
    bool hasVisualAid() const;

     /**
    @return  : the has website flag
    **/
    bool hasWebsite() const; 
    /*
    @return  : a everything printed in the format:
              "Manual: <title> by <author> (<page_count> pages)
              Device: <device>
              Website: <website>
              Visual Aid: <visual aid>
    */
    void display() override;
    /**
     * @brief displays the Manual's information if the key matches the Manual's device
     * 
     * @param key 
     */
    void displayFilter(std::string key) override; 
    /**
     * @brief returns the Manual's device
     * 
     * @param device 
     * @return std::string 
     */
    std::string helper(std::string device);

    
  private:
    std::string website_; // a string that represents a url
    std::string device_; // a string that represents the name of the device
    bool has_visual_aid_; // a boolean indicating whether the Manual has a visual aid
    bool has_website_; // a boolean indicating whether the Manual has a website
};
// end Manual class
#endif