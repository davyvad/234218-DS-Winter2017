#include "List.hpp"
#include "Group.hpp"


using namespace std;

int NodeGroup::NumOfGlads(){
    if(group_glad_tree->GetRoot() == NULL) return 0;
	return group_glad_tree->GetRoot()->num_sons;
}


int NodeGroup::GetGroupIndex(){
	return _heap_equivalent->GetIndex();
}

int NodeGroup::GetNumGroup(){
	return this->group_num;
}

void NodeGroup::SetNotActive(){
	_heap_equivalent=NULL;
}
NodeGroup::NodeGroup(NodeGroup* group, NodeGroup* next): group_num(group->GetNumGroup()), next(next), _heap_equivalent(group->_heap_equivalent){
    this->group_glad_tree = group->group_glad_tree;
}


NodeGroup::NodeGroup(Group* group): group_num(group->GetId()){
    _heap_equivalent = group;
    //cout<< " Create tree ";
    this->group_glad_tree = new SPtree<>();
}




    // LIST //

List::List(): head(NULL), listSize(0){}

List::List(NodeGroup* group_num): head(new NodeGroup(group_num, NULL)), listSize(1){}


ListRes List::insert(NodeGroup* group_num){
    if(!head){
        assert(1);
    }
    NodeGroup* tmp= NULL;
    try {
        tmp= new NodeGroup(group_num, head);
    } catch (std::bad_alloc) {
        return LIST_MEMORY;
    }
    head= tmp;
    listSize++;
    return LIST_SUCCES;
}
NodeGroup** List::getAllVal(int* num){
    NodeGroup** groups;
    if(head==NULL){
        assert(listSize==0);
        groups= NULL;
    }
    else{
        groups = new NodeGroup*[listSize];
        int i=0;
        NodeGroup* tmp= head;
        while(tmp){
            groups[i++] = tmp;
            tmp= tmp->next;
        }
        *num= i;
    }
    return groups;
}



void List::delAll(){
    NodeGroup* tmp;
    while (head) {
        tmp= head;
        head= head->next;
        delete tmp;
        listSize--;
    }
}

NodeGroup* List::find(int group_num){
    NodeGroup* tmp= head;
    while(tmp!= NULL){
        if( tmp->group_num== group_num){
            return tmp;
        }
        tmp= tmp->next;
    }
    return tmp;
}

List::~List(){
    NodeGroup* tmp;
    while (head) {
        tmp= head;
        //cout<< "del nodeGroup ";
        delete tmp->group_glad_tree;
        delete tmp->_heap_equivalent;
        head= head->next;
        delete tmp;
        listSize--;
    }
}



std::ostream& operator<<(std::ostream& output, const List* list){
    if (!list)
        return output;
    output <<  "List : " ;
    NodeGroup* tmp=  list->head;
    while(tmp){
        output<< tmp->group_num << "    ";
        tmp= tmp->next;
    }
    cout << endl;
    
    return output;
}
