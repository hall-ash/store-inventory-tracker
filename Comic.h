/*
 file name: Comic.h
 author: Hall, Ashley
 The Comic class extends the Collectible class. It represents comics sold and
 bought by the store.
 */

#ifndef COMIC_H
#define COMIC_H

#include "Collectible.h"

class Comic : public Collectible
{
public:
   /**
    Comic constructor.
    */
   Comic();
   
   /**
    Comic destructor.
    */
   virtual ~Comic();
   
   /**
    Sets the data members of a Comic object to elements in the 'data' vector.
    @pre The elements in the 'data' vector must contain appropriate data and the vector must contain at
    least four elements.
    @post The data members 'publisher', 'title',  'year' , and 'grade' will be set to the values in
    data[0], data[1],  data[2], and data[3], respectively.
    */
   virtual bool setData(const std::vector<std::string>& data);
   
   
   /**
    Returns a pointer to a Comic object.
    @pre None
    @post A Comic object will be created and a pointer to it will be returned.
    */
   virtual Collectible* create() const;
   
   /**
    Determines if two Comic objects are equal.
    @pre The operands must be of type Comic.
    @post Returns true if the Comic objects on the left and right side of the operator have the
    same value. Returns false otherwise.
    */
   virtual bool operator==( const Comparable& rhsComparable ) const;
   
   /**
    Determines if two Comic objects are not equal.
    @pre The operands must be of type Comic.
    @post Returns true if the Comic objects on the left and right side of the operator do not
    have the same value. Returns false otherwise.
    */
   virtual bool operator!=( const Comparable& rhsComparable ) const;
   
   /**
    Determines if the Comic object on the left side of the operator is less than the
    Comic object on the right.
    @pre The operands must be of type Comic.
    @post Returns true if the left side Comic object is less than the right side Comic
    object. Returns false otherwise.
    */
   virtual bool operator<( const Comparable& rhsComparable ) const;
   
   /**
    Determines if the Comic object on the left side of the operator is greater than the
    Comic object on the right.
    @pre The operands must be of type Comic.
    @post Returns true if the left side Comic object is greater than the right side
    Comic object. Returns false otherwise.
    */
   virtual bool operator>( const Comparable& rhsComparable ) const;
   
   
protected:

   /**
    Returns the Comic object's publisher, title, year and grade as a string.
    @return The string containing the Comic object's data.
    @pre None.
    @post The string containing the Comic object's data will be returned.
    */
   virtual std::string toString() const;
   
   std::string publisher;
   std::string title;
   std::string grade;
   
   //data indices
   const static int YEAR = 0;
   const static int GRADE = 1;
   const static int TITLE = 2;
   const static int PUBLISHER = 3;
   

};

#endif
