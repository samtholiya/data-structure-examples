#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> heapArray = {};

int parentIndexOfIndex(int index) {
    int oneBasedIndex = index + 1;
    int oneBasedParentIndex = floor(oneBasedIndex / 2);
    return oneBasedParentIndex - 1;
}

vector<int> childIndicesOfParentIndex(int parentIndex) {
    int oneBasedIndex = parentIndex + 1;
    int childFirstIndex = oneBasedIndex * 2;
    vector<int> indices = {};
    if (heapArray.size() > childFirstIndex - 1) {
        indices.push_back(childFirstIndex - 1);
        if (heapArray.size() > childFirstIndex) {
            indices.push_back(childFirstIndex);
        }
    }
    return indices;
}

void addValueToHeap(int value) {
    for (int i = 0; i < heapArray.size(); i++) {
        if (heapArray[i] == value) {
            return;
        }
    }
    
    int newValueIndex = heapArray.size();
    heapArray.push_back(value);
    
    //Rebalance if required
    int parentIndex = parentIndexOfIndex(newValueIndex);
    int childIndex = newValueIndex;
    while (parentIndex >= 0) {
        //If value is smaller then we bubble up
        if (value < heapArray[parentIndex]) {
            heapArray[childIndex] = heapArray[parentIndex];
            heapArray[parentIndex] = value;
            childIndex = parentIndex;
            parentIndex = parentIndexOfIndex(childIndex);
        }
        else {
            break;
        }
    }
}

void moveIndexToAppropriateChildOrParent(int indexToMove) {
    int parentIndex = parentIndexOfIndex(indexToMove);
    if (parentIndex >= 0 && heapArray[indexToMove] < heapArray[parentIndex]) {
        int parentValue = heapArray[parentIndex];
        heapArray[parentIndex] = heapArray[indexToMove];
        heapArray[indexToMove] = parentValue;
        moveIndexToAppropriateChildOrParent(parentIndex);
    }
    else {
        vector<int> childIndices = childIndicesOfParentIndex(indexToMove);
        if (childIndices.size() > 0) {
            int childIndex = childIndices[0];
            if (childIndices.size() == 2) {
                if (heapArray[childIndex] > heapArray[childIndices[1]]) {
                    childIndex = childIndices[1];
                }
            }
            if (heapArray[indexToMove] > heapArray[childIndex]) {
                int childValue = heapArray[childIndex];
                heapArray[childIndex] = heapArray[indexToMove];
                heapArray[indexToMove] = childValue;
                moveIndexToAppropriateChildOrParent(childIndex);
            }
        }
    }
}

void replaceIndexWithLastElement(int indexToReplace) {
    heapArray[indexToReplace] = heapArray[heapArray.size() - 1];
    heapArray.pop_back();
}

void deleteValueFromHeap(int value) {
    int indexToDelete = -1;
    for (int i = 0; i < heapArray.size(); i++) {
        if (heapArray[i] == value) {
            indexToDelete = i;
            break;
        }
    }
    if (indexToDelete == -1) {
        cout << "did not find value";
        return;
    }
    
    replaceIndexWithLastElement(indexToDelete);
    moveIndexToAppropriateChildOrParent(indexToDelete);
}

int currentHeapMin() {
    return heapArray[0];
}

int main() {
    
    int numQueries;
    cin >> numQueries;
    
    for (int i = 0; i < numQueries; i++) {
        int operationType, value;
        cin >> operationType;
        if (operationType == 1) {
            cin >> value;
            addValueToHeap(value);
        }
        else if (operationType == 2) {
            cin >> value;
            deleteValueFromHeap(value);
        }
        else {
            cout << currentHeapMin() << "\n";
        }
    }
    
    return 0;
}