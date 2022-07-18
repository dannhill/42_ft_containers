#include "containers.hpp"

namespace ft
{

template <class T, class Container = vector<T> >
class stack{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

		explicit stack (const container_type& ctnr = container_type()) : _stack(ctnr) {
			return;
		}
	
		bool empty() const{
			return (this->_stack.empty() );
		}

		size_type size() const{
			return (this->_stack.size() );
		}

		value_type& top(){
			return (this->_stack.back() );
		}

		const value_type& top() const{
			return (this->_stack.back() );
		}

		void push (const value_type& val){
			return (this->_stack.push_back(val) );
		}

		void pop(){
			return (this->_stack.pop_back() );
		}
	private:
		container_type	_stack;

		friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
		friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
		friend bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
		friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
		friend bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
		friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

};

template <class T, class Container>
bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs){

	return (lhs._stack == rhs._stack);
}

template <class T, class Container>
bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){

	return (lhs._stack != rhs._stack);
}

template <class T, class Container>
bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs){

	return (lhs._stack < rhs._stack);
}

template <class T, class Container>
bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){

	return (lhs._stack <= rhs._stack);
}

template <class T, class Container>
bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs){

	return (lhs._stack > rhs._stack);
}

template <class T, class Container>
bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){

	return (lhs._stack >= rhs._stack);
}

}