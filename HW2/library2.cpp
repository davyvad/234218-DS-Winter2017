#include <iostream>
#include <stdio.h>
#include "Colosseum.hpp"
#include "library2.h"


void* init(int n, int *trainingGroupsIDs) {
	//david, has to be in minHeap, but it hasnt work
	if(n<2) return NULL;
	for (int i = 0; i < n; i++) {
		if(trainingGroupsIDs[i] <0){
			return NULL;
		}
	}
	Colosseum* DS = new Colosseum(n,trainingGroupsIDs);
	return (void*)DS;

}


StatusType addTrainingGroup(void *DS, int trainingGroupID){

	if(DS == NULL || trainingGroupID<0) {
			return INVALID_INPUT;
		}

		return ((Colosseum*)DS)->Colosseum::addTrainingGroup(trainingGroupID);

}

StatusType addGladiator(void *DS, int gladiatorID, int score, int trainingGroup) {

	if(DS==NULL || gladiatorID<0 || trainingGroup<0 || score<0) {
		return INVALID_INPUT;
	}

	return ((Colosseum*)DS)->addGladiator(gladiatorID, score, trainingGroup);

}

StatusType trainingGroupFight(void* DS, int trainingGroup1, int trainingGroup2, int k1, int k2){
    if (DS== NULL || k1<= 0 || k2<=0 || trainingGroup1<0 || trainingGroup2<0)
    	return INVALID_INPUT;

    return ((Colosseum*)DS)->trainingGroupFight(trainingGroup1,trainingGroup2,k1, k2);
}

StatusType getMinTrainingGroup (void* DS, int* trainingGroup){
	if(DS==NULL || trainingGroup==NULL) {
			return INVALID_INPUT;
		}

    return ((Colosseum*)DS)->getMinTrainingGroup(trainingGroup);
}


void quit(void** DS){
    //(*(Colosseum**)DS)->~Colosseum();
    delete *((Colosseum**)DS);
    *DS = NULL;

}

