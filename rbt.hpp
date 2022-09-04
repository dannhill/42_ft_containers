//red-black tree implementation
#pragma once
#include "containers.hpp"
#include "ft_iterator.hpp"

#include <memory>

#include <cassert>
#include <stdexcept>
#include <functional>
#include "ft_type_traits.hpp"

#define NIL   NULL
#define LEFT  0
#define RIGHT 1
// #define left  child[LEFT]
// #define right child[RIGHT]

enum color_e { BLACK, RED, DBLACK};
typedef	enum color_e color_t;

// template<typename T, class Alloc = std::allocator<T> >
// class RBnode;

// template<typename T, class Alloc = std::allocator<T> >
// class RBtree;

#pragma region RB tree - Node
template<typename T, class Alloc>
class RBnode{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;

		RBnode(void) : parent(NULL), val(), color(RED){
			allocator_type	alloc = allocator_type();

			val = alloc.allocate(1);
			alloc.construct(val, value_type() );
			this->child[0] = NULL;
			this->child[1] = NULL;

			return;
		}

		RBnode(value_type iniz) : parent(NULL), val(), color(RED){
			allocator_type	alloc = allocator_type();

			val = alloc.allocate(1);
			alloc.construct(val, iniz);
			this->child[0] = NULL;
			this->child[1] = NULL;
			
			return;
		}

		RBnode(value_type iniz, color_t col) : parent(NULL), val(), color(col){
			allocator_type	alloc = allocator_type();

			val = alloc.allocate(1);
			alloc.construct(val, iniz);
			this->child[0] = NULL;
			this->child[1] = NULL;
			
			return;
		}

		~RBnode(void){
			defal.destroy(val);
			defal.deallocate(val, 1);
			return;
		}

		RBnode &	operator=(RBnode const & asn){
			this->parent = asn.parent;
			this->child = asn->child;
			this->val = asn.getVal();
			this->color = asn.getColor();

			return (*this);
		}

		value_type	*getVal(void){
			return this->val;
		}

		RBnode<T, Alloc>	*getChild(size_t n){
			if (n != 0 && n != 1)
				throw std::exception();
			return this->child[n];
		}

		color_t const &	getColor(void){
			return (this->color);
		}

	private:
		allocator_type	defal;
		RBnode<T, Alloc>	*parent;
		RBnode<T, Alloc>	*child[2];
		value_type	*val;
		color_t color;

		friend class RBtree<T>;
};
#pragma endregion

template<typename T, class Alloc>
class RBtree{
	public:
		typedef RBnode<T, Alloc> nodeType;
		
		RBtree(void) : root(NIL){
			return;
		}

		RBtree(RBnode<T, Alloc> *iniz) : root(iniz){
			return;
		}

		//desturctor
		~RBtree(void){
			this->clear();
			this->root = NULL;
			return;
		}

		#pragma region RB tree Rotate
		static RBnode<T, Alloc>	*RotateDirRoot(RBtree<T> *Tree, RBnode<T, Alloc> *Parent, short dir){
			RBnode<T, Alloc>	*Gran = Parent->parent;
			RBnode<T, Alloc>	*Sib = Parent->child[1 - dir];
			RBnode<T, Alloc>	*C;

			assert(Sib != NIL);
			
			C = Sib->child[dir];
			Parent->child[1 - dir] = C;
			if (C != NIL)
				C->parent = Parent;
			Sib->child[  dir] = Parent;
			Parent->parent = Sib;
			Sib->parent = Gran;
			if (Gran != NULL)
				Gran->child[Parent == Gran->child[RIGHT] ? RIGHT : LEFT] = Sib;
			else
				Tree->root = Sib;
			return Sib;
		}

		RBnode<T, Alloc>	*RotateDir(RBnode<T, Alloc> *Parent, short dir){
			return RotateDirRoot(this, Parent, dir);
		}

		RBnode<T, Alloc>	*RotateLeft(RBnode<T, Alloc> *Parent){
			return RotateDir(Parent, LEFT);
		}

		RBnode<T, Alloc>	*RotateRight(RBnode<T, Alloc> *Parent){
			return RotateDir(Parent, RIGHT);
		}
		#pragma endregion

		#pragma region RB tree Insert
		static void	RBinsertRoot(RBtree<T> *Tree, RBnode<T, Alloc> *New, RBnode<T, Alloc> *Parent, short dir){
			
			if (Parent == NULL){
				New->color = ::BLACK;
				Tree->root = New;
				return;
			}
			
			RBnode<T, Alloc>	*Gran;
			RBnode<T, Alloc>	*Unc;

			New->color = RED;
			New->child[LEFT] = NIL;
			New->child[RIGHT] = NIL;
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

		void	RBinsert(RBnode<T, Alloc> *New, RBnode<T, Alloc> *Parent, short dir){
			RBinsertRoot(this, New, Parent, dir);
			return;
		}
		#pragma endregion

		#pragma region RB tree Delete
		static void	RBdeleteRoot(RBtree<T>* Tree, RBnode<T, Alloc>* N){
			if (!N)
				return;
			
			RBnode<T, Alloc>	*P = N->parent;  // -> parent node of N
			
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
				RBnode<T, Alloc>	*swap;

				swap = findMax(N->child[LEFT]);
				*(N->val) = *(swap->getVal());

				RBdeleteRoot(Tree, swap);

				return;
			}

			//find side of element to delete
			short	dir;
			if (N->parent)
				dir = childDir(N);

			//case: New has exactly one child
			if ((N->getChild(LEFT) != NIL || N->getChild(RIGHT) != NIL) && (N->getChild(LEFT) == NIL || N->getChild(RIGHT) == NIL))
			{
				RBnode<T, Alloc>	*child(NULL);

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
			
			RBnode<T, Alloc>	*S;  // -> sibling of N
			RBnode<T, Alloc>	*C = NULL;  // -> close   nephew
			RBnode<T, Alloc>	*D = NULL;  // -> distant nephew

			//remove node from memory, and dangling pointer
			P->child[dir] = NULL;
			delete N;
			N = NULL;

			do {
				if (N != NULL)
					dir = childDir(N);   // side of parent P on which node N is located

				S = P->child[!dir]; // sibling of N (has black height >= 1)
				if (S)
				{
					D = S->child[!dir]; // distant nephew
					C = S->child[dir]; // close   nephew
				}
				if (S && S->color == ::RED)
				{
					// S red && P+C+D black: D3
					RotateDirRoot(Tree,P,dir); // P may be the root
					P->color = RED;
					S->color = BLACK;
					
					S = C; // != NIL
					
					// now: P red && S black 
					if (S)
						D = S->child[1-dir]; // distant nephew
					if (D != NIL && D->color == ::RED)
						return RBtree<T>::dcase6(Tree, P, S, D, dir);      // D red && S black
					if (S)
						C = S->child[  dir]; // close   nephew
					if (C != NIL && C->color == ::RED)
						return RBtree<T>::dcase5(Tree, P, S, C, D, dir);      // C red && S+D black
					// Otherwise C+D considered black.
					// fall through to Case_D4
					
					// P red && S+C+D black: D4
					if (S)
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
				if (S)
					S->color = ::RED;
				N = P; // new current node (maybe the root)
				// iterate 1 black level
				//   (= 1 tree level) higher
			} while ((P = N->parent) != NULL);
			// end of the (do while)-loop

			//case D2:
			return;
		}

		void	RBdelete(RBnode<T, Alloc>* New){
			return RBdeleteRoot(this, New);
		}
		#pragma endregion

		RBnode<T, Alloc>	*find(RBnode<T, Alloc> *root, T value){
			if (root == NULL)
				return NULL;
			if (value == *(root->getVal() ) )
				return root;

			RBnode<T, Alloc>	*res;

			res = find(root->child[0], value);
			if (res == NIL || *(res->getVal() ) != value)
				res = find(root->child[1], value);
			
			return res;
		}

		RBnode<T, Alloc>	*findCompare(RBnode<T, Alloc> *root, T value, bool (*less)(const T& x, const T& y)){
			if (root == NULL)
				return NULL;
			if (!(less(*(root->getVal() ), value) || less(value, *(root->getVal() ) ) ) )
				return root;
			else if (less(*(root->getVal() ), value) && root->getChild(RIGHT) )
				return findCompare(root->getChild(RIGHT), value, less);
			else
				return findCompare(root->getChild(LEFT), value, less);

			return NULL;
		}

		static RBnode<T, Alloc>	*findNext(RBnode<T, Alloc> *root){		
			if (!root)
				return NULL;
			if (root->child[RIGHT])
				return (findMin(root->child[RIGHT]) );
			if (root->parent && childDir(root) == LEFT)
				return (root->parent);

			do
			{
				root = root->parent;
			} while (root && root->parent && childDir(root) );

			if (root)
				return (root->parent);

			return NULL;
		}

		static RBnode<T, Alloc>	*findPrev(RBnode<T, Alloc> *root){
			if (!root)
				return NULL;
			if (root->child[LEFT])
				return (findMax(root->child[LEFT]) );
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

		static RBnode<T, Alloc>	*findMax(RBnode<T, Alloc>	*subtree)
		{
			if (subtree == NULL)
				return NULL;
			if (subtree->getChild(RIGHT) == NIL)
				return subtree;
			
			return findMax(subtree->getChild(RIGHT) );
		}

		static RBnode<T, Alloc>	*findMin(RBnode<T, Alloc>	*subtree)
		{
			if (subtree == NULL)
			{
				// std::cout << "despacito\n";
				// throw std::exception();
				return NULL;
			}
			if (subtree->child[LEFT] == NIL)
				return subtree;
			
			return findMin(subtree->child[LEFT]);
		}

		void	applyFn(RBnode<T, Alloc> *root, void(*func)(RBnode<T, Alloc> *val)){
			if (root == NULL)
				return;

			applyFn(root->child[0], func);
			applyFn(root->child[1], func);
			func(root);

			return;
		}

		RBnode<T, Alloc>	*getRoot(void) const{
			if (!this->root)
				return NULL;
			return (this->root);
		}

		static inline short	childDir(RBnode<T, Alloc> *New){
			if (New == New->parent->child[RIGHT])
				return RIGHT;
			else
				return LEFT;
		}

		static void	deleteNode(RBnode<T, Alloc> *node){
			delete node;
			node = NULL;
			return;
		}

		void	clear(void){
			this->applyFn(this->getRoot(), deleteNode);
			this->root = NULL;

			return;
		}

	private:
		RBnode<T, Alloc>	*root;

		#pragma region Insert Cases
		static inline void	icase4(RBnode<T, Alloc> *Parent){
			Parent->color = BLACK;
			return;
		}

		inline void	icase56(RBnode<T, Alloc> *New, RBnode<T, Alloc> *Parent, RBnode<T, Alloc> *Gran, short dir){ //make static?
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

		static inline void	dcase5(RBtree<T> *Tree, RBnode<T, Alloc> *P, RBnode<T, Alloc> *S, RBnode<T, Alloc> *C, RBnode<T, Alloc> *D, short dir){
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

		static inline void	dcase6(RBtree<T> *Tree, RBnode<T, Alloc> *P, RBnode<T, Alloc> *S, RBnode<T, Alloc> *D, short dir){
			// D red && S black: D6
			RotateDirRoot(Tree, P, dir); // P may be the root
			S->color = P->color;
			P->color = ::BLACK;
			D->color = ::BLACK;
			return; // deletion complete
		}

		friend class RBnode<T, Alloc>;
};


