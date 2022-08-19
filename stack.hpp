#include "vector.hpp"

namespace ft
{

	template <class T, class Container = vector<T> >
	class stack;

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	
	template <class T, class Container>
	bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	
	template <class T, class Container>
	bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

template <class T, class Container>
class stack{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

		explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {
			return;
		}
	
		bool empty() const{
			return (this->c.empty() );
		}

		size_type size() const{
			return (this->c.size() );
		}

		value_type& top(){
			return (this->c.back() );
		}

		const value_type& top() const{
			return (this->c.back() );
		}

		void push (const value_type& val){
			return (this->c.push_back(val) );
		}

		void pop(){
			return (this->c.pop_back() );
		}
	protected:
		container_type	c;

		template <class U, class Cont>
		friend bool operator== (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

		template <class U, class Cont>
		friend bool operator!= (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

		template <class U, class Cont>
		friend bool operator< (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

		template <class U, class Cont>
		friend bool operator<= (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

		template <class U, class Cont>
		friend bool operator> (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

		template <class U, class Cont>
		friend bool operator>= (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

};

template <class U, class Cont>
bool operator== (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs){

	return (lhs.c == rhs.c);
}

template <class U, class Cont>
bool operator!= (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs){

	return (lhs.c != rhs.c);
}

template <class U, class Cont>
bool operator< (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs){

	return (lhs.c < rhs.c);
}

template <class U, class Cont>
bool operator<= (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs){

	return (lhs.c <= rhs.c);
}

template <class U, class Cont>
bool operator> (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs){

	return (lhs.c > rhs.c);
}

template <class U, class Cont>
bool operator>= (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs){

	return (lhs.c >= rhs.c);
}

}