#pragma once
#include <iterator>// library used only for base iterator
#include <cstddef>// library used only to include ptrdiff_t
#include <iostream>// library used only to print debug

namespace ft
{

#pragma region Random Access Iterator
template<typename T>
class iterator : public std::iterator<std::random_access_iterator_tag, T>{
	public:
		using typename std::iterator<std::random_access_iterator_tag, T>::iterator_category;
		using typename std::iterator<std::random_access_iterator_tag, T>::value_type;
		using typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
		using typename std::iterator<std::random_access_iterator_tag, T>::pointer;
		using typename std::iterator<std::random_access_iterator_tag, T>::reference;


		iterator(void) : std::iterator<std::random_access_iterator_tag, value_type>(){
			this->p = NULL;

			return;
		}

		iterator(iterator const & cpy) : std::iterator<std::random_access_iterator_tag, value_type>(){
			this->p = cpy.p;

			return;
		}

		virtual ~iterator(void){
			return;
		}

		virtual iterator &	operator=(iterator const & asn){
			this->p = asn.p;

			return (*this);
		}

		virtual bool	operator==(iterator const & cmp) const{
			return this->p == cmp.p;
		}

		virtual bool	operator!=(iterator const & cmp) const{
			return this->p != cmp.p;
		}

		virtual value_type &	operator*(void) const{
			return *(this->p);
		}

		virtual value_type *	operator->(void) const{ // to substitute with pointer keyword
			return &(operator*());
		}

		// BOH
		// value_type *	operator->(void){
		// 	return this->p;
		// }

		// value_type const *	operator->(void) const{
		// 	return this->p;
		// }

		iterator	operator++(int){
			iterator	tmp(*this);

			(this->p)++;
			
			return iterator(tmp);
		}

		iterator &	operator++(void){
			(this->p)++;

			return (*this);
		}

		iterator	operator--(int){
			iterator	tmp(*this);

			(this->p)--;
			
			return iterator(tmp);
		}

		iterator &	operator--(void){
			(this->p)--;

			return (*this);
		}

		virtual iterator	operator+(difference_type	add) const{
			iterator tmp;
			
			if (add < 0)
				tmp.p = this->p - (add * (-1));
			else if (add >= 0)
				tmp.p = this->p + add;
			
			return tmp;
		}

		virtual difference_type	operator-(iterator const & sub) const{
			return this->p - sub.p;
		}

		virtual iterator	operator-(difference_type	sub) const{
			iterator tmp;

			if (sub < 0)
				tmp.p = this->p + (sub * (-1));
			else if (sub >= 0)
				tmp.p = this->p - sub;
			
			return tmp;
		}

		virtual bool	operator<(iterator const & cmp) const{
			return this->p < cmp.p;
		}

		virtual bool	operator>(iterator const & cmp) const{
			return this->p > cmp.p;
		}

		virtual bool	operator<=(iterator const & cmp) const{
			return this->p <= cmp.p;
		}

		virtual bool	operator>=(iterator const & cmp) const{
			return this->p >= cmp.p;
		}

		virtual iterator &	operator+=(difference_type	add){
			if (add < 0)
				this->p -= add * (-1);
			else if (add >= 0)
				this->p += add;
			
			return (*this);
		}

		virtual iterator &	operator-=(difference_type	sub){
			if (sub < 0)
				this->p += sub * (-1);
			else if (sub >= 0)
				this->p -= sub;
			
			return (*this);
		}

		virtual value_type &	operator[](difference_type n){
			return *(this->p + n);
		}

		virtual const value_type &	operator[](difference_type n) const{
			return *(this->p + n);
		}
	protected:
		value_type	*p;
};
#pragma endregion

#pragma region Const Iterator
template<typename T>
class const_iterator : public iterator<const T>{};
#pragma endregion

#pragma region Reverse Iterator
template<typename T>
class	reverse_iterator : public iterator<T>{
	public:
		using typename ft::iterator<T>::iterator_category;
		using typename ft::iterator<T>::value_type;
		using typename ft::iterator<T>::difference_type;
		using typename ft::iterator<T>::pointer;
		using typename ft::iterator<T>::reference;

		reverse_iterator(void) : iterator<T>(){
			return;
		}

		explicit	reverse_iterator(iterator<T> const & cpy) : iterator<T>(cpy){
			return;
		}

		iterator<value_type>	base(void) const{
			return static_cast<iterator<value_type> >(*this);
		}

		reverse_iterator	operator+(difference_type n) const{
			reverse_iterator	tmp(*this);

			tmp.p -= n;

			return tmp;
		}

		reverse_iterator &	operator++(void){
			return --(this->p);
		}

		reverse_iterator	operator++(int){
			reverse_iterator	tmp(*this);

			(this->p)--;

			return tmp;
		}

		reverse_iterator &	operator+=(difference_type n){
			this->p -= n;

			return *this;
		}

		reverse_iterator	operator-(difference_type n) const{
			reverse_iterator	tmp(*this);

			tmp.p += n;

			return tmp;
		}

		reverse_iterator &	operator--(void){
			return ++(this->p);
		}

		reverse_iterator	operator--(int){
			reverse_iterator	tmp(*this);

			(this->p)++;

			return tmp;
		}

		reverse_iterator &	operator-=(difference_type n){
			this->p += n;

			return *this;
		}
};

#ifndef __APPLE__
// # define value_type T
# undef difference_type
#endif

template<typename T>
reverse_iterator<T>	operator+(typename reverse_iterator<T>::difference_type n,
	const reverse_iterator<T>& rev_it){
	reverse_iterator<typename reverse_iterator<T>::value_type>	tmp(rev_it);
	
	tmp.p -= n;

	return tmp;
}

template<typename T>
reverse_iterator<T>	operator-(typename reverse_iterator<T>::difference_type n,
	const reverse_iterator<T>& rev_it){
	reverse_iterator<typename reverse_iterator<T>::value_type>	tmp(rev_it);
	
	tmp.p += n;

	return tmp;
}

#ifndef __APPLE__
// # define value_type T
# define difference_type ptrdiff_t
#endif

#pragma endregion

#pragma region Const Reverse Iterator
template<typename T>
class const_reverse_iterator : public reverse_iterator<const T>{};
#pragma endregion

}