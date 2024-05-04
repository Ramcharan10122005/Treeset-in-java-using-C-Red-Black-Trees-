#include <stdio.h>
#include <stdlib.h>

// Header root
struct header {
    struct item *root;
};

// Defining structure for RBT
struct item {
    int key;
    struct item *left, *right, *parent;
    int color; // '1' for red and '0' for black
};

// Creating a node using value
struct item *createnode(struct header *T, int v) {
    struct item *p = (struct item *)malloc(sizeof(struct item));
    p->key = v;
    p->left = NULL;
    p->right = NULL;
    return p;
}

// Minimum element of BST
struct item *BST_minimum(struct item *x) {
    while (x->left != NULL)
        x = x->left;
    return x;
}

// Maximum element of BST
struct item *BST_maximum(struct item *x) {
    while (x->right != NULL)
        x = x->right;
    return x;
}

// Immediate successor
struct item *successor(struct item *x) {
    struct item *temp = BST_minimum(x->right);
    return temp;
}

// Immediate predecessor
struct item *predecessor(struct item *x) {
    struct item *temp = BST_maximum(x->left);
    return temp;
}

// Return iterator to element having value key
struct item *Find(struct item *x, int k) {
    if (x == NULL || k == x->key) {
        return x;
    }
    if (k < x->key) {
        return Find(x->left, k);
    } else {
        return Find(x->right, k);
    }
}

// BST insertion
void BST_insert(struct header *t, struct item *z) {
    struct item *x = t->root;
    struct item *y = NULL;
    while (x != NULL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == NULL) {
        t->root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
}

void rightrotate(struct header *t, struct item *x) {
    struct item *y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        t->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}

void leftrotate(struct header *t, struct item *x) {
    struct item *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        t->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// Color violation for insertion
void RB_Insert_Fixup(struct header *t, struct item *z) {
    while (z->parent != NULL && z->parent->color == 1) {
        if (z->parent == z->parent->parent->left) {
            struct item *y = z->parent->parent->right;
            if (y != NULL && y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftrotate(t, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                rightrotate(t, z->parent->parent);
            }
        } else {
            struct item *y = z->parent->parent->left;
            if (y != NULL && y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightrotate(t, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                leftrotate(t, z->parent->parent);
            }
        }
    }
    t->root->color = 0;
}



// Color violation for deletion
void RB_Delete_Fixup(struct header *t, struct item *x) {
    struct item *w = NULL;
    while (x != t->root && x->color == 0) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w != NULL && w->color == 1) {
                w->color = 0;
                x->parent->color = 1;
                leftrotate(t, x->parent);
                w = x->parent->right;
            }
            if ((w->left == NULL || w->left->color == 0) && (w->right == NULL || w->right->color == 0)) {
                w->color = 1;
                x = x->parent;
            } else {
                if (w->right == NULL || w->right->color == 0) {
                    if (w->left != NULL) w->left->color = 0;
                    w->color = 1;
                    rightrotate(t, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 0;
                if (w->right != NULL) w->right->color = 0;
                leftrotate(t, x->parent);
                x = t->root;
            }
        } else {
            w = x->parent->left;
            if (w != NULL && w->color == 1) {
                w->color = 0;
                x->parent->color = 0;
                rightrotate(t, x->parent);
                w = x->parent->left;
            }
            if ((w->right == NULL || w->right->color == 0) && (w->left == NULL || w->left->color == 0)) {
                w->color = 1;
                x = x->parent;
            } else {
                if (w->left == NULL || w->left->color == 0) {
                    if (w->right != NULL) w->right->color = 0;
                    w->color = 1;
                    leftrotate(t, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 0;
                if (w->left != NULL) w->left->color = 0;
                rightrotate(t, x->parent);
                x = t->root;
            }
        }
    }
    x->color = 0;
}


// RBT insertion
void Insert(struct header *t, int v) {
    struct item *z = createnode(t, v);
    BST_insert(t, z);
    z->left = NULL;
    z->right = NULL;
    z->color = 1;
    RB_Insert_Fixup(t, z);
    printf("\nvalue %d is added.\n",v);
}

// Transplant function
void transplant(struct header *t, struct item *u, struct item *v) {
    if (u->parent == NULL) {
        t->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

// BST deletion
void BST_delete(struct header *t, struct item *z) {
    if (z->left == NULL) {
        transplant(t, z, z->right);
    } else if (z->right == NULL) {
        transplant(t, z, z->left);
    } else if (z->left != NULL && z->right != NULL) {
        struct item *y = BST_minimum(z->right);
        if (y != z->right) {
            transplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}

// RBT deletion
void Erase(struct header *T, int v) {
    struct item *z = Find(T->root,v);
    struct item *y = z;
    struct item *x=malloc(sizeof(struct item ));
    
    int temp = y->color;

    if (z->left == NULL) {
        x = z->right;
        transplant(T, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(T, z, z->left);
    } else {
        y = BST_minimum(z->right);
        temp = y->color;
        x = y->right;

        if (y != z->right) {
          transplant(T, y, y->right);
          y->right = z->right;
          y->right->parent = y;
           }
        else
        x->parent = y;
        transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (temp == 0) {
        RB_Delete_Fixup(T, x);
    }
     printf("\nvalue %d is deleted.\n",v);
    
}

void Clear(struct item *x) {
    if (x != NULL) {
        Clear(x->left);
        Clear(x->right);
        free(x);
    }
}

void Empty(struct header *t) {
    if (t->root == NULL) {
        printf("\nTrue, set is Empty\n");
    } else {
        printf("\nFalse, set is not Empty\n");
    }
}

void Begin(struct header *t) {
    if (t->root != NULL) {
        printf("\nThe first element in the set is : %d\n", BST_minimum(t->root)->key);
    } else {
        printf("\nThe set is empty.\n");
    }
}

void End(struct header *t) {
    if (t->root != NULL) {
        printf("\nThe last element in the set is : %d\n", BST_maximum(t->root)->key);
    } else {
        printf("\nThe set is empty.\n");
    }
}

void Emplace(struct header *t, int v) {
    if (Find(t->root, v) == NULL) {
        Insert(t, v);
        printf("\nvalue %d is successfully added\n",v);
    }
    else{
    	printf("\nThe value %d already exixts,cannot be added\n",v);
	}
}
int Ceiling(struct item *x, int k) {
    if (x == NULL)
        return -1; 
    if (k <= x->key) {
        int leftCeiling = Ceiling(x->left, k);
        if (leftCeiling != -1) {
            return leftCeiling;
        } else {
            return x->key;
        }
    } else {
        return Ceiling(x->right, k);
    }
}

int Floor(struct item *x, int k) {
    if (x == NULL)
        return -1; 
    if (k >= x->key) {
        int rightFloor = Floor(x->right, k);
        if (rightFloor != -1) {
            return rightFloor;
        } else {
            return x->key;
        }
    } else {
        return Floor(x->left, k);
    }
}

void Tailset(struct item *x, int value, int *printed) {
    if (x != NULL) {
        Tailset(x->left, value, printed);
        if (x->key >= value && !printed[x->key]) {
            printf("%d ", x->key);
            printed[x->key] = 1; 
        }
        Tailset(x->right, value, printed);
    }
}

// Headset function modified to print elements only once
void Headset(struct item *x, int value, int *printed) {

    if (x != NULL) {
        Headset(x->left, value, printed);
        if (x->key < value && !printed[x->key]) {
            printf("%d ", x->key);
            printed[x->key] = 1; 
        }
        Headset(x->right, value, printed);
    }
}


void Subset(struct item *x, int j, int k,int *printed) {
    if (x != NULL) {
        int i;
        for ( i = 0; i < j; i++) {
            printed[i] = 1;
        }
        for ( i = k ; i < 1000; i++) {
            printed[i] = 1;
        }
        Tailset(x, j, printed);   
        Headset(x, k, printed);
    }
}
void Display(struct item *x) {
    if (x != NULL) {
        Display(x->left);
        printf("%d ", x->key);
        Display(x->right);
    }
}
int Size(struct item *x) {
  if (x == NULL) {
    return 0;
  }
  return Size(x->left) + Size(x->right) + 1;
}

int main() {
    int choice;
    struct header *t = malloc(sizeof(struct header));
    int *printed = (int *)calloc(1000, sizeof(int));
    if (t == NULL) {
        printf("Memory allocation failed for header.\n");
        return 1;
    }
    t->root = NULL;
    int v;
    int i;
    do {
        printf("\n1. Insert\n");
        printf("2. Erase\n");
        printf("3. Clear\n");
        printf("4. Empty\n");
        printf("5. Begin\n");
        printf("6. End\n");
        printf("7. Emplace\n");
        printf("8. Find\n");
        printf("9. Ceiling function\n");
        printf("10. Floor function\n");
        printf("11. Headset function\n");
        printf("12. Tailset function\n");
        printf("13. Subset function\n");
        printf("14. Size\n");
        printf("15. Display the elements of set\n");
        printf("0. Exit\n");
        printf("\nEnter your choice:");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\nEnter the value to be added into set:");
                scanf("%d", &v);     
                Insert(t, v);
                break;
            case 2:
                printf("\nEnter the value to be deleted from set:");
                scanf("%d", &v);
                Erase(t, v);
                break;
            case 3:
                Clear(t->root);
                t->root = NULL; // Resetting root after clearing
                break;
            case 4:
                Empty(t);
                break;
            case 5:
                Begin(t);
                break;
            case 6:
                End(t);
                break;
            case 7:
                printf("\nEnter the value to be emplaced into set:");
                scanf("%d", &v);
                Emplace(t, v);
                break;
            case 8:
                printf("\nEnter the value to be searched in the set:");
                scanf("%d", &v);
                if (Find(t->root, v) != NULL) {
                    printf("\nValue %d is present in the set.\n", v);
                } else {
                    printf("\nValue %d is not present in the set.\n", v);
                }
                break;
            case 9:
                printf("\nEnter the value: ");
                scanf("%d",&v);
                if(Ceiling(t->root,v)==-1)
                printf("\nNo such element greater than %d exists\n",v);
                else
                printf("\nThe least element greater than or equal to %d is: %d",v,Ceiling(t->root,v));
                printf("\n");
                break;
            case 10:
                printf("\nEnter the value: ");
                scanf("%d",&v);
                if(Floor(t->root,v)==-1)
                printf("\nNo such element less than or equal to %d exists\n");
                else
                printf("\nThe greatest element less than or equal to %d is: %d",v,Floor(t->root,v));
                printf("\n");
                break;
            case 11:
                for ( i = 0; i < 1000; i++) {
                    printed[i] = 0;
                }
				printf("\nEnter the value: ");
                scanf("%d",&v);
                printf("\nElements less than %d:",v);
                Headset(t->root,v,printed);
                printf("\n");
                break;
            case 12:
                for ( i = 0; i < 1000; i++) {
                    printed[i] = 0;
                }
                printf("\nEnter the value: ");
                scanf("%d",&v);
                printf("\nElements greater than or equal to %d:",v);
                Tailset(t->root,v,printed);
                printf("\n");
                break;
            case 13:
                for ( i = 0; i < 1000; i++) {
                    printed[i] = 0;
                }
                int val1,val2;
                printf("\nEnter the values for range[j,k): ");
                scanf("%d%d",&val1,&val2);
                printf("\nElements in the range [%d,%d):",val1,val2);
                Subset(t->root,val1,val2,printed);
                printf("\n");
                break;
            case 14:
            	printf("\nsize of the set:");
            	printf("%d",Size(t->root));
            	printf("\n");
            	break;
            case 15:
                printf("\nElements of set: ");
                Display(t->root);
                printf("\n");
                break;
            case 0:
                printf("\nExiting.\n");
                break;
            default:
                printf("\nInvalid choice!!!\n");
        }
    } while (choice != 0);
    Clear(t->root);
    free(printed);
    free(t);
    return 0;
}
