#ifndef _SINGLETON_HPP_
#define _SINGLETON_HPP_



#include <vector>
#include <cmath>
#include "piece.hpp"
#include "Singleton.hpp"

class Singleton {

protected:
    Singleton();

    static Singleton* singleton;

    vector<vector<Piece>>* aAllSolution;
    long numIterations;
    long numPieces;
    long rowSize;
    Piece possibleMatch;
    
public:
    Singleton(Singleton &other) = delete;
    void operator=(const Singleton &) = delete;

    static Singleton *GetInstance();

    vector<vector<Piece>>* getAllSolutions() {
        return aAllSolution;
    }

    void setAllSolution(vector<vector<Piece>>* value) {
        aAllSolution = value;
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



    
