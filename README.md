# Summer-of-Bitcoin-Task

### **Data Input and Sorting**

1. I first started with taking input from the CSV file. I created a separate class for them and added some essential functions to retrieve the values stored to maintain the transactions.

2. After much thinking, I found that arranging the transactions beforehand, so that parent transactions come before the child transactions will eventually be very helpful. I created a separate function for handling sorting.

---

### **Solving the Problem**

Now a naive approach can be to check all the possible combinations of transactions, but that will give an exponential time-complexity (2<sup>n</sup>, where n is the 
given the number of transactions), and is not at all practical.

This problem is similar to the 0/1 knapsack problem (based on Dynamic Programming Paradigm), but the trick here is the decision to include the next transaction also depends on previously included transactions. 

3. A separate function to implement Knapsack was written, but space and time complexity were very large.

One idea was to divide the weight by minimum; this will also decrease the maximum weight limit, thus reducing space and time, but most of them had weights less than 1000, so it would not have been fruitful.

*Intuitively, I think because of parent-child relation between the transaction, we cannot use Knapsack Approach.*

---

Using the Naive approach, which is recursive calling and checking all the possibilities, we can never check all the possibilities. Still, we can add some constraints to reduce the size of the recursion tree.

4. Then, I started improvising the Naive Approach. First added that if the difference between the maximum allowed weight and the current total weight of the block is less than the minimum weight of the transaction, return the function. 
Added an upper bound to the number of iterations of the recursion tree.

When looking at Knapsack for the first time, many of us feel that we first need to choose the objects/transactions with a greater ratio (fees/weight) and keep repeating this process. 
This approach does give an optimum result in some cases, but not always. So, I started building my solution around this Approach.

Suppose we directly choose the transactions with the highest ratio. In that case, we are not guaranteed that it's the parent is also included, and we might end up skipping this transaction. This will make this method very messy.

But if we have some threshold (Inspiration from the Photoelectric Effect) and iterate in our sorted transaction vector, choosing the ones crossing this threshold ratio, we are also ensuring that if the transaction has a parent which also crosses this threshold, then it is also included.

5. I chose the average ratio as our threshold, and the results were much better than the direct Naive Approach. After I have included the transactions crossing the threshold, I still had a lot of remaining weight. On these remaining weights, I used the Naive Approach with the rest of the transaction. 

If we think over this problem, we can see one problem with the Threshold Method. What if the parent does not cross the threshold and the child has a very large ratio (fees/weight) crossing the threshold? Then this won't be included in our block. The worst will be when even the Naive Method does not include this transaction (Because of the upper limit).<br/>
A solution to the above problem is to reduce the threshold and keep doing so that it reaches an optimum value.

Why optimum? Cause below this optimum value, we will be including most of the transactions, which have a low ratio, and we might reach our given upper limit of Weight and miss out on the remaining transactions, which might have a good ratio.

6. Iteratively checked for the optimum value of the threshold, by comparing the total fees of the block. This manual method can also be programmed (almost similar to the Gradient Descent method).


Some observation:<br/>
minimum weight : 440, and 10 ids, have this minimum weight.<br/>
Average fees/weight = 1.03046<br/>
Final maximum Fees : 5701763<br/>
Final maximum Weight : 3999968<br/>