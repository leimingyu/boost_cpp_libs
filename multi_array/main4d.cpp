#include <iostream>
#include <boost/multi_array.hpp>
#include <cassert>

// References:
// [1] https://www.boost.org/doc/libs/1_61_0/libs/multi_array/doc/user.html
int main()
{
    // Create a 4D array that is 2 x 3 x 4 x 1 
    typedef boost::multi_array<int, 4> array_type;
    array_type::extent_gen extents;
    array_type A(extents[2][3][4][1]);

    typedef array_type::index index; // to index the array element

    // Assign values to the elements
    int values = 0;
    for(index i = 0; i != 2; ++i)
        for(index j = 0; j != 3; ++j)
            for(index m = 0; m != 4; ++m)
                for(index n = 0; n != 1; ++n)
                    A[i][j][m][n] = values++;

    // Verify values
    int verify = 0;
    for(index i = 0; i != 2; ++i)
        for(index j = 0; j != 3; ++j)
            for(index m = 0; m != 4; ++m)
                for(index n = 0; n != 1; ++n)
                    assert(A[i][j][m][n] == verify++);


    // test 1: accessing elements
    A[0][0][0][0] = 4;
    assert(A[0][0][0][0] == 4);

    // test 2: accessing elements
    boost::array<array_type::index,4> idx = {{0,0,0,0}};
    A(idx) = 3;
    assert(A(idx) == 3);

    // test 3: change array shape using "reshape" operation

    std::cout << "dim (2,3,4,1) \n";
    values = 0;
    for(index i = 0; i != 2; ++i) {
        for(index j = 0; j != 3; ++j) {
            for(index m = 0; m != 4; ++m) {
                for(index n = 0; n != 1; ++n) {
                    A[i][j][m][n] = values++;
                    std::cout <<  A[i][j][m][n] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "reshape to dim (1,3,4,2) \n";
    boost::array<array_type::index,4> dims = {{1,3,4,2}};  
    A.reshape(dims);

    for(index i = 0; i != 1; ++i) {
        for(index j = 0; j != 3; ++j) {
            for(index m = 0; m != 4; ++m) {
                for(index n = 0; n != 2; ++n) {
                    std::cout <<  A[i][j][m][n] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

}
