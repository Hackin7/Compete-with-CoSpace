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

bool dijkstraStarted = false;
int prevDepositTime = 0;
int depositNode = 13;
void depositDijkstra(){
    if (LoadedObjects >= 4 || LoadedSuperObj > 0){
        if (!dijkstraStarted){
            depositNode = zoneDijkstra(depositNodes,DEPOSITNODES);
            dijkstraStarted=true;
        }
        printf("depositNode:%d\t",depositNode);
        moveDijkstra(coordinates[depositNode][0],coordinates[depositNode][1]);

        if (Time - prevDepositTime > 10){
            depositNode = zoneDijkstra(depositNodes,DEPOSITNODES);
            prevDepositTime = Time;
        }
    }
    else{
            dijkstraStarted = false;
        }
}

