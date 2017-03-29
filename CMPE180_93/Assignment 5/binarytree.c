# include <iostream>
# include <cstdlib>
# include <unistd.h>
# include <time.h>

using namespace std;

int t1,t2,t;

struct Stack
	  {
    	  	int size;
    		int top;
    		struct node* *array;
	  };

struct Stack* createStack(int size)
	  {
    	  	struct Stack* stack =
          	(struct Stack*) malloc(sizeof(struct Stack));
          	stack->size = size;
    		stack->top = -1;
    		stack->array =(struct node**) malloc(stack->size * sizeof(struct node*));
    		return stack;
	  };


struct node
    {
        int data;
        struct node *left;
        struct node *right;

    }*root;


   /** Function Declaration  **/

	    int count;
	    int count2;		

     	    void find(int, node **, node **);     
            void insert(node *tree , node *newnode);
            void del(int);
            void case_a(node *,node *);
            void case_b(node *,node *);
            void case_c(node *,node *);
            void preorder(node *);
            void inorder(node *);
            void postorder(node *);
            void display(node *, int);
	    void sort(node *ptr);
	    void generic(node* tree, int number);
 	    int leaves(node* root);
	    void InorderNonrecursive(node *root);
	    void PreorderNonRecursive(node* root);
	    void postorderNonRecursive(node* root);
	    node* copytree(node *);
	    node *balance(node *temp);
	    node *rr_rotation(node *parent);
 	    node *ll_rotation(node *parent);
	    node *lr_rotation(node *parent);
	    node *rl_rotation(node *parent);
	    int size(node *);
	    int Height(node *tree);
	    int diff(node *temp);
            bool search(node *tree);


    /** Class Declaration **/

    class BST

    {
	public:

            void find(int, node **, node **);    
            void insert(node *tree , node *newnode);
            void del(int);
            void case_a(node *,node *);
            void case_b(node *,node *);
            void case_c(node *,node *);
            void preorder(node *);
            void inorder(node *);
            void postorder(node *);
            void display(node *, int);
	    void sort(node *ptr);
	    void InorderNonrecursive(node *root);
	    void PreorderNonRecursive(node* root);
            void postorderNonRecursive(node* root);
	    void generic(node* tree, int number);
            node *balance(node *temp);
	    node *rr_rotation(node *parent);
 	    node *ll_rotation(node *parent);
	    node *lr_rotation(node *parent);
	    node *rl_rotation(node *parent);
	    node* copytree(node *);
	    int size(node *);
	    int Height(node *tree);
 	    int diff(node *temp);
	    int leaves(node* root);
	    bool search(node *tree);
            BST()
            {
                root = NULL;
            }
    };

    /** Main Function **/

    int main()

    {
        int choice, num;
        BST bst;
        node *temp;
        while (1)

        {
            cout<<"                 "<<endl;
            cout<<"Operations on BST"<<endl;
            cout<<"                 "<<endl;
            cout<<"1.Insert Element "<<endl;
            cout<<"2.Delete Element "<<endl;
            cout<<"3.Inorder Traversal"<<endl;
            cout<<"4.Preorder Traversal"<<endl;
            cout<<"5.Postorder Traversal"<<endl;
            cout<<"6.Display"<<endl;
            cout<<"7.Search"<<endl;
	    cout<<"8.Count Nodes"<<endl;
	    cout<<"9.Copy the tree"<<endl;         
	    cout<<"10.Height of tree"<<endl;
	    cout<<"11.Inorder traversal of tree without using recursion"<<endl;
	    cout<<"12.Preorder traversal of tree without using recursion"<<endl;
	    cout<<"13.Postorder traversal of tree without using recursion"<<endl;
	    cout<<"14.Count the number of leaves"<<endl;
	    cout<<"15.Balance the tree"<<endl;
	    cout<<"16.Display Sorted Tree"<<endl;
	    cout<<"17.Quit"<<endl;
	    cout<<"                 "<<endl;
            cout<<"Enter your choice : ";

            cin>>choice;

            switch(choice)

            {

            case 1:

                temp = new node;
                cout<<"Enter the number to be inserted : "<<endl;
    	        cin>>temp->data;
                bst.insert(root, temp);
      		break;

            case 2:

                if (root == NULL)
                {
                    cout<<"Tree is already empty."<<endl;
                    continue;
                }

                cout<<"Enter the number to be deleted : ";
                cin>>num;
		bst.del(num);
                break;

            case 3:

                cout<<"Inorder Traversal of BST:"<<endl;
		double duration3;
                t1=clock();
                bst.inorder(root);
	 	t2=clock();
                t=t2-t1;
                duration3=((float)t/CLOCKS_PER_SEC)*1000;
                cout<<"Execution time in milliseconds: "<<duration3<<endl;
		cout<<endl;
                break;

    	    case 4:

                cout<<"Preorder Traversal of BST:"<<endl;
	        double duration4;
                t1=clock();
		bst.preorder(root);
	        t2=clock();
                t=t2-t1;
                duration4=((float)t/CLOCKS_PER_SEC)*1000;
                cout<<"Execution time in milliseconds: "<<duration4<<endl; 
		cout<<endl;

                break;

            case 5:

                cout<<"Postorder Traversal of BST:"<<endl;
	        double duration5;
                t1=clock();
		bst.postorder(root);
	        t2=clock();
                t=t2-t1;
                duration5=((float)t/CLOCKS_PER_SEC)*1000;
                cout<<"Execution time in milliseconds: "<<duration5<<endl; 
		cout<<endl;

                break;

            case 6:

                cout<<"Display BST:"<<endl;
		bst.display(root,1);
		cout<<endl;

                break;

 	    
	    case 7:
		
		bool b ;
		b = false;
		double duration7;
                t1=clock();
                b = bst.search(root);
	        t2=clock();
                t=t2-t1;
                duration7=((float)t/CLOCKS_PER_SEC)*1000;
                cout<<"Execution time in milliseconds: "<<duration7<<endl; 
		if (b == true)
		{
			cout<<"Element is already present in the tree"<<endl;
		}
		else
		{
			cout<<"Element is not present"<<endl;
		}	
		cout<<endl;

                break;
	   
	    case 8:
		
		int a;
                a = bst.size(root);
		cout<<"Number of nodes in tree = "<<a<<endl;
                cout<<endl;

                break;
	   
	     case 9:

                cout<<"Copy the tree"<<endl;
		bst.copytree(root);
		cout<<endl;

                break;

	    case 10:
		
	       int ht;
               ht  = bst.Height(root);
               cout<<"Height of the tree is: "<<ht<<endl;
		
		break;

	    case 11:
		
		 cout<<"Inorder traversal of tree without using recursion "<<endl;
                 double duration11;
                 t1=clock();
		 InorderNonrecursive(root);
                 t2=clock();
                 t=t2-t1;
                 duration11=((float)t/CLOCKS_PER_SEC)*1000;
                 cout<<"Execution time in milliseconds: "<<duration11<<endl;
	         break;
	    
	    case 12:
		
		 cout<<"Preorder traversal of tree without using recursion "<<endl;
	         double duration12;
                 t1=clock();
		 PreorderNonRecursive(root);
                 t2=clock();
	         t=t2-t1;
                 duration12=((float)t/CLOCKS_PER_SEC)*1000;
                 cout<<"Execution time in milliseconds: "<<duration12<<endl;
	         break;  

	    case 13:
		
		 cout<<"Postrder traversal of tree without using recursion "<<endl;
                 double duration13;
                 t1=clock();
		 postorderNonRecursive(root);
                 t2=clock();
	         t=t2-t1;
                 duration13=((float)t/CLOCKS_PER_SEC)*1000;
                 cout<<"Execution time in milliseconds: "<<duration13<<endl;
	         break; 
	
	    case 14:
 	 	
		int o;
                o = bst.leaves(root);
		cout<<"Number of leaf nodes in tree = "<<o<<endl;
                cout<<endl;

                break;
	
	    case 15:

	     if (root == NULL)

            {
		cout<<"Tree is Empty"<<endl;
		continue;

            }

            	cout<<"Balanced Tree:"<<endl;
	    	double duration15;
            	t1=clock();
	    	bst.display(root, 1);
 	   	t2=clock();
            	t=t2-t1;
            	duration15=((float)t/CLOCKS_PER_SEC)*1000;
            	cout<<"Execution time in milliseconds: "<<duration15<<endl;
	    	cout<<endl;
            	break; 
	
	    case 16:
	    	
	    	cout<<"Sorted BST:"<<endl;
		double duration16;
                t1=clock();
                bst.sort(root);
	 	t2=clock();
                t=t2-t1;
                duration16=((float)t/CLOCKS_PER_SEC)*1000;
                cout<<"Execution time in milliseconds: "<<duration16<<endl;
		cout<<endl;
                break;
	                     
            
	    case 17:
                
		exit(1);

            default:

                cout<<"Wrong choice"<<endl;
            }
        }
    }

  /* Additional find function **/   

    void BST::find(int item, node **par, node **loc)

    {

        node *ptr, *ptrsave;
        if (root == NULL)
        {
            *loc = NULL;
            *par = NULL;
            return;
        }

        if (item == root->data)
        {
            *loc = root;
            *par = NULL;
            return;
        }

        if (item < root->data)
            ptr = root->left;
        else
            ptr = root->right;
        ptrsave = root;
        while (ptr != NULL)
        {
            if (item == ptr->data)
            {
                *loc = ptr;
                *par = ptrsave;
                return;
            }

            ptrsave = ptr;
            if (item < ptr->data)
                ptr = ptr->left;
    	else
    	    ptr = ptr->right;
        }
        *loc = NULL;
        *par = ptrsave;
    }

    /** Insert **/

    void BST::insert(node *tree, node *newnode)

    {
        if (root == NULL)
        {
            root = new node;
            root->data = newnode->data;
            root->left = NULL;
            root->right = NULL;
            cout<<"Root Node is Added"<<endl;
            return;

        }

        if (tree->data == newnode->data)
        {
            cout<<"Element already in the tree"<<endl;
            return;
        }
        if (tree->data > newnode->data)
        {
            if (tree->left != NULL)
            {
                insert(tree->left, newnode);	
    	}
    	else
    	{
                tree->left = newnode;
                (tree->left)->left = NULL;
                (tree->left)->right = NULL;
                cout<<"Node Added To Left"<<endl;
                return;
            }
        }
        else
        {
            if (tree->right != NULL)
            {
                insert(tree->right, newnode);
            }
            else
            {
                tree->right = newnode;
                (tree->right)->left = NULL;
                (tree->right)->right = NULL;
                cout<<"Node Added To Right"<<endl;
                return;
            }	
        }
    }

    /** Delete **/

    void BST::del(int item)
    {
        node *parent, *location;
        if (root == NULL)
        {
            cout<<"Tree is empty"<<endl;
            return;
        }
        find(item, &parent, &location);
        if (location == NULL)
        {
            cout<<"Item not present in tree"<<endl;
            return;
        }
        if (location->left == NULL && location->right == NULL)
            case_a(parent, location);
        if (location->left != NULL && location->right == NULL)
            case_b(parent, location);
        if (location->left == NULL && location->right != NULL)
            case_b(parent, location);
        if (location->left != NULL && location->right != NULL)
            case_c(parent, location);
        free(location);
    }
    
    /** Case A **/

    void BST::case_a(node *par, node *loc )
    {
        if (par == NULL)
        {
            root = NULL;
        }
        else
        {
            if (loc == par->left)
                par->left = NULL;
            else
                par->right = NULL;
        }
    }
     

    /** Case B **/

    void BST::case_b(node *par, node *loc)

    {
        node *child;
        if (loc->left != NULL)
            child = loc->left;
        else
            child = loc->right;
        if (par == NULL)
        {
            root = child;
        }
        else
        {
            if (loc == par->left)
                par->left = child;
            else
                par->right = child;
        }
    }
     

    /** Case C **/

    void BST::case_c(node *par, node *loc)

    {
        node *ptr, *ptrsave, *suc, *parsuc;
        ptrsave = loc;
        ptr = loc->right;
        while (ptr->left != NULL)
      {
            ptrsave = ptr;
            ptr = ptr->left;
        }
        suc = ptr;
       parsuc = ptrsave;
        if (suc->left == NULL && suc->right == NULL)
            case_a(parsuc, suc);
        else
            case_b(parsuc, suc);
        if (par == NULL)
        {
            root = suc;
        }
        else
       {
            if (loc == par->left)
               par->left = suc;
            else
                par->right = suc;
        }
       suc->left = loc->left;
       suc->right = loc->right;
    }

     /** Search **/

	bool BST::search(node *tree)
	{	
   		if (root == NULL)
        {
            cout<<"Tree is empty"<<endl;
            return 0;
        }
	cout<<"Enter the element to be searched"<<endl;		
		int num;		
		cin>>num;                
   node *temp=tree;

   while(temp!=NULL)
   {
      if(temp->data==num)         
	break;
      if(num>temp->data)         
	temp=temp->right;
      if(num<temp->data)
	temp=temp->left;
   }

   if(temp==NULL)      
      return false;
      else if(temp->data==num)      
      return true;   
}    

    /** Pre Order Traversal **/

    void BST::preorder(node *ptr)

    {

        if (root == NULL)

        {
          cout<<"Tree is empty"<<endl;

            return;

        }

        if (ptr != NULL)

        {

            cout<<ptr->data<<"  ";

            preorder(ptr->left);

            preorder(ptr->right);

        }

    }

    /** Counter **/
	

int BST::size(node *n) 
{

if (root == NULL)
        {
            cout<<"Tree is empty"<<endl;
            return 0;
        }
    if(!n)         
	return 0;
     else
	return size(n->left) + 1 + size(n->right); 
}
    
    /** In Order Traversal **/

   void BST::inorder(node *ptr)

    {

        if (root == NULL)

        {

            cout<<"Tree is empty"<<endl;

            return;

        }

        if (ptr != NULL)

        {

            inorder(ptr->left);

            cout<<ptr->data<<"  ";

            inorder(ptr->right);

        }

    }

     

    /** Postorder Traversal **/

    void BST::postorder(node *ptr)

    {

        if (root == NULL)

        {

            cout<<"Tree is empty"<<endl;

            return;

        }

        if (ptr != NULL)

        {

            postorder(ptr->left);

            postorder(ptr->right);

            cout<<ptr->data<<"  ";

        }

    }

    
    /** Copy the tree **/
       
     node* BST::copytree(node *root)
{
    if (root == NULL)
        {
            cout<<"Tree is empty"<<endl;
            return 0;
        }
    node* copyNode = NULL;
    if (root)
    {
	copyNode = root;
     /*   copyNode = new node();
        copyNode->data = root->data;
        copyNode->left = copytree(root->left);
        copyNode->right = copytree(root->right);
	*/
	inorder(copyNode);
    }

    return copyNode;
}
     
	/** Height **/

    int BST::Height(node *tree)
	{
   		 if (tree==NULL) 
        	 return 0;
        
   else
   {
       
       int lDepth = Height(tree->left);
       int rDepth = Height(tree->right);
 
       
       if (lDepth > rDepth) 
           return(lDepth+1);
       else 
	return(rDepth+1);
   }
	}


        /*****Height Difference*****/

int BST::diff(node *temp)

{

    int lHeight = Height (temp->left);

    int rHeight = Height (temp->right);

    int b_factor= lHeight - rHeight;

    return b_factor;
}


 /***Sorted Tree***/

 void BST::sort(node *ptr)

    {

        if (root == NULL)

        {

            cout<<"Tree is empty"<<endl;

            return;

        }

        if (ptr != NULL)

        {

            sort(ptr->left);

            cout<<ptr->data<<"  ";

            sort(ptr->right);

        }

    }

     

/** Inorder without recursion **/

void InorderNonrecursive(struct node *root)
{ 
  if (root == NULL)

        {
          cout<<"Tree is empty"<<endl;
	  return;

        }



  sleep(10);
  struct node *current,*pre;
 
  if(root == NULL)
     return; 
 
  current = root ;
  while(current != NULL)
  {                 
    if(current->left == NULL)
    {
      cout<<current->data<<endl;
      current = current->right;      
    }    
    else
    {
      
      pre = current->left;
      while(pre->right != NULL && pre->right != current)
        pre = pre->right;
 
      
      if(pre->right == NULL)
      {
        pre->right = current;
        current = current->left;
      }
             
        
      else 
      {
        pre->right = NULL;
        cout<<current->data<<endl;
        current = current->right;      
      } 
    } 
  } 
}


/** Preorder without recursion **/

void PreorderNonRecursive(node* root)
{

   if (root == NULL)

        {
          cout<<"Tree is empty"<<endl;
	  return;

        }

    while (root)
    {
        
        if (root->left == NULL)
        {
            cout<<root->data<<endl;
            root = root->right;
        }
        else
        {
            
            struct node* current = root->left;
            while (current->right && current->right != root)
                current = current->right;
 
            
            if (current->right == root)
            {
                current->right = NULL;
                root = root->right;
            }
 
            
            else
            {
                cout<<root->data<<endl;
                current->right = root;
                root = root->left;
            }
        }
    }
}



int isFull(struct Stack* stack)
{  return stack->top - 1 == stack->size; }
 
int isEmpty(struct Stack* stack)
{  return stack->top == -1;  }
 
void push(struct Stack* stack, struct node* root)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = root;
}
struct node* pop(struct Stack* stack)
{
    	  	if (isEmpty(stack))
          	return NULL;
         	return stack->array[stack->top--];
};



/** Postorder without Recursion **/


void postorderNonRecursive(struct node* root)
{
   if (root == NULL)

        {
          cout<<"Tree is empty"<<endl;
	  return;

        }
 
    struct Stack* s1 = createStack(100);
    struct Stack* s2 = createStack(100);
 
    
    push(s1, root);
 
 
    
    while (!isEmpty(s1))
    {
       
        root = pop(s1);
        push(s2, root);
 
        
        if (root->left)
            push(s1, root->left);
        if (root->right)
            push(s1, root->right);
    }
 
    
    while (!isEmpty(s2))
    {
        root = pop(s2);
        cout<<root->data<<endl;
    }
}



	void Sort(node *root)
          {

	       if(root!=NULL)
               {
                      
               
			Sort(root->left);                         
                        Sort(root->right);
                        cout<<root->data<<",";
                   
            
               }

                 else
               {

               		//cout<<"Tree is empty"<<endl;		      


               } 
          }
     

    /** Count number of leaves **/

int BST::leaves(node* root)
{
  if(root == NULL)       
    return 0;
  if(root->left == NULL && root->right==NULL)      
    return 1;            
  else
    return leaves(root->left) + leaves(root->right);      
}


/*******Balance the Tree*******/

node *BST::rr_rotation(node *parent)

{

    node *temp;

    temp = parent->right;

    parent->right = temp->left;

    temp->left = parent;

    return temp;

}

node *BST::ll_rotation(node *parent)

{

    node *temp;

    temp = parent->left;

    parent->left = temp->right;

    temp->right = parent;

    return temp;

}

node *BST::lr_rotation(node *parent)

{

    node *temp;

    temp = parent->left;

    parent->left = rr_rotation (temp);

    return ll_rotation (parent);

}

node *BST::rl_rotation(node *parent)

{

    node *temp;

    temp = parent->right;

    parent->right = ll_rotation (temp);

    return rr_rotation (parent);

}

node *BST::balance(node *temp)

{
   
    int bal_factor = diff (temp);

    if (bal_factor > 1)

    {

        if (diff (temp->left) > 0)

            temp = ll_rotation (temp);

        else

            temp = lr_rotation (temp);

    }

    else if (bal_factor < -1)

    {

        if (diff (temp->right) > 0)

            temp = rl_rotation (temp);

        else

            temp = rr_rotation (temp);

    }

    return temp;

}

     



    /** Display Tree **/

    void BST::display(node *ptr, int level)

    {
	if (root == NULL)
        {
            cout<<"Tree is empty"<<endl;
            return;
        }

        int i;
        if (ptr != NULL)
        {
            display(ptr->right, level+1);
            cout<<endl;
            if (ptr == root)
                cout<<"Root->:  ";
            else
            {
                for (i = 0;i < level;i++)
                    cout<<"       ";
    	}
           cout<<ptr->data;
            display(ptr->left, level+1);
        }
    }

