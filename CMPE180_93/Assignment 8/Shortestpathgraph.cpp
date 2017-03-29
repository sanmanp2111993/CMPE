  #include <iostream>
  #include <stdio.h>
  #include <limits.h>
  #include <map>
  #include <vector>
  #include <string>
  #include <list>
  #include <functional>
  
  using namespace std;
  struct Vertex;
  struct Edge
  {
       Vertex *dest;
       double cost;
       Edge(Vertex *d=0,double c=0.0)
        : dest(d),cost(c){}
  };
  struct Vertex
  {

       string name;
       vector<Edge> adj;
       double dist;
       Vertex *prev;
       unsigned int scratch;
       Vertex(const string &character):name(character)
       {reset();}
       void reset()
       {
            dist=3000000;
            prev=0;
            scratch=0;
    }
  };

//Class Declaration
  class Graph
  {
       public:
          Graph(){};
         ~Graph();
         void addEdge(const string & source,const string & destination,double cost);
         void showPath(const string & destination) const;
         bool dag(const string & init);
         void printdag();
       

      private:
         Vertex * getVertex(const string & v_name);
         void showPath(const Vertex & dest) const;
         void clearAll();
         typedef map<string,Vertex *,less<string> > vmap;
         vmap vertexMap;
  };
  Graph::~Graph()
  {
       for(vmap::iterator itr=vertexMap.begin();itr!=vertexMap.end();++itr)
            delete (*itr).second;
  }
  Vertex * Graph::getVertex(const string & v_name)
  {
       vmap::iterator itr=vertexMap.find(v_name);
       if(itr==vertexMap.end())
       {
            Vertex *newv=new Vertex(v_name);
            vertexMap[v_name]=newv;
            return newv;
       }
       return (*itr).second;
  }
  void Graph::addEdge(const string & source,
            const string & destination,double cost)
  {
       Vertex *v=getVertex(source);
       Vertex *w=getVertex(destination);
       v->adj.push_back(Edge(w,cost));
  }

  void Graph::printdag()
  {
       for(vmap::iterator itr =vertexMap.begin();itr!=vertexMap.end();++itr)
        {
            cout<<(*itr).first;
            showPath((*itr).first);
        }
  }	
  void Graph::clearAll()
  {
       for(vmap::iterator itr=vertexMap.begin();itr!=vertexMap.end();++itr)
            (*itr).second->reset();
  }
  void Graph::showPath(const Vertex & dest) const
  {
       if(dest.prev!=0)
       {
            showPath(*dest.prev);
            cout<<"-->";
       }
       cout<<dest.name;
  }
  void Graph::showPath(const string &destination) const
  {
       vmap::const_iterator itr=vertexMap.find(destination);
       if(itr==vertexMap.end())
       {
            cout<<destination<<"is not present in graph"<<endl;
            return;
       }
       Vertex & w =*(*itr).second;
       if(w.dist==3000000)
            cout<<destination<<"cannot access"<<endl;
       else
       {
            cout<<"(Cost is: "<<w.dist<< ")";
            showPath(w);
       }
       cout<<endl;
  }
  
  bool Graph::dag(const string & init)
  {
       vmap::iterator itr=vertexMap.find(init);
       if(itr==vertexMap.end())
       {
            cout<<"Vertex not found"<<endl;
            return false;
    }
    clearAll();
    Vertex *start=(*itr).second;
    start->dist=0;
    list<Vertex *> q;
    for(itr=vertexMap.begin();itr!=vertexMap.end();++itr)  //Computation of Indegree of each vertices
    {                                                       
            Vertex *v =(*itr).second;                      
            for(unsigned int i=0;i<v->adj.size();i++)
            {
                 v->adj[i].dest->scratch++;
            }
       }
       for(itr=vertexMap.begin();itr!=vertexMap.end();++itr)
       {
            Vertex *v=(*itr).second;                 //Make a queue of vertices by pushing them
            if(v->scratch==0)
            {                                       //The vertices having 0 indegree pushed first
                 q.push_back(v);
            }
       }
       unsigned int y;
       for(y=0;!q.empty();y++)
       {
            Vertex *v=q.front();
            q.pop_front();
            for(unsigned int i =0;i<v->adj.size();i++)
            {
                 Edge e=v->adj[i];
                 Vertex *w=e.dest;
                 double cvw=e.cost;
                 if(--w->scratch==0)
                      q.push_back(w);
                 if(v->dist==3000000)
                      continue;
                 if(w->dist>v->dist+cvw)
                 {
                      w->dist=v->dist+cvw;
                      w->prev=v;
                 }
            }
       }
       if(y!=vertexMap.size())
            {
                 cout<<"Cycle is present in graph"<<endl;
                 return false;
            }
       else
              return true;
  }


  int main(int argc, char** argv)
  {
       Graph g;
       cout<<"Enter the Graph description in following pattern:->"<<endl;
       cout<<"SourceCity_Initials | DestinationCity_Initials | Cost"<<endl;
       //cout<<"Enter the detail"<<endl;
       int a,cost;
       a=1;
       string src,dest;
       while(a==1)
       {
        cin>>src>>dest>>cost;
        g.addEdge(src,dest,cost);
        cout<<"To Continue enter 1 or Enter 0 to stop: ";
	
        cin>>a;
    }
    cout<<"Enter the Source:";
    cin>>src;
    bool flag;
    flag=g.dag(src);
    if(flag==true)
    {
       cout<<"Shortest path to Distinct nodes are :-->"<<endl;
       g.printdag();
       return 0;
    }
    else
       return 0;
 }
