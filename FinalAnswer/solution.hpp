#ifndef _SOLUTION_HPP_
#define _SOLUTION_HPP_

#include <string>
#include <vector>
#include "piece.hpp"

using namespace std;

class Solution {
    
private:
    string _id;
    vector<Piece> _pieces;
    vector<vector<string>> _matrix;
    
 
    void  calculateMatrix();
    
    void createStringRep();

public:
    friend bool operator== ( const Solution &s1, const Solution &s2);
    Solution() ;

    Solution(Solution *s);

    Solution(vector<Piece> *vp);

    void prepareOutput();

    void addPiece(Piece p);

    vector<Piece> getPieces();
    
    string getId();
    
    vector<vector<string>> getMatrix();


    
};

#endif
