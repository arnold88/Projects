// 
// $Id: weights.hpp,v 1.1.1.1 2000/08/06 10:21:10 amos Exp $
//
// Definition of ||| class
//
// <real-name> <<mail-name>>
// Created on: <05-Nov-1999 06:43:02 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef WEIGHTS_HPP
#define WEIGHTS_HPP

const int FB_Weights[8*8] =
{
    16, 1, 10, 8, 8, 10, 1, 16,
    1,  1, 2,  2, 2, 2,  1, 1,
    10, 2, 2,  4, 4, 2,  2, 10,
    8,  2, 4,  1, 1, 4,  2, 8,
    8,  2, 4,  1, 1, 4,  2, 8,
    10, 2, 2,  4, 4, 2,  2, 10,
    1,  1, 2,  2, 2, 2,  1, 1,
    16, 1, 10, 8, 8, 10, 1, 16
};

const int FB_WeightsAdjust[8*8] =
{
    48, 16, 10, 9, 8, 7, 13, 48,
    16, 11, 8,  7, 6, 5, 0,  0,
    10, 8,  4,  0, 0, 0, 0,  8,
    9,  7,  0,  0, 0, 0, 0,  8,
    8,  6,  0,  0, 0, 0, 0,  8,
    7,  5,  0,  0, 0, 0, 0,  8,
    13, 0,  0,  0, 0, 0, 0,  0,
    48, 0,  8,  8, 8, 8, 0,  8
};

#endif // WEIGHTS_HPP
