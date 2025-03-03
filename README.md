## Introduction
Implements and benchmarks sequential and concurrent heap-sort algorithms (in C++). The algorithm uses multi-threading to divide and run the sorting task, this aims to optimize performance on multi-core processors. The benchmarks track the sorting times across different input sizes and thread counts, this highlights the trade-offs from concurrency.
## Implementations
### Sequential and Concurrent Sorting
- Sequential Sort: Uses a basic heap sort algorithm that processes the entire input vector in a single thread.
- Concurrent Sort: Uses multiple threads to divide the input vector into subvectors, sorts them concurrently, and then merges the results.

## Tuning the Concurrent Algorithm

The number of threads used by the concurrent algorithm is an important parameter as that can determine how fast the sorting algorithm can finish with a large vector. In this implementation:

- Hardware Threads: The maximum threads available on the system were determined using std::thread::hardware_concurrency(). This is displayed in the output file as "Hardware Threads:"
- Max Threads: For testing, two configurations were evaluated: using 4 threads (max hardware concurrency) and 2 threads (limited concurrency). (limited testing due to the limited amount of cores my computer has)

## Changing Parameters in the Software
- If you desire to change the maximum number of threads used go to line 65 of chbench.cpp and change the value of *max_threads* to the desired number of threads used. (*NOTE: Amount of hardware threads available will be outputed as "Hardware Threads: " that is the max your device is able to use)
-  The benchmark output file is named *chbench_output.txt* if you desire to change it go to line 71 of chbench.cpp and change the name to *____.txt*.

## Results

### Max Threads: 4

     Hardware Threads: 4
     Max Threads: 4
     List Size   Sequential Sort Time (s)   Concurrent Sort Time (s)
                min       max      average      min     max    average
      ------  -----      -----    -------     -----     -----    -------
          1   0.00000   0.00000   0.00000    0.00000   0.00000   0.00000
         10   0.00000   0.00000   0.00000    0.00012   0.00142   0.00029
        100   0.00003   0.00004   0.00003    0.00012   0.00036   0.00016
       1000   0.00043   0.00050   0.00044    0.00023   0.00046   0.00032
      10000   0.00600   0.00641   0.00611    0.00156   0.00288   0.00214
     100000   0.07878   0.10425   0.08695    0.02006   0.05216   0.02674
    1000000   1.02224   1.18077   1.05616    0.26361   0.80309   0.40082

### Max Threads: 2
     Hardware Threads: 4
     Max Threads: 2
     List Size   Sequential Sort Time (s)   Concurrent Sort Time (s)
                min       max      average      min     max    average
      ------  -----      -----    -------     -----     -----    -------
          1   0.00000   0.00000   0.00000    0.00000   0.00000   0.00000
         10   0.00000   0.00000   0.00000    0.00005   0.00056   0.00013
        100   0.00003   0.00009   0.00004    0.00008   0.00124   0.00027
       1000   0.00044   0.00066   0.00048    0.00027   0.00135   0.00053
      10000   0.00623   0.01030   0.00715    0.00299   0.00323   0.00310
     100000   0.07829   0.09678   0.08099    0.03820   0.04494   0.04006
    1000000   1.03288   1.86230   1.24966    0.49066   0.74579   0.61487

## Observations

- Small List Sizes (list size 1 - 100):  The concurrent sorting version showed slightly lower performance than the sequential version due to the overhead of managing threads.
- Medium and Large List Sizes (list size 1,000 - 1,000,000): As input size increased the concurrent sort outperformed the sequential sort. This is attributed to efficient load distribution across threads.
- With 4 threads (the number of hardware threads my computer has reported bystd::thread::hardware_concurrency), the concurrent sort achieved a speedup of around 4.25x on average compared to sequential sort (specifically for list size 1,000,000).
- When the thread count was capped at 2, the concurrent algorithm still provided significant speedups with larger list sizes, but less pronounced than the 4-thread configuration. For list size 1,000,000 2 threads had a 2.11× compared to the sequential average time. 
- For small workloads, fewer threads can outperform more threads due to reduced overhead. This is seen in the list size of 1,000, the 4-thread configuration achieved a speedup of 1.25×, while the 2-thread configuration achieved a higher speedup of 1.90×.
- Sequential was the fastest for list sizes 1 - 100, concurrent with two threads was the fastest at list size 1,000, and concurrent with four threads was the fastest for all the sizes after.
- With this benchmark, I can assume that the larger the list size, the more efficient concurrent sorting becomes, especially when utilizing all available hardware threads.
##  Conclusion
The performance of the concurrent algorithm increased two times with double the number of threads, especially for larger inputs, but the overhead made it less effective for smaller inputs. On a 4-core machine, utilizing all available cores generally provided the best performance for large lists but lacked performance for smaller lists because of the overhead. Limiting concurrency to 2 threads reduced overhead making the algorithm performance efficient for the smaller lists but it remained slower than the sequential sort until list size 1,000 but after list size 1,000 the more threads were faster than both the sequential and concurrent with 2 threads. 

