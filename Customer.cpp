/*
 file name: Customer.cpp
 author: Hall, Ashley
 The Customer class holds each customer’s 3 digit ID, their name, and their
 transaction history. Customer objects are sorted alphabetically by name.
 The transaction history is represented by a vector of pointers to Transaction
 structs which hold Collectible pointers and action chars.
 The Customer class will assume ownership for the memory of pointed-to
 Transaction structs in the transactions vector and the Collectible pointers
 they contain.
 */
#include "Customer.h"

/**
 Customer constructor. Sets the customer's ID and name.
 @pre custID and custName must be of type string.
 @post The customer's ID and name will be set to custID and custName, respectively.
 */
Customer::Customer( const std::string& custID, const std::string& custName )
: idNumber(custID), name(custName)
{
}

/**
 Customer destructor. Deallocates memory for items in the transactions vector and transaction structs.
 */
Customer::~Customer()
{
   clearTransactions();
}

/**
 Deallocates memory for items in the transactions vector and transaction structs.
 @pre None
 @post Memory allocated in the transactions vector will be deallocated.
 */
void Customer::clearTransactions()
{
   for ( int i = 0; i < transactions.size(); i++ )
   {
      if ( transactions[i] != nullptr )
      {
         //delete collectible
         if ( transactions[i]->item != nullptr )
         {
            delete transactions[i]->item;
            transactions[i]->item = nullptr;
         }
         
         //delete transaction struct
         delete transactions[i];
         transactions[i] = nullptr;
     }
   }
   transactions.resize(0);
}


/**
 Determines if two Customer objects are equal.
 @pre The operands must be of type Customer.
 @post Returns true if the Customer objects on the left and right side of the operator have the
 same value. Returns false otherwise.
 */
bool Customer::operator==( const Comparable& rhsComparable ) const
{
   const Customer& rhsCustomer = static_cast<const Customer&>(rhsComparable);
   return rhsCustomer.name == name && rhsCustomer.idNumber == idNumber;
}

/**
 Determines if two Customer objects are not equal.
 @pre The operands must be of type Customer.
 @post Returns true if the Customer objects on the left and right side of the operator do not
 have the same value. Returns false otherwise.
 */
bool Customer::operator!=( const Comparable& rhsComparable ) const
{
   const Customer& rhsCustomer = static_cast<const Customer&>(rhsComparable);
   return !(rhsCustomer == *this);
}


/**
 Determines if the Customer object on the left side of the operator is less than the
 Customer object on the right.
 @pre The operands must be of type Customer.
 @post Returns true if the left side Customer object is less than the right side Customer
 object. Returns false otherwise.
 */
bool Customer::operator<( const Comparable& rhsComparable ) const
{
   const Customer& rhsCustomer = static_cast<const Customer&>(rhsComparable);
   return name < rhsCustomer.name;
}

/**
 Determines if the Customer object on the left side of the operator is greater than the
 Customer object on the right.
 @pre The operands must be of type Customer.
 @post Returns true if the left side Customer object is greater than the right side
 Customer object. Returns false otherwise.
 */
bool Customer::operator>( const Comparable& rhsComparable ) const
{
   const Customer& rhsCustomer = static_cast<const Customer&>(rhsComparable);
   return name > rhsCustomer.name;
}


/**
 Appends a transaction to the customer's transaction history.
 @pre 'action' must be the char 'B' or 'S'. 'item' must be a Collectible pointer.
 @post The transaction will be added to the customer's transaction list and true will be returned.
 The newly added transaction will be the last element of the transactions vector.
 If item is nullptr or action is not one of the valid chars an error message will be output and false will
 be returned.
 */
bool Customer::addTransaction(char actionType, Collectible* collectItem)
{
   if ( actionType != 'B' && actionType != 'S' )
   {
      std::cerr << "addTransaction invalid arg: " << actionType << std::endl;
      return false;
   }
   
   if ( collectItem == nullptr )
   {
      std::cerr << "addTransaction invalid arg: nullptr passed in" << std::endl;
      return false;
   }
   
   //create transaction object with given values
   Transaction* transaction = new Transaction;
   transaction->action = actionType;
   transaction->item = collectItem;
   
   //add to end of transactions list
   transactions.push_back(transaction);
   
   return true;
}

/**
 Inserts the Customer object and their transactions into the output stream.
 @pre outputStream must be an ostream object.
 @post The Customer object and their transactions are inserted into the output stream.
 */
void Customer::print(std::ostream& outputStream) const
{
   //print id and name
   outputStream << toString() << std::endl;
   //print transaction list in chronological order
   insertTransactions(outputStream);
   outputStream << std::endl;
}

/**
 Inserts the Customer's transactions into the output stream.
 @param outputStream The outputStream
 @pre outputStream must be of type std::ostream
 @post The transactions will be inserted into the output stream. If no transactions were made
 the string "none" will be inserted into the output stream.
 */
void Customer::insertTransactions( std::ostream& outputStream) const
{
   outputStream << "Transactions:" << std::endl;
   if ( transactions.size() == 0 )
   {
      outputStream << "none" << std::endl;
      return;
   }
   
   for ( int i = 0; i < transactions.size(); i++ )
   {
      outputStream << transactions[i]->action << ": ";
      outputStream << *transactions[i]->item << std::endl;
   }
}

/**
 Returns the Customer's ID, name, and each transaction made in chronological order with 1 transaction
 per line.
 @return The string containing the Comic object's data.
 @pre None.
 @post The string containing the Comic object's data will be returned.
 */
std::string Customer::toString() const
{
   return "Customer: " + idNumber
   + ", " + name;
}
