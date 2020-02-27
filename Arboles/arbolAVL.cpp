#include <iostream>
#include<stdio.h>
#include <stdlib.h>
using namespace std;
template <class Comparable>

class arbolAVL
{
private:

	struct AvlNode
	{
	Comparable element;
	AvlNode *left;
	AvlNode *right;
	int
	height;
	AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
		: element{ ele }, left{ lt }, right{ rt }, height{ h } { }
	AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
		: element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
	};
	AvlNode *root;

	AvlNode * findMin( AvlNode *t ) const
	{
	if( t == nullptr )
		return nullptr;
	if( t->left == nullptr )
		return t;
	return findMin( t->left );
	}
	AvlNode * findMax( AvlNode *t ) const
	{
	if( t != nullptr )
		while( t->right != nullptr )
			t = t->right;
	return t;
	}
public:
	FILE *fp;
	arbolAVL(){root = nullptr;}
	~arbolAVL()
	{
		makeEmpty( );
	}
	void makeEmpty(){
		makeEmpty(root);
	}
	void makeEmpty( AvlNode *&t ){
		{
		if( t != nullptr )
		{
			makeEmpty( t->left );
			makeEmpty( t->right );
			delete t;
		}
		t = nullptr;
	}
	}
	int height( AvlNode *t ) const
	{
		return t == nullptr ? -1 : t->height;
	}
	/**
* Internal method to insert into a subtree.
* x is the item to insert.
* t is the node that roots the subtree.
* Set the new root of the subtree.
*/
	void insert(const Comparable & v){
		insert(v,root);
	}
	void insert( const Comparable & x, AvlNode * & t )
	{
		if( t == nullptr )
			t = new AvlNode{ x, nullptr, nullptr };
		else if( x < t->element )
			insert( x, t->left );
		else if( t->element < x )
			insert( x, t->right );
		balance( t );
	}
	static const int ALLOWED_IMBALANCE = 1;
	void rotateWithLeftChild( AvlNode * & k2 )
	{
		AvlNode *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
		k1->height = max( height( k1->left ), k2->height ) + 1;
		k2 = k1;
	}
	void rotateWithRightChild( AvlNode * & k2 )
	{
		AvlNode *k1 = k2->right;
		k2->right = k1->left;
		k1->left = k2;
		k2->height = max( height( k2->right ), height( k2->left ) ) + 1;
		k1->height = max( height( k1->right ), k2->height ) + 1;
		k2 = k1;
	}
	/**
	* Double rotate binary tree node: first left child
	* with its right child; then node k3 with new left child.
	* For AVL trees, this is a double rotation for case 2.
	* Update heights, then set new root.
	*/
	void doubleWithLeftChild( AvlNode * & k3 )
	{
		rotateWithRightChild( k3->left );
		rotateWithLeftChild( k3 );
	}
	void doubleWithRightChild( AvlNode * & k3 )
	{
		rotateWithLeftChild( k3->right );
		rotateWithRightChild( k3 );
		
	}
	// Assume t is balanced or within one of being balanced
	void balance( AvlNode * & t )
	{
		if( t == nullptr )
			return;
		if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
			if( height( t->left->left ) >= height( t->left->right ) )
				rotateWithLeftChild( t );
			else
				doubleWithLeftChild( t );
		else
			if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
				if( height( t->right->right ) >= height( t->right->left ) )
					rotateWithRightChild( t );
				else
					doubleWithRightChild( t );
		t->height = max( height( t->left ), height( t->right ) ) + 1;
	}
	/**
	* Rotate binary tree node with left child.
	* For AVL trees, this is a single rotation for case 1.
	* Update heights, then set new root.
	*/
	
	/**
	* Internal method to remove from a subtree.
	* x is the item to remove.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void remove( const Comparable & x, AvlNode * & t )
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
			AvlNode *oldNode = t;
			t = ( t->left != nullptr ) ? t->left : t->right;
			delete oldNode;
		}
		balance( t );
	}

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
	void printTree( AvlNode *t, ostream & out ) const
	{
		if( t != nullptr )
		{
			printTree( t->left, out );
			out << t->element << endl;
			printTree( t->right, out );
		}
	}

	void graficar(){
    if (root==nullptr){
        puts("el arbol esta vacio ");
        return;
    }
    fp = fopen("avl.dot","w");
    fprintf(fp,"digraph avl{\n");
    fprintf(fp,"graph[overlap=true, fontsize =1];\n");
    fprintf(fp,"subgraph Info{\n");
    fprintf(fp,"node [shape=box];\n");
    fprintf(fp,"nodoInfo[label=\"Dato--> :%d\\n\"];\n",root->element);
    fprintf(fp,"}\n");
    fprintf(fp,"subgraph arbol{\n");
    recorridoImpresion(root,fp);
    fprintf(fp,"}\n");
    fprintf(fp,"}");
    fclose(fp);
    system("dot -Tpng avl.dot -o avl.png");
}

void recorridoImpresion(AvlNode *cuerpo,FILE *fp){
    if(cuerpo->left!=nullptr)
    {
        fprintf(fp,"nodo%p[label=\"Dato-->:%d\"];\n",&(*cuerpo),cuerpo->element);
        fprintf(fp,"nodo%p[label=\"Dato-->:%d\"];\n",&(*(cuerpo->left)),cuerpo->left->element);
        fprintf(fp,"nodo%p->nodo%p[label=\"I\"];\n",&(*cuerpo),&(*(cuerpo->left)));

        recorridoImpresion(cuerpo->left,fp);
    }
    if(cuerpo->right!=nullptr)
    {
        fprintf(fp,"nodo%p[label=\"Dato-->:%d\"];\n",&(*cuerpo),cuerpo->element);
        fprintf(fp,"nodo%p[label=\"Dato-->:%d\"];\n",&(*(cuerpo->right)),cuerpo->right->element);
        fprintf(fp,"nodo%p->nodo%p[label=\"I\"];\n",&(*cuerpo),&(*(cuerpo->right)));

        recorridoImpresion(cuerpo->right,fp);
    }
}

	
};

int main(int argc, char const *argv[])
{
	arbolAVL<int> a;
	a.insert(8);
	a.insert(4);
	a.insert(6);
	a.insert(2);
	a.insert(5);
	a.insert(1);
	a.insert(9);
	a.insert(10);
	a.insert(20);
	a.insert(15);
	a.insert(14);
	a.makeEmpty();
	a.printTree();
	return 0;
}