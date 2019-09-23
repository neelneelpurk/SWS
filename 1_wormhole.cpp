#include<iostream>

using namespace std;

int adj[1001][1001];	//matrix representation of start and end node + entry and exit as vertices of the worm hole
int X[1001];			//x coordinate of all vertices of start and end node + entry and exit as vertices of the worm hole
int Y[1001];			//y coordinate of (same as above)
int W[5];			// time from one vertices to another.  This is comes as input for every given worm hole.
int V;              //total number of vertices include tart and end node + entry and exit as vertices of the worm hole
int visited[1001];	//visited the node or not
int key[1001];		//Key - maintain the minimum time to reach from SOURCE to other vertices.

int getMin()		//function to find the next available minimum travel time vertex.
{
	int min=100000;		//assume this is the max time - we call it infinity
	int min_vertex;		//next available vertex with minimum cost from the source.
	int i;

	for(i=1;i<=V;i++)
	{
		if(min>key[i] && visited[i]==0)
		{
			min = key[i];
			min_vertex = i;		//found the next available vertex with minimium cost and not visited as condition.
		}
	}
	return min_vertex;
}

int djikstra(){
    for(int i=1;i<=V;i++) key[i]=100000;    //infinity initialized as time from source to destination 
    key[1] = 0;  // time to traveql from source to itself is zero

    for(int i=1;i<=V;i++){
        int u = getMin();
		visited[u] = 1;
		for(int v=1;v<=V;v++)
		{
			if(!visited[v] && adj[u][v] && key[u]+adj[u][v] < key[v])
			    key[v] = key[u]+adj[u][v];			//adding the min time at the intermediate destination node from the source, which over write all infinite value with actuals.
		}
    }
    return key[2];  // key[2] is time for source to destination
}

int solveUtil(){
    for(int i=1;i<=V+1;i++)
	{
		for(int j=1;j<=V+1;j++)   //calculate the min time between any 2 vertex (populating our full graph)
		{
			adj[i][j] = (X[i]-X[j] > 0?X[i]-X[j] : X[j]-X[i]) + (Y[i]-Y[j] > 0?Y[i]-Y[j] : Y[j]-Y[i]);
			adj[j][i] = adj[i][j];
		}
	}
    int j=0;
    for(int i=3;i<V;){
        adj[i][i+1] = W[j];
        adj[i+1][i] = W[j++];
        i+=2;
    }
    return djikstra();
}

void reset(){
    for(int i=0;i<1001;i++) visited[i]=0;
}

int main(){
    int T,ans;
    cin>>T;
    for(int a0 = 0; a0 < T; a0 ++){
        reset(); // reseting the visited array
        int N;
        cin>>N; //N = number of wormholes
        int i=1;
        cin>>X[i]>>Y[i]>>X[i+1]>>Y[i+1];  //i=1 is source and //i=2 is destination
        i+=2;
        V= 2*N + 2; //total number of vertex
        for(int k=0;k<N;k++){
            cin>>X[i]>>Y[i]>>X[i+1]>>Y[i+1]>>W[k];
            i+=2;
        }
        int s_d_x = X[1]>X[2]?X[1]-X[2]:X[2]-X[1];
        int s_d_y = Y[1]>Y[2]?Y[1]-Y[2]:Y[2]-Y[1];
        int s_d = s_d_x + s_d_y;
        if(N==0) ans = s_d;
        else ans = solveUtil();
        cout<<"Test Case #"<<a0+1<<" ";
        cout<<ans<<endl;
    }
}