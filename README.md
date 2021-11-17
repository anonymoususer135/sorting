# sorting

## Sorting Revisited

-Sorting is a very common and useful operation

-Efficient sorting algorithms can have large saving for many apps

-Algorithms are evaluated on:

  -Number of comparisons
  
  -Times data is moved
  
  -Amount of additional memory used
  
 ## Sorting Efficiency
 
 -**Worst case**: The data is in reverse order
 
 -***Average Case**: Random data, may be somewhat sorted already
 
 -Best case: Array already sorted
 
 -Average and worst case performance are similar, if not identical
 
 -For many algorithms, best case is also case for other cases
 
 ## Straight Selection Sort
 
 1. Set "current" to the first index of the array
 2. Find the smallest value in the array
 3. Swap the smallest value with current one
 4. Increment current and repeat 2-4 until end of array

Example:
1. 126, 43, 26, 1, 113
2. **1**, 43, 26, 126, 113
3. 1, **26*, 43, 126, 113
4. 1, 26, **43**, 126, 113
5. 1, 26, 43, 113, 126

Context: In 5, the 113 and 126 are swapped and the array is finally sorted.

## Analyzing Selection Sort
-A simple and easy to understand algorithm

-N iteration performed

-Iteration I checs N-I items to find the next smallest value

-There are N*(N-1)/2 comparison total

-Selection sort is O(N^2)

-Even in best case, it's still O(N^2)

## Bubble Sort

1. Set current to the first index of the array
2. For every index from the end of the list to 1, swap adjacent pair of element out of order
3. Increment current and repeat 2-3
4. Stop when current is at end of array

The name comes from smaller elements bubbling up

It takes N-1 iterations, since last one puts 2 value in order

Each iteration I perform N-I comparison

Bubblesort is therefore O(N^2)

It performs several swap per iteration

Is best case better? Already sorted array only needs 1 iteration

## Insertion Sort

-Acts like inserting element in sorted array, like moving elements down if necessary

-Use swapping

O(N^2) like previous sorts

Best case: O(N), since only 1 comparison is needed and no data is moved

O(N^2) not good enough when sorting large set of data

## O(N log2 N) sort

-Sorting whole array is O(N^2) with these sorts

-Splitting array in halt, sorting it, then merging the two array is (N/2)^2 + (N/2)^2

-This divide and conquer approach can then be applied to each half, giving O(N log2 N) sort

## Merge Sort

1. Split the array in half
2. Recursively Mergesort two halves
3. Merge two halves
4. Base Case: Array of <2 element already sorted

log2(16)= 4 level of merging, if N=16 in MergeSort function

## Quick Sort

-Choose value from array

-If arrays are evenly spilit, log2N split is used and algorithm is O(N log2 N)
-If not split evently, then algorithm approach O(N^2)
-QS inefficient if data is already mostly sorted

## Heap Sort

-Turn Array into heap, then place root at last unsorted slot of array untl heap is depleted

-Use Heap operation(ReheapDown) to find next largest element in heap

-Overhead for building heap is significant, O(N) and thus heap sort should be avoided for small array

-ReheapDown is O(log2N) and is called N times

-overall performance is O(N log2 N)

-Initial order of element doesn't matter

-No additional space needed

## Other consideration

-Efficiency is not only thing to consisder when choosing which sorting algorithm to use

-Big O ignores constants and other factor

## When N is small

-O(N^2) sorts often have low overhead and few action besides comparison

-O(N log2N) sort usually have more overhead and more action, like merging

-When N is small enough, O(N^2) sort might be faster than O(N log2N) sort

## Eliminating call to function

-Every function call add more overhead

-But replacing each function call with the body of the function makes ocde less clear

-The inline keyword sugest to compiler to replace function call with function body, giving best of both worlds

-This is useful for function like swap which are short and used often

## Programmer time

-Someone has to tae time to design, implement, ansd terst sorting algorithms 

-More complex algorithm are more likely to have error

-Fortunately, user rely onstandard library and package with highly optimized and well debugged implementation

## Space Consideration

-MergeSort require additional N memory

-Depending on implementation and data. QuickSort uses O(N) memory

-HeapSort is more algorithmically complex, but no additional memory

-Consider memory constraint of system and size of input when choosing

## Keys And Stability

-A record may contain multiple key, lie name, id numver, and major

-Some of the key may not be unique

-What if we want list sorted  by major, but have alphabetical order of name within each major?

-Sort twice, first by name and then major

-This only works if sort is stable

## Stabling Algorithms

-Stable Sort is sorting algorithm that preserve order of duplicate 

-Heap sort is only algorithm so far which is unstable

## Sorting with pointer

-Moving around large object is inefficient

-Instead, we have array of pointer to those large aobjects, and have the sort move the pointer

-Object don't move but can be accessed in sorted order

## Caching

-Not all computer memory is equal, even though user pretend it is

-It take as much time to access memory cell as for computer to execute 100 instruction

-Processor uses cache, small store of very fast memory, to access small amt of memory quickly

-Cache can store very limited amout of data and code

## Sorting Algorithms and Caching

-Bubble Sort has predictable memory access pattern, and only compare adjacent element, which complement cache behavior

-Selection sort much search whole list for next smallest element, not work well with cache

-Array of pointer to object scatter throughout memory defeats cache, since, there no way to predict next access

## Radix sort

-Radix sort is not comparison sort, it doesn't sort by comparing item against each other

-Sort considers each position in key and groups keys by radix

## Radix Sort Algorithm

-Consider sorting three digit posituve integer

-We have 10 queue, one or every digit, (0-9)

## Parallel Merge Sort

-Somtimes O(Nlog2N) isn't enough

-Parallel process perform multiple operation simutaneously, unlike serial processing

-Merge sort divides work into indeoendent part making it ideal candidate for splitting among several threads

