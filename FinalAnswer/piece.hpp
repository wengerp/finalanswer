#ifndef _PIECE_HPP_
#define _PIECE_HPP_

#include <iostream>
#include <iomanip>
#include <string>
#include "termcolor.hpp"

using namespace std;

static int ID;

class Piece {

private:
    int _id;
    string _originalColors;
    string _colors;
    
    
public:
    friend bool operator== ( const Piece &p1, const Piece &p2);

    
    bool operator < (const Piece& p) const
    {
        return (_id < p._id);
    }
 
    Piece() {
        _id = 0;
        _colors = "";
        _originalColors = "";
        init(_id, _colors, _originalColors);
    };

    Piece(const string colors) {
        _colors = colors;
        init(0,colors,"");
    };

    Piece(int id, const string colors, const string originalColors) {
        _colors = colors;
        init(id, colors, originalColors);
    };
    
    void init(int id, const string colors, const string originalColors) {
        
        ++ID;
        
        if ( id == 0) {
            _id = ID;
        }
        else {
            _id = id;
        }

        if ( originalColors.length() == 0) {
            _originalColors = colors;
        }
        else {
            _originalColors = originalColors;
        }
    };
    
    int getId() const {
        return _id;
    }

    string getColors() const {
        return _colors;
    }

    void setColors(string value) {
        _colors = value;
    }

    string getOriginalColors() const {
        return _originalColors;
    }
    

    void print() const {
        cout << termcolor::blue << "PIECE: ( _id:" << setw(3) << termcolor::reset << to_string(_id) << termcolor::blue << ", _colors:" << termcolor::reset << _colors << termcolor::blue << ", _originalColors:" << termcolor::blue << _originalColors << " )" << termcolor::reset << endl;
    };
    
    string toString() const {
        string outString;
        outString = "PIECE: ( _id:" + to_string(_id) + ", _colors:" + _colors + ", _originalColors:" + _originalColors +  " )";
        return outString;
    }

    Piece rotate() {
        Piece oNew(_id, _colors, _originalColors);
        string sColors = oNew.getColors();
        
        string sNewColors = { sColors[1], sColors[2], sColors[3], sColors[0] };
        oNew._colors = sNewColors;
        return oNew;
    }

};


#endif
