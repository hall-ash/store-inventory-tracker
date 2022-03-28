/*
 file name: SportsCard.cpp
 author: Hall, Ashley
 The SportsCard class extends the Collectible class. It represents sports cards
 sold and bought by the store.
 */

#include "SportsCard.h"

/**
 SportsCard constructor.
 */
SportsCard::SportsCard()
{
   setSymbol('S');
}

/**
 SportsCard destructor.
 */
SportsCard::~SportsCard() {}

/**
 Sets the data members of a SportsCard object to elements in the 'data' vector.
 @pre The elements in the 'data' vector must contain appropriate data and the vector must contain at
 least four elements.
 @post The data members 'year', 'grade',  'player' , and 'manufacturer' will be set to the values in
 data[0], data[1],  data[2], and data[3], respectively.
 */
bool SportsCard::setData(const std::vector<std::string>& data)
{
   if ( !isValidYear(data[YEAR]) || !validDataVector(data, DATA_LENGTH))
   {
      return false;
   }
   year = stoi(data[YEAR]);
   grade = data[GRADE];
   player = data[PLAYER];
   manufacturer = data[MANUFACTURER];
   return true;
}

/**
 Returns a pointer to a SportsCard object.
 @pre None
 @post A SportsCard object will be created and a pointer to it will be returned.
 */
Collectible* SportsCard::create() const
{
   return new SportsCard;
}

/**
 Determines if two SportsCard objects are equal.
 @pre The operands must be of type SportsCard.
 @post Returns true if the SportsCard objects on the left and right side of the operator have the
 same value. Returns false otherwise.
 */
bool SportsCard::operator==( const Comparable& rhsComparable ) const
{
   const SportsCard& rhsSportsCard =
      static_cast<const SportsCard&>(rhsComparable);
   return rhsSportsCard.player == player &&
      rhsSportsCard.year == year &&
      rhsSportsCard.manufacturer == manufacturer &&
      rhsSportsCard.grade == grade;
}

/**
 Determines if two SportsCard objects are not equal.
 @pre The operands must be of type SportsCard.
 @post Returns true if the SportsCard objects on the left and right side of the operator do not
 have the same value. Returns false otherwise.
 */
bool SportsCard::operator!=( const Comparable& rhsComparable ) const
{
   const SportsCard& rhsSportsCard =
      static_cast<const SportsCard&>(rhsComparable);
   return !(rhsSportsCard == *this);
}

/**
 Determines if the SportsCard object on the left side of the operator is less than the
 SportsCard object on the right.
 @pre The operands must be of type SportsCard.
 @post Returns true if the left side SportsCard object is less than the right side SportsCard
 object. Returns false otherwise.
 */
bool SportsCard::operator<( const Comparable& rhsComparable ) const
{
   const SportsCard& rhsSportsCard =
      static_cast<const SportsCard&>(rhsComparable);
   
   if ( player < rhsSportsCard.player )
      return true;
   else if ( player == rhsSportsCard.player )
   {
      if ( year < rhsSportsCard.year )
         return true;
      else if ( year == rhsSportsCard.year )
      {
         if ( manufacturer < rhsSportsCard.manufacturer )
            return true;
         else if ( manufacturer == rhsSportsCard.manufacturer )
         {
            if ( grade < rhsSportsCard.grade )
               return true;
         }
      }
   }
   return false;
}

/**
 Determines if the SportsCard object on the left side of the operator is greater than the
 SportsCard object on the right.
 @pre The operands must be of type SportsCard.
 @post Returns true if the left side SportsCard object is greater than the right side
 SportsCard object. Returns false otherwise.
 */
bool SportsCard::operator>( const Comparable& rhsComparable ) const
{
   const SportsCard& rhsSportsCard =
      static_cast<const SportsCard&>(rhsComparable);
   
   if ( player > rhsSportsCard.player )
      return true;
   else if ( player == rhsSportsCard.player )
   {
      if ( year > rhsSportsCard.year )
         return true;
      else if ( year == rhsSportsCard.year )
      {
         if ( manufacturer > rhsSportsCard.manufacturer )
            return true;
         else if ( manufacturer == rhsSportsCard.manufacturer )
         {
            if ( grade > rhsSportsCard.grade )
               return true;
         }
      }
   }
   return false;
}


/**
 Returns the SportsCard object's player, year, manufacturer, and grade as a string.
 @return The string containing the SportsCard object's data.
 @pre None.
 @post The string containing the SportsCard object's data will be returned.
 */
std::string SportsCard::toString() const
{
   return player + ", " + std::to_string(year) + ", "
   + manufacturer + ", " + grade;
}
