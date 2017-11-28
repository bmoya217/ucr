#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

struct point;

struct edge{
    string name;
    int flow;
    point *connect;
    point *from;
};

struct equeue{
    vector<edge*> q;
    void push(edge *item){
        q.push_back(item);
    }
    edge* top(){
        int index= 0;
        for(int i= 1; i < q.size(); ++i)
            if(q[i]->flow > q[index]->flow)
                index= i;
        return q[index];
    }
    void pop(){
        int index= 0;
        for(int i= 1; i < q.size(); ++i)
            if(q[i]->flow > q[index]->flow)
                index= i;
        
        for(int i= index; i < q.size()-1; ++i)
            q[i]= q[i+1];
        
        q.pop_back();
    }
    int size(){
        return q.size();
    }
};

struct point{
    string name;
    vector<edge*> edges;
    int status; // 1-undiscovered, 2-discovered, 3-active, 4-complete
    
    void removeEdge(int index){
        point *phold= edges[index]->from;
        point *phold2= edges[index]->connect;
        
        for(int i= index; i < edges.size()-1; ++i)
            edges[i]= edges[i+1];
        edges.pop_back();
        
        for(int i= 0; i < phold2->edges.size(); ++i){
            if(phold2->edges[i]->connect==phold){
                for(int j= i; j < phold2->edges.size()-1; ++j)
                    phold2->edges[j]= phold2->edges[j+1];
                phold2->edges.pop_back();
                return;
            }
        }
    }
};

struct graph{
    point *source;
    point *sink;
    vector<point*> points;
    
    int find(string name){
        for(int i= 0; i < points.size(); ++i)
            if(name==points[i]->name)
                return i;
        return -1;
    }
    int find(vector<string> v, string findme){
        for(int i= 0; i < v.size(); ++i)
            if(v[i]==findme)
                return i;
        return -1;
    }
    
    graph(string shold){
        ifstream ifile(shold.c_str());
        int pointCount, edgeCount, ihold; string shold2, shold3;
        getline(ifile, shold);
        istringstream counts(shold);
        counts >> pointCount;
        counts >> edgeCount;
        
        //set up points vector
        for(int i= 0; i < pointCount; ++i){
            //get info for point
            getline(ifile, shold);
            istringstream pointname(shold);
            pointname >> shold;
            
            //add point to list of points
            point *phold= new point;
            phold->name= shold;
            points.push_back(phold);
            
            //set sink or source accordingly
            if(pointname >> shold2){
                if(shold2=="sink")
                    sink= phold;
                if(shold2=="source")
                    source= phold;
            }
        }
        
        //set up edges vectors -- for the points
        for(int i= 0; i < edgeCount; ++i){
            getline(ifile, shold);
            istringstream in(shold);
            in >> shold3;    //toss the name of the edge
            in >> ihold;    //flow
            in >> shold;    //point1
            in >> shold2;   //point2
            
            //add teh info to both points
            edge *ehold= new edge;
            ehold->flow= ihold;
            ehold->name= shold3;
            ehold->connect= points[find(shold2)];
            ehold->from= points[find(shold)];
            points[find(shold)]->edges.push_back(ehold);
            
            edge *ehold2= new edge;
            ehold2->flow= ihold;
            ehold2->name= shold3;
            ehold2->connect= points[find(shold)];
            ehold2->from= points[find(shold2)];
            points[find(shold2)]->edges.push_back(ehold2);
        }
        
        maxFlow();
    }
    
    bool proceed(){
        for(int i= 0; i < points.size(); ++i)
            if(points[i]->status != 4 && points[i] != sink)
                return true;
        return false;
    }
    
    void maxFlow(){
        int undiscovered= 1, discovered= 2, active= 3, complete= 4;
        equeue que; point *pcur= source; edge *ecur;
        vector<string> names; int maxflow= 2147483647; //max an int can hold
        vector<edge*> path;
        
        //gets roots
        while(sink!=pcur){
            for(int i= 0; i < pcur->edges.size(); ++i){
                if(pcur->edges[i]->connect->status!=complete){
                    pcur->edges[i]->connect->status= discovered;
                    que.push(pcur->edges[i]);
                }
            }
            pcur->status= complete;
            
            do{
                ecur= que.top();
                pcur= ecur->connect;
                que.pop();
            } while(pcur->status == complete);
            path.push_back(ecur);
        }
        
        mapMeOut(path);
    }
    
    void mapMeOut(vector<edge*> &path){
        bool found;
        for(int p= 0; p < points.size(); ++p){
            for(int e= 0; e < points[p]->edges.size(); ++e){
                found= false;
                for(int i= 0; i < path.size(); ++i){
                    if((points[p]->edges[e]==path[i]) || (points[p]->edges[e]->from==path[i]->connect && points[p]->edges[e]->connect==path[i]->from))
                        found= true;
                }
                if(found==false){
                    points[p]->removeEdge(e);
                }
            }
        }
        
        for(int i= 0; i < points.size(); ++i){
            if(points[i] != sink && points[i] != source){
                if(points[i]->edges.size() == 1){
                    points[i]->removeEdge(0);
                    i= -1;
                }
            }
        }
        
        route();
    }
    
    void route(){
        point *cur= source;
        string last= cur->name;
        int maxflow=cur->edges[0]->flow;
        
        cout << "(" << cur->name;
        while(cur!=sink){
            if(cur->edges[0]->connect->name != last){
                last= cur->name;
                if(cur->edges[0]->flow < maxflow)
                    maxflow= cur->edges[0]->flow;
                cur= cur->edges[0]->connect;
            }
            else{
                last= cur->name;
                if(cur->edges[0]->flow < maxflow)
                    maxflow= cur->edges[0]->flow;
                cur= cur->edges[1]->connect;
            }
            
            cout << ", " << cur->name;
        }
        cout << ")\nWith a maxflow of " << maxflow << endl;
    }
};

int main(int argc, char *argv[]){
    string shold= argv[1];
    graph myGraph(shold);
}