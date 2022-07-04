
#pragma once
#include <memory>
#include <cstdio> // library used only to define "size_t"
#include <iostream> // library used only to debug printing
#include <stdexcept>
#include <string>
#include "ft_iterator.hpp"
#include "rbt.hpp"
#include "ft_type_traits.hpp"
#include "ft_utility.hpp"

namespace ft
{



template < class Key, class T, class Compare = std::less<Key>,
	class Alloc = std::allocator<std::pair<const Key,T> > >
class map{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type,mapped_type> value_type;
		typedef Compare key_compare;
		class	value_compare;
		typedef std::allocator<value_type> allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::iterator<value_type, RBtree<value_type> > iterator;
		typedef typename ft::const_iterator<value_type, RBtree<value_type> > const_iterator;
		typedef typename ft::reverse_iterator<value_type, RBtree<value_type> > reverse_iterator;
		typedef typename ft::const_reverse_iterator<value_type, RBtree<value_type> > const_reverse_iterator;
		typedef typename ft::iterator<value_type, RBtree<value_type> >::difference_type difference_type;
		typedef size_t size_type;
		//optional
		typedef RBnode<value_type> nodeType;

		#pragma region (constructor)
		explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _size(0){
			(void)comp;
			(void)alloc;

			tree = new RBtree<value_type>;

			return;
		}

		template <class InputIterator>
  		map (InputIterator first, InputIterator last,
       		const key_compare& comp = key_compare(),
       		const allocator_type& alloc = allocator_type()) : _size(0){
			
			(void)comp;
			(void)alloc;

			tree = new RBtree<value_type>;

			for(; first != last; first++, this->_size++)
			{
				this->tree->RBinsert(new nodeType(*first), //create new node with same element of first
				this->tree->findMax(this->tree->getRoot() ), //find the current max element in the new tree
				RIGHT ); //set the new node as the right child
			}
		
			return;
		}

		map (const map& x) : _size(x._size){
			const_iterator	ite(x.begin());

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
			(void)x;

			return (*this);
		}
		#pragma endregion

		#pragma region Iterators
		iterator begin(){
			return (iterator(tree->findMin(tree->getRoot() ) ) );
		}

		const_iterator begin() const{
			return (const_iterator(tree->findMin(tree->getRoot() ) ) );
		}

		iterator end(){
			return (iterator(tree->findMax(tree->getRoot() ), 1 ) );
		}

		const_iterator	end() const{
			return (const_iterator(tree->findMax(tree->getRoot() ), 1) );
		}

		reverse_iterator rbegin(){
			return (reverse_iterator(tree->findMax(tree->getRoot() ) ) );
		}

		const_reverse_iterator rbegin() const{
			return (const_reverse_iterator(tree->findMax(tree->getRoot() ) ) );
		}

		reverse_iterator rend(){
			return (reverse_iterator(tree->findMin(tree->getRoot() ), 3) );
		}

		const_reverse_iterator rend() const{
			return (const_reverse_iterator(tree->findMin(tree->getRoot() ), 3) );
		}
		#pragma endregion

		#pragma region Capacity
		bool empty() const{
			return (tree->getRoot() == NULL);
		}

		size_type size() const{
			return (this->_size);
		}

		size_type max_size() const{
			return (this->_max_size);
		}
		#pragma endregion

		#pragma region Element access
		//TODO: operator[]
		#pragma endregion

		#pragma region Operations
		iterator find (const key_type& k){
			
		}
		#pragma endregion

	public: //must change to private(or protected)
		RBtree<value_type>	*tree;

		size_type			_size;
		static size_type	_max_size;
};

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
		
		bool operator() (const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
};

template < class Key, class T, class Compare, class Alloc>
map<Key, T, Compare, Alloc>::size_type	map<Key, T, Compare, Alloc>::_max_size(230584300921369395);

}