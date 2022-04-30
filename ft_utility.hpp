#pragma once

namespace ft
{

#pragma region Pair
template <class T1, class T2>
struct pair{
	public:
		typedef T1 first_type;
		typedef T2 second_type;

		pair(void){return;}

		pair(const pair<T1, T2> & pr){
			this->first = pr.first;
			this->second = pr.second;

			return;
		}
	
		pair(const first_type & a, const second_type & b){
			this->first = a;
			this->second = b;

			return;
		}


		pair & operator=(const pair& pr){
			this->first = pr.first;
			this->second = pr.second;

			return;
		}

		first_type	first;
		second_type	second;
};

template <class T1, class T2>
bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
	if (lhs.first == rhs.first)
		if (lhs.second == rhs.second)
			return true;
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