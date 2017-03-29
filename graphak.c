  #include <iostream>
  #include <stdio.h>
  #include <limits.h>
  #include <map>
  #include <vector>
  #include <string>
  #include <list>
  #include <functional>
  
  using namespace std;
  struct vert;
  struct Edge
  {
       vert *dest;
       double dist;
       Edge(vert *d=0,double c=0.0)
        : dest(d),dist(c){}
  };
  struct vert
  {

       string name;
       vector<Edge> adj;
       double dist;
       vert *prev;
       unsigned int scratch;
       vert(const string &character):name(character)
       {reset();}
       void reset()
       {
            dist=3000000;
            prev=0;
            scratch=0;
    }
  };

//Class Declaration
  class graph
  {
       public:
          graph(){};
         ~graph();
         void addlink(const string & source,const string & destination,double dist);
         void showPath(const string & destination) const;
         bool directacyclicgraph(const string & init);
         void printdag();
       

      private:
         vert * get_V(const string & v_name);
         void showPath(const vert & dest) const;
         void clearAll();
         typedef map<string,vert *,less<string> > vmap;
         vmap vert_map;
  };
  graph::~graph()
  {
       for(vmap::iterator itr=vert_map.begin();itr!=vert_map.end();++itr)
            delete (*itr).second;
  }
  vert * graph::get_V(const string & v_name)
  {
       vmap::iterator itr=vert_map.find(v_name);
       if(itr==vert_map.end())
       {
            vert *newv=new vert(v_name);
            vert_map[v_name]=newv;
            return newv;
       }
       return (*itr).second;
  }
  void graph::addlink(const string & source,
            const string & destination,double dist)
  {
       vert *v=get_V(source);
       vert *w=get_V(destination);
       v->adj.push_back(Edge(w,dist));
  }

  void graph::printdag()
  {
       for(vmap::iterator itr =vert_map.begin();itr!=vert_map.end();++itr)
        {
            cout<<(*itr).first;
            showPath((*itr).first);
        }
  }	
  void graph::clearAll()
  {
       for(vmap::iterator itr=vert_map.begin();itr!=vert_map.end();++itr)
            (*itr).second->reset();
  }
  void graph::showPath(const vert & dest) const
  {
       if(dest.prev!=0)
       {
            showPath(*dest.prev);
            cout<<"-->";
       }
       cout<<dest.name;
  }
  void graph::showPath(const string &destination) const
  {
       vmap::const_iterator itr=vert_map.find(destination);
       if(itr==vert_map.end())
       {
            cout<<destination<<"is not present in graph"<<endl;
            return;
       }
       vert & w =*(*itr).second;
       if(w.dist==3000000)
            cout<<destination<<"cannot access"<<endl;
       else
       {
            cout<<"(Distance is: "<<w.dist<< ")";
            showPath(w);
       }
       cout<<endl;
  }
  
  bool graph::directacyclicgraph(const string & init)
  {
       vmap::iterator itr=vert_map.find(init);
       if(itr==vert_map.end())
       {
            cout<<"Vertex not found"<<endl;
            return false;
    }
    clearAll();
    vert *start=(*itr).second;
    start->dist=0;
    list<vert *> q;
    for(itr=vert_map.begin();itr!=vert_map.end();++itr)  //Computation of Indegree of each vertices
    {                                                       
            vert *v =(*itr).second;                      
            for(unsigned int i=0;i<v->adj.size();i++)
            {
                 v->adj[i].dest->scratch++;
            }
       }
       for(itr=vert_map.begin();itr!=vert_map.end();++itr)
       {
            vert *v=(*itr).second;                 //Make a queue of vertices by pushing them
            if(v->scratch==0)
            {                                       //The vertices having 0 indegree pushed first
                 q.push_back(v);
            }
       }
       unsigned int y;
       for(y=0;!q.empty();y++)
       {
            vert *v=q.front();
            q.pop_front();
            for(unsigned int i =0;i<v->adj.size();i++)
            {
                 Edge e=v->adj[i];
                 vert *w=e.dest;
                 double cvw=e.dist;
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
       if(y!=vert_map.size())
            {
                 cout<<"Cycle is present in graph"<<endl;
                 return false;
            }
       else
              return true;
  }


  int main(int argc, char** argv)
  {
       graph g;
       cout<<"Enter the graph description in following pattern:->"<<endl;
       cout<<"SourceCity_Initials | DestinationCity_Initials | Distance"<<endl;
      
       int a,dist;
       a=1;
       string src,dest;
       while(a==1)
       {
        cin>>src>>dest>>dist;
        g.addlink(src,dest,dist);
        cout<<"To Continue enter 1 or Enter 0 to stop: ";
	
        cin>>a;
    }
    cout<<"Enter the Source:";
    cin>>src;
    bool flag;
    flag=g.directacyclicgraph(src);
    if(flag==true)
    {
       cout<<"Shortest path to Distinct nodes are :-->"<<endl;
       g.printdag();
       return 0;
    }
    else
       return 0;
 }
