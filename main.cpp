#include <iostream>
#include <string>
#include <deque>
#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	// #include <map.hpp>
	// #include <stack.hpp>
	#include <list>
	#include "vector.hpp"
	#include "ft_type_traits.hpp"
#endif

#include <stdlib.h>
#include <cstdlib>
#include "rbt.hpp"

void	printNode(RBnode<int> *node){
	std::cout << node->getVal() << ": " << node->getColor() << std::endl;
}

RBtree<int>	*randomTree(int size){
	RBnode<int>	*root = new RBnode<int>(0, BLACK);
	RBtree<int>	*tree = new RBtree<int>(root);
	


	for (int i = 1; i < size; i++){
		RBnode<int>	*temp;
		if ((temp = tree->find(tree->getRoot(), i - 1))->getChild(RIGHT) == NIL)
		{
			tree->RBinsert(new RBnode<int>(i, RED), temp, RIGHT);
		}
	}

	return tree;
}

int	main(void){
	RBtree<int>	*albero;

	srand(time(NULL));

	albero = randomTree(14);

	albero->RBdelete(albero->find(albero->getRoot(), 7));

	if (albero->getRoot() != NULL)
		std::cout << "Root: " << albero->getRoot()->getVal() << std::endl;

	albero->applyFn(albero->getRoot(), printNode);

	ft::const_reverse_iterator<int, RBtree<int> >	kek(albero);

	ft::const_reverse_iterator<int, RBtree<int> >	lel(albero);

	kek++;

	std::cout << kek[0] << std::endl;

	delete albero;

	return 0;
}
