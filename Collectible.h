/*
 file name: Collectible.h
 author: Hall, Ashley
 The Collectible class represents the collectible items sold and bought by
 the store. It is extended by the following child classes:
 Coin: Coin objects are sorted first by their type, year, then grade.
 Comic: Comic objects are sorted first by their publisher, title, year, then
 grade.
 SportsCard: SportsCard objects are sorted first by their player, year,
 manufacturer, then grade.
 */

#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include <vector>
#include <string>
#include "Comparable.h"

class Collectible : public Comparable
{
   
public:
   
   /**
    Collectible constructor.
    */
   Collectible();
   
   /**
    Collectible destructor.
    */
   virtual ~Collectible();
   
   /**
    Sets the data members of a Collectible object to elements in the 'data' vector.
    @param data The data to set the Collectible subclass object.
    @pre The elements in the 'data' vector must contain appropriate data.
    @post The data members of the Collectible object will be set to the values in the 'data' vector.
    */
   virtual bool setData(const std::vector<std::string>& data) = 0;

   
   /**
    Returns the Collectible subclass object as a string.
    @return The string representing the object.
    @pre None.
    @post The string containing the Collectible subclass object's data will be returned.
    */
   virtual std::string toString() const = 0;
   
   /**
    Returns a pointer to a Collectible object.
    @pre None
    @post An object from a subclass of Collectible will be created and a pointer to it will be returned.
    */
   virtual Collectible* create() const = 0;
   
   /**
    Determines whether a string represents an integer no less than 1.
    @param numStr The string representing the integer.
    @return True if the string represents a valid integer no less than 1. False otherwise.
    @pre numStr must be a string.
    @post True will be returned if the string represents a valid integer no less than 1. False will be
    returned otherwise.
    */
   virtual bool isValidNumber(const std::string& numStr) const;
   
   /**
    Determines whether a string represents a valid year from 0 to the current year.
    @param yearStr The string representing the year.
    @return True if the string represents a valid year. False otherwise.
    @pre yearStr must be a string.
    @post True will be returned if the string represents a valid year. False otherwise.
    */
   virtual bool isValidYear(const std::string& yearStr) const;
   
   /**
    Determines whether the data vector is the correct length and contains no empty strings.
    @param data The data vector.
    @param numElements The number of elements that must be in the vector.
    @return True if the data vector is the correct length and contains no empty strings.
    @pre data must be a vector of strings. numElements must be of type int.
    @post True will be returned if the data vector is the correct length and contains no empty strings.
    False otherwise.
    */
   virtual bool validDataVector(const std::vector<std::string>& data,
                        int numElements) const;
   
   /**
    Returns the char symbol associated with the Collectible subclass.
    @return The symbol associated with the Collectible subclass.
    @pre None
    @post Returns a char.
    */
   virtual char getSymbol() const;
   
protected:
   
   /**
    Sets the current year. Needed to validate year when setting its 'year' data member.
    @param year The current year.
    @pre year is an int.
    @post currYear will be set to year.
    */
   virtual void setCurrYear(int year);
   
   /**
    Sets the char symbol associated with the Collectible subclass.
    @param itemSymbol The symbol for the subclass.
    @pre itemSymbol is a char
    @post symbol will be set to itemSymbol
    */
   virtual void setSymbol(char itemSymbol);
   
   /**
    Inserts the Collectible subclass object into the output stream.
    @param outputStream The outputStream to insert the object.
    @pre outputStream must be an ostream object.
    @post The Collectible object is inserted into the output stream.
    */
   virtual void print(std::ostream& outputStream) const;
   
   char symbol; //symbol for Collectible
   int currYear = 2020; //current year
   int year; //year of Collectible
};

#endif
