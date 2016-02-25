/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int start = 0;
    int end = n-1;
    int mid;

        while (start <= end)
        {
            mid = (start + end) / 2;

            if (value == values[mid] )
            {
                return true;
            }

            else if (value < values[mid])
            {
                end = mid - 1;
            }

            else if (value > values[mid])
            {
                start = mid +1;
            }
        }

        return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    bool iterate;
    do
    {
        iterate = false;
        for( int x = 0; x < n-1; x++)
            {   
            if (values[x] > values[x+1])
                {
                 int temp = values[x];
                 values[x] = values[x+1];
                 values[x+1] = temp;
                 iterate = true;
             }
         }
    } while (iterate);
    return;
}
