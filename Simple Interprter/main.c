#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#define STACKSIZE 100
#define ITEM float
typedef struct
{
	int top;
    float* items ;
} Stack;
/*
 */
 Stack *initialize(Stack *s)
{
   s->top =0;
	s->items = malloc(STACKSIZE*sizeof(ITEM));
}
/*
*/
int isEmpty(Stack *s)
 {
	if(s->top==0)
        return 1;
 else
    return 0;
}
/*
 */
ITEM top(Stack *s)
{
	return s->items[s->top-1];
}
/*
 */
ITEM pop(Stack *s)
{
	return s->items[-- s->top];
}
/*
 */
void push(Stack *s, float val)
{
	s->items[s->top ++]= val;
}
/*
 */
 int piority(char x)
 {
    switch(x)
    {
    case '+':
    case '-':
         return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    case '(':
           return 4;
    }
}
/*
*/
int isnumber(char*expression)
{
    int i;
    for(i=0;i<strlen(expression);i++)
        {
        if(!isdigit(expression[i])&& expression[i]!= '.' )
            return 0;
        }
        return 1;
}
/*
*/
int isNegnum(char*expression)
{
    if(expression[0]=='-'&& strlen(expression)>1)
        {
        for(int i=1;i<strlen(expression);i++)
        {
            if(!isdigit(expression[i])&& expression[i]!= '.' )
                return 0;
        }
        return 1;
    }
    else
        return 0;
}
/*
*/
int isoperator(char c)
{
    if(c== '+' || c== '-' || c== '*' || c== '/' || c== '%'|| c== '^')
        return 1;
    else
        return 0;
}
/*
*/
void removespaces(char *expression)
{
char temp[100];
int i,j=0;
for(i=0;i<strlen(expression);i++)
    {
    if(expression[i]==' ')
        continue;
    else
        temp[j++]=expression[i];
}
temp[j]='\0';
strcpy(expression,temp);
}
/*
*/
void infixToPostfix(char* infix, char* postfix)
{
	int i,j=0;
	Stack s;
	initialize(&s);
	removespaces(infix);
	for(i=0;i<strlen(infix);i++)
	{
 if(isdigit(infix[i]) || infix[i] =='.' ||(infix[i]== '-' && (i==0 || isoperator(infix[i-1]) || infix[i-1]=='(' )))
            postfix[j++]=infix[i];

        else if(infix[i]==')')
        {

            while(!isEmpty(&s)&&top(&s)!='(')
                  {
                    postfix[j++]=' ';
                    postfix[j++]=pop(&s);
                    postfix[j++]=' ';
                  }
            pop(&s);
        }
        else if(isEmpty(&s))
        {
            push(&s,infix[i]);
            postfix[j++]=' ';
        }
        else
            {
            while(!isEmpty(&s)&&piority(top(&s))>=piority(infix[i])&&top(&s)!='(')
                  {
                    postfix[j++]=' ';
                    postfix[j++]=pop(&s);
                    postfix[j++]=' ';
                  }
                    push(&s,infix[i]);
                    postfix[j++]=' ';
        }
	}
	 if(!isEmpty(&s))
	 {
	 while(!isEmpty(&s))
	 {
        postfix[j++]=' ';
        postfix[j++]=pop(&s);
	 }
	 }
	 else
        strcpy(postfix,infix);
}
/*
*/
float evaluatePostfix(char *postfix)
{
	Stack s;
    initialize(&s);
    float operand1,operand2,y;
    char *temp;
    temp=strtok(postfix," ");
while(temp != NULL)
{
    if(isnumber(temp) || isNegnum(temp))
    {
        y=atof(temp); /*convert string to double */
        push(&s,y);
    }
        else{
            operand2=pop(&s);
            operand1=pop(&s);

            if(strcmp(temp, "+")==0)
                push(&s,operand2+operand1);
            else if (strcmp(temp, "-")==0)
                push(&s,operand1-operand2);
            else if(strcmp(temp,"*")==0)
                push(&s,operand2*operand1);
            else if(strcmp(temp,"/")==0)
                push(&s,operand1/operand2);
                 else if(strcmp(temp,"^")==0)
                push(&s,pow(operand1,operand2));
        }
        temp = strtok(NULL," ");
    }
     return pop(&s);
}
/*
 */
typedef struct
{
    char data[30];
    float value;
    struct node *left,*right;
}node;
/*
 */
typedef struct
{
    node *root;
}BST;
/*
 */
BST *treeinit()
{
    BST *t=malloc(sizeof(BST));
   t->root=NULL;
   return t;
}
/*
 */
node *Newnode(char *key,float val)
{
    node *n=malloc(sizeof(node));
    strcpy(n->data,key);
    n->value=val;
    n->left=NULL;
    n->right=NULL;
    return n;
}
/*
 */
 node *insert(node *n, char *key,float value)
{
 if (n==NULL)
 return Newnode(key,value);
 if (strcasecmp(key,n->data)<0)
    n->left=insert(n->left,key,value);
 else if (strcasecmp(key,n->data)>0)
    n->right=insert(n->right,key,value);
            return n;
}
/*
 *function to search a tree with a given key and return node.
 */
node *search_node(node *n,char *key)
{
    node *t=n;
    node *prev=NULL;
    int flag=0;
 while (t!=NULL)
 {
    if (strcasecmp(t->data,key)==0)
        {
        return t;
        flag=1;
        }
    else if (strcasecmp(key,t->data)<0)
        {
        prev=t;
        t=t->left;
        }
    else
        {
        prev=t;
        t=t->right;
        }
 }
    if(flag==1)
    return prev;

    else
        return NULL;
}
/*
 * Function to search a tree with a given key and returns the (data) in the same node of that key.
 */
char *search(node *n,char *key)
{
    node *t=n;
    node *prev=NULL;
    int flag=0;

 while (t!=NULL)
 {
    if (strcasecmp(t->data,key)==0)
        {
        return t->data;
        flag=1;
        }

    else if (strcasecmp(key,t->data)<0)
        {
        prev=t;
        t=t->left;
        }
    else
        {
        prev=t;
        t=t->right;
        }
 }
    if(flag==1)
    return prev->data;

    else
        return NULL;
}
/*
 * Function to search a tree with a given key and returns the (value) in the same node of that key.
 */
 float search_val(node *n,char *key)
{
    node *t=n;
    node *prev=NULL;
    int flag=0;

 while (t!=NULL)
 {
    if (strcasecmp(t->data,key)==0)

       {
           return t->value;
           flag=1;
       }

    else if (strcasecmp(key,t->data)<0)
        {
        prev=t;
        t=t->left;
        }
    else{
        prev=t;
        t=t->right;
    }
 }
    if(flag==1)
    return prev->value;

    else
        return 0;
}
/*
 * Function to print tree in a (in order) traverse.
 */
void INorderTraverse(node *t)
{
    if(t!=NULL)
    {
       INorderTraverse(t->left);
         printf("%s = %.2f\n",t->data,t->value);
        INorderTraverse(t->right);
    }
}
/*
 * Function to deliver number of lines in a file.
 */
int sizeofFile(char name[])
{
    FILE *f1;
    char datatoberead[100];
    f1=fopen(name,"r");
    int count=0;
   while(!feof(f1))
    {
        fscanf(f1,"%[^\n]%2%s",datatoberead);
        count ++;
     }
      return count;
}
/*
 * Function to change a single character into string type.
 */
 char *charTOstr(char source)
{
	char *destination;
	destination = malloc(2 * sizeof(char)); // just to be clear
	destination[0] = source;	// copy the character into the string
	destination[1] = '\0';		// null-terminate the string
	return destination;
}
/*
 * Function to change a string into float.
 */
 char *fTOstr(float f)
{
     char *buf;
     buf= malloc(10*sizeof(char));
     return gcvt(f,4,buf);
}
/*
 * Function to concatenate a string to another string.
 */
 char* concat(char *s1,char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
/*
 * Function to update value of a variable.
 */
void update(node *n,char *key,float val)
{
    node *t=search_node(n,key);
    if(t)
        t->value=val;
}
/*
 * Functions to do heap sort (minimum heap).
 */
void *swap(node *n1,node *n2)
{
    node temp=*n1;
    *n1=*n2;
     *n2=temp;
}
/*
 */
void heapify(node *arr[],int n,int i)
{
	int largest = i; // Initialize largest as root
	int l = 2*i + 1; // left = 2*i + 1
	int r = 2*i + 2; // right = 2*i + 2

	// If left child is larger than root
	if (l < n && arr[l]->value > arr[largest]->value )
		largest = l;

	// If right child is larger than largest so far
	if (r < n && arr[r]->value > arr[largest]->value)
		largest = r;

	// If largest is not root
	if (largest != i)
	{
		swap(arr[i],arr[largest]);

		// Recursively heapify the affected sub-tree
		heapify(arr, n, largest);
	}
}
/*
 *main function to do heap sort.
 */
void heapSort(node *arr[], int n)
{
	// Build heap (rearrange array)
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// One by one extract an element from heap
	for (int i=n-1; i>0; i--)
	{
		// Move current root to end
		swap(arr[0],arr[i]);

		// call max heapify on the reduced heap
		heapify(arr, i, 0);
	}
}
/*
 * Function to print array of size n.
 */
void printArray(node *arr[], int n)
{
	for (int i=0; i<n; ++i)
		printf("%s = %.2f\n",arr[i]->data,arr[i]->value);
}
/*
 * function to delete duplicated nodes from an array.
 */
int del_dup(node *arr[],int size)
{
    int i,j,k;       // Loop control variables
    for(i=0;i<size;i++)
    {
        for(j=i+1;j<size;j++)
        {
            /* If any duplicate found */
            if(arr[i]==arr[j])
            {
                /* Delete the current duplicate element */
                for(k=j;k<size;k++)
                {
                    arr[k]=arr[k+1];
                }
                /* Decrement size after removing duplicate element */
                size--;

                /* If shifting of elements occur then don't increment j */
                j--;
            }
        }
    }
    return size;
}
/*
 * Functions to handle errors.

 * check if there is equal in the statement.
 */
 int ExistEqual(char *s)
 {
 char *z;
 char w[]="=";
 z=strstr(s,w);
    if(z)
       return 1;
    else
        return 0;
 }
/*
 * check if there is more than one variable in L.H.S.
 */
int OneVariable(char *s)
{
    for(int i=0;i<strlen(s);i++)
   {
    if(isoperator(s[i]))
    {
       return 0;
        break;
    }
    else
        continue;
    }
}
/*
 * check if there is invalid variable in L.H.S.
 */
int notAlpha(char c)
{
    if(isalpha(c)||c=='_'||c=='$')
        return 0;
    else
        return 1;
}
int validVariable(char *s)
{
if(notAlpha(s[0]))
    return 0;
else
    return 1;
}
/*
 * function to check if the the expression is valid or not.
 */
int validExp(char *s)
{
    int count=0;
    for(int i=0;i<strlen(s);i++)
    {
        if(s[i]=='('||s[i]==')')
            count++;
    }
    if(count%2==0)
        return 1;
    else
        return 0;
}
/*
 * function to test all errors in the file.
 */
int testError(char *name)
{
    int flag=0;
    FILE *f1;
    f1=fopen(name,"r");
    char *x[100];
    char *instruction[256];
    char *p=malloc(sizeof(char));
    int i=0,j=0;

    for(int i=0;i<sizeofFile(name);i++)
    {
        fscanf(f1,"%[^\n]%2%s",&instruction[i]);
        removespaces(&instruction[i]);
       if (ExistEqual(&instruction[i]))
       {
        p=strtok(&instruction[i],"=");

         while(p!=NULL)
          {
            x[j]=p;
            printf("%s\n",x[j])
            p=strtok(NULL,"=");
            j++;
          }

          if(OneVariable(x[j-2])&&validVariable(x[j-2])&&validExp(x[j-1]))
          {
              flag=1;
          }
          else
          {
              flag=0;
           puts("-------------------");
            printf("ERROR!!!\nstatement (%d) is invalid.\a\n",i+1);
             puts("-------------------");
            break;
          }
       }
       else
        {
            flag=0;
            puts("-------------------");
            printf("ERROR!!!\nstatement (%d) is invalid.\a\n",i+1);
             puts("-------------------");
            break;
        }
    }
    if(flag==1)
        return 1;
    else
        return 0;
}
/*
 * Main function to interpret a given file.
 */
void interpret(char name[])
{
    char *instruction[256];
    char postfixExpr[256]="";

    node *arr[sizeofFile(name)];   /*array of nodes for heap sort*/

     BST *t=treeinit();

    FILE *f1;
    f1=fopen(name,"r");

    char *x[200];  /*each pointer will hold an infix expression*/
    char *y[200];  /*each pointer will hold a copy from the infix expression*/

    char *p;
    int i=0,j=0;
    int flag=0;

   if(testError(name))
   {
    for(int i=0;i<sizeofFile(name);i++)
    {
        fscanf(f1,"%[^\n]%2%s",&instruction[i]);  /*scan from file line by line and assign a pointer to each line */
        removespaces(&instruction[i]);/*to remove i=any spaces in the instruction line*/

        p=strtok(&instruction[i],"=");   /* divide line into 2 parts */

         while(p!=NULL)
          {
            x[j]=p;
            p=strtok(NULL,"=");
            j++;
          }

      if(!search(t->root,x[j-2]))     /*new variable is added to the file(NOT PREdefined)*/
        {
             y[i-1]="";
          int len=strlen(x[j-1]);

          for(int k=0;k<len;k++)
          {
                if(search(t->root,charTOstr(x[j-1][k])))
                {
                    y[i-1]=concat(y[i-1],fTOstr(search_val(t->root,charTOstr(x[j-1][k]))));
                    flag=1;
                   continue;
                }
              else if(!search(t->root,charTOstr(x[j-1][k]))&&(notAlpha((x[j-1][k])) || isoperator(x[j-1][k])))
                {
                    y[i-1]=concat(y[i-1],charTOstr(x[j-1][k]));
                    flag=1;
                    continue;
                }
                else  /*to handle case of variables in the infix exp. that not predefined*/
                {
                   puts("-------------------");
                   printf("ERROR!!!\nstatement (%d) is invalid.\a\n",i+1);
                   puts("-------------------");
                   flag=0;
                  break;
                }
          }
           infixToPostfix(y[i-1],postfixExpr);
           float result=evaluatePostfix(postfixExpr);
           t->root=insert(t->root,x[j-2],result);
                arr[i]=search_node(t->root,x[j-2]);   /*insert same node in the array for heap sorting*/
        }

    else  /*variable is already exist and need to be updated*/
    {
               y[i-1]="";
          int len=strlen(x[j-1]);

          for(int w=0;w<len;w++)
          {
                if(search(t->root,charTOstr(x[j-1][w])))
                {
                    y[i-1]=concat(y[i-1],fTOstr(search_val(t->root,charTOstr(x[j-1][w]))));
                    flag=1;
                   continue;
                }
              else
                {
                    y[i-1]=concat(y[i-1],charTOstr(x[j-1][w]));
                    flag=1;
                    continue;
                }
           }
            infixToPostfix(y[i-1],postfixExpr);
            float result=evaluatePostfix(postfixExpr);
            update(t->root,x[j-2],result);            /*update value of the preexist variable instead of inserting*/
            arr[i]=search_node(t->root,x[j-2]);
     }
  }
         if (flag==1)
         {
        printf("1)sorted output using BST INorder traverse:\n\n");
        INorderTraverse(t->root);
        /*to delete any repeated element as in case of (updating a predefined variable)*/
        /*it's only print the last value for the node */
        int n=del_dup(arr,sizeofFile(name));
        heapSort(arr,n);
        printf("\n2)sorted output using heap sort:\n\n");
         printArray(arr,n);
         }
   }
}
int main()
{
   char filename[101];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");

    while(fgets(filename,100,stdin)!=NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
             interpret(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("\nEnter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }
    return 0;
}
