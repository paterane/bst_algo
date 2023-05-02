#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}Node;

Node *rootNode = NULL;  // empty tree declaration
#define SIZE 16         // size of data in the array
int data_arr[SIZE] = {0}; 
/**
 * Data filling in the array in ascending order
*/
void init_data(){
    for(int i=0; i<SIZE; i++){
        data_arr[i] = i+1;
    }
}
/**
 * return nearest value of float
*/
int div_2_round(float a){
    int d = (int)a;
    int p = ((a - d) * 10) / 5;
    return (d+p);
}
/**
 * create single node
*/
Node *create_new_node(int data){
    Node *newNode = (Node*)(malloc(sizeof(Node)));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
/**
 * push single data into tree
*/
void insertNode(Node **rootNode, int weight){
    if(*rootNode == NULL){
        *rootNode = create_new_node(weight);
    }
    else{
        if(weight > (*rootNode)->data){
            insertNode(&((*rootNode)->right), weight);
        }
        else{
            insertNode(&((*rootNode)->left), weight);
        }
    }
}
/**
 * printing all data in the tree recursively
*/
void printAllData(Node *rootNode){
    if(rootNode != NULL){
        printAllData(rootNode->left);
        printf("data: %d\n", rootNode->data);
        printAllData(rootNode->right);    
    }
    
}
/**
 * building bst tree with sorted data
*/
void build_tree(int start, int max, int d_size){ // at frist start = 2 // max = 3
    int mid = div_2_round((float)start + (float)(max - start)/2); //mid 3
    if(mid != max){ // equal
        insertNode(&rootNode, data_arr[mid-1]);
        build_tree(mid, max, d_size); //
        max = mid;
        build_tree(start, max, d_size);
    }
    if(mid == d_size){
        insertNode(&rootNode, data_arr[mid-1]);
    }
}


int main(){

    init_data();
    build_tree(0, SIZE, SIZE);

    return 0;
}