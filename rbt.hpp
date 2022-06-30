//red-black tree implementation
#pragma once

#include <cassert>
#include <stdexcept>
#include <functional>
#include "ft_iterator.hpp"

#define NIL   NULL
#define LEFT  0
#define RIGHT 1
#define left  child[LEFT]
#define right child[RIGHT]

enum color_e { BLACK, RED, DBLACK};
typedef	enum color_e color_t;

template<typename T>
class RBnode;

template<typename T>
class RBtree;

#pragma region RB tree - Node
template<typename T>
class RBnode{
	public:
		typedef T value_type;

		RBnode(void) : parent(NULL), val(T()), color(RED){
			this->child[0] = NULL;
			this->child[1] = NULL;

			return;
		}

		RBnode(value_type iniz) : parent(NULL), val(iniz), color(RED){
			this->child[0] = NULL;
			this->child[1] = NULL;
			
			return;
		}

		RBnode(value_type iniz, color_t col) : parent(NULL), val(iniz), color(col){
			this->child[0] = NULL;
			this->child[1] = NULL;
			
			return;
		}

		RBnode &	operator=(RBnode const & asn){
			this->parent = asn.parent;
			this->child = asn->child;
			this->val = asn.getVal();
			this->color = asn.getColor();

			return (*this);
		}

		value_type &	getVal(void){
			return this->val;
		}

		RBnode<T>	*getChild(size_t n){
			if (n != 0 && n != 1)
				throw std::exception();
			return this->child[n];
		}

		color_t const &	getColor(void){
			return (this->color);
		}

	private:
		RBnode<T>	*parent;
		RBnode<T>	*child[2];
		value_type	val;
		color_t color;

		friend class RBtree<T>;
};
#pragma endregion

template<typename T>
class RBtree{
	public:
		RBtree(void) : root(NIL){
			return;
		}

		RBtree(RBnode<T> *iniz) : root(iniz){
			return;
		}

		//desturctor
		~RBtree(void){
			this->applyFn(this->getRoot(), deleteNode);
			return;
		}

		#pragma region RB tree Rotate
		static RBnode<T>	*RotateDirRoot(RBtree<T> *Tree, RBnode<T> *Parent, short dir){
			RBnode<T>	*Gran = Parent->parent;
			RBnode<T>	*Sib = Parent->child[1 - dir];
			RBnode<T>	*C;

			assert(Sib != NIL);
			
			C = Sib->child[dir];
			Parent->child[1 - dir] = C;
			if (C != NIL)
				C->parent = Parent;
			Sib->child[  dir] = Parent;
			Parent->parent = Sib;
			Sib->parent = Gran;
			if (Gran != NULL)
				Gran->child[Parent == Gran->right ? RIGHT : LEFT] = Sib;
			else
				Tree->root = Sib;
			return Sib;
		}

		RBnode<T>	*RotateDir(RBnode<T> *Parent, short dir){
			return RotateDirRoot(this, Parent, dir);
		}

		RBnode<T>	*RotateLeft(RBnode<T> *Parent){
			return RotateDir(Parent, LEFT);
		}

		RBnode<T>	*RotateRight(RBnode<T> *Parent){
			return RotateDir(Parent, RIGHT);
		}
		#pragma endregion

		#pragma region RB tree Insert
		static void	RBinsertRoot(RBtree<T> *Tree, RBnode<T> *New, RBnode<T> *Parent, short dir){
			
			if (Parent == NULL){
				New->color = ::BLACK;
				Tree->root = New;
				return;
			}
			
			RBnode<T>	*Gran;
			RBnode<T>	*Unc;

			New->color = RED;
			New->left  = NIL;
			New->right = NIL;
			New->parent = Parent;

			Parent->child[dir] = New;
			do{
				if (Parent->getColor() == BLACK)
					return;
				if ((Gran = Parent->parent) == NULL)
					return Tree->icase4(Parent);
				dir = childDir(Parent);
				Unc = Gran->child[1 - dir];
				if (Unc == NIL || Unc->color == BLACK)
					return Tree->icase56(New, Parent, Gran, dir);
				Parent->color = BLACK;
				Unc->color = BLACK;
				Gran->color = RED;
				New = Gran;
			} while ((Parent = New->parent) != NULL);

			return;
		}

		void	RBinsert(RBnode<T> *New, RBnode<T> *Parent, short dir){
			RBinsertRoot(this, New, Parent, dir);
			return;
		}
		#pragma endregion

		#pragma region RB tree Delete
		static void	RBdeleteRoot(RBtree<T>* Tree, RBnode<T>* N){
			RBnode<T>	*P = N->parent;  // -> parent node of N
			
			//case: N is root node and it's a 1 element tree
			if (N->getChild(LEFT) == NIL && N->getChild(RIGHT) == NIL && P == NULL)
			{
				delete N;
				N = NULL;
				Tree->root = NULL;
				return;
			}
			
			//case: N is tree or subtree root with 2 non-null children or it's 
			if (N->getChild(LEFT) != NIL && N->getChild(RIGHT) != NIL)
			{
				RBnode<T>	*swap;

				swap = findMax(N->child[LEFT]);
				N->val = swap->getVal();

				RBdeleteRoot(Tree, swap);

				return;
			}

			//find side of element to delete
			short	dir = childDir(N);

			//case: New has exactly one child
			if ((N->getChild(LEFT) != NIL || N->getChild(RIGHT) != NIL) && (N->getChild(LEFT) == NIL || N->getChild(RIGHT) == NIL))
			{
				RBnode<T>	*child(NULL);

				if (N->getChild(LEFT) != NIL)
					child = N->getChild(LEFT);
				else if (N->getChild(RIGHT) != NIL)
					child = N->getChild(RIGHT);

				//case: New or his only child is red(not both, but this case is impossible)
				if (child->color == ::RED || N->color == ::RED)
					child->color = ::BLACK;
				//case: both nodes are black
				// else						//not needed?
				// 	child->color = ::DBLACK;

				//change references to deleted node accordingly
				if (N->parent != NULL)
					N->parent->child[childDir(N)] = child;
				else
					Tree->root = child;
				child->parent = N->parent;
			
				//remove node from memory, and dangling pointer
				delete N;
				N = NULL;				

				return;
			}
			
			RBnode<T>	*S;  // -> sibling of N
			RBnode<T>	*C;  // -> close   nephew
			RBnode<T>	*D;  // -> distant nephew

			//remove node from memory, and dangling pointer
			P->child[dir] = NULL;
			delete N;
			N = NULL;

			do {
				if (N != NULL)
					dir = childDir(N);   // side of parent P on which node N is located

				S = P->child[!dir]; // sibling of N (has black height >= 1)
				D = S->child[!dir]; // distant nephew
				C = S->child[dir]; // close   nephew
				if (S->color == ::RED)
				{
					// S red && P+C+D black: D3
					RotateDirRoot(Tree,P,dir); // P may be the root
					P->color = RED;
					S->color = BLACK;
					
					S = C; // != NIL
					
					// now: P red && S black 
					D = S->child[1-dir]; // distant nephew
					if (D != NIL && D->color == ::RED)
						return RBtree<T>::dcase6(Tree, P, S, D, dir);      // D red && S black
					C = S->child[  dir]; // close   nephew
					if (C != NIL && C->color == ::RED)
						return RBtree<T>::dcase5(Tree, P, S, C, D, dir);      // C red && S+D black
					// Otherwise C+D considered black.
					// fall through to Case_D4
					
					// P red && S+C+D black: D4
					S->color = ::RED;
					P->color = ::BLACK;
					return; // deletion complete
				}                  // S red ===> P+C+D black
				// S is black:
				if (D != NIL && D->color == ::RED) // not considered black
					return RBtree<T>::dcase6(Tree, P, S, D, dir);  // D red && S black
				if (C != NIL && C->color == ::RED) // not considered black
					return RBtree<T>::dcase5(Tree, P, S, C, D, dir); // C red && S+D black
				// Here both nephews are == NIL (first iteration) or black (later).
				if (P->color == ::RED)
				{
					// P red && S+C+D black: D4
					S->color = ::RED;
					P->color = ::BLACK;
					return; // deletion complete -- P red && C+S+D black
				}
				// Case_D1 (P+C+S+D black): D1
				S->color = ::RED;
				N = P; // new current node (maybe the root)
				// iterate 1 black level
				//   (= 1 tree level) higher
			} while ((P = N->parent) != NULL);
			// end of the (do while)-loop

			//case D2:
			return;

			//do all other cases
			// RBnode<T>	*sib = New->parent->child[!dir];
			// if (sib != NIL && sib->getColor() == ::BLACK)
			// {
			// 	RBnode<T>	*clos = sib->getChild(dir);
			// 	if (clos != NIL && clos->getColor() == ::RED)
			// 	{
			// 		RotateDir(sib, !dir);
			// 		sib->color = ::RED;
			// 		clos->color = ::BLACK;
			// 		dist = sib;
			// 		sib = clos;
			// 	}
			// 	RBnode<T>	*dist = sib->getChild(!dir);

			// 	if (dist != NIL && dist->getColor() == ::RED)
			// 	{
			// 		RotateDirRoot(Tree, New->parent, dir);
			// 		sib->color = New->parent->color;
			// 		New->parent->color = BLACK;
			// 		dist->color = BLACK;
			// 		return;
			// 	}
			// }
			// (void)Tree;
		}

		void	RBdelete(RBnode<T>* New){
			return RBdeleteRoot(this, New);
		}
		#pragma endregion

		RBnode<T>	*find(RBnode<T> *root, T value){
			if (root == NULL)
				return NULL;
			if (value == root->getVal())
				return root;

			RBnode<T>	*res;

			res = find(root->child[0], value);
			if (res == NIL || res->getVal() != value)
				res = find(root->child[1], value);
			
			return res;
		}

		static RBnode<T>	*findNext(RBnode<T> *root){
			// if (root == NULL)
			// 	return NULL;
			// if (value == root->getVal())
			// 	return (root->child[1] * (root->child[1] != NULL)
			// 	+ root->parent * (!childDir(root)));

			// RBnode<T>	*res;

			// res = find(root->child[0], value);
			// if (res == NIL || res->getVal() != value)
			// 	res = find(root->child[1], value);
			
			if (!root)
				return NULL;
			if (root->child[RIGHT])
				return (findMin(root->child[RIGHT]));
			if (root->parent && childDir(root) == LEFT)
				return (root->parent);

			do
			{
				root = root->parent;
			} while (root && root->parent && childDir(root));

			if (root)
				return (root->parent);

			return NULL;
		}

		static RBnode<T>	*findPrev(RBnode<T> *root){
			if (!root)
				return NULL;
			if (root->child[LEFT])
				return (findMax(root->child[LEFT]));
			if (root->parent && childDir(root) == RIGHT)
				return (root->parent);

			do
			{
				root = root->parent;
			} while (root && root->parent && !childDir(root));

			if (root)
				return (root->parent);

			return NULL;
		}

		static RBnode<T>	*findMax(RBnode<T>	*subtree)
		{
			if (subtree == NULL)
				throw std::exception();
			if (subtree->child[RIGHT] == NIL)
				return subtree;
			
			return findMax(subtree->child[RIGHT]);
		}

		static RBnode<T>	*findMin(RBnode<T>	*subtree)
		{
			if (subtree == NULL)
				throw std::exception();
			if (subtree->child[LEFT] == NIL)
				return subtree;
			
			return findMin(subtree->child[LEFT]);
		}

		void	applyFn(RBnode<T> *root, void(*func)(RBnode<T> *val)){
			if (root == NULL)
				return;

			applyFn(root->child[0], func);
			applyFn(root->child[1], func);
			func(root);

			return;
		}

		RBnode<T>	*getRoot(void) const{
			return (this->root);
		}

		static inline short	childDir(RBnode<T> *New){
			if (New == New->parent->right)
				return RIGHT;
			else
				return LEFT;
		}

		static void	deleteNode(RBnode<T> *node){
			delete node;
			node = NULL;
			return;
		}

	private:
		RBnode<T>	*root;

		#pragma region Insert Cases
		static inline void	icase4(RBnode<T> *Parent){
			Parent->color = BLACK;
			return;
		}

		inline void	icase56(RBnode<T> *New, RBnode<T> *Parent, RBnode<T> *Gran, short dir){ //make static?
			if (New == Parent->child[1 - dir]){
				this->RotateDir(Parent, dir);
				New = Parent;
				Parent = Gran->child[dir];
			}
			this->RotateDir(Gran, 1 - dir);
			Parent->color = BLACK;
			Gran->color = RED;
			return;
		}
		#pragma endregion

		static inline void	dcase5(RBtree<T> *Tree, RBnode<T> *P, RBnode<T> *S, RBnode<T> *C, RBnode<T> *D, short dir){
			// C red && S+D black: D5
			RotateDirRoot(Tree, S, !dir); // S is never the root
			S->color = ::RED;
			C->color = ::BLACK;
			D = S;
			S = C;
			// now: D red && S black
			// fall through to Case_D6
			dcase6(Tree, P, S, D, dir);
			return;
		}

		static inline void	dcase6(RBtree<T> *Tree, RBnode<T> *P, RBnode<T> *S, RBnode<T> *D, short dir){
			// D red && S black: D6
			RotateDirRoot(Tree, P, dir); // P may be the root
			S->color = P->color;
			P->color = ::BLACK;
			D->color = ::BLACK;
			return; // deletion complete
		}

		friend class RBnode<T>;
};


