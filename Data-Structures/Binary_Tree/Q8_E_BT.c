//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 8 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode
{
    BTNode *btnode;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    StackNode *top;
} Stack;


///////////////////////// Function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int hasGreatGrandchild(BTNode *node);

BTNode *createBTNode(int item);

BTNode *createTree();
void push( Stack *stack, BTNode *node);
BTNode* pop(Stack *stack);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    char e;
    int c,value;
    BTNode *root;

    c = 1;
    root = NULL;

    printf("1: Create a binary tree.\n");
    printf("2: Find the great grandchildren of the binary tree.\n");
    printf("0: Quit;\n");


    while(c != 0)
    {
        printf("Please input your choice(1/2/0): ");
        if( scanf("%d",&c) > 0)
        {
            switch(c)
            {
            case 1:
                removeAll(&root);
                root = createTree();
                printf("The resulting binary tree is: ");
                printTree(root);
                printf("\n");
                break;
            case 2:
                printf("\nThe values stored in all nodes of the tree that has at least one great-grandchild are: ");
                hasGreatGrandchild(root);
                removeAll(&root);
                break;
            case 0:
                removeAll(&root);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
        }
        else
        {
            scanf("%c",&e);
        }

    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int findGGChild(BTNode *node, int childCnt)
{
    if(childCnt == 3)
        return 1;

    if(node->left == NULL && node->right == NULL)
        return -1;

    int Lresult = -1;
    int Rresult = -1;

    if(node->left != NULL)
        Lresult = findGGChild(node->left, childCnt + 1);
    
    if(node->right != NULL)
        Rresult = findGGChild(node->right, childCnt + 1);

    return max(Lresult, Rresult);
}

int hasGreatGrandchildStack(BTNode *node)
{
	Stack *st = malloc(sizeof(Stack));
    st->top = NULL;
    int isContinue = 1;
    push(st, node);

    while (isContinue)
    {
        BTNode *poped = pop(st);
        if(poped != NULL)
        {
            int Lresult = -1;
            int Rresult = -1;
            if(poped->left != NULL)
            {
                push(st, poped->left);
                Lresult = findGGChild(poped->left, 1);
            }


            if(poped->right != NULL)
            {
                push(st, poped->right);
                Rresult = findGGChild(poped->right, 1);
            }

            if(max(Lresult, Rresult) > 0)
                printf("%d ", poped->item);
        }
        else
        {
            isContinue = 0;
        }
    }
    printf("\n");
    free(st);
    // 저절로 개행 안해주길래 내 재량껏 삽입
}

int hasGreatGrandchild(BTNode *node)
{
    if(node == NULL)
        return 0;
    
    BTNode *Lcur = node->left;
    BTNode *Rcur = node->right;
    int Lcount = 0;
    int Rcount = 0;

        Lcount = hasGreatGrandchild(Lcur);
        Lcount++;

        Rcount = hasGreatGrandchild(Rcur);
        Rcount++;

    int total = max(Lcount, Rcount);
    if(total > 3)
        printf("%d ", node->item);
    
    return total;

}

//////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item)
{
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////////////////////////////////////////////////////////////////////////////


BTNode *createTree()
{
    Stack stack;
    BTNode *root, *temp;
    char s;
    int item;

    stack.top = NULL;
    root = NULL;
    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if(scanf("%d",&item) > 0)
    {
        root = createBTNode(item);
        push(&stack,root);
    }
    else
    {
        scanf("%c",&s);
    }

    while((temp =pop(&stack)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if(scanf("%d",&item)> 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if(scanf("%d",&item)>0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        if(temp->right != NULL)
            push(&stack,temp->right);
        if(temp->left != NULL)
            push(&stack,temp->left);
    }
    return root;
}

void push( Stack *stack, BTNode *node)
{
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if(temp == NULL)
        return;
    temp->btnode = node;
    if(stack->top == NULL)
    {
        stack->top = temp;
        temp->next = NULL;
    }
    else
    {
        temp->next = stack->top;
        stack->top = temp;
    }
}

BTNode* pop(Stack *stack)
{
    StackNode *temp, *top;
    BTNode *ptr;
    ptr = NULL;

    top = stack->top;
    if(top != NULL)
    {
        temp = top->next;
        ptr = top->btnode;

        stack->top = temp;
        free(top);
        top = NULL;
    }
    return ptr;
}

void printTree(BTNode *node)
{
    if(node == NULL) return;

    printTree(node->left);
    printf("%d ",node->item);
    printTree(node->right);
}

void removeAll(BTNode **node)
{
    if(*node != NULL)
    {
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}

