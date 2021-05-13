#include<iostream>
#include<iterator>
#ifndef __bstree_included
#define __bstree_included


enum TRAVERSAL_METHOD {
    INORDER,
    PREORDER,
    POSTORDER
};


class Less
{   public:
        int Type=0;
        template<typename T>
        bool operator()(T a, T b) const
        {
            return a < b;
        }
};

class Greater
{   public:
        int Type=1;
        template<typename T>
        bool operator()(T a, T b) const
        {
            return a > b;
        }
};
template <typename TKey, typename TVal,typename Pred=Less> class BSTree {

    
    public:
        typedef struct node {
            TKey key;
            TVal data;
            struct node* left;
            struct node* right;
            struct node* parent;

        } node;
        
        class iterator {
            public:
                iterator();
                bool operator== (const iterator& rhs) const;
                bool operator!= (const iterator& rhs) const;
                const node& operator* () const;
                iterator& operator= (const iterator& rhs);
                iterator& operator++ ();
                iterator operator++ (int);
                iterator& operator-- ();
                iterator operator-- (int);
                const TVal get();
               typedef ptrdiff_t difference_type; 
			   typedef TKey value_type; 
			   typedef const node& reference; 
			   typedef const node* pointer; 
			   typedef std::bidirectional_iterator_tag iterator_category; 
            private: 
                node* currentNode;
                BSTree<TKey, TVal,Pred>* tree;
                iterator(node* currentNode, BSTree<TKey, TVal,Pred>* tree) : currentNode(currentNode), tree(tree) {};
                Pred pred=Pred();
            friend class BSTree;
            
        };
        //default
        BSTree() {};
        //copy constructor
		BSTree(const BSTree& rhs);
				//copy assignment
		BSTree& operator=(const BSTree& rhs) {
    	std::cout<<"copy assignment operator called\n";
        
		    if(this != &rhs){
            //deleting the tree at lhs
		    _deleteTree(root);
            //making deep copy of rhs tree
		    root = copyHelper(rhs.root); 
		    
		    }
		     return *this;
		}
        node* copyHelper(const node*);


		//move constructor
        BSTree(BSTree&& rhs);
		//move assignment
        BSTree& operator=(BSTree&& rhs) {
    	std::cout<<"move assignment operator called\n";

		    if(this != &rhs){
		    _deleteTree(root);
		    root = copyHelper(rhs.root); 
		    _deleteTree(rhs.root);
		    rhs.root=nullptr;
		    
		    }
		     return *this;
		}
        ~BSTree();

        void insert(TKey, TVal);
        bool del(TKey);
        bool remove(TKey); // identical with "del"
        bool change(TKey, TVal);
        void print(TRAVERSAL_METHOD);
        bool has(TKey);
        node* findNode(TKey);
        const TVal* getVal(TKey);
        int totalcount();
        int leafcount();
        int height();

        iterator begin();
        iterator begin(int);
        iterator rbegin(); // returns a forward iterator at the last element, not a reverse iterator.
        iterator end();
        iterator min_element();
        iterator max_element(); 
        iterator lower_bound(TKey);
        iterator upper_bound(TKey);

    
    private:
        

        node* root = nullptr;
        node* _insert(node*, TKey, TVal);
        node* _newNode(TKey, TVal);
        int _totalcount(node* root);
        int _leafcount(node* root);
        int _height(node* root);
        void _deleteTree(node* root);
        void _printInOrder(node*);
        void _printPreOrder(node*);
        void _printPostOrder(node*);
        bool _has(node*, TKey);
        node* _lower_bound(node* root,TKey );
        node* _upper_bound(node* root,TKey );
        node* _max(node* root);
        node* _min(node* root);   
        Pred pred;
};

#endif