//
//  piece.cpp
//  FinalAnswer
//
//  Created by Patrick Wenger on 27.10.22.
//

#include <stdio.h>
#include "piece.hpp"

bool operator== ( const Piece &p1, const Piece &p2)
{
        return p1._id == p2._id;
}
