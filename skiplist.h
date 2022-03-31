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

#ifndef ASS4_SKIPLIST_H
#define ASS4_SKIPLIST_H

#include <iostream>
#include <vector>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <string>
using namespace std;

//Must be declared to be referenced
class SkipList;


class SNode {
    //Only SkipList class can create SNode objects
    friend class SkipList;
    //Prints the value of the node's data field only
    friend ostream &operator<<(ostream &out, const SNode& node);

    private:
        //Constructor
        explicit SNode(int value);

        //Data contained in the SNode
        int data;

        //Link to rightward SNode
        SNode* right;
        //Link to leftward SNode
        SNode* left;
        //Link to upward SNode
        SNode* up;
        //Link to downward SNode
        SNode* down;
    
    public:
        //Retruns this SNode's data field as a string
        string toString() const;
};

class SkipList {
    //Prints all data from every possible row of the SkipList
    //Every row of every SkipList always contains INT_MIN and INT_MAX,
    //even if no other values have been added to that row. As a result,
    //this operator becomes unwieldy at high values for maxLevel
    friend ostream &operator<<(ostream &out, const SkipList &skip);

    public:
        //Constructor: Default SkipList
        //Has only 1 level, just one doubly-linked list
        //To deliver on O(log(n)) behavior:
        //maxLevel should be log(expected size), and probability = 50
        //Every SkipList always contains INT_MIN and INT_MAX
        //maxLevel can be on range [1,INT_MAX]
        //probability can be on range [0,99]
        explicit SkipList(int maxLevel = 1, int probability = 0);
        //Destructor
        virtual ~SkipList();

        //Copy not allowed
        SkipList(const SkipList &other) = delete;
        //Move not allowed
        SkipList(SkipList &&other) = delete;
        //Assignment not allowed
        SkipList &operator=(const SkipList &other) = delete;
        //Move assignment not allowed
        SkipList &operator=(SkipList &&other) = delete;

        //Returns true if successfully added, otherwise returns false.
        //No duplicates allowed in the SkipList
        //Every SkipList always contains INT_MIN and INT_MAX
        bool add(int value);
        //Attempts to add each element from the vector to the SkipList.
        //Returns true if any value was successfully added, false if
        //the list remains unchanged. No duplicates are allowed in a
        //SkipList, and every SkipList always contains INT_MIN and INT_MAX
        bool add(const vector<int> &values);
        //Attempts to find and remove the given integer from the SkipList.
        //If it is found, it will be removed, and true will be returned.
        //Otherwise, the list will remain unchanged, and returns false.
        //However, if you attempt to remove INT_MIN or INT_MAX, the list
        //will remain unchanged and returns false
        bool remove(int data);
        //Returns true if the value is contained in SkipList
        //Every SkipList always contains INT_MIN and INT_MAX
        bool contains(int data) const;
    
        //Provides a string representation of this SkipList
        //Every row of every SkipList always contains INT_MIN and INT_MAX,
        //even if no other values have been added to that row. As a result,
        //this operator becomes unwieldy at high values for maxLevel
        string toString() const;

    private:
        //Pointer to bottom level's left guardian
        SNode* head;
        //Maximum number of levels, on the range [1,INT_MAX]
        int maxLevel;
        //Probability% of inserting at a higher level on the range [0,99]
        int probability;
        
        //Given a newNode, place it after the given prevNode
        //Does not modify up/down pointers, only left/right
        void addAfter(SNode* prevNode, SNode* newNode);
        //Returns true probability% of time
        //If probability == 50, returns true 50% of the time
        bool shouldInsertAtHigher() const;
        //Probabilistically builds higher levels for given node, and all
        //requisite connections. Height will not exceed maxLevel
        void buildUp(SNode* baseNode);
        //Returns a pointer to the SNode on the bottom row of the
        //SkipList who's data value is the greatest in the list still
        //satisfying: (data <= value)
        SNode* closestSNode(int value) const;
};


#endif // ASS4_SKIPLIST_H
