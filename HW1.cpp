#include <iostream>   // std::cout, std::cin
#include <stdexcept>  // std::invalid_argument
#include <vector>     // std::vector
#include <unordered_map>

#include "Node.h"  // Node
#include "util.h"  // containerToString, listToString, makeList, freeList
// Note: the include comments are just for your educational purposes.
// Normally, one does not include those comments. Include additional
// headers as needed.

/*
 * Add your key ideas to this comment.
 * How did you approach the problem?
 * Why does your code work?
 * At first, I was a little confused at the instructions given, because I didn't understand how that return formula had anything to do with the missing number, but when I worked out a few exampled by hand I was actually shocked to see that it was a true formula for this instance. Once I put that together, I didn't have any trouble putting the pseudocode to practice. 

 I can only presume my code works becuase I was given a great algorithm, but aside from the 'magic' formula, I interpret the input correctly, and supply the output as instructed. In the loops, there are no cases where they may run unterminated.
 */
int findMissingNumber(const std::vector<int>& vec) {
  int sum = 0;
  for (int i=0; i<vec.size(); i++) {
    sum += vec[i];
  }
  return (vec.size() * (vec.size()+1)) / 2 - sum;
}

/*
 * Add your key ideas to this comment.
 * How did you approach the problem?
 * Why does your code work?
 *
 I interpreted the input as a vector of integers, and the output to be a single integer that is the maximum value in the given array.

Noted that in a vector of size zero, the instructions state to return an exception. My input takes negative and nonnegative numbers.

 */
int findMaxOfVector(const std::vector<int>& vec) {
  if (vec.size() == 0)
    throw std::invalid_argument("Vector size < 1.");
  int max = vec[0];
  for (int i=0; i<vec.size(); i++) { 
    if (vec[i] > max)
      max = vec[i];
  }
  return max;
}

/*
 * Add your key ideas to this comment.
 * How did you approach the problem?
 * Why does your code work?
 *
 I admittedly have seen a variation of this problem before, and previously have solved it by taking a for loop and looping through at changing points to record a value and its index, but have since grown more familiar with hash maps. 

 For any given iteration, if the value needed (target - vec[i]) was in the hash map, then we can take those two numbers and return them. If not, then we would add that number and its index to the map. This can be done in O(N), with the best case being two sum pair are in spots 0 and 1, and the worst case being one of the pairs is the last element, or not found.
 */
std::pair<int, int> findTwoSumPair(const std::vector<int>& vec, int targetSum) {
  std::unordered_map<int,int> sums;
  
  for(int i=0; i<vec.size(); i++){
    if (sums.count(targetSum - vec[i])) {
      return std::make_pair(sums[targetSum - vec[i]],i);
    }
    sums[vec[i]] = i;
  }
  return std::make_pair(-1,-1);
}

/*
 * Add your key ideas to this comment.
 * How did you approach the problem?
 * Why does your code work?
 *
  This question did throw me for a loop a little bit, but most likely because I had to read through the provided code and sort out where to pick up from there. My original solution would have been different, as I would have kept l1 and changed the values of that rather than making a new node every time, and I had to reorganize my solution a little bit.

  Since I know that there are four basic list succession scenarios (branching into with a carry and without a carry), I was able to sort out that a new node would need to be created in all of those scenarios that exist while the loop is running, so no condition needed there, and I could make it first thing in the loop so as not to get lost in the conditions.

  Next, I had to be sure to reset the carry at the end of every addition set, either to have it maintain the 1, or contain a 0. I did forget this step in one secenario, when the two lists have ended but still need to finish the carry operation, but was able to use breakpoints in replit's debugger to quickly sort out the issue.

  There are other things I could explain, but those were the main points that I had to emphasize to get the correct answer as I was solving the question.
 */
Node<int>* add(Node<int>* l1, Node<int>* l2) {
  Node<int>* head = nullptr;
  Node<int>* tail = nullptr;
  int carry = 0;
  while (l1 != nullptr || l2 != nullptr || carry > 0) {
    int placeSum = 0;
    // TODO your code here (remove logic_error)
    
    // construct the new node
    Node<int>* tmp = new Node<int>();
    tmp->value = placeSum;
    tmp->next = nullptr;
    if (head == nullptr) {
      head = tmp;
      tail = tmp;
    } else {
      tail->next = tmp;
      tail = tail->next;
    }

    if(l1 && l2) {
      placeSum = l1->value + l2->value + carry;
      if(placeSum > 9){
        placeSum -= 10;
        carry = 1;
      }
      else {
        carry = 0;
      }
      tmp->value = placeSum;
      l1 = l1->next;
      l2 = l2->next;
    }
    else if (l1) {
      placeSum = l1->value + carry;
      if(placeSum > 9){
        placeSum -= 10;
        carry = 1; 
      }
      else {
        carry = 0;
      }
      tmp->value = placeSum;
      l1 = l1->next;
    }
    else if (l2) {
      placeSum = l2->value + carry;
      if(placeSum > 9){
        placeSum -= 10;
        carry = 1;
      }
      else {
        carry = 0;
      }
      tmp->value = placeSum;
      l2 = l2->next;
    }
    else {
      tmp->value = 1;
      carry = 0; //almost forgot this!
    }
  }
  return head;
}

    
    // 7 4 3 6
    // 1 7 5 5 5

    // 8
    // 8 1, carry 1
    // 8 1 3+5+1
    // 8 1 9 
    // 8 1 9 1, carry 1
    // 8 1 9 1 5+1
    // 8 1 9 1 6
