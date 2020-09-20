/*! \file       main.cpp
 *  \author     Sergey Shershakov
 *  \version    0.2
 *  \date       18.09.2020
 *
 *  Undirected graphs.
 */

#include <iostream>

#include "ugraph.hpp"

// Creates a simple matrix.
void test1()
{

//    Matrix m;
//    Matrix::SizePair mSize = m.getSize();

//    std::cout << "Matrix's size: " << mSize << '\n';

//    m.resize(3, 4);
//    std::cout << "New matrix's size: " << m.getSize() << '\n';

//    std::cout << m << '\n';

//    m.resize(4, 5, 1);
//    std::cout << "New matrix's size (2): " << m.getSize() << '\n';

//    std::cout << m << "\n\n";     // TODO: want to print the matrix


//    // creates a vector by using the factory method Matrix::createVector()
//    Matrix::MatrixVector simpleVector =
//            Matrix::createVector(10, 2);




//    // how to get a row of a matrix:
//    Matrix::MatrixVector& m0Row0 = m.getRow(0);  //
//    m0Row0[0] = 42;
//    std::cout << "The matrix m after changing an el:\n" << m << "\n\n";     // TODO: want to print the matrix

//    const Matrix m2 = m;
//    //std::cout << "The size of the matrix m2: " << m2.getSize() << '\n';
//    //std::cout << "\nThe m2 matrix is:\n" << m2;

//    const Matrix::MatrixVector& m2Row0 = m2.getRow(0);
//    //m2Row0[0] = 42;       // not possible to assign to a const object


//    int a = 0;
}


//#include <vector>

int main()
{
    std::cout << "Let's do some undirected graphs!\n";

//    std::vector<int> iv;
//    std::vector<int>::iterator it;
//    std::vector<int>::iterator::iterator_type

    test1();
//    test2();
//    test3();

    std::cout << "\n\nBye-bye!\n\n";
    return 0;
}

