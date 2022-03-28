/*
 file name: StoreInventory.cpp
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

#include "StoreInventory.h"

/**
 StoreInventory default constructor.
 @pre None
 @post A Store object with an empty inventory and no customers will be created. 
 */
StoreInventory::StoreInventory() : customerDict(MAX_CUSTOMERS, nullptr),
   inventoryTree(INVENTORY_SIZE, nullptr)
{
   //create a tree to store each item type
   for ( int i = 0; i < itemSymbols.size(); i++ )
   {
      int index = hashItem(itemSymbols[i]);
      inventoryTree[index] = new SearchTree<Collectible>;
   }
}

/**
 StoreInventory destructor
 @pre None
 @post Memory allocated for objects in the customerTree and inventory will be deallocated.
 */
StoreInventory::~StoreInventory()
{
   
   for ( int i = 0; i < inventoryTree.size(); i++ )
   {
      if ( inventoryTree[i] != nullptr )
      {
         delete inventoryTree[i];
         inventoryTree[i] = nullptr;
      }
   }

}

/**
 Adds customers from a file.
 @param customerFile The file to read.
 @pre The file has been successfully opened and the file contains properly formatted data as
 described in the program specification.
 @post The customerTree and customerDict will contain pointers to the same Customer
 objects created from the file input, and nodes will be indexed in the customerTree alphabetically
 by the customer's name.
 */
void StoreInventory::addCustomersFromFile(std::ifstream& customerFile)
{
   std::string line;
   std::string entry;
   std::vector<std::string> customerInfo;
   const int ID = 0;
   const int NAME = 1;
   
   //read each line from customer file
   while( getline(customerFile, line))
   {
      //clear customer info of previous data
      customerInfo.clear();
      std::stringstream lineStream(line);
      
      //read each entry per line
      while(getline(lineStream, entry, ','))
      {
         //erase leading space
         if ( entry.at(0) == ' ' )
            entry.erase(0,1);
         //add entry to customer info
         customerInfo.push_back(entry);
      }

      //validate customer id and name
      if ( isValidCustID(customerInfo[ID]) &&
          isValidCustName(customerInfo[NAME]))
      {
         //create customer
         Customer* customer = new Customer(customerInfo[ID],
                                           customerInfo[NAME]);
         
         //add customer to dictionary
         customerDict[stoi(customerInfo[ID])] = customer;
         
         //add customer to customer tree
         customerTree.insert(customer);
      }
      else
         std::cerr << "Invalid customer information: " << customerInfo[ID] <<
         ", " << customerInfo[NAME]
         << ". Could not add customer." << std::endl;
      
   }
}

/**
 Determines whether the customer's name contains appropriate characters: letters or spaces.
 @param name The customer's name.
 @return True if the name only contains letters or spaces. False otherwise.
 @pre name must be a string.
 @post True will be returned if name only contains letters or spaces. False otherwise.
 */
bool StoreInventory::isValidCustName(const std::string& name) const
{
   //ensure that name only contains letters or spaces
   for ( int i = 0; i < name.length(); i++ )
   {
      if ( !isalpha(name[i]) && !(name[i] == ' ') )
      {
         return false;
      }
   }
   return true;
}

/**
 Determines whether the customer's ID number is in the range 0-999.
 @param ID The customer's ID
 @return True if the customer's ID is valid. False otherwise.
 @pre ID must be a string.
 @post True will be returned if the ID string represents a number between 0-999. False will be
 returned otherwise.
 */
bool StoreInventory::isValidCustID(const std::string& ID) const
{
   return stoi(ID) >= 0 && stoi(ID) < 1000;
}


/**
 Adds Collectible objects to the inventory from a file.
 @param inventoryFile The file to read.
 @pre The file has been successfully opened and the file contains properly formatted data as
 described in the program specification.
 @post The SearchTrees in the inventoryTree array will contain pointers to
 Coin objects, Comic objects, and SportsCard objects. Nodes in each tree will be indexed
 according to the sorting order for each object.
 */
void StoreInventory::buildInventoryFromFile(std::ifstream& inventoryFile)
{
   std::string line;
   std::string entry;
   std::vector<std::string> data;
   char itemType;
   std::string itemCount;
   std::string garbage;
   
   //read each line from inventory file
   while( getline(inventoryFile, line))
   {
      //clear data vector of previous entries
      data.clear();
      
      std::stringstream lineStream(line);
      
      //get item type and item count
      lineStream >> itemType;
      lineStream >> garbage;
      lineStream >> itemCount;
      itemCount.pop_back();
      
      //read each entry per line
      while(getline(lineStream, entry, ','))
      {
         //erase leading space
         if ( entry.at(0) == ' ' )
            entry.erase(0,1);
         //add entry to data vector
         data.push_back(entry);
      }
      //ensure item count is not negative
      if ( stoi(itemCount) < 1 )
         std::cerr << "Invalid item count."
            << " Could not add item to inventory." << std::endl;
      
      //create Collectible item
      Collectible* itemPtr = collectibleFactory.createObject(itemType);
      
      //item type is valid
      if ( itemPtr != nullptr )
      {
         //invalid data, delete item
         if ( !itemPtr->setData(data) )
         {
            delete itemPtr;
            itemPtr = nullptr;
         }
         else //valid data, add item to inventory
         {
            int index = hashItem(itemType);
            
            inventoryTree[index]->insert(itemPtr, stoi(itemCount));
         }
      }
   }
}

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
void StoreInventory::processCommandsFromFile(std::ifstream& commandFile)
{
   std::string line;
   std::string entry;
   std::vector<std::string> data;
   char command;
   std::string garbage;
   
   //read each line in command file
   while( getline(commandFile, line))
   {
      //clear data vector of previous entries
      data.clear();
      
      std::stringstream lineStream(line);
      
      //read command
      lineStream >> command;
      lineStream >> garbage;
      
      //read each entry in line
      while(getline(lineStream, entry, ','))
      {
         //erase leading space
         if ( entry.at(0) == ' ' )
            entry.erase(0,1);
         
         //add entry to data
         data.push_back(entry);
      }
      
      //create StoreCommand object
      StoreCommand* commandPtr = commandFactory.createCommand(command);
      
      //command char is valid
      if ( commandPtr != nullptr)
      {
         //execute command
         commandPtr->execute(data, *this);

         //delete command object
         delete commandPtr;
         commandPtr = nullptr;
      }
   }
}

/**
 Hashes the symbol for a Collectible item to an index in the inventoryTree array.
 @param itemType The char symbol for a Collectible item.
 @return The index in the inventoryTree array.
 @pre itemType must be a char between 'A' and 'Z'.
 @post The index in the inventoryTree array will be returned as an array.
 */
int StoreInventory::hashItem(char itemType) const
{
   //accepts item with symbols A-Z
   if ( itemType < 'A' || itemType > 'Z' )
   {
      std::cerr << "StoreInventory::hashItem: invalid argument" << std::endl;
      return -1;
   }
   //return the index of the inventoryTree containing the appropriate item
   //types
   return (itemType - 'A') % inventoryTree.size();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// COMMANDFACTORY IMPLEMENTATION
/**
 Constructs a CommandFactory object and initializes the commandFactory array with addresses of
 subclass objects.
 @pre None
 @post The commandFactory array will be initialized with addresses of subclass objects.
 */
StoreInventory::CommandFactory::CommandFactory() :
   factoryVector(FACTORY_SIZE, nullptr)
{
   factoryVector[hash('H')] = new ShowTransactHistory;
   factoryVector[hash('B')] = new BuyItem;
   factoryVector[hash('C')] = new ShowCustomerTransact;
   factoryVector[hash('D')] = new DisplayInventory;
   factoryVector[hash('S')] = new SellItem;
}

/**
 Deallocates memory for objects in the commandFactory array.
 @pre None
 @post Memory for objects in commandFactory will be deallocated.
 */
StoreInventory::CommandFactory::~CommandFactory()
{
   for ( int i = 0; i < factoryVector.size(); i++)
   {
      if ( factoryVector[i] != nullptr )
      {
         delete factoryVector[i];
         factoryVector[i] = nullptr;
      }
   }
}

/**
 Returns a StoreCommand subclass object.
 @param command The char representing the command.
 @return Returns a pointer to a StoreCommand subclass object.
 @pre The itemType must hash to an index in the commandFactory array.
 @post A StoreCommand subclass object will be returned. If command does not hash to an int within the
 bounds of the command Factory array an error will be output.
 */
StoreInventory::StoreCommand*
StoreInventory::CommandFactory::createCommand(char command) const
{
   int index = hash(command);
   //ensure the index is valid
   if ( index < 0 )
   {
      std::cerr << "CollectibleFactory::createCommand: command hashed to"
      <<" negative index" << std:: endl;
      return nullptr;
   }
   //create the subclass object
   if ( factoryVector[index] != nullptr )
      return factoryVector[index]->create();
   else
      return nullptr;
}

/**
 Hashes the given itemType to an int.
 @param commandType The char symbol for the command.
 @return The int representing an index  in the CommandFactory vector.
 @pre None
 @post The index of the CommandFactory vector where the subclass object is stored.
 */
int StoreInventory::CommandFactory::hash(char commandType) const
{
   if ( commandType < 'A' || commandType > 'Z' )
   {
      std::cerr << "CollectibleFactory::hash: invalid argument" << std::endl;
      return -1;
   }
   
   return (commandType - 'A') % factoryVector.size();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//SELLITEM IMPLEMENTATION

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
bool StoreInventory::SellItem::execute(const std::vector<std::string>& args,
                                       StoreInventory& store)
{
   const char SELL = 'S';
   //indices of elements in 'args'
   const int ID = 0;
   const int ITEM_TYPE = 1;
   const int FIRST_DATA_ELEMENT = 2;
   
   //check valid id
   if ( !store.isValidCustID(args[ID]) )
   {
      std::cout << "Sell Item Error: Customer ID " << args[ID]
      << " invalid.\n" << std::endl;
      return false;
   }
   //check if customer exists
   Customer* customer = store.customerDict[stoi(args[ID])];
   if ( customer == nullptr )
   {
      std::cout << "Sell Item Error: Customer ID " << args[ID]
      << " not found.\n" << std::endl;
      return false;
   }
   
   //create Collectible object from itemType
   char itemType = (args[ITEM_TYPE])[0];
   Collectible* itemPtr = store.collectibleFactory.createObject(itemType);
   
   //create subvector of data elements from args[2]-args[args.size()-1]
   std::vector<std::string>::const_iterator first = args.begin()
      + FIRST_DATA_ELEMENT;
   std::vector<std::string>::const_iterator last = args.end();
   std::vector<std::string> data(first, last);
   
   //Collectible item was created
   if ( itemPtr != nullptr )
   {
      //find the appropriate inventory tree
      int inventoryTreeIndex = store.hashItem(itemType);
      
      //invalid index
      if ( inventoryTreeIndex < 0 )
      {
         std::cerr << "SellItem::execute: itemType hashed to negative"
         << " index" << std:: endl;
         
         //delete item
         delete itemPtr;
         itemPtr = nullptr;
         return false;
      }
      
      //itemType hashed to index holding SearchTree
      if ( store.inventoryTree[inventoryTreeIndex] != nullptr )
      {
         //set item's data
         //if data is valid
         if ( itemPtr->setData(data) )
         {
            //atempt to remove 1 instance of item
            bool removed =
               store.inventoryTree[inventoryTreeIndex]->remove(*itemPtr);
            
            //item not found in inventory
            if ( !removed )
            {
               std::cout << "Sell Item Error. Item not found: " << *itemPtr
               << "\n" << std::endl;
               
               //delete item
               delete itemPtr;
               itemPtr = nullptr;

               return false;
            }
            
            //1 instance of item removed from tree
            //add item to customers transactions
            customer->addTransaction(SELL, itemPtr);
            
            return true;
         }
         else //invalid data, delete item
         {
            delete itemPtr;
            itemPtr = nullptr;
            std::cout << "Sell Item Error. Invalid data.\n" << std::endl;
            return false;
         }
      }
      else //itemType hashed to index holding nullptr
      {
         delete itemPtr;
         itemPtr = nullptr;
         std::cerr<< "Item type hashed to index in inventoryTree holding"
         << " nullptr.\n" << std::endl;
         return false;
      }
   }
 
   //item was not created, invalid itemType
   std::cout << "Sell Item Error. Invalid item type: "
   << itemType << "\n" << std::endl;
   return false;
}

/**
 Creates and allocates memory for a SellItem object.
 @pre None
 @post A SellItem object will be created and memory for the object will be allocated on the heap.
 */
StoreInventory::StoreCommand* StoreInventory::SellItem::create() const
{
   return new SellItem;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//BUYITEM IMPLEMENTATION

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
bool StoreInventory::BuyItem::execute(
      const std::vector<std::string>& args, StoreInventory& store)
{
   const char BUY = 'B';
   //indices of elements in 'args'
   const int ID = 0;
   const int ITEM_TYPE = 1;
   const int FIRST_DATA_ELEMENT = 2;

   //check valid id
   if ( !store.isValidCustID(args[ID]) )
   {
      std::cout << "Buy Item Error: Customer ID " << args[ID]
      << " invalid.\n" << std::endl;
      return false;
   }
   
   //check if customer exists
   Customer* customer = store.customerDict[stoi(args[ID])];
   if ( customer == nullptr )
   {
      std::cout << "Buy Item Error: Customer ID " << args[ID]
      << " not found.\n" << std::endl;
      return false;
   }
   
   //create item to add to inventory
   char itemType = (args[ITEM_TYPE])[0];
   Collectible* itemPtr = store.collectibleFactory.createObject(itemType);
   
   //create subvector of data elements from args[2]-args[args.size()-1]
   std::vector<std::string>::const_iterator first = args.begin()
      + FIRST_DATA_ELEMENT;
   std::vector<std::string>::const_iterator last = args.end();
   std::vector<std::string> data(first, last);
   
   //Collectible item was created
   if ( itemPtr != nullptr )
   {
      //find the appropriate inventory tree
      int inventoryTreeIndex = store.hashItem(itemType);
      
      //itemType hashed to invalid index
      if ( inventoryTreeIndex < 0 )
      {
         std::cerr << "BuyItem::execute: itemType hashed to negative index"
         << std:: endl;
         //delete item
         delete itemPtr;
         itemPtr = nullptr;
         return false;
      }
      //item hashed to index holding SearchTree
      if ( store.inventoryTree[inventoryTreeIndex] != nullptr )
      {
         //set item's data
         //if data is valid
         if ( itemPtr->setData(data) )
         {
            //add item to inventory
            bool inserted =
               store.inventoryTree[inventoryTreeIndex]->insert(itemPtr);
            
            //item was incremented in inventory
            //add item to customer's transactions
            if ( store.inventoryTree[inventoryTreeIndex]->contains(*itemPtr)
                && !inserted )
            {
               customer->addTransaction(BUY, itemPtr);
               return true;
            }
            //item was added to inventory
            //add copy of item to customer's transactions
            if ( inserted )
            {
               Collectible* itemCopy =
                  store.collectibleFactory.createObject(itemType);
               itemCopy->setData(data);
               
               customer->addTransaction(BUY, itemCopy);
               return true;
            }
            //item could not be added to inventory
            if ( !inserted )
            {
               //delete item
               delete itemPtr;
               itemPtr = nullptr;
               std::cerr << "Error adding item to inventory.\n" << std::endl;
               return false;
            }
         }
         else //invalid data, delete item
         {
            delete itemPtr;
            itemPtr = nullptr;
            std::cout << "Buy Item Error. Invalid data.\n" << std::endl;
            return false;
         }
      }
      else //itemType hashed to index holding nullptr
      {
         delete itemPtr;
         itemPtr = nullptr;
         std::cerr<< "Item type hashed to index in inventoryTree holding"
         << " nullptr.\n" << std::endl;
         return false;
      }
   }

   //item was not created
   std::cout << "Buy Item Error. Invalid item type:" << itemType
   << "\n" << std::endl;
   return false;
}

/**
 Creates and allocates memory for a BuyItem object.
 @pre None
 @post A BuyItem object will be created and memory for the object will be allocated on the heap.
 */
StoreInventory::StoreCommand* StoreInventory::BuyItem::create() const
{
   return new BuyItem;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//SHOWCUSTOMERTRANSACT IMPLEMENTATION

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
bool StoreInventory::ShowCustomerTransact::execute(
      const std::vector<std::string>& args, StoreInventory& store)
{
   const int ID = 0;

   //check valid id
   if ( !store.isValidCustID(args[ID]) )
   {
      std::cout << "Customer ID " << args[ID]
      << " invalid.\n" << std::endl;
      return false;
   }
   
   //check if customer exists
   Customer* customer = store.customerDict[stoi(args[ID])];
   if ( customer == nullptr )
   {
      std::cout << "Customer ID " << args[ID]
      << " not found.\n" << std::endl;
      return false;
   }
   //customer found, output id, name, and transactions
   std::cout << *customer;
   
   return true;
}

/**
 Creates and allocates memory for a ShowCustomerTransact object.
 @pre None
 @post A ShowCustomerTransact object will be created and memory for the object will be allocated
 on the heap.
 */
StoreInventory::StoreCommand*
StoreInventory::ShowCustomerTransact::create() const
{
   return new ShowCustomerTransact;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//SHOWTRANSACTHISTORY IMPLEMENTATION

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
bool StoreInventory::ShowTransactHistory::execute(
   const std::vector<std::string>& args, StoreInventory& store )
{
   std::cout << "Transaction History: " << std::endl;
   //print customer's in alphabetical order, including their transactions
   store.customerTree.printWithoutCounts();
   return true;
}

/**
 Creates and allocates memory for a ShowTransactHistory object.
 @pre None
 @post A ShowTransactHistory object will be created and memory for the object will be allocated on the
 heap.
 */
StoreInventory::StoreCommand*
StoreInventory::ShowTransactHistory::create() const
{
   return new ShowTransactHistory;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//DISPLAYINVENTORY IMPLEMENTATION

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
bool StoreInventory::DisplayInventory::execute(
   const std::vector<std::string>& args, StoreInventory& store)
{
   std::cout << "Inventory: " << std::endl;
   //print the inventory tree for each Collectible type
   for ( int i = 0; i < store.itemSymbols.size(); i++ )
   {
      int index = store.hashItem( store.itemSymbols[i] );
      std::cout << *store.inventoryTree[index];
   }
   std::cout << std::endl;
   return true;
}

/**
 Creates and allocates memory for a DisplayInventory object.
 @pre None
 @post A DisplayInventory object will be created and memory for the object will be allocated on the heap.
 */
StoreInventory::StoreCommand*
StoreInventory::DisplayInventory::create() const
{
   return new DisplayInventory;
}



