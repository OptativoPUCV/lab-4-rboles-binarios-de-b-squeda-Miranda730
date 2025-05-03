#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    TreeMap* tree = (TreeMap *)malloc(sizeof(TreeMap));
    tree->root = NULL;
    tree->current = NULL;
    tree->lower_than = lower_than;
    return tree;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode* new = createTreeNode(key, value);

    if(tree->root == NULL){
        tree->current = new;
        tree->root = new;
        return;
    } else {
        TreeNode* aux = tree->root;
        while(1){
            if(tree->lower_than(key, aux->pair->key)){
                if(aux->left != NULL){
                    aux = aux->left;
                } else {
                    aux->left = new;
                    break;
                }
            } else if(tree->lower_than(aux->pair->key, key)){
                if(aux->right != NULL){
                    aux = aux->right;
                } else {
                    aux->right = new;
                    break;
                }
            } else {
                return;
            }
        }
        new->parent = aux;
        tree->current = new;
        return;
    }
    
}

TreeNode * minimum(TreeNode * x){
    while(x->left != NULL){
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    TreeNode* aux = tree->root;
    TreeNode* padre = NULL;

    while(aux != NULL && aux != node){
        padre = aux;
        if(tree->lower_than(node->pair->key, aux->pair->key)){
            aux = aux->left;
        } else if(tree->lower_than(aux->pair->key, node->pair->key)){
            aux = aux->right;
        } else {
            return;
        }
    }
    if(aux->left == NULL && aux->right == NULL){
        if(aux != tree->root){
            if(padre->left == aux){
                padre->left = NULL;
            }else {
                padre->right = NULL;
            }
        } else {
            tree->root = NULL;
        }
        free(aux);
    } else if(aux->left == NULL || aux->right == NULL){
        TreeNode* nino = NULL;

        if(aux->left != NULL){
            nino = aux->left;
        } else {
            nino = aux->right;
        }
        if(tree->root !=aux){
            if(padre->left == aux){
                padre->left = nino;
            }else {
                padre->right = nino;
            }   
            nino->parent = padre;
        } else {
            tree->root = nino;
        }
        free(aux);
    } else {
        TreeNode* minimo = minimum(aux->right);
        node->pair = minimo->pair;
        removeNode(tree, minimo);
    }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode * aux = tree->root;
    
    while(aux != NULL){
        if(is_equal(tree, aux->pair->key,key)){
            tree->current = aux;
            return aux->pair;
        } else if((tree->lower_than(key, aux->pair->key))){
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
