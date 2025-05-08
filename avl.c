
/* Relevant includes, you may not use any other includes */
#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------------*/
/* My full name: Or Ishlach*/
/* My friend's full name: Micheal Ghanadre*/

/* My Id: 314861584 */
/* My friend's Id: 211401674 */
/*--------------------------------------------*/

/*------------------------------- AVL DECLERATION -------------------------------*/

typedef enum Position { LEFT, RIGHT } Position;

typedef struct AVLNode* AVLNodePtr;

typedef struct AVLNode
{
    AVLNodePtr child[2]; /*child[0] is left, child[1] is right.*/
    AVLNodePtr parent;
    AVLNodePtr time_tree;
    int key,val,height, rank,flag_time_tree,count;
} AVLNode;

/*------------------------------- BALANCE IMPLEMANT -------------------------------*/

/*Helper functions declaration*/
int _max(int x, int y)
{
    return (x < y) ? y : x;
}
int _abs(int x)
{
    return (x < 0) ? -x : x;
}
int avl_helper_update_height(AVLNodePtr root);
AVLNodePtr avl_helper_balance(AVLNodePtr root);
int avl_helper_balance_factor(AVLNodePtr root);
int avl_helper_update_rank(AVLNodePtr root);


/*Helper functions implemant*/

/*AVL Left rotate */
AVLNodePtr avl_left_rotate(AVLNodePtr root)
{
    AVLNodePtr A = root;
    AVLNodePtr B = A->child[RIGHT];
    AVLNodePtr P = A->parent;

    A->child[RIGHT] = B->child[LEFT];
    if (B->child[LEFT] != NULL)
        B->child[LEFT]->parent = A;
    B->child[LEFT] = A;
    A->parent = B;
    B->parent = P;

    if (P != NULL)
    {
        if (P->child[LEFT] == A)
            P->child[LEFT] = B;
        else
            P->child[RIGHT] = B;
    }

    A->height = avl_helper_update_height(A);
    A->rank = avl_helper_update_rank(A);
    B->height = avl_helper_update_height(B);
    B->rank = avl_helper_update_rank(B);

    return B;
}
/*AVL Right rotate */
AVLNodePtr avl_right_rotate(AVLNodePtr root)
{
    AVLNodePtr A = root;
    AVLNodePtr B = A->child[LEFT];
    AVLNodePtr P = A->parent;

    A->child[LEFT] = B->child[RIGHT];
    if (B->child[RIGHT] != NULL)
        B->child[RIGHT]->parent = A;
    B->child[RIGHT] = A;
    A->parent = B;
    B->parent = P;

    if (P != NULL)
    {
        if (P->child[LEFT] == A)
            P->child[LEFT] = B;
        else
            P->child[RIGHT] = B;
    }

    A->height = avl_helper_update_height(A);
    A->rank = avl_helper_update_rank(A);
    B->height = avl_helper_update_height(B);
    B->rank = avl_helper_update_rank(B);

    return B;
}
/* AVL height update */
int avl_helper_update_height(AVLNodePtr root)
{
    if (!root)
        return -1;

    if (root->child[LEFT] && root->child[RIGHT])
        return _max(root->child[LEFT]->height, root->child[RIGHT]->height) + 1;

    if (root->child[LEFT])
        return root->child[LEFT]->height + 1;
    if (root->child[RIGHT])
        return root->child[RIGHT]->height + 1;

    return 0;
}

/* AVL rank update */
int avl_helper_update_rank(AVLNodePtr root)
{
    if (!root)
        return 0;
    else if (root->child[LEFT] && root->child[RIGHT])
        return root->child[LEFT]->rank + root->child[RIGHT]->rank + root->count;

    else if (root->child[LEFT])
        return root->child[LEFT]->rank + root->count;
    else  if (root->child[RIGHT])
        return root->child[RIGHT]->rank + root->count;

    return root->count;
}
/* AVL balance update */
AVLNodePtr avl_helper_balance(AVLNodePtr root)
{
    /*Calculates child's heights*/
    int rightHeight = avl_helper_update_height(root->child[RIGHT]);
    int leftHeight = avl_helper_update_height(root->child[LEFT]);
    int mainRightIsHeavy, secondaryRightIsHeavy;

    /*If balanced do nothing*/
    if (_abs(avl_helper_balance_factor(root)) < 2)

        return root;

    /*Determine which child is heavy*/
    mainRightIsHeavy = rightHeight > leftHeight;

    /*Get the heights of the heavy child's children*/
    rightHeight = avl_helper_update_height(root->child[mainRightIsHeavy ? RIGHT : LEFT]->child[RIGHT]);
    leftHeight = avl_helper_update_height(root->child[mainRightIsHeavy ? RIGHT : LEFT]->child[LEFT]);

    /*Determine which of the child's children is heavy*/
    secondaryRightIsHeavy = rightHeight > leftHeight;

    /*Secondary rotation*/
    if (mainRightIsHeavy != secondaryRightIsHeavy)
    {
        if (mainRightIsHeavy)
            root->child[RIGHT] = avl_right_rotate(root->child[RIGHT]);
        else
            root->child[LEFT] = avl_left_rotate(root->child[LEFT]);
    }

    /*Base rotation*/
    if (mainRightIsHeavy)
        root = avl_left_rotate(root);
    else
        root = avl_right_rotate(root);

    return root;
}

int avl_helper_balance_factor(AVLNodePtr root)
{
    int left_bf,right_bf;
    if (!root)
        return 0;

     left_bf = root->child[LEFT] ? root->child[LEFT]->height + 1 : 0;
     right_bf = root->child[RIGHT] ? root->child[RIGHT]->height + 1 : 0;

    return left_bf - right_bf;
}


/*------------------------------- SEARCH AVL IMPLEMANT -------------------------------*/

/* Function to search a node in AVL */
AVLNodePtr avl_search(AVLNodePtr root, int x)
{
    if (!root)
    {
        return NULL; /*node not found, return NULL*/
    }

    if (x == root->key)
    {
        return root;
    }
    else if (x < root->key)
    {
        return avl_search(root->child[LEFT], x);
    }
    else
    {
        return avl_search(root->child[RIGHT], x);
    }
}


/*------------------------------- INSERT AVL IMPLEMANT -------------------------------*/
/* Function creating a new node */
AVLNodePtr new_avl_node(int newKey, int newVal)
{
    AVLNodePtr newNode = (AVLNodePtr)malloc(sizeof(AVLNode));
    if (!newNode) return NULL;

    newNode->parent = NULL;
    newNode->time_tree = NULL;
    newNode->child[LEFT] = NULL;
    newNode->child[RIGHT] = NULL;
    newNode->key = newKey;
    newNode->val = newVal;
    newNode->height = 0;
    newNode->rank = 1;
    newNode->flag_time_tree = 0;
    newNode->count = 1; /* Count duplicate for quality */  

    return newNode;
}

/* Function to insert a new node */
    AVLNodePtr avl_insert(AVLNodePtr root, int newKey, int newVal,int flag)
    {       
        AVLNodePtr current;

        if (root == NULL)
        {
            AVLNodePtr newNode = new_avl_node(newKey, newVal);
            newNode->flag_time_tree = flag;
            return newNode;
        }

        if (newKey == root->key )
        {
            root->count++;
            root->rank = avl_helper_update_rank(root);

            return root; /*node already exists*/
        }

        if (newKey < root->key)
        {
            root->child[LEFT] = avl_insert(root->child[LEFT], newKey, newVal,flag);
            root->child[LEFT]->parent = root;
        }
        else
        {
            root->child[RIGHT] = avl_insert(root->child[RIGHT], newKey, newVal,flag);
            root->child[RIGHT]->parent = root;
        }

        /*update height and rank*/
        root->height = avl_helper_update_height(root);
        root->rank = avl_helper_update_rank(root);

        /* balance the tree*/
        root = avl_helper_balance(root);

        /*update the rank of the nodes from the newly inserted node to the root*/ 
        current = root->parent;
        while (current != NULL)
        {
            current->rank = avl_helper_update_rank(current);
            current = current->parent;
        }

        return root;
    }

    /*------------------------------- DELETE IMPLEMANT -------------------------------*/
    /* Function to delete a node */
    AVLNodePtr avl_delete(AVLNodePtr root, int keyDel, int valDel)
    {
      AVLNodePtr toDelete;
        if (!root) return NULL;

         toDelete = avl_search(root, keyDel);
        if (!toDelete) return NULL;

        if (keyDel < root->key)
            root->child[LEFT] = avl_delete(root->child[LEFT], keyDel, valDel);
        else if (keyDel > root->key)
            root->child[RIGHT] = avl_delete(root->child[RIGHT], keyDel, valDel);
        else
        {
            if (!root->child[LEFT] || !root->child[RIGHT])
            {
                AVLNodePtr temp = root->child[LEFT] ? root->child[LEFT] : root->child[RIGHT];
                if (!temp)   /*No children*/
                {
                    temp = root;
                    root = NULL;

                    /*1 child*/
                }
                else
                {
                    if (root->child[LEFT])
                        root->child[LEFT]->parent = root;
                    else
                        root->child[RIGHT]->parent = root;

                    *root = *temp;
                    free(temp);
                }
            }
            else
            {
                AVLNodePtr temp = root->child[RIGHT];
                while (temp->child[LEFT])
                    temp = temp->child[LEFT];

                root->key = temp->key;
                root->val = temp->val;

                root->child[RIGHT] = avl_delete(root->child[RIGHT], temp->key, temp->val);
            }
        }
        if (!root) return NULL;

        root = avl_helper_balance(root);
        root->height = avl_helper_update_height(root);
        root->rank = avl_helper_update_rank(root);

        return root;
    }

    /*Function to delete the time tree */
    AVLNodePtr delete_time_tree(AVLNodePtr root_quality_time, AVLNodePtr root_time)
    {
        if (!root_quality_time) return root_time;

        /*Traverse left subtree*/ 
        root_time = delete_time_tree(root_quality_time->child[LEFT], root_time);

        /* Perform AVL deletion and update root_time only if the node is found*/
        root_time = avl_delete(root_time, root_quality_time->key, root_quality_time->val);

        /*Traverse right subtree*/ 
        root_time = delete_time_tree(root_quality_time->child[RIGHT], root_time);

        /*Free memory for the current node*/ 
        free(root_quality_time);

        return root_time; /*Return the updated root_time*/ 
    }

    /*------------------------------- HELP FUNCTIONS IMPLEMANT FOR DS -------------------------------*/

/*Function to find the i - th sized node in an AVL tree*/ 
    AVLNodePtr find_ith_sized_node(AVLNodePtr node, int i)
    {
        int left_size;
        if (!node)
        {
            return NULL;
        }

         left_size = node->child[LEFT] ? node->child[LEFT]->rank : 0; /*Size of left subtree*/ 

        /*If i corresponds to the current node*/ 
        if (i == left_size + 1)
        {
            return node; /*Return the current node if it is the i - th sized node*/ 
        }
        /*If i is greater than the rank of the left subtree*/ 
        else if (i > left_size + 1)
        {
            return find_ith_sized_node(node->child[RIGHT], i - (left_size + 1)); /*Search in the right subtree*/ 
        }
        /*If i is less than the rank of the left subtree*/ 
        else
        {
            return find_ith_sized_node(node->child[LEFT], i); /*Search in the left subtree*/ 
        }
    }

/*Function to find the i - th sized node in an AVL tree based on quality*/ 
    AVLNodePtr find_ith_sized_node_quality(AVLNodePtr node, int i)
    {
        int left_size, current;
        if (!node)
        {
            return NULL;
        }

         left_size = node->child[LEFT] ? node->child[LEFT]->rank : 0; /* Size of left subtree*/
        /*If i is greater than the rank of the left subtree*/ 
        if (i > left_size)
        {
            i -= left_size; /* Adjust i to search in the time tree*/
             current = node->time_tree ? node->time_tree->rank : 0;

            /*If i is greater than the rank of the time tree*/ 
            if (i > current)
            {
                return find_ith_sized_node_quality(node->child[RIGHT], i - current); /* Search in the right subtree*/
            }
            /*If i is less than or equal to the rank of the time tree*/ 
            else
            {
                return find_ith_sized_node(node->time_tree, i); /*Search in the time tree*/ 
            }
        }
        /*If i is less than or equal to the rank of the left subtree*/ 
        else
        {
            return find_ith_sized_node_quality(node->child[LEFT], i); /*Search in the left subtree*/ 
        }
    }


    /*------------------------------- DATA STRUCTURE IMPLEMANT -------------------------------*/


    typedef struct DataStructure
    {
        AVLNodePtr root_quality; /*Pointer to the root node of AVL tree for quality*/ 
        AVLNodePtr root_main_time; /*Pointer to the root node of AVL tree for time*/ 
        int special_quality;
        int special_quality_flag;
    } DataStructure;


    DataStructure Init(int s) /*Creating our data structure that includes two AVL trees (Time comp : O(1)) */
    {
        DataStructure ds;
        ds.root_main_time = NULL;
        ds.root_quality = NULL;
        ds.special_quality = s;
        return ds;
    }

    void AddProduct(DataStructure* ds, int time, int quality) /*Adding a product to our trees once according to time tree and ones according to quality tree . (Time comp : O(logn)) */
    {
        AVLNodePtr node;
        if (!ds) return;

        /*Update special quality flag if quality matches special_quality*/ 
        if (quality == ds->special_quality)
        {
            ds->special_quality_flag = 1;
        }

        ds->root_quality = avl_insert(ds->root_quality, quality, time, 0);

        /*Search for the node with the given quality and time*/ 
         node = avl_search(ds->root_quality, quality);
        node->time_tree = avl_insert(node->time_tree, time, quality,1);

        /*Insert time into root_main_time AVL tree*/ 
        ds->root_main_time = avl_insert(ds->root_main_time, time, quality,0);

    }

    void RemoveProduct(DataStructure* ds, int time) /*Removing product from the tree according to his insertion time , we remove it from the two trees . (Time comp : O(logn)) */
    {
        AVLNodePtr node_t,node_q;
        int quality;
        if (!ds) return;

         node_t = avl_search(ds->root_main_time, time);
         quality = node_t->val;

        /*product exist*/
        if (node_t)
        {
            /*in case product we want to delete has special_quality*/
            if (ds->special_quality == quality)
            {
                ds->special_quality_flag = 0;
            }

            /*is product in root_quality*/ 
             node_q = avl_search(ds->root_quality, quality);

            node_q->time_tree =  avl_delete(node_q->time_tree, time, quality);

            if (node_q->time_tree)
            {
                node_q->val = node_q->time_tree->key;
                node_q->count--;

            }
            else  ds->root_quality = avl_delete(ds->root_main_time, time, node_t->val);

            ds->root_main_time =  avl_delete(ds->root_main_time, time, node_t->val);
        }

    }



    void RemoveQuality(DataStructure* ds, int quality)   /*Removing the products according to the quality , (Time comp : O(klogn)) */
    {
        AVLNodePtr node_quality;
        if (!ds) return;

         node_quality = avl_search(ds->root_quality, quality); /*Search for the node with the given quality*/ 
        if (!node_quality) return;

        if (ds->special_quality == quality)
        {
            ds->special_quality_flag = 0;
        }

        /*Remove all corresponding times from the main time AVL tree*/ 
        if (node_quality->time_tree)
        {
            ds->root_main_time = delete_time_tree(node_quality->time_tree, ds->root_main_time);
        }

        /*Delete the node from the quality AVL tree*/ 
        ds->root_quality = avl_delete(ds->root_quality, quality, 0);
    }



    /* Function to return the insertion time for the i-th product . (Time comp : O(logn)) */
    int GetIthRankProduct(DataStructure ds, int i)
    {
        AVLNodePtr ith_sized_node;
        if (ds.root_quality->rank < i) /*Check if the number of the nodes in the tree smaller than i (We return -1 ) */

        {
            return  -1;

        }
         ith_sized_node = find_ith_sized_node_quality(ds.root_quality, i);
        if (ith_sized_node )
        {
            return  (ith_sized_node->flag_time_tree == 1) ? ith_sized_node->key : ith_sized_node->val;
        }
        return -1;
    }

    /* Function to return the insertion time for the i-product in the range between time1 and time2 . (Time comp : O(logn)) */
    int GetIthRankProductBetween(DataStructure ds, int time1, int time2, int i)
    {
        int count = 0; /*Counter for the number of items found within the time range*/ 
        int rank = 0; /*Rank of the current item*/ 
        int productTime = -1; /*Time of the ith ranked product within the time range*/ 

        /* Iterate over each rank until we find the ith rank product within the time range*/
        while (rank != -1 && count < i)
        {
            productTime = GetIthRankProduct(ds, rank); /*Get the time of the current rank product*/ 
            if (productTime != -1 && productTime >= time1 && productTime <= time2)
            {
                count++; /*Increment count if the product time is within the range*/ 
            }
            rank++; /*Move to the next rank*/ 
        }

        /*Return the time of the ith rank product within the time range*/ 
        if (count == i)
        {
            return productTime;
        }
        else
        {
            return -1; /*Return -1 if no such product is found*/
        }
    }


    int Exists(DataStructure ds)
    {
        return (ds.special_quality_flag == 1) ? 1 : 0;

    }

/*-------------------------------------------*/
/* Main function for testing the data structure */
 
 /* Utility – flush the input buffer after scanf-ing numbers */
 static void clear_stdin(void)
 {
     int ch;
     while ((ch = getchar()) != '\n' && ch != EOF) { }
 }
 
 int main(void)
 {
     int s;
     printf("Enter the SPECIAL quality value (s): ");
     if (scanf("%d", &s) != 1) return 1;
     clear_stdin();
 
     /* initialise data-structure */
     DataStructure ds = Init(s);
 
     /* interactive loop */
     for (;;)
     {
         int choice;
         puts("\n========== PRODUCT MENU ==========");
         puts("1. Add product               ");
         puts("2. Remove product by time    ");
         puts("3. Remove products by quality");
         puts("4. Get i-th rank product     ");
         puts("5. Get i-th rank product between times");
         puts("6. Does special quality exist?");
         puts("0. Exit");
         printf("Choose: ");
 
         if (scanf("%d", &choice) != 1) break;
         clear_stdin();
 
         switch (choice)
         {
             case 1: {
                 int time, quality;
                 printf("Insert time  and quality: ");
                 if (scanf("%d %d", &time, &quality) == 2) {
                     AddProduct(&ds, time, quality);
                     puts("Product added.");
                 }
                 break;
             }
             case 2: {
                 int time;
                 printf("Insert time to remove: ");
                 if (scanf("%d", &time) == 1) {
                     RemoveProduct(&ds, time);
                     puts("Done (if existed).");
                 }
                 break;
             }
             case 3: {
                 int q;
                 printf("Insert quality to remove: ");
                 if (scanf("%d", &q) == 1) {
                     RemoveQuality(&ds, q);
                     puts("Done (if existed).");
                 }
                 break;
             }
             case 4: {
                 int i;
                 printf("Insert i (rank): ");
                 if (scanf("%d", &i) == 1) {
                     int t = GetIthRankProduct(ds, i);
                     (t == -1)
                         ? puts("No such rank.")
                         : printf("Product time = %d\n", t);
                 }
                 break;
             }
             case 5: {
                 int t1, t2, i;
                 printf("Insert time1 time2 i: ");
                 if (scanf("%d %d %d", &t1, &t2, &i) == 3) {
                     int t = GetIthRankProductBetween(ds, t1, t2, i);
                     (t == -1)
                         ? puts("No such product in range.")
                         : printf("Product time = %d\n", t);
                 }
                 break;
             }
             case 6:
                 printf("Special quality %s.\n", Exists(ds) ? "exists" : "does NOT exist");
                 break;
 
             case 0:
                 puts("Bye!");
                 return 0;
 
             default:
                 puts("Illegal option. Try again.");
         }
         clear_stdin(); /* clean up after each iteration */
     }
 
     return 0;
 }
 