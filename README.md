
C++ Console Application ECSM-lamda-coordinates


This implements the Elliptic Curve Scalar Multiplicaion over binary field GF(2^163) using Lamda Projective Coordinates.

Features:

   * Based on Montgomery Ladder
   * Using Lamda Projective Coordniates
   * Cost of Point Addition: 10M + 3S + 2D + 9A
   * Cost of Point Doubling: 3M + 5S + 2D + 8A
   * Cost of Mixed Point Addition: 8M + 3S + 2D + 8A
   where M, S, D, A represented Multiplication, Square, Multiplication with constant, Addition respectively over the finite field GF(2^163) 

Provided the comparison of Lammda ECSM with general ECSM (left-right algorithm).