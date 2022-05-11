//red-black tree implementation
#pragma once

#include <cassert>

#define NIL   NULL
#define LEFT  0
#define RIGHT 1
#define left  child[LEFT]
#define right child[RIGHT]

enum color_e { BLACK, RED };
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

		RBnode(void) : val(T()), color(RED){
			return;
		}

		RBnode(value_type iniz) : val(iniz), color(RED){
			return;
		}

		RBnode(value_type iniz, color_t col) : val(iniz), color(col){
			return;
		}

		value_type &	getVal(void){
			return this->val;
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

		//desturctor
		// ~RBtree(void){
		// 	this->clear();
		// 	return;
		// }

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
			RBnode<T>	*Gran;
			RBnode<T>	*Unc;

			New->color = RED;
			New->left  = NIL;
			New->right = NIL;
			New->parent = Parent;
			if (Parent == NULL){
				Tree->root = New;
				return;
			}
			Parent->child[dir] = New;
			do{
				if (Parent->color == BLACK)
					return;
				if ((Gran = Parent->parent) == NULL)
					return Tree->case4(Parent);
				dir = childDir(Parent);
				Unc = Gran->child[1 - dir];
				if (Unc == NIL || Unc->color == BLACK)
					return Tree->case56(New, Parent, Gran, dir);
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

		RBnode<T> &	getRoot(void) const{
			return *(this->root);
		}

		static inline short	childDir(RBnode<T> *New){
			if (New == New->parent->right)
				return RIGHT;
			else
				return LEFT;
		}

	private:
		RBnode<T>	*root;

		void	case4(RBnode<T> *Parent){
			Parent->color = BLACK;
			return;
		}

		void	case56(RBnode<T> *New, RBnode<T> *Parent, RBnode<T> *Gran, short dir){
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

		friend class RBnode<T>;
};


