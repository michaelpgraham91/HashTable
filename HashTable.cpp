// Author: Michael Graham
//
// Spring 2018 - CS 3358 - Section 0
//
// This program creates an array of 30 integers and assigns
// 15 of those values to random numbers between 125 and 425
// inclusive. These values are passed through a hash function
// before they are added to determine their position in the array.
// If a collision occurs linear probing is used to determine
// the new position in the array. There are functions to
// display the array elements, search for values in the array,
// add values, and delete values. On program termination,
// the number of collisions that occurred when creating the array
// as well as the number of collisions that occurred when adding
// values to the array will be displayed.

#include <iostream>
#include <ctime>

using namespace std;

class Hash{
private:
    int hash_pos;
    int arr[30];
    int numCollisions;
    int numHashes;
public:
    Hash();
    void populate();
    void insertValue();
    void Search();
    int hashValue(int);
    int reHash(int);
    void Delete();
    void Display();
    int getNumCollisions();
    int getNumHashes();
};

int main(int argc, char** argv) {
    char i = ' ';
    bool repeat = true;
    Hash hash1;
    srand(time(nullptr));

    cout << "Welcome to my Hashing Program\n\n";
    cout << "---------------------------------\n\n";
    cout << "1. Creates an integer array of size 30. Assigning * to each\n";
    cout << "   location in the array indicating that the array is empty.\n";
    cout << "2. Populates half the array with random integer values\n";
    cout << "   between 125 and 425 inclusive.\n";
    cout << "3. If a collision occurs, linear probing will fine the next\n";
    cout << "   available position / location.\n";
    cout << "4. The generated array will be displayed in 2 lines.\n";
    cout << "   Each line contains 15 number separated by 2 spaces.\n\n";

    hash1.populate();
    cout << "Generated Array" << endl;
    cout << "---------------\n\n";

    hash1.Display();

    do {
        cout << "\nSelect from the following menu options: \n\n";
        cout << "A. Display the generated array.\n";
        cout << "B. Search for a number (between 125-425) in the array.\n";
        cout << "C. Insert a new number (between 125=425) in the array.\n";
        cout << "D. Delete a number (between 125-425) from the array.\n";
        cout << "X. End the program.\n";
        cout << "\nSelect your option: "; cin >> i;

        if(cin.fail()) {
            cin.clear();
            cin.ignore();
            i = -1;
        }

        switch(i) {
            case 'a': case 'A': {
                cout << "Displaying the generated array.\n\n";
                hash1.Display();
                cout << "\n\n";
                break;
            }
            case 'b': case 'B': {
                hash1.Search();
                break;
            }
            case 'c': case 'C': {
                hash1.insertValue();
                break;
            }
            case 'd': case 'D': {
                hash1.Delete();
                break;
            }
            case 'x': case 'X': {
                repeat = false;
                break;
            }
            default: {
                cout << "*** Invalid Option ***\n";
                break;
            }
        }
    } while(repeat == true);

    cout << "Number of probes while hashing is: ";
    cout << hash1.getNumHashes() << endl;
    cout << "Number of collisions while adding values is : ";
    cout << hash1.getNumCollisions() << endl;
    cout << "\nThis Hashing Program was Implemented by\n";
    cout << "Michael Graham - April 30, 2018";
    return 0;
}
// Constructor for hash class, initializes all values to
// '*' and sets collision and hash counters to zero
Hash::Hash() {
    for(int i=0; i<30; i++) {
        arr[i] = '*';
    }
    numCollisions = 0;
    numHashes = 0;
}

// Fills 15 of the 30 array positions with randomly generated numbers
// between 125 and 425. Uses the hash function to assign them to the
// array
void Hash::populate() {
    int r;
    int hash_pos;
    for(int i=0; i<15; i++) {
        r = rand() % 301 + 125;
        hash_pos = hashValue(r);
        if(hash_pos >= 30) {
            hash_pos = 0;
            }
        while(arr[hash_pos] != '*') {
            hash_pos = reHash(hash_pos);
            numHashes++;
        }
        if(arr[hash_pos] == '*') {
            arr[hash_pos] = r;
        }
    }
}

// Hash function, uses value of data modulo the size of the array
int Hash::hashValue(int data) {
    return (data % 30);
}
// ReHash function, adds 1 to the data and hashes
int Hash::reHash(int data) {
    return ((data+1) % 30);
}
// Inserts data with hash function and provides appropriate feedback
// if table is full
void Hash::insertValue() {
    int data;
    int counter = 0;
    cout << "Enter the data to insert: ";
    cin >> data;
    hash_pos = hashValue(data);
    if(hash_pos >= 30) {
        hash_pos = 0;
    }
    while(arr[hash_pos] != '*') {
        hash_pos = reHash(hash_pos);
        numCollisions++;
        counter++;
        if(counter>=30) {
            cout << "Memory Full! No space is available for storage";
            break;
        }
    }
    if(arr[hash_pos] == '*') {
        arr[hash_pos] = data;
    }
    cout << "Data is stored at index " << hash_pos << endl;
}
// Searches for value in hash table by using the hash function to determine
// position. Provides appropriate response if value is not found
void Hash::Search() {
    int key;
    int key_pos;
    cout << "Enter the key to search: "; cin >> key;
    key_pos = hashValue(key);
    if(key == arr[key_pos]) {
        cout << "\nThe number " << key << " is found at index : ";
        cout << key_pos << endl;
        return;
    }
    for(int i=1; i<30; i++) {
        key_pos = reHash(key_pos);
        if(key == arr[key_pos]) {
            cout << "\nThe number ";
            cout << key << " is found at index: " << key_pos << endl;
            return;
        }
    }
    cout << "Key not found\n";
}
// Searches for value by using hash function and sets it to '*' if found,
// notifies user if value is not found
void Hash::Delete() {
    int key;
    int key_pos;
    cout << "Enter the key to delete: ";
    cin >> key;
    key_pos = hashValue(key);
    if(key == arr[key_pos]) {
        cout << "Key deleted\n";
        arr[key_pos] = '*';
        return;
    }
    for(int i=1; i<30; i++) {
        key_pos = reHash(key_pos);
        if(key == arr[key_pos]) {
            cout << "\nKey deleted\n" << endl;
            arr[key_pos] = '*';
            return;
        }
    }
    cout << "Key not found\n";
}
// Shows values in hash table in lines of 15 separated by two spaces
void Hash::Display() {
    int lineBreak = 0;
    for(int i=0; i<30; i++) {
        cout << arr[i] << "  ";
        lineBreak++;
        if(lineBreak % 15 == 0) {
            cout << endl;
        }
    }
}

int Hash::getNumCollisions() {
    return numCollisions;
}

int Hash::getNumHashes() {
    return numHashes;
}
