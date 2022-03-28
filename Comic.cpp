/*
 file name: Comic.cpp
 author: Hall, Ashley
 The Comic class extends the Collectible class. It represents comics sold and
 bought by the store.
 */

#include "Comic.h"

/**
 Comic constructor.
 */
Comic::Comic()
{
   setSymbol('C');
}

/**
 Comic destructor.
 */
Comic::~Comic() {}

/**
 Sets the data members of a Comic object to elements in the 'data' vector.
 @pre The elements in the 'data' vector must contain appropriate data and the vector must contain at
 least four elements.
 @post The data members 'year', 'grade',  'title' , and 'publisher' will be set to the values in
 data[0], data[1],  data[2], and data[3], respectively.
 */
bool Comic::setData(const std::vector<std::string>& data)
{
   if ( !isValidYear(data[YEAR]) || !validDataVector(data, 4))
   {
      return false;
   }
   
   year = stoi(data[YEAR]);
   grade = data[GRADE];
   title = data[TITLE];
   publisher = data[PUBLISHER];
   return true;
}

/**
 Returns a pointer to a Comic object.
 @pre None
 @post A Comic object will be created and a pointer to it will be returned.
 */
Collectible* Comic::create() const
{
   return new Comic;
}

/**
 Determines if two Comic objects are equal.
 @pre The operands must be of type Comic.
 @post Returns true if the Comic objects on the left and right side of the operator have the
 same value. Returns false otherwise.
 */
bool Comic::operator==( const Comparable& rhsComparable ) const
{
   const Comic& rhsComic = static_cast<const Comic&>(rhsComparable);
   return rhsComic.publisher == publisher && rhsComic.title == title
   && rhsComic.year == year && rhsComic.grade == grade;
}

/**
 Determines if two Comic objects are not equal.
 @pre The operands must be of type Comic.
 @post Returns true if the Comic objects on the left and right side of the operator do not
 have the same value. Returns false otherwise.
 */
bool Comic::operator!=( const Comparable& rhsComparable ) const
{
   const Comic& rhsComic = static_cast<const Comic&>(rhsComparable);
   return !(rhsComic == *this);
}

/**
 Determines if the Comic object on the left side of the operator is less than the
 Comic object on the right.
 @pre The operands must be of type Comic.
 @post Returns true if the left side Comic object is less than the right side Comic
 object. Returns false otherwise.
 */
bool Comic::operator<( const Comparable& rhsComparable ) const
{
   const Comic& rhsComic = static_cast<const Comic&>(rhsComparable);
   
   if ( publisher < rhsComic.publisher )
      return true;
   else if ( publisher == rhsComic.publisher )
   {
      if ( title < rhsComic.title )
         return true;
      else if ( title == rhsComic.title )
      {
         if ( year < rhsComic.year )
            return true;
         else if ( year == rhsComic.year )
         {
            if ( grade < rhsComic.grade )
               return true;
         }
      }
   }
   return false;
}

/**
 Determines if the Comic object on the left side of the operator is greater than the
 Comic object on the right.
 @pre The operands must be of type Comic.
 @post Returns true if the left side Comic object is greater than the right side
 Comic object. Returns false otherwise.
 */
bool Comic::operator>( const Comparable& rhsComparable ) const
{
   const Comic& rhsComic = static_cast<const Comic&>(rhsComparable);
   
   if ( publisher > rhsComic.publisher )
      return true;
   else if ( publisher == rhsComic.publisher )
   {
      if ( title > rhsComic.title )
         return true;
      else if ( title == rhsComic.title )
      {
         if ( year > rhsComic.year )
            return true;
         else if ( year == rhsComic.year )
         {
            if ( grade > rhsComic.grade )
               return true;
         }
      }
   }
   return false;
}


/**
 Returns the Comic object's publisher, title, year and grade as a string.
 @return The string containing the Comic object's data.
 @pre None.
 @post The string containing the Comic object's data will be returned.
 */
std::string Comic::toString() const
{
   return publisher + ", " + title + ", " + std::to_string(year)
      + ", " + grade;
}

