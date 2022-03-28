/*
 file name: SearchTree.h
 author: Hall, Ashley
 description:
 The SearchTree class represents a binary search tree that stores the
 frequency of items in a document. Each node in the tree stores a unique
 Comparable (or an object from a subclass of Comparable) read from a document
 and its number of occurrences in the document. The tree is indexed by the
 value stored in each Comparable. Outputting a SearchTree object to the
 console will display each Comparable in the SearchTree and its number of
 occurrences in order. Each Comparable and its number of occurrences
 will be printed on one line separated by a space.
 */

#ifndef SearchTree_h
#define SearchTree_h

#include <iostream>


template<typename Comparable>
class SearchTree
{
private:
   
   struct TreeNode
   {
      Comparable* item; //pointer to a Comparable
      int itemCount; //the number of occurrences of the Comparable
      TreeNode* rightChildPtr; //pointer to the right child TreeNode
      TreeNode* leftChildPtr; //pointer to the left child TreeNode
   };
   
   TreeNode* root; //pointer to the root node
   
   /**
    Creates a deep copy of each node in the given SearchTree object.
    @param origTreePtr The TreeNode pointer to the root of the original tree.
    @return The TreeNode pointer to the root of the copied tree.
    @pre origTreePtr must be a pointer to a TreeNode
    @post All nodes in the original tree will be deep copied and the pointer to the root node of the copied
    tree will be returned.
    */
   TreeNode* copyTree( const TreeNode* origTreePtr ) const
   {
      //original tree is empty, return nullptr
      TreeNode* copiedTreePtr = nullptr;
      
      //tree is not empty
      if ( origTreePtr != nullptr )
      {
         //create a copy of the parent node in the original tree
         copiedTreePtr = new TreeNode;
         //create a copy of the Comparable in the original parent node
         Comparable* copiedItemPtr = new Comparable;
         //set the value of the copied Comparable to the value of the
         //original
         *copiedItemPtr = *origTreePtr->item;
         //set the copied node's item to point to the copied Comparable
         copiedTreePtr->item = copiedItemPtr;
         //set the Comparable count of the original node to the
         //copied node
         copiedTreePtr->itemCount = origTreePtr->itemCount;
         
         //recursively traverse the left subtree
         copiedTreePtr->leftChildPtr =
         copyTree( origTreePtr->leftChildPtr );
         
         //recursively traverse the right subtree
         copiedTreePtr->rightChildPtr =
         copyTree( origTreePtr->rightChildPtr );
      }
      
      //return the copied tree node pointer
      return copiedTreePtr;
   }
   
   /**
    Helper method to deallocate memory for the TreeNodes in the SearchTree and the
    Comparable objects within the TreeNodes. Sets the root to nullptr.
    @param treePtr The pointer to the root of the tree.
    @pre treePtr must be a pointer to a TreeNode object.
    @post Memory for the SearchTree's TreeNodes and the Comparable objects within the
    TreeNodes will be deallocated. The root will be set to nullptr.
    */
   void makeEmptyHelper( TreeNode*& treePtr )
   {
      //if tree contains nodes to be deleted
      if ( treePtr != nullptr )
      {
         //recursively traverse and delete nodes in the left subtree
         makeEmptyHelper(treePtr->leftChildPtr);
         //recursively traverse and delete nodes in the right subtree
         makeEmptyHelper(treePtr->rightChildPtr);
         
         //delete the parent node
         deleteNode( treePtr );
      }
   }
   
   /**
    Determines whether two trees or subtrees have the same node structure with each matching
    node pair containing identical data.
    @param treeNode1Ptr The TreeNode pointer to the root node of the first subtree.
    @param treeNode2Ptr The TreeNode pointer to the root of the second subtree.
    @return True if both TreeNode pointers  are nullptr or true if the TreeNode pointers point
    to trees with the same TreeNode structure where each matching TreeNode pair in the first
    and second tress contain the same items and item counts. Returns false otherwise.
    @pre treeNode1Ptr and treeNode2Ptr must be pointers to TreeNodes.
    @post Returns true if both TreeNode pointers  are nullptr or true if the TreeNode pointers
    point to trees with the same TreeNode structure where each matching TreeNode pair in the
    first and second tress contain the same items and item counts. Returns false otherwise.
    */
   bool sameNodes( const TreeNode* treeNode1Ptr,
                  const TreeNode* treeNode2Ptr) const
   {
      //subtrees are empty
      if ( treeNode1Ptr == nullptr && treeNode2Ptr == nullptr )
         return true;
      //one subtree is empty, the other is not
      else if ( treeNode1Ptr == nullptr ^ treeNode2Ptr == nullptr )
         return false;
      else
         //compare the nodes' items
         return *treeNode1Ptr->item == *treeNode2Ptr->item &&
         //compare the nodes' item counts
         treeNode1Ptr->itemCount == treeNode2Ptr->itemCount &&
         //recursively traverse the left subtree
         sameNodes( treeNode1Ptr->leftChildPtr,
                   treeNode2Ptr->leftChildPtr ) &&
         //recursively traverse the right subtree
         sameNodes( treeNode1Ptr->rightChildPtr,
                   treeNode2Ptr->rightChildPtr );
   }
   
   /**
    Helper method to output the SearchTree to the console.
    @param treePtr The TreeNode pointer to the root of the tree or subtree.
    @pre treePtr must be a pointer to a TreeNode.
    @post Displays each Comparable item in the SearchTree and the number of occurrences
    of that item. Each item is printed on one line followed by its number of occurrences separated
    by a space. If the SearchTree is empty nothing is displayed.
    */
   void printHelper( TreeNode* treePtr, std::ostream& outputStream ) const
   {
      //if tree is not empty
      if ( treePtr != nullptr )
      {
         //recursively traverse the left subtree
         printHelper( treePtr->leftChildPtr, outputStream );
         
         //print the item and item count, separated by a space
         outputStream << *treePtr->item << "; Count: " << treePtr->itemCount << std::endl;
         
         //recursively traverse the right subtree
         printHelper( treePtr->rightChildPtr, outputStream );
      }
   }
   
   /**
    Helper method to output items in the SearchTree to the console.
    @param treePtr The TreeNode pointer to the root of the tree or subtree.
    @pre treePtr must be a pointer to a TreeNode.
    @post Displays each Comparable item in the SearchTree and omits the number of occurrences
    of that item. Each item is printed on one line. If the SearchTree is empty nothing is displayed.
    */
   void printWithoutCountsHelper( TreeNode* treePtr ) const
   {
      //if tree is not empty
      if ( treePtr != nullptr )
      {
         //recursively traverse the left subtree
         printWithoutCountsHelper( treePtr->leftChildPtr );
         
         //print the item and item count, separated by a space
         std::cout << *treePtr->item;
         
         //recursively traverse the right subtree
         printWithoutCountsHelper( treePtr->rightChildPtr );
      }
   }
   
   /**
    Helper method to insert a Comparable into the SearchTree. If the Comparable is already in the tree,
    the number of occurrences for that Comparable will be incremented.
    @param treeNodePtr The pointer to the root of the tree.
    @param itemPtr The pointer to the Comparable to be inserted into the tree.
    @return True if the Comparable was inserted into the tree. False if the Comparable is already in the
    tree.
    @pre treeNodePtr must point to a TreeNode and itemPtr must point to a Comparable.
    @post If the Comparable is not found in the tree, it will be inserted in ASCII order and true will be
    returned. In addition, the ownership of memory for the Comparable will be transferred to the tree,
    the new TreeNode created will have an item count of 1, the number of nodes in the tree will be
    incremented, and the tree will maintain its binary tree structure. If the Comparable is in the tree,
    it will not be inserted, and false will be returned. In addition, the item count for the Comparable
    will be incremented in the relevant TreeNode and the number of nodes and the tree's structure will
    not change.
    */
   bool insertHelper( TreeNode*& treeNodePtr, Comparable*  itemPtr )
   {
      //ensure itemPtr != nullptr
      try
      {
         if ( itemPtr == nullptr )
            throw std::invalid_argument( "itemPtr is nullptr." );
         
         //if the tree is empty
         if ( treeNodePtr == nullptr )
         {
            //create a new node
            treeNodePtr = new TreeNode;
            //set item to the Comparable pointer passed in
            treeNodePtr->item = itemPtr;
            //set the number of occurrences of the item to 1
            treeNodePtr->itemCount = 1;
            //set children to nullptr
            treeNodePtr->leftChildPtr = nullptr;
            treeNodePtr->rightChildPtr = nullptr;
            return true;
         }
         //the tree is not empty
         //the value of the Comparable is less than the current TreeNode
         else if  ( *itemPtr < *treeNodePtr->item )
            //recursively call the method to insert into the left subtree
            return insertHelper( treeNodePtr->leftChildPtr, itemPtr );
         //the value of the Comparable is equal to the TreeNode,
         //the Comparable was found
         else if ( *itemPtr == *treeNodePtr->item )
         {
            //increase the number of occurrences
            treeNodePtr->itemCount++;
            return false;
         }
         //the value of the Comparable is greater than the TreeNode
         else
            //recursively call thte method to insert into the
            //right subtree
            return insertHelper( treeNodePtr->rightChildPtr, itemPtr );
      }
      //catch invalid argument: nullptr
      catch ( const std::invalid_argument& ex )
      {
         std::cerr << "Invalid argument: " << ex.what() << std::endl;
         return false;
      }
   }
   
   /**
    Helper method to insert a Comparable into the SearchTree. If the Comparable is already in the tree,
    the number of occurrences for that Comparable will be increased by numItems.
    @param treeNodePtr The pointer to the root of the tree.
    @param itemPtr The pointer to the Comparable to be inserted into the tree.
    @param numItems The number of items to insert into the tree.
    @return True if the Comparable was inserted into the tree. False if the Comparable is already in the
    tree.
    @pre treeNodePtr must point to a TreeNode and itemPtr must point to a Comparable.
    @post If the Comparable is not found in the tree, it will be inserted in order and true will be
    returned. In addition, the ownership of memory for the Comparable will be transferred to the tree,
    the new TreeNode created will have an item count of numItems, the number of nodes in the tree will be
    incremented, and the tree will maintain its binary tree structure. If the Comparable is in the tree,
    it will not be inserted, and false will be returned. In addition, the item count for the Comparable
    will be increased by numItems in the relevant TreeNode and the number of nodes and the
    tree's structure will not change.
    */
   bool insertHelper( TreeNode*& treeNodePtr,
                     Comparable* itemPtr, int numItems )
   {
      //ensure itemPtr != nullptr
      try
      {
         if ( itemPtr == nullptr )
            throw std::invalid_argument( "itemPtr is nullptr." );
         
         //if the tree is empty
         if ( treeNodePtr == nullptr )
         {
            //create a new node
            treeNodePtr = new TreeNode;
            //set item to the Comparable pointer passed in
            treeNodePtr->item = itemPtr;
            //set the number of occurrences of the item to numItems
            treeNodePtr->itemCount = numItems;
            //set children to nullptr
            treeNodePtr->leftChildPtr = nullptr;
            treeNodePtr->rightChildPtr = nullptr;
            return true;
         }
         //the tree is not empty
         //the value of the Comparable is less than the current TreeNode
         else if  ( *itemPtr < *treeNodePtr->item )
            //recursively call the method to insert into the left subtree
            return insertHelper( treeNodePtr->leftChildPtr, itemPtr, numItems );
         //the value of the Comparable is equal to the TreeNode,
         //the Comparable was found
         else if ( *itemPtr == *treeNodePtr->item )
         {
            //increase the number of occurrences
            treeNodePtr->itemCount += numItems;
            return false;
         }
         //the value of the Comparable is greater than the TreeNode
         else
            //recursively call thte method to insert into the
            //right subtree
            return insertHelper( treeNodePtr->rightChildPtr, itemPtr, numItems );
      }
      //catch invalid argument: nullptr
      catch ( const std::invalid_argument& ex )
      {
         std::cerr << "Invalid argument: " << ex.what() << std::endl;
         return false;
      }
   }
   
  
   
   /**
    Helper ;method to remove one occurrence of a Comparable from the tree. If it is the last occurrence,
    the relevant node will be removed.
    @param root The root of the tree.
    @param itemToRemove The Comparable item to be removed from the tree.
    @return True if one occurrence of the Comparable was removed from the tree. False if the
    Comparable was not be found.
    @pre root must be a TreeNode and itemToRemove must be a Comparable.
    @post If the Comparable is found and the item count > 1, the item count in the relevant node will be
    decremented, and true will be returned. If the item count <= 1, the relevant node will be removed from
    the tree, and true will be returned. In addition, the number of nodes in the tree will be decremented, and
    the tree will maintain its binary tree structure. If the Comparable is not found, false will be returned, and
    the number of nodes and the tree's structure will not change.
    */
   bool removeHelper( TreeNode*& root, const Comparable& itemToRemove )
   {
      //the tree or subtree is empty
      //the Comparable was not found
      if ( root == nullptr )
         return false;
      //the Comparable was found
      else if ( itemToRemove == *root->item )
      {
         //if the number of occurrences of the Comparable is > 1
         //decrement the count
         if ( root->itemCount > 1 )
         {
            root->itemCount--;
         }
         //the number of occurrences is == 1
         //delete the node
         else
            deleteNode( root );
         return true;
      }
      //if the value of the Comparable is less than the current node
      else if ( itemToRemove < *root->item )
         //recursively call the method to traverse the left subtree
         return removeHelper( root->leftChildPtr, itemToRemove );
      //the value of the Comparable is greater than the current node
      else
         //recursively call the method to traverse the right subtree
         return removeHelper( root->rightChildPtr, itemToRemove );
   }
   
   /**
    Deletes a node in the tree.
    @param treeNode The pointer to the node to be removed.
    @pre treeNode must be of type TreeNode and is not set to nullptr.
    @post The node will be deleted from the tree, the number of nodes in the tree will be decremented,
    and the tree will maintain its binary tree structure. No node will be deleted if the tree is empty.
    */
   void deleteNode( TreeNode*& treeNode )
   {
      //deleteNode should not be called with nullptr as arg
      try
      {
         if ( treeNode == nullptr )
            throw std::invalid_argument( "nullptr passed into deleteNode()");
         
         //deallocate memory for the Comparable
         if ( treeNode->item != nullptr )
         {
            delete treeNode->item;
            treeNode->item = nullptr;
         }
         
         
         //the node is a leaf
         if ( treeNode->leftChildPtr == nullptr &&
             treeNode->rightChildPtr == nullptr )
         {
            //deallocate memory for the TreeNode
            delete treeNode;
            //set to nullptr to prevent a dangling pointer
            treeNode = nullptr;
         }
         
         //the node has one child
         else if ( treeNode->leftChildPtr == nullptr
                  || treeNode->rightChildPtr == nullptr )
         {
            //create a temporary pointer to the node to be deleted
            TreeNode* nodeToDelete = treeNode;
            //the node has 1 right child
            if ( treeNode->rightChildPtr != nullptr )
               //let the parent of the current node adopt its right child
               treeNode = treeNode->rightChildPtr;
            //the node has 1 left child
            else
               //let the parent of the current node adopt its left child
               treeNode = treeNode->leftChildPtr;
            //delete the node
            delete nodeToDelete;
            nodeToDelete = nullptr;
         }
         
         //the node has 2 children
         else
         {
            //find the the node containing the smallest Comparable value
            //in the right subtree and set its Comparable pointer and its
            //item count to the current node's
            int itemCount;
            treeNode->item = findAndDeleteMostLeft( treeNode->rightChildPtr,
                                                   itemCount );
            treeNode->itemCount = itemCount;
         }
      }
      catch( const std::invalid_argument& ex )
      {
         std::cerr << "Invalid argument: " << ex.what() << std::endl;
      }
      
   }
   
   /**
    Deletes the node with the smallest Comparable value in the tree.
    @param treeNodePtr The pointer to a TreeNode.
    @param itemCount The number of occurrences of the smallest Comparable in the tree.
    @return The pointer to the Comparable with the smallest value in the tree.
    @pre treeNodePtr must be a pointer to a TreeNode and must not be set to nullptr. itemCount
    must be an int.
    @post Memory for the leftmost node in the tree will be deallocated and the Comparable pointer
    held by that node will be returned. The leftmost node's item and itemCount will be transferred to
    the parent of the TreeNode passed into the method. The number of TreeNodes in the tree will be
    decremented, and the tree will maintain its binary structure.
    */
   Comparable* findAndDeleteMostLeft( TreeNode*& treeNodePtr, int& itemCount )
   {
      //findAndDeleteMostLeft should not be called with nullptr as arg for
      //treeNodePtr
      try
      {
         if ( treeNodePtr == nullptr )
            throw
            std::invalid_argument( "nullptr passed into findAndDeleteMostLeft()" );
         
         //if the node has no left child, it holds the smallest Comparable
         if ( treeNodePtr->leftChildPtr == nullptr )
         {
            //create a pointer to the node's item
            Comparable* item = treeNodePtr->item;
            //set itemCount to the node's item count
            itemCount = treeNodePtr->itemCount;
            //create a pointer to the node to be deleted
            TreeNode* nodeToDelete = treeNodePtr;
            //let the parent of the current node adopt its right child
            //(or nullptr)
            treeNodePtr = treeNodePtr->rightChildPtr;
            //delete the node
            delete nodeToDelete;
            nodeToDelete = nullptr;
            //return the pointer to the smallest Comparable
            return item;
         }
         //the node has a left child, it does not hold the smallest
         //Comparable
         else
            return findAndDeleteMostLeft( treeNodePtr->leftChildPtr,
                                         itemCount );
      }
      catch ( const std::invalid_argument &ex )
      {
         std::cerr << "Invalid argument: " << ex.what() << std::endl;
         exit (EXIT_FAILURE);
      }
   }
   
   /**
    Finds the TreeNode containing the given Comparable.
    @param treeNodePtr The pointer to the root of the tree.
    @param itemToFind TheComparable to be found.
    @return The pointer to the TreeNode containing the given Comparable. Returns nullptr if
    the Comparable is not in the tree or the tree is empty.
    @pre treeNodePtr must be a TreeNode pointer and itemToFind must be a Comparable.
    @post If the Comparable is found, the TreeNode pointer containing the given Comparable will be
    returned. If it is not found, nullptr will be returned. If the tree is empty nullptr will be returned.
    */
   TreeNode* findNode( TreeNode* treeNodePtr, const Comparable& itemToFind )
   const
   {
      //the tree is empty or end of branch has been reached
      if ( treeNodePtr == nullptr )
         return nullptr;
      //the Comparable is less than the current node's
      else if ( itemToFind < *treeNodePtr->item )
         //recursively traverse the left subtree
         return findNode( treeNodePtr->leftChildPtr, itemToFind );
      //the Comparable is equal to the current node's
      else if ( itemToFind == *treeNodePtr->item )
         //the Comparable was found return the TreeNode pointer
         return treeNodePtr;
      //the Comparable is greater than the current node's
      else
         //recursively traverse the right subtree
         return findNode( treeNodePtr->rightChildPtr, itemToFind );
   }
   
   /**
    Returns the height of a given TreeNode in the tree.
    @param treeNodePtr The pointer to a TreeNode
    @return An int representing the height of the TreeNode in the tree. If the tree is empty 0 will be
    returned.
    @pre treeNodePtr must be a TreeNode.
    @post An int representing the height of the TreeNode in the tree. If the tree is empty 0 will be
    returned.
    */
   int nodeHeight( TreeNode* treeNodePtr ) const
   {
      //the tree or subtree is empty
      if ( treeNodePtr == nullptr )
         return 0;
      //the node is a leaf
      else if ( treeNodePtr->leftChildPtr == nullptr &&
               treeNodePtr->rightChildPtr == nullptr )
         return 0;
      else
      {
         //find the max height between the left and right subtrees
         int maxHeight = max( nodeHeight( treeNodePtr->leftChildPtr ),
                             nodeHeight( treeNodePtr->rightChildPtr ) );
         return 1 + maxHeight;
      }
   }
   
   /**
    Helper method to find the maximum of two numbers.
    @param num1 The first number to compare.
    @param num2 The second number to compare.
    @return An int representing the maximum number.
    @pre num1 and num2 must be of type int.
    @post The maximum of the two numbers will be returned as an int. If num1 == num2, num2
    will be returned.
    */
   int max( const int& num1, const int& num2 ) const
   {
      return num1 > num2 ? num1 : num2;
   }
   
public:
   
   /**
    The default constructor.
    Constructs an empty SearchTree object and initializes the root to nullptr.
    @pre None.
    @post An empty SearchTree object will be instantiated, and its root will be initialized to nullptr.
    */
   SearchTree() : root(nullptr) {};
   
   /**
    The copy constructor.
    Creates a deep copy of the supplied SearchTree object.
    @param tree The SearchTree object to be copied.
    @pre The parameter tree must be a SearchTree object.
    @post A deep copy of the SearchTree object passed in as the argument will be created.
    */
   SearchTree( const SearchTree& tree )
   {
      root = copyTree( tree.root );
   }
   
   /**
    The destructor.
    Destroys the SearchTree object, freeing the memory allocated for the TreeNode objects and the
    Comparable objects within the TreeNodes when the object's lifetime ends.
    @pre None.
    @post Memory for the SearchTree's TreeNodes and the Comparable objects within the TreeNodes
    will be deallocated.
    */
   virtual ~SearchTree()
   {
      //calls private method on root pointer to recursively delete nodes
      makeEmpty();
   }
   
   /**
    Overloaded assignment operator.
    Creates a deep copy of the tree on the right side of the operator and assigns it
    to the tree on the left side.
    @param rightTree The tree on the right side of the assignment operator.
    @pre Operands must be SearchTree objects.
    @post The tree on the left side of the operator will be a deep copy of the tree on the right.
    */
   SearchTree& operator=( const SearchTree& rightTree )
   {
      //make sure objects aren't the same by comparing addresses
      if ( this != &rightTree)
      {
         //deallocate memory assigned to left hand tree
         makeEmpty();
         
         //copy nodes from right hand tree to left hand tree
         root = copyTree(rightTree.root);
      }
      
      //return a copy of the right hand tree
      return *this;
   }
   
   /**
    Overloaded equality operator.
    Determines if two SearchTree objects are equal.
    @param rightTree The SearchTree object on the right side of the operator.
    @return True if both SearchTree objects are empty or true if the SearchTree
    objects on the left and right side of the operator have the same TreeNode structure
    and each structurally matching TreeNode pair on the left and right contain the same i
    tems and item counts. Returns false otherwise.
    @pre The operands must be of type SearchTree.
    @post Returns true if both SearchTree objects are empty or true if the SearchTree objects
    on the left and right side of the operator have the same TreeNode structure and each
    structurally matching TreeNode pair on the left and right contain the same items and
    item counts. Returns false otherwise.
    */
   bool operator==( const SearchTree& rightTree )
   {
      return sameNodes( root, rightTree.root );
   }
   
   /**
    Overloaded inequality operator.
    Determines if two SearchTree objects are not equal.
    @param rightTree The SearchTree object on the right side of the operator.
    @return False if both SearchTree objects are empty or false if the SearchTree
    objects on the left and right side of the operator have the same TreeNode structure
    and each structurally matching TreeNode pair on the left and right contain the
    same items and item counts. Returns true otherwise.
    @pre The operands must be of type SearchTree.
    @post Returns false if both SearchTree objects are empty or false if the SearchTree
    objects on the left and right side of the operator have the same TreeNode structure and
    each structurally matching TreeNode pair on the left and right contain the same items
    and item counts. Returns true otherwise.
    */
   bool operator!=( const SearchTree& rightTree )
   {
      return !sameNodes( root, rightTree.root );
   }
   
   /**
    Overloaded  stream insertion operator.
    Outputs the SearchTree object to the console.
    @param outputStream The output stream from which to display the SearchTree object.
    @param outputSearchTree The SearchTree object to be displayed.
    @return The output stream.
    @pre None.
    @post Displays each item in the SearchTree and the number of occurrences of that item. Each item
    is printed on one line followed by its number of occurrences separated by a space. If the SearchTree
    is empty a message to the console indicating so will be printed.
    */
   friend std::ostream& operator<<( std::ostream& outputStream,
                                   const SearchTree& outputSearchTree )
   {
      //if tree is not empty
      if ( outputSearchTree.root != nullptr )
      {
         //print the contents using an inorder traversal
         outputSearchTree.printHelper(outputSearchTree.root, outputStream);
      }
      
      return outputStream;
   }
   
   /**
    Prints the items in the SearchTree. Omits their counts.
    @pre None
    @post Items in the SearchTree will be printed in order. If the tree is empty, nothing will be printed.
    */
   void printWithoutCounts() const
   {
      printWithoutCountsHelper(root);
   }
   
   
   
   /**
    Inserts a Comparable into the SearchTree. If the Comparable is already in the tree, the number of
    occurrences for that Comparable will be incremented.
    @param itemPtr The pointer to the Comparable to be inserted into the tree.
    @return True if the Comparable was inserted into the tree. False if the Comparable is already in
    the tree.
    @pre itemPtr must point to a Comparable.
    @post If the Comparable is not found in the tree, it will be inserted in ASCII order and true will be
    returned. In addition, the ownership of memory for the Comparable will be transferred to the tree,
    the new TreeNode created will have an item count of 1, the number of nodes in the tree will be
    incremented, and the tree will maintain its binary tree structure. If the Comparable is in the tree,
    it will not be inserted, and false will be returned. In addition, the item count for the Comparable
    will be incremented in the relevant TreeNode and the number of nodes and the tree's structure will
    not change.
    */
   bool insert( Comparable* itemPtr )
   {
      return insertHelper( root, itemPtr );
   }
   
   bool insert( Comparable* itemPtr, int numItems )
   {
      return insertHelper( root, itemPtr, numItems );
   }
   
   /**
    Removes one occurrence of a Comparable from the tree. If it is the last occurrence, the relevant
    node will be removed.
    @param itemToRemove The Comparable item to be removed from the tree.
    @return True if one occurrence of the Comparable was removed from the tree. False if the
    Comparable was not found.
    @pre itemToRemove must be a Comparable.
    @post If the Comparable is found and the item count > 1, the item count in the relevant node
    will be decremented, and true will be returned. If the item count <= 1, the relevant node will be
    removed from the tree, and true will be returned. In addition, the number of nodes in the tree will
    be decremented, and the tree will maintain its binary tree structure. If the Comparable is not found,
    false will be returned, and the number of nodes and the tree's structure will not change.
    */
   bool remove( const Comparable& itemToRemove )
   {
      return removeHelper( root, itemToRemove);
   }
   
   /**
    Deallocates memory for the TreeNodes in the SearchTree and the Comparable objects
    within the TreeNodes, and sets the root to nullptr.
    @pre None.
    @post Memory for the SearchTree's TreeNodes and the Comparable objects within the
    TreeNodes will be deallocated. The root will be set to nullptr.
    */
   void makeEmpty()
   {
      makeEmptyHelper( root );
   }
   
   /**
    Retrieves a Comparable in the tree.
    @param itemToRetrieve The Comparable to be retrieved.
    @return The Comparable to be retrieved or nullptr if it is not found.
    @pre itemToRetrieve must be a Comparable
    @post If the Comparable is found, a pointer to a Comparable of the same value will be returned.
    If the Comparable is not found, nullptr will be returned.
    */
   const Comparable* retrieve( const Comparable& itemToRetrieve ) const
   {
      //find the node containing the desired Comparable
      TreeNode* treeNode = findNode( root, itemToRetrieve );
      //if the node was found
      if ( treeNode != nullptr )
         //return the pointer to the Comparable
         return treeNode->item;
      //the node was not found
      else
         return nullptr;
   }
   
   /**
    Determines if the SearchTree contains an item.
    @param item The Comparable to find.
    @return True if the SearchTree contains the item. False otherwise.
    @pre item must be of type Comparable
    @post True will be returned if the SearchTree contains the item. False otherwise.
    */
   bool contains( const Comparable& item ) const
   {
      return retrieve(item) != nullptr;
   }
   
   /**
    Returns the height of the node storing the Comparable in the tree.
    @param key The Comparable by which to search the tree.
    @return If the Comparable is found, an int representing the height of the node storing the given
    Comparable. If it is not found, -1 is returned.
    @pre key must be a Comparable.
    @post If the Comparable is found, an int representing the height of the node storing the given
    Comparable will be returned. If it is not found, -1 will be returned.
    */
   int height( const Comparable& key )
   {
      //find the TreeNode containing the given Comparable
      TreeNode* treeNode = findNode( root, key );
      //node was not found
      if ( treeNode == nullptr )
         return -1;
      //node was found, get its height
      else
         return nodeHeight( treeNode );
   }
   
   /**
    Determines whether the SearchTree is empty.
    @pre None.
    @post True will be returned if the SearchTree contains no items. False otherwise.
    */
   bool isEmpty() const
   {
      return root == nullptr;
   }
   
};


#endif
