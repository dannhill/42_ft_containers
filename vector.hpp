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

template<typename T, class Alloc /*= std::allocator<T>*/ >
class vector
{
	public:
		typedef unsigned long long size_type;
		typedef Alloc allocator_type;
		typedef T value_type;

		#pragma region (constructor)
		explicit vector(const allocator_type& tmp = allocator_type()){
			allocator_type&	alloc = const_cast<allocator_type &>(tmp);
			value_type	*pippo = alloc.allocate(1);
			alloc.deallocate(pippo, 1);
			// _arr = alloc.allocate(0);
			_size = 0;
			_capacity = 0;

			return;
		}

		explicit vector(size_t n, const value_type& val = value_type(),
			const allocator_type& tmp = allocator_type()){
			allocator_type&	alloc = const_cast<allocator_type &>(tmp);
			_arr = alloc.allocate(n * 2);
			_size = n;
			_capacity = n * 2;
			for (size_t i(0); i < this->capacity(); i++)
			{
				if (i < this->size())
					alloc.construct(&_arr[i], val);
				// else if (i >= this->size())
				// 	alloc.destroy(&_arr[i]);
			}

			return;
		}

		template <class InputIterator>
    	vector(typename ft::disable_if<ft::is_integral<InputIterator>::value, InputIterator>
		::type first, InputIterator last,
        	const allocator_type& tmp = allocator_type()){
			allocator_type&	alloc = const_cast<allocator_type &>(tmp);
			_size = 0;
			for (; last != first; _size++, last--);
			_arr = alloc.allocate(_size * 2);
			_capacity = _size * 2;
			for (size_t i(0); i < this->capacity(); i++)
			{
				if (i < this->size())
				{
					alloc.construct(&_arr[i], *first);
					first++;
				}
				// else if (i >= this->size())
				// 	alloc.destroy(&_arr[i]);
			}

			return;
		}

		vector(vector<T> const & cpy) : _size(cpy.size()), _capacity(cpy.capacity()){
			_arr = defal.allocate(cpy.capacity());

			for (size_t i(0); i < this->capacity(); i++)
			{
				if (i < this->size())
					defal.construct(&_arr[i], cpy[i]);
				// else if (i >= this->size())
				// 	defal.destroy(&_arr[i]);
			}

			return;
		}
		#pragma endregion

		#pragma region (destructor)
		virtual	~vector(void){
			for (size_t i(0); i < this->size(); i++)
				defal.destroy(&_arr[i]);
			if (this->size() > 0)
				defal.deallocate(_arr, this->capacity());

			return;
		}
		#pragma endregion

		#pragma region operator=
		vector & operator=(vector<T> const & asn){
			
			for (size_t i(0); i < this->size(); i++)
				defal.destroy(&_arr[i]);
			if (this->size() > 0)
				defal.deallocate(_arr, this->capacity());

			_size = asn.size();
			_capacity = asn.capacity();
			_arr = defal.allocate(asn.capacity());
			for (size_t i(0); i < this->capacity(); i++)
			{
				if (i < this->size())
					defal.construct(&_arr[i], asn[i]);
				// else if (i >= this->size())
				// 	defal.destroy(&_arr[i]);
			}

			return (*this);
		}
		#pragma endregion

		#pragma region Iterators

		typedef ft::iterator<value_type> 				iterator;
		typedef	ft::reverse_iterator<value_type>		reverse_iterator;
		typedef ft::const_iterator<value_type>			const_iterator;
		typedef ft::const_reverse_iterator<value_type>	const_reverse_iterator;
		
		iterator	begin(void){
			iterator	ret;

			ret += reinterpret_cast<typename iterator::difference_type>(this->_arr) / sizeof(value_type);

			return ret;
		}

		const_iterator	begin(void) const{
			const_iterator	ret;

			ret += reinterpret_cast<typename iterator::difference_type>(this->_arr) / sizeof(value_type);

			return ret;
		}

		iterator	end(void){
			iterator ret;

			ret += reinterpret_cast<typename iterator::difference_type>(this->_arr + this->_size) / sizeof(value_type);

			return ret;
		}

		const_iterator	end(void) const{
			const_iterator ret;

			ret += reinterpret_cast<typename iterator::difference_type>(this->_arr + this->_size) / sizeof(value_type);

			return ret;
		}

		reverse_iterator	rbegin(void){
			reverse_iterator	ret;

			ret -= reinterpret_cast<typename iterator::difference_type>(this->_arr + this->_size - 1) / sizeof(value_type);

			return ret;
		}

		const_reverse_iterator	rbegin(void) const{
			const_reverse_iterator	ret;

			ret -= reinterpret_cast<typename iterator::difference_type>(this->_arr + this->_size - 1) / sizeof(value_type);

			return ret;
		}

		reverse_iterator	rend(void){
			reverse_iterator	ret;

			ret -= reinterpret_cast<typename iterator::difference_type>(this->_arr - 1) / sizeof(value_type);

			return ret;
		}

		const_reverse_iterator	rend(void) const{
			const_reverse_iterator	ret;

			ret -= reinterpret_cast<typename iterator::difference_type>(this->_arr - 1) / sizeof(value_type);

			return ret;
		}
		#pragma endregion

		#pragma region Capacity
		size_t	size(void) const{
			return this->_size;
		}

		size_t	max_size(void) const{
			return this->_max_size;
		}

		void	resize(size_t n, value_type val = value_type()){
			if (n <= this->size())
			{
				if (n == this->size())
					return;
				// for (size_t i(n); i < this->size(); i++)
				// 	defal.destroy(&_arr[i]);
					// _arr[i] = reinterpret_cast<value_type>(0);
				this->_size = n;
			}
			else if (n > this->size() && n <= this->capacity())
			{
				for (size_t i(this->size()); i < this->capacity(); i++)
					defal.construct(&_arr[i], val);
				this->_size = n;
			}
			else if (n > this->capacity() && n <= this->max_size())
			{
				value_type	*swap;
				size_t		new_capacity;

				new_capacity = n * 2;
				if (n * 2 > this->max_size())
					new_capacity = this->max_size();

				swap = defal.allocate(new_capacity);
				for (size_t i(0); i < new_capacity; i++)
				{
					if (i < this->size())
					{
						defal.construct(&swap[i], _arr[i]);
						defal.destroy(&_arr[i]);
					}
					else if (i >= this->size() && i < n)
						defal.construct(&swap[i], val);
					// else if (i >= n)
					// 	defal.destroy(&swap[i]);
				}
				if (this->size() > 0)
					defal.deallocate(_arr, this->capacity());
				this->_size = n;
				this->_capacity = new_capacity;
				this->_arr = swap;
			}
			else if (n > this->max_size())
				throw std::length_error("size exceeds maximum value");

			return;
		}

		size_t	capacity(void) const{
			return this->_capacity;
		}

		bool	empty(void) const{
			return !this->size();
		}

		void	reserve(size_t n){
			if (n <= this->capacity())
				return;
			else if (n > this->max_size())
				throw std::length_error("capacity exceeds maximum value");
			else if (n > this->capacity() && n <= this->max_size())
			{
				value_type	*swap;

				swap = defal.allocate(n, this->_arr);
				for (size_t i(0); i < this->capacity(); i++)
				{
					if (i < this->size())
					{
						swap[i] = _arr[i];
						defal.destroy(&_arr[i]);
					}
					else if (i >= this->size())
						swap[i] = reinterpret_cast<value_type>(0);
				}
				defal.deallocate(_arr, this->capacity());
				this->_capacity = n;
				this->_arr = swap;
			}

			return;
		}
		#pragma endregion

		#pragma region Element access
		value_type &	operator[](size_t n){
			return _arr[n];	
		}

		value_type const &	operator[](size_t n) const{
			return _arr[n];
		}

		value_type &	at(size_t n){
			if (n >= this->size())
				throw std::out_of_range(this->what_of_range);

			return _arr[n];	
		}

		value_type const &	at(size_t n) const{
			if (n >= this->size())
				throw std::out_of_range(this->what_of_range);

			return _arr[n];
		}

		value_type &	front(){
			return _arr[0];	
		}

		value_type const &	front() const{
			return _arr[0];	
		}

		value_type &	back(){
			return _arr[this->size() - 1];	
		}

		value_type const &	back() const{
			return _arr[this->size() - 1];	
		}
		#pragma endregion

		#pragma region Modifiers
		template <class InputIterator>
		typename ft::disable_if<ft::is_integral<InputIterator>::value
		>::type assign(InputIterator first, InputIterator last){
			size_t	sz(0);
			for (; last != first; sz++, last--);

			this->resize(sz);
			for (size_t i(0); i < sz; i++, first++)
			{
				defal.destroy(&_arr[i]);
				defal.construct(&_arr[i], *first);
			}

			return;
		}

		void	assign(size_t n, const value_type& val){
			size_t	old_size(this->size());

			this->resize(n, val);
			for (size_t i(0); i < old_size; i++)
			{
				defal.destroy(&_arr[i]);
				defal.construct(&_arr[i], val);
			}

			return;
		}

		void	push_back(const value_type& val){
			this->resize(this->size() + 1, val);

			return;
		}

		void	pop_back(void){
			this->resize(this->size() - 1);

			return;
		}

		iterator insert (iterator position, const value_type& val){
			size_t	offset(position - this->begin());
			size_t	sz(this->size());
			iterator	ret;

			this->push_back(val);
			for (size_t i(this->size() - 1); i > offset && sz > 0; i--)
				(*this)[i] = (*this)[i - 1];
			(*this)[offset] = val;

			ret += reinterpret_cast<typename iterator::difference_type>(this->_arr + offset) / sizeof(value_type);

			return ret;
		}

		void insert (iterator position, size_t n, const value_type& val){
			size_t	offset(position - this->begin());
			size_t	sz(this->size());

			this->resize(sz + n, val);

			for (size_t i(this->size() - 1); i >= offset + n && sz > 0; i--)
				(*this)[i] = (*this)[i - n];
			for (size_t i(offset); i < offset + n && sz > 0; i++)
				(*this)[i] = val;
			
			return;
		}

		template <class InputIterator>
			typename ft::disable_if<ft::is_integral<InputIterator>::value
			>::type insert(iterator position, InputIterator first, InputIterator last){
			size_t	offset(position - this->begin());
			size_t	range(0);
			for (; last != first; range++, last--);
			size_t	sz(this->size());
			
			this->resize(sz + range);
			for (size_t i(offset); i + range< this->size() && sz > 0; i++)
				(*this)[i + range] = (*this)[i]; //BUG HEAP BUFFER OVERFLOW
			for (size_t i(offset); i < offset + range && sz > 0; i++, first++)
				(*this)[i] = *first;

			return;
		}

		iterator erase(iterator position){
			size_t	offset(position - this->begin());
			size_t	sz(this->size());

			for (size_t i(offset); i < sz - 1; i++)
				(*this)[i] = (*this)[i + 1];
			this->pop_back();

			return this->begin() + offset;
		}

		iterator erase(iterator first, iterator last){
			size_t	offset(first - this->begin());
			size_t	range(last - first);
			size_t	sz(this->size());

			for (size_t i(offset); i < sz - range; i++)
				(*this)[i] = (*this)[i + range];
			this->resize(sz - range);

			return this->begin() + offset;
		}

		void	swap(vector& x){
			size_t		tmp_size(x.size());
			size_t		tmp_cap(x.capacity());
			value_type	*tmp_arr(x._arr);

			x._size = this->size();
			x._capacity = this->capacity();
			x._arr = this->_arr;

			this->_size = tmp_size;
			this->_capacity = tmp_cap;
			this->_arr = tmp_arr;

			return;
		}

		void clear(void){
			size_t	sz(this->size());

			for (size_t i(0); i < sz; i++)
				defal.destroy(&_arr[i]);
			this->_size = 0;

			return;
		}
		#pragma endregion

		#pragma region Allocator
		allocator_type	get_allocator() const{
			return this->defal;
		}
		#pragma endregion
		
	protected:
		// protected vars
		value_type				*_arr;
		size_t					_size;
		size_t					_capacity;
		allocator_type			defal;
		
		// static const
		static const size_t	_max_size = 2305843009213693951;
		static const std::string	what_of_range;

};

template<typename T, class Alloc>
const std::string vector<T, Alloc>::what_of_range("vector size exceeded");

#pragma region Non-member functions overloads
template <class T, class Alloc>
void swap(vector<T,Alloc>& x, vector<T,Alloc>& y){
	x.swap(y);

	return;
}

template <class T, class Alloc>
bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	size_t sz(lhs.size());
	if (sz != rhs.size())
		return false;
	
	for (size_t i(0); i < sz; i++)
		if (lhs[i] != rhs[i])
			return false;

	return true;
}

template <class T, class Alloc>
bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	size_t	sz = lhs.size() < rhs.size() ? lhs.size() : rhs.size();

	for (size_t i(0); i < sz; i++)
	{
		if (lhs[i] < rhs[i])
			return true;
		else if (lhs[i] > rhs[i])
			return false;
	}

	return lhs.size() < rhs.size() ? true : false;
}

template <class T, class Alloc>
bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	return !(lhs < rhs);
}
#pragma endregion

}