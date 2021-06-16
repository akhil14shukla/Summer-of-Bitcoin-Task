# Summer-of-Bitcoin-Task

Very rough overview of the process

Took input from CSV file.

Then arranged the transaction such that if a transaction has some parent transactions then they occur before the child transaction.

Now a naive appproach can be to check all the possible combinations of transactions, but that will give a exponential time-complexity (2^{n} , where n are the given number of transactions)

This problem is similar to 0/1 knapsack problem (based on Dynamic Programming Paradigm), but the trick here is the decision to include the next transaction depends also on previously included transactions.
(One idea was to divide the weight by minimum, this will also decrease the maximum limit, thus reducing space and time, but most of them had weights less than 1000, it would not have been fruitful.)

Direct Knapsack can't be used, too much space and Time. 
So, using Naive approach, that is recursive calling and checking all the possibilities. Obviously can not check all the possibilities, so adding some constraints. To add further constraints and get more optimum answer, analysing the data.


Adding some observation, for my own use:
minimum weight : 440, and 10 ids, have this minimum weight.
Average fees/weight = 1.01107 

Next, I will be adding a mix of Greedy and Naive Approach. Following is the approach :
First inlcuded all the transactions, whose fees/weight ratio was greater than average, and then ran the naive algorithm to fill the remaining void. We can reach closer the optimum by making the threshold less than the average.
