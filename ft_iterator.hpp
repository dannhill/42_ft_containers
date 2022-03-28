#pragma once
#include <iterator>// library used only for base iterator
#include <cstddef>// library used only to include ptrdiff_t
#include <iostream>// library used only to print debug

namespace ft
{

// to delete later, after i figure out how does macos work
#ifndef __APPLE__
# define value_type T
# define difference_type ptrdiff_t
#endif

#pragma region Random Access Iterator
template<typename T>
class iterator : public std::iterator<std::random_access_iterator_tag, T>{
	public:
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

		virtual iterator	operator+(difference_type	add){
			iterator tmp;
			
			if (add < 0)
				tmp.p = this->p - (add * (-1));
			else if (add >= 0)
				tmp.p = this->p + add;
			
			return tmp;
		}

		virtual difference_type	operator-(iterator const & sub){
			return this->p - sub.p;
		}

		virtual iterator	operator-(difference_type	sub){
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
	protected:
		value_type	*p;
};
#pragma endregion

#pragma region Reverse Iterator
template<typename T>
class	reverse_iterator : public iterator<T>{
	public:
		reverse_iterator(void) : iterator<value_type>(){
			return;
		}

		explicit	reverse_iterator(iterator<value_type> const & cpy) : iterator<value_type>(cpy){
			return;
		}

		iterator<value_type> &	base(void) const{
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

		value_type &	operator[](difference_type n) const{
			this->base() -= n + 1;

			return (*this);
		}
};

#ifndef __APPLE__
// # define value_type T
# undef difference_type
#endif

template<typename T>
reverse_iterator<T>	operator+(typename reverse_iterator<T>::difference_type n,
	const reverse_iterator<T>& rev_it){
	reverse_iterator<value_type>	tmp(rev_it);
	
	tmp.p -= n;

	return tmp;
}

template<typename T>
reverse_iterator<T>	operator-(typename reverse_iterator<T>::difference_type n,
	const reverse_iterator<T>& rev_it){
	reverse_iterator<value_type>	tmp(rev_it);
	
	tmp.p += n;

	return tmp;
}

#ifndef __APPLE__
// # define value_type T
# define difference_type ptrdiff_t
#endif

#pragma endregion

}