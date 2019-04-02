#include <iostream>
#include<fstream>
#include<limits>
#include<queue>
#include<vector>
using namespace std;
ifstream f("date.txt");

struct muchie
{   int owner;
    int vecin, cost;
};

void citire (vector<muchie> **ls_vecini, int &n, vector<int> *fortarete)
{
   int m,x,y,c,k,fort;
   muchie mc;
   f>>n>>m>>k;

   for(int i=0;i<k;i++)
    {
        f>>fort;
        (*fortarete).push_back(fort);
    }

   *ls_vecini=new vector<muchie>[n+1];
   for(int i=0;i<m;i++)
     {
       f>>x>>y>>c;
	   mc.vecin=y;
	   mc.cost=c;
       (*ls_vecini)[x].push_back(mc);
       mc.vecin=x;
	   mc.cost=c;
	   (*ls_vecini)[y].push_back(mc);
     }

}

void Dijkstra(vector<muchie> *ls_vecini,int *dist,int *viz,int Start,int n,int *owner)
{
  priority_queue<int> qu;

  (viz)[Start]=1;
  (dist)[Start]=0;
  qu.push(Start);
   owner[Start]=0;
  while(!qu.empty())
  {
    int nod=qu.top();
     qu.pop();

     for(unsigned i=0;i<ls_vecini[nod].size();i++)  /// .size returneaza un unsigned
     { int vecin= ls_vecini[nod][i].vecin;
       int cost=ls_vecini[nod][i].cost;

       if((dist)[nod]+cost <(dist)[vecin])
        {
           owner[ls_vecini[nod][i].vecin]=Start;
          (dist)[vecin]=(dist)[nod]+cost;
          if(!(viz)[vecin])
          {
           (viz)[vecin]=1;
           qu.push(vecin);
          }

        }

     }

  }

}

int main()
{
    int n,*viz, *dist, *owner;

    vector<int> fortarete;
    vector<muchie> *ls_vec;

    citire(&ls_vec,n,&fortarete);

    dist=new int[n+1];
    viz=new int[n+1];
    for(int i=1;i<=n;i++)
      (dist)[i]=INT_MAX;

    owner=new int[n+1];

    for(int i=1;i<=n;i++)
        owner[i]=0;
    for(unsigned int i=0;i<fortarete.size();i++)
       {
           for(int i=1;i<=n;i++)
              (viz)[i]=0;
           Dijkstra(ls_vec,dist,viz,fortarete[i],n, owner);
       }

     for(int i=1;i<=n;i++)
           cout<<owner[i]<<" ";

    return 0;
}
