
#include "Hash2.hpp"

using namespace std;


int Hash::hashing(int i, int size){
    if(size==-1){
        size=m;
    }
    return i%size;
}

void Hash::addGroup(NodeGroup* i, List** groups, int size){
    
    if(!groups || size==-1){
        groups= groups_table;
        size= m;
    }
    int k= hashing(i->GetNumGroup(), size);
    if(!groups[k]){
        groups[k]= new List(i);
    }else{
        groups[k]->insert(i);   //Insertion of the groups
    }
}


Hash::Hash(){
    m=0;
    n=0; groups_table=NULL;
}

Hash::Hash(int m, Group** nums): m(m), n(0), groups_table((List**)new List* [m]){
    for(int i=0; i<m; i++){
        groups_table[i]= NULL;      //Init of list-pointers of the table
    }
    for(int i=1; i<=m; i++){
        //Group* group = nums[i];
        NodeGroup g(nums[i]);
        addGroup(&g);
        n++;
    }
}


List** Hash::createEmptyTable(){
    List** tmp=(List**)new List* [HEAVY_FACTOR *m];
    
    for(int i=0;i<HEAVY_FACTOR*m ; i++){
        tmp[i]=NULL;
    }
    return tmp;
}

HashRes Hash::insert(Group* group_num){
    if(n==0){
        groups_table= (List**)new List* [2];
        m=2;
    }
    NodeGroup g(group_num);
    addGroup(&g);
    n++;
    
    if(n>= HEAVY_FACTOR* m){        //REHASH !!
        List** tmp= createEmptyTable();
        
        int old_table_size = m;
        
        for(int i=0; i<old_table_size; i++){
            if(groups_table[i]== NULL){     //If there isn't any groups in the i cell
                continue;
            }
            int num_groups;
            NodeGroup** groups= groups_table[i]->getAllVal(&num_groups);
            
            for(int j=0; j<num_groups; j++){
                this->addGroup(groups[j], tmp, HEAVY_FACTOR* m);
            }
            
            delete[] groups;
            groups_table[i]->delAll();
        }
        
        for(int i=0; i<m; i++){
            if(groups_table[i]){
                delete groups_table[i];
            }
        }
        delete [] this->groups_table;
        this->m= HEAVY_FACTOR * m;
        groups_table=tmp;
    }
    return HASH_SUCCESS;
}


NodeGroup* Hash::findGroup(int group_num){
    int k =hashing (group_num);
    if(!groups_table[k]){       // If the k cell is empty
        return NULL;
    }
    NodeGroup* tmp= groups_table[k]->find(group_num);
    return tmp;
}

Hash::~Hash(){
    for (int i=0; i< this->m; i++){
        List* l=  groups_table[i];
        if(!l){
            continue;
        }
        groups_table[i]->~List();
        delete groups_table[i];
    }
    delete[] groups_table;
}

/*std::ostream& operator<<(std::ostream& output, const Hash& hash){
    output<< "\n\nHash Table:\n";
    for(int i=0; i< hash.m ; i++){
        cout << hash.groups_table[i];
    }
    return output;
}*/



