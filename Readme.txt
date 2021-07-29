


Name:
Majd Barakat
-----------------------------------------------

Please confirm that you compiled your solution with test cases exercising ALL functions using g++ -std=c++11.  Confirm this statement by typing YES below.
(If you did not do this, compilation errors may result in an overall grade of zero!)

YES





Describe what augmentations to the bst data structures you made to complete the project -- i.e., what types / data members did you change and why?

I added int size_left and int size_right to the bst_node which tracks of the number of nodes on the left subtree and the number of nodes on the right subtree


-----------------------------------------------
Which functions did you need to modify as a result of the augmentations from the previous question?  

bool remove(T & x)
bool insert(T & x)
static bst * from_sorted_vec(const std::vector<T> &a, int n)



-----------------------------------------------
For each function from the previous question, how did you ensure that the (asymptotic) runtime remained the same?

The only modification to these function is to add/substract 1 from/to size_left and size_right so that so that the number of nodes in the left and right subtrees is updated.
This modification takes constant time O(1), therefore it will not affect the runtime of these functions.


-----------------------------------------------
For each of the assigned functions, tell us how far you got using the choices 0-5 and
answer the given questions.  


0:  didn't get started
1:  started, but far from working
2:  have implementation but only works for simple cases
3:  finished and I think it works most of the time but not sure the runtime req is met. 
4:  finished and I think it works most of the time and I'm sure my design leads to 
       the correct runtime (even if I still have a few bugs).
5:  finished and confident on correctness and runtime requirements


to_vector level of completion:  _____5______  


-----------------------------------------------
get_ith level of completion:  ____5_______  

    How did you ensure O(h) runtime?

    ANSWER: instead of treversing the entire tree to find the ith element, size_left and size_right were used to guid us toward the ith elemen resulting in an O(h) runtime. for example, if i < size_left, then there is no need to traverse the right subtree which lowers the overall runtime.

-----------------------------------------------
position_of level of completion:  ____5_______  

    How did you ensure O(h) runtime?

    ANSWER: instead of treversing the entire tree to find the position of x, size_left and size_right are used to calculate the position of element x. Thus the run time depends on the height of the tree O(h).

-----------------------------------------------
num_geq level of completion:  _____5______  

    How did you ensure O(h) runtime?

    ANSWER: size_right is used to avoid traversing the entire tree. The function tries to find the boundary node that is equal or greater than x and then size_right is used to find the number of element that are greater than x immediately. Thus resulting in O(h) overall runtime.

-----------------------------------------------
num_leq level of completion:  _____5_______

    How did you ensure O(h) runtime?

    ANSWER: size_left is used to avoid traversing the entire tree. The function tries to find the boundary node that is equal or less than x and then size_left is used to find the number of element that are less than x immediately. Thus resulting in O(h) overall runtime.

-----------------------------------------------
num_range level of completion:  _____5_______

    How did you ensure O(h) runtime?

    ANSWER: a helper function _num_lessThan is constructed to find the number of nodes less than x, which uses O(h).
    Then, the number of elements within a certain range can be found using: num_leq(max) - _num_lessThan(min). 
    Since both, num_leq and _num_lessThan use O(h) then the overall runtime is O(h).

-----------------------------------------------
extract_range level of completion:  _____5_______

    How did you ensure O(h+k) runtime?

    ANSWER: If an element is not inside the given range, a recursive call is made in order to traverse in the direction closer to the range (either left or right). Therefore, the entire tree is not traveresd unnecessarily in order to reach the specified range.
    The runtime so far is O(h). Once the elements is withen the range are reached, they are added into an array in an ascending order. Therefore, the overall runtime is O(h+k). Where k is the number of elements within the given range.

Implementation of size-balanced criteria according to 
the given guidelines:

    Level of completion: _____5______











