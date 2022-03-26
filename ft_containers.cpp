#include "ft_vector.hpp"
#include <vector>
#include <iostream>

using namespace std;

int	main(void){
	ft::vector<int>	vec(10);
	ft::vector<int>	gianni(0);

	cout << vec.capacity() << endl;
	cout << vec.size() << endl;
	cout << vec.max_size() << endl;
	cout << boolalpha << vec.empty() << endl;
	vec.reserve(35);
	vec.assign(10, 22);
	vec.pop_back();
	vec.begin();
	vec.end();
	// vec.resize(99999999999);

	cout << endl;

	cout << vec.capacity() << endl;
	cout << vec.size() << endl;
	cout << vec.max_size() << endl;
	cout << boolalpha << vec.empty() << endl;

	for (size_t i(0); i < vec.size(); i++)
		cout << vec[i] << endl;

	cout << endl;

}
