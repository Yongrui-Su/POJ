#include <iostream>
#include <algorithm>
using namespace std;
 
// Returns number of bins required using next fit 
// online algorithm
int firstFit(int weight[], int n, int c)
{
    // Initialize result (Count of bins)
    int res = 0;
 
    // Create an array to store remaining space in bins
    // there can be at most n bins
    int bin_rem[n];
 
    // Place items one by one
    for (int i=0; i<n; i++)
    {
        // Find the first bin that can accommodate
        // weight[i]
        int j;
        for (j=0; j<res; j++)
        {
            if (bin_rem[j] >= weight[i])
            {
                bin_rem[j] = bin_rem[j] - weight[i];
                break;
            }
        }
 
        // If no bin could accommodate weight[i]
        if (j==res)
        {
            bin_rem[res] = c - weight[i];
            res++;
        }
    }
    return res;
}
 
 
// Driver program
int main()
{
    int weight[] = {6,3,7,4};
    int c = 10;
    sort(weight,weight+sizeof(weight)/sizeof(int));
    int n = sizeof(weight) / sizeof(weight[0]);
    cout << "Number of bins required in First Fit : "
         << firstFit(weight, n, c)<<endl;;
    return 0;
}
