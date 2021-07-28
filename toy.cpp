#include <iostream>
#include "bst.h"


int main(){
    int x;
    int h;

    bst<int> *t = new bst<int>();
    
    for(int i = 9; i>=1; i--){
      //std::cout<<"i: " << i << std::endl;
      t->insert(i);
      t->preorder();
     //std::cout<< t->size()<< std::endl;
    }
    /**
    while( (std::cin >> x)) {
      if(x == 'q')
        break;
      t->insert(x);
    }
     */   

    if(t->size() <= 500) {
      t->inorder();
      t->preorder();
    }

    h = t->height();
    std::cout << "\n#### Reported height of tree:   " << h << "\n";
    /*
    // my code
    std::vector<int>* arr = t->to_vector();
    std:: cout << "vector" << std::endl;
    for(int i = 0; i < arr->size(); i++){
      std::cout<< arr->at(i) << std::endl;
    }// for
    int z = 0;
    /*
    t->get_ith(9,z);
    std::cout << "ith: " << z << std::endl;

    std::cout << "position of: " << t->position_of(3)<<std::endl;
    for(int i = 0; i < 18; i++){
      std::cout << "num-geq: " << t->num_geq(i)<<std::endl;
    std::cout << "num-geq slow: " << t->num_geq_SLOW(i)<<std::endl;
    }
    
    for(int i = 0; i < 18; i++){
      std::cout << "num-leq: " << t->num_leq(i)<<std::endl;
    std::cout << "num-leq slow: " << t->num_leq_SLOW(i)<<std::endl;
    }*/
    /*
    std::cout<< "range: " << t->num_range(8,17)<<std::endl;
    std::cout<< "range slow: " << t->num_range_SLOW(8,17)<<std::endl;
    std::vector<int>* answer = t->extract_range(17, 19);
    std:: cout << "vector" << std::endl;
    for(int i = 0; i < answer->size(); i++){
      std::cout<< answer->at(i) << std::endl;
    }// for
    */
   /*
   int y = 4;
   
   //t->inorder();

   t->remove(y);
   
   std::cout<< "removing: " << std::endl;
   t->inorder();
  
 //std:: cout<< arr->size()<< std::endl;
 /*
  bst<int> *copy ;
  copy = copy->from_sorted_vec(*arr, arr->size());
  
  //std::cout<<"sa " <<copy->size();
  //copy = t;
  copy->preorder();
*/
// my code

  for(int i = 9; i >= 0; i--){
    if(i%2 == 0){
      std::cout<<"remove i: " << i << std::endl;
      t->remove(i);
    }
      
  }
  t->preorder();
  t->inorder();
/*
   if(t->size() <= 3000) {
      t->inorder();
      t->preorder();
    }*/
    /*
    t->preorder();
     std::cout<<"n leq: min  " <<  t->num_leq(20)<< std::endl;
     std::cout<<"n leq slow: min  " <<  t->num_leq_SLOW(20)<< std::endl;
   std::cout<<"n leq: max " <<  t->num_leq(70)<< std::endl;
   std::cout<<"n leq slow: max  " <<  t->num_leq_SLOW(70)<< std::endl;

    std::cout<<"n geq: min " <<  t->num_geq(5)<< std::endl;
    std::cout<<"n geq slow: min " <<  t->num_geq_SLOW(5)<< std::endl;
   std::cout<<"n geq: max " <<  t->num_geq(70)<< std::endl;
   std::cout<<"n geq slow: max " <<  t->num_geq_SLOW(70)<< std::endl;
   
   std::cout<<"n range: " <<  t->num_range(5, 70)<< std::endl;
   std::cout<<"n range slow: " <<  t->num_range_SLOW(5, 70)<< std::endl;
   
  /*
  int k = t->size()/2;
  std::vector<int>* arr = t->to_vector();
  
  int ele = arr->at(k);
  std::cout<< ele<< std::endl;
  t->remove(ele);
  std::cout<<"n geq: min " <<  t->num_geq(35)<< std::endl;
    std::cout<<"n geq slow: min " <<  t->num_geq_SLOW(35)<< std::endl;
    */

   
    delete t;
    
    
    return 0;
}
