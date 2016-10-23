#pragma once
#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

//////////////////////////////////////////////////////////////////////////
// FileName:    SelectionSort.h
// Description: Declares all the member functions and attributes of the SelectionSort class
// Author:      Terry Weiss 466751950
// Project:     Selection Sort (Homework 4 Assignment)
//////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>


class SelectionSort
{
private:
    //The default length of the small tester array/vector
    static const int TEST_LIST_LENGTH = 20;

    //The default length of the large array/vector
    static const int LARGE_LIST_LENGTH = 10000;

    //The largest possible value in the array
    static const int MAX_VALUE = 100;

    //Output row length
    static const int ROW_LENGTH = 30;

    //Unassigned index with recursion
    static const int NULL_INDEX = -1;

    //Unset swap value
    static const int NULL_SWAP_VALUE = 0;

    enum SortDirection
    {
        ASCENDING, DESCENDING
    };

    //Unsorted array
    int *unsortedArray = NULL;

    //Sorted array
    int *sortedArray = NULL;

    //Unsorted vector
    std::vector<int> unsortedVector;

    //Sorted vector
    std::vector<int> sortedVector;


    //Generates a random list of integers between 1 and MAX_VALUE
    template<class T> void fillRandomIntList(T list, const int size);

    //Copies an array to a new one
    void copyArray(const int oldData[], int newData[], const int size);

    //Tests the sorted arrays to make sure they're successfully sorted
    void printSortTest(const int data[], const int size, SortDirection direction);

    bool shouldSwap(SortDirection direction, int current, int compareTo);

    int iterativeSwapIndex(int data[], const int size, SortDirection direction);

    void iterativeSort(int data[], const int size, SortDirection direction);

    void iterativeSort(std::vector<int> *data, SortDirection direction);

    void recursiveSort(int data[], int start, SortDirection direction, bool recursiveSearch,
                       const int swapIndex = NULL_INDEX, int swapValue=NULL_SWAP_VALUE);

    void recursiveSort(const std::vector<int> *oldData, std::vector<int> *newData, int start,
                       SortDirection direction, bool recursiveSearch);

    int recursiveSwapIndex(const int data[], int start, SortDirection direction,
                           int swapValue=NULL_SWAP_VALUE);

    int recursiveNextElement(const std::vector<int> *data, int start, SortDirection direction);


    SortDirection promptSortDirection();


    template<class T> void printData(const T data, const int size);

public:
    //Constructs a new selection sort object
    SelectionSort();

    //Creates an array and vector and sorts them recursively and iteratively.
    void go();
};

#endif
