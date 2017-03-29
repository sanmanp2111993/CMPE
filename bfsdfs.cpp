        #include <iostream>
	#include <string>
	#include <vector>
	#include <queue>
	#include <stack>
	#include <algorithm>
	
	using namespace std;
	
	class Node{
		char value;
		vector<Node> child_node;
	public:
		Node(char c){value = c;}
	
		void addChild(Node n){
			child_node.push_back(n);
			return;
		}
	
		void addChild(char n){
			Node foo(n);
			child_node.push_back(foo);
		}
	
		char getValue(){return value;}
		vector<Node> getChildren(){return child_node;}
		bool isLeaf(){return child_node.size()==0;}
		bool operator==(Node b){return b.value==value;}
	};
	
	
	void construct(Node *r)
	{
		string foo;
		cout<<"Enter child_node for "<< r->getValue() <<" (-1 for leaf)"<<endl;
		cin>>foo;
	
		if(foo == "-1")
			return;
		else{
			for(int i = 0; i < foo.length(); i++)
			{
				Node t(foo[i]);
				construct(&t);
				r->addChild(t);
			}
		}
	}

	string depthFirstSearch(Node root, Node goal)
	{
		std::stack<Node> Q;
		std::vector<Node> child_node;
		string path = "--> ";
	
		Q.push(root);
		
	
		while(!Q.empty())
		{
			Node t = Q.top();
			path += t.getValue();
			Q.pop();
			
			if(t == goal)
			{
			  return path;
			}
			child_node = t.getChildren();
			std::reverse(child_node.begin(),child_node.end());
	
			for (int i = 0; i < child_node.size(); ++i)
			{
			  Q.push(child_node[i]);
			  Q.push('-');
			}
		}
		return path;
	}
	
	string breadthFirstSearch(Node root, Node goal)
	{
		std::queue<Node> Q;
		std::vector<Node> child_node;
		string path = "--> ";
		Q.push(root);
		Q.push('-');
	
		while(!Q.empty())
		{
			Node t = Q.front();
			path += t.getValue();
	
			Q.pop();
	
			if(t == goal)
			{
				return path;
			}
			child_node = t.getChildren();
			for (int i = 0; i < child_node.size(); ++i)
			{
				Q.push(child_node[i]);
				Q.push('-');
			}
		
				
		}
		return path;
	}
	
	
	int main(int argc, char** args)
	{
		char r;
		cout<<"Enter root node"<<endl;
		cin>>r;
	
		Node root(r);
		construct(&root);
	
		cout<<"Enter Node to search for: ";
		cin>>r;
	
		cout<<endl;
	
		cout<<"BFS Traversal: "<<breadthFirstSearch(root, Node(' '))<<endl;
		cout<<"BFS Search Path: "<<breadthFirstSearch(root, Node(r))<<endl<<endl;
	
		cout<<"DFS Traversal: "<<depthFirstSearch(root, Node(' '))<<endl;
		cout<<"DFS Search Path: "<<depthFirstSearch(root, Node(r))<<endl;
	
		return 0;
	}
