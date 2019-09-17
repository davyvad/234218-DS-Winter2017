
#ifndef NodeTree_hpp
#define NodeTree_hpp

#include <stdio.h>
#include "Gladiator.hpp"

class Node {

public:
    int num_sons;
    int score_sons;
    Glad _value;
    Node* _father;
    Node* _left_son;
    Node* _right_son;
    
    Node(const Glad& value, Node* father);
    Node(Node* father);
    Glad& getValue();
};

#endif /* NodeTree_hpp */
