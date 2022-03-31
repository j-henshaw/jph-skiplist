#include <cassert>
#include <iostream>

#include "skiplist.h"

using namespace std;

//Tests provided from instructor
//Modified the output slightly
void test1() {
    cout << "\nBeginning instructor-provided tests (output slightly modified).\n" << endl;
    // setting seed for easy testing
    srand(10000);
    SkipList skp(5, 80);
    cout << boolalpha;
    cout << skp << endl;
    skp.add(3);
    cout << skp << endl;
    skp.add(5);
    cout << skp << endl;
    skp.add(vector<int>{1, 7, 9});
    cout << skp << endl;
    // cannot add existing
    assert( !( skp.add(vector<int>{1, 7}) ) );
    cout << skp << endl;
    cout << "7 ? " << skp.contains(7) << endl;
    cout << "3 ? " << skp.contains(3) << endl;
    cout << "-100 ? " << skp.contains(-100) << endl;
    cout << "100 ? " << skp.contains(100) << endl << endl;
    bool result = skp.remove(5);
    assert(result);
    result = skp.remove(5);
    assert(!result);
    cout << skp << endl;
    cout << "Done." << endl << endl;
}

//Tests written by me!! For edge cases & stress test
void test2(){
    cout << "Beginning Student's Edge Cases & Stress Test #1..." << endl << endl;
    SkipList* list = new SkipList(20,50);
    
    //SkipList must always contain INT_MIN and INT_MAX
    assert( list->contains(INT_MIN) );
    assert( list->contains(INT_MAX) );
    assert( !(list->remove(INT_MIN)) );
    assert( !(list->remove(INT_MAX)) );
    assert( list->contains(INT_MIN) );
    assert( list->contains(INT_MAX) );
    
    //Edge cases
    assert( !(list->contains(INT_MIN + 1)) );
    assert( !(list->contains(INT_MAX - 1)) );
    assert( !(list->remove(INT_MIN + 1)) );
    assert( !(list->remove(INT_MAX - 1)) );
    assert( !(list->contains(INT_MIN + 1)) );
    assert( !(list->contains(INT_MAX - 1)) );
    assert( list->add(INT_MIN + 1) );
    assert( list->add(INT_MAX - 1) );
    assert( list->contains(INT_MIN + 1) );
    assert( list->contains(INT_MAX - 1) );
    assert( list->remove(INT_MIN + 1) );
    assert( list->remove(INT_MAX - 1) );
    assert( !(list->contains(INT_MIN + 1)) );
    assert( !(list->contains(INT_MAX - 1)) );
    
    //Stress test
    for (int toAdd = -10000; toAdd < 10000; ++toAdd){
        //cout << toAdd << " ? ";
        assert( !(list->contains(toAdd)) );
        assert(list->add(toAdd));
        assert(list->contains(toAdd));
        //cout << toAdd << endl;
    }
    //remove and add a middle value
    assert( list->contains(500) );
    assert( list->remove(500) );
    assert( !(list->contains(500)) );
    assert( list->add(500) );
    assert( list->contains(500) );
    cout << "*Added successfully" << endl;
    vector<int> addVector;
    //empty vector
    assert( !(list->add(addVector)) );
    for (int toAdd = -10000; toAdd < 10000; ++toAdd){
        addVector.push_back(toAdd);
    }
    //all same values
    assert( !(list->add(addVector)) );
    //one new value
    assert( list->remove(1000) );
    assert(list->add(addVector));
    //all same values
    assert( !(list->add(addVector)) );
    cout << "*Vectors tested" << endl;
    //removing
    for (int toRemove = -10000; toRemove < 10000; ++toRemove){
        assert(list->contains(toRemove));
        assert( !(list->add(toRemove)) );
        assert( list->remove(toRemove) );
        assert( !(list->contains(toRemove)) );
        assert( !(list->remove(toRemove)) );
    }
    cout << "*Removement works" << endl;
    
    //For posterity
    //cout << "BIG OL LIST" << endl << list;
    
    //Do it in reverse
    for (int toAdd = 10000; toAdd > -10000; --toAdd){
        assert( !(list->contains(toAdd)) );
        assert(list->add(toAdd));
        assert(list->contains(toAdd));
    }
    //remove and add a middle value
    assert( list->contains(500) );
    assert( list->remove(500) );
    assert( !(list->contains(500)) );
    assert( list->add(500) );
    assert( list->contains(500) );
    //removing
    for (int toRemove = 10000; toRemove > -10000; --toRemove){
        assert(list->contains(toRemove));
        assert( !(list->add(toRemove)) );
        assert( list->remove(toRemove) );
        assert( !(list->contains(toRemove)) );
        assert( !(list->remove(toRemove)) );
    }
    cout << "*Functions in reverse" << endl;
    
    //Add the vector back as stress test for delete
    assert( list->add(addVector) );
    delete list;
    cout << "*Destructor functions" << endl << endl;
    
    cout << "Stress Test #1 Passed!!" << endl << endl;
    
}

//Same as test2() but with a height of 1
void test22(){
    cout << "Beginning Student's Edge Cases & Stress Test #2..." << endl << endl;
    SkipList* list = new SkipList(1,50);
    
    //SkipList must always contain INT_MIN and INT_MAX
    assert( list->contains(INT_MIN) );
    assert( list->contains(INT_MAX) );
    assert( !(list->remove(INT_MIN)) );
    assert( !(list->remove(INT_MAX)) );
    assert( list->contains(INT_MIN) );
    assert( list->contains(INT_MAX) );
    
    //Edge cases
    assert( !(list->contains(INT_MIN + 1)) );
    assert( !(list->contains(INT_MAX - 1)) );
    assert( !(list->remove(INT_MIN + 1)) );
    assert( !(list->remove(INT_MAX - 1)) );
    assert( !(list->contains(INT_MIN + 1)) );
    assert( !(list->contains(INT_MAX - 1)) );
    assert( list->add(INT_MIN + 1) );
    assert( list->add(INT_MAX - 1) );
    assert( list->contains(INT_MIN + 1) );
    assert( list->contains(INT_MAX - 1) );
    assert( list->remove(INT_MIN + 1) );
    assert( list->remove(INT_MAX - 1) );
    assert( !(list->contains(INT_MIN + 1)) );
    assert( !(list->contains(INT_MAX - 1)) );
    
    //Stress test
    for (int toAdd = -10000; toAdd < 10000; ++toAdd){
        //cout << toAdd << " ? ";
        assert( !(list->contains(toAdd)) );
        assert(list->add(toAdd));
        assert(list->contains(toAdd));
        //cout << toAdd << endl;
    }
    //remove and add a middle value
    assert( list->contains(500) );
    assert( list->remove(500) );
    assert( !(list->contains(500)) );
    assert( list->add(500) );
    assert( list->contains(500) );
    cout << "*Added successfully" << endl;
    vector<int> addVector;
    //empty vector
    assert( !(list->add(addVector)) );
    for (int toAdd = -10000; toAdd < 10000; ++toAdd){
        addVector.push_back(toAdd);
    }
    //all same values
    assert( !(list->add(addVector)) );
    //one new value
    assert( list->remove(1000) );
    assert(list->add(addVector));
    //all same values
    assert( !(list->add(addVector)) );
    cout << "*Vectors tested" << endl;
    //removing
    for (int toRemove = -10000; toRemove < 10000; ++toRemove){
        assert(list->contains(toRemove));
        assert( !(list->add(toRemove)) );
        assert( list->remove(toRemove) );
        assert( !(list->contains(toRemove)) );
        assert( !(list->remove(toRemove)) );
    }
    cout << "*Removement works" << endl;
    
    //For posterity
    //cout << "BIG OL LIST" << endl << list;
    
    //Do it in reverse
    for (int toAdd = 10000; toAdd > -10000; --toAdd){
        assert( !(list->contains(toAdd)) );
        assert(list->add(toAdd));
        assert(list->contains(toAdd));
    }
    //remove and add a middle value
    assert( list->contains(500) );
    assert( list->remove(500) );
    assert( !(list->contains(500)) );
    assert( list->add(500) );
    assert( list->contains(500) );
    //removing
    for (int toRemove = 10000; toRemove > -10000; --toRemove){
        assert(list->contains(toRemove));
        assert( !(list->add(toRemove)) );
        assert( list->remove(toRemove) );
        assert( !(list->contains(toRemove)) );
        assert( !(list->remove(toRemove)) );
    }
    cout << "*Functions in reverse" << endl;
    
    //Add the vector back as stress test for delete
    assert( list->add(addVector) );
    delete list;
    cout << "*Destructor functions" << endl << endl;
    
    cout << "Stress Test #2 Passed!!" << endl << endl;
}


//Some string tests
void test3(){
    cout << "Beginning student's string tests:\n" << endl;
    
    //Check that verticality is maintained properly
    for(int listHeight = 1; listHeight < 11; ++listHeight){
        SkipList list(listHeight,50);
        string expected = "";
        for(int stringLevel = listHeight - 1; stringLevel >= 0; --stringLevel){
            expected += "Level: ";
            expected += to_string(stringLevel);
            expected += " -- -2147483648, 2147483647, \n\n";
        }
        assert( list.toString() == expected );
        
    }
    cout << "*String tests for height passed" << endl;
    
    //Check that length and sort is maintained
    SkipList list2(1,50);
    int values[] = {-50,400,33,-200,0};
    string results[] = {
        "Level: 0 -- -2147483648, 2147483647, \n\n",
        "Level: 0 -- -2147483648, -50, 2147483647, \n\n",
        "Level: 0 -- -2147483648, -50, 400, 2147483647, \n\n",
        "Level: 0 -- -2147483648, -50, 33, 400, 2147483647, \n\n",
        "Level: 0 -- -2147483648, -200, -50, 33, 400, 2147483647, \n\n",
        "Level: 0 -- -2147483648, -200, -50, 33, 0, 400, 2147483647, \n\n",
    };
    for (int i = 0; i < 5; ++i) {
        assert( list2.toString() == results[i] );
        assert( list2.add(values[i]) );
    }
    
    cout << "*String tests for length and sort passed\n" << endl;
    cout << "Strings conform to standards." << endl << endl;
    
}

//Run all tests
int main() {
    test1();
    test2();
    test22();
    test3();
    cout << "***Done. All tests PASSED!! :D" << endl << endl;
    return 0;
}
