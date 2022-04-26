
#pragma once
#include <memory>
#include <cstdio> // library used only to define "size_t"
#include <iostream> // library used only to debug printing
#include <stdexcept>
#include <string>
#include "ft_iterator.hpp"
#include "ft_type_traits.hpp"

namespace ft
{

template < class Key, class T, class Compare = std::less<Key>,
	class Alloc = std::allocator<std::pair<const Key,T> > >
class map{
	
};

}