#pragma once
#include <iostream>
#include <vector>

struct HeapElement
{
    int     uniqueId;
    double  weight;
};

class BinaryHeap
{
    private:
    std::vector<HeapElement> elements;
    int count; //no. of element


    
    void percolateDown(int hole) {
    int child;
    HeapElement local = elements[hole];
    
    for( ; hole*2 <= count; hole = child) {
        child = hole * 2;
        if(child != count && elements[child + 1].weight < elements[child].weight)
            child++;
        if(elements[child].weight < local.weight)
            elements[hole] = elements[child];
        else
            break;
    }
    elements[hole] = local;
    }

    void buildHeap(){
        for(int i = count/2; i > 0; i-- )
        percolateDown(i);
    }
    // Do not remove this the tester will utilize this
    // to access the private parts.
    friend class HW3Tester;

    protected:
    public:
        // Constructors & Destructor
                            BinaryHeap();
        //
        bool                Add(int uniqueId, double weight);
        bool                PopHeap(int& outUniqueId, double& outWeight);
        bool                ChangePriority(int uniqueId, double newWeight);
        int                 HeapSize() const;
        
        void print(){
            int a = 1;
            while(a < (int)elements.size()){
                std::cout << elements[a].weight << std::endl;
                a++;
            }
        }
};