#pragma once
#include <memory>
#include <cstdio> //library used only to define "size_t"
#include <stdexcept>
#include <string>

namespace ft
{

#define allocator_type Alloc
#define value_type T

template<typename T, class Alloc = std::allocator<T> >
class vector
{
	public:
		explicit vector(const allocator_type& tmp = allocator_type()){
			allocator_type&	alloc = const_cast<allocator_type &>(tmp);
			_arr = alloc.allocate(0);
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
					else if (i >= this->size())
						_arr[i] = reinterpret_cast<value_type>(0);
				}

				return;
			}

		virtual	~vector(void){
			allocator_type	alloc;
			for (size_t i(0); i < this->size(); i++)
				alloc.destroy(&_arr[i]);
			alloc.deallocate(_arr, this->capacity());

			return;
		}

		vector(vector<T> const & cpy) : _size(cpy.size()), _capacity(cpy.capacity()){
			allocator_type	alloc;
			_arr = alloc.allocate(cpy.capacity());
			for (size_t i(0); i < this->capacity(); i++)
			{
				if (i < this->size())
					alloc.construct(&_arr[i], cpy[i]);
				else if (i >= this->size())
					_arr[i] = reinterpret_cast<value_type>(0);
			}

			return;
		}

		vector & operator=(vector<T> const & asn){
			allocator_type	alloc;
			_size = asn.size();
			_capacity = asn.capacity();
			_arr = alloc.allocate(asn.capacity());
			for (size_t i(0); i < this->capacity(); i++)
			{
				if (i < this->size())
				{
					alloc.destroy(&_arr[i]);
					_arr[i] = asn[i];
				}
				else if (i >= this->size())
					_arr[i] = reinterpret_cast<value_type>(0);
			}

			return *this;
		}

		size_t	size(void) const{
			return this->_size;
		}

		size_t	capacity(void) const{
			return this->_capacity;
		}

		size_t	max_size(void) const{
			return this->_max_size;
		}

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

		value_type &	front(size_t n){
			return _arr[0];	
		}

		value_type const &	front(size_t n) const{
			return _arr[0];	
		}

		value_type &	back(size_t n){
			return _arr[this->size() - 1];	
		}

		value_type const &	back(size_t n) const{
			return _arr[this->size() - 1];	
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
				allocator_type	alloc;
				value_type	*swap;

				swap = alloc.allocate(n, this->_arr);
				for (size_t i(0); i < this->capacity(); i++)
				{
					if (i < this->size())
					{
						swap[i] = _arr[i];
						alloc.destroy(&_arr[i]);
					}
					else if (i >= this->size())
						swap[i] = reinterpret_cast<value_type>(0);
				}
				alloc.deallocate(_arr, this->capacity());
				this->_capacity = n;
				this->_arr = swap;
			}

			return;
		}

		void	resize(size_t n, value_type val = value_type()){
			if (n <= this->size())
			{
				if (n == this->size())
					return;
				for (size_t i(n); i < this->size(); i++)
					_arr[i] = reinterpret_cast<value_type>(0);
				this->_size = n;
			}
			else if (n > this->size() && n <= this->capacity())
			{
				for (size_t i(this->size()); i < this->capacity(); i++)
					_arr[i] = val;
				this->_size = n;
			}
			else if (n > this->capacity() && n <= this->max_size())
			{
				allocator_type	alloc;
				value_type	*swap;
				size_t		new_capacity;

				new_capacity = n * 2;
				if (n * 2 > this->max_size())
					new_capacity = this->max_size();
				swap = alloc.allocate(new_capacity, this->_arr);
				for (size_t i(0); i < new_capacity; i++)
				{
					if (i < this->size())
					{
						swap[i] = _arr[i];
						alloc.destroy(&_arr[i]);
					}
					else if (i >= this->size() && i < n)
						swap[i] = val;
					else if (i >= n && i < this->capacity())
						continue;
					else if (i >= this->capacity())
						swap[i] = reinterpret_cast<value_type>(0);
				}
				alloc.deallocate(_arr, this->capacity());
				this->_size = n;
				this->_capacity = new_capacity;
				this->_arr = swap;
			}
			else if (n > this->max_size())
				throw std::length_error("size exceeds maximum value");

			return;
		}

	protected:
		// protected vars
		value_type	*_arr;
		size_t		_size;
		size_t		_capacity;
		
		// static const
		static const size_t	_max_size = 536870912;
		static const std::string	what_of_range;

};

template<typename T, class Alloc>
const std::string vector<T, Alloc>::what_of_range("vector size exceeded");

}