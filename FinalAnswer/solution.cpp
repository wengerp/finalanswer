//
//  solution.cpp
//  FinalAnswer
//
//  Created by Patrick Wenger on 08.11.22.
//

#include "solution.hpp"
#include "Singleton.hpp"

bool operator== ( const Solution &s1, const Solution &s2)
{
        return s1._id == s2._id;
}

void  Solution::calculateMatrix() {
     unsigned long M =  Singleton::GetInstance()->getRowSize() * 2;
     unsigned long N =  Singleton::GetInstance()->getRowSize();
     unsigned long  offset = 0;
     string default_value = "_";
     vector<string> v(N, default_value);
     vector<vector<string>> matrix(M, v);

     for (int i = 0; i < Singleton::GetInstance()->getRowSize() * 2; ++i ) {
         for ( int j = 0; j < Singleton::GetInstance()->getRowSize();  ++j ) {
              if ( i > 11 ){
                  offset = Singleton::GetInstance()->getRowSize() * 6;
              } else if ( i > 9 ){
                  offset = Singleton::GetInstance()->getRowSize() * 5;
              } else if ( i > 7 ){
                  offset = Singleton::GetInstance()->getRowSize() * 4;
              } else if ( i > 5 ){
                  offset = Singleton::GetInstance()->getRowSize() * 3;
              } else if ( i > 3 ){
                  offset = Singleton::GetInstance()->getRowSize() * 2;
              } else if ( i > 1 ) {
                  offset = Singleton::GetInstance()->getRowSize() * 1;
              } else if ( i > -1 ) {
                  offset = 0;
              }
              if (i % 2 == 0 ) {
                  
                  matrix[i][j] = _pieces[j + offset].getColors().substr(0,2);

              }  else {
                  matrix[i][j] = _pieces[j + offset].getColors().substr(3,1) + _pieces[j + offset].getColors().substr(2,1);
              }
         }
    }
    copy(matrix.begin(), matrix.end(), back_inserter(_matrix));
 }
 
 void Solution::createStringRep () {
     
      vector<string> vUniSols;
     string sUniSol;
     string sLine;
     
     if (_matrix.size() == 0) {
         return;
     }
     for ( int i = 0; i < Singleton::GetInstance()->getRowSize() * 2; ++i) {
         string sLine;
         for ( int j = 0; j < Singleton::GetInstance()->getRowSize(); ++j) {
             string sC = _matrix[i][j];
             sLine = sLine + sC;
         }
         sUniSol = sUniSol + sLine;
     }
     _id = sUniSol;
 }

Solution::Solution() {
    _id = "";
    _pieces = vector<Piece>(Singleton::GetInstance()->getNumPieces() * 4);
}

Solution::Solution(Solution *s) {
    this->_id = s->_id;
    copy(s->_pieces.begin(), s->_pieces.end(), back_insert_iterator(this->_pieces));
}

Solution::Solution(vector<Piece> *vp) {
    this->_id = "";
    copy(vp->begin(), vp->end(), back_insert_iterator(this->_pieces));
}

void Solution::prepareOutput() {
    this->calculateMatrix();
    this->createStringRep();
}

void Solution::addPiece(Piece p) {
    _pieces.push_back(p);
}

vector<Piece> Solution::getPieces() {
    return _pieces;
}

string Solution::getId() {
    return _id;
}

vector<vector<string>> Solution::getMatrix() {
    return _matrix;
}
