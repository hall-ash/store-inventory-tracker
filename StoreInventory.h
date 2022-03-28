/*
 file name: StoreInventory.h
 author: Hall, Ashley
 The StoreInventory class keeps track of a store’s inventory of collectible items,
 its customers, and customer transactions. The class initializes its inventory
 and customers from an inventory file and customer file, respectively. Customer
 transactions including commands to display the inventory, display a given
 customer’s transaction history, and display transaction histories for all
 customers are processed from a third file. Customer data are stored in a
 SearchTree object and a dictionary, both containing Customer pointers.The
 store’s item inventory will be implemented with an array of SearchTree objects
 storing Collectible pointers (one tree for each Collectible subclass).
 The StoreInventory class will assume ownership for the memory of the
 allocated SearchTrees. The SearchTree class will assume ownership for the
 memory of the pointed-to Collectible objects and Customer objects.
 The Customer class will assume ownership of the memory for the transaction
 structs and Collectible objects pointed to in the Customer's transactions
 vector. The Store class will also contain the following nested classes which
 are used to execute the commands read from the third file: CommandFactory,
 StoreCommand, and StoreCommand’s subclasses.
 */

#ifndef STOREINVENTORY_H
#define STOREINVENTORY_H

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include "Comparable.h"
#include "Customer.h"
#include "SearchTree.h"
#include "CollectibleFactory.h"

class StoreInventory
{
   
public:
   /**
    StoreInventory default constructor.
    @pre None
    @post A Store object with an empty inventory and no customers will be created.
    */
   StoreInventory();
   
   /**
    StoreInventory destructor
    @pre None
    @post Memory allocated for objects in the customerTree and inventory will be deallocated.
    */
   virtual ~StoreInventory();
   
   /**
    Adds customers from a file.
    @param customerFile The file to read.
    @pre The file has been successfully opened and the file contains properly formatted data as
    described in the program specification.
    @post The customerTree and customerDict will contain pointers to the same Customer
    objects created from the file input, and nodes will be indexed in the customerTree alphabetically
    by the customer's name.
    */
   void addCustomersFromFile(std::ifstream& customerFile);
   
   /**
    Adds Collectible objects to the inventory from a file.
    @param inventoryFile The file to read.
    @pre The file has been successfully opened and the file contains properly formatted data as
    described in the program specification.
    @post The SearchTrees in the inventoryTree array will contain pointers to
    Coin objects, Comic objects, and SportsCard objects. Nodes in each tree will be indexed
    according to the sorting order for each object.
    */
   void buildInventoryFromFile(std::ifstream& inventoryFile);
   
   
   /**
    Processes store commands from a file.
    @param commandFile The file to read.
    @pre The file has been successfully opened and the file contains properly formatted data as
    described in the program specification.
    @post
    Data will will not be modified after 'display', 'customer', and 'history' commands. Data in the
    inventory and customerTree may be modified after 'sell' or 'buy' commands.
    Nodes in the inventory may be modified (item count incremented or decremented), deleted,
    or inserted. The length of a Customer object's transactions vector may be incremented after a 'sell'
    or 'buy' command.
    */
   void processCommandsFromFile(std::ifstream& commandFile);
   
   
private:
   
   /*
    The StoreCommand class represents the various commands/actions that
    must be processed by the Store class.
    */
   class StoreCommand
   {
   public:
      
      /**
       StoreCommand constructor.
       */
      StoreCommand() {};
      
      /**
       StoreCommand destructor.
       */
      virtual ~StoreCommand() {};
      
      /**
       Executes a StoreCommand from a vector of strings.
       @pre Store must be a store object and the elements in the 'args' vector must contain appropriate
       data.
       @post The StoreCommand will be executed.
       */
      virtual bool execute(const std::vector<std::string>& args,
                           StoreInventory& storeInventory) = 0;
      
      
      /**
       Returns a pointer to a StoreCommand object.
       @pre None
       @post An object from a subclass of StoreCommand will be created and a pointer to it will be
       returned.
       */
      virtual StoreCommand* create() const = 0;
   };
   
   /*
    The CommandFactory class employs a factory method to create subclasses of
    the StoreCommand class.
    */
   class CommandFactory
   {
   public:
      
      /**
       Constructs a CommandFactory object and initializes the commandFactory array with addresses of
       subclass objects.
       @pre None
       @post The commandFactory array will be initialized with addresses of subclass objects.
       */
      CommandFactory();
      
      /**
       Deallocates memory for objects in the commandFactory array.
       @pre None
       @post Memory for objects in commandFactory will be deallocated.
       */
      virtual ~CommandFactory();
      
      /**
       Returns a StoreCommand subclass object.
       @param command The char representing the command.
       @return Returns a pointer to a StoreCommand subclass object.
       @pre The itemType must hash to an index in the commandFactory array.
       @post A StoreCommand subclass object will be returned. If command does not hash to an
       int within the bounds of the command Factory array an error will be output.
       */
      virtual StoreCommand* createCommand(char command) const;
      
      
   private:
      
      const static int FACTORY_SIZE = 29;
      //array of pointers to StoreCommand objects
      std::vector<StoreCommand*> factoryVector;
      
      /**
       Hashes the given itemType to an int.
       @param commandType The char symbol for the command.
       @return The int representing an index  in the CommandFactory vector.
       @pre None
       @post The index of the CommandFactory vector where the subclass object is stored.
       */
      virtual int hash(char commandType) const;
      
   };
   
   /*
    Command to sell an item to a customer.
    */
   class SellItem : public StoreCommand
   {
      /**
       Executes SellItem.
       If the item to be sold is in the inventory and the customer is in the store's database, the item's count
       is decremented or, if the item's count is one, the item is removed from the inventory. A transaction
       containing a record of the item sold is added to the customer's transaction history.
       @param args The arguments to execute the SellItem command.
       @param store The StoreInventory object on which the SellItem command will act.
       @return True if the command was executed successfully. False otherwise.
       @pre The elements in the 'args' vector must contain appropriate data.
       @post The item is removed from the inventory or its item count is decremented. The transaction is
       appended to the customer's list of transactions. If the customer or item are not found, error
       messages will be output.
       */
      virtual bool execute(const std::vector<std::string>& args,
                           StoreInventory& store);
      
      /**
       Creates and allocates memory for a SellItem object.
       @pre None
       @post A SellItem object will be created and memory for the object will be allocated on the heap.
       */
      virtual StoreCommand* create() const;
   };
   
   /*
    Command to buy an item from a customer.
    */
   class BuyItem : public StoreCommand
   {
      /**
       Executes BuyItem.
       The item is added to the inventory or its item count is incremented if it is already in the inventory. A
       transaction containing a record of the item bought from the customer is added to the customer's
       transaction history.
       @param args The arguments to execute the BuyItem command.
       @param store The StoreInventory object on which the BuyItem command will act.
       @return True if the command was executed successfully. False otherwise.
       @pre The elements in the 'args' vector must contain appropriate data.
       @post The item is added to the inventory or its item count is incremented. The transaction is
       appended to the customer's list of transactions. If the customer is not found, an error message
       will be output.
       */
      virtual bool execute(const std::vector<std::string>& args,
                           StoreInventory& store);
      
      /**
       Creates and allocates memory for a BuyItem object.
       @pre None
       @post A BuyItem object will be created and memory for the object will be allocated on the heap.
       */
      virtual StoreCommand* create() const;
   };
   
   
   /*
    Displays all transactions
    for a given customer in chronological order.
    */
   class ShowCustomerTransact : public StoreCommand
   {
      /**
       Executes ShowCustomerTransact.
       Displays all transactions for the given customer in chronological order.
       @param args The arguments to execute the ShowCustomerTransact command.
       @return True if the command was executed successfully. False otherwise.
       @pre The element in the 'args' vector must contain an appropriate customer ID number stored
       at arg[0].
       @post All the transactions for the given customer will be output in chronological order with 1
       transaction per line.
       */
      virtual bool execute(const std::vector<std::string>& args,
                           StoreInventory& store);
      
      /**
       Creates and allocates memory for a ShowCustomerTransact object.
       @pre None
       @post A ShowCustomerTransact object will be created and memory for the object will be allocated
       on the heap.
       */
      virtual StoreCommand* create() const;
   };
   
   
   /*
    Displays the transaction histories of all
    customers in alphabetical order by the customer's name.
    */
   class ShowTransactHistory : public StoreCommand
   {
      /**
       Executes ShowTransactHistory
       Displays all transactions for the every customer in alphabetical order by the customer's name.
       @param args The arguments needed to execute a ShowTransactHistory command.
       @param store The StoreInventory object on which the command will act.
       @return True if the command executed successfully. False otherwise.
       @pre None
       @post The transaction history for every customer will be output in alphabetical order by the
       customer's name. One transaction will be output per line.
       */
      virtual bool execute(const std::vector<std::string>& args,
                           StoreInventory& store);
      
      /**
       Creates and allocates memory for a ShowTransactHistory object.
       @pre None
       @post A ShowTransactHistory object will be created and memory for the object will be
       allocated on the heap.
       */
      virtual StoreCommand* create() const;
      
   };
   
   /*
    Displays all items in the inventory.
    */
   class DisplayInventory : public StoreCommand
   {
      /**
       Executes DisplayInventory
       Outputs each item in the inventory and its count in sorted order. All items will be printed on one line.
       Collectible item types will be output in the following order: Coin objects, Comic objects, and
       SportsCard objects.
       @param args The arguments needed to execute the command.
       @param store The StoreInventory object on which the command will be executed.
       @return True if the command was executed successfully. False otherwise.
       @pre None
       @post Each item in the inventory and its count will be output to the console.
       */
      virtual bool execute(const std::vector<std::string>& args,
                           StoreInventory& store);
      
      /**
       Creates and allocates memory for a DisplayInventory object.
       @pre None
       @post A DisplayInventory object will be created and memory for the object will be allocated on
       the heap.
       */
      virtual StoreCommand* create() const;
   };
   
   //private methods for StoreInventory class
   /**
    Hashes the symbol for a Collectible item to an index in the inventoryTree array.
    @param itemType The char symbol for a Collectible item.
    @return The index in the inventoryTree array.
    @pre itemType must be a char between 'A' and 'Z'.
    @post The index in the inventoryTree array will be returned as an array.
    */
   virtual int hashItem(char itemType) const;
   
   /**
    Determines whether the customer's name contains appropriate characters: letters or spaces.
    @param name The customer's name.
    @return True if the name only contains letters or spaces. False otherwise.
    @pre name must be a string.
    @post True will be returned if name only contains letters or spaces. False otherwise.
    */
   bool isValidCustName(const std::string& name) const;
   
   /**
    Determines whether the customer's ID number is in the range 0-999.
    @param ID The customer's ID
    @return True if the customer's ID is valid. False otherwise.
    @pre ID must be a string.
    @post True will be returned if the ID string represents a number between 0-999. False will be
    returned otherwise.
    */
   bool isValidCustID(const std::string& ID) const;
   
   //max number of customers
   static const int MAX_CUSTOMERS = 1000;
   //allows all capital letter ASCII symbols to map to unique indices
   static const int INVENTORY_SIZE = 29;
   //list of item symbols
   std::vector<char> itemSymbols = {'M', 'C', 'S'};
   
   //contains all Collectible items in store's inventory
   //SearchTree<Collectible> inventoryTree[NUM_ITEM_TYPES];
   std::vector<SearchTree<Collectible>*> inventoryTree;
   
   //used to display customer data by customer's name in alphabetical order
   SearchTree<Customer> customerTree;
   
   //array of Customer pointers for O(1) lookup & modification of customer data
   std::vector<Customer*> customerDict;
   
   CollectibleFactory collectibleFactory; //factory to create Collectible items
   
   CommandFactory commandFactory; //factory to create StoreCommand items
  
};
#endif
