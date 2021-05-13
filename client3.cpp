#include <algorithm>
#include "bstree.hpp"
#include "student.h"
#include <iostream>

int main()
{	
	//Lets create a bst of students ordered by SRN
	BSTree<Student,int> tree;
	tree.insert(Student("PES1201800002","Bhaskar",7.0),1);
	tree.insert(Student("PES1201800003","Charu",8.0),2);
	tree.insert(Student("PES1201800004","Dinesh",9.0),3);
	tree.insert(Student("PES1201800001","Anil",6.0),4);
	tree.insert(Student("PES1201800005","Edward",10.0),5);

    tree.print(INORDER);
    
	std::cout << "Total number of nodes are:";
    std::cout << tree.totalcount() << "\n\n";
    // // Implemented
    std::cout << "Maximum element is:" << (*tree.max_element()).key << "\n";
    std::cout << "Minimum element is:" << (*tree.min_element()).key << "\n";
    std::cout << "\n";

	std::cout << "Inorder traversal as follows :\n";
    tree.print(INORDER);
    std::cout << "\n";

    std::cout << "Printing in reverse order :\n";
    auto it = tree.end();
    --it;
    while(it != tree.begin())
    {
        std::cout << (*it).key << "\t";
        --it;
    }
    std::cout << (*it).key;
    std::cout << "\n\n";
    
	 std::cout << "Iterating through all nodes from beginning to the end of the tree by inorder traversal:" << std::endl;
    auto i = tree.begin();
    while(i != tree.end()) {
        std::cout << "[" << (*i).key << ", " << (*i).data << "] ";
        i++;
    }
    std::cout<<"\n";
     std::cout << "Testing the findNode function used for searching a node by a given key :\n";
    auto itf = tree.findNode(Student("PES1201800007","Ram",9.0));
    if(itf)
    {
        std::cout << itf->key << " found\n\n";
    }
    else
    {
        std::cout << "PES1201800007 Ram 9.0" <<" not found\n\n";
    }

    auto itnew=tree.findNode(Student("PES1201800002","Bhaskar",7.0));
    if(itnew)
    {
        std::cout << itnew->key << " found\n\n";
    }
    else
    {
        std::cout << "student" <<" not found\n\n";
    }

	std::cout << "Inorder traversal as follows :\n";
    tree.print(INORDER);
    std::cout << "Preorder traversal as follows :\n";
    tree.print(PREORDER);
    std::cout << "Postorder traversal as follows :\n";
    tree.print(POSTORDER);
    std::cout << "\n";
	std::cout << "Leafcount: " << tree.leafcount() << "\n";
    std::cout << "Height: " << tree.height() << "\n\n";
    std::cout << "Now testing upper and lower bound functions :\n";
    auto itnn= tree.lower_bound(Student("PES1201800002","Bhaskar",7.0));
    std::cout << "Lower bound of student PES1201800002 is: " << (*itnn).key << "\n\n";
    auto itr= tree.lower_bound(Student("PES1201800000","Bhaskar",7.0));
    std::cout << "As lower bound is not possible for PES1201800000 so Lowest value returned is: " << (*itr).key << "\n\n";
    auto itrn= tree.upper_bound(Student("PES1201800004","Dinesh",9.0));
    std::cout << "Upper bound of PES1201800004 is: " << (*itrn).key << "\n\n";
    auto itro= tree.upper_bound(Student("PES1201800006","Edward",10.0));
    std::cout << "As upper bound is not possible for PES1201800006 so Highest value returned is: " << (*itro).key << "\n\n";
	bool b=tree.del(Student("PES1201800005","Edward",10.0));
    if(b){
        std::cout << "deletion successful!!!!\n";
    }
    else{
        std::cout << "deletion failed!!!!\n";
    }
    std::cout << "After removing PES1201800005 inorder traversal is" <<"\n";
    tree.print(INORDER);
    std::cout << "Leafcount: " << tree.leafcount() << "\n";
    std::cout << "Height: " << tree.height() << "\n\n";
    bool c=tree.del(Student("PES1201800007","Edward",10.0));
    if(c){
        std::cout << "deletion successful!!!!\n";
    }
    else{
        std::cout << "deletion failed for PES1201800007!!!!\n";
    }
    tree.print(INORDER);
    std::cout << "Leafcount: " << tree.leafcount() << "\n";
    std::cout << "Height: " << tree.height() << "\n\n";
    
	std::cout << "Now testing move assignment operator, move constructor,copy assignment operator and copy constructor :\n";
   BSTree<Student,int> bst1;
   bst1=std::move(tree);
   bst1.print(INORDER);
   BSTree<Student,int> bst3(std::move(bst1));
   bst3.print(INORDER);
   BSTree<Student,int> bst2;
   bst2=bst3;
   bst2.print(INORDER);
   BSTree<Student,int> bst4(bst2);
   bst4.print(INORDER);
    return 0;

}