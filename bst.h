#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <vector>

template <typename T>
class bst {

  private: 
    struct bst_node {
      T      val;
      bst_node *left;
      bst_node *right;

      int size_left;
      int size_right;

      bst_node ( const T & _val = T{}, bst_node * l = nullptr, bst_node *r = nullptr)
        : val { _val },  left { l }, right {r} 
      {
        size_left = 0;
        size_right = 0;
      }

    };



  public:
    // constructor:  initializes an empty tree
    bst(){
      root = nullptr;
    }

  private:
    // helper function which recursively deallocates nodes
    //   in a tree.
    static void delete_nodes(bst_node *r){
      if(r==nullptr) return;
      delete_nodes(r->left);
      delete_nodes(r->right);
      delete r;
    }

  public:
    // destructor
    ~bst() {
      delete_nodes(root);
    }

  private:
    static int _max_subTree(int x, int y){
      if(x >=  y)
        return x;
      return y;
    }
    static int _min_subTree(int x, int y){
      if(x <= y)
        return x;
      return y;
    }

    static bool violater_node(int min, int max){
      if(max > 2*min + 1)
        return true;
      return false;
    }

    

/**
 * function:  insert()
 * desc:      recursive helper function inserting x into
 *            binary search tree rooted  at r.
 *
 * returns:   pointer to root of tree after insertion.
 *
 * notes:     if x is already in tree, no modifications are made.
 */
    static bst_node * _insert(bst_node *r, T & x, bool &success, bst_node* & violation, bst_node* &violationParent, bool& leftChild){
      if(r == nullptr){
        success = true;
        return new bst_node(x, nullptr, nullptr);
      }

      if(r->val == x){
        success = false;
        return r;
      }
      if(x < r->val){
        r->left = _insert(r->left, x, success, violation, violationParent, leftChild);
        r->size_left++;

        if(violater_node(_min_subTree(r->size_left,r->size_right),_max_subTree(r->size_left,r->size_right)))
          violation = r;

        if(violation != nullptr && r->left == violation){
          violationParent = r;
          leftChild = true;
        }
        else if(violation != nullptr && r->right == violation){
          violationParent = r;
          leftChild = false;
        }

        return r;
      }// if

      else {
        r->right = _insert(r->right, x, success, violation, violationParent, leftChild);
        r->size_right++;

        if(violater_node(_min_subTree(r->size_left,r->size_right),_max_subTree(r->size_left,r->size_right)))
          violation = r;

        if(violation != nullptr && r->left == violation){
          violationParent = r;
          leftChild = true;
        }
        else if(violation != nullptr && r->right == violation){
          violationParent = r;
          leftChild = false;
        }

        return r;
      }// else
    }

    static void _to_node_vec(std::vector<bst_node*>* arr, bst_node* r){
      if(r == nullptr)
        return;

      _to_node_vec(arr, r->left);
      arr->push_back(r);
      _to_node_vec(arr, r->right);

      return;
    }

    static bst_node* _from_node_vec( std::vector<bst_node*>* &arr, int low, int hi){
      int m;
      bst_node* root;

      if(hi < low)
        return nullptr;
      
      m = (low + hi)/2;
      root = arr->at(m);

      root->size_left = m - low;
      root->size_right = hi - m;

      root->left  = _from_node_vec(arr, low, m-1);
      root->right = _from_node_vec(arr, m+1, hi);
      
      return root;
    }

     void _size_balanced(bst_node* &violation, bst_node* &violationParent, bool leftChild){
      std::vector<bst_node*> *arr = new std::vector<bst_node*>();

      _to_node_vec(arr, violation);
    
      if(violation == this->root){
        violation = _from_node_vec(arr,0, violation->size_left + violation->size_right);
        std::cout<<violation->val <<std::endl;
        this->root = violation;
      }
      else{
        violation = _from_node_vec(arr,0, violation->size_left + violation->size_right);
        if(leftChild)
          violationParent->left = violation;
        else
          violationParent->right = violation;
      }    

      delete arr;
    }


  public:
  /**
   * function:  insert
   * desc:      inserts x into BST given by t.  Note that
   *            a BST stores a SET -- no duplicates.  Thus,
   *            if x is already in t when call made, no 
   *            modifications to tree result.
   *
   * note:      helper function does most of the work.
   *
   */
   bool insert(T & x){
      bool success;
      bst_node* violation = nullptr;
      bst_node* violationParent;
      bool leftChild = false;

      root = _insert(root, x, success, violation, violationParent, leftChild);
      
      if(violation != nullptr){
        //std::cout<< "final violation: " <<violation->val <<std::endl;
        _size_balanced(violation, violationParent, leftChild);
      }// if        
      
      return success;
   }

/**
 * function:  contains()
 * desc:      returns true or false depending on whether x is an
 *            element of BST (calling object)
 *
 */
    bool contains(const T & x){
      bst_node *p = root;

      while(p != nullptr){

        if(p->val == x)
          return true;
        if(x < p->val){
          p = p->left;
        }
        else
          p = p->right;
      }
      return false;  
    }

  private:
    // returns pointer to node containing
    //   smallest value in tree rooted at r
    static bst_node * _min_node(bst_node *r ){
      if(r==nullptr)
        return nullptr; // should never happen!
      while(r->left != nullptr)
        r = r->left;
      return r;
    }

    // returns pointer to node containing
    //   smallest value in tree rooted at r
    static bst_node * _max_node(bst_node *r ){
      if(r==nullptr)
        return nullptr; // should never happen!
      while(r->right != nullptr)
        r = r->right;
      return r;
    }

    // recursive helper function for node removal
    //   returns root of resulting tree after removal.
    static bst_node * _remove(bst_node *r, T & x, bool &success, bst_node* & violation, bst_node* &violationParent, bool& leftChild){
      bst_node *tmp;
      bool sanity;

      if(r==nullptr){
        success = false;
        return nullptr;
      }// of
      if(r->val == x){
        success = true;

        if(r->left == nullptr){
          tmp = r->right;
          delete r;
          return tmp;
        }// if
        if(r->right == nullptr){
          tmp = r->left;
          delete r;
          return tmp;
        }// if
        // if we get here, r has two children
        r->val = _min_node(r->right)->val;
        r->size_right--;
        r->right = _remove(r->right, r->val, sanity, violation, violationParent, leftChild);
        if(!sanity)
          std::cerr << "ERROR:  remove() failed to delete promoted value?\n";
        
        return r;
      }// if

      if(x < r->val){
        r->left = _remove(r->left, x, success, violation, violationParent, leftChild);
        if(success)
          r->size_left--;
        
        if(violater_node(_min_subTree(r->size_left,r->size_right),_max_subTree(r->size_left,r->size_right)))
          violation = r;

        if(violation != nullptr && r->left == violation){
          violationParent = r;
          leftChild = true;
        }
        else if(violation != nullptr && r->right == violation){
          violationParent = r;
          leftChild = false;
        }

      }// if
      else {
        r->right = _remove(r->right, x, success, violation, violationParent, leftChild);
        if(success)
          r->size_right--;

        if(violater_node(_min_subTree(r->size_left,r->size_right),_max_subTree(r->size_left,r->size_right)))
          violation = r;

        if(violation != nullptr && r->left == violation){
          violationParent = r;
          leftChild = true;
        }
        else if(violation != nullptr && r->right == violation){
          violationParent = r;
          leftChild = false;
        }
      }// else
      return r;

    }

  public:

    bool remove(T & x){
      bool success;
      bst_node* violation = nullptr;
      bst_node* violationParent;
      bool leftChild = false;

      root = _remove(root, x, success, violation, violationParent, leftChild);
      
      if(violation != nullptr){
        //std::cout<< "final violation: " <<violation->val <<std::endl;
        _size_balanced(violation, violationParent, leftChild);
      }// if
      
      return success;
    }


  private:
    // recursive helper function to compute size of
    //   tree rooted at r
    static int _size(bst_node *r){
      if(r==nullptr) return 0;
      return _size(r->left) + _size(r->right) + 1;
    }

  public: 
    int size() {
      //return _size(root);
      return root->size_left + root->size_right + 1;
    }

  private:

    static int _height(bst_node *r){
      int l_h, r_h;

      if(r==nullptr) return -1;
      l_h = _height(r->left);
      r_h = _height(r->right);
      return 1 + (l_h > r_h ? l_h : r_h);
    }

  public:

    int height() {
      return _height(root);
    }

    bool min(T & answer) {
      if(root == nullptr){
        return false;
      }
      answer = _min_node(root)->val;
      return true;
    }

    T max() {
      return _max_node(root)->val;
    }
    private:
    static void _to_vector(std::vector<T>* arr, bst_node* r){
      if(r == nullptr)
        return;
      
      _to_vector(arr, r->left);
      arr->push_back(r->val);
      _to_vector(arr, r->right);
      return;
    }
    public:
    /******************************************
     *
     * "stubs" for assigned TODO functions below 
     *
     *****************************************/
    
    /* TODO
     * Function:  to_vector
     * Description:  allocates a vector of type T and populates
     *               it with the elements of the tree in sorted
     *               order.  A pointer to the vector is returned.
     *
     * runtime:  O(n) where n is the tree size.
     *
     */
    std::vector<T> * to_vector() {
      std::vector<T>* answer = new std::vector<T>();
      
      _to_vector(answer, root);

      return answer;
    }
    
    private:
    static void _get_ith(bst_node* r, int i, T &x){
      if(r == nullptr)
        return;
      
      if(i == r->size_left + 1 ){
        x = r->val;
        return;
      }// if

      if(i <= r->size_left)
        _get_ith(r->left, i, x);
      
      else{
        i = i - (r->size_left + 1);
        _get_ith(r->right, i, x);
      }// else
      
      return;
    }
    public:

    /* TODO
     * Function:  get_ith
     * Description:  determines the ith smallest element in t and
     *    "passes it back" to the caller via the reference parameter x.  
     *    i ranges from 1..n where n is the number of elements in the 
     *    tree.
     *
     *    If i is outside this range, false is returned.
     *    Otherwise, true is returned (indicating "success").
     *
     * Runtime:  O(h) where h is the tree height
     */
    bool get_ith(int i, T &x) {
      if(root == nullptr || i > (root->size_left + root->size_right + 1) || i <= 0)
        return false;

      _get_ith(root, i, x);
      
      return false;   // placeholder
    }


    /* 
     * get_ith_SLOW:  slow version of get_ith which gives the right answer, but
     *   does so by "walking the entire tree".
     * might be helpful for debugging?
     * Private helper below does most of the work
     */
    bool get_ith_SLOW(int i, T &x) {
      int n = size();
      int sofar=0;

      if(i < 1 || i > n) 
        return false;

      _get_ith_SLOW(root, i, x, sofar);
      return true;
    }

  private:
    // recursive helper function that does most of the work
    static void _get_ith_SLOW(bst_node *t, int i, T &x, int &sofar) {
      if(t==nullptr) 
        return;
      _get_ith_SLOW(t->left, i, x, sofar);

      if(sofar==i) 
        return;
      sofar++;
      if(sofar==i) {
        x = t->val;
        return;
      }
      _get_ith_SLOW(t->right, i, x, sofar);
    }

  static void _position_of(bst_node* r, int& i, const T & x){
    if(r == nullptr){
      i = -1;
      return;
    }

    if(x == r->val){
      i = i + r->size_left + 1;
      return;
    }

    if(x < r->val)
      _position_of(r->left, i, x);
    

    else{
      i = i + r->size_left + 1 ;
       _position_of(r->right, i, x);
    }// else
    
    return;
  }


  public:

    /* TODO
     * Function: position_of 
     * Description:  this is like the inverse of
     *       get_ith:  given a value x, determine the 
     *       position ("i") where x would appear in a
     *       sorted list of the elements and return
     *       the position as an integer.
     *       If x is not in the tree, -1 is returned.
     *       Examples:
     *           if x happens to be the minimum, 1 is returned
     *           if x happens to be the maximum, n is returned where
     *               n is the tree size.                  
     *                  
     *       Notice the following property:  for a bst t with n nodes,                  
     *           pick an integer pos:1 <= pos <= n.                  
     *           Now consider the following:
     *       
                    T x;
                    int pos, pos2;
                    // set pos to a value in {1..n}
                    t.get_ith(pos, x);  // must return true since pos is in {1..n}

                    // now let's find the position of x (just retrieved) 
                    pos2 = t.position_of(x);
                    if(pos != pos2) {
                        std::cout << "THERE MUST BE A BUG!\n";
                    }

                 See how position_of performs the inverse operation of get_ith?
     *       
     * Return:  -1 if x is not in the tree; otherwise, returns the position where x 
     *          would appear in the sorted sequence of the elements of the tree (a
     *          value in {1..n}          
     *
     * Runtime:  O(h) where h is the tree height
     */
    int position_of(const T & x) {
      int i = 0;
      _position_of(root, i, x);
      return i;  // placeholder
    }

    private:

    static void _num_geq(bst_node* r, int& n, const T & x){
      if(r == nullptr)
        return;

      n = n + r->size_right + 1;
       
      if(x == r->val)
        return;
      

      if(x > r->val){
        n -= r->size_right + 1;
        _num_geq(r->right, n, x);
      }
      else
        _num_geq(r->left, n, x);

    }

    public:
    /* TODO
     * Function:  num_geq
     * Description:  returns the number of elements in tree which are 
     *       greater than or equal to x.
     *
     * Runtime:  O(h) where h is the tree height
     */
    int num_geq(const T & x) {
      int n = 0;
      _num_geq(root, n, x);
      return n;  // placeholder
    }

    /*
     * function:     num_geq_SLOW
     * description:  same functionality as num_geq but sloooow (linear time)
     *                (private helper does most of the work)
     *
     */
    int num_geq_SLOW(const T & x) {
      return _num_geq_SLOW(root, x);
    }

  private:
    static int _num_geq_SLOW(bst_node * t, const T & x) {
      int total;

      if(t==nullptr) return 0;
      total =_num_geq_SLOW(t->left, x) + _num_geq_SLOW(t->right, x);

      if(t->val >= x)
        total++;
      return total;
    }
  
  private:
  static void _num_leq(bst_node* r, int& n, const T &x){
    if(r == nullptr)
      return;
    
    n = n + r->size_left + 1;

    if(x == r->val)
      return;
    
    if(x < r->val){
      n -= r->size_left + 1;
      _num_leq(r->left, n, x);
    }
    else{
      _num_leq(r->right, n, x);
    }

  }
  public:

    /* TODO
     * Function:  num_leq
     * Description:  returns the number of elements in tree which are less
     *      than or equal to x.
     *
     * Runtime:  O(h) where h is the tree height
     *
     **/
    int num_leq(const T &x) {
      int n = 0;
      _num_leq(root, n, x);
      return n;  // placeholder
    }

    /*
     * function:     num_leq_SLOW
     * description:  same functionality as num_leq but sloooow (linear time)
     *               (private helper _num_leq_SLOW does most of the work)
     */
    int num_leq_SLOW(const T & x) {
      return _num_leq_SLOW(root, x);
    }
  private:

    // helper for num_leq_SLOW
    static int _num_leq_SLOW(bst_node *t, const T &x) {
      int total;

      if(t==nullptr) return 0;
      total =_num_leq_SLOW(t->left, x) + _num_leq_SLOW(t->right, x);

      if(t->val <= x)
        total++;
      return total;
    }

    static void _num_range(bst_node* r, int& n, const T & min, const T & max){
      if(r == nullptr)
        return;

      if( r->val > max ){
        _num_range(r->left, n,  min, max);
        return;
      }

      if(r->val <  min){
        _num_range(r->right, n, min, max);
        return;
      }

      n++;
      _num_range(r->left, n, min, max);
      _num_range(r->right, n, min, max);
    }

  public:

    /* TODO
     * Function:  num_range
     * Description:  returns the number of elements in tree which are
     *       between min and max (inclusive).
     *
     * Runtime:  O(h) where h is the tree height
     *
     **/
    int num_range(const T & min, const T & max) {
      int n = 0;

      _num_range(root, n, min, max);
      
      return n;
    }

    /*
     * function:     num_range_SLOW
     * description:  same functionality as num_range but sloooow (linear time)
     *               (private helper _num_range_SLOW does most of the work)
     *
     */
    int num_range_SLOW(const T & min, const T & max) {
      return _num_range_SLOW(root, min, max);
    }

  private:
    static int _num_range_SLOW(bst_node *t, const T &min, const T &max) {
      int total;

      if(t==nullptr) return 0;
      total =_num_range_SLOW(t->left, min, max) + 
                _num_range_SLOW(t->right, min, max);

      if(t->val >= min && t->val <= max)
        total++;
      return total;
    }

    static void _extract_range(bst_node* r, std::vector<T> *answer, const T & min, const T & max){
      if(r == nullptr)
        return;

      if( r->val > max ){
        _extract_range(r->left, answer,  min, max);
        return;
      }

      if(r->val <  min){
        _extract_range(r->right, answer, min, max);
        return;
      }
      _extract_range(r->left, answer, min, max);
      answer->push_back(r->val);
      
      _extract_range(r->right, answer, min, max);
    }
  public:

    /*
     * TODO
     * function:     extract_range
     * Description:  allocates a vector of element type T
     *               and populates it with the tree elements
     *               between min and max (inclusive) in order.  
     *               A pointer to the allocated and populated
     *               is returned.
     *
     * notes/comments:  even if the specified range is empty, a
     *                  vector is still allocated and returned;
     *                  that vector just happens to be empty.
     *                  (The function NEVER returns nullptr).
     *
     * runtime:  the runtime requirement is "output dependent".
     *           Let k be the number of elements in the specified range
     *           (and so the length of the resulting vector) and let h
     *           be the height of the tree.  The runtime must be:
     *
     *                  O(h + k)
     *
     *           So...while k can be as large as n, it can be as small
     *           as zero.  
     *
     */
    std::vector<T> * extract_range(const T & min, const T & max) {
      std:: vector<int> *answer = new std::vector<int>;

      _extract_range(root, answer, min, max);

      return answer;
    }

  /***************************************************
  *  PREORDER AND INORDER TREE TRAVERSALS BELOW      * 
  *                                                  * 
  ***************************************************/

  private:
    static void indent(int m){
      int i;
      for(i=0; i<m; i++)
        std::cout << "-";
    }

    static void _inorder(bst_node *r){
      if(r==nullptr) return;
      _inorder(r->left);
      std::cout << "[ " << r->val << " ]\n";
      // my code
      std::cout<< "size left: " << r->size_left<<std::endl;
      std::cout<< "size right: " << r->size_right <<std::endl;
      //
      _inorder(r->right);
    }

    static void _preorder(bst_node *r, int margin){
      if(r==nullptr) {
        indent(margin);
        std::cout << " nullptr \n";
      } 
      else {
        indent(margin);
        std::cout << "[ " << r->val << " ]\n";
        _preorder(r->left, margin+3);
        _preorder(r->right, margin+3);
      }
    }

  public:
    void inorder() {
      std::cout << "\n======== BEGIN INORDER ============\n";
      _inorder(root);
      std::cout << "\n========  END INORDER  ============\n";
    }


    void preorder() {

      std::cout << "\n======== BEGIN PREORDER ============\n";
      _preorder(root, 0);
      std::cout << "\n========  END PREORDER  ============\n";

    }

  /***************************************************
  *  END PREORDER AND INORDER TREE TRAVERSALS        * 
  *                                                  * 
  ***************************************************/

  private:
    /* 
     * Recursive  helper function _from_vec, used by
     * from_sorted_arr(...). The function must return a sub-tree that is
     * perfectly balanced, given a sorted array of elements a.
     */
    static bst_node * _from_vec(const std::vector<T> &a, int low, int hi){
      int m;
      bst_node *root;

      if(hi < low) return nullptr;
      m = (low+hi)/2;
      root = new bst_node(a[m]);

      // update size of left tree and right tree.
      root->size_left = m - low;
      root->size_right = hi - m;
      
      root->left  = _from_vec(a, low, m-1);
      root->right = _from_vec(a, m+1, hi);
        
      return root;
    }

  public:
    static bst * from_sorted_vec(const std::vector<T> &a, int n){
      bst * t = new bst();
      t->root = _from_vec(a, 0, n-1);

      return t;
    }

  private:

    /*
     * DO NOT MODIFY THE TWO FUNCTIONS BELOW!!!
     */
    static void _to_preorder_vec(bst_node *t, std::vector<T> &vec) {
      if(t==nullptr) return;
      vec.push_back(t->val);
      _to_preorder_vec(t->left, vec);
      _to_preorder_vec(t->right, vec);
    }
    std::vector<T> * to_preorder_vec() {
      std::vector<T> *vec = new std::vector<T>();
      _to_preorder_vec(root, *vec);
      return vec;
    }

  /*
   * Finally, the data members of the bst class
   */
  private:
    bst_node *root;


}; // end class bst

#endif
