#ifndef List_hpp
#define List_hpp
#include <iostream>     // std::cout
#include <stdio.h>
#include "MinimumHeap.hpp"
#include "splay.hpp"

//using namespace std;

typedef enum{
    LIST_SUCCES, LIST_MEMORY
} ListRes;

class NodeGroup{
public:
    int group_num;
    NodeGroup* next;
    SPtree<>* group_glad_tree;
    Group* _heap_equivalent;
    
    NodeGroup(NodeGroup* group, NodeGroup* next= NULL);
    NodeGroup(Group* group);
    int NumOfGlads();
    int GetNumGroup();
    int GetGroupIndex();
    void SetNotActive();
    //~NodeGroup();
};

class List{
    NodeGroup *head; //pointer to the first element of the list.
    int listSize;
    
public:
    List();
    List(NodeGroup* group_num);
    
    ListRes insert(NodeGroup* group_num);
    NodeGroup** getAllVal(int* num);
    
    void delAll();
    NodeGroup* find(int group_num);
    friend std::ostream& operator<<(std::ostream& output, const List* list);

    ~List();
};

std::ostream& operator<<(std::ostream& output, const List* list);


#endif /* List_hpp */
