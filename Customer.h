/*
 file name: Customer.h
 author: Hall, Ashley
 The Customer class holds each customer’s 3 digit ID, their name, and their
 transaction history. Customer objects are sorted alphabetically by name.
 The transaction history is represented by a vector of pointers to Transaction
 structs which hold Collectible pointers and action chars.
 The Customer class will assume ownership for the memory of pointed-to
 Transaction structs in the transactions vector and the Collectible pointers
 they contain.
*/

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Comparable.h"
#include "Collectible.h"

class Customer : public Comparable

{
public:

   /**
    Customer constructor. Sets the customer's ID and name.
    @pre custID and custName must be of type string.
    @post The customer's ID and name will be set to custID and custName, respectively.
    */
   Customer( const std::string& custID, const std::string& custName);

   /**
    Customer destructor. Deallocates memory for items in the transactions vector and transaction structs.
    */
   virtual ~Customer();

   /**
    Deallocates memory for items in the transactions vector and transaction structs.
    @pre None
    @post Memory allocated in the transactions vector will be deallocated. The size of the
    transactions struct will be set to 0.
    */
   virtual void clearTransactions();
   
   /**
    Determines if two Customer objects are equal.
    @pre The operands must be of type Customer.
    @post Returns true if the Customer objects on the left and right side of the operator have the
    same value. Returns false otherwise.
    */
   virtual bool operator==( const Comparable& rhsComparable ) const;

   /**
    Determines if two Customer objects are not equal.
    @pre The operands must be of type Customer.
    @post Returns true if the Customer objects on the left and right side of the operator do not
    have the same value. Returns false otherwise.
    */
   virtual bool operator!=( const Comparable& rhsComparable ) const;

   /**
    Determines if the Customer object on the left side of the operator is less than the
    Customer object on the right.
    @pre The operands must be of type Customer.
    @post Returns true if the left side Customer object is less than the right side Customer
    object. Returns false otherwise.
    */
   virtual bool operator<( const Comparable& rhsComparable ) const;

   /**
    Determines if the Customer object on the left side of the operator is greater than the
    Customer object on the right.
    @pre The operands must be of type Customer.
    @post Returns true if the left side Customer object is greater than the right side
    Customer object. Returns false otherwise.
    */
   virtual bool operator>( const Comparable& rhsComparable ) const;


   /**
    Appends a transaction to the customer's transaction history.
    @pre 'action' must be the char 'B' or 'S'. 'item' must be a Collectible pointer.
    @post The transaction will be added to the customer's transaction list and true will be returned.
    The newly added transaction will be the last element of the transactions vector.
    If item is nullptr or action is not one of the valid chars an error message will be output and false will
    be returned.
    */
   virtual bool addTransaction(char action, Collectible* item);
   

protected:

   struct Transaction
   {
      char action; //'B' or 'S'
  
      Collectible* item = nullptr;
   };
   
   /**
    Inserts the Customer object and their transactions into the output stream.
    @pre outputStream must be an ostream object.
    @post The Customer object and their transactions are inserted into the output stream.
    */
   virtual void print(std::ostream& outputStream) const;
   
   /**
    Inserts the Customer's transactions into the output stream.
    @param outputStream The outputStream
    @pre outputStream must be of type std::ostream
    @post The transactions will be inserted into the output stream. If no transactions were made
    the string "none" will be inserted into the output stream.
    */
   virtual void insertTransactions( std::ostream& outputStream) const;
   
   /**
    Returns the Customer's ID, name, and each transaction made in chronological order with 1 transaction
    per line.
    @return The string containing the Comic object's data.
    @pre None.
    @post The string containing the Comic object's data will be returned.
    */
   virtual std::string toString() const;

   std::string idNumber; //customer's 3 digit ID number
   std::string name; //customer's name
   std::vector<Transaction*> transactions; //customer's transaction history
   
   
};

#endif 
