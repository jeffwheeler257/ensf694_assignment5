//
//  HashTable.h
//  Flight Hash Table Using Linked List
//
//  Created by Mahmood Moussavi on 2024-05-25.
//

#ifndef HashTable_h
#define HashTable_h
#include "List.h"
#include "Flight.h"
#include <vector>

class HashTable {
private:
    vector<List> table;
    unsigned int tableSize;
    unsigned int numberOfRecords;
    unsigned int firstPassRecords;
    
    // REQUIRES: flight number
    // PROMISES: returns a hash/index number created by a hash funciton
    // developed by students
    unsigned int hashFunction(const string &flightNumber) const;
    
public:
    // PROMISES: intializes the data members tableSize with size, numberOfRecords to zero
    // vector table to the size, calling resize member of class vector.
    HashTable(unsigned int size);
    
    // PROMISE: inserts a flight into the vector table, at the position indicated by the
    // hash function, updates the numberOfRecords
    void insert(const Flight &flight);
    
    // PROMISE: inserts a flight into the vector table, at the position indicated by the
    // hash function, if it is empty on the first pass, then updates the numberOfRecords
    bool insertFirstPass(const Flight &flight);
    
    // PROMISE: After the first pass, inserts a flight into the vector table, at the position indicated by the
    // hash function, using chaining concept, then updates the numberOfRecords
    void insertSecondPass(const Flight &flight);
    
    // PROMISES: searches the table and returns a pointer to the found flight.
    // returns nullptr if it fails
    Flight* search(const string &flightNumber) const;
    
    // PROMISES: returns pcksing density
    double calculatePackingDensity() const;
    
    // PROMISES: reutrns hash efficiency
    double calculateHashEfficiency() const;
    
    // PROMISES: displays the flights in each "Bucket" of table, calling the linked list
    // display member function.
    void display() const;
};
#endif
