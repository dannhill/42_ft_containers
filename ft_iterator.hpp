#pragma once
#include <iterator>// library used only for base iterator
#include <cstddef>// library used only to include ptrdiff_t
#include <iostream>// library used only to print debug
#include "rbt.hpp"
#include "vector.hpp"
#include <cmath>

namespace ft
{

#pragma region Forward Declarations
template<typename T, class Alloc = std::allocator<T> >
class vector;

template<typename T, class dstruct = vector<T> >
class const_iterator;

template<typename T, class dstruct = vector<T> >
class iterator;

template<typename T, class dstruct = vector<T> >
class reverse_iterator;

template<typename T, class dstruct = vector<T> >
class const_reverse_iterator;

template<typename value_type, class dstruct>
class tpointer;
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

		iterator(void) : std::iterator<std::random_access_iterator_tag, value_type>(){
			this->p = static_cast<dstruct *>(NULL);

			return;
		}

		iterator(dstruct * container) : std::iterator<std::random_access_iterator_tag, value_type>(){// useful only for red-black tree node pointer. need to modify for vector
			this->p = container;

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
			return (static_cast<value_type *>(this->p) == static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator!=(iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) != static_cast<value_type *>(cmp.p));
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

		virtual bool	operator>(iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) > static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator<=(iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) <= static_cast<value_type *>(cmp.p));
		}

		virtual bool	operator>=(iterator const & cmp) const{
			return (static_cast<value_type *>(this->p) >= static_cast<value_type *>(cmp.p));
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
		tpointer<value_type, dstruct>	p;
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
template<typename T, class dstruct>
class const_iterator : public iterator<T, dstruct>{
	public:
		using typename iterator<T, dstruct>::iterator_category;
		using typename iterator<T, dstruct>::value_type;
		using typename iterator<T, dstruct>::difference_type;
		using typename iterator<T, dstruct>::pointer;
		using typename iterator<T, dstruct>::reference;

		const_iterator(void) : iterator<T, dstruct>(){
			this->p = static_cast<dstruct *>(NULL);

			return;
		}

		const_iterator(dstruct * container) : iterator<T, dstruct>(container){// useful only for red-black tree node pointer. need to modify for vector

			return;
		}

		const_iterator(const_iterator const & cpy) : iterator<T, dstruct>(){
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

		reverse_iterator(dstruct * container) : iterator<T, dstruct>(container){// useful only for red-black tree node pointer. need to modify for vector

			return;
		}

		reverse_iterator(reverse_iterator<T> const & cpy) : iterator<T, dstruct>(cpy){
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

			tmp.p = tmp.p - n;

			return tmp;
		}

		reverse_iterator &	operator++(void){
			this->p = this->p + static_cast<size_t>(1);

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
template<typename T, class dstruct>
class const_reverse_iterator : public const_iterator<const T, dstruct>{
	public:
		using typename ft::const_iterator<const T, dstruct>::iterator_category;
		using typename ft::const_iterator<const T, dstruct>::value_type;
		using typename ft::const_iterator<const T, dstruct>::difference_type;
		using typename ft::const_iterator<const T, dstruct>::pointer;
		using typename ft::const_iterator<const T, dstruct>::reference;

		const_reverse_iterator(void) : const_iterator<const T, dstruct>(){
			return;
		}

		const_reverse_iterator(dstruct * container) : const_iterator<const T, dstruct>(container){// useful only for red-black tree node pointer. need to modify for vector

			return;
		}

		const_reverse_iterator(const_reverse_iterator<const T, dstruct> const & cpy) : const_iterator<const T, dstruct>(cpy){
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
		tpointer(dstruct *container){
			if (container)
				this->p = &(container[0]);
			else
				this->p = NULL;

			return;
		}

		tpointer &	operator=(tpointer const & asn){
			if (asn)
				this->p = &(asn[0]);

			return (*this);
		}

		operator value_type*(){
			return p;
		}
	private:
		value_type	*p;
};

template<typename value_type>
class tpointer<value_type, RBtree<value_type> >{
	typedef tpointer<value_type, RBtree<value_type> > point;
	
	public:
		tpointer<value_type, RBtree<value_type> >(void){
			this->_p = NULL;

			return;
		}

		tpointer<value_type, RBtree<value_type> >(RBnode<value_type> *node){
			this->_p = node;

			return;
		}

		tpointer<value_type, RBtree<value_type> >(point const & cpy){
			this->_p = cpy._p;

			return;
		}

		tpointer<value_type, RBtree<value_type> >(RBtree<value_type> *cpy){
			this->_p = cpy->getRoot();

			return;
		}

		operator value_type*() const{
			if (this->_p == NULL)
				return NULL;
			return &(this->_p->getVal());
		}

		point &	operator=(point const & asn){
			this->_p = asn._p;

			return (*this);
		}

		point &	operator=(RBnode<value_type> *asn){
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
			RBnode<value_type> *tmp = this->_p;
			RBnode<value_type> *(*func)(RBnode<value_type> *);
			
			if (add < 0)
				func = RBtree<value_type>::findPrev;
			else if (add >= 0)
				func = RBtree<value_type>::findNext;
			
			for (int i = labs(static_cast<long>(add)); tmp && i > 0; i--)
				tmp = func(tmp);

			return point(tmp);
		}

		point	operator-(size_t	sub) const{
			RBnode<value_type> *tmp = this->_p;
			RBnode<value_type> *(*func)(RBnode<value_type> *);
			
			if (sub < 0)
				func = RBtree<value_type>::findNext;
			else if (sub >= 0)
				func = RBtree<value_type>::findPrev;
			
			for (int i = labs(static_cast<long>(sub)); tmp && i > 0; i--)
				tmp = func(tmp);

			return point(tmp);
		}

		// tpointer<value_type, RBtree<value_type> >	operator-(size_t	sub) const{
		// 	iterator tmp;

		// 	if (sub < 0)
		// 		tmp.p = this->_p + (sub * (-1));
		// 	else if (sub >= 0)
		// 		tmp.p = this->_p - sub;
			
		// 	return tmp;
		// }

	public:
		RBnode<value_type>	*_p;
};
#pragma endregion

}