# N-Dimensional-Array

A basic n-dimensional array to demonstrate explicit operator recursion and compile time variadic template expansion into arrays. Oh and object suicide.

An example of a 5th-dimensional array.
```C++
#include <iostream>
#include "Header.hpp"
using namespace std;

int main() {
    multi_array<int, 5, 2, 2, 2, 2> mygrid;
    /* Display Dimensions */
    cout << "W: " << mygrid.dimensions[0] << endl;
    cout << "H: " << mygrid.dimensions[1] << endl;
    cout << "D: " << mygrid.dimensions[2] << endl;
    cout << "T: " << mygrid.dimensions[3] << endl;
    cout << "S: " << mygrid.dimensions[4] << endl << endl;
    cin.get();

    /* Populate all indices in 1D */
    for (int j = 0; j < mygrid.dimensions[4] * mygrid.dimensions[3] * mygrid.dimensions[2] * mygrid.dimensions[1] * mygrid.dimensions[0]; j++) {
        mygrid.pointer[j] = 0;
    }

    cout << endl;

    /* Displays 5D Madness */
    for (int s = 0; s < mygrid.dimensions[4]; s++) {
        cout << "******************** 5D ********************" << endl;

        for (int t = 0; t < mygrid.dimensions[3]; t++) {
            cout << "************ 4D ************" << endl;

            for (int k = 0; k < mygrid.dimensions[2]; k++) {
                cout << "****** 3D ******" << endl;
                for (int j = 0; j < mygrid.dimensions[1]; j++) {
                    for (int i = 0; i < mygrid.dimensions[0]; i++) {
                        mygrid[i][j][k][t][s] = rand() % 20;
                        cout << (mygrid[i][j][k][t][s] = rand() % 20) << ", ";
                    }

                    cout << endl;
                }

                cout << "****** 3D ******" << endl << endl;
            }

            cout << "************ 4D ************" << endl << endl;
        }

        cout << "******************** 5D ********************" << endl << endl;
    }

    cin.get();
}
``
