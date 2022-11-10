/*
 Singleton.cpp
 
 */

#include <stdio.h>
#include <vector>
#include "piece.hpp"
#include "Singleton.hpp"

Singleton::Singleton() {
    aAllSolution = new vector<Solution>();
    numIterations = 0;
    numPieces = 0;
    rowSize = 0;
    possibleMatch = Piece();
    }

Singleton* Singleton::singleton = nullptr;;


Singleton *Singleton::GetInstance()
{
    if(singleton == nullptr){
        singleton = new Singleton();
    }
    return singleton;
}



