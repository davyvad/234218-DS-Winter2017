#ifndef MinimumHeap_hpp
#define MinimumHeap_hpp

#include "Group.hpp"
#include <iostream>

typedef enum {HEAP_SUCCESS, HEAP_MEMORY}HeapStatus;

class MinimumHeap
{
private:
	Group** _heap;
	int _Groups_in_fact;
	int _Groups_in_memory;

    void SiftDown(int index);
    void SiftUp(int index);

public:
    MinimumHeap(int* array, int n);
    //MinimumHeap();
    Group* Insert(int newValue);
    int FindMin();
    HeapStatus DelKey(int index);
    Group** get_heap();
    ~MinimumHeap();
    
    friend std::ostream& operator<<(std::ostream& output,
                                    const MinimumHeap& heap);

};

std::ostream& operator<<(std::ostream& output, const MinimumHeap& heap);


#endif /* MinimumHeap_hpp */
