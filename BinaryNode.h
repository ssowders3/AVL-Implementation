#ifndef _BINARY_NODE
#define _BINARY_NODE

template<class ItemType>
class BinaryNode
{
private:
	int					  balance;		  // Even, left-high, or right-high	
	ItemType              item;           // Data portion
	BinaryNode<ItemType>* leftChildPtr;   // Pointer to left child
	BinaryNode<ItemType>* rightChildPtr;  // Pointer to right child

public:
	BinaryNode() : leftChildPtr(nullptr), rightChildPtr(nullptr) {} 
	BinaryNode(const ItemType& anItem) : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr) {}
	BinaryNode(const ItemType& anItem, BinaryNode<ItemType>* leftPtr, BinaryNode<ItemType>* rightPtr) : item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr) {}

																										 
	BinaryNode(const BinaryNode<ItemType> & right) : leftChildPtr(nullptr), rightChildPtr(nullptr) { *this = right; }

	// add assignment operator
	const BinaryNode<ItemType> &operator = (const BinaryNode<ItemType> & right);

	void setItem(const ItemType& anItem) { item = anItem; }
	ItemType getItem() const { return item; }

	bool isLeaf() const { return (leftChildPtr == nullptr && rightChildPtr == nullptr ? true : false); }

	int getBalance() { return balance; }
	BinaryNode<ItemType>* getLeftChildPtr() const { return leftChildPtr; }
	BinaryNode<ItemType>* getRightChildPtr() const { return rightChildPtr; }

	void setBalance(const int& newBalance)				  { balance = newBalance;	  }
	void setLeftChildPtr(BinaryNode<ItemType>* leftPtr)   { leftChildPtr = leftPtr;   }
	void setRightChildPtr(BinaryNode<ItemType>* rightPtr) { rightChildPtr = rightPtr; }
}; // end BinaryNode

   // Implementation

template<class ItemType>
const BinaryNode<ItemType> & BinaryNode<ItemType>::operator = (const BinaryNode<ItemType> & right)
{
	if (this == &right)
		return *this;

	item = right.item;
	leftChildPtr = right.leftChildPtr;
	rightChildPtr = right.rightChildPtr;

	return *this;
}

#endif