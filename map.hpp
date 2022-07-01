
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
		using allocator_type::reference reference;
		using allocator_type::const_reference const_reference;
		using allocator_type::pointer pointer;
		using allocator_type::const_pointer;
		//TODO
		typedef ft::iterator<value_type, RBtree<value_type> >::iterator;
		typedef ft::const_iterator<value_type, RBtree<value_type> >::const_iterator;
		typedef ft::reverse_iterator<value_type, RBtree<value_type> >::reverse_iterator;
		typedef ft::const_reverse_iterator<value_type, RBtree<value_type> >::const_reverse_iterator;
		typedef ft::iterator<value_type, RBtree<value_type> >::difference_type;
		typedef size_t size_type;
		
		explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()){
			
			return;
		}
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

}