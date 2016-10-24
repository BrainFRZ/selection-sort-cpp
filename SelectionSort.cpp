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
    //Direction of sorts
    SortDirection direction = promptSortDirection();

    runArraySort(TEST_LIST_LENGTH, direction, true);
    runVectorSort(TEST_LIST_LENGTH, direction, true);

    std::cout << std::endl;

    runArraySort(LARGE_LIST_LENGTH, direction, false);
    runVectorSort(LARGE_LIST_LENGTH, direction, false);
}

void SelectionSort::runArraySort(const int size, const SortDirection direction, const bool print)
{
    std::cout << "Array sort" << std::endl;
    unsortedArray = new int[size];
    fillRandomIntList(unsortedArray, size);

    sortedArray = new int[size];
    copyArray(unsortedArray, sortedArray, size);
    printResult(unsortedArray, size, print, direction);

    std::cout << "Iterative sort: ";
    iterativeSort(sortedArray, size, direction);
    printResult(sortedArray, size, print, direction);

    std::cout << "Recursive sort: ";
    copyArray(unsortedArray, sortedArray, size);
    recursiveSort(sortedArray, size - 1, direction, false);
    printResult(sortedArray, size, print, direction);
}

void SelectionSort::runVectorSort(const int size, const SortDirection direction, const bool print)
{
    std::cout << std::endl << "Vector sort" << std::endl;
    unsortedVector = std::vector<int>(size);
    fillRandomIntList(unsortedVector, size);
    printResult(unsortedVector, size, print, direction);

    std::cout << "Iterative sort: ";
    sortedVector = std::vector<int>(unsortedVector);
    iterativeSort(sortedVector, direction);
    printResult(sortedVector, size, print, direction);

    std::cout << "Recursive sort: ";
    sortedVector.clear();
    recursiveSort(unsortedVector, sortedVector, size - 1, direction);
    printResult(sortedVector, size, print, direction);
}


template<class T>
void SelectionSort::fillRandomIntList(T &list, const int size)
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


//Determines whether to swap current ("outer" value currently in place) with the value its
//comparing to ("inner" unsorted value left in the list).
bool SelectionSort::shouldSwap(SortDirection direction, int current, int compareTo)
{
    return (((direction == ASCENDING)  && (compareTo > current))
         || ((direction == DESCENDING) && (compareTo < current)));
}


template<class T>
int SelectionSort::iterativeSwapIndex(T &data, int startIndex, SortDirection direction)
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

void SelectionSort::iterativeSort(std::vector<int> &data, const SortDirection direction)
{
    int swapIndex = 0;
    int swapValue = 0;

    for (int startIndex = static_cast<int>(data.size()) - 1; startIndex >= 0; startIndex--)
    {
        swapIndex = startIndex;

        for (int searchIndex = startIndex; searchIndex >= 0; searchIndex--)
        {
            if (data.at(searchIndex) > data.at(swapIndex))
            {
                swapIndex = searchIndex;
            }
        }

        swapValue = data.at(swapIndex);
        data.at(swapIndex) = data.at(startIndex);
        data.at(startIndex) = swapValue;
    }
}

void SelectionSort::recursiveSort(int data[], const int start, const SortDirection direction,
                                  int swapIndex, int swapValue)
{
    if (start <= 0)
    {
        return;
    }
    else
    {
        if (start <= MAX_RECURSIVE_SEARCH)
        {
            if (swapIndex == NULL_INDEX)
            {
                recursiveSort(data, start, direction, recursiveSwapIndex(data, start, direction));
            }
            else if (swapValue == NULL_SWAP_VALUE)
            {
                recursiveSort(data, start, direction, swapIndex, data[swapIndex]);
            }
            else
            {
                data[swapIndex] = data[start];
                data[start] = swapValue;
                recursiveSort(data, start - 1, direction, recursiveSwapIndex(data, start - 1, direction));
            }
        }
        else
        {
            swapIndex = iterativeSwapIndex(data, start, direction);
            swapValue = data[swapIndex];
            data[swapIndex] = data[start];
            data[start] = swapValue;
            recursiveSort(data, start - 1, direction);
        }
    }
}

void SelectionSort::recursiveSort(std::vector<int> &oldData, std::vector<int> &newData, const int start,
                                  const SortDirection direction, int swapIndex)
{
    if (start < 0)
    {
        return;
    }
    if (swapIndex == NULL_INDEX)
    {
        recursiveSort(oldData, newData, start, direction,
                      recursiveSwapIndex(oldData, start, direction));
    }
    else
    {
        newData.insert(newData.begin(), oldData.at(swapIndex));
        oldData.erase(oldData.begin() + swapIndex);
        recursiveSort(oldData, newData, start - 1, direction,
                        recursiveSwapIndex(oldData, start - 1, direction));
    }
}

template<class T>
int SelectionSort::recursiveSwapIndex(const T &data, const int start, const SortDirection direction,
                                      const int swapIndex)
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
void SelectionSort::printData(const T &data, const int size)
{
    for (int index = 0; index < size; index++)
    {
        std::cout << data[index] << " ";
    }

    std::cout << std::endl;
}

template<class T>
void SelectionSort::printSortTest(const T &data, const int size, const SortDirection direction)
{
    for (int index = size - 1; index > 0; index--)
    {
        if (shouldSwap(direction, data[index], data[index - 1]))
        {
            std::cout << "Incorrectly sorted. " << data[index] << " (index " << index
                      << ") is after " << data[index - 1] << std::endl;
            return;
        }
    }

    std::cout << "Correctly sorted." << std::endl;
}

template<class T>
void SelectionSort::printResult(const T &data, const int size, const bool print,
                                const SortDirection direction)
{
    if (print)
    {
        printData(data, size);
    }
    else
    {
        printSortTest(data, size, direction);
    }
}