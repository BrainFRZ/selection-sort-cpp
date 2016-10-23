//////////////////////////////////////////////////////////////////////////
// FileName:    SelectionSort.h
// Description: Defines all methods of the interface SelectionSort.h
// Author:      Terry Weiss 466751950
// Project:     Selection Sort (Homework 4 Assignment)
//////////////////////////////////////////////////////////////////////////

#include "SelectionSort.h"


//Seeds random number generator
SelectionSort::SelectionSort()
{
    srand(static_cast<unsigned int>(time(NULL)));
}


//Creates a small random array and prints it, then sorts it and prints the new version both
//iteratively and recursively. It then does the same thing with a vector. After these are
//done, it creates a very large array and sorts it, then prints its benchmarking info. It
//then does the same thing with a vector.
void SelectionSort::go()
{
    //Direction of sort
    SortDirection direction = ASCENDING;

    std::cout << "Array sort" << std::endl;
    unsortedArray = new int[TEST_LIST_LENGTH];
    fillRandomIntList(unsortedArray, TEST_LIST_LENGTH);

    sortedArray = new int[TEST_LIST_LENGTH];
    copyArray(unsortedArray, sortedArray, TEST_LIST_LENGTH);

    direction = promptSortDirection();
    printData(unsortedArray, TEST_LIST_LENGTH);

    std::cout << "Iterative sort: ";
    iterativeSort(sortedArray, TEST_LIST_LENGTH, direction);
    printData(sortedArray, TEST_LIST_LENGTH);
    printSortTest(sortedArray, TEST_LIST_LENGTH, direction);

    std::cout << "Recursive sort: ";
    copyArray(unsortedArray, sortedArray, TEST_LIST_LENGTH);
    recursiveSort(sortedArray, TEST_LIST_LENGTH - 1, direction, true);
    printSortTest(sortedArray, TEST_LIST_LENGTH, direction);
    printData(sortedArray, TEST_LIST_LENGTH);

    std::cout << std::endl << "Vector sort" << std::endl;
    unsortedVector = std::vector<int>(TEST_LIST_LENGTH);
    fillRandomIntList(&unsortedVector, TEST_LIST_LENGTH);
    printData(&unsortedVector, TEST_LIST_LENGTH);

    sortedVector = std::vector<int>();
    iterativeSort(&sortedVector, direction);
    printData(&sortedVector, TEST_LIST_LENGTH);
}



template<class T>
void SelectionSort::fillRandomIntList(T list, const int size)
{
    for (int index = 0; index < size; index++)
    {
        list[index] = std::rand() % MAX_VALUE + 1;
    }
}

void SelectionSort::copyArray(const int oldData[], int newData[], const int size)
{
    for (int index = 0; index < size; index++)
    {
        newData[index] = oldData[index];
    }
}

void SelectionSort::printSortTest(const int data[], const int size, SortDirection direction)
{
    for (int index = size - 1; index > 0; index--)
    {
        if (shouldSwap(direction, data[index], data[index - 1]))
        {
            std::cout << "Incorrectly sorted. " << data[index] << " (index " << index
                      << ") is after " << data[index - 1] << std::endl;
        }
    }

    std::cout << "Correctly sorted." << std::endl;
}


//Determines whether to swap current ("outer" value currently in place) with the value its
//comparing to ("inner" unsorted value left in the list).
bool SelectionSort::shouldSwap(SortDirection direction, int current, int compareTo)
{
    return (((direction == ASCENDING)  && (compareTo > current))
         || ((direction == DESCENDING) && (compareTo < current)));
}


int SelectionSort::iterativeSwapIndex(int data[], int startIndex, SortDirection direction)
{
    int swapIndex = 0;

    for (int searchIndex = startIndex; searchIndex >= 0; searchIndex--)
    {
        if (shouldSwap(direction, data[swapIndex], data[searchIndex]))
        {
            swapIndex = searchIndex;
        }
    }

    return swapIndex;
}

void SelectionSort::iterativeSort(int data[], const int size, SortDirection direction)
{
    int swapIndex = 0;
    int swapValue = 0;

    for (int startIndex = size - 1; startIndex >= 0; startIndex--)
    {
        swapIndex = iterativeSwapIndex(data, startIndex, direction);

        swapValue = data[swapIndex];
        data[swapIndex] = data[startIndex];
        data[startIndex] = swapValue;
    }
}

void SelectionSort::iterativeSort(std::vector<int> *data, SortDirection direction)
{
    int swapIndex = 0;
    int swapValue = 0;

    for (int startIndex = static_cast<int>(data->size()) - 1; startIndex >= 0; startIndex--)
    {
        swapIndex = startIndex;

        for (int searchIndex = startIndex; searchIndex >= 0; searchIndex--)
        {
            if (data->at(searchIndex) > data->at(swapIndex))
            {
                swapIndex = searchIndex;
            }
        }

        swapValue = data->at(swapIndex);
        data->at(swapIndex) = data->at(startIndex);
        data->at(startIndex) = swapValue;
    }
}

void SelectionSort::recursiveSort(int data[], int start, SortDirection direction, bool recursiveSearch,
                                  int swapIndex, int swapValue)
{
    if (start <= 0)
    {
        return;
    }
    else
    {
        if (recursiveSearch)
        {
            if (swapIndex == NULL_INDEX)
            {
                recursiveSort(data, start, direction, recursiveSearch,
                              recursiveSwapIndex(data, start, direction));
            }
            else if (swapValue == NULL_SWAP_VALUE)
            {
                recursiveSort(data, start, direction, recursiveSearch,
                              swapIndex, data[swapIndex]);
            }
            else
            {
                data[swapIndex] = data[start];
                data[start] = swapValue;
                start -= 1;
                recursiveSort(data, start, direction, recursiveSearch,
                              recursiveSwapIndex(data, start, direction));
            }
        }
        else
        {
            recursiveSort(data, start - 1, direction, recursiveSearch);
            //data[start] = iterativeNextElement(data, start);
        }
    }
}

int SelectionSort::recursiveSwapIndex(const int data[], int start, SortDirection direction,
                                      int swapIndex)
{
    if (start < 0)
    {
        return swapIndex;
    }
    else if (swapIndex == NULL_INDEX)
    {
        return recursiveSwapIndex(data, start, direction, start);
    }
    else if (shouldSwap(direction, data[swapIndex], data[start]))
    {
        return recursiveSwapIndex(data, start - 1, direction, start);
    }
    else
    {
        return recursiveSwapIndex(data, start - 1, direction, swapIndex);
    }
}

void SelectionSort::recursiveSort(const std::vector<int> *oldData, std::vector<int> *newData,
                                  int start, SortDirection direction, bool recursiveSearch)
{

}

int SelectionSort::recursiveNextElement(const std::vector<int> *data, int start, SortDirection direction)
{
    return 0;
}


SelectionSort::SortDirection SelectionSort::promptSortDirection()
{
    SortDirection direction;
    std::string input;

    std::cout << "Would you like to sort a list in ascending order [Y/n]? ";
    std::cin >> input;

    if (input == "N" || input == "n")
    {
        direction = DESCENDING;
    }
    else
    {
        direction = ASCENDING;
    }

    return direction;
}


template<class T>
void SelectionSort::printData(const T data, const int size)
{
    for (int index = 0; index < size; index++)
    {
        std::cout << data[index] << " ";
    }

    std::cout << std::endl;
}
