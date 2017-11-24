#include "AVL.h"

/*	=================== Constructor ===================
Initializes private data.
Pre     class is being defined
Post    private data initialized
*/

template <class ItemType>
AvlTree<ItemType>::AvlTree() : tree(nullptr), count(0)
{
}	//  Constructor

template<class ItemType>
AvlTree<ItemType>::AvlTree(const AvlTree<ItemType>& treePtr)
{
	tree = copyTree(treePtr.tree);
}	// end Copy Constructor


	/*	==================== add ====================
	This function inserts new data into the tree.
	Pre    newData contains data to be inserted
	Post   data have been inserted or memory overflow
	Return success (true) or overflow (false)
	*/

template <class ItemType>
bool AvlTree<ItemType>::add(const ItemType& newData)
{
	//	Local Definitions 
	BinaryNode<ItemType>  *newPtr;
	bool taller;

	//	Statements 
	if (!(newPtr = new BinaryNode<ItemType>))
		return false;
	
	newPtr->setBalance(EH);
	newPtr->setRightChildPtr(nullptr);
	newPtr->setLeftChildPtr(nullptr);
	newPtr->setItem(newData);

	try {
		tree = insert(tree, newPtr, taller);
		count++;
	}
	catch (DuplicateException) {
		return false;
	}
	return true;
}	//  Avl_Insert   


	/*	======================= insert =======================
	This function uses recursion to insert the new data into
	a leaf BinaryNode in the AVL tree.
	Pre    application has called AVL_Insert, which passes
	root and data pointers
	Post   data have been inserted
	Return pointer to [potentially] new root
	*/

template <class ItemType>
BinaryNode<ItemType>*  AvlTree<ItemType>::insert(BinaryNode<ItemType> *rootPtr, BinaryNode<ItemType> *newPtr, bool& taller) throw (DuplicateException)
{
	//	Statements   
	if (rootPtr == nullptr)
	{
		rootPtr = newPtr;
		taller = true;
		return  rootPtr;
	} //  if NULL tree 

	// No duplicate keys allowed
	if ( newPtr->getItem() == rootPtr->getItem() )
		throw DuplicateException();

	if ( newPtr->getItem() < rootPtr->getItem() )
	{
		rootPtr->setLeftChildPtr( insert(rootPtr->getLeftChildPtr(), newPtr, taller) );
		if (taller)
			//  Left subtree is taller 
			switch ( rootPtr->getBalance() )
			{
			case 1: // Was left high--rotate 
				rootPtr = leftBalance(rootPtr, taller);
				break;

			case 0: // Was balanced--now LH 
				rootPtr->setBalance(LH);
				break;

			case -1: // Was right high--now EH 
				rootPtr->setBalance(EH);
				taller = false;
				break;
			} // switch 
	} //  new data < root data 
	else
		//  new data > root data 
	{
		rootPtr->setRightChildPtr( insert(rootPtr->getRightChildPtr(), newPtr, taller) );
		if (taller)
			// Right subtree is taller
			switch (rootPtr->getBalance())
			{
			case 1: // Was left high--now EH 
				rootPtr->setBalance(EH);
				taller = false;
				break;

			case 0: // Was balanced--now RH
				rootPtr->setBalance(RH);
				break;

			case -1: // Was right high--rotate 
				rootPtr = rightBalance(rootPtr, taller);
				break;
			} //  switch 
	} //  else new data > root data 
	return rootPtr;
}	//  _insert 


	/*	===================== leftBalance =====================
	The tree is out of balance to the left. This function
	rotates the tree to the right.
	Pre     the tree is left high
	Post    balance restored
	Returns potentially new root
	*/

template <class ItemType>
BinaryNode<ItemType>  *AvlTree<ItemType>::leftBalance(BinaryNode<ItemType> *rootPtr, bool& taller)
{
	// 	Local Definitions 
	BinaryNode<ItemType>  *rightTree;
	BinaryNode<ItemType>  *leftTree;

	//	Statements 
	leftTree = rootPtr->getLeftChildPtr();
	switch ( leftTree->getBalance() )
	{
	case 1: // Left High--Rotate Right 
		rootPtr->setBalance(EH);
		leftTree->setBalance(EH);

		// Rotate Right 
		rootPtr = rotateRight(rootPtr);
		taller = false;
		break;
	case 0: // This is an error 
		cout << "\n\a\aError in leftBalance\n";
		exit(100);
	case -1: // Right High - Requires double rotation: 
			 // first left, then right 
		rightTree = leftTree->getRightChildPtr();
		switch ( rightTree->getBalance() )
		{
		case 1: 
			rootPtr->setBalance(RH);
			leftTree->setBalance(EH);
			break;
		case 0: 
			rootPtr->setBalance(EH);
			leftTree->setBalance(EH);
			break;
		case -1: 
			rootPtr->setBalance(EH);
			leftTree->setBalance(LH);
			break;
		} //  switch rightTree 

		rightTree->setBalance(EH);
		//  Rotate Left 
		rootPtr->setLeftChildPtr( rotateLeft(leftTree) );

		// Rotate Right 
		rootPtr = rotateRight(rootPtr);
		taller = false;
	} // switch leftTree
	return rootPtr;
}	// leftBalance 


	/*	===================== rotateLeft ======================
	This function exchanges pointers so as to rotate the
	tree to the left.
	Pre  rootPtr points to tree to be rotated
	Post BinaryNode rotated and new root returned
	*/

template <class ItemType>
BinaryNode<ItemType>* AvlTree<ItemType>::rotateLeft(BinaryNode<ItemType> *rootPtr)
{
	//	Local Definitions 
	BinaryNode<ItemType>  *tempPtr;

	//	Statements 
	tempPtr = rootPtr->getRightChildPtr();
	rootPtr->setRightChildPtr( tempPtr->getLeftChildPtr() );
	tempPtr->setLeftChildPtr( rootPtr );

	return tempPtr;
}	//  rotateLeft 


	/*	===================== rotateRight =====================
	This function exchanges pointers to rotate the tree
	to the right.
	Pre   rootPtr points to tree to be rotated
	Post  BinaryNode rotated and new root returned
	*/

template <class ItemType>
BinaryNode<ItemType>*  AvlTree<ItemType>::rotateRight(BinaryNode<ItemType> *rootPtr)
{
	//	Local Definitions 
	BinaryNode<ItemType>  *tempPtr;

	//	Statements 
	tempPtr = rootPtr->getLeftChildPtr();
	rootPtr->setLeftChildPtr( tempPtr->getRightChildPtr() );
	tempPtr->setRightChildPtr( rootPtr );

	return tempPtr;
}	//  rotateRight  


	/*	====================  rightBalance ===================
	The tree is out-of-balance to the right. This function
	rotates the tree to the left.
	Pre     The tree is right high
	Post    Balance restored
	Returns potentially new root
	*/

template <class ItemType>
BinaryNode<ItemType>* AvlTree<ItemType>::rightBalance(BinaryNode<ItemType> *rootPtr, bool& taller)
{
	//	Local Definitions 
	BinaryNode<ItemType> *rightTree;
	BinaryNode<ItemType> *leftTree;

	//	Statements 
	rightTree = rootPtr->getRightChildPtr();

	switch ( rightTree->getBalance() )
	{
	case 1: // Left High - Requires double rotation:
			 //             first right, then left 
		leftTree = rightTree->getLeftChildPtr();

		//  First Rotation - Left 
		switch ( leftTree->getBalance() )
		{
		case -1: 
			rootPtr->setBalance(LH);
			rightTree->setBalance(EH);
			break;

		case 0: 
			rootPtr->setBalance(EH);
			rightTree->setBalance(EH);
			break;

		case 1: 
			rootPtr->setBalance(EH);
			rightTree->setBalance(RH);
			break;
		} //  switch 
		leftTree->setBalance(EH);

		rootPtr->setRightChildPtr( rotateRight(rightTree) );
		rootPtr = rotateLeft(rootPtr);
		taller = false;
		break;

	case 0: // Deleting from balanced BinaryNode 
		rootPtr->setBalance(EH);
		taller = false;
		break;

	case -1: // Right High - Rotate Left 
		rootPtr->setBalance(EH);
		rightTree->setBalance(EH);
		rootPtr = rotateLeft(rootPtr);
		taller = false;
		break;
	} // switch 
	return rootPtr;
}	//  rightBalance   


	/*	====================== remove ======================
	This function deletes a BinaryNode from the tree and rebalances
	it if necessary.
	Pre    searchKey contains key to be deleted
	Post   the BinaryNode is deleted and its space recycled
	-or- an error code is returned
	Return success (true) or not found (false)
	*/

template <class ItemType>
bool  AvlTree <ItemType>::remove(const ItemType& searchKey)
{
	//	Local Definitions 
	bool shorter;
	bool success;

	BinaryNode<ItemType>  *newRoot;

	//	Statements 
	newRoot = removeValue(tree, searchKey, shorter, success);
	if (success)
	{
		tree = newRoot;
		count--;
	} // if 
	return success;
}	// remove


	/*	======================== removeValue =======================
	This function deletes a BinaryNode from the tree and rebalances
	it if necessary.
	Pre    searchKey contains key of BinaryNode to be deleted
	shorter is Boolean indicating tree is shorter
	Post   the BinaryNode is deleted and its space recycled
	-or- if key not found, tree is unchanged
	Return true if deleted, false if not found
	pointer to root
	*/

template <class ItemType>
BinaryNode<ItemType>* AvlTree<ItemType>::removeValue(BinaryNode<ItemType> *rootPtr, const ItemType& searchKey, bool& shorter, bool& success)
{
	//  Local Definitions 
	BinaryNode<ItemType> *dltPtr;
	BinaryNode<ItemType> *exchPtr;
	BinaryNode<ItemType> *newRoot;

	// 	Statements 
	if (rootPtr == nullptr)
	{
		shorter = false;
		success = false;
		return nullptr;
	} //  if -- base case 

	if ( searchKey < rootPtr->getItem() )
	{
		rootPtr->setLeftChildPtr( removeValue(rootPtr->getLeftChildPtr(), searchKey, shorter, success) );
		if (shorter)
			rootPtr = dltRightBalance(rootPtr, shorter);
	} // if less 
	else if ( searchKey > rootPtr->getItem() )
	{
		rootPtr->setRightChildPtr( removeValue(rootPtr->getRightChildPtr(), searchKey, shorter, success) );
		if (shorter)
			rootPtr = dltLeftBalance(rootPtr, shorter);
	} //  if greater 
	else
		//  Found equal BinaryNode 
	{
		dltPtr = rootPtr;
		if ( rootPtr->getRightChildPtr() == nullptr )
			// Only left subtree 
		{
			newRoot = rootPtr->getLeftChildPtr();
			success = true;
			shorter = true;
			delete dltPtr;
			dltPtr = nullptr;
			return newRoot;            //  base case 
		} //  if true 
		else
			if ( rootPtr->getLeftChildPtr() == nullptr )
				//  Only right subtree 
			{
				newRoot = rootPtr->getRightChildPtr();
				success = true;
				shorter = true;
				delete dltPtr;
				dltPtr = nullptr;
				return newRoot;        // base case 
			} //  if 
			else
				//  Delete BinaryNode has two subtrees 
			{
				exchPtr = rootPtr->getLeftChildPtr();
				while (exchPtr->getRightChildPtr() != nullptr)
					exchPtr = exchPtr->getRightChildPtr();

				rootPtr->setItem( exchPtr->getItem() );
				rootPtr->setLeftChildPtr( removeValue(rootPtr->getLeftChildPtr(), exchPtr->getItem(), shorter, success) );
				if (shorter)
					rootPtr = dltRightBalance(rootPtr, shorter);
			} //  else 

	} // equal BinaryNode 
	return rootPtr;
}	// removeValue


	// ================== dltLeftBalance ==================
	/*	The tree is out-of-balance to the left (left high)--
	rotates the tree to the right.
	Pre     The tree is left high
	Post    Balance has been restored
	Returns potentially new root
	*/

template <class ItemType>
BinaryNode<ItemType>*  AvlTree<ItemType>::dltLeftBalance(BinaryNode<ItemType> *rootPtr, bool& smaller)
{
	//	Local Definitions 
	BinaryNode<ItemType>  *rightTree;
	BinaryNode<ItemType>  *leftTree;

	//	Statements 
	switch ( rootPtr->getBalance() )
	{
	case -1:  
		rootPtr->setBalance(EH);
		break;

	case 0:  // Delete occurred on right 
		rootPtr->setBalance(LH);
		smaller = false;
		break;

	case 1:  
		leftTree = rootPtr->getLeftChildPtr();

		switch ( leftTree->getBalance() )
		{
		case 1:
		case 0: // Rotate Single Left 
			if ( leftTree->getBalance() == EH )
			{
				rootPtr->setBalance(LH);
				leftTree->setBalance(RH);
				smaller = false;
			} // if
			else
			{
				rootPtr->setBalance(EH);
				leftTree->setBalance(EH);
			} // else

			rootPtr = rotateRight(rootPtr);
			break;

		case -1:	//Double Rotation 
			rightTree = leftTree->getRightChildPtr();
			switch ( rightTree->getBalance() )
			{
			case 1: 
				rootPtr->setBalance(RH);
				leftTree->setBalance(EH);
				break;
			case 0: 
				rootPtr->setBalance(EH);
				leftTree->setBalance(EH);
				break;
			case -1: 
				rootPtr->setBalance(EH);
				leftTree->setBalance(LH);
				break;
			} //  switch 
			rightTree->setBalance(EH);
			rootPtr->setLeftChildPtr( rotateLeft(leftTree) );
			rootPtr = rotateRight(rootPtr);
			break;
		} //  switch : leftTree->balanced  

	} //  switch : root->balanced 
	return rootPtr;
}	// dltLeftBalance 


	/*	=================== dltRightBalance ==================
	The tree is shorter after a delete on the left.
	Adjust the balance factors and rotate the tree
	to the left if necessary.
	Pre     the tree is shorter
	Post    balance factors adjusted and balance restored
	Returns potentially new root
	*/

template <class ItemType>
BinaryNode<ItemType>* AvlTree<ItemType>::dltRightBalance(BinaryNode<ItemType> *rootPtr, bool& shorter)
{
	//  Local Definitions 
	BinaryNode<ItemType>  *rightTree;
	BinaryNode<ItemType>  *leftTree;

	//	Statements
	switch ( rootPtr->getBalance() )
	{
	case 1: //  Deleted Left--Now balanced 
		rootPtr->setBalance(EH);
		break;
	case 0: //  Now Right high 
		rootPtr->setBalance(RH);
		shorter = false;
		break;
	case -1: //  Right High - Rotate Left 
		rightTree = rootPtr->getRightChildPtr();
		if ( rightTree->getBalance() == LH )
			// Double rotation required 
		{
			leftTree = rightTree->getLeftChildPtr();

			switch ( leftTree->getBalance() )
			{
			case 1: 
				rightTree->setBalance(RH);
				rootPtr->setBalance(EH);
				break;
			case 0: 
				rootPtr->setBalance(EH);
				rightTree->setBalance(EH);
				break;
			case -1: 
				rootPtr->setBalance(LH);
				rightTree->setBalance(EH);
				break;
			} // switch 

			leftTree->setBalance(EH);

			// Rotate Right then Left 
			rootPtr->setRightChildPtr( rotateRight(rightTree) );
			rootPtr = rotateLeft(rootPtr);
		} //  if rightTree->bal == LH 
		else
		{
			//  Single Rotation Only 
			switch ( rightTree->getBalance() )
			{
			case 1:
			case -1:
				rootPtr->setBalance(EH);
				rightTree->setBalance(EH);
				break;
			case 0: 
				rootPtr->setBalance(RH);
				rightTree->setBalance(LH);
				shorter = false;
				break;
			} // switch rightTree->bal 
			rootPtr = rotateLeft(rootPtr);
		} // else 
	} //  switch root bal 
	return rootPtr;
}	//  dltRightBalance 


	/*	==================== get ===================
	Retrieve BinaryNode searches the tree for the BinaryNode containing
	the requested key and returns pointer to its data.
	Pre     searchKey is variable to receive data
	Post    tree searched and data returned
	Return  true if found, false if not found
	*/
template <class ItemType>
bool  AvlTree<ItemType>::get(ItemType& searchKey) const
{
	//	Local Definitions
	BinaryNode<ItemType> *BinaryNode;

	//	Statements 
	if (tree == nullptr)
		return false;

	BinaryNode = findNode(searchKey, tree);
	if (BinaryNode != nullptr)
	{
		searchKey = BinaryNode->getItem();
		return true;
	} // if found
	else
		return false;
}	//  get


	/*	===================== findNode =====================
	Retrieve searches tree for BinaryNode containing requested
	key and returns its data to the calling function.
	Pre     get called: passes key to be located
	Post    tree searched and data pointer returned
	Return  address of matching BinaryNode returned
	if not found, nullptr returned
	*/
template <class ItemType>
BinaryNode<ItemType>* AvlTree<ItemType>::findNode(const ItemType& key, BinaryNode<ItemType> *rootPtr) const
{
	//	Statements 
	if (rootPtr != nullptr)
	{
		if ( key < rootPtr->getItem() )
			return findNode( key, rootPtr->getLeftChildPtr() );
		else if ( key > rootPtr->getItem() )
			return findNode( key, rootPtr->getRightChildPtr() );
		else
			// Found equal key 
			return rootPtr;
	} // if root 
	else
		//Data not in tree 
		return rootPtr;
}	//  findNode 

template<class ItemType>
BinaryNode<ItemType>* AvlTree<ItemType>::copyTree(const BinaryNode<ItemType>* treePtr) const
{
	BinaryNode<ItemType>* newTreePtr = nullptr;

	// Copy tree nodes
	if (treePtr != nullptr)
	{
		newTreePtr = new BinaryNode<ItemType>(treePtr->getItem(), nullptr, nullptr);
		newTreePtr->setLeftChildPtr( copyTree(treePtr->getLeftChildPtr()) );
		newTreePtr->setRightChildPtr( copyTree(treePtr->getRightChildPtr()) );
	}

	return newTreePtr;
}	// end copyTree


	/*	==================== Public Traversals ====================
	Process tree using inorder, preorder, and postorder traversals.
	Pre   process used to "visit" BinaryNodes during traversal
	Post  all BinaryNodes processed in LNR (inorder) sequence
	*/

template<class ItemType>
void AvlTree<ItemType>::preorderTraverse( void visit(ItemType&) ) const
{
	preorder(visit, tree);
}   // end preorderTraverse

template <class ItemType>
void  AvlTree<ItemType>::inorderTraverse( void visit(ItemType&) ) const
{
	inorder(visit, tree);
}	// end inorderTraverse 

template<class ItemType>
void AvlTree<ItemType>::postorderTraverse( void visit(ItemType&) ) const
{
	postorder(visit, tree);
}   // end postorderTraverse


	/*	===================== Private Traversals =====================
	Traverse tree using inorder, preorder, and postorder traversals. To process a
	BinaryNode, we use the function passed when traversal is called.
	Pre   tree has been created (may be null)
	Post  all BinaryNodes processed
	*/

template<class ItemType>
void AvlTree<ItemType>::preorder(void visit(ItemType&), BinaryNode<ItemType>* rootPtr) const
{
	if (rootPtr != nullptr)
	{
		ItemType theItem = rootPtr->getItem();
		visit(theItem);
		preorder(visit, rootPtr->getLeftChildPtr());
		preorder(visit, rootPtr->getRightChildPtr());
	}  // end if
}  // end preorder

template <class ItemType>
void  AvlTree<ItemType>::inorder(void visit(ItemType&), BinaryNode<ItemType>* rootPtr) const
{
	//	Statements 
	if (rootPtr != nullptr)
	{
		inorder( visit, rootPtr->getLeftChildPtr() );
		ItemType theItem = rootPtr->getItem();
		visit(theItem);
		inorder( visit, rootPtr->getRightChildPtr() );
	} //  if 
}	//  inorder 

   // added
template<class ItemType>
void AvlTree<ItemType>::postorder(void visit(ItemType&), BinaryNode<ItemType>* rootPtr) const
{
	if (rootPtr != nullptr)
	{
		postorder(visit, rootPtr->getLeftChildPtr());
		postorder(visit, rootPtr->getRightChildPtr());
		ItemType theItem = rootPtr->getItem();
		visit(theItem);
	}  // end if
}  // end preorder


	/*	=================== isEmpty ==================
	Returns true if tree is empty, false if any data.
	Pre      tree has been created; may be null
	Returns  true if tree empty, false if any data
	*/

template <class ItemType>
bool AvlTree<ItemType>::isEmpty() const
{
	//	Statements 
	return (count == 0);
}	//  AVL_Empty 


	/*	=================== isFull ===================
	If there is no room for another BinaryNode, returns true.
	Pre      tree has been created
	Returns  true if no room, false if room
	*/

template <class ItemType>
bool AvlTree<ItemType>::isFull() const
{
	//	Local Definitions 
	BinaryNode<ItemType>  *newPtr;

	//	Statements 
	newPtr = new BinaryNode<ItemType>;
	if (newPtr)
	{
		delete  newPtr;
		newPtr = nullptr;
		return false;
	} // if
	else
		return true;
}	//  AVL_Full 


	/*	=================== getNumberOfNodes ===================
	Returns number of BinaryNodes in tree.
	Pre     tree has been created
	Returns tree count
	*/

template <class ItemType>
int  AvlTree<ItemType>::getNumberOfNodes() const
{
	return (count);
}	//  AVL_Count 


	/*	=================== Destructor ===================
	Deletes all data in tree and recycles memory.
	The BinaryNodes are deleted by calling a recursive
	function to traverse the tree in inorder sequence.
	Pre      tree is a pointer to a valid tree
	Post     all data have been deleted
	*/

template <class ItemType>
AvlTree<ItemType>:: ~AvlTree()
{
	//	Statements 
	if (tree)
		destroyTree(tree);
}	// Destructor

template<class ItemType>
AvlTree<ItemType>& AvlTree<ItemType>::operator=(const AvlTree<ItemType> & rightTree)
{
	if (this == &rightTree)
		return *this;
	
	destroyTree(tree);

	tree = copyTree(rightTree.tree);

	return *this;
}	// end overloaded = operator


	/*	=================== destroyTree ===================
	Deletes all data in tree and recycles memory.
	The BinaryNodes are deleted by calling a recursive
	function to traverse the tree in postorder sequence.
	Pre   tree is being destroyed
	Post  all data have been deleted
	*/

template <class ItemType>
void  AvlTree<ItemType>::destroyTree(BinaryNode<ItemType>  *rootPtr)
{
	//	Statements 
	if (rootPtr != nullptr)
	{
		destroyTree( rootPtr->getLeftChildPtr() );
		destroyTree( rootPtr->getRightChildPtr() );
		delete rootPtr;
		rootPtr = nullptr;
	} // if 
}	//  destroyTree


	/*  ============================= AVL_Print =============================
	This function prints the AVL tree by calling a recursive inorder
	traversal. NOTE: THIS IS NOT AN APPLICATION ADT FUNCTION. IT IS
	USED ONLY FOR DEBUGGING PURPOSES.

	To correctly visualize the tree when turned sideways, the actual
	traversal is RNL.
	Pre	 Tree must be initialized. Null tree is OK.
	Level is BinaryNode level: root == 0
	Post Tree has been printed.
	*/
template <class ItemType>
void  AvlTree<ItemType>::AVL_Print() const
{
	/*  statements */
	_print(tree, 0);
}   /* AVL_PRINT */

	/*  ============================= _print =============================
	This function is not a part of the ADT. It is included to verify
	that the tree has been properly built by printing out the tree
	structure.
	*/

	/*  This function uses recursion to print the tree. At each level, the
	level number is printed along with the BinaryNode contents (an integer).
	Pre		root is the root of a tree or subtree
	level is the level of the tree: tree root is 0
	Post    Tree has been printed.
	*/
template <class ItemType>
void  AvlTree<ItemType>::_print(BinaryNode<ItemType> *rootPtr, int level) const
{
	/* Local Definitions */
	int i;

	/* Statements */
	if (rootPtr != nullptr)
	{
		_print(rootPtr->getRightChildPtr(), level + 1);

		cout << "bal " << setw(3) << rootPtr->getBalance()
			<< ": Level " << setw(3) << level;

		for (i = 0; i <= level; i++)
			cout << "....";
		cout << setw(3) << rootPtr->getItem();
		if (rootPtr->getBalance() == LH)
			cout << " (LH)\n";
		else if (rootPtr->getBalance() == RH)
			cout << " (RH)\n";
		else
			cout << " (EH)\n";

		_print(rootPtr->getLeftChildPtr(), level + 1);
	} /* if */

} /* AVL_Print */