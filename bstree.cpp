#include <iostream>
#include "bstree.hpp"
#include "student.h"

/*
*
********* BSTREE CLASS
*   
********* Public Methods   
*
*/

/*
*   Function: Destructor
*   
*   Description: Destroys the tree by freeing all nodes it possesses
*
*/
template <typename TKey, typename TVal,typename Pred> BSTree<TKey, TVal,Pred>::~BSTree() {
    _deleteTree(root);
}

// copy constructor
template <typename TKey, typename TVal,typename Pred> BSTree<TKey, TVal,Pred>::BSTree(const BSTree& rhs) {
    std::cout<<"copy constructor called\n";
 //helper function to deep copy 
  root = copyHelper(rhs.root);
}

//helper function doing deep copy
template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::node* BSTree<TKey, TVal,Pred>::copyHelper(const node *toCopy){
    if (toCopy == NULL)
		return NULL;
	node* copyNode = _newNode(toCopy->key, toCopy->data);
	copyNode->left = copyHelper(toCopy->left);
	copyNode->right = copyHelper(toCopy->right);
	return copyNode;
}

//move constructor
template <typename TKey, typename TVal,typename Pred> BSTree<TKey, TVal,Pred>::BSTree(BSTree&& rhs) {
    std::cout<<"move constructor called\n";
    _deleteTree(root);
    root = rhs.root;
	rhs.root = nullptr;
}

/*
*   Function: insert
*   @param1: TKey key : Lookup key.
*   @param2: TVal data : The data which the key leads to.
*   @returns: void
*   
*   Description: This function inserts the specified data (@param2) to the binary search tree
*                and uses the key (@param1) to determine the node's location.
*
*/
template <typename TKey, typename TVal,typename Pred> void BSTree<TKey, TVal,Pred>::insert(TKey key, TVal data) {

    // If the BSTree is empty, create the node at the root.
    if(!root) {
        root = _newNode(key, data);

    } else {

        BSTree<TKey, TVal,Pred>::node** current = &root, *parent = NULL;

        // Loop until an empty slot is found in the tree
        while(*current) {

            parent = *current;

            if(pred(key,(*current)->key)) {
                current = &parent->left;
            } else {
                current = &parent->right;
            }
        }
        // Empty slot is found, fill it with the given parameters.
        *current = _newNode(key,data);
        (*current)->parent = parent;
    }
}


/*
*   Function: del
*   @param1: TKey key : Lookup key.
*   @returns: true if successful, false otherwise.
*   
*   Description: This function finds and deletes the desired node from the 
*                binary search tree using the given lookup key (@param1).
*
*/
template <typename TKey, typename TVal,typename Pred> bool BSTree<TKey, TVal,Pred>::del(TKey key) {

    // Check if the binary search tree is not empty.
    if(!root) {
        return false;
    }

    BSTree<TKey, TVal,Pred>::node** current = &root;

    // Loop until the node with given key is found, 
    // or until there are no nodes left to look for. 
    while(*current && (*current)->key != key) {

        if(pred (key, (*current)->key)) {
            current = &(*current)->left;
        } 
        else {
            current = &(*current)->right;
        }
    }
    // Check if the end of the tree is reached.
    if(!*current) {
        return false;
    }
    // If not then the desired node is found.


    // If the left and the right nodes are both present,
    // find the leftmost (smallest) node in the right subtree
    // and copy the contents to the node that will be deleted.
    if((*current)->left!=NULL && (*current)->right!=NULL){
        BSTree<TKey, TVal,Pred>::node** temp = &(*current)->right;

        while((*temp)->left) temp = &(*temp)->left;

        (*current)->data = (*temp)->data;
        (*current)->key = (*temp)->key;

        // Delete the copied node.
        BSTree<TKey, TVal,Pred>::node* ptrToFree = *temp;
        *temp = (*temp)->right;
        delete ptrToFree;
    }
    // If the left node is empty, move the right node
    // to the current node.
    else if((*current)->left==NULL) {
        if((*current)->right!=NULL) {
            (*current)->right->parent = (*current)->parent;
           // (*current)->parent->left=(*current)->right;
        }
        BSTree<TKey, TVal,Pred>::node* ptrToFree = *current;
        *current = (*current)->right;
        delete ptrToFree;
        
    }
    // If the right node is empty, move the left node
    // to the current node.
    else if((*current)->right==NULL) {
        if((*current)->left!=NULL) {
            (*current)->left->parent = (*current)->parent;
            //(*current)->parent->right=(*current)->left;
        }
        BSTree<TKey, TVal,Pred>::node* ptrToFree = *current;
        *current = (*current)->left;
        delete ptrToFree;
    }
    

    return true;

}
// Same as del
template <typename TKey, typename TVal,typename Pred> bool BSTree<TKey, TVal,Pred>::remove(TKey key) {

    return del(key);

}
/*
*   Function: print
*   @param1: TRAVERSAL_METHOD t : Method to be used to print the tree (inorder, preorder, postorder)
*   @returns: void
*   
*   Description: This function prints the values inside the binary search tree
*                to the stdout with desired order (@param1).
*
*/
template <typename TKey, typename TVal,typename Pred> void BSTree<TKey, TVal,Pred>::print(TRAVERSAL_METHOD t) {
    switch(t) {
        case INORDER : {
            _printInOrder(root);
            break;
        }
        case PREORDER : {
            _printPreOrder(root);
            break;
        }
        case POSTORDER : {
            _printPostOrder(root);
            break;
        }
    }
    std::cout << std::endl;
}
/*
*   Function: has
*   @param1: TKey key : Lookup key.
*   @returns: true if found, false otherwise.
*   
*   Description: This function checks if the binary search tree
*                has a node with the given key (@param1).
*
*/
template <typename TKey, typename TVal,typename Pred> bool BSTree<TKey, TVal,Pred>::has(TKey key) {

    BSTree<TKey, TVal,Pred>::node* current = root;

    // Loop until there are no nodes left to check.
    while(current) {
        // If the current key equals to the search key (@param1), the node is found; return
        if(key == current->key) {
            return true;
        }
        if(pred(key , current->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return false;
    
}
/*
*   Function: findNode
*   @param1: TKey key : Lookup key.
*   @returns: The read-only reference of the node with given key.
*   
*   Description: This function finds the node with given key (@param1) and
*                returns its read-only reference.
*
*/
template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::node* BSTree<TKey, TVal,Pred>::findNode(TKey key) {

    // Same procedure with function "has"
    BSTree<TKey, TVal,Pred>::node* current = root;
    
    while(current) {
        if(key == current->key) {
            return current;
        }
        if(pred(key , current->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL;
}
/*
*   Function: getVal
*   @param1: TKey key : Lookup key.
*   @returns: The read-only reference of the data that the key leads to.
*   
*   Description: This function finds the node with given key (@param1) and
*                returns its data field's read-only reference.
*
*/
template <typename TKey, typename TVal,typename Pred> const TVal* BSTree<TKey, TVal,Pred>::getVal(TKey key) {
    
    // Same procedure with function "has"
    BSTree<TKey, TVal,Pred>::node* current = root;

    while(current) {
        if(key == current->key) {
            return &(current->data);
        }
        if(pred(key , current->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL;
}
/*
*   Function: change
*   @param1: TKey key : Lookup key.
*   @param2: TVal data : New data to change to.
*   @returns: true if successful, false otherwise.
*   
*   Description: This function finds the node with given key (@param1) and
*                changes its data field with the given data (@param2).
*
*/
template <typename TKey, typename TVal,typename Pred> bool BSTree<TKey, TVal,Pred>::change(TKey key, TVal data) {

    BSTree<TKey, TVal,Pred>::node** current = &root;

    // Loop until there are no nodes left to check.
    while(*current) {
        // If the current key equals to the search key (@param1),
        // change the node's data to the given data (@param2).
        if(key == (*current)->key) {
            (*current)->data = data;
            return true;
        }

        if(pred(key , (*current)->key)) {
            current = &(*current)->left;
        } else {
            current = &(*current)->right;
        }
    }
    return false;
}

//totalcount gives the total number of nodes
template <typename TKey, typename TVal,typename Pred> int BSTree<TKey, TVal,Pred>::totalcount() {
    return _totalcount(root);
}

//leafcount gives the total number of leafnodes
template <typename TKey, typename TVal,typename Pred> int BSTree<TKey, TVal,Pred>::leafcount() {
    return _leafcount(root);
}

//returns height of the tree
template <typename TKey, typename TVal,typename Pred> int BSTree<TKey, TVal,Pred>::height() {
    return _height(root);
}

//returns the iterator to the minimum element
template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::iterator BSTree<TKey, TVal,Pred>::min_element() {
    return iterator(_min(root),this);
}

//returns the iterator to the maximum element
template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::iterator BSTree<TKey, TVal,Pred>::max_element() {
    return iterator(_max(root),this);
}

//returns iterator to the lower bound of the element
template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::iterator BSTree<TKey, TVal,Pred>::lower_bound(TKey key) {
  
    return iterator(_lower_bound(root,key),this);
}

//returns iterator to the upper bound of the element
template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::iterator BSTree<TKey, TVal,Pred>::upper_bound(TKey key) {
     
    return iterator(_upper_bound(root,key),this);
    
}

/*
*   Function: begin
*   @returns: An inorder BSTree iterator object at the 
*             beginning of the tree (node with smallest key)
*/
template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::iterator BSTree<TKey, TVal,Pred>::begin() {

    BSTree<TKey, TVal,Pred>::node* current = root;

    // Check if the tree is empty
    if(current != NULL) {
        // If it's not, make the iterator object point to the leftmost node of the tree.
        while(current->left != NULL) current = current->left;
    }

    // Create the object with the private constructor and return it.
    // If the tree is empty, the iterator will point to the end of the tree (which is NULL).
    return iterator(current,this);

}
/*
*   Function: begin (overload)
*   @param1: int start : Offset
*   @returns: An inorder BSTree iterator object that points to the node 
*             at the given position (@param1) in the tree.
*/
template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::iterator BSTree<TKey, TVal,Pred>::begin(int start) {

    // Create an iterator that points to the first element.
    BSTree<TKey, TVal,Pred>::iterator temp = this->begin();
    
    // Iterate by desired amount (@param1).
    int i=0;
    while(i<start && temp != this->end()) {
        temp++;
        i++;
    }
    // Return it at the current position.
    return temp;
}
/*
*   Function: rbegin
*   @returns: An inorder BSTree iterator object that points to the
*             last node in the tree (node with greatest key).
*
*   Description: rbegin = reverse begin.
*/
template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::iterator BSTree<TKey, TVal,Pred>::rbegin() {

    BSTree<TKey, TVal,Pred>::node* current = root;
    
    if(current != NULL) {
        // Find the rightmost element
        while(current->right != NULL) current = current->right;
    }

    return iterator(current,this);

}

/*
*   Function: end
*   @returns: An inorder BSTree iterator object at the end of 
*             the tree (an iterator that points to a NULL node).
*
*   Description: Used to compare with other iterators, to represent the end condition.
*/
template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::iterator BSTree<TKey, TVal,Pred>::end() {

    return iterator(NULL,this);

}

/*
*********   Private Methods
*/

/*
*   Creates and initializes a node struct
*/

template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::node* BSTree<TKey, TVal,Pred>::_newNode(TKey key, TVal data) {
    node* newNode = new node;
    newNode->data = data;
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

template <typename TKey, typename TVal,typename Pred> int BSTree<TKey, TVal,Pred>::_totalcount(node* root) {
    
   BSTree<TKey, TVal,Pred>::iterator temp = this->begin();
   if(root==NULL){
       return 0;
   }
   int i=0;
   while(temp!=this->end()){
       temp++;
       i++;
   }
   return i;
}

template <typename TKey, typename TVal,typename Pred> int BSTree<TKey, TVal,Pred>::_leafcount(node* root) {

    if(root==NULL){
        return 0;
    }
    if(root->right==NULL && root->left==NULL){
        return 1;
    }
    else{
       return  _leafcount(root->left) + _leafcount(root->right);
    }
}

template <typename TKey, typename TVal,typename Pred> int BSTree<TKey, TVal,Pred>::_height(node* root) {

    if(root==NULL){
        return -1;
    }
    else{
        int lh=_height(root->left);
        int rh=_height(root->right);
        if(lh>rh){
            return lh+1;
        }
        else{
            return rh+1;
        }
    }
}

template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::node* BSTree<TKey, TVal,Pred>::_min(node* root) {

    BSTree<TKey, TVal,Pred>::node* Node=root;   
    if(Node == nullptr)
        return Node;
    while(Node->left)
        Node = Node->left;
    return Node;
}

template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::node* BSTree<TKey, TVal,Pred>::_max(node* root) {

    BSTree<TKey, TVal,Pred>::node* Node=root;   
    if(Node == nullptr)
        return Node;
    while(Node->right)
        Node = Node->right;
    return Node;
}

template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::node* BSTree<TKey, TVal,Pred>::_lower_bound(node* root,TKey key) {
    if(pred.Type==0){
     BSTree<TKey, TVal,Pred>::iterator first=this->begin(); 
     BSTree<TKey, TVal,Pred>::iterator last=this->end();
     if(key<(*first).key){
             std::cout << "No possible Lowerbound...We are giving you lowest value" << '\n';
             return first.currentNode;
         }
         while(first!=last && (*first).key < key){
             ++first;
         }
        return (--first).currentNode;
    }
    else{
        BSTree<TKey, TVal,Pred>::iterator first=this->end(); 
        BSTree<TKey, TVal,Pred>::iterator last=this->rbegin();
        if(key<(*last).key){
         std::cout << "No possible lower_bound...We are giving you lowest value" << '\n';
         return last.currentNode;
     }
     while(last!=first && (*last).key < key){
         --last;
     }
     return (++last).currentNode;
 
    }
    
}
template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::node* BSTree<TKey, TVal,Pred>::_upper_bound(node* root,TKey key) {
    if(pred.Type==0){
        BSTree<TKey, TVal,Pred>::iterator first=this->end(); 
         BSTree<TKey, TVal,Pred>::iterator last=this->rbegin();
          if(key>(*last).key){
             std::cout << "No possible Upperbound...We are giving you highest value" << '\n';
             return last.currentNode;
         }
         while(last!=first && ((*last).key>key || (*last).key == key)){
             --last;
         }
         return (++last).currentNode;
    }
    else{
        BSTree<TKey, TVal,Pred>::iterator first=this->begin(); 
        BSTree<TKey, TVal,Pred>::iterator last=this->end();
        if(key>(*first).key){
             std::cout << "No possible Upperbound...We are giving you highest value" << '\n';
             return first.currentNode;
         }
         while(first!=last && ((*first).key > key  || (*first).key == key)){
             ++first;
         }
        return (--first).currentNode;

    }
}

/*
*   Destroys the tree with given root by freeing all nodes it possesses recursively
*/

template <typename TKey, typename TVal,typename Pred> void BSTree<TKey, TVal,Pred>::_deleteTree(node* root) {
    if(root != NULL) {
        _deleteTree(root->left);
        _deleteTree(root->right);
        delete root;
    }
}

/*
*   RECURSIVE PRINTERS
*/ 
template <typename TKey, typename TVal,typename Pred> void BSTree<TKey, TVal,Pred>::_printInOrder(node* root) {
    if(root != NULL) {
        _printInOrder(root->left);
        std::cout << root->key << " ";
        _printInOrder(root->right);
    }
}
template <typename TKey, typename TVal,typename Pred> void BSTree<TKey, TVal,Pred>::_printPreOrder(node* root) {
    if(root != NULL) {
        std::cout << root->key << " ";
        _printPreOrder(root->left);
        _printPreOrder(root->right);
    }
}
template <typename TKey, typename TVal,typename Pred> void BSTree<TKey, TVal,Pred>::_printPostOrder(node* root) {
    if(root != NULL) {
        _printPostOrder(root->left);
        _printPostOrder(root->right);
        std::cout << root->key << " ";
    }
}




/*
*
********* BSTREE ITERATOR SUBCLASS
*
*/

template <typename TKey, typename TVal,typename Pred> const TVal BSTree<TKey, TVal,Pred>::iterator::get() {
    return currentNode->data;
}

template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::iterator& BSTree<TKey, TVal,Pred>::iterator::operator= (const iterator& rhs) {

    this->currentNode = rhs.currentNode;
    this->tree = rhs.tree;
    return *this;

}

// PRE-INCREMENT
template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::iterator& BSTree<TKey, TVal,Pred>::iterator::operator++ () {

    if(currentNode == NULL) {
            currentNode = tree->root;
            // If it is still NULL, then the tree is empty.

            while( currentNode->left != NULL)  currentNode =  currentNode->left;
       
    } else {
        // if node at right exists then tale the leftmost value from the subtree whose node is right else if no tree is present right will be currentnode
        if(currentNode->right != NULL) {
            currentNode = currentNode->right;
            while(currentNode->left != NULL) {
                currentNode = currentNode->left;
            }
        //go to the root value which will be the next biggest value after it, if node is in left subtree of parent then its parent 
        //is the desired root and if it is in right subtree of parent then it means its bigger than parent node
        // so the we travese up to find the parent node which is the actual inorder successor of the currentnode and then make it the current node
        } else {
            BSTree<TKey, TVal,Pred>::node* parent = currentNode->parent;
            while(parent != NULL && currentNode != parent->left) {
                currentNode = parent;
                parent = parent->parent;
            }
            currentNode = parent;
        }
    }


    return *this;
}

// POST-INCREMENT
template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::iterator BSTree<TKey, TVal,Pred>::iterator::operator++ (int) {

    BSTree<TKey, TVal,Pred>::iterator temp = *this;

   ++(*this); 
   
    return temp;
}

// PRE-DECREMENT
template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::iterator& BSTree<TKey, TVal,Pred>::iterator::operator-- () {

    if(currentNode == NULL) {
            currentNode = tree->root;
            // If it is still NULL, then the tree is empty.

            // Go to the rightmost leaf.
            while( currentNode->right != NULL)  currentNode =  currentNode->right;
        
    } else {
       //if left node is present then take the largest value in left subtree that is the actual inorder predecessor
       //if left node doesnt have a subtree then the left node will be the currentnode
        if(currentNode->left != NULL) {
            currentNode = currentNode->left;
            while(currentNode->right != NULL) {
                currentNode = currentNode->right;
            }
        //if no node in left node then go to next smallest value and if the desired node is in the right subtree of the parent node and is its leftmost value then
        // traverse up to the next smallest nroot node that is parent which is its inorder predecessor 
        //and if node is the only node to the right of parent then its parent is its inorder predecessor
        } else {
            BSTree<TKey, TVal,Pred>::node* parent = currentNode->parent;
            while(parent != NULL && currentNode != parent->right) {
                currentNode = parent;
                parent = parent->parent;
            }
            currentNode = parent;
        }
    }


    return *this;
}
// POST-DECREMENT
template <typename TKey, typename TVal,typename Pred> typename BSTree<TKey, TVal,Pred>::iterator BSTree<TKey, TVal,Pred>::iterator::operator-- (int) {

    BSTree<TKey, TVal,Pred>::iterator temp = *this;

    --(*this);


    return temp;
}


template <typename TKey, typename TVal,typename Pred> bool BSTree<TKey, TVal,Pred>::iterator::operator== (const BSTree<TKey, TVal,Pred>::iterator& rhs) const {
    return this->currentNode == rhs.currentNode;
}
template <typename TKey, typename TVal,typename Pred> bool BSTree<TKey, TVal,Pred>::iterator::operator!= (const BSTree<TKey, TVal,Pred>::iterator& rhs) const {
    return this->currentNode != rhs.currentNode;
}
template <typename TKey, typename TVal,typename Pred> const typename BSTree<TKey, TVal,Pred>::node& BSTree<TKey, TVal,Pred>::iterator::operator* () const {
    return *(this->currentNode);
}




template class BSTree<int, int>;
template class BSTree<int, const char*>;


template class BSTree<char, int>;
template class BSTree<char, const char*>;

template class BSTree<const char*, int>;
template class BSTree<const char*, const char*>;

template class BSTree<float, const char*>;
template class BSTree<float,int>;
template class BSTree<int,float>;

template class BSTree<Student,int>;



template class BSTree<int, int,Greater>;
template class BSTree<int, const char*,Greater>;


template class BSTree<char, int,Greater>;
template class BSTree<char, const char*,Greater>;

template class BSTree<const char*, int,Greater>;
template class BSTree<const char*, const char*,Greater>;

template class BSTree<float, const char*,Greater>;
template class BSTree<float,int,Greater>;
template class BSTree<int,float,Greater>;

template class BSTree<Student,int,Greater>;

