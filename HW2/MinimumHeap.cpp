#include "MinimumHeap.hpp"
#include <stdio.h>
#include <assert.h>
#include <iostream>
using namespace std;

void MinimumHeap::SiftDown(int index) {
	int length = _Groups_in_fact;
	int leftChildIndex = 2 * index;
	int rightChildIndex = 2 * index + 1;

    if (leftChildIndex > length){
        if(_Groups_in_fact==1){
            _heap[1]->SetIndex(1);
        }
		return; //index is a leaf
    }
	int minIndex = index;

	if (*(_heap[index]) > *(_heap[leftChildIndex])) {
		minIndex = leftChildIndex;
	}

	if ((rightChildIndex <= length)
			&& (*(_heap[minIndex]) > *(_heap[rightChildIndex]))) {
		minIndex = rightChildIndex;
	}

	if (minIndex != index) {
		_heap[index]->SetIndex(minIndex);
		_heap[minIndex]->SetIndex(index);

		//need to swap
		Group* temp = _heap[index];
		_heap[index] = _heap[minIndex];
		_heap[minIndex] = temp;
		SiftDown(minIndex);
	}
}
void MinimumHeap::SiftUp(int index) {
	if (index == 1)
		return;

	int parentIndex = (index ) / 2;
	if (*(_heap[parentIndex]) > *(_heap[index])) {
		_heap[index]->SetIndex(parentIndex);
		_heap[parentIndex]->SetIndex(index);

		//need to swap
		Group* temp = _heap[parentIndex];
		_heap[parentIndex] = _heap[index];
		_heap[index] = temp;
		SiftUp(parentIndex);
	}
}

MinimumHeap::MinimumHeap(int* array, int n) {
	_Groups_in_fact = n;
	_Groups_in_memory = 2 * n;

	_heap = (Group**) new Group*[2 * n+1];
    _heap[0]= NULL;
    
	for (int i = 0; i < n; i++) {
		_heap[i + 1] = new Group(array[i], i+1);
	}

	for (int j = n / 2; j > 0; j--) {
		SiftDown(j);
	}
}

/*MinimumHeap::MinimumHeap() {
	_Groups_in_fact = 0;
	_Groups_in_memory =0;
}*/

Group* MinimumHeap::Insert(int newValue) {
    if (_Groups_in_fact < _Groups_in_memory) {
        _Groups_in_fact++;
        Group* gr= new Group(newValue,_Groups_in_fact);
        _heap[_Groups_in_fact] =gr;
        SiftUp (_Groups_in_fact);
        return gr;
        
    }else {
        assert(_Groups_in_fact==_Groups_in_memory);
        Group** arr = (Group**) new Group*[2 * _Groups_in_memory+1];
        arr[0]= NULL;
        for(int i=1; i<=_Groups_in_memory; i++){
            arr[i]=_heap[i];
        }
        delete [] _heap;
        _Groups_in_fact++;
        _Groups_in_memory=2* _Groups_in_memory;
        _heap=arr;
        Group* gr=new Group(newValue,_Groups_in_fact);
        _heap[_Groups_in_fact] =gr;
        SiftUp (_Groups_in_fact);
        return gr;
    }
}





int MinimumHeap::FindMin() {
	return _heap[1]->GetId();
}

HeapStatus MinimumHeap::DelKey(int index){
	 delete _heap[index];
    if(index== _Groups_in_fact){
        _Groups_in_fact--;
        return HEAP_SUCCESS; }
	_heap[index]=_heap[_Groups_in_fact];
    _heap[index]->SetIndex(index);
    if(_heap[index]== NULL){
        assert(1);
    }
    
    //_heap[index]->SetIndex(index);
	//_heap[_Groups_in_fact]=NULL;
	_Groups_in_fact--;
	SiftDown(index);

    return HEAP_SUCCESS;
}
Group**   MinimumHeap::get_heap(){
    return _heap;
}

MinimumHeap::~MinimumHeap(){
    /*for (int i=1; i<= _Groups_in_fact; i++){
        std::cout<< "i="<< i << std::endl;
        delete(_heap[i]);
    }*/
    
    delete[] _heap;
}



std::ostream& operator<<(std::ostream& output, const MinimumHeap& heap){
    output << "\nHeap:\n";
    for(int i=1; i< heap._Groups_in_fact+1 ; i++){
        output<<" ID, index : "<< heap._heap[i]->GetId()<<","<< heap._heap[i]->GetIndex()<<"  ";
    }
    
    return output;
}

