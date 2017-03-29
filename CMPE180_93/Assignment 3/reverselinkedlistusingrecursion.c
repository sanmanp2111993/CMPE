    #include<iostream>
    using namespace std;
    struct node
    {
        int data;
        struct node *next;
    };
    void insert(struct node **head,int x)
    {
        struct node *newnode= new node[sizeof(node)];
        newnode->data = x;
        newnode->next = *head;
    	*head = newnode;
    }
    void display(struct node *head)
    {
        while(head!=0)
        {
            cout<<head->data<<"->";
            head=head->next;
        }
        cout<<endl;
    }
    struct node * reverse(struct node* newnode,struct node **head)
    {
        if(newnode->next==0)
        {
        	*head = newnode;
            return newnode;
        }
        else
        {
            struct node *prev = reverse(newnode->next,head);
    		prev -> next = newnode;
    		newnode -> next = 0;
            return newnode;
        }
    }
    int main()
    {
    	struct node *head = 0;
    	int n=10;
    	while(n!=0)
    	    insert(&head,n--);
    	    
        
        display(head);
        
        reverse(head,&head);
    	display(head);
        return 0;
    }
