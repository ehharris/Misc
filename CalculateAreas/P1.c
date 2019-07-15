// P1 Assignment
// Author: Eli Harris
// Date:   8/23/2017
// Class:  CS270
// Email:  ehharris@rams.colostate.edu

// Include files
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void computeCircle(double diameter, double *addressOfVolume)
{
    // Compute volume
    double result = (3.141593 * diameter * diameter) / 4;

    // Dereference pointer to return result
    *addressOfVolume = result;
}

void computeTriangle(double side, double *addressofArea)
{
    // Compute volume
    double result = .433013 * side * side;

    // Dereference pointer to return result
    *addressofArea = result;
    
}

void computeRectangle(double side, double side2, double *addressofArea)
{
    // Compute volume
    double result = side * side2;
    // Dereference pointer to return result
    *addressofArea = result;
    
}

void computeHexagon(double side, double *addressofArea)
{
    // Compute volume
    double result;
    computeTriangle(side, &result);
    result = result * 6;

    // Dereference pointer to return result
    *addressofArea = result;
    
}

int main(int argc, char *argv[])
{
    // Check number of arguments
    if (argc != 6) {
        printf("usage: ./P1 double double double double double\n");
        return EXIT_FAILURE;
    }
    // Parse arguments
    
    double sides[5] = {atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5])};
    double results[4];
    

    // Call function
    computeCircle(sides[0], &results[0]);
    
    // Print volume
    printf("CIRCLE, diameter = %.5f, area = %.5f.\n", sides[0], results[0]);
    
    computeTriangle(sides[1], &results[1]);
    printf("TRIANGLE, side = %.5f, area = %.5f.\n", sides[1], results[1]);
    
    computeRectangle(sides[2], sides[3], &results[2]);
    printf("RECTANGLE, side1 = %.5f, side2 = %.5f, area = %.5f.\n", sides[2], sides[3], results[2]);
    
    computeHexagon(sides[4], &results[3]);
    printf("HEXAGON, side = %.5f, area = %.5f.\n", sides[4], results[3]);
    // Return success
    return EXIT_SUCCESS;
}
