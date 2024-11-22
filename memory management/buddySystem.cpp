#include <bits/stdc++.h>
using namespace std;

struct node{
    int size;
    int rem;
    struct node* left;
    struct node* right;
};


void insertProcess(struct node** root, int psize){
    if(*root==NULL){
        *root = (struct node*)malloc(sizeof(struct node));
        (*root)->left = NULL;
        (*root)->right = NULL;
        (*root)->size = SIZE;
        (*root)->rem = SIZE;
    }

    struct node* temp = *root;
    if(psize<=SIZE && psize>(SIZE/2)){
        (*root)->rem -= psize;
        return;
    }

}
