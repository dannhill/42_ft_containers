#pragma once

namespace ft
{

#pragma region integral_constant

template<class T, T v>
struct integral_constant{
	static const T value = v;
	typedef T value_type;
	typedef integral_constant<T,v> type;
	const T operatorT(void){return v;}
};

typedef integral_constant<bool,true> true_type;
typedef integral_constant<bool,false> false_type;

#pragma endregion

#pragma region is_integral
template<class T>
struct is_integral : public integral_constant<bool, false>{
	using typename integral_constant<bool, false>::value_type;
	using typename integral_constant<bool, false>::type;
	static const value_type	value = integral_constant<bool, false>::value;

	operator value_type(void) const{
		return value;
	}
};

template<>
struct is_integral<bool> : public integral_constant<bool, true>{
	using typename integral_constant<bool, true>::value_type;
	using typename integral_constant<bool, true>::type;
	static const value_type	value = integral_constant<bool, true>::value;

	operator value_type(void) const{
		return value;
	}
};

template<>
struct is_integral<char> : public integral_constant<bool, true>{
	using typename integral_constant<bool, true>::value_type;
	using typename integral_constant<bool, true>::type;
	static const value_type	value = integral_constant<bool, true>::value;

	operator value_type(void) const{
		return value;
	}
};

//++++++++++++++++++++++++++C++11 specification++++++++++++++++++++++++++++++++++++++++++
// template<>
// struct is_integral<char16_t> : public integral_constant<bool, true>{
// 	using typename integral_constant<bool, true>::value_type;
// 	using typename integral_constant<bool, true>::type;
// 	static const value_type	value = integral_constant<bool, true>::value;

// 	operator value_type(void) const{
// 		return value;
// 	}
// };

// template<>
// struct is_integral<char32_t> : public integral_constant<bool, true>{
// 	using typename integral_constant<bool, true>::value_type;
// 	using typename integral_constant<bool, true>::type;
// 	static const value_type	value = integral_constant<bool, true>::value;

// 	operator value_type(void) const{
// 		return value;
// 	}
// };

template<>
struct is_integral<wchar_t> : public integral_constant<bool, true>{
	using typename integral_constant<bool, true>::value_type;
	using typename integral_constant<bool, true>::type;
	static const value_type	value = integral_constant<bool, true>::value;

	operator value_type(void) const{
		return value;
	}
};

template<>
struct is_integral<signed char> : public integral_constant<bool, true>{
	using typename integral_constant<bool, true>::value_type;
	using typename integral_constant<bool, true>::type;
	static const value_type	value = integral_constant<bool, true>::value;

	operator value_type(void) const{
		return value;
	}
};

template<>
struct is_integral<short int> : public integral_constant<bool, true>{
	using typename integral_constant<bool, true>::value_type;
	using typename integral_constant<bool, true>::type;
	static const value_type	value = integral_constant<bool, true>::value;

	operator value_type(void) const{
		return value;
	}
};

template<>
struct is_integral<int> : public integral_constant<bool, true>{
	using typename integral_constant<bool, true>::value_type;
	using typename integral_constant<bool, true>::type;
	static const value_type	value = integral_constant<bool, true>::value;

	operator value_type(void) const{
		return value;
	}
};

template<>
struct is_integral<long int> : public integral_constant<bool, true>{
	using typename integral_constant<bool, true>::value_type;
	using typename integral_constant<bool, true>::type;
	static const value_type	value = integral_constant<bool, true>::value;

	operator value_type(void) const{
		return value;
	}
};

template<>
struct is_integral<long long int> : public integral_constant<bool, true>{
	using typename integral_constant<bool, true>::value_type;
	using typename integral_constant<bool, true>::type;
	static const value_type	value = integral_constant<bool, true>::value;

	operator value_type(void) const{
		return value;
	}
};

template<>
struct is_integral<unsigned char> : public integral_constant<bool, true>{
	using typename integral_constant<bool, true>::value_type;
	using typename integral_constant<bool, true>::type;
	static const value_type	value = integral_constant<bool, true>::value;

	operator value_type(void) const{
		return value;
	}
};

template<>
struct is_integral<unsigned short int> : public integral_constant<bool, true>{
	using typename integral_constant<bool, true>::value_type;
	using typename integral_constant<bool, true>::type;
	static const value_type	value = integral_constant<bool, true>::value;

	operator value_type(void) const{
		return value;
	}
};

template<>
struct is_integral<unsigned int> : public integral_constant<bool, true>{
	using typename integral_constant<bool, true>::value_type;
	using typename integral_constant<bool, true>::type;
	static const value_type	value = integral_constant<bool, true>::value;

	operator value_type(void) const{
		return value;
	}
};

template<>
struct is_integral<unsigned long int> : public integral_constant<bool, true>{
	using typename integral_constant<bool, true>::value_type;
	using typename integral_constant<bool, true>::type;
	static const value_type	value = integral_constant<bool, true>::value;

	operator value_type(void) const{
		return value;
	}
};

template<>
struct is_integral<unsigned long long int> : public integral_constant<bool, true>{
	using typename integral_constant<bool, true>::value_type;
	using typename integral_constant<bool, true>::type;
	static const value_type	value = integral_constant<bool, true>::value;

	operator value_type(void) const{
		return value;
	}
};

#pragma endregion

#pragma region enable_if
template<bool Cond, class T = void> struct enable_if {};
template<class T> struct enable_if<true, T> { typedef T type; };
#pragma endregion

#pragma region disable_if
template<bool Cond, class T = void> struct disable_if {};
template<class T> struct disable_if<false, T> { typedef T type; };
#pragma endregion

#pragma region remove_const
template< class T > struct remove_const                { typedef T type; };
template< class T > struct remove_const<const T>       { typedef T type; };
#pragma endregion

#pragma region is_same
template<class T, class U>
struct is_same : false_type {};
 
template<class T>
struct is_same<T, T> : true_type {};
#pragma endregion

}