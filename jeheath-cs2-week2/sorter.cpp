/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The bubble sort, quick sort, merge sort, and in-place quicksort
 * algorithms (implementation).
 *
 */
#include "sorter.hpp"

int main(int argc, char* argv[])
{
    // Set up buffers and data input
    std::vector<int> nums;
    std::string line;
    char *filename;
    int sort_type;

    // Ensure that at most one type of sort and at least a filename are specified.
    if (argc > 3 || argc < 2)
    {
        usage();
    }

    // default sort is bubble sort
    sort_type = BUBBLE_SORT;

    // Figure out which sort to use
    for (int i = 1; i < argc; ++i)
    {
        char *arg = argv[i];
        if (strcmp(arg, "-b") == 0) { sort_type = BUBBLE_SORT; }
        else if (strcmp(arg, "-q") == 0) { sort_type = QUICK_SORT; }
        else if (strcmp(arg, "-m") == 0) { sort_type = MERGE_SORT; }
        else if (strcmp(arg, "-qi") == 0) { sort_type = QUICK_SORT_INPLACE; }
        else { filename = argv[i]; }
    }

    // Read the file and fill our vector of integers
    // THIS FUNCTION IS STUDENT IMPLEMENTED
    readFile(filename, nums);

    switch (sort_type)
    {
        case BUBBLE_SORT:
        print_vector(bubbleSort(nums));
        break;

        case QUICK_SORT:
        print_vector(quickSort(nums));
        break;

        case MERGE_SORT:
        print_vector(mergeSort(nums));
        break;

        case QUICK_SORT_INPLACE:
        quicksort_inplace(nums, 0, nums.size() - 1);
        print_vector(nums);
        break;

        default:
        usage();
        break;
    }
    return 0;
}

/**
 * Usage    Prints out a usage statement and exits.
 */
void usage()
{
    std::cerr << usage_string << std::endl;
    exit(1);
}

/**
 * swap_element     Swaps two elements of a vector in place
 * @param i index to be swapped
 * @param j index to be swapped
 * @param v Vector within which swapping occurs
 * @returns nothing.
 */
void swap_element(int i, int j, std::vector<int> &v)
{
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/**
 * This function is an implementation of the bubblesort algorithm. It 
 * will sort its vector<int> argument from smallest to largest with a 
 * time complexity of O(n^2).
 * @return vector<int> The final sorted vector.
 * @param vector<int> The vector to be sorted.
 *  
 * Outline:
 * 
 * FOR num_elements:
 *      FOR num_elements - 1 - iterations:
 *          if list[i] > list[i + 1]:
 *              swap
 *      iterations++
 */
std::vector<int> bubbleSort(std::vector<int> &list)
{
    for (unsigned int i = 0; i < list.size(); i++)
    {
        for (unsigned int j = 0; j < list.size() - i - 1; j++)
        {
            if (list[j] > list[j+1])
            {
                swap_element(j, j + 1, list);
            }
        }
    }
    return list;
}

/**
 * This function will be an implementation of the quicksort algorithm. 
 * 
 * Outline:
 * 
 * if list.size = 1:
 *      return list
 * else:
 *      choose pivot to be leftmost element
 *      make two lists, big/small
 *      add elements < pivot to small
 *      add elements > pivot to big
 *      quicksort(big)
 *      quicksort(small) --These are reursive calls to this function
 *      reset list to be in the order: small -> pivot -> big
 *      return list
 * 
 * @param list The vector to be sorted
 * @returns The sorted vector
 * 
 * Note: The function will return the sorted list, but since it is pass
 * by reference, it will also simply sort the list that you pass it. 
 * The return value doesn't need to be stored. 
 */
std::vector<int> quickSort(std::vector<int> &list)
{
    if (list.size() <= 1)
    {
       return list;
    }
    else
    {
        int pivot = list[0];
        std::vector<int> list_big;
        std::vector<int> list_small;
        for (unsigned int i = 1; i < list.size(); i++)
        if (list[i] <= pivot)
        {
            list_small.push_back(list[i]);
        }
        else
        {
            list_big.push_back(list[i]);
        }
        
        quickSort(list_small);
        quickSort(list_big);
        unsigned int j = 0;
        while (j < list_small.size())
        {
            list[j] = list_small[j];
            j++;
        }
        list[j] = pivot;
        j++;
        unsigned int k = 0;
        while (k < list_big.size())
        {
            list[j] = list_big[k];
            j++;
            k++;
        }
        return list;
    }
}

/**
 * This is the implementation of the merge sort algorithm!
 * @param list The list to be sorted
 * @returns The final sorted list
 * 
 * Outline:
 * 
 * for num_elements:
 *      vector v;
 *      v.push_back(element);
 *      vector<vector> super_v; // This will be a vector of vectors
 *      super_v.push_back(v); // All elements are turned into vectors
 *                            // and added to the super list of vectors
 * int index = 0;
 * while (super_v.size() >= index + 2)
 *      vector r = super_v[index];
 *      index++;
 *      vector l = super_v[index];
 *      index++;
 *      vector n = merge(r, l);
 *      super_v.push_back(n); // This will make super_v nlog(n) in size,
 *                            // but it will be very time efficient!
 * list = super_v[index];
 * return super_v[index];
 */
std::vector<int> mergeSort(std::vector<int> &list)
{
    std::vector<std::vector<int>> super_v; 
    for (unsigned int i = 0; i < list.size(); i++)
    {
        std::vector<int> v;
        v.push_back(list[i]);
        super_v.push_back(v); 
    }
    unsigned int index = 0;
    unsigned int s = super_v.size();
    while (index + 1 < s)
    {
        std::vector<int> n = merge(super_v[index], super_v[index + 1]);
        index += 2;
        super_v.push_back(n); 
        s += 1;
    }
    list = super_v[index];
    return list;
}

/**
 * This is a helper function for mergeSort. It takes two ordered lists, 
 * and sorts them each into a third new ordered list. 
 * @param left A sorted vector to be merged
 * @param right A sorted vector to be merged
 * @returns The merged, sorted list
 */
std::vector<int> merge(std::vector<int> left, std::vector<int> right)
{
    std::vector<int> list; // Creates a new empty list
    
    // This will loop until both indicies are out of the range of their 
    // respective list.
    unsigned int i = 0, j = 0;
    while ((i < left.size()) || (j < right.size()))
    {
        if ((i >= left.size()))
        {
            list.push_back(right[j]);
            j++;
        }
        else if (j >= right.size())
        {
            list.push_back(left[i]);
            i++;
        }
        else if (left[i] > right[j])
        {
            list.push_back(right[j]);
            j++;
        }
        else
        {
            list.push_back(left[i]);
            i++;
        }
    }
    return list;
}

/*
 * quicksort_inplace:  In-place version of the quicksort algorithm. Requires
 *              O(1) instead of O(N) space, same time complexity. Each call of
 *              the method partitions the list around the pivot (an item taken
 *              from the middle of the array) with items left of the pivot
 *              smaller than it and items to its right larger than it. Then the
 *              method recursively sorts the left and right portions of the list
 *              until it reaches its base case: a list of length 1 is already
 *              sorted.
 *
 * @param list: pointer to integer array to be sorted
 * @returns:    Nothing, the array is sorted IN-PLACE.
 * 
 * Outline:
 * 
 * if (right == left)
 *      return;
 * else:
 *      // choose pivot to be left element
 *      int pivot = left;
 *      for (int i = left + 1; i <= right; i++)
 *      if a number is less than the pivot:
 *          swap the pivot with the element in front of it
 *          pivot++;
 *          swap the element now behind the pivot with the element less
 *          than the pivot, assuming that the element hasn't been moved
 *          already. 
 *      quicksort_inplace(left, pivot - 1);
 *      quicksort_inplace(pivot + 1, right);
 */
void quicksort_inplace(std::vector<int> &list, int left, int right)
{
    if (right <= left)
    {
        return;
    }
    else
    {
        // choose pivot to be left element
        int pivot = left;
        for (int i = left + 1; i <= right; i++)
        {
            if ((list[i]) < (list[pivot]))
            {
                swap_element(pivot, pivot + 1, list);
                pivot++;
                if (pivot != i)
                {
                    swap_element(pivot - 1, i, list);
                }
            }
        }
        quicksort_inplace(list, left, pivot - 1);  // Recursively sort 
        quicksort_inplace(list, pivot + 1, right); // about the pivot.
    }
}

