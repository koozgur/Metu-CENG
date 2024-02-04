#include "BinaryHeap.h"

BinaryHeap::BinaryHeap()
{
    // TODO: or not
     elements.resize(1);
     count = 0;
}


bool BinaryHeap::Add(int uniqueId, double weight)
{
    // TODO:
    int exist_flag = 0;
    for(int a = 1; a <= count; a++)
        if(elements[a].uniqueId == uniqueId)
            exist_flag = 1;
    if(exist_flag == 1)
        return false;
    else{
        HeapElement x;
        x.uniqueId = uniqueId;
        x.weight = weight;
     elements[0] = x; // initialize 
    
    if((count + 1) == ( (int) elements.size()))
        elements.resize(elements.size( )*2 + 1);
    
    // Percolate up
    int hole = ++count;
    for( ; x.weight < elements[hole/2].weight; hole /= 2 )
        elements[hole] = elements[hole/2];
    elements[hole] = x;
    }
    return true;
}

bool BinaryHeap::PopHeap(int& outUniqueId, double& outWeight)
{
    // TODO:
    if(count == 0)
        return false; 
    outWeight = elements[1].weight;
    outUniqueId = elements[1].uniqueId;
    elements[1] = elements[count--];
    percolateDown(1);
    return true;
    
}

bool BinaryHeap::ChangePriority(int uniqueId, double newWeight)
{
    // TODO:
    int i = 1;
    while(i <= count){
        if(elements[i].uniqueId == uniqueId){
            elements[i].weight = newWeight;
            break;
        }
    i++;
    }
    if(i <= count){
        buildHeap();
        return true;
    }
    return false;
}

int BinaryHeap::HeapSize() const
{
    // TODO:
    return count;
}