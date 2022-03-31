/*
 Jonathan Henshaw
 CSS 342, Winter 2021
 Dr. Afra Mashhadi, Assignment 4: SkipList
 
 This Class describes a probabilistic data structure called SkipList, which
 can search and insert in O(log(n)) time: https://en.wikipedia.org/wiki/Skip_list
 
 For this class, the probabilistic nature and depth of the structure can be
 modified, allowing us to trade off between storage and speed if desired. A
 SkipList with 50% probability and INT_MAX depth will fulfil the promise of
 O(lon(n)) behavior. With a depth of 1, it is similar to a doubly-linked list.
 
 Every row in this Class will necessarily contain INT_MIN and INT_MAX
 
 */

#ifndef ASS4_SKIPLIST_CPP
#define ASS4_SKIPLIST_CPP

#include "skiplist.h"
#incluse <sstream>
using namespace std;

//—————————————//
//SNODE METHODS//
//—————————————//

//Prints the value of the node's data field only
ostream &operator<<(ostream &out, const SNode& node){
    out << (node.toString());
    return out;
}

//Constructor
SNode::SNode(int value) : data{value} {
    right = nullptr;
    left = nullptr;
    up = nullptr;
    down = nullptr;
}

//Retruns this SNode's data field as a string
string SNode::toString() const { return to_string(this->data); }


//——————————————//
//PUBLIC METHODS//
//——————————————//

//Prints all data from every possible row of the SkipList
//Every row of every SkipList always contains INT_MIN and INT_MAX,
//even if no other values have been added to that row. As a result,
//this operator becomes unwieldy at high values for maxLevel
ostream &operator<<(ostream& out, const SkipList& skip) {
    out << skip.toString();
    return out;
}

//Constructor: Default SkipList
//Has only 1 level, just one doubly-linked list
//To deliver on O(log(n)) behavior:
//maxLevel should be log(expected size), and probability = 50
//Every SkipList always contains INT_MIN and INT_MAX
//maxLevel can be on range [1,INT_MAX]
//probability can be on range [0,99]
SkipList::SkipList(int maxLevel, int probability){
    assert(maxLevel > 0 && probability >= 0 && probability < 100);
    this->maxLevel = maxLevel;
    this->probability = probability;
    head = new SNode(INT_MIN);
}

//Destructor
SkipList::~SkipList() {
    //Clear contents
    while (head->right != nullptr) { remove(head->right->data); }
    //Remove guards
    while (head != nullptr){
        SNode* temp = head;
        head = head->up;
        delete temp;
    }
}

//Returns true if successfully added, otherwise returns false.
//No duplicates allowed in the SkipList
//Every SkipList always contains INT_MIN and INT_MAX
bool SkipList::add(int value) {
    //Can't add guard vals
    if (value == INT_MIN || value == INT_MAX) { return false; }
    
    //Get pointer to the SNode on the bottom row that is <= our value
    SNode* preceedingNode = closestSNode(value);
    
    //SkipList cannot contain duplicates
    if (preceedingNode->data == value) { return false; }
    
    //Insert the new value
    SNode* temp = new SNode(value);
    addAfter(preceedingNode, temp);
    
    //Build upwards from temp
    buildUp(temp);
    
    //We've added!
    return true;
}

//Attempts to add each element from the vector to the SkipList.
//Returns true if any value was successfully added, false if
//the list remains unchanged. No duplicates are allowed in a
//SkipList, and every SkipList always contains INT_MIN and INT_MAX
bool SkipList::add(const vector<int> &values) {
    bool anyAdded = false;
    
    for (int i = 0; i < values.size(); ++i){
        if (add(values[i])) { anyAdded = true;}
    }
    
    return anyAdded;
}

//Attempts to find and remove the given integer from the SkipList.
//If it is found, it will be removed, and true will be returned.
//Otherwise, the list will remain unchanged, and returns false.
//However, if you attempt to remove INT_MIN or INT_MAX, the list
//will remain unchanged and returns false
bool SkipList::remove(int data) {
    //We can't remove the guards
    if (data == INT_MIN || data == INT_MAX) { return false; }
    
    //Get the node on the bottom row <= our desired value
    SNode* targetNode = closestSNode(data);
    
    //If this is not what we were trying to remove, return false
    if (targetNode->data != data) { return false; }
    
    //Delete this node and all above it
    while(targetNode != nullptr){
        //Remove targetNode from this row
        targetNode->left->right = targetNode->right;
        if(targetNode->right != nullptr){
            targetNode->right->left = targetNode->left;
        }
        
        //Save a reference to current targetNode
        SNode* temp = targetNode;
        //Go up
        targetNode = targetNode->up;
        //Delete that targetNode
        delete temp;
    }
    
    //We did it!
    return true;
}

//Returns true if the value is contained in SkipList
//Every SkipList always contains INT_MIN and INT_MAX
bool SkipList::contains(int data) const {
    //Every skiplist contains INT_MIN and INT_MAX
    if (data == INT_MIN || data == INT_MAX) { return true; }
    
    return ( ( (closestSNode(data))->data ) == data );
}

//Provides a string representation of this SkipList
//Every row of every SkipList always contains INT_MIN and INT_MAX,
//even if no other values have been added to that row. As a result,
//this function becomes unwieldy at high values for maxLevel
string SkipList::toString() const {
    int height = 0;
    SNode* guardian = head;
    //Get the guard for the top row
    while(guardian->up != nullptr){
        guardian = guardian->up;
        ++height;
    }
    
    //We don't actually store unused rows
    string result = "";
    for (int extraRows = (maxLevel - 1); extraRows > height; --extraRows) {
        result.append("Level: " + to_string(extraRows) + " -- ");
        result.append(to_string(INT_MIN) + ", " + to_string(INT_MAX) + ", \n\n");
    }
    
    //Concatenate each row
    for(int currRow = height; currRow >= 0; --currRow){
        //Concatenate row header
        result.append("Level: " + to_string(currRow) + " -- ");
        
        //Look at the first value in this row
        SNode* currentNode = guardian;
        
        //Print each value on this row
        while (currentNode != nullptr){
            result.append(to_string(currentNode->data) + ", ");
            currentNode = currentNode->right;
        }
        //INT_MAX is not actually stored
        result.append(to_string(INT_MAX) + ", \n\n");
        
        //go to the next row down
        guardian = guardian->down;
    }
    
    return result;
}


//———————————————//
//PRIVATE METHODS//
//———————————————//

//Given a newNode, place it after the given prevNode
//Does not modify up/down pointers, only left/right
void SkipList::addAfter(SNode* prevNode, SNode* newNode) {
    newNode->right = prevNode->right;
    newNode->left = prevNode;
    
    prevNode->right = newNode;
    if (newNode->right != nullptr) { newNode->right->left = newNode; }
}

//Returns true probability% of time
//If probability == 50, returns true 50% of the time
bool SkipList::shouldInsertAtHigher() const {
  return rand() % 100 < probability;
}

//Probabilistically builds higher levels for given node, and all
//requisite connections. Height will not exceed maxLevel
void SkipList::buildUp(SNode* baseNode){
    SNode* guardian = head;
    int level = 1;
    while(shouldInsertAtHigher() && (level < maxLevel) ){
        //Build up Left guard if necessary
        if (guardian->up == nullptr){
            guardian->up = new SNode(INT_MIN);
            guardian->up->down = guardian;
        }
        
        //Get closest node on the left that goes up
        SNode* leftest = baseNode;
        while( (leftest->left != nullptr) && (leftest->up == nullptr) ){
            leftest = leftest->left;
        }
        //And go up from it
        leftest = leftest->up;
        
        //Add one row up, and connect
        baseNode->up = new SNode(baseNode->data);
        baseNode->up->down = baseNode;
        baseNode = baseNode->up;
        addAfter(leftest, baseNode);
        
        //Move up on the guardrail
        guardian = guardian->up;
        //Connect to guardrail if necessary
        if(leftest->left == nullptr && leftest->data != INT_MIN){
            leftest->left = guardian;
            guardian->right = leftest;
        }
        ++level;
    }
}

//Returns a pointer to the SNode on the bottom row of the
//SkipList who's data value is the greatest in the list still
//satisfying: (data <= value)
SNode* SkipList::closestSNode(int value) const {
    //Get pointer to the top row's left guard
    SNode* toCompare = head;
    int height = 0;
    while (toCompare->up != nullptr){
        toCompare = toCompare->up;
        ++height;
    }
    
    for(int currRow = height; currRow >= 0; --currRow){
        //Find the greatest element in this row that is <= our value
        while (toCompare->right != nullptr &&
               toCompare->right->data <= value) {
            toCompare = toCompare->right;
        }
        //Move down to the next row
        if(toCompare->down != nullptr) { toCompare = toCompare->down; }
    }
    
    return toCompare;
}

#endif //ASS4_SKIPLIST_CPP
