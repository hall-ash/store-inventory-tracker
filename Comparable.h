/*
 file name: Comparable.h
 author: Hall, Ashley
 The Comparable class represents objects that have a sorting order
 allowing them to be inserted into the correct location in sorted containers.
 It is extended by the Customer and Collectible classes.
 */
#include <iostream>

#ifndef COMPARABLE_H
#define COMPARABLE_H

class Comparable
{
public:
   
   /**
    Comparable constructor.
    */
   Comparable() {};
   
   /**
    Comparable destructor.
    */
   virtual ~Comparable() {};
   
   /**
    Determines if two Comparable objects are equal.
    @pre The operands must be of type Comparable.
    @post Returns true if the Comparable objects on the left and right side of the operator have the
    same value. Returns false otherwise.
    */
   virtual bool operator==( const Comparable& right ) const = 0;
   
   /**
    Determines if two Comparable objects are not equal.
    @pre The operands must be of type Comparable.
    @post Returns true if the Comparable objects on the left and right side of the operator do not
    have the same value. Returns false otherwise.
    */
   virtual bool operator!=( const Comparable& right ) const = 0;
   
   /**
    Determines if the Comparable object on the left side of the operator is less than the
    Comparable object on the right.
    @pre The operands must be of type Comparable.
    @post Returns true if the left side Comparable object is less than the right side Comparable
    object. Returns false otherwise.
    */
   virtual bool operator<( const Comparable& right ) const = 0;
   
   /**
    Determines if the Comparable object on the left side of the operator is greater than the
    Comparable object on the right.
    @pre The operands must be of type Comparable.
    @post Returns true if the left side Comparable object is greater than the right side
    Comparable object. Returns false otherwise.
    */
   virtual bool operator>( const Comparable& right ) const = 0;
   
   /**
    Overloads the stream insertion operator to display Comparable objects.
    @pre outputStream must be an ostream object and outputComparable must be a Comparable.
    @post The Comparable object is output to the console.
    */
   friend std::ostream& operator<<( std::ostream& outputStream,
                              const Comparable& outputComparable)
   {
      outputComparable.print(outputStream);
      return outputStream;
   }
   
protected:
   /**
    Inserts the Comparable object into the output stream.
    @pre outputStream must be an ostream object.
    @post The Comparable object is inserted into the output stream.
    */
   virtual void print(std::ostream& outputStream) const = 0;
};

#endif
