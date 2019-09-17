#include <iostream>
#include <stdio.h>
#include "library2.h"
#include "Hash2.hpp"
#include "MinimumHeap.hpp"
#include "NodeTree.hpp"
#include "Group.hpp"
#include "List.hpp"


class Colosseum{

	MinimumHeap _activeGroups;
	Hash _allGroups;
    SPtree<GladLessById> _allGladById;
public:

    Colosseum(int n, int *trainingGroupsIDs);
	StatusType addTrainingGroup(int trainingGroupID);
	StatusType addGladiator(int gladiatorID, int score, int trainingGroup);
	StatusType trainingGroupFight( int trainingGroup1, int trainingGroup2, int k1, int k2);
    StatusType getMinTrainingGroup( int* trainingGroup);
	
    ~Colosseum();
    
};
