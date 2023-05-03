#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}Node;
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
 * Arranging data for bst tree
*/
void data_arrange(int start, int max, Node **rootNode, int *arr){ // at frist start = 0, max = size of data set
    int mid = div_2_round((float)start + (float)(max - start)/2); 
    if(mid != max){ 
        insertNode(&(*rootNode), arr[mid-1]);
        data_arrange(mid, max, &(*rootNode), arr); 
        max = mid;
        data_arrange(start, max, &(*rootNode), arr);
    }
}
/**
 * build bst tree with the given data set
*/
void build_tree(Node **rootNode, int *arr, int arr_size){
    data_arrange(0, arr_size, &(*rootNode), arr);
    insertNode(&(*rootNode), arr[arr_size-1]);
}
/**
 * a structure to return data found or not and number of step it had to go
*/
struct SCHINFO {
    unsigned int found:1; //bit whether data is found or not
    int step; // number of steps it had to go
};
struct SCHINFO search_info;
/**
 * Search data from the tree
*/
struct SCHINFO search_data(Node *rootNode, int data){
    if(rootNode != NULL){
        if(data == rootNode->data){
            search_info.found = 1;
        }
        else if(data > rootNode->data){
            search_info.step++;
            search_data(rootNode->right, data);
        }
        else{
            search_info.step++;
            search_data(rootNode->left, data);
        }
    }
    else{
        search_info.found = 0;
    }
    return search_info;
}

struct SCHINFO linear_search(int *data_set,int data_size, int data){
    for(int i=0; i<data_size; i++){
        if(data == data_set[i]){
            search_info.found = 1;
            return search_info;
        }
        else{
            search_info.step++;
        }
    }
    search_info.found = 0;
    return search_info;
}

int main(){
    Node *rootNode = NULL;
    int data_set[1000];
    for(int i=0; i<sizeof(data_set)/sizeof(int); i++){
        data_set[i] = i+1;
    }
    build_tree(&rootNode, data_set, sizeof(data_set)/sizeof(int));
    struct SCHINFO data_found = search_data(rootNode, 50);
    // struct SCHINFO data_found = linear_search(data_set, sizeof(data_set)/sizeof(int), 50);
    printf("Number of steps it went through: %d\nData %s\n", data_found.step, (data_found.found)? "found":"not found");
    return 0;
}