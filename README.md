# Summer-of-Bitcoin-Task

### **Data Input and Sorting**

1. I first started wth taking input from CSV file. To maintain the transactions, I created a separate class fot them and added some basic functions to retrieve the values stored.

2. After much of thinking, I found that, arranging the transactions beforehand in a order such that parent transactions come before the child transactions will 
eventually be very helpful. I created a separate function for handling sorting.

### **Solving the Problem**

Now a naive appproach can be to check all the possible combinations of transactions, but that will give a exponential time-complexity (2<sup>n</sup> , where n are the 
given number of transactions), and is not at all practical.

This problem is similar to 0/1 knapsack problem (based on Dynamic Programming Paradigm), but the trick here is the decision to include the next transaction depends also on previously included transactions. 

3. A separate function to implement Knapsack was written, but the space and time complexity were very large.

One of the idea was to divide the weight by minimum, this will also decrease the maximum limit of weight, thus reducing space and time, but most of them had weights less than 1000, so it would not have been fruitful.

*Intuitively, I think because of parent-child relation between the transaction, we cannot use Knapsack Approach.*

---

Using Naive approach, that is recursive calling and checking all the possibilities, we can never check all the possibilities, but we can add some constraints, to reduce the size of recursion tree.

4. Then, I started improvising the Naive Approach. First added that if difference between Maximum allowed weight and current total weight of block is less than minimum weight of transaction, then return the function. 
Added an upper bound to the number of iterations of the recursion tree.

Many of us, when look at Knapsack for the first time, do feel that we first need to choose the objects/transactions which have greater ratio (fees/weight) and keep repeat this process. 
This approach do gives an optimum result in some cases, but not always. So, I started building my solution around this Approach.

If we directly choose the transactions, with the highet ratio, we are not guaranteed that it's parent is also included, and we might end up skipping this transaction. This will make this method very messy.

But if we have some threshold (Inspiration from the Photoelectric Effect) and iterate in our sorted transaction vector, choosing the ones crossing this threshold ratio, we are also ensuring that if the transaction has a parent which also crosses this threshold then it is also included.

5. I chose average ratio as our threshold, and results were much better than direct Naive Approach. After I have included the tranactions crossing the threshold, I still had a lot of remaining weight. On this remaining weights, I used Naive Approach with the rest of the transaction. 

If we think over this problem, we can see one problem with the Threshold Method. What if the parent does not cross the threshold and child has a very large ratio (fees/weight) crossing the threshold, then this won't be included in our block. Worst will be when even Naive Method will not inlcude this transaction (Because of the upper limit).

A solution to above problem is to reduce the threshold, and keep doing so that it reaches an optimum value.

Why optimum ? cause below this optimum value, we will be including most of the transactions, which have a low ratio, and we might reach our given upper limit of Weight, and miss out on the remaining transactions, which might have a good ratio.

6. Iteratively checked for the optimum value of threshold, by comparing the total fees of the block. This manual method can also be  programmed (almost similar to Gradient Descent method).


Some observation:
minimum weight : 440, and 10 ids, have this minimum weight.
Average fees/weight = 1.03046
Final maximum Fees : 5701763
Final maximum Weight : 3999968