# Summer-of-Bitcoin-Task

### Data Input and Sorting

1. I first started wth taking input from CSV file. To maintain the transactions, I created a separate class fot them and added some basic functions to retrieve the values stored.

2. After much of thinking, I found that, arranging the transactions beforehand in a order such that parent transactions come before the child transactions will 
eventually be very helpful. I created a separate function for handling sorting.

### Solving the Problem

3. Now a naive appproach can be to check all the possible combinations of transactions, but that will give a exponential time-complexity (2<sup>n</sup> , where n are the 
given number of transactions), and is not at all practical.

This problem is similar to 0/1 knapsack problem (based on Dynamic Programming Paradigm), but the trick here is the decision to include the next transaction depends also on previously included transactions. A separate function to implement Knapsack was written, but the space and time complexity were very large.
(One idea was to divide the weight by minimum, this will also decrease the maximum limit, thus reducing space and time, but most of them had weights less than 1000, it would not have been fruitful.) 
Intuitively, I think because of parent-child relation between the transaction, we cannot use Knapsack Approach.

Then, I tried improvising the Naive Approach.
Many of us, when first look at Knapsack, do feel that, we first need to choose the object/transaction which have greater ratio (fees/weight) and repeat this
process. This approach do gives an optimum result in some cases, but not always. So, I started building my solution around this Approach.
So, using Naive approach, that is recursive calling and checking all the possibilities. Obviously can not check all the possibilities, so adding some constraints. To add further constraints and get more optimum answer, analysing the data.


Adding some observation, for my own use:
minimum weight : 440, and 10 ids, have this minimum weight.
Average fees/weight = 1.01107 

Next, I will be adding a mix of Greedy and Naive Approach. Following is the approach :
First inlcuded all the transactions, whose fees/weight ratio was greater than average, and then ran the naive algorithm to fill the remaining void. We can reach closer the optimum by making the threshold less than the average.
