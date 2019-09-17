#include <assert.h>
#include <stdlib.h>

#include "Colosseum.hpp"




using namespace std;

Colosseum::Colosseum(int n, int *trainingGroupsIDs): _activeGroups(MinimumHeap(trainingGroupsIDs, n)),
                _allGroups(Hash(n, _activeGroups.get_heap())) {
	SPtree<GladLessById> _allGladById;
}
StatusType Colosseum::addTrainingGroup(int trainingGroupID) {
	if (_allGroups.findGroup(trainingGroupID) != NULL) {
		return FAILURE;
	}
	Group* gr = _activeGroups.Insert(trainingGroupID);
	assert(gr!=NULL);
	_allGroups.insert(gr);
	return SUCCESS;
}

StatusType Colosseum::addGladiator(int gladiatorID, int score,
		int trainingGroup) {
	Glad to_find(gladiatorID, score);
	Node* node_glad = _allGladById.find(to_find);
	NodeGroup* Group = _allGroups.findGroup(trainingGroup);
	if (node_glad != NULL || Group == NULL) {
		return FAILURE;
	}
	Group->group_glad_tree->insert(to_find);
    
	_allGladById.insert(to_find);
	return SUCCESS;
}

StatusType Colosseum::trainingGroupFight(int trainingGroup1, int trainingGroup2,
		int k1, int k2) {
	if (trainingGroup1 == trainingGroup2) {
		return FAILURE;
	}
    if(trainingGroup1==3 && trainingGroup2==12){
        assert(1);
    }
    //cout<< "\nFight between : "<< trainingGroup1<< " & "<< trainingGroup2;
	NodeGroup* gr1 = _allGroups.findGroup(trainingGroup1);
	NodeGroup* gr2 = _allGroups.findGroup(trainingGroup2);
	if ( gr1 == NULL || gr1->_heap_equivalent==NULL || gr2 == NULL || gr2->_heap_equivalent==NULL) {
		return FAILURE;
	}
	if(gr1->NumOfGlads() < k1 || gr2->NumOfGlads() < k2){
		return FAILURE;
	}
	int score1=-1;
	int score2=-1;
	gr1->group_glad_tree->findKbest(k1,&score1);
	gr2->group_glad_tree->findKbest(k2,&score2);

	if(score1 > score2 || (score1 == score2 && gr1->GetNumGroup()<gr2->GetNumGroup())){
		_activeGroups.DelKey(gr2->GetGroupIndex());
		gr2->SetNotActive();
	}
	else{
		_activeGroups.DelKey(gr1->GetGroupIndex());
		gr1->SetNotActive();
	}
    //cout << this->_activeGroups<< endl;
	return SUCCESS;
}

StatusType Colosseum::getMinTrainingGroup(int* trainingGroup) {
	*trainingGroup = _activeGroups.FindMin();
	return SUCCESS;
}


Colosseum::~Colosseum(){};
