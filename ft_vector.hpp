#pragma once
#include <memory>
#include <cstdio> // library used only to define "size_t"
#include <stdexcept>
#include <string>
#include <iterator> // library used only for base iterator

namespace ft
{

#define allocator_type Alloc
#define value_type T

template<typename T, class Alloc = std::allocator<T> >
class vector
{
	public:

		#pragma region (constructor)
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

		vector(vector<T> const & cpy) : _size(cpy.size()), _capacity(cpy.capacity()){
			_arr = defal.allocate(cpy.capacity());
			for (size_t i(0); i < this->capacity(); i++)
			{
				if (i < this->size())
					defal.construct(&_arr[i], cpy[i]);
				else if (i >= this->size())
					_arr[i] = reinterpret_cast<value_type>(0);
			}

			return;
		}
		#pragma endregion

		#pragma region (destructor)
		virtual	~vector(void){
			for (size_t i(0); i < this->size(); i++)
				defal.destroy(&_arr[i]);
			defal.deallocate(_arr, this->capacity());

			return;
		}
		#pragma endregion

		#pragma region operator=
		vector & operator=(vector<T> const & asn){
			_size = asn.size();
			_capacity = asn.capacity();
			_arr = defal.allocate(asn.capacity());
			for (size_t i(0); i < this->capacity(); i++)
			{
				if (i < this->size())
				{
					defal.destroy(&_arr[i]);
					_arr[i] = asn[i];
				}
				else if (i >= this->size())
					_arr[i] = reinterpret_cast<value_type>(0);
			}

			return *this;
		}
		#pragma endregion

		#pragma region Iterators
		std::iterator	begin(void){
			return std::iterator<std::random_access_iterator_tag, value_type>(
				
			)
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
				value_type	*swap;
				size_t		new_capacity;

				new_capacity = n * 2;
				if (n * 2 > this->max_size())
					new_capacity = this->max_size();
				swap = defal.allocate(new_capacity, this->_arr);
				for (size_t i(0); i < new_capacity; i++)
				{
					if (i < this->size())
					{
						swap[i] = _arr[i];
						defal.destroy(&_arr[i]);
					}
					else if (i >= this->size() && i < n)
						swap[i] = val;
					else if (i >= n && i < this->capacity())
						continue;
					else if (i >= this->capacity())
						swap[i] = reinterpret_cast<value_type>(0);
				}
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
		#pragma endregion

		#pragma region Allocator
		allocator_type	get_allocator() const{
			return this->defal;
		}
		#pragma endregion
		
	protected:
		// protected vars
		value_type		*_arr;
		size_t			_size;
		size_t			_capacity;
		allocator_type	defal;
		
		// static const
		static const size_t	_max_size = 536870912;
		static const std::string	what_of_range;

};

template<typename T, class Alloc>
const std::string vector<T, Alloc>::what_of_range("vector size exceeded");

}