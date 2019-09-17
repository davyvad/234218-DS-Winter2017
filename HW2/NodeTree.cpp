
#include "NodeTree.hpp"

Node::Node(const Glad& value, Node* father): num_sons(1), score_sons(value.getLevel()),_value(value), _father(father),
_left_son(NULL), _right_son(NULL) {}

Glad& Node::getValue(){
    return _value;
}
