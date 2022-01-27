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
 * 
 */
int findMissingNumber(const std::vector<int>& vec) {
  int sum = 0;
  for(int i=0; i<vec.size(); i++){
    sum += vec[i];
  }
  return (vec.size() * (vec.size()+1)) / 2 - sum;
}

/*
 * Add your key ideas to this comment.
 * How did you approach the problem?
 * Why does your code work?
 *
 */
int findMaxOfVector(const std::vector<int>& vec) {
  if(vec.size() == 0)
    throw std::invalid_argument("Vector size < 1.");
  int max = vec[0];
  for(int i=0; i<vec.size(); i++){ //must start at zero in case of vector size = 1, or must account for size 1, which would defeat the purpose of starting at 1
    if(vec[i] > max)
      max = vec[i];
  }
  return max;
}

/*
 * Add your key ideas to this comment.
 * How did you approach the problem?
 * Why does your code work?
 *
 */
std::pair<int, int> findTwoSumPair(const std::vector<int>& vec, int targetSum) {
  std::unordered_map<int,int> sums;
  
  for(int i=0; i<vec.size(); i++){
    if(sums.count(targetSum - vec[i])){
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

    if(l1 && l2){
      placeSum = l1->value + l2->value + carry;
      if(placeSum > 9){
        placeSum -= 10;
        carry = 1;
      }
      else{
        carry = 0;
      }
      tmp->value = placeSum;
      l1 = l1->next;
      l2 = l2->next;
    }
    else if(l1){
      placeSum = l1->value + carry;
      if(placeSum > 9){
        placeSum -= 10;
        carry = 1; 
      }
      else{
        carry = 0;
      }
      tmp->value = placeSum;
      l1 = l1->next;
    }
    else if(l2){
      placeSum = l2->value + carry;
      if(placeSum > 9){
        placeSum -= 10;
        carry = 1;
      }
      else{
        carry = 0;
      }
      tmp->value = placeSum;
      l2 = l2->next;
    }
    else{
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
