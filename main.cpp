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
	#include "ft_utility.hpp"
	#include "ft_iterator.hpp"
	#include "rbt.hpp"
	#include "map.hpp"
	#include "vector.hpp"
	#include "ft_type_traits.hpp"
#endif

#include <stdlib.h>
#include <cstdlib>

void	printNode(RBnode<ft::pair<int, std::string> > *node){
	std::cout << node->getVal().first << ": " << node->getColor() << std::endl;
}

void	printNode(RBnode<ft::pair<const int, std::string> > *node){
	std::cout << node->getVal().first << ": " << node->getColor() << std::endl;
}

RBtree<ft::pair<const int, std::string> >	*randomTree(int size){
	RBnode<ft::pair<const int, std::string> >	*root = new RBnode<ft::pair<const int, std::string> >(ft::pair<const int, std::string>(0, "first"), BLACK);
	RBtree<ft::pair<const int, std::string> >	*tree = new RBtree<ft::pair<const int, std::string> >(root);

	for (int i = 1; i < size; i++){
		RBnode<ft::pair<const int, std::string> >	*temp;
		if ((temp = tree->findMax(tree->getRoot()))->getChild(RIGHT) == NIL)
		{
			tree->RBinsert(new RBnode<ft::pair<const int, std::string> >(ft::pair<const int, std::string>(i, "next"), RED), temp, RIGHT);
		}
	}

	return tree;
}

RBtree<const int>	*randomTree(int size, bool con){
	RBnode<const int>	*root = new RBnode<const int>(0, BLACK);
	RBtree<const int>	*tree = new RBtree<const int>(root);
	(void)con;


	for (int i = 1; i < size; i++){
		RBnode<const int>	*temp;
		if ((temp = tree->find(tree->getRoot(), i - 1))->getChild(RIGHT) == NIL)
		{
			tree->RBinsert(new RBnode<const int>(i, RED), temp, RIGHT);
		}
	}

	return tree;
}

int	main(void){
	RBtree<ft::pair<const int, std::string> >	*albero;

	ft::iterator<int>	ite;

	srand(time(NULL));

	albero = randomTree(14);

	albero->RBdelete(albero->find(albero->getRoot(), ft::pair<const int, std::string>(7, "next") ) );

	if (albero->getRoot() != NULL)
		std::cout << "Root: " << albero->getRoot()->getVal().first << std::endl;

	albero->applyFn(albero->getRoot(), printNode);

	ft::iterator<ft::pair<const int, std::string>, RBtree<ft::pair<const int, std::string> > >	kek(albero);

	ft::iterator<ft::pair<const int, std::string>, RBtree<ft::pair<const int, std::string> > >	lel(albero);

	kek -= 3;
	lel += 9;

	std::cout << (lel - kek) << std::endl;

	ft::map<int, std::string>	pippo(kek, lel + 1);

	ft::map<int, std::string>::iterator	itb = pippo.begin();

	// albero->applyFn(pippo.tree->getRoot(), printNode);

	for(; itb != pippo.end() ; itb++)
		std::cout << itb->first << std::endl;

	delete albero;

	return 0;
}
