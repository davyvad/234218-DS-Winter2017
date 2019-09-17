
#ifndef SPtree_h
#define SPtree_h
#include <stdio.h>
#include <iostream>
#include <assert.h>
#include "NodeTree.hpp"
#include "Group.hpp"


//     TREE     //

typedef enum{
    SP_NOT_IN_TREE , SP_SUCCESS, SP_ALREADY_IN_TREE
}SPResult;


template <class Compare= std::less<Glad> >
class SPtree {
    Compare comp;
public:
    Node * _root;
   int _node_number;

    SPtree(): _root(NULL), _node_number(0){} ;
    SPtree(Node * root);
    ~SPtree();

    void clean();
    Node* insert(const Glad& value);
    SPResult remove(const Glad& value);

    Node* find(const Glad& value);
    Node* GetRoot();

	void Inorder(Node * node);
    Node* findMax(Node * node= NULL);
    bool split(const Glad& value, Node** left, Node** right);
    int getSumScores();
    Node* findKbest(int k, int* sum);

private:

    Node* insertAux(const Glad& value, Node* node);
    //void removeAux(const T& value, Node* node);
    void cleanAux(Node* node);

    Node* findAux(const Glad& value, Node* node);

	void Zig_Right(Node* node);
	void Zig_Left(Node* node);

	void ArrangSPtree(Node* node);

};


template <class Compare>
SPtree<Compare>::SPtree(Node* root) : _root(root) {
	if(_root==NULL) {
		_node_number = 0;
	}
	else _node_number = 1;
}

template < class Compare>
SPtree<Compare>::~SPtree(){
	clean();
}

template < class Compare>
void SPtree<Compare>::cleanAux(Node * p) {
	if(p==NULL) return;
	cleanAux(p->_left_son);
	cleanAux(p->_right_son);
	delete p;
	return;
}

template < class Compare>
void SPtree< Compare>::clean() {
	cleanAux(_root);
	_root = NULL;
	return;
}

template <class Compare>
Node * SPtree<Compare>::findAux(const Glad& _value, Node * p){
    if(p == NULL){
    	return NULL;
    }
    else if (_value == p->_value ){
    	return p;
    }
    else if(p->_left_son == NULL && p->_right_son == NULL){
    	return p;
    }

    else if (comp(_value, p->_value)){      //If value is less than p->_value
    	if(p->_left_son == NULL)	 return p;
        return findAux(_value, p->_left_son);
    }

    else {                                  //else if(_value > p->_value)
    	if(p->_right_son == NULL)	 return p;
        return findAux(_value, p->_right_son);
    }
}

template < class Compare>
Node * SPtree<Compare>::find(const Glad& value) {
    if(_root){
        if( _root->_value == value){
            return _root;
        }
    }
    Node* node =  findAux(value, _root);
    if(node){
        ArrangSPtree(node);
        assert(node == _root);
    
        if(node->_value == value){
            return node;
        }
    }
    return NULL;
    
}

template <class Compare>
bool SPtree<Compare>::split(const Glad& value, Node** left, Node** right){
    find(value);
    Node* node = _root;
    if(comp( node->_value , value)){        //If node->_value < value
        *right = node->_right_son;
        if(node->_right_son != NULL){
            node->_right_son->_father = NULL;
            node->num_sons -= node->_right_son->num_sons;
            node->score_sons -= node->_right_son->score_sons;   //Update scores & num of sons
        }
        node->_right_son = NULL;
        node->_father = NULL;
        *left = node;
        return true;

    }else if(comp(value, node->_value)){    //If node->value > value
        *left = node->_left_son;
        if(node->_left_son != NULL) {   node->_left_son->_father = NULL;
            node->num_sons -= node->_left_son->num_sons;
        
            node->score_sons -= node->_left_son->score_sons;   //Update scores & num of sons
        }
        
        node->_left_son = NULL;
        node->_father = NULL;
        *right = node;
        return true;
    }
    return false;       // if value == node->_value
}




template < class Compare>
Node* SPtree< Compare>::insert(const Glad& value) {
    if(_root==NULL) {
        _root=new Node(value, NULL);
        _root->score_sons = _root->getValue().getLevel();
        _node_number++;
        return _root;
    }
    Node* left, *right;
    bool b= split(value, &left, &right);
    if(!b) {
        return NULL;        //Returns NULL if the value is already in the tree !
    }
    Node* new_node = new Node(value, NULL);
    new_node->_left_son = left;
    if(left){
        left->_father = new_node;
        new_node->score_sons+= left->score_sons;
        new_node->num_sons+= left->num_sons;

    }
    new_node->_right_son = right;
    if(right){
        right->_father  = new_node;
        new_node->score_sons+= right->score_sons;
        new_node->num_sons+= right->num_sons;

    }
    _root = new_node;
    _node_number++;
    return  new_node;
}

//Rotating from Left to Right
template < class Compare>
void SPtree< Compare>::Zig_Left(Node* x){

	Node* temp=x->_right_son;
	Node* y=x->_father;
	Node* GrandFather=x->_father->_father;
    
    int xRightScore=0, yRightScore=0, scoreRoot= y->score_sons;
    int xRightSons=0, yRightSons=0, sonsRoot= y->num_sons;
    if(x->_right_son!= NULL){ xRightScore= x->_right_son->score_sons;
        xRightSons = x->_right_son->num_sons;
    }
    if(y->_right_son!= NULL){
        yRightScore= y->_right_son->score_sons;
        yRightSons= y->_right_son->num_sons;
    }
	//fix z
	if(GrandFather!=NULL){
	   		if(GrandFather->_left_son==y){
	   			GrandFather->_left_son=x;
	   		}
	   		else if(GrandFather->_right_son==y){
	   			GrandFather->_right_son=x;
	   		}

	}
	//fix y
	y->_left_son=temp;
	y->_father=x;
    y->score_sons = y->getValue().getLevel() + xRightScore +yRightScore;
    y->num_sons = 1 + xRightSons + yRightSons;
    
   	//fix x left son
	if(x->_right_son !=NULL)    x->_right_son->_father=y;

	//fix x
	x->_right_son=y;
	x->_father=GrandFather;
    x->score_sons= scoreRoot;
    x->num_sons = sonsRoot;
}

//Rotating from Right to Left
template < class Compare>
void SPtree< Compare>::Zig_Right(Node* x){
// we will do 4 changes in grandparent, in parent, in son and the son of the son:

	Node* temp=x->_left_son;
	Node* y=x->_father;
	Node* GrandFather=y->_father;

    int xLeftScore=0, yLeftScore=0, scoreRoot= y->score_sons;
    int xLeftSons=0, yLeftSons=0, sonsRoot= y->num_sons;

    if(x->_left_son!= NULL){xLeftScore= x->_left_son->score_sons;
        xLeftSons = x->_left_son->num_sons;
    }
    if(y->_left_son!= NULL){yLeftScore= y->_left_son->score_sons;
        yLeftSons= y->_left_son->num_sons;
    }
    
    
    //fix z
	if(GrandFather!=NULL){
	   		if(GrandFather->_left_son==y){
	   			GrandFather->_left_son=x;
	   		}
	   		else if(GrandFather->_right_son==y){
	   			GrandFather->_right_son=x;
	   		}

	}
	//fix y
   	y->_right_son=temp;
   	y->_father=x;
    y->score_sons = y->getValue().getLevel() + xLeftScore +yLeftScore;
    y->num_sons = 1 + xLeftSons + yLeftSons;


   	//fix x left son
   	if(y->_right_son !=NULL)    x->_left_son->_father=y;

   	//fix x
   	x->_left_son=y;
   	x->_father=GrandFather;
    x->score_sons= scoreRoot;
    x->num_sons = sonsRoot;
}

template <class Compare>
void SPtree< Compare>::ArrangSPtree(Node * node){
	if(node->_father == NULL) {
		_root=node;
		return;
	}
	Node * y=node->_father;
    
	if(y->_right_son == node){
		Zig_Right(node);
        y = node->_father;
        if(y!= NULL)   {
            assert(y->_left_son == node || y->_right_son ==node);
        }
		ArrangSPtree(node);
	}

	else if( y->_left_son == node){
			Zig_Left(node);
        y = node->_father;
        if(y!= NULL)   {
            assert(y->_left_son == node || y->_right_son ==node);
        }
			ArrangSPtree(node);
	}
    
	return;

}

template < class Compare>
Node*  SPtree< Compare>::GetRoot(){
	return _root;
}

template < class Compare>
void SPtree< Compare>::Inorder(Node * node){
		if(node==NULL) return;
		Inorder(node->_left_son);
		std::cout << "key:" << node->_value <<" , ";
		Inorder(node->_right_son);

}

//Returns the maximum node in the subtree which the root is node
template< class Compare>
Node* SPtree< Compare>::findMax(Node * node){
    if(node== NULL){
        node = _root;
    }
    if (!node)
        return NULL;
    Node* res=  node;
    while(res->_right_son){
        res=res->_right_son;
    }
    ArrangSPtree(res);
    return res;
}


template< class Compare>
SPResult SPtree< Compare>::remove(const Glad& value){
    Node* node= find(value);
    if (!node){
        return SP_NOT_IN_TREE;
    }
    assert(node== _root);
    Node* left = node->_left_son;
    Node* right = node->_right_son;
    
    if(left != NULL && right != NULL){
        left->_father= NULL;
        right->_father = NULL;
    
        Node* new_left_root = findMax(left);
        new_left_root->_right_son  = right;
        right->_father = new_left_root;
    }
    else if(right != NULL ){
        right->_father = NULL;
        _root = right;
    }
    else if(left!= NULL){
        left->_father =  NULL;
        _root = left;
    }
    else {
        _root =  NULL;
    }
    delete node;
    return SP_SUCCESS;
}


template< class Compare>
int SPtree<Compare>::getSumScores(){
    return _root->score_sons;
}

template< class Compare>
Node* SPtree<Compare>::findKbest(int k, int* sum){
    if(k> _node_number || k<=0){
        *sum =-1;
        return NULL;
    }
    else{
        Node* actual = _root;
        int j =-1;
        while(j!=k){

            if(actual->_left_son ){
                j= actual->num_sons - actual->_left_son->num_sons;
                if(j>k){
                    actual = actual->_right_son;
                    continue;
                }
                else if(j<k){
                    k -= j;
                    actual = actual->_left_son;
                    j=0;
                    continue;
                }
                else{       //j =k
                    find(actual->getValue());
                }
            }
            else if(actual->_right_son){
                j= 1+ actual->_right_son->num_sons;
                if(j>k){
                    actual = actual->_right_son;
                    continue;
                }
                else if(j<k){
                    k -= j;
                    actual = actual->_left_son;
                    continue;
                }
                else{       //j =k
                    find(actual->getValue());
                }
            }
            else{
                assert(actual->num_sons= k);
                find(actual->getValue());
                break;
            }
        }
        
        find(actual->getValue());
        int lessScore =0;
        if (_root->_left_son)
            lessScore= _root->_left_son->score_sons;
        *sum = _root->score_sons - lessScore;
    }
    return _root;
}


#endif /* SPtree_h */

