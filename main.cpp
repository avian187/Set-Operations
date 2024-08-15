/********************************************
*	DEVELOPER:	Ian Utnehmer
* COLLABORATORS: N/A
*	COURSE:	CS226 Discrete Structures
*	PROJECT:	2
*	LAST MODIFIED:	3/3/2024
********************************************/
/********************************************
*	<TITLE OF PROGRAM>
 *	Set Operations Manipulator
*********************************************
*	PROGRAM DESCRIPTION:
*	Takes two input sets and performs the following operations:
 * 1. A ∪ B (the union of A and B)
 * 2. A ∩ B (the intersection of A and B)
 * 3. A x B (the Cartesian product of A and B)
 * 4. A ⊕ B (the symmetric difference of A and B)
 * 5. P(A) (the power set of A)
 * Results are output to a file and the console.
 *
 * INPUT FILE FORMAT:
 * Elements are separated by spaces.
 * The first line contains the size of set A.
 * The second line contains the elements of set A.
 * The third line contains the size of set B.
 * The last (fourth) line contains the elements of set B.
 *
 * OUTPUT FILE FORMAT:
 * The output file contains the results of the operations in the following format:
 * A ∪ B: <elements of union>
 * A ∩ B: <elements of intersection>
 * A x B: <pairs of cartesian product>
 * A ⊕ B: <elements of symmetric difference>
 * P(A): <elements of power set>
*********************************************
*	FUNCTIONS:
*  main() - reads the input file, performs the operations, and writes the results to an output file
 *  No other functions are required.
*********************************************/

/*********************************************
*	SETUP STATEMENTS and PURPOSE:
*********************************************/

#include <iostream> // for input and output
#include <set> // for set operations
#include <fstream> // for file input and output

using namespace std;

int main() {
    // Read the set from the file first:
    set <int> setA;
    set <int> setB;
    set <int> unionSet;
    set <int> intersectionSet;
    set <pair<int, int>> cartesianProduct;
    set <int> symmetricDifference;
    set <int> powerSet;
    int powerSetSize;
    int setASize;
    int setBSize;

    ifstream file;
    file.open("input.txt");
    if (!file) {
        cerr << "Unable to open file";
        exit(1);
    }
    int setSize;
    file >> setSize;
    int element;
    for (int i = 0; i < setSize; i++) {
        file >> element;
        setA.insert(element);
    }

    file >> setSize;
    for (int i = 0; i < setSize; i++) {
        file >> element;
        // Include duplicates when reading the set
        setB.insert(element);
    }
    file.close();

    // Print the sets to the console
    cout << "Set A: { ";
    for (auto i : setA) {
        cout << i << (i != *setA.rbegin() ? ", " : " }\n"); // print the element and a comma if it's not the last element
    }
    cout << "Set B: { ";
    for (auto i : setB) {
        cout << i << (i != *setB.rbegin() ? ", " : " }\n"); // print the element and a comma if it's not the last element
    }

    // Now we can perform the operations:
    // 1. A ∪ B (the union of A and B)
    for (int i : setA) {
        unionSet.insert(i); // insert all elements of setA into unionSet
    }
    for (int i : setB) {
        unionSet.insert(i);  // insert all elements of setB into unionSet
    }
    cout << "A Union B: ";
    for (auto i : unionSet) {
        cout << i << " "; // print the unionSet
    }
    // This works because the set data structure automatically removes duplicates
    cout << endl;

    // 2. A ∩ B (the intersection of A and B)
    for (int i : setA) { // for each element in setA
        if (setB.find(i) != setB.end()) { // if the element is also in setB
            intersectionSet.insert(i); // insert the element into intersectionSet
        }
    }
    cout << "A Intersect B: ";
    for (auto i : intersectionSet) { // print the intersectionSet
        cout << i << " ";
    }
    cout << endl;

    // 3. A x B (the Cartesian product of A and B)
    // Include duplicates
    for (int i : setA) {
        for (int j : setB) {
            cartesianProduct.insert(make_pair(i, j)); // insert the pair (i, j) into cartesianProduct
        }
    }
    cout << "A Cross B: ";
    for (auto i : cartesianProduct) { // print the cartesianProduct
        cout << "(" << i.first << ", " << i.second << ") "; // print the pair
    }
    cout << endl;

    // 4. A ⊕ B (the symmetric difference of A and B)
    for (int i : setA) {
        if (setB.find(i) == setB.end()) { // if the element is not in setB
            symmetricDifference.insert(i); // insert all elements of setA that are not in setB into symmetricDifference
        }
    }
    for (int i : setB) {
        if (setA.find(i) == setA.end()) {
            symmetricDifference.insert(i); // insert all elements of setB that are not in setA into symmetricDifference
        }
    }
    cout << "A Symmetric Difference B: ";
    if (symmetricDifference.empty()) cout << "{ }";
    else for (auto i : symmetricDifference) {
        cout << i << " ";
    }
    // If the result is the empty set, print "Empty Set"
    cout << endl;

    // 5. P(A) (the power set of A)
    // The power set of a set is the set of all subsets of that set
    powerSetSize = 1 << setA.size(); // the size of the power set is 2^size of setA
    cout << "Power Set of A: " << endl;
    for (int i = 0; i < powerSetSize; i++) {
        cout << "{ ";
        int index = 0;
        for (int it : setA) {
            if (i & (1 << index)) { // if the jth bit of i is set
                cout << it << " "; // print the element
            }
            index++;
        }
        cout << "}" << endl;
    }



    // Now we can write the results to a file:
    ofstream fileOut;
    fileOut.open("output.txt");
    if (!fileOut) {
        cerr << "Unable to open file";
        exit(1);
    }
    fileOut << "A ∪ B: ";
    for (auto i : unionSet) {
        fileOut << i << " ";
    }
    fileOut << endl;
    fileOut << "A ∩ B: ";
    for (auto i : intersectionSet) {
        fileOut << i << " ";
    }
    fileOut << endl;
    fileOut << "A x B: ";
    for (auto i : cartesianProduct) {
        fileOut << "(" << i.first << ", " << i.second << ") ";
    }
    fileOut << endl;
    fileOut << "A ⊕ B: ";
    for (auto i : symmetricDifference) {
        fileOut << i << " ";
    }
    fileOut << endl;
    fileOut << "P(A): " << endl;
    for (int i = 0; i < powerSetSize; i++) {
        fileOut << "{ ";
        for (int j = 0; j < setA.size(); j++) {
            if (i & (1 << j)) {
                fileOut << j << " ";
            }
        }
        fileOut << "}" << endl;
    }
    fileOut.close();
    return 0;
}
