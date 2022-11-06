#ifndef _SINGLETON_CPP
#define _SINGLETON_CPP



#include <stdio.h>
#include <vector>
#include "piece.hpp"
#include "Singleton.hpp"

Singleton::Singleton() {
    numIterations = 0;
    rowSize = 0;
    aAllSolution = {};
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



#endif
