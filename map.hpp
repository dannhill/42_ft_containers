
#pragma once
#include "containers.hpp"
#include <cstdio> // library used only to define "size_t"
#include <iostream> // library used only to debug printing
#include <stdexcept>
#include <string>
#include "rbt.hpp"
#include "ft_type_traits.hpp"
#include "ft_utility.hpp"

namespace ft
{

template < class Key, class T, class Compare,
	class Alloc >
class map{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type,mapped_type> value_type;
		typedef Compare key_compare;
		class	value_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::iterator<value_type, RBtree<value_type, allocator_type> > iterator;
		typedef typename ft::const_iterator<value_type, RBtree<value_type, allocator_type> > const_iterator;
		typedef typename ft::reverse_iterator<value_type, RBtree<value_type, allocator_type> > reverse_iterator;
		typedef typename ft::const_reverse_iterator<value_type, RBtree<value_type, allocator_type> > const_reverse_iterator;
		typedef typename ft::iterator<value_type, RBtree<value_type, allocator_type> >::difference_type difference_type;
		typedef size_t size_type;
		//optional
		typedef RBnode<value_type, allocator_type> nodeType;

		#pragma region (constructor)
		explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _size(0){
			(void)comp;
			(void)alloc;

			tree = new RBtree<value_type, allocator_type>;

			return;
		}

		template <class InputIterator>
  		map (InputIterator first, InputIterator last,
       		const key_compare& comp = key_compare(),
       		const allocator_type& alloc = allocator_type()) : _size(0){
			
			(void)comp;
			(void)alloc;

			tree = new RBtree<value_type, allocator_type>;

			this->insert(first, last);

			// for(; first != last; first++, this->_size++)
			// {
				// this->tree->RBinsert(new nodeType(*first), //create new node with same element of first
				// this->tree->findMax(this->tree->getRoot() ), //find the current max element in the new tree
				// RIGHT ); //set the new node as the right child
			// }
		
			return;
		}

		map (const map& x) : _size(x._size){
			const_iterator	ite(x.begin());
			this->tree = new RBtree<value_type, allocator_type>;

			for(; ite != x.end(); ite++)
			{ //curly brackets for clearer code
				this->tree->RBinsert(new nodeType(*ite), //create new node with same element of first
					this->tree->findMax(this->tree->getRoot()), //find the current max element in the new tree
					RIGHT); //set the new node as the right child
			}

			return;
		}
		#pragma endregion

		#pragma region (destructor)
		~map(void){
			delete tree;
		}
		#pragma endregion

		#pragma region operator=
		map& operator= (const map& x){
			// this->_size = x.size();

			// const_iterator	ite(x.begin());

			// for(; ite != x.end(); ite++)
			// { //curly brackets for clearer code
			// 	this->tree->RBinsert(new nodeType(*ite), //create new node with same element of first
			// 		this->tree->findMax(this->tree->getRoot()), //find the current max element in the new tree
			// 		RIGHT); //set the new node as the right child
			// }

			this->clear();

			this->tree->clear();

			this->insert(x.begin(), x.end());

			return (*this);
		}
		#pragma endregion

		#pragma region Iterators
		iterator begin(){
			if (this->size() == 0)
				return this->end();
			return (iterator(tree->findMin(tree->getRoot() ) ) );
		}

		const_iterator begin() const{
			if (this->size() == 0)
				return this->end();
			return (const_iterator(tree->findMin(tree->getRoot() ) ) );
		}

		iterator end(){
			if (this->size() == 0)
				return iterator(NULL, 1);
			return (iterator(tree->findMax(tree->getRoot() ), 1 ) );
		}

		const_iterator	end() const{
			if (this->size() == 0)
				return const_iterator(NULL, 1);
			return (const_iterator(tree->findMax(tree->getRoot() ), 1) );
		}

		reverse_iterator rbegin(){
			if (this->size() == 0)
				return this->rend();
			return (reverse_iterator(tree->findMax(tree->getRoot() ) ) );
		}

		const_reverse_iterator rbegin() const{
			if (this->size() == 0)
				return this->rend();
			return (const_reverse_iterator(tree->findMax(tree->getRoot() ) ) );
		}

		reverse_iterator rend(){
			if (this->size() == 0)
				return reverse_iterator(NULL, 2);
			return (reverse_iterator(tree->findMin(tree->getRoot() ), 2) );
		}

		const_reverse_iterator rend() const{
			if (this->size() == 0)
				return const_reverse_iterator(NULL, 2);
			return (const_reverse_iterator(tree->findMin(tree->getRoot() ), 2) );
		}
		#pragma endregion

		#pragma region Capacity
		bool empty() const{
			return (this->size() == 0);
		}

		size_type size() const{
			return (this->_size);
		}

		size_type max_size() const{
			return (this->_max_size);
		}
		#pragma endregion

		#pragma region Element access
		mapped_type& operator[] (const key_type& k){
			return (this->insert(ft::make_pair(k, mapped_type() ) ).first->second);
		}
		#pragma endregion

		#pragma region Modifiers
		pair<iterator, bool> insert (const value_type& val){//doesn't work with the const
			nodeType	*node;

			node = this->findCompare(this->tree->getRoot(), //find element
				val, // of this value
				false); //do not insert
			if (node != NULL)
				return ft::make_pair(iterator(node), false);
			else
			{
				if (this->size() <= 0)
					this->tree->clear();
				
				iterator	ite(this->findCompare(this->tree->getRoot(), val, true) );
				return ft::make_pair(ite, true);
			}
		}

		iterator insert (iterator position, const value_type& val){
			value_compare	comp( (key_compare()) );

			if ( (position != iterator() //check if position doesn't point to NULL
				&& position.getPoint().getEnd() != 1) //check if position is not this->end()
				&& ( position.getPoint().getEnd() == 2 || comp(*position, val) ) //if it's before begin (useless, cause it's only the case of reverse iterators)
				&& ( (position + 1).getPoint().getEnd() == 1 || comp(val, *(position + 1) ) ) //if next is after last (AKA: this->end() )
				&& comp(*position, val) )//follows order 
			{
				nodeType	*node = new nodeType(val);

				if (this->size() <= 0)
					this->tree->clear();
				
				nodeType	*curr = position.getPoint().getNode();
				nodeType	*prev = curr;
				for (; curr != NULL && comp( *(curr->getVal() ), val); curr = this->tree->findNext(curr) )
					prev = curr;

				if (curr && curr->getVal()->first == val.first)
					return iterator(curr);

				this->tree->RBinsert(node, //attach newly created node
				prev->getChild(RIGHT) ? curr : prev, //this position is father
				prev->getChild(RIGHT) ? LEFT : RIGHT); // put it as the right child

				this->_size++;

				return iterator(node); //return iterator of the newly attached node
			}
			else
				return this->insert(val).first;
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last){
			iterator	iend(this->end() );
			iterator	hint(iend);

			if (this->size() <= 0 && first != last)
					this->tree->clear();

			for(; first != last; first++)
			{
				if (hint == iend)
					hint = this->insert(*first).first;
				else
					hint = this->insert(hint, *first);
			}

			return;
		}

		void erase (iterator position){
			nodeType	*toDel;
			if (position.getPoint().getNode() == NULL)
				return;
			else if ( (toDel = this->findCompare(this->tree->getRoot(), *position, false) ) == NULL)
				return;
			else
				this->tree->RBdelete(toDel);

			this->_size--;

			return;
		}

		size_type erase (const key_type& k){
			iterator	toDel(this->find(k) ); // find node by key

			if (toDel == this->end() ) // if not found, return
				return 0;
			this->tree->RBdelete(toDel.getPoint().getNode() ); //delete element
			this->_size--; // decrease map size
			return 1; // return number of deleted elements
		}

		void erase (iterator first, iterator last){
			for(nodeType *index; //static_cast<value_type *>(first.getPoint()) && 
				//first.getPoint().getNode() && 
				first != last;
				this->_size--)
			{
				index = first.getPoint().getNode();
				first++;
				this->tree->RBdelete(index);
			}

			// if (last.getPoint().getEnd() == 1)
			// {
			// 	std::cout << "hello\n";
			// 	this->erase(--last);
			// }

			return;
		}

		void swap (map& x){
			RBtree<value_type, allocator_type>	*temp;
			size_type			tsize;

			temp = x.tree;
			tsize = x._size;

			x.tree = this->tree;
			x._size = this->_size;

			this->tree = temp;
			this->_size = tsize;

			return;
		}

		void clear(){
			this->tree->clear();

			this->tree->RBinsert(new nodeType(ft::pair<const key_type, mapped_type>(key_type(), mapped_type() ) ),
			this->tree->getRoot(), RIGHT);

			//not sure if this works

			this->_size = 0;
			return;
		}
		#pragma endregion

		#pragma region Observers
		key_compare key_comp() const{
			return key_compare();
		}

		value_compare value_comp() const{
			return value_compare(key_compare() );
		}
		#pragma endregion

		#pragma region Operations
		iterator find (const key_type& k){	
			nodeType	*node;

			node = this->findCompare(this->tree->getRoot(), // tree root
			value_type(k, mapped_type() ) ); //key of element to find

			if (!node)
				return (this->end() );
			else
				return iterator(node);
		}

		const_iterator find (const key_type& k) const{	
			nodeType	*node;

			node = this->findCompare(this->tree->getRoot(), // tree root
			value_type(k, mapped_type() ) ); //key of element to find

			if (!node)
				return (this->end() );
			else
				return const_iterator(node);
		}

		size_type count (const key_type& k) const{
			return static_cast<size_type>(this->find(k) != this->end() );
		}

		iterator lower_bound (const key_type& k){
			return iterator(this->findCompare(this->tree->getRoot(),
				value_type(k, mapped_type() ),
				2) ); //lower_bound mode: returns node >= k
		}

		const_iterator lower_bound (const key_type& k) const{
			return const_iterator(this->findCompare(this->tree->getRoot(),
				value_type(k, mapped_type() ),
				2) ); //lower_bound mode: returns node >= k
		}

		iterator upper_bound (const key_type& k){
			return iterator(this->findCompare(this->tree->getRoot(),
				value_type(k, mapped_type() ),
				3) ); //upper_bound mode: returns node > k
		}

		const_iterator upper_bound (const key_type& k) const{
			return const_iterator(this->findCompare(this->tree->getRoot(),
				value_type(k, mapped_type() ),
				3) ); //upper_bound mode: returns node > k
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const{
			const_iterator	res = lower_bound(k);
			const_iterator	res2 = upper_bound(k);

			return ft::make_pair(res, res2);
		}

		pair<iterator,iterator>             equal_range (const key_type& k){
			iterator res = lower_bound(k);
			iterator res2 = upper_bound(k);

			return ft::make_pair(res, res2);
		}
		#pragma endregion

		#pragma region Allocator
		allocator_type	get_allocator(void) const{
			return allocator_type();
		}
		#pragma endregion

	public: //must change to private(or protected)
		RBtree<value_type, allocator_type>	*tree;

		size_type			_size;
		static const size_type	_max_size;

		// don't know if this should be declared const, tests need to be made
		nodeType	*findCompare(nodeType *root, value_type value, short insert = 0){
			value_compare	comp( (key_compare()) );

			if (root && !(comp(*(root->getVal() ), value) || comp(value, *(root->getVal() ) ) )
				&& insert != 3)
				return root;
			else if (root && comp(*(root->getVal() ), value) && root->getChild(RIGHT) )
				return findCompare(root->getChild(RIGHT), value, insert);
			else if (root && comp(value, *(root->getVal() ) ) && root->getChild(LEFT) )
				return findCompare(root->getChild(LEFT), value, insert);
			else if (insert == 1)
			{
				nodeType	*node = new nodeType(value);

				if (this->size() <= 0)
					this->tree->clear();

				tree->RBinsert(node, root, root ? comp(*(root->getVal() ), value) : RIGHT ); //insert new node on the right direction
				
				this->_size++; //increase the size of the map by 1
				
				return node;
			}
			else if (insert >= 2)
			{
				if (comp(value, *(root->getVal())))
					return root;
					
				return (tree->findNext(root));
				//else
				// return root;
			}
			else
				return NULL;
		}

		nodeType	*findCompare(nodeType *root, value_type value, short insert = 0) const{
			value_compare	comp( (key_compare()) );

			if (root && !(comp(*(root->getVal() ), value) || comp(value, *(root->getVal() ) ) )
				&& insert != 3)
				return root;
			else if (root && comp(*(root->getVal() ), value) && root->getChild(RIGHT) )
				return findCompare(root->getChild(RIGHT), value, insert);
			else if (root && comp(value, *(root->getVal() ) ) && root->getChild(LEFT) )
				return findCompare(root->getChild(LEFT), value, insert);
			else if (insert == 1)
			{
				nodeType	*node = NULL;//new nodeType(value);

				// tree->RBinsert(node, root, root ? comp(*(root->getVal() ), value) : RIGHT ); //insert new node on the right direction
				
				// this->_size++; //increase the size of the map by 1
				
				return node;
			}
			else if (insert >= 2)
			{
				if (comp(value, *(root->getVal())))
					return root;
					
				return (tree->findNext(root));
				//else
				// return root;
			}
			else
				return NULL;
		}

		template <class K, class U, class Cmp, class Al>
		friend bool operator==(const map<K,U,Cmp,Al>& lhs, const map<K,U,Cmp,Al>& rhs);

		template <class K, class U, class Cmp, class Al>
		friend bool operator!=(const map<K,U,Cmp,Al>& lhs, const map<K,U,Cmp,Al>& rhs);

		template <class K, class U, class Cmp, class Al>
		friend bool operator>(const map<K,U,Cmp,Al>& lhs, const map<K,U,Cmp,Al>& rhs);

		template <class K, class U, class Cmp, class Al>
		friend bool operator<(const map<K,U,Cmp,Al>& lhs, const map<K,U,Cmp,Al>& rhs);

		template <class K, class U, class Cmp, class Al>
		friend bool operator>=(const map<K,U,Cmp,Al>& lhs, const map<K,U,Cmp,Al>& rhs);

		template <class K, class U, class Cmp, class Al>
		friend bool operator<=(const map<K,U,Cmp,Al>& lhs, const map<K,U,Cmp,Al>& rhs);

};

	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y){
		return x.swap(y);
	}

template <class Key, class T, class Compare, class Alloc>
class map<Key,T,Compare,Alloc>::value_compare
{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
	friend class map;
	protected:
		Compare comp;
		value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
		public:
		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;
		
		bool operator() (const value_type& x, const value_type& y) const //remove const qualifier?
		{
			return comp(x.first, y.first);
		}

		template <class K, class U, class Cmp, class Al>
		friend bool operator==(const map<K,U,Cmp,Al>& lhs, const map<K,U,Cmp,Al>& rhs);

		template <class K, class U, class Cmp, class Al>
		friend bool operator<(const map<K,U,Cmp,Al>& lhs, const map<K,U,Cmp,Al>& rhs);
};

template < class Key, class T, class Compare, class Alloc>
const typename map<Key, T, Compare, Alloc>::size_type	map<Key, T, Compare, Alloc>::_max_size(230584300921369395);

#pragma region non-member functions
template <class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs){
	typename ft::map<Key,T,Compare,Alloc>::value_compare cmp( (Compare() ) );

	size_t sz(lhs.size());
	if (sz != rhs.size())
		return false;
	
	typename ft::map<Key,T,Compare,Alloc>::const_iterator lbegin = lhs.begin();
	typename ft::map<Key,T,Compare,Alloc>::const_iterator rbegin = rhs.begin();
	for (size_t i(0); i < sz; i++)
	{
		if (cmp(*lbegin, *rbegin) || cmp(*rbegin, *lbegin) )
			return false;
		lbegin++;
		rbegin++;
	}

	return true;
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs){
	return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs){
	size_t	sz = lhs.size() < rhs.size() ? lhs.size() : rhs.size();
	// typename ft::map<Key,T,Compare,Alloc>::value_compare cmp( (Compare() ) );
	Compare cmp;
	std::less<T> cmp1;

	typename ft::map<Key,T,Compare,Alloc>::const_iterator lbegin = lhs.begin();
	typename ft::map<Key,T,Compare,Alloc>::const_iterator rbegin = rhs.begin();
	for (size_t i(0); i < sz; i++)
	{
		if (cmp((*lbegin).first, (*rbegin).first) )
			return true;
		else if (cmp((*rbegin).first, (*lbegin).first) )
			return false;
		else if (cmp1((*lbegin).second, (*rbegin).second) )
			return true;
		else if (cmp1((*rbegin).second, (*lbegin).second) )
			return false;
		lbegin++;
		rbegin++;
	}

	return lhs.size() < rhs.size() ? true : false;
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs){
	return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs){
	return (rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs){
	return !(lhs < rhs);
}
#pragma endregion

}