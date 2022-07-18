#pragma once
// #include <iostream>
// #include <vector>
#include <functional>
#include <memory>
#include "ft_utility.hpp"

template<typename T, class Alloc = std::allocator<T> >
class RBnode;

template<typename T, class Alloc = std::allocator<T> >
class RBtree;

namespace ft
{

template<typename T, class Alloc = std::allocator<T> >
class vector;

template < class Key, class T, class Compare = std::less<Key>,
	class Alloc = std::allocator<pair<const Key,T> > >
class map;

template<typename T, class dstruct = vector<T> >
class const_iterator;

template<typename T, class dstruct = vector<T> >
class iterator;

template<typename T, class dstruct = vector<T> >
class reverse_iterator;

template<typename T, class dstruct = vector<T> >
class const_reverse_iterator;

template<typename value_type, class dstruct = vector<value_type> >
class tpointer;

}