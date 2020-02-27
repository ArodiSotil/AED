#include<iostream>

using namespace std;


template <typename Comparable>
class BinarySearchTree
{
private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;
		BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
			: element{ theElement }, left{ lt }, right{ rt } { }
		BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt ):element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
	};
public:
	BinarySearchTree( ){
		root = nullptr;
	}
	/**
	* Copy constructor
	*/
	BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
	{
		root = clone( rhs.root );
	}
	BinarySearchTree( BinarySearchTree && rhs );
	/**
	* Destructor for the tree
	*/
	~BinarySearchTree( )
	{
		makeEmpty( );
	}

		/**
		* Internal method to make subtree empty.
		*/
	
	const Comparable & findMin( ) const;
	const Comparable & findMax( ) const;
	bool contains( const Comparable & x ) const;
	bool isEmpty( ) const{
		return root==nullptr;
	}
	void printTree( ostream & out = cout ) const
	{
		if( isEmpty( ) )
			out << "Empty tree" << endl;
		else
			printTree( root, out );
	}
	void makeEmpty( ){
		makeEmpty(root);
	}
	
	void insert( const Comparable & x );
	void insert( Comparable && x );
	void remove( const Comparable & x );
	
	BinarySearchTree & operator=( const BinarySearchTree & rhs );
	BinarySearchTree & operator=( BinarySearchTree && rhs );


private:
	

	BinaryNode *root;
	void insert( const Comparable & x, BinaryNode * & t );
	void insert( Comparable && x, BinaryNode * & t );
	void remove( const Comparable & x, BinaryNode * & t );
	BinaryNode * findMin( BinaryNode *t ) const
	{
	if( t == nullptr )
		return nullptr;
	if( t->left == nullptr )
		return t;
	return findMin( t->left );
	}
	BinaryNode * findMax( BinaryNode *t ) const
	{
	if( t != nullptr )
		while( t->right != nullptr )
			t = t->right;
	return t;
	}
	bool contains( const Comparable & x, BinaryNode *t ) const;
	void makeEmpty( BinaryNode *&t );
	void printTree( BinaryNode *t, ostream & out ) const
	{
		if( t != nullptr )
		{
			printTree( t->left, out );
			out << t->element << endl;
			printTree( t->right, out );
		}
	}
	BinaryNode * clone( BinaryNode *t ) const
	{
		if( t == nullptr )
			return nullptr;
		else
			return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
	}
};
template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty( BinaryNode * & t )
	{
		if( t != nullptr )
		{
			makeEmpty( t->left );
			makeEmpty( t->right );
			delete t;
		}
		t = nullptr;
	}
/**
* Returns true if x is found in the tree.
*/
template <typename Comparable>
bool BinarySearchTree<Comparable>::contains( const Comparable & x ) const
{
	return contains( x, root );
}
/**
* Internal method to test if an item is in a subtree.
* x is item to search for.
* t is the node that roots the subtree.
*/
template <typename Comparable>
bool BinarySearchTree<Comparable>::contains( const Comparable & x, BinaryNode *t ) const
{
	if( t == nullptr )
		return false;
	else if( x < t->element )
		return contains( x, t->left );
	else if( t->element < x )
		return contains( x, t->right );
	else
		return true;
// Match
}
/**
* Insert x into the tree; duplicates are ignored.
*/
template <typename Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x )
{
	insert( x, root );
}
template <typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable &&x )
{
	insert( x, root );
}

/**
* Internal method to insert into a subtree.
* x is the item to insert.
* t is the node that roots the subtree.
* Set the new root of the subtree.
*/
template <typename Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x, BinaryNode * & t )
{
	if( t == nullptr )
		t = new BinaryNode{ x, nullptr, nullptr };
	else if( x < t->element )
		insert( x, t->left );
	else if( t->element < x )
		insert( x, t->right );
	else
	; // Duplicate; do nothing
}
/**
* Internal method to insert into a subtree.
* x is the item to insert by moving.
* t is the node that roots the subtree.
* Set the new root of the subtree.
*/
template <typename Comparable>
void BinarySearchTree<Comparable>::insert( Comparable && x, BinaryNode * & t )
{
	if( t == nullptr )
		t = new BinaryNode{ std::move( x ), nullptr, nullptr };
	else if( x < t->element )
		insert( std::move( x ), t->left );
	else if( t->element < x )
		insert( std::move( x ), t->right );
	else
; // Duplicate; do nothing
}
/**
* Remove x from the tree. Nothing is done if x is not found.
*/
template <typename Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x )
{
	remove( x, root );
}

/**
* Internal method to remove from a subtree.
* x is the item to remove.
* t is the node that roots the subtree.
* Set the new root of the subtree.
*/
template <typename Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x, BinaryNode * & t )
{
	if( t == nullptr )
		return;
	// Item not found; do nothing
	if( x < t->element )
		remove( x, t->left );
	else if( t->element < x )
		remove( x, t->right );
	else if( t->left != nullptr && t->right != nullptr ) // Two children
	{
		t->element = findMin( t->right )->element;
		remove( t->element, t->right );
	}
	else
	{
		BinaryNode *oldNode = t;
		t = ( t->left != nullptr ) ? t->left : t->right;
		delete oldNode;
	}
}


int main(int argc, char const *argv[])
{
	/* code */
	BinarySearchTree<int> a;
	a.insert(5);
	a.insert(4);
	a.insert(6);
	a.insert(2);
	a.insert(8);
	a.insert(1);
	a.printTree();
	return 0;
}