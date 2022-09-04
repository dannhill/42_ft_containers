#include "vector.hpp"
#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"

int	main(void){
	ft::map<char, int>	mappetta;

	mappetta.insert(ft::make_pair('a', 100));
	mappetta.insert(ft::make_pair('z', 200));
	mappetta.insert(ft::make_pair('z', 500));
	
	ft::map<char, int>::iterator beg = mappetta.begin();

	mappetta.insert(beg, ft::make_pair('b', 300));
	mappetta.insert(beg, ft::make_pair('c', 400));

	ft::map<char, int>::iterator iend = mappetta.end();
	for (ft::map<char, int>::iterator ite = mappetta.begin(); ite != iend; ite++)
		std::cout << ite->first << std::endl;

}