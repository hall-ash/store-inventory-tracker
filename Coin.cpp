/*
 file name: Coin.cpp
 author: Hall, Ashley
 The Coin class extends the Collectible class. It represents coins sold and
 bought by the store.
 */

#include "Coin.h"

/**
 Coin constructor.
 @pre None.
 @post A Coin object will be constructed.
 */
Coin::Coin()
{
   setSymbol('M');
}

/**
 Coin destructor.
 @pre None.
 @post The Coin object will be destroyed.
 */
Coin::~Coin() {}

/**
 Sets the data members of a Coin object to elements in the 'data' vector.
 @pre The elements in the 'data' vector must contain appropriate data and the vector must contain at
 least three elements.
 @post The data members 'year', 'grade', and 'type' will be set to the values in data[0], data[1], and
 data[2], respectively.
 */
bool Coin::setData(const std::vector<std::string>& data)
{
   //ensure data is valid
   if ( !isValidYear(data[YEAR]) || !isValidNumber(data[GRADE])
      || !validDataVector(data, DATA_LENGTH))
   {
      return false;
   }
   year = stoi(data[YEAR]);
   grade = stoi(data[GRADE]);
   type = data[TYPE];
   return true;
}

/**
 Returns a pointer to a Coin object.
 @pre None
 @post A Coin object will be created and a pointer to it will be returned.
 */
Collectible* Coin::create() const
{
   return new Coin;
}

/**
 Determines if two Coin objects are equal.
 @pre The operands must be of type Coin.
 @post Returns true if the Coin objects on the left and right side of the operator have the
 same value. Returns false otherwise.
 */
bool Coin::operator==( const Comparable& comparable ) const
{
   const Coin& rhsCoin = static_cast<const Coin&>(comparable);
   return rhsCoin.grade == grade && rhsCoin.type == type
      && rhsCoin.year == year;
}

/**
 Determines if two Coin objects are not equal.
 @pre The operands must be of type Coin.
 @post Returns true if the Coin objects on the left and right side of the operator do not
 have the same value. Returns false otherwise.
 */
bool Coin::operator!=( const Comparable& comparable ) const
{
   const Coin& rhsCoin = static_cast<const Coin&>(comparable);
   return !(rhsCoin == *this);
}

/**
 Determines if the Coin object on the left side of the operator is less than the
 Coin object on the right.
 @pre The operands must be of type Coin.
 @post Returns true if the left side Coin object is less than the right side Coin
 object. Returns false otherwise.
 */
bool Coin::operator<( const Comparable& comparable ) const
{
   const Coin& rhsCoin = static_cast<const Coin&>(comparable);
   if ( type < rhsCoin.type )
      return true;
   else if ( type == rhsCoin.type )
   {
      if ( year < rhsCoin.year )
         return true;
      else if ( year == rhsCoin.year )
      {
         if ( grade < rhsCoin.grade )
            return true;
      }
   }
   return false;
}

/**
 Determines if the Coin object on the left side of the operator is greater than the
 Coin object on the right.
 @pre The operands must be of type Coin.
 @post Returns true if the left side Coin object is greater than the right side
 Coin object. Returns false otherwise.
 */
bool Coin::operator>( const Comparable& comparable ) const
{
   const Coin& rhsCoin = static_cast<const Coin&>(comparable);
   if ( type > rhsCoin.type )
      return true;
   else if ( type == rhsCoin.type )
   {
      if ( year > rhsCoin.year )
         return true;
      else if ( year == rhsCoin.year )
      {
         if ( grade > rhsCoin.grade )
            return true;
      }
   }
   return false;
}


/**
 Returns the Coin object's type, year, and grade as a string.
 @return The string containing the Coin object's data.
 @pre None.
 @post The string containing the Coin object's data will be returned.
 */
std::string Coin::toString() const
{
   return type + ", " + std::to_string(year)
   + ", " + std::to_string(grade);
}




