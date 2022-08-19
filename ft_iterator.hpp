#pragma once
#include "containers.hpp"
#include <iterator>// library used only for base iterator
#include <cstddef>// library used only to include ptrdiff_t
#include <iostream>// library used only to print debug
#include "ft_type_traits.hpp"
#include "vector.hpp"
#include "rbt.hpp"
#include <cmath>

namespace ft
{

#pragma region Forward Declarations
// template<typename T>
// class RBnode;

// template<typename T>
// class RBtree;

// template<typename T, class dstruct = vector<T> >
// class const_iterator;

// template<typename T, class dstruct = vector<T> >
// class iterator;

// template<typename T, class dstruct = vector<T> >
// class reverse_iterator;

// template<typename T, class dstruct = vector<T> >
// class const_reverse_iterator;

// template<typename value_type, class dstruct = vector<value_type> >
// class tpointer;

	template<typename T>
	iterator<T>	operator+(typename iterator<T>::difference_type n,
		const iterator<T>& it);
	
	template<typename T>
	iterator<T>	operator-(typename iterator<T>::difference_type n,
		const iterator<T>& it);
#pragma endregion

#pragma region Random Access Iterator
template<typename T, class dstruct>
class iterator : public std::iterator<std::random_access_iterator_tag, T>{
	public:
		using typename std::iterator<std::random_access_iterator_tag, T>::iterator_category;
		using typename std::iterator<std::random_access_iterator_tag, T>::value_type;
		using typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
		using typename std::iterator<std::random_access_iterator_tag, T>::pointer;
		using typename std::iterator<std::random_access_iterator_tag, T>::reference;

		iterator(void) : std::iterator<std::random_access_iterator_tag, value_type>(), p(static_cast<dstruct *>(NULL) ){
			// this->p = static_cast<dstruct *>(NULL);

			return;
		}

		iterator(tpointer<value_type, dstruct> point) : p(point){
			return;
		}

		iterator(dstruct * container) : std::iterator<std::random_access_iterator_tag, value_type>(), p(container){// useful only for red-black tree node pointer. need to modify for vector
			// this->p = container;

			return;
		}

		iterator(typename dstruct::nodeType * point, bool end = false) : std::iterator<std::random_access_iterator_tag, value_type>(), p(point, end){

			return;
		}

		iterator(iterator const & cpy) : std::iterator<std::random_access_iterator_tag, value_type>(), p(cpy.p){
			// this->p = cpy.p;

			return;
		}

		virtual ~iterator(void){
			return;
		}

		iterator &	operator=(iterator const & asn){
			this->p = asn.p;

			return (*this);
		}

		tpointer<value_type, dstruct> const &	getPoint(void) const{
			return (this->p);
		}

		virtual bool	operator==(iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) == static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator==(const_iterator<value_type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) == const_cast<value_type *>(static_cast<const value_type *>(cmp.p) ) );
		}

		virtual bool	operator!=(iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) != static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator!=(const_iterator<value_type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) != const_cast<value_type *>(static_cast<const value_type *>(cmp.p) ) );
		}

		virtual value_type &	operator*(void) const{
			return *(this->p);
		}

		virtual value_type *	operator->(void) const{ // to substitute with pointer keyword
			return this->p;
		}

		iterator	operator++(int){
			iterator	tmp(*this);

			this->p = this->p + static_cast<size_t>(1);
			
			return iterator(tmp);
		}

		iterator &	operator++(void){
			this->p = this->p + static_cast<size_t>(1);

			return (*this);
		}

		iterator	operator--(int){
			iterator	tmp(*this);

			this->p = this->p - static_cast<size_t>(1);
			
			return iterator(tmp);
		}

		iterator &	operator--(void){
			this->p = this->p - static_cast<size_t>(1);

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
			return (static_cast<value_type *>(this->p) < static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator<(const_iterator<value_type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) < const_cast<value_type *>(static_cast<const value_type *>(cmp.p) ) );
		}

		virtual bool	operator>(iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) > static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator>(const_iterator<value_type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) > const_cast<value_type *>(static_cast<const value_type *>(cmp.p) ) );
		}

		virtual bool	operator<=(iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) <= static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator<=(const_iterator<value_type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) <= const_cast<value_type *>(static_cast<const value_type *>(cmp.p) ) );
		}

		virtual bool	operator>=(iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) >= static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator>=(const_iterator<value_type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) >= const_cast<value_type *>(static_cast<const value_type *>(cmp.p) ) );
		}

		iterator &	operator+=(difference_type	add){
			if (add < 0)
				this->p = this->p - add * (-1);
			else if (add >= 0)
				this->p = this->p + add;
			
			return (*this);
		}

		iterator &	operator-=(difference_type	sub){
			if (sub < 0)
				this->p = this->p + sub * (-1);
			else if (sub >= 0)
				this->p = this->p - sub;
			
			return (*this);
		}

		virtual value_type &	operator[](difference_type n){
			return *(this->p + n);
		}

		virtual const value_type &	operator[](difference_type n) const{
			return *(this->p + n);
		}

		operator const_iterator<value_type, dstruct>(void){
			const_iterator<value_type, dstruct> ret(this->p);

			// ret += reinterpret_cast<difference_type>(static_cast<value_type *>(this->p)) / sizeof(value_type *);
			return ret;
		}

		operator reverse_iterator<value_type, dstruct>(void){
			reverse_iterator<value_type, dstruct> ret;

			ret -= reinterpret_cast<difference_type>(static_cast<value_type *>(this->p)) / sizeof(value_type);
			return ret;
		}

		operator const_reverse_iterator<value_type, dstruct>(void){
			const_reverse_iterator<value_type, dstruct> ret;

			ret -= reinterpret_cast<difference_type>(static_cast<value_type *>(this->p)) / sizeof(value_type);
			return ret;
		}
	protected:
		tpointer<value_type, dstruct>	p;

		template<typename U>
		friend iterator<U>	operator+(typename iterator<U>::difference_type n,
			const iterator<U>& it);

		template<typename U>
		friend iterator<U>	operator-(typename iterator<U>::difference_type n,
			const iterator<U>& it);

		template <class Iterator>
		friend bool operator==(const iterator<Iterator>& lhs, const iterator<Iterator>& rhs);

		template <class Iterator>
		friend bool operator!=(const iterator<Iterator>& lhs, const iterator<Iterator>& rhs);


		template<typename U, class ustruct>
		friend class const_iterator;
};

template<typename T>
iterator<T>	operator+(typename iterator<T>::difference_type n,
	const iterator<T>& it){
	iterator<typename iterator<T>::value_type>	tmp(it);

	// tmp.p += n;

	return tmp + n;
}

template<typename T>
iterator<T>	operator-(typename iterator<T>::difference_type n,
	const iterator<T>& it){
	iterator<typename iterator<T>::value_type>	tmp(it);
	
	// tmp.p -= n;

	return tmp - n;
}

template <class Iterator>
bool operator==(const iterator<Iterator>& lhs, const iterator<Iterator>& rhs){
	return lhs == rhs;
}

template <class Iterator>
bool operator==(const iterator<Iterator>& lhs, const const_iterator<Iterator>& rhs){
	return lhs == rhs;
}

template <class Iterator>
bool operator!=(const iterator<Iterator>& lhs, const iterator<Iterator>& rhs){
	return lhs != rhs;
}

template <class Iterator>
bool operator!=(const iterator<Iterator>& lhs, const const_iterator<Iterator>& rhs){
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
template<typename T, class dstruct>
class const_iterator : public std::iterator<std::random_access_iterator_tag, T>{
	public:
		using typename std::iterator<std::random_access_iterator_tag, T>::iterator_category;
		using typename std::iterator<std::random_access_iterator_tag, T>::value_type;
		using typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
		using typename std::iterator<std::random_access_iterator_tag, T>::pointer;
		using typename std::iterator<std::random_access_iterator_tag, T>::reference;

		const_iterator(void) : std::iterator<std::random_access_iterator_tag, value_type>(), p(){
			// this->p = static_cast<dstruct *>(NULL);

			return;
		}

		const_iterator(tpointer<value_type, dstruct> point) : p(point){
			return;
		}

		const_iterator(dstruct * container) : std::iterator<std::random_access_iterator_tag, value_type>(), p(container){// useful only for red-black tree node pointer. need to modify for vector
			// this->p = container;

			return;
		}

		const_iterator(typename dstruct::nodeType * point, bool end = false) : std::iterator<std::random_access_iterator_tag, value_type>(), p(point, end){

			return;
		}

		const_iterator(const_iterator const & cpy) : std::iterator<std::random_access_iterator_tag, value_type>(), p(cpy.p){
			// this->p = cpy.p;

			return;
		}

		virtual ~const_iterator(void){
			return;
		}

		virtual tpointer<value_type, dstruct> const &	getPoint(void) const{
			return this->p;
		}

		const_iterator &	operator=(const_iterator const & asn){
			this->p = asn.p;

			return (*this);
		}

		virtual bool	operator==(const_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) == static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator==(iterator<typename ft::remove_const<value_type>::type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) == const_cast<const value_type *>(static_cast<value_type *>(cmp.p) ) );
		}

		virtual bool	operator!=(const_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) != static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator!=(iterator<typename ft::remove_const<value_type>::type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) != const_cast<const value_type *>(static_cast<value_type *>(cmp.p) ) );
		}

		virtual value_type &	operator*(void) const{
			return *(this->p);
		}

		virtual value_type *	operator->(void) const{ // to substitute with pointer keyword
			return this->p;
		}

		const_iterator	operator++(int){
			const_iterator	tmp(*this);

			this->p = this->p + static_cast<size_t>(1);
			
			return const_iterator(tmp);
		}

		const_iterator &	operator++(void){
			this->p = this->p + static_cast<size_t>(1);

			return (*this);
		}

		const_iterator	operator--(int){
			const_iterator	tmp(*this);

			this->p = this->p - static_cast<size_t>(1);
			
			return const_iterator(tmp);
		}

		const_iterator &	operator--(void){
			this->p = this->p - static_cast<size_t>(1);

			return (*this);
		}

		const_iterator	operator+(difference_type	add) const{
			const_iterator tmp(*this);
			
			if (add < 0)
				tmp.p = this->p - (add * (-1));
			else if (add >= 0)
				tmp.p = this->p + add;
			
			return tmp;
		}

		difference_type	operator-(const_iterator const & sub) const{
			return this->p - sub.p;
		}

		const_iterator	operator-(difference_type	sub) const{
			const_iterator tmp(*this);

			if (sub < 0)
				tmp.p = this->p + (sub * (-1));
			else if (sub >= 0)
				tmp.p = this->p - sub;
			
			return tmp;
		}

		virtual bool	operator<(const_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) < static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator<(iterator<typename ft::remove_const<value_type>::type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) < const_cast<const value_type *>(static_cast<value_type *>(cmp.p) ) );
		}

		virtual bool	operator>(const_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) > static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator>(iterator<typename ft::remove_const<value_type>::type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) > const_cast<const value_type *>(static_cast<value_type *>(cmp.p) ) );
		}

		virtual bool	operator<=(const_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) <= static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator<=(iterator<typename ft::remove_const<value_type>::type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) <= const_cast<const value_type *>(static_cast<value_type *>(cmp.p) ) );
		}

		virtual bool	operator>=(const_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) >= static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator>=(iterator<typename ft::remove_const<value_type>::type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) >= const_cast<const value_type *>(static_cast<value_type *>(cmp.p) ) );
		}

		const_iterator &	operator+=(difference_type	add){
			if (add < 0)
				this->p = this->p - add * (-1);
			else if (add >= 0)
				this->p = this->p + add;
			
			return (*this);
		}

		const_iterator &	operator-=(difference_type	sub){
			if (sub < 0)
				this->p = this->p + sub * (-1);
			else if (sub >= 0)
				this->p = this->p - sub;
			
			return (*this);
		}

		virtual value_type &	operator[](difference_type n){
			return *(this->p + n);
		}

		virtual const value_type &	operator[](difference_type n) const{
			return *(this->p + n);
		}

		operator iterator<value_type, dstruct>(void){
			iterator<value_type, dstruct> ret(this->p);

			// ret += reinterpret_cast<difference_type>(static_cast<value_type *>(this->p)) / sizeof(value_type *);
			return ret;
		}

		operator reverse_iterator<const value_type, dstruct>(void){
			reverse_iterator<const value_type, dstruct> ret(this->p);

			return ret;
		}

		operator const_reverse_iterator<const value_type, dstruct>(void){
			const_reverse_iterator<const value_type, dstruct> ret(this->p);

			return ret;
		}
	protected:
		tpointer<value_type, dstruct>	p;

		template<typename U, class ustruct>
		friend class iterator;

		template <class Iterator>
		friend bool operator==(const const_iterator<Iterator>& lhs, const const_iterator<Iterator>& rhs);

		template <class Iterator>
		friend bool operator!=(const const_iterator<Iterator>& lhs, const const_iterator<Iterator>& rhs);
};

template<typename T>
const_iterator<T>	operator+(typename const_iterator<T>::difference_type n,
	const const_iterator<T>& con_it){
	const_iterator<typename const_iterator<T>::value_type>	tmp(con_it);

	// tmp.p += n;

	return tmp + n;
}

template<typename T>
const_iterator<T>	operator-(typename const_iterator<T>::difference_type n,
	const const_iterator<T>& con_it){
	const_iterator<typename const_iterator<T>::value_type>	tmp(con_it);
	
	// tmp.p -= n;

	return tmp - n;
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
template<typename T, class dstruct>
class	reverse_iterator : public iterator<T, dstruct>{
	public:
		using typename ft::iterator<T, dstruct>::iterator_category;
		using typename ft::iterator<T, dstruct>::value_type;
		using typename ft::iterator<T, dstruct>::difference_type;
		using typename ft::iterator<T, dstruct>::pointer;
		using typename ft::iterator<T, dstruct>::reference;

		reverse_iterator(void) : iterator<T, dstruct>(){
			return;
		}

		reverse_iterator(tpointer<value_type, dstruct> point) : iterator<T, dstruct>(point){
			return;
		}

		reverse_iterator(dstruct * container) : iterator<T, dstruct>(container){// useful only for red-black tree node pointer. need to modify for vector

			return;
		}

		// reverse_iterator(reverse_iterator<T, dstruct> const & cpy) : iterator<T, dstruct>(cpy){
		// 	return;
		// }

		reverse_iterator(iterator<T, dstruct> const & cpy) : iterator<T, dstruct>(cpy - 1){
			return;
		}

		iterator<value_type>	base(void) const{
			return static_cast<iterator<value_type, dstruct> >(*this) + 1;
		}

		virtual bool	operator==(reverse_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) == static_cast<value_type *>(cmp.getPoint()));
		}

		virtual bool	operator==(const_reverse_iterator<value_type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) == const_cast<value_type *>(static_cast<const value_type *>(cmp.getPoint()) ) );
		}

		virtual bool	operator!=(reverse_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) != static_cast<value_type *>(cmp.getPoint()));
		}

		virtual bool	operator!=(const_reverse_iterator<value_type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) != const_cast<value_type *>(static_cast<const value_type *>(cmp.getPoint()) ) );
		}

		reverse_iterator	operator+(difference_type n) const{
			reverse_iterator	tmp(*this);

			tmp.p = tmp.p - n;

			return tmp;
		}

		reverse_iterator &	operator++(void){
			this->p = this->p - static_cast<size_t>(1);

			return (*this);
		}

		reverse_iterator	operator++(int){
			reverse_iterator	tmp(*this);

			this->p = this->p - static_cast<size_t>(1);

			return tmp;
		}

		reverse_iterator &	operator+=(difference_type n){
			this->p = this->p - n;

			return *this;
		}

		reverse_iterator &	operator-=(difference_type n){
			this->p = this->p + n;

			return *this;
		}

		difference_type	operator-(reverse_iterator const & sub) const{
			return this->p - sub.p;
		}

		reverse_iterator	operator-(difference_type n) const{
			reverse_iterator	tmp(*this);

			tmp.p = tmp.p + n;

			return tmp;
		}

		reverse_iterator &	operator--(void){
			this->p = this->p + static_cast<size_t>(1);

			return (*this);
		}

		reverse_iterator	operator--(int){
			reverse_iterator	tmp(*this);

			this->p = this->p + static_cast<size_t>(1);

			return tmp;
		}

		virtual bool	operator<(reverse_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) < static_cast<value_type *>(cmp.getPoint()));
		}

		virtual bool	operator<(const_reverse_iterator<value_type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) < const_cast<value_type *>(static_cast<const value_type *>(cmp.getPoint()) ) );
		}

		virtual bool	operator>(reverse_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) > static_cast<value_type *>(cmp.getPoint()));
		}

		virtual bool	operator>(const_reverse_iterator<value_type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) > const_cast<value_type *>(static_cast<const value_type *>(cmp.getPoint()) ) );
		}

		virtual bool	operator<=(reverse_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) <= static_cast<value_type *>(cmp.getPoint()));
		}

		virtual bool	operator<=(const_reverse_iterator<value_type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) <= const_cast<value_type *>(static_cast<const value_type *>(cmp.getPoint()) ) );
		}

		virtual bool	operator>=(reverse_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) >= static_cast<value_type *>(cmp.getPoint()));
		}

		virtual bool	operator>=(const_reverse_iterator<value_type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) >= const_cast<value_type *>(static_cast<const value_type *>(cmp.getPoint()) ) );
		}

		virtual value_type &	operator[](difference_type n){
			return *(this->p - n);
		}

		virtual const value_type &	operator[](difference_type n) const{
			return *(this->p - n);
		}

		operator const_reverse_iterator<value_type, dstruct>(void){
			const_reverse_iterator<value_type, dstruct> ret(this->p);

			return ret;
		}

		operator const_iterator<value_type, dstruct>(void){
			const_iterator<value_type, dstruct> ret(this->p);
			// ret -= 1;

			return ret;
		}

		operator iterator<value_type, dstruct>(void){
			iterator<value_type, dstruct> ret(this->p);
			// ret -= 1;

			return ret;
		}

		protected:


		// template<typename U, class ustruct>
		friend class const_iterator<T, dstruct>;

		// template<typename U, class ustruct>
		friend class const_reverse_iterator<T, dstruct>;

		template<typename U>
		friend reverse_iterator<U>	operator+(typename reverse_iterator<U>::difference_type n,
			const reverse_iterator<U>& rev_it);

		template<typename U>
		friend reverse_iterator<U>	operator-(typename reverse_iterator<U>::difference_type n,
			const reverse_iterator<U>& rev_it);
};

// template<typename T>
// reverse_iterator<T>	operator+(typename reverse_iterator<T>::difference_type n,
// 	const reverse_iterator<T>& rev_it){
// 	reverse_iterator<typename reverse_iterator<T>::value_type>	tmp(rev_it);

// 	tmp.p -= n;

// 	return tmp;
// }

template<typename T>
reverse_iterator<T>	operator-(typename reverse_iterator<T>::difference_type n,
	const reverse_iterator<T>& rev_it){
	reverse_iterator<typename reverse_iterator<T>::value_type>	tmp(rev_it);
	
	tmp.p = tmp.p + n;

	return tmp;
}

template<typename T>
reverse_iterator<T>	operator+(typename reverse_iterator<T>::difference_type n,
	const reverse_iterator<T>& rev_it){
	reverse_iterator<typename reverse_iterator<T>::value_type>	tmp(rev_it);
	
	tmp.p = tmp.p - n;

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
template<typename T, class dstruct>
class const_reverse_iterator : public const_iterator<T, dstruct>{
	public:
		using typename ft::const_iterator<T, dstruct>::iterator_category;
		using typename ft::const_iterator<T, dstruct>::value_type;
		using typename ft::const_iterator<T, dstruct>::difference_type;
		using typename ft::const_iterator<T, dstruct>::pointer;
		using typename ft::const_iterator<T, dstruct>::reference;

		const_reverse_iterator(void) : const_iterator<T, dstruct>(){
			return;
		}

		const_reverse_iterator(tpointer<value_type, dstruct> point) : const_iterator<T, dstruct>(point){
			
			return;
		}

		const_reverse_iterator(const_iterator<T, dstruct> & ite) : const_iterator<T, dstruct>(ite){
			return;
		}

		const_reverse_iterator(iterator<T, dstruct> & ite) : const_iterator<T, dstruct>(ite){
			return;
		}

		const_reverse_iterator(dstruct * container) : const_iterator<T, dstruct>(container){// useful only for red-black tree node pointer. need to modify for vector

			return;
		}

		// const_reverse_iterator(const_reverse_iterator<T, dstruct> const & cpy) : const_iterator<T, dstruct>(cpy){
		// 	return;
		// }



		iterator<value_type>	base(void) const{
			return static_cast<const_iterator<value_type> >(*this);
		}

		virtual bool	operator==(const_reverse_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) == static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator==(reverse_iterator<typename ft::remove_const<value_type>::type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) == const_cast<const value_type *>(static_cast<value_type *>(cmp.getPoint() ) ) );
		}

		virtual bool	operator!=(const_reverse_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) != static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator!=(reverse_iterator<typename ft::remove_const<value_type>::type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) != const_cast<const value_type *>(static_cast<value_type *>(cmp.getPoint() ) ) );
		}

		const_reverse_iterator	operator+(difference_type n) const{
			const_reverse_iterator	tmp(*this);

			tmp.p = tmp.p - n;

			return tmp;
		}

		const_reverse_iterator &	operator++(void){
			this->p = this->p - static_cast<size_t>(1);

			return (*this);
		}

		const_reverse_iterator	operator++(int){
			const_reverse_iterator	tmp(*this);

			this->p = this->p - static_cast<size_t>(1);

			return tmp;
		}

		difference_type	operator-(const_reverse_iterator const & sub) const{
			return this->p - sub.p;
		}

		const_reverse_iterator	operator-(difference_type n) const{
			const_reverse_iterator	tmp(*this);

			tmp.p = tmp.p + n;

			return tmp;
		}

		const_reverse_iterator &	operator--(void){
			this->p = this->p + static_cast<size_t>(1);
			
			return (*this);
		}

		const_reverse_iterator	operator--(int){
			const_reverse_iterator	tmp(*this);

			this->p = this->p + static_cast<size_t>(1);

			return tmp;
		}

		virtual bool	operator<(const_reverse_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) < static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator<(reverse_iterator<typename ft::remove_const<value_type>::type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) < const_cast<const value_type *>(static_cast<value_type *>(cmp.getPoint() ) ) );
		}

		virtual bool	operator>(const_reverse_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) > static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator>(reverse_iterator<typename ft::remove_const<value_type>::type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) > const_cast<const value_type *>(static_cast<value_type *>(cmp.getPoint() ) ) );
		}

		virtual bool	operator<=(const_reverse_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) <= static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator<=(reverse_iterator<typename ft::remove_const<value_type>::type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) <= const_cast<const value_type *>(static_cast<value_type *>(cmp.getPoint() ) ) );
		}

		virtual bool	operator>=(const_reverse_iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) >= static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator>=(reverse_iterator<typename ft::remove_const<value_type>::type, dstruct> const & cmp) const{
			return (static_cast<value_type *>(this->p) >= const_cast<const value_type *>(static_cast<value_type *>(cmp.getPoint() ) ) );
		}

		virtual value_type &	operator[](difference_type n){
			return *(this->p - n);
		}

		virtual const value_type &	operator[](difference_type n) const{
			return *(this->p - n);
		}

		const_reverse_iterator &	operator-=(difference_type n){
			this->p = this->p + n;

			return *this;
		}

		const_reverse_iterator &	operator+=(difference_type n){
			this->p = this->p - n;

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
	typedef typename Iterator::difference_type difference_type;
	typedef typename Iterator::value_type value_type;
	typedef typename Iterator::pointer pointer;
	typedef typename Iterator::reference reference;
	typedef typename Iterator::iterator_category iterator_category;
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

#pragma region Template Pointer
template<typename value_type, class dstruct>
class tpointer{
	public:
		typedef value_type * pointer;
		typedef const value_type	c_type;
		
		tpointer(short def = 0) : _p(NULL){
			(void)def;
		}
		
		tpointer(tpointer<value_type, dstruct> const & cpy) : _p(cpy._p){
			return;
		}

		tpointer(ft::vector<value_type> *container, short foo = 0){
			(void)foo;
			if (container)
				this->_p = &(container->front());
			else
				this->_p = NULL;

			return;
		}

		tpointer(value_type *val, short foo = 0) : _p(val){
			(void)foo;
			return;
		}

		tpointer &	operator=(tpointer const & asn){
			this->_p = asn._p;

			return (*this);
		}

		tpointer &	operator=(value_type *asn){
			if (asn)
				this->_p = asn;

			return (*this);
		}

		// operator c_type*(){
		// 	return const_cast<const value_type *>(this->_p);
		// }

		operator value_type*(){
			return const_cast<typename ft::remove_const<value_type>::type *>(this->_p);
		}

		operator value_type*() const{
			return const_cast<value_type *>(this->_p);
		}

		// operator c_type*() const{
		// 	return const_cast<const value_type *>(this->_p);
		// }

		// operator c_type*() const{
		// 	return const_cast<const value_type *>(this->_p);
		// }
	private:
		value_type	*_p;
};

template<typename value_type>
class tpointer<value_type, class RBtree<value_type> >{
	typedef tpointer<value_type, RBtree<value_type> > point;
	typedef typename RBtree<value_type>::nodeType nodeType;

	public:
		tpointer(short end = 0) : _p(NULL), _end(end){

			return;
		}

		tpointer(nodeType *node, short end = 0) : _p(node), _end(end){

			return;
		}

		tpointer(point const & cpy, short end = 0) : _p(cpy._p), _end(end){

			return;
		}

		tpointer(RBtree<value_type> *cpy, short end = 0) : _end(end){
			if (cpy == NULL)
				this->_p = NULL;
			else
				this->_p = cpy->getRoot();

			return;
		}

		nodeType	*getNode(void) const{
			if (this->getEnd() != 0)
				return NULL;
			return (this->_p);
		}

		short	getEnd(void) const{
			return (this->_end);
		}

		operator value_type*() const{
			if (this->_p == NULL || this->_end)
				return NULL;
			return (this->_p->getVal());
		}

		point &	operator=(point const & asn){
			this->_p = asn._p;
			this->_end = asn._end;
			
			return (*this);
		}

		point &	operator=(nodeType *asn){
			this->_p = asn;

			return (*this);
		}

		point & operator=(RBtree<value_type> *asn){
			if (asn)
				this->_p = asn->getRoot();

			return (*this);
		}

		point	operator+(long	add) const{
			return (this->operator+(static_cast<size_t>(add) ) ); 
		}

		point	operator-(long	sub) const{
			return (this->operator-(static_cast<size_t>(sub) ) ); 
		}

		point	operator+(size_t	add) const{
			nodeType	*tmp = this->_p;
			nodeType	*(*func)(nodeType *);
			short		isBeg(this->_end == 2);
			
			if (add > 0)
			{
				add -= (this->_end == 2);
				isBeg = 0;
			}

			if (add < 0)
				func = RBtree<value_type>::findPrev;
			else if (add >= 0)
				func = RBtree<value_type>::findNext;
			
			for (int i = labs(static_cast<long>(add)); tmp && i > 0; i--)
				tmp = func(tmp);

			return point(tmp, (tmp == NULL) + (tmp != NULL) * isBeg);
		}

		point	operator-(size_t	sub) const{
			nodeType	*tmp = this->_p;
			nodeType	*(*func)(nodeType *);
			short		isEnd(this->_end == 1);

			if (sub > 0)
			{
				sub -= this->_end == 1;
				isEnd = 0;
			}

			if (sub < 0)
				func = RBtree<value_type>::findNext;
			else if (sub >= 0)
				func = RBtree<value_type>::findPrev;
			
			for (int i = labs(static_cast<long>(sub)); tmp && i > 0; i--)
				tmp = func(tmp);

			return point(tmp, (tmp == NULL) * 2 + (tmp != NULL) * isEnd);
		}

		size_t	operator-(point const & sub) const{
			if (!this->_p)
				throw std::exception();

			point tmp(*this);
			size_t	i;

			for(i = 0; tmp._p != sub._p; i++)
				tmp = tmp - static_cast<size_t>(1);

			return i + (this->_end == 1) + (tmp._end == 2);
		}

		// tpointer<value_type, RBtree<value_type> >	operator-(size_t	sub) const{
		// 	iterator tmp;

		// 	if (sub < 0)
		// 		tmp.p = this->_p + (sub * (-1));
		// 	else if (sub >= 0)
		// 		tmp.p = this->_p - sub;
			
		// 	return tmp;
		// }

	private:
		nodeType	*_p;
		short		_end;
};


#pragma endregion

}