/*
 file name: Collectible.cpp
 author: Hall, Ashley
 The Collectible class represents the collectible items sold and bought by
 the store. It is extended by the following child classes:
 Coin: Coin objects are sorted first by their type, year, then grade.
 Comic: Comic objects are sorted first by their publisher, title, year, then
 grade.
 SportsCard: SportsCard objects are sorted first by their player, year,
 manufacturer, then grade.
 */

#include "Collectible.h"

/**
 Collectible constructor.
 */
Collectible::Collectible() {}

/**
 Collectible destructor.
 */
Collectible::~Collectible() {}

/**
 Determines whether a string represents an integer no less than 1.
 @param numStr The string representing the integer.
 @return True if the string represents a valid integer no less than 1. False otherwise.
 @pre numStr must be a string.
 @post True will be returned if the string represents a valid integer no less than 1. False will be
 returned otherwise.
 */
bool Collectible::isValidNumber(const std::string& numStr) const
{
   //numStr must contain only digits
   bool invalidNum = false;
   for ( int i = 0; i < numStr.length(); i++ )
   {
      if ( !isdigit(numStr[i]) )
         invalidNum = true;
   }
   //numStr must be greater than 0
   if ( invalidNum || stoi(numStr) < 1 )
   {
      return false;
   }
   return true;
}

/**
 Determines whether a string represents a valid year from 0 to the current year.
 @param yearStr The string representing the year.
 @return True if the string represents a valid year. False otherwise.
 @pre yearStr must be a string.
 @post True will be returned if the string represents a valid year. False otherwise.
 */
bool Collectible::isValidYear(const std::string& yearStr) const
{
   if ( isValidNumber(yearStr) && stoi(yearStr) <= currYear )
      return true;
   else
      return false;
}

/**
 Determines whether the data vector is the correct length and contains no empty strings.
 @param data The data vector.
 @param numElements The number of elements that must be in the vector.
 @return True if the data vector is the correct length and contains no empty strings.
 @pre data must be a vector of strings. numElements must be of type int.
 @post True will be returned if the data vector is the correct length and contains no empty strings.
 False otherwise.
 */
bool Collectible::validDataVector(const std::vector<std::string>& data,
                     int numElements) const
{
   if ( data.size() != numElements )
      return false;
   for ( int i = 0; i < numElements; i++ )
   {
      if ( data[i] == "" )
         return false;
   }
   return true;
}

/**
 Sets the current year. Needed to validate year when setting its 'year' data member.
 @param year The current year.
 @pre year is an int.
 @post currYear will be set to year.
 */
void Collectible::setCurrYear(int year)
{
   currYear = year;
}

/**
 Sets the char symbol associated with the Collectible subclass.
 @param itemSymbol The symbol for the subclass.
 @pre itemSymbol is a char
 @post symbol will be set to itemSymbol
 */
void Collectible::setSymbol(char itemSymbol)
{
   symbol = itemSymbol;
}

/**
 Returns the char symbol associated with the Collectible subclass.
 @return The symbol associated with the Collectible subclass.
 @pre None
 @post Returns a char.
 */
char Collectible::getSymbol() const
{
   return symbol;
}

/**
 Inserts the Collectible subclass object into the output stream.
 @param outputStream The outputStream to insert the object.
 @pre outputStream must be an ostream object.
 @post The Collectible object is inserted into the output stream.
 */
void Collectible::print(std::ostream& outputStream) const
{
   outputStream << toString();
}
