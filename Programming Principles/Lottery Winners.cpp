//
//  70023 Lottery Winners.cpp
//  Programming Assignment 2
//
//  Created by Ben Sebring on 10/11/16.
//
//


#include <iostream>
using namespace std;

bool searchList (const long[], int, long);

int main ()
{
    long search = 0;
    int size = 10;
    const long lottery [size] = {13579, 26791, 26792, 33445, 55555, 62483, 77777, 79422, 85647, 93121};
    
    cout << "\nPlease enter this weel's 5-digit winning lottery number: ";
    cin >> search;
    
    bool linearSearch = searchList(lottery, size, search);
    if (linearSearch) {
        cout << "\nYou have a winning ticket.";
    } else {
        cout << "\nYou did not win this week."
    }
    return 0;
}

bool searchList (const long array[], int size, long searchValue)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == searchValue)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
