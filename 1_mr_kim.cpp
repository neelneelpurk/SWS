#include<iostream>
//#define ABS(x) (x<0?(-1)*x)
//#define MIN(a,b) (a>b?b:a)
#define MAX 9999999

using namespace std;

int N;
int sx,sy;
int dx,dy;
int cusX[12],cusY[12];
int vis[12];
int ans;
int ABS(int aa)
{
	if(aa<0)
		return (-1)*aa;
	return aa;
}


void solve(int xx, int yy, int visited, int tot_cost, int idx){
    int cost = 0;
    if(idx!=-1) vis[idx]=1;
    if(visited==N){
        tot_cost += ABS(xx-dx) + ABS(yy-dy);
        ans = min(ans,tot_cost);
        return;
    }
    for(int i=0;i<N;i++){
        if(!vis[i]){
            cost = tot_cost + ABS(xx-cusX[i]) + ABS(yy-cusY[i]);
            solve(cusX[i],cusY[i],visited+1,cost,i);
            vis[i]=0;
        }
    }
    if(idx!=-1)
		vis[idx]=0;
}

int main(){
    int T;
    cin>>T;
    for(int t0=1;t0<=T;t0++){
        ans = MAX;
        cin>>N;
        cin>>sx>>sy;
        cin>>dx>>dy;
        for(int i=0;i<N;i++){
            vis[i]=0;
            cin>>cusX[i]>>cusY[i];
        }
        solve(sx,sy,0,0,-1);
        cout<<"Test case #"<<t0<<" "<<ans<<endl;
    }
}