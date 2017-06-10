#include "bst.h"

/*

                                        depth = 0                      
                                     10 Height = 3                     
                                     /\ num nodes = 1                  
                                    /  \                               
                                   8    33                             
                                 /\      /\                            
                                /  \    /  \                           
                               5    9  21   55                         
                             /\              /\                        
                            /  \            /  \                       
                          7-    6          44   58depth = 3            
                                                  Height = 0           
                                                 num nodes = 4         
                                                                       
                                                                       



                              F              Level 0                                             
                              /\                                                                 
                             /  \                                                                
                            /    \                                                               
                           /      \                                                              
                          D        J         Level 1                                             
                       /\           /\                                                           
                      /  \         /  \                                                          
                     /    \       /    \                                                         
                    /      \     /      \                                                        
                   B        E   G        K    Level 2                                            
                 /\               \                                                              
                /  \               \                                                             
               /    \               \                                                            
              /      \               \                                                           
             A        C               I       Level 3                                            
                                     /                                                           
                                    /                                                            
                                   /                                                             
                                  /                                                              
                                 H             Level 4                                           
                                                                                                 
                                                                                                 
Tree Traversal                                                                                   
    |                                                                                            
    |                                                                                            
    |------Breath First                                                                          
    |          |                                                                                 
    |          |--- Level Order                                                                  
    |             F, D, J, B, E, G, K, A, C, I, H                                                
    |                                                                                            
    |                                                                                            
    |--------Depth First                                                                         
                 |                                                                               
                 |---------PreOrder  (root-left-right)                                           
                 |                                                                               
                 |              F, D, B, A, C, E, J, G, I, H, K                                  
                 |                                                                               
                 |                                                                               
                 |--------- InOrder  (left-root-right)                                           
                 |                                                                               
                 |               A, B, C, D, E, F, G, H, I, K                                    
                 |                                                                               
                 |                                                                               
                 |---------- PostOrder  (left-right-root)                                        
                                                                                                 
                                 A, C, B, E, D, H, I, G, K, J, F                                 
*/


BstNode *BstRoot = NULL;

BstNode* GetNewNode (char data) {
    BstNode* newNode = malloc(sizeof(BstNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

bool SearchNode (BstNode *root, char data)
{
    if(root == NULL)
        return false;
    else if (root->data == data)
        return true;
    else if (data < root->data)
        return SearchNode(root->left, data);
    else
        return SearchNode(root->right, data);
}


BstNode* InsertNode (BstNode *root, char data)
{
    if(root == NULL) 
        return GetNewNode(data);
    if(root->data > data) 
        root->left = InsertNode(root->left, data);
    else if (root->data < data)
        root->right = InsertNode(root->right, data);
    else
        printf("Data %d not valid\n", data);
    return root;
}

int FindMin(BstNode *root)
{
    if(root == NULL) {
        printf("Error: Tree is Empty\n");
        return -1;
    }
    if(root->left == NULL)
        return root->data;
    return FindMin(root->left);
}

BstNode* FindMinNode(BstNode *root)
{
    if(root == NULL) {
        return root;
    }
    if(root->left == NULL)
        return root;
    return FindMinNode(root->left);
}


int FindMax(BstNode *root)
{
    if(root == NULL) {
        printf("Error: Tree is Empty\n");
        return -1;
    }
    if(root->right == NULL)
        return root->data;
    return FindMax(root->right);
}

int FindHeight(BstNode *root)
{
    if(root == NULL) {
        return -1;    
    }
    return MAX(FindHeight(root->left), FindHeight(root->right)) + 1;
}

void PrintLevel (BstNode *root, int level)
{
    if(root == NULL)
        return;
    if(level == 0)
        printf("%c ", root->data);
    else if (level > 0) {
        PrintLevel(root->left, level-1);
        PrintLevel(root->right, level-1);
    }
}

void PrintLevelDir (BstNode *root, int level, bool LtoR)
{
    if(root == NULL)
        return;
    if(level == 0)
        printf("%c ", root->data);
    else if (level > 0) {
        if(LtoR) {
            PrintLevelDir(root->left, level-1, LtoR);
            PrintLevelDir(root->right, level-1, LtoR);
        } else {
            PrintLevelDir(root->right, level-1, LtoR);
            PrintLevelDir(root->left, level-1, LtoR);
        }
    }
}

void SnakeTraversalTop (BstNode *root)
{
    int i, level;
    if (root == NULL)
        return;
    level = FindHeight(root);
    for(i=0 ; i <= level; i++) {
        PrintLevelDir(root, i, i%2);
    }
}

void SnakeTraversalBottom (BstNode *root)
{
    int i, level;
    if (root == NULL)
        return;
    level = FindHeight(root);
    printf("level:%d\n", level);
    for(i=level ; i >= 0; i--) {
        PrintLevelDir(root, i, i%2);
    }
}

void LevelOrderTraversal (BstNode *root)
{
    int i, level;
    if (root == NULL)
        return;
    level = FindHeight(root);
    for(i=0 ; i <= level; i++) {
        PrintLevel(root, i);
    }
}

/*PreOrder  (root-left-right)*/
void PreOrderTraversal (BstNode *root)
{
    if(root == NULL)
        return;
    printf("%c, ", root->data);
    PreOrderTraversal(root->left);
    PreOrderTraversal(root->right);
}

/*InOrder  (left-root-right)*/
void InOrderTraversal (BstNode *root)
{
    if(root == NULL)
        return;
    InOrderTraversal(root->left);
    printf("%c, ", root->data);
    InOrderTraversal(root->right);
}

/*PostOrder  (left-right-root)*/
void PostOrderTraversal (BstNode *root)
{
    if(root == NULL)
        return;
    PostOrderTraversal(root->left);
    PostOrderTraversal(root->right);
    printf("%c, ", root->data);
}

BstNode* DeleteNode (BstNode *root, char data)
{
    if(root == NULL)
        return root;
    if(data < root->data)
        root->left = DeleteNode(root->left, data);
    if(data > root->data)
        root->right = DeleteNode(root->right, data);
    else {
        //case 1; no child
        if((root->left == NULL) && (root->right == NULL)) {
            free(root);
            root = NULL;
        }
        //case 2; single child
        else if(root->left == NULL) {
            struct BstNode_ *temp = root;
            root = root->right;
            free(temp);
        }
        else if(root->right == NULL) { 
            struct BstNode_ *temp = root;
            root = root->left;
            free(temp);
        }

        //case 3; two children
        else {
            BstNode *temp = FindMinNode(root->right);
            root->data = temp->data;
            root->right = DeleteNode(root->right, temp->data);
        }
    }
    return root;
}


int main()
{
    int min, max, height;

    //Inserting following
    //F, D, J, B, E, G, K, A, C, I, H
    BstRoot = InsertNode(BstRoot, 'F');
    BstRoot = InsertNode(BstRoot, 'D');
    BstRoot = InsertNode(BstRoot, 'J');
    BstRoot = InsertNode(BstRoot, 'B');
    BstRoot = InsertNode(BstRoot, 'E');
    BstRoot = InsertNode(BstRoot, 'G');
    BstRoot = InsertNode(BstRoot, 'K');
    BstRoot = InsertNode(BstRoot, 'A');
    BstRoot = InsertNode(BstRoot, 'C');
    BstRoot = InsertNode(BstRoot, 'I');
    BstRoot = InsertNode(BstRoot, 'H');

    if(SearchNode(BstRoot, 'C'))
        printf("found\n");
    else
        printf("not found\n");

    min = FindMin(BstRoot);
    printf("Min = %c\n", min);

    max = FindMax(BstRoot);
    printf("Max = %c\n", max);

    height = FindHeight(BstRoot);
    printf("Height = %d\n", height);

    printf("\n Printing level 3\n");
    PrintLevel(BstRoot, 0);
    printf("\n");
    PrintLevel(BstRoot, 1);
    printf("\n");
    PrintLevel(BstRoot, 2);
    printf("\n");
    PrintLevel(BstRoot, 3);
    printf("\n");
    PrintLevel(BstRoot, 4);


    printf("\n Printing level 3 RtoL\n");
    PrintLevelDir(BstRoot, 3, 0);

    printf("\n Printing level 4 RtoL\n");
    PrintLevelDir(BstRoot, 4, 0);

    printf("SnakeTraversalTop:\n");
    SnakeTraversalTop(BstRoot);
    printf("\n");
    
    printf("SnakeTraversalBottom:\n");
    SnakeTraversalBottom(BstRoot);
    printf("\n");

    printf("LevelOrderTraversal:\n");
    LevelOrderTraversal(BstRoot);
    printf("\n");

    printf("PreOrderTraversal:\n");
    PreOrderTraversal(BstRoot);
    printf("\n");

    printf("InOrderTraversal:\n");
    InOrderTraversal(BstRoot);
    printf("\n");

    printf("PostOrderTraversal:\n");
    PostOrderTraversal(BstRoot);
    printf("\n");

    DeleteNode(BstRoot, 'J');

    printf("InOrderTraversal:\n");
    InOrderTraversal(BstRoot);
    printf("\n");

    printf("\n Printing level \n");
    PrintLevel(BstRoot, 0);
    printf("\n");
    PrintLevel(BstRoot, 1);
    printf("\n");
    PrintLevel(BstRoot, 2);
    printf("\n");
    PrintLevel(BstRoot, 3);
    printf("\n");
    PrintLevel(BstRoot, 4);
    return 0;
}
