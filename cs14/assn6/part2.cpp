#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <cstdlib>

using namespace std;

struct edge;

struct point{
    string name;
    vector<edge*> edges;
    int status; // 1-undiscovered, 2-discovered, 3-active, 4-complete
    
    point(string n):name(n), status(1){}
};

struct edge{
    string name;
    int cap;
    int flow;
    point *connect;
    point *from;
    
    edge(int f, point *c, point *fr):cap(f), connect(c), from(fr), flow(0){}
    
    int getSign(){
        if(from->name > connect->name)
            return -1;
        return 1;
    }
    
    //max flow that can be passed through an edge in a certain direction
    int weight(){
        if((getSign() == -1 && flow < 0) || (getSign() == 1 && flow > 0))
            return cap - abs(flow);
        return cap + abs(flow); 
    }
    
    void updateflow(int flowton){
        flow+= flowton*getSign();
        edge *ehold= getEdge();
        ehold->flow= flow;
    }
    
    edge* getEdge(){
        for(int i= 0; i < connect->edges.size(); ++i)
            if(connect->edges[i]->connect == from)
                return connect->edges[i];
        return NULL;
    }
};

struct equeue{
    vector<edge*> q;
    
    void push(edge *item){
        q.push_back(item);
    }
    
    edge* top(){
        int index= 0;
        for(int i= 1; i < q.size(); ++i)
            if(q[i]->weight() > q[index]->weight())
                index= i;
        return q[index];
    }
    
    void pop(){
        int index= 0;
        for(int i= 1; i < q.size(); ++i)
            if(q[i]->weight() > q[index]->weight())
                index= i;
        
        for(int i= index; i < q.size()-1; ++i)
            q[i]= q[i+1];
        
        q.pop_back();
    }
};

struct graph{
    point *source;
    point *sink;
    vector<point*> points;
    vector<vector<string> > paths;
    vector<int> maxflows;
    vector<string> mincut;
    
    //constructs graphs using info form input file passed in as string
    graph(string shold){
        ifstream ifile(shold.c_str());
        int inputCount, ihold; string shold2;
        getline(ifile, shold);
        istringstream counts(shold);
        
        counts >> inputCount; //for points
        for(int i= 0; i < inputCount; ++i){
            getline(ifile, shold);
            istringstream pointname(shold);
            pointname >> shold;
            
            point *phold= new point(shold);
            points.push_back(phold);
            
            //set sink or source accordingly
            if(pointname >> shold2){
                if(shold2=="sink")
                    sink= phold;
                if(shold2=="source")
                    source= phold;
            }
        }
        
        counts >> inputCount; //for edges
        for(int i= 0; i < inputCount; ++i){
            getline(ifile, shold);
            istringstream in(shold);
            in >> shold;    //name of the edge -- gets tossed
            in >> ihold;    //cap/initial flow
            in >> shold;    //point1
            in >> shold2;   //point2
            
            edge *ehold= new edge(ihold, getPoint(shold2), getPoint(shold));
            getPoint(shold)->edges.push_back(ehold);
            
            ehold= new edge(ihold, getPoint(shold), getPoint(shold2));
            getPoint(shold2)->edges.push_back(ehold);
        }
        
        maxFlow();
    }
    
    //returns a pointer to a point with the name passed in
    point* getPoint(string name){
        for(int i= 0; i < points.size(); ++i)
            if(name==points[i]->name)
                return points[i];
        return NULL;
    }
    
    //find teh max flow path
    void maxFlow(){
        // reset discovered status'
        for(int i= 0; i < points.size(); ++i)
            points[i]->status= 1;
        
        equeue que; vector<edge*> path; point *pcur= source; edge *ecur;
        
        //gets "tree"
        while(sink!=pcur){
            for(int i= 0; i < pcur->edges.size(); ++i){
                if(pcur->edges[i]->connect->status!=4 && pcur->edges[i]->weight()!=0){ //complete
                    pcur->edges[i]->connect->status= 2; //discovered
                    que.push(pcur->edges[i]);
                }
            }
            pcur->status= 4; //complete
            
            do{
                if(que.q.size()==0){
                    if(mincut.size()==0)
                        for(int i= 0; i < points.size(); ++i)
                            if(points[i]->status  == 4)
                                mincut.push_back(points[i]->name);
                    return;
                }
                
                ecur= que.top();
                pcur= ecur->connect;
                que.pop();
            } while(pcur->status == 4); //complete
            pcur->status= 3; //active
            path.push_back(ecur);
        }
        
        mapMeOut(path);
    }
    
    //cuts off branches that lead to nothing
    void mapMeOut(vector<edge*> &path){
        for(int i= 0; i < path.size()-1; ++i){
            bool found= false;
            for(int j= i+1; j < path.size(); ++j)
                if(path[i]->connect == path[j]->from){
                    found= true;
                    break;
                }
            
            if(!found){
                for(int k= i+1; k < path.size(); ++k)
                    path[k-1]= path[k];
                path.pop_back();
                i= -1;
            }
        }
        
        updatePath(path);
    }
    
    //update the edges with the path's info
    void updatePath(vector<edge*> &path){
        int maxflow= path[0]->weight();
        vector<string> vhold;
        
        vhold.push_back(path[0]->from->name);
        for(int i= 0; i < path.size(); ++i){
            if(path[i]->weight() < maxflow)
                maxflow= path[i]->weight();
            vhold.push_back(path[i]->connect->name);
        }
        
        paths.push_back(vhold);
        maxflows.push_back(maxflow);
        
        for(int i= 0; i < path.size(); ++i)
            path[i]->updateflow(maxflow); //write update flow
        
        maxFlow();
    }
    
    // runs maxflow again with new caps and finds max flow augmenting paths
    void finish(string shold){
        while(paths.size()>0){
            paths.pop_back();
            maxflows.pop_back();
        }
        
        for(int i= 0; i < points.size(); ++i){
            for(int j= 0; j < points[i]->edges.size(); ++j){
                points[i]->edges[j]->cap= abs(points[i]->edges[j]->flow);
                points[i]->edges[j]->flow= 0;
            }
        }
        
        maxFlow();
        
        outfileInfo(shold);
    }
    
    void outfileInfo(string shold){
        int maxx= 0; bool found; vector<string> vertices;
        ofstream ofile(shold.c_str());
        
        // Max flow obtained: 8
        for(int i= 0; i < maxflows.size(); i++)
            maxx+= maxflows[i];
        ofile << "Max flow obtained: " << maxx << endl;
        
        // Vertices in min cut: 1 2 3 4 5 6
        ofile << "Vertices in min cut:";
        for(int i= 0; i < mincut.size(); ++i){
            ofile << " " << mincut[i];
        }
        
        // Flow rate: 3 Path: 1 4 6 7
        for(int i= 0; i < paths.size(); ++i){
            ofile << "\nFlow rate: " << maxflows[i] << " Path:";
            for(int j= 0; j < paths[i].size(); ++j)
                ofile << " " << paths[i][j];
        }
        ofile << endl;
    }
};

int main(int argc, char *argv[]){
    string shold= argv[1];
    graph myGraph(shold);
    
    int ihold= shold.find(".");
    if(ihold != -1)
        shold= shold.substr(0,ihold);
    shold+= ".out";
    myGraph.finish(shold);
}
