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
    static const int LARGE_LIST_LENGTH = 5001;

    //The largest possible value in the array
    static const int MAX_VALUE = 100;

    //Output row length
    static const int ROW_LENGTH = 30;

    //Unassigned index with recursion
    static const int NULL_INDEX = -1;

    //Unset swap value
    static const int NULL_SWAP_VALUE = 0;

    //Maximum list size to do a recursive search
    static const int MAX_RECURSIVE_SEARCH = 1500;

    enum SortDirection
    {
        ASCENDING, DESCENDING
    };

    enum ListType
    {
        ARRAY, VECTOR
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
    template<class T> void fillRandomIntList(T &list, const int size);

    //Copies an array to a new one
    void copyArray(const int oldData[], int newData[], const int size);

    bool shouldSwap(const SortDirection direction, const int current, const int compareTo);

    template<class T> int iterativeSwapIndex(T &data, const int size, const SortDirection direction);

    void iterativeSort(int data[], const int size, const SortDirection direction);

    void iterativeSort(std::vector<int> &data, const SortDirection direction);

    void recursiveSort(int data[], int start, const SortDirection direction,
                       int swapIndex = NULL_INDEX, int swapValue = NULL_SWAP_VALUE);

    void recursiveSort(std::vector<int> &oldData, std::vector<int> &newData, const int start,
                       const SortDirection direction, const int swapIndex = NULL_INDEX);

    template<class T>int recursiveSwapIndex(const T &data, const int start, const SortDirection direction,
                                            int swapValue = NULL_SWAP_VALUE);

    void runArraySort(const int size, const SortDirection direction, const bool print);

    void runVectorSort(const int size, const SortDirection direction, const bool print);

    SortDirection promptSortDirection();


    template<class T> void printData(const T &data, const int size);

    //Tests the sorted arrays to make sure they're successfully sorted
    template<class T> void printSortTest(const T &data, const int size, SortDirection direction);

    template<class T> void printResult(const T &data, const int size, const bool printList,
                                       const SortDirection direction);

public:
    //Constructs a new selection sort object
    SelectionSort();

    //Creates an array and vector and sorts them recursively and iteratively.
    void go();
};

#endif
