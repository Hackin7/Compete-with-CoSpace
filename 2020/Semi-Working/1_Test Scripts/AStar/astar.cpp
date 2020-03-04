#include <bits/stdc++.h>
using namespace std;
#include "../../World1/w1map.hpp"
#include "../../World2/w2map.hpp"
#include "../../CoordinateSystem/location.hpp"
#include "../../Navigation/astar.hpp"

void outputMap(int map[width][height]){
    cout<<"Map\n";
    for (int i=0;i<width;i++){
        for (int j=0;j<height;j++){
            cout<<map[i][j];
        }
        cout<<endl;
    }
}
//AStar mapper;
Map location(layout);
AStar mapper(&location);

class CheckReached:public FindNode{
    private: int x1, y1;
public:
     CheckReached(int x, int y) {x1 = x; y1 = y;};
     virtual bool operator() (int x, int y){return (x == x1 && y == y1);};
};

int main() {
    srand(12345);

    int x1, y1, x2, y2;
    x1 = 305; y1 = 83; x2 = 35; y2 = 131;//305,83,35,131
    cin>>x1>>y1>>x2>>y2;

    FindNode* reached = new CheckReached(x2,y2);
    vector<coordinates> stuff = mapper.getPath(x1, y1, reached);

    int count = 0;
    for (int i=0; i<(int)stuff.size(); i++){
            for(int j=max(0,stuff[i].pos[0]-10);j<stuff[i].pos[0];j++){
                for(int k=max(0,stuff[i].pos[1]-10);k<stuff[i].pos[1];k++){
                    cout<<j<<" "<<k<<endl;count++;
                }}
        cout<<stuff[i].pos[0]<<" "<<stuff[i].pos[1]<<endl;
        count++;
    }
    cout<<count;//stuff.size();
}
