
#ifndef Hash2_hpp
#define Hash2_hpp


#include "List.hpp"
#include <stdio.h>


#define HEAVY_FACTOR 2
//#define COEFF 2


typedef enum {
    HASH_SUCCESS, HASH_ALREADY_IN_TABLE, HASH_NOT_FOUND, HASH_MEMORY
}HashRes;

class Hash{
    int m, n;       // m is the size of the table, n is the number of groups now
    List** groups_table;
    
    
    int hashing(int i, int size= -1);
    void addGroup(NodeGroup* i, List** groups= NULL, int size= -1);
    List** createEmptyTable();
    
    
public:
    Hash();
    Hash(int m, Group** nums);
    HashRes insert(Group* group_num);
    NodeGroup* findGroup(int group_num);
    
    friend std::ostream& operator<<(std::ostream& output, const Hash& hash);

    ~Hash();
};



#endif /* Hash2_hpp */
