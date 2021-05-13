#include <algorithm>
#include "bstree.hpp"
#include <iostream>


int main()
{
    BSTree<int,const char*> bst;
    bst.insert(50,"a");
    bst.insert(30,"b");
    bst.insert(20,"c");
    bst.insert(40,"d");
    bst.insert(70,"e");
    bst.insert(60,"f");
    bst.insert(80,"g");
    std::cout << "Inorder traversal as follows :\n";
    bst.print(INORDER);
    std::cout << '\n';
    std::cout << "Total number of nodes are:";
    std::cout << bst.totalcount() << "\n\n";
    // // Implemented
    std::cout << "Maximum element is:" << (*bst.max_element()).key << "\n";
    std::cout << "Minimum element is:" << (*bst.min_element()).key << "\n";
    std::cout << "\n";

    std::cout << "Inorder traversal as follows :\n";
    bst.print(INORDER);
    std::cout << "\n";

    std::cout << "Printing in reverse order :\n";
    auto it = bst.end();
    --it;
    while(it != bst.begin())
    {
        std::cout << (*it).key << "\t";
        --it;
    }
    std::cout << (*it).key;
    std::cout << "\n\n";

    std::cout << "Iterating through all nodes from beginning to the end of the tree by inorder traversal:" << std::endl;
    BSTree<int, const char*>::iterator i = bst.begin();
    while(i != bst.end()) {
        std::cout << "[" << (*i).key << ", " << (*i).data << "] ";
        i++;
    }
    std::cout<<"\n";
    std::cout << "Testing the findNode function used for searching a node by a given key :\n";
    auto itf = bst.findNode(150);
    if(itf)
    {
        std::cout << itf->key << " found\n\n";
    }
    else
    {
        std::cout << 150 <<" not found\n\n";
    }

    auto itnew=bst.findNode(40);
    if(itnew)
    {
        std::cout << itnew->key << " found\n\n";
    }
    else
    {
        std::cout << 40 <<" not found\n\n";
    }
    std::cout << "Inorder traversal as follows :\n";
    bst.print(INORDER);
    std::cout << "Preorder traversal as follows :\n";
    bst.print(PREORDER);
    std::cout << "Postorder traversal as follows :\n";
    bst.print(POSTORDER);

    std::cout << "\n";
   
    std::cout << "Leafcount: " << bst.leafcount() << "\n";
    std::cout << "Height: " << bst.height() << "\n\n";
    std::cout << "Now testing upper and lower bound functions :\n";
    BSTree<int,const char*>::iterator itnn= bst.lower_bound(40);
    std::cout << "Lower bound of 40 is: " << (*itnn).key << "\n\n";
     BSTree<int,const char*>::iterator itr= bst.lower_bound(10);
    std::cout << "As lower bound is not possible for 10 so Lowest value returned is: " << (*itr).key << "\n\n";
     BSTree<int,const char*>::iterator itrn= bst.upper_bound(65);
    std::cout << "Upper bound of 65 is: " << (*itrn).key << "\n\n";
     BSTree<int,const char*>::iterator itro= bst.upper_bound(100);
    std::cout << "As upper bound is not possible for 100 so Highest value returned is: " << (*itro).key << "\n\n";
    std::cout << "Now testing deletion :\n";
    bool b=bst.del(20);
    if(b){
        std::cout << "deletion successful!!!!\n";
    }
    else{
        std::cout << "deletion failed!!!!\n";
    }
    std::cout << "After removing 20 inorder traversal is" <<"\n";
    bst.print(INORDER);
    std::cout << "Leafcount: " << bst.leafcount() << "\n";
    std::cout << "Height: " << bst.height() << "\n\n";
     bool c=bst.del(30);
     if(c){
        std::cout << "deletion successful!!!!\n";
    }
    else{
        std::cout << "deletion failed!!!!\n";
    }
    std::cout << "After removing 30 inorder traversal is" <<"\n";
    bst.print(INORDER);
    std::cout << "Leafcount: " << bst.leafcount() << "\n";
    std::cout << "Height: " << bst.height() << "\n\n";
   bool d=bst.del(50);
    if(d){
        std::cout << "deletion successful!!!!\n";
    }
    else{
        std::cout << "deletion failed!!!!\n";
    }
    std::cout << "After removing 50 inorder traversal is" <<"\n";
    bst.print(INORDER);
    std::cout << "Leafcount: " << bst.leafcount() << "\n";
    std::cout << "Height: " << bst.height() << "\n\n";
    std::cout << "Now again trying to delete 50 :\n";
    bool e=bst.del(50);
    if(e){
        std::cout << "deletion successful!!!!\n";
    }
    else{
        std::cout << "deletion failed!!!!\n";
    }
  std::cout << "Now testing move assignment operator, move constructor,copy assignment operator and copy constructor :\n";
   BSTree<int,const char*> bst1;
   bst1=std::move(bst);
   bst1.print(INORDER);
   BSTree<int,const char*> bst3(std::move(bst1));
   bst3.print(INORDER);
   BSTree<int,const char*> bst2;
   bst2=bst3;
   bst2.print(INORDER);
   BSTree<int,const char*> bst4(bst2);
   bst4.print(INORDER);
    return 0;
}

