/*
 file name: CollectibleFactory.h
 author: Hall, Ashley
 The CollectibleFactory class employs a factory method to create subclasses of
 the Collectible class.
 */

#ifndef COLLECTIBLEFACTORY_H
#define COLLECTIBLEFACTORY_H

#include "Collectible.h"


class CollectibleFactory
{
   
public:
   
   /**
    Constructs a CollectibleFactory object and initializes the collectFactory array with addresses of
    subclass objects.
    @pre None
    @post The collectFactory array will be initialized with addresses of Collectible subclass objects.
    */
   CollectibleFactory();
   
   /**
    Deallocates memory for objects in the factoryVector..
    @pre None
    @post Memory for objects in factoryVector will be deallocated.
    */
   virtual ~CollectibleFactory();
   
   /**
    Returns a pointer to a Collectible subclass object.
    @param objectType The char representing the Collectible subclass.
    @return A pointer to the created Collectible subclass object.
    @pre The itemType must hash to an index in the Collectible factory vector.
    @post A pointer to Collectible subclass object will be returned. If itemType does not hash to an int
    within the bounds of the collectible factory vector, an error will be output.
    */
   virtual Collectible* createObject(char objectType) const;
   
   
protected:
   
   /**
    Hashes the given itemType to an int.
    @param objectType The char representing the Collectible subclass.
    @return The index that contains an address to the Collectible subclass object in the factory vector.
    @pre None
    @post The index of the factory vector will be returned as an int.
    */
   virtual int hash(char objectType) const;
   
   const static int FACTORY_SIZE = 29;
   
   //array of pointers to Collectible objects
   std::vector<Collectible*> factoryVector;

};


#endif

