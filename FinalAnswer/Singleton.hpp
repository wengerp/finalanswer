#ifndef _SINGLETON_HPP_
#define _SINGLETON_HPP_



#include <vector>
#include <cmath>
#include "piece.hpp"
#include "solution.hpp"

// forward declaration
class Solution;

class Singleton {

protected:
    Singleton();

    static Singleton* singleton;

    vector<Solution>* aAllSolution;
    long numIterations;
    long numPieces;
    long rowSize;
    Piece possibleMatch;
    
public:
    Singleton(Singleton &other) = delete;
    void operator=(const Singleton &) = delete;

    static Singleton *GetInstance();

    vector<Solution>* getAllSolution() {
        return aAllSolution;
    }

    void addSolution(Solution s) {
        aAllSolution->push_back(s);
    }
    
    void setAllSolution(vector<Solution>* value) {
        for ( Solution sol : *value ) {
            this->aAllSolution->push_back(sol);
        }
    }
    
    void setNumPieces(long pPieces) {
        numPieces = pPieces;
        rowSize = sqrt(numPieces);
    }

    unsigned long getNumPieces() {
        return numPieces;
    }

    unsigned long getRowSize() {
        return rowSize;
    }

    long getNumSolutions() {
        return aAllSolution->size();
    }

    void const incNumIterations() {
        numIterations = numIterations + 1;
    }

    long* getNumIterations() {
        return &numIterations;
    }
   
    Piece getPossibleMatch() {
        return possibleMatch;
    }
    
    void setPossibleMatch(Piece value) {
        possibleMatch = value;
    }

};


#endif



    
