/*
 file name: CollectibleFactory.cpp
 author: Hall, Ashley
 The CollectibleFactory class employs a factory method to create subclasses of
 the Collectible class.
 */

#include "CollectibleFactory.h"
#include "Collectible.h"
#include "SportsCard.h"
#include "Comic.h"
#include "Coin.h"

/**
 Constructs a CollectibleFactory object and initializes the collectFactory array with addresses of
 subclass objects.
 @pre None
 @post The collectFactory array will be initialized with addresses of Collectible subclass objects.
 */
CollectibleFactory::CollectibleFactory() : factoryVector(FACTORY_SIZE, nullptr)
{
   //fill appropriate indices with addresses of Collectible subclass objects
   factoryVector[hash('S')] = new SportsCard;
   factoryVector[hash('C')] = new Comic;
   factoryVector[hash('M')] = new Coin;
}

/**
 Deallocates memory for objects in the factoryVector..
 @pre None
 @post Memory for objects in factoryVector will be deallocated.
 */
CollectibleFactory::~CollectibleFactory()
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
 Returns a pointer to a Collectible subclass object.
 @param objectType The char representing the Collectible subclass.
 @return A pointer to the created Collectible subclass object.
 @pre The itemType must hash to an index in the Collectible factory vector.
 @post A pointer to Collectible subclass object will be returned. If itemType does not hash to an int
 within the bounds of the collectible factory vector, an error will be output.
 */
Collectible* CollectibleFactory::createObject(char objectType) const
{
   //find appropriate index in factoryVector
   int index = hash(objectType);
   if ( index < 0 )
   {
      std::cerr << "CollectibleFactory::createObject: objectType hashed"
      <<" to negative index" << std:: endl;
      return nullptr;
   }
   //return a pointer to the Collectible subclass object
   if ( factoryVector[index] != nullptr )
      return factoryVector[index]->create();
   else
      return nullptr;
}

/**
 Hashes the given itemType to an int.
 @param objectType The char representing the Collectible subclass.
 @return The index that contains an address to the Collectible subclass object in the factory vector.
 @pre None
 @post The index of the factory vector will be returned as an int.
 */
int CollectibleFactory::hash(char objectType) const
{
   //accept chars from 'A'-'Z'
   if ( objectType < 'A' || objectType > 'Z' )
   {
      std::cerr << "CollectibleFactory::hash: invalid argument" << std::endl;
      return -1;
   }
   
   return (objectType - 'A') % factoryVector.size();

}


