/*
 file name: SportsCard.h
 author: Hall, Ashley
 The SportsCard class extends the Collectible class. It represents sports cards
 sold and bought by the store.
 */

#ifndef SPORTSCARD_H
#define SPORTSCARD_H

#include "Collectible.h"

class SportsCard : public Collectible
{
public:
   /**
    SportsCard constructor.
    */
   SportsCard();
   
   /**
    SportsCard destructor.
    */
   virtual ~SportsCard();
   
   /**
    Sets the data members of a SportsCard object to elements in the 'data' vector.
    @pre The elements in the 'data' vector must contain appropriate data and the vector must contain at
    least four elements.
    @post The data members 'player', 'year',  'manufacturer' , and 'grade' will be set to the values in
    data[0], data[1],  data[2], and data[3], respectively.
    */
   virtual bool setData(const std::vector<std::string>& data);
   
   
   /**
    Returns a pointer to a SportsCard object.
    @pre None
    @post A SportsCard object will be created and a pointer to it will be returned.
    */
   virtual Collectible* create() const;
   
   /**
    Determines if two SportsCard objects are equal.
    @pre The operands must be of type SportsCard.
    @post Returns true if the SportsCard objects on the left and right side of the operator have the
    same value. Returns false otherwise.
    */
   virtual bool operator==( const Comparable& rhsComparable ) const;
   
   /**
    Determines if two SportsCard objects are not equal.
    @pre The operands must be of type SportsCard.
    @post Returns true if the SportsCard objects on the left and right side of the operator do not
    have the same value. Returns false otherwise.
    */
   virtual bool operator!=( const Comparable& rhsComparable ) const;
   
   /**
    Determines if the SportsCard object on the left side of the operator is less than the
    SportsCard object on the right.
    @pre The operands must be of type SportsCard.
    @post Returns true if the left side SportsCard object is less than the right side SportsCard
    object. Returns false otherwise.
    */
   virtual bool operator<( const Comparable& rhsComparable ) const;
   
   /**
    Determines if the SportsCard object on the left side of the operator is greater than the
    SportsCard object on the right.
    @pre The operands must be of type SportsCard.
    @post Returns true if the left side SportsCard object is greater than the right side
    SportsCard object. Returns false otherwise.
    */
   virtual bool operator>( const Comparable& rhsComparable ) const;
   
   
protected:
   //protected methods
   
   /**
    Returns the SportsCard object's player, year, manufacturer, and grade as a string.
    @return The string containing the SportsCard object's data.
    @pre None.
    @post The string containing the SportsCard object's data will be returned.
    */
   virtual std::string toString() const;
   
   
   //protected data members
   std::string player;
   std::string manufacturer;
   std::string grade;
   const static int DATA_LENGTH = 4; //length of data vector
   
   //data indices
   const static int YEAR = 0;
   const static int GRADE = 1;
   const static int PLAYER = 2;
   const static int MANUFACTURER = 3;
   
   
};

#endif
