// sorting items from the heaviest to lightest
// by selecting the heaviest item at each time  

#include <iostream>
#include <vector>
#include "sort_heaviest.h"

using namespace std;

void sort_heaviest(vector<int>& v, int& comparisons)
{
    // The index of the heaviest element
    size_t heaviest;

    /* TODO */
    // Make sure to update comparisons whenever you compare elements

    for (int i = 0; i < v.size() - 1; i++)
    {
        heaviest = i;

        for ( int j = i+1; j < v.size(); j++)
        {
            comparisons = comparisons + 1;

            if (v[j] > v[heaviest])
            {
                heaviest = j;
            }
        }
        
        int temp = v[heaviest];            // swapping
        v[heaviest] = v[i];
        v[i] = temp;
    }
}