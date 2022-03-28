/*
 file name: main.cpp
 author: Hall, Ashley
 Creates a StoreInventory object, fills it with customers and inventory items
 from the customerFile and inventoryFile, respectively, and processes commands
 on the StoreInventory object from a commandFile.
 Assumptions:
 The customer, inventory, and command files are named: hw4customers.txt,
 hw4inventory.txt, and hw4commands.txt, respectively.
 The files are correctly formatted as described in the program's design
 specification.
 */


#include "StoreInventory.h"


int main()
{

   std::string customerFileName =  "hw4customers.txt";
   
   std::string inventoryFileName = "hw4inventory.txt";
   
   std::string commandFileName = "hw4commands.txt";
   
   
   //read from the customer, inventory, and command files
   std::ifstream customerFile(customerFileName);
   if (!customerFile) {
      std::cerr << "File could not be opened." << std::endl;
      return 1;
   }
   
   std::ifstream inventoryFile(inventoryFileName);
   if (!inventoryFile) {
      std::cerr << "File could not be opened." << std::endl;
      return 1;
   }
   
   std::ifstream commandFile(commandFileName);
   if (!commandFile) {
      std::cerr << "File could not be opened." << std::endl;
      return 1;
   }
   
   //instantiate a StoreInventory object
   StoreInventory storeInv;
   
   //add customers to storeInv
   storeInv.addCustomersFromFile(customerFile);
   
   //add Collectible items to storeInv
   storeInv.buildInventoryFromFile(inventoryFile);
   
   //process commands on storeInv
   storeInv.processCommandsFromFile(commandFile);
   
   
   return 0;
}
