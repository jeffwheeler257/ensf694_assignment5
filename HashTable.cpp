/*
 *  HashTable.cpp
 *  ENSF 694 Lab 4 - Exercise D
 *  Created by Jeff Wheeler
 *  Submission date: August 2, 2024
 */

#include "HashTable.h"
#include <iostream>

unsigned int HashTable::hashFunction(const string &flightNumber) const {
    unsigned int hash_number;
    for (int i = 0; i < int(flightNumber.size()); i++){
        hash_number += int(flightNumber[i]);
    }
    hash_number = ((67*hash_number + 41)%101);
    return hash_number % this->tableSize;
}

HashTable::HashTable(unsigned int size){
    tableSize = size;
    numberOfRecords = 0;
    firstPassRecords = 0;
    table.resize(size);
}

void HashTable::insert(const Flight &flight){
    if(this->insertFirstPass(flight)){
        return;
    }
    this->insertSecondPass(flight);
}
    
bool HashTable::insertFirstPass(const Flight &flight){
    unsigned int position = this->hashFunction(flight.flightNumber);
    if (table.at(position).isEmpty()){
        table.at(position).insert(flight);
        numberOfRecords++;
        firstPassRecords++;
        return true;
    }
    return false;
}
    
void HashTable::insertSecondPass(const Flight &flight){
    unsigned int position = this->hashFunction(flight.flightNumber);
    table.at(position).insert(flight);
    numberOfRecords++;
}
    
Flight* HashTable::search(const string &flightNumber) const{
    Flight* temp = nullptr;
    for (int i = 0; i < int(tableSize); i++){
        temp = table.at(i).search(flightNumber);
        if (temp != nullptr){
            return temp;
        }
    }
    return temp;
}
    
double HashTable::calculatePackingDensity() const{
    if (tableSize > 0)
        return double(firstPassRecords)/tableSize;
    return -1.0;
}
    
double HashTable::calculateHashEfficiency() const{
    if (firstPassRecords > 0)
        return this->calculatePackingDensity()/(numberOfRecords/firstPassRecords);
    return -1.0;
}
    
void HashTable::display() const{
    for(int i = 0; i < int(tableSize); i++){
        cout << "Bucket " << i << ":" << endl;
        table.at(i).display();
    }
}