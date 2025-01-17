// File: Game1Dijkstra/zoneDijkstra.c
int zoneDijkstra(int *points, int no){
    int minDist = 2147483647;//INT MAX
    int endNode = points[0];
       for (int i=0;i<no;i++){
            int toGo = pythagoreanDistance(PositionX,PositionY,coordinates[points[i]][0],coordinates[points[i]][1]);
            //dijkstra(cost, coordinates, MAX, startNode,depositNodes[i]);
            if (toGo < minDist){
                minDist = toGo;
                endNode = points[i];
            }
            printf("%d %dNode dist:%d\n",i,points[i],toGo);
        }
        //endNode=13;
    startDijkstra(endNode);
        return endNode;
}

bool depositDijkstraStarted = false;
int prevDepositTime = 0;
int depositNode = 13;
bool depositDijkstra(bool start){
    if (start){
        if (!depositDijkstraStarted){
            depositNode = zoneDijkstra(depositNodes,DEPOSITNODES);
            depositDijkstraStarted=true;
        }
        printf("depositNode:%d\t",depositNode);
        moveDijkstra(coordinates[depositNode][0],coordinates[depositNode][1]);
        /*if (Time - prevDepositTime > 10){
            depositNode = zoneDijkstra(depositNodes,DEPOSITNODES);
            prevDepositTime = Time;
        }*/
    }
    else{depositDijkstraStarted = false;}
}
