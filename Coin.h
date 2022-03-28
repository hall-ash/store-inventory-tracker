/*
 file name: Coin.h
 author: Hall, Ashley
 The Coin class extends the Collectible class. It represents coins sold and
 bought by the store.
 */

#ifndef COIN_H
#define COIN_H

#include "Collectible.h"

class Coin : public Collectible
{
public:
   /**
    Coin constructor.
    @pre None.
    @post A Coin object will be constructed.
    */
   Coin();
   
   /**
    Coin destructor.
    @pre None.
    @post The Coin object will be destroyed.
    */
   virtual ~Coin();
   
   /**
    Sets the data members of a Coin object to elements in the 'data' vector.
    @param data The data needed to set the data members of the Coin object.
    @pre The elements in the 'data' vector must contain appropriate data and the vector must contain at
    least three elements.
    @post The data members 'year', 'grade', and 'type' will be set to the values in data[0], data[1], and
    data[2], respectively.
    */
   virtual bool setData(const std::vector<std::string>& data);
   
   /**
    Returns a pointer to a Coin object.
    @pre None
    @post A Coin object will be created and a pointer to it will be returned.
    */
   virtual Collectible* create() const;
   
   /**
    Determines if two Coin objects are equal.
    @pre The operands must be of type Coin.
    @post Returns true if the Coin objects on the left and right side of the operator have the
    same value. Returns false otherwise.
    */
   virtual bool operator==( const Comparable& rhsComparable ) const;
   
   /**
    Determines if two Coin objects are not equal.
    @pre The operands must be of type Coin.
    @post Returns true if the Coin objects on the left and right side of the operator do not
    have the same value. Returns false otherwise.
    */
   virtual bool operator!=( const Comparable& rhsComparable ) const;
   
   /**
    Determines if the Coin object on the left side of the operator is less than the
    Coin object on the right.
    @pre The operands must be of type Coin.
    @post Returns true if the left side Coin object is less than the right side Coin
    object. Returns false otherwise.
    */
   virtual bool operator<( const Comparable& rhsComparable ) const;
   
   /**
    Determines if the Coin object on the left side of the operator is greater than the
    Coin object on the right.
    @pre The operands must be of type Coin.
    @post Returns true if the left side Coin object is greater than the right side
    Coin object. Returns false otherwise.
    */
   virtual bool operator>( const Comparable& rhsComparable ) const;
   
   
   
protected:
   //protected methods
   
   /**
    Returns the Coin object's type, year, and grade as a string.
    @return The string containing the Coin object's data.
    @pre None.
    @post The string containing the Coin object's data will be returned.
    */
   virtual std::string toString() const;
   
   
   //protected data members
   std::string type;
   int grade;
   const static int DATA_LENGTH = 3;
   
   //data vector indices
   const static int YEAR = 0;
   const static int GRADE = 1;
   const static int TYPE = 2;
   
};

#endif
