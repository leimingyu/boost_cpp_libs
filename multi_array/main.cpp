#include <iostream>
#include <boost/multi_array.hpp>
#include <cassert>

// References:
// [1] https://www.boost.org/doc/libs/1_61_0/libs/multi_array/doc/user.html
int main()
{
    // Create a 3D array that is 3 x 4 x 2 
    typedef boost::multi_array<int, 3> array_type;
    array_type A(boost::extents[3][4][2]);

    typedef array_type::index index; // to index the array element

    // Assign values to the elements
    int values = 0;
    for(index i = 0; i != 3; ++i) 
        for(index j = 0; j != 4; ++j)
            for(index k = 0; k != 2; ++k)
                A[i][j][k] = values++;

    // Verify values
    int verify = 0;
    for(index i = 0; i != 3; ++i) 
        for(index j = 0; j != 4; ++j)
            for(index k = 0; k != 2; ++k)
                assert(A[i][j][k] == verify++);

    // test 1: accessing elements
    A[0][0][0] = 4;
    //assert(A[0][0][0] == 5);
    assert(A[0][0][0] == 4);

    // test 2: accessing elements
    boost::array<array_type::index,3> idx = {{0,0,0}};
    A(idx) = 3;
    assert(A(idx) == 3);
    //assert(A(idx) == 4);


}
