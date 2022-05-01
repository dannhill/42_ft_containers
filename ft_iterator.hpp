#pragma once
#include <iterator>// library used only for base iterator
#include <cstddef>// library used only to include ptrdiff_t
#include <iostream>// library used only to print debug

namespace ft
{

#pragma region Forward Declarations
template<typename T>
class const_iterator;

template<typename T>
class iterator;

template<typename T>
class reverse_iterator;

template<typename T>
class const_reverse_iterator;
#pragma endregion

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

		iterator &	operator=(iterator const & asn){
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
			return this->p;
		}

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

		iterator	operator+(difference_type	add) const{
			iterator tmp;
			
			if (add < 0)
				tmp.p = this->p - (add * (-1));
			else if (add >= 0)
				tmp.p = this->p + add;
			
			return tmp;
		}

		difference_type	operator-(iterator const & sub) const{
			return this->p - sub.p;
		}

		iterator	operator-(difference_type	sub) const{
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

		iterator &	operator+=(difference_type	add){
			if (add < 0)
				this->p -= add * (-1);
			else if (add >= 0)
				this->p += add;
			
			return (*this);
		}

		iterator &	operator-=(difference_type	sub){
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

		operator const_iterator<value_type>(void){
			const_iterator<value_type> ret;

			ret += reinterpret_cast<difference_type>(this->p) / sizeof(value_type);
			return ret;
		}

		operator reverse_iterator<value_type>(void){
			reverse_iterator<value_type> ret;

			ret -= reinterpret_cast<difference_type>(this->p) / sizeof(value_type);
			return ret;
		}

		operator const_reverse_iterator<value_type>(void){
			const_reverse_iterator<value_type> ret;

			ret -= reinterpret_cast<difference_type>(this->p) / sizeof(value_type);
			return ret;
		}
	protected:
		value_type	*p;
};

template<typename T>
iterator<T>	operator+(typename iterator<T>::difference_type n,
	const iterator<T>& it){
	iterator<typename iterator<T>::value_type>	tmp(it);

	tmp.p += n;

	return tmp;
}

template<typename T>
iterator<T>	operator-(typename iterator<T>::difference_type n,
	const iterator<T>& it){
	iterator<typename iterator<T>::value_type>	tmp(it);
	
	tmp.p -= n;

	return tmp;
}

template <class Iterator>
bool operator==(const iterator<Iterator>& lhs, const iterator<Iterator>& rhs){
	return lhs == rhs;
}

template <class Iterator>
bool operator!=(const iterator<Iterator>& lhs, const iterator<Iterator>& rhs){
	return lhs != rhs;
}

template <class Iterator>
bool operator<(const iterator<Iterator>& lhs, const iterator<Iterator>& rhs){
	return lhs < rhs;
}

template <class Iterator>
bool operator<=(const iterator<Iterator>& lhs, const iterator<Iterator>& rhs){
	return lhs <= rhs;
}

template <class Iterator>
bool operator>(const iterator<Iterator>& lhs, const iterator<Iterator>& rhs){
	return lhs > rhs;
}

template <class Iterator>
bool operator>=(const iterator<Iterator>& lhs, const iterator<Iterator>& rhs){
	return lhs >= rhs;
}
#pragma endregion

#pragma region Const Iterator
template<typename T>
class const_iterator : public iterator<const T>{
	public:
		using typename iterator<const T>::iterator_category;
		using typename iterator<const T>::value_type;
		using typename iterator<const T>::difference_type;
		using typename iterator<const T>::pointer;
		using typename iterator<const T>::reference;

		const_iterator(void) : iterator<const T>(){
			this->p = NULL;

			return;
		}

		const_iterator(const_iterator const & cpy) : iterator<const T>(){
			this->p = cpy.p;

			return;
		}

		virtual ~const_iterator(void){
			return;
		}

		const_iterator &	operator=(const_iterator const & asn){
			this->p = asn.p;

			return (*this);
		}

		virtual bool	operator==(const_iterator const & cmp) const{
			return this->p == cmp.p;
		}

		virtual bool	operator!=(const_iterator const & cmp) const{
			return this->p != cmp.p;
		}

		const_iterator	operator++(int){
			const_iterator	tmp(*this);

			(this->p)++;
			
			return const_iterator(tmp);
		}

		const_iterator &	operator++(void){
			(this->p)++;

			return (*this);
		}

		const_iterator	operator--(int){
			const_iterator	tmp(*this);

			(this->p)--;
			
			return const_iterator(tmp);
		}

		const_iterator &	operator--(void){
			(this->p)--;

			return (*this);
		}

		const_iterator	operator+(difference_type	add) const{
			const_iterator tmp;
			
			if (add < 0)
				tmp.p = this->p - (add * (-1));
			else if (add >= 0)
				tmp.p = this->p + add;
			
			return tmp;
		}

		const_iterator	operator-(difference_type	sub) const{
			const_iterator tmp;

			if (sub < 0)
				tmp.p = this->p + (sub * (-1));
			else if (sub >= 0)
				tmp.p = this->p - sub;
			
			return tmp;
		}

		difference_type	operator-(const_iterator const & sub) const{
			return this->p - sub.p;
		}

		virtual bool	operator<(const_iterator const & cmp) const{
			return this->p < cmp.p;
		}

		virtual bool	operator>(const_iterator const & cmp) const{
			return this->p > cmp.p;
		}

		virtual bool	operator<=(const_iterator const & cmp) const{
			return this->p <= cmp.p;
		}

		virtual bool	operator>=(const_iterator const & cmp) const{
			return this->p >= cmp.p;
		}

		const_iterator &	operator+=(difference_type	add){
			if (add < 0)
				this->p -= add * (-1);
			else if (add >= 0)
				this->p += add;
			
			return (*this);
		}

		const_iterator &	operator-=(difference_type	sub){
			if (sub < 0)
				this->p += sub * (-1);
			else if (sub >= 0)
				this->p -= sub;
			
			return (*this);
		}

		operator iterator<value_type>(void){
			iterator<value_type> ret;

			ret += reinterpret_cast<difference_type>(this->p) / sizeof(value_type);
			return ret;
		}

		operator reverse_iterator<value_type>(void){
			reverse_iterator<value_type> ret;

			ret -= reinterpret_cast<difference_type>(this->p) / sizeof(value_type);
			return ret;
		}

		operator const_reverse_iterator<value_type>(void){
			const_reverse_iterator<value_type> ret;

			ret -= reinterpret_cast<difference_type>(this->p) / sizeof(value_type);
			return ret;
		}
};

template<typename T>
const_iterator<T>	operator+(typename const_iterator<T>::difference_type n,
	const const_iterator<T>& con_it){
	const_iterator<typename const_iterator<T>::value_type>	tmp(con_it);

	tmp.p += n;

	return tmp;
}

template<typename T>
const_iterator<T>	operator-(typename const_iterator<T>::difference_type n,
	const const_iterator<T>& con_it){
	const_iterator<typename const_iterator<T>::value_type>	tmp(con_it);
	
	tmp.p -= n;

	return tmp;
}

template <class Iterator>
bool operator==(const const_iterator<Iterator>& lhs, const const_iterator<Iterator>& rhs){
	return lhs == rhs;
}

template <class Iterator>
bool operator!=(const const_iterator<Iterator>& lhs, const const_iterator<Iterator>& rhs){
	return lhs != rhs;
}

template <class Iterator>
bool operator<(const const_iterator<Iterator>& lhs, const const_iterator<Iterator>& rhs){
	return lhs < rhs;
}

template <class Iterator>
bool operator<=(const const_iterator<Iterator>& lhs, const const_iterator<Iterator>& rhs){
	return lhs <= rhs;
}

template <class Iterator>
bool operator>(const const_iterator<Iterator>& lhs, const const_iterator<Iterator>& rhs){
	return lhs > rhs;
}

template <class Iterator>
bool operator>=(const const_iterator<Iterator>& lhs, const const_iterator<Iterator>& rhs){
	return lhs >= rhs;
}
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

		reverse_iterator(reverse_iterator<T> const & cpy) : iterator<T>(cpy){
			return;
		}

		iterator<value_type>	base(void) const{
			return static_cast<iterator<value_type> >(*this);
		}

		virtual bool	operator==(reverse_iterator const & cmp) const{
			return this->p == cmp.p;
		}

		virtual bool	operator!=(reverse_iterator const & cmp) const{
			return this->p != cmp.p;
		}

		reverse_iterator	operator+(difference_type n) const{
			reverse_iterator	tmp(*this);

			tmp.p -= n;

			return tmp;
		}

		reverse_iterator &	operator++(void){
			(this->p)--;

			return (*this);
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

		difference_type	operator-(reverse_iterator const & sub) const{
			return this->p - sub.p;
		}

		reverse_iterator	operator-(difference_type n) const{
			reverse_iterator	tmp(*this);

			tmp.p += n;

			return tmp;
		}

		reverse_iterator &	operator--(void){
			(this->p)++;

			return (*this);
		}

		reverse_iterator	operator--(int){
			reverse_iterator	tmp(*this);

			(this->p)++;

			return tmp;
		}

		virtual bool	operator<(reverse_iterator const & cmp) const{
			return this->p < cmp.p;
		}

		virtual bool	operator>(reverse_iterator const & cmp) const{
			return this->p > cmp.p;
		}

		virtual bool	operator<=(reverse_iterator const & cmp) const{
			return this->p <= cmp.p;
		}

		virtual bool	operator>=(reverse_iterator const & cmp) const{
			return this->p >= cmp.p;
		}

		reverse_iterator &	operator-=(difference_type n){
			this->p += n;

			return *this;
		}

		virtual value_type &	operator[](difference_type n){
			return *(this->p - n);
		}

		virtual const value_type &	operator[](difference_type n) const{
			return *(this->p - n);
		}

		operator const_reverse_iterator<value_type>(void){
			const_reverse_iterator<value_type> ret;

			ret -= reinterpret_cast<difference_type>(this->p) / sizeof(value_type);
			return ret;
		}

		operator const_iterator<value_type>(void){
			const_iterator<value_type> ret;

			ret += reinterpret_cast<difference_type>(this->p) / sizeof(value_type);
			return ret;
		}

		operator iterator<value_type>(void){
			iterator<value_type> ret;

			ret += reinterpret_cast<difference_type>(this->p) / sizeof(value_type);
			return ret;
		}
};

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

template <class Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
	return lhs == rhs;
}

template <class Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
	return lhs != rhs;
}

template <class Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
	return lhs < rhs;
}

template <class Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
	return lhs <= rhs;
}

template <class Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
	return lhs > rhs;
}

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
	return lhs >= rhs;
}

#pragma endregion

#pragma region Const Reverse Iterator
template<typename T>
class const_reverse_iterator : public const_iterator<const T>{
	public:
		using typename ft::const_iterator<const T>::iterator_category;
		using typename ft::const_iterator<const T>::value_type;
		using typename ft::const_iterator<const T>::difference_type;
		using typename ft::const_iterator<const T>::pointer;
		using typename ft::const_iterator<const T>::reference;

		const_reverse_iterator(void) : const_iterator<const T>(){
			return;
		}

		const_reverse_iterator(const_reverse_iterator<const T> const & cpy) : const_iterator<const T>(cpy){
			return;
		}

		iterator<value_type>	base(void) const{
			return static_cast<const_iterator<value_type> >(*this);
		}

		virtual bool	operator==(const_reverse_iterator const & cmp) const{
			return this->p == cmp.p;
		}

		virtual bool	operator!=(const_reverse_iterator const & cmp) const{
			return this->p != cmp.p;
		}

		const_reverse_iterator	operator+(difference_type n) const{
			const_reverse_iterator	tmp(*this);

			tmp.p -= n;

			return tmp;
		}

		const_reverse_iterator &	operator++(void){
			(this->p)--;

			return (*this);
		}

		const_reverse_iterator	operator++(int){
			const_reverse_iterator	tmp(*this);

			(this->p)--;

			return tmp;
		}

		const_reverse_iterator &	operator+=(difference_type n){
			this->p -= n;

			return *this;
		}

		difference_type	operator-(const_reverse_iterator const & sub) const{
			return this->p - sub.p;
		}

		const_reverse_iterator	operator-(difference_type n) const{
			const_reverse_iterator	tmp(*this);

			tmp.p += n;

			return tmp;
		}

		const_reverse_iterator &	operator--(void){
			(this->p)++;
			
			return (*this);
		}

		const_reverse_iterator	operator--(int){
			const_reverse_iterator	tmp(*this);

			(this->p)++;

			return tmp;
		}

		virtual bool	operator<(const_reverse_iterator const & cmp) const{
			return this->p < cmp.p;
		}

		virtual bool	operator>(const_reverse_iterator const & cmp) const{
			return this->p > cmp.p;
		}

		virtual bool	operator<=(const_reverse_iterator const & cmp) const{
			return this->p <= cmp.p;
		}

		virtual bool	operator>=(const_reverse_iterator const & cmp) const{
			return this->p >= cmp.p;
		}

		virtual value_type &	operator[](difference_type n){
			return *(this->p - n);
		}

		virtual const value_type &	operator[](difference_type n) const{
			return *(this->p - n);
		}

		const_reverse_iterator &	operator-=(difference_type n){
			this->p += n;

			return *this;
		}

		operator iterator<value_type>(void){
			iterator<value_type> ret;

			ret += reinterpret_cast<difference_type>(this->p) / sizeof(value_type);
			return ret;
		}

		operator const_iterator<value_type>(void){
			const_iterator<value_type> ret;

			ret += reinterpret_cast<difference_type>(this->p) / sizeof(value_type);
			return ret;
		}

		operator reverse_iterator<value_type>(void){
			reverse_iterator<value_type> ret;

			ret -= reinterpret_cast<difference_type>(this->p) / sizeof(value_type);
			return ret;
		}
};

template<typename T>
const_reverse_iterator<T>	operator+(typename const_reverse_iterator<T>::difference_type n,
	const const_reverse_iterator<T>& rev_it){
	const_reverse_iterator<typename const_reverse_iterator<T>::value_type>	tmp(rev_it);

	tmp.p -= n;

	return tmp;
}

template<typename T>
const_reverse_iterator<T>	operator-(typename const_reverse_iterator<T>::difference_type n,
	const const_reverse_iterator<T>& rev_it){
	const_reverse_iterator<typename const_reverse_iterator<T>::value_type>	tmp(rev_it);
	
	tmp.p += n;

	return tmp;
}

template <class Iterator>
bool operator==(const const_reverse_iterator<Iterator>& lhs, const const_reverse_iterator<Iterator>& rhs){
	return lhs == rhs;
}

template <class Iterator>
bool operator!=(const const_reverse_iterator<Iterator>& lhs, const const_reverse_iterator<Iterator>& rhs){
	return lhs != rhs;
}

template <class Iterator>
bool operator<(const const_reverse_iterator<Iterator>& lhs, const const_reverse_iterator<Iterator>& rhs){
	return lhs < rhs;
}

template <class Iterator>
bool operator<=(const const_reverse_iterator<Iterator>& lhs, const const_reverse_iterator<Iterator>& rhs){
	return lhs <= rhs;
}

template <class Iterator>
bool operator>(const const_reverse_iterator<Iterator>& lhs, const const_reverse_iterator<Iterator>& rhs){
	return lhs > rhs;
}

template <class Iterator>
bool operator>=(const const_reverse_iterator<Iterator>& lhs, const const_reverse_iterator<Iterator>& rhs){
	return lhs >= rhs;
}
#pragma endregion

#pragma region Iterator Traits
template <class Iterator>
class iterator_traits{
	typedef Iterator::difference_type difference_type;
	typedef Iterator::value_type value_type;
	typedef Iterator::pointer pointer;
	typedef Iterator::reference reference;
	typedef Iterator::iterator_category iterator_category;
};

template <class T>
class iterator_traits<T*>{
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef std::random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T*>{
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef const T* pointer;
	typedef const T& reference;
	typedef std::random_access_iterator_tag iterator_category;
};
#pragma endregion

}