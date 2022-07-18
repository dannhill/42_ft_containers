#pragma once
#include "ft_type_traits.hpp"
namespace ft
{

#pragma region Pair
template <class T1, class T2>
struct pair{
	public:
		typedef T1 first_type;
		typedef T2 second_type;

		pair(void){return;}

		pair(const pair<T1, T2> & pr) : first(pr.first), second(pr.second){

			return;
		}
	
		pair(const first_type & a, const second_type & b) : first(a), second(b){

			return;
		}

		// operator pair<const first_type, second_type>(){
		// 	return (pair<const first_type, second_type>(const first_type, second_type) );
		// }

		//temporarily removed const qualifier. Must change pair allocation to dynamic in RBT nodes and tree
		pair & operator=(const pair& pr){
			const_cast<typename ft::remove_const<first_type>::type &>(this->first) = pr.first;
			const_cast<typename ft::remove_const<second_type>::type &>(this->second) = pr.second;

			return (*this);
		}

		first_type	first;
		second_type	second;
};

template <class T1, class T2>
bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
	if (lhs.first == rhs.first)
		if (lhs.second == rhs.second)
			return true;
	return false;
}

template <class T1, class T2>
bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
	return !(lhs == rhs);
}

template <class T1, class T2>
bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
	if (lhs.first < rhs.first)
		return true;
	else if (lhs.first == rhs.first && lhs.second < rhs.second)
		return true;
	else
		return false;
}

template <class T1, class T2>
bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
	return !(rhs < lhs);
}

template <class T1, class T2>
bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
	return (rhs < lhs);
}

template <class T1, class T2>
bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
	return !(lhs < rhs);
}
#pragma endregion

#pragma region make_pair
template <class T1,class T2>
pair<T1,T2> make_pair(T1 x, T2 y){
	return ( pair<T1,T2>(x,y) );
}
#pragma endregion

}