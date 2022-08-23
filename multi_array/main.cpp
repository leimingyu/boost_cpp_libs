#include <iostream>
#include <boost/multi_array.hpp>
#include <cassert>

// References:
// [1] https://www.boost.org/doc/libs/1_61_0/libs/multi_array/doc/user.html
int main()
{
    // Create a 3D array that is 3 x 4 x 2 
    typedef boost::multi_array<int, 3> array_type;
    array_type::extent_gen extents;
    array_type A(extents[3][4][2]);

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


    // test 3 : views - a subset of data from multiarray

    // test 4: storage ordering (reshape)
    // this can be useful for permutation the tensor array for tensorflow
    // features
    //    - you can use different index bases, instead of the default zero-based one
    //    - change array shape using "reshape" operation
    //    - resize an array

    std::cout << "dim (3,4,2) \n";
    values = 0;
    for(index i = 0; i != 3; ++i) {
        for(index j = 0; j != 4; ++j) {
            for(index k = 0; k != 2; ++k) {
                A[i][j][k] = values++;
                std::cout <<  A[i][j][k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "reshape to dim (2,3,4) \n";
    int ndims=3;
    boost::array<array_type::index,3> dims = {{2,3,4}};  
    A.reshape(dims);

    for(index i = 0; i != 2; ++i) {
        for(index j = 0; j != 3; ++j) {
            for(index k = 0; k != 4; ++k) {
                std::cout <<  A[i][j][k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
