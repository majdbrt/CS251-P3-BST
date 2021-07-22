#include <iostream>
#include "bst.h"


int main(){
    int x;
    int h;

    bst<int> *t = new bst<int>();
    
    while( (std::cin >> x)) {
      if(x == 'q')
        break;
      t->insert(x);
    }
        

    if(t->size() <= 20) {
      t->inorder();
      t->preorder();
    }

    h = t->height();
    std::cout << "\n#### Reported height of tree:   " << h << "\n";
    // my code
    std::vector<int>* arr = t->to_vector();
    std:: cout << "vector" << std::endl;
    for(int i = 0; i < arr->size(); i++){
      std::cout<< arr->at(i) << std::endl;
    }// for
// my code
    delete t;
    
    return 0;
}
