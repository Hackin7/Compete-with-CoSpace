
/*
class FindZone:public FindNode{
    private:
        int val = 4;
        Map *currlocation;
        ZoneNodes *zn;
    public:
        FindZone(Map *c,ZoneNodes *zz, int v){
            val = v;
            currlocation = c;
            zn=zz;
        };
         virtual bool operator() (int x, int y){
             coordinates n = createCoordinates(x,y);
             bool condition = currlocation->getPixel(x,y) == val && !zn->seenZone(n);
             return condition;
        };
};
//void moveDeposit(Map *currentlocation){moveZone(currlocation->deposit);}
*/


int numberOfZones = 6;
int zones[][3] =  {
    {321, 67, 0},
    {321, 207, 0},
    {257, 245, 1},
    {45, 146, 0},
    {130, 80, 2},
    {218, 106, 0}
};
int zoneNo = 0;
Timer Timing;
bool cycle(bool blue, bool red, bool black){
    printf("ZoneNo %d\n", zoneNo);
    bool bypass = (!blue && zones[zoneNo][2] == 0)
                    || (!red && zones[zoneNo][2] == 1);
                    //|| (black && zones[zoneNo][2] == 2);
    if (Timing.timeout(30) || bypass){
        Timing.reset();
        zoneNo++;
        if (zoneNo>=numberOfZones){zoneNo=0;}
    }
    int x=zones[zoneNo][0]; int y=zones[zoneNo][1];
    if (reached(x,y, 20, 20)){
        int choice = rand() % 2;
            //printf("Choice: %d\n",choice);
            switch(choice){
                case 0:WheelLeft=3;WheelRight=3;break;
                case 1:WheelLeft=3;WheelRight=4;break;
                case 2:WheelLeft=4;WheelRight=3;break;
                case 3:WheelLeft=2;WheelRight=4;break;
                case 4:WheelLeft=4;WheelRight=2;break;
                case 5:WheelLeft=-3;WheelRight=3;break;
                case 6:WheelLeft=3;WheelRight=-3;break;
                //default:WheelLeft=3;WheelRight=3;break;
            }
        return true;
    }
    else{
        moveAStar(&mapping, &location, x, y);
        return true;
    }
    return false;
}
///////////////////////////////////////////////////////////////////////
ofstream outfile;
ofstream mapFile;
ofstream pathFile;

void boxOut(int box, int x, int y){
    for(int j=max(0,x-box);j<x;j++){
        for(int k=max(0,y-box);k<y;k++){
            pathFile<<j<<" "<<k<<"\n";//count++;
    }}
}

static void Game1(){
    PositionX1 = PositionX;PositionY1 = PositionY;
    posInfoLost();
    colorSensorX = PositionX1+(int)round(cos((Compass+90.0)*PI/180)*5);
	colorSensorY = PositionY1+(int)round(sin((Compass+90.0)*PI/180)*5);
	if (PositionX1 == 0 || PositionY1 == 0){PositionX1=tx;PositionY1=ty;}
    //cout<<"X:"<<PositionX1<<" Y:"<<PositionY1<<" TX:"<<tx<<" TY:"<<ty<<endl;

    if (Duration){ //>0
		Duration--;
		return;
	}

	///File IO/////////////////////////////////////////////////////////////

    if (!mapFile.is_open()){
        mapFile.open("map.txt", ios::out | ios::trunc); //Check the Robotics Dev Studio Folder
    }else{
        ///Map
        for (int i=width-1;i>=0;i--){
            //if (i!=0){
            mapFile<<endl;//}
            for (int j=0;j<height;j++){
                //if (j!=0)
                mapFile<<" ";
                mapFile<<location.getPixel(i,j);
            }
        }
        mapFile.flush();
        mapFile.seekp(0, ios::beg);
    }
    if (!pathFile.is_open()){
        pathFile.open("path.txt"); //Check the Robotics Dev Studio Folder
    }else{
        for (auto i:mapping.path){
            //boxOut(5,i.pos[0],i.pos[1]);
            pathFile<<i.pos[0]<<" "<<i.pos[1]<<endl;
        }
        //outfile<<data;
        pathFile.flush();
        pathFile.seekp(0, ios::beg);
    }

    /////////////////////////////////////////////////////////////////////////

    bool collectBlue = w2Obj.LoadedObjects<6 && (w2Obj.LoadedBlue + w2Obj.LoadedSuperObj + w2Obj.noSuperObj)<2;//true;
	bool collectRed = w2Obj.LoadedObjects<6 && w2Obj.LoadedRed<2;//true;
	bool collectBlack = w2Obj.LoadedObjects<6 && w2Obj.LoadedBlack<2;//true;
	bool deposit = w2Obj.LoadedObjects>=3 ||  w2Obj.LoadedSuperObj > 0;//true;
	bool avoid = w2Obj.LoadedObjects>=2|| w2Obj.LoadedSuperObj > 0;//true;

	if (w2Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	//else if (colorCheck(w2Obj.slowarea,20) && Time>60){WheelLeft=-3;WheelRight=-4;Duration=2;}
    //else if ( US_Front < 15){WheelLeft=-2;WheelRight=-3;Duration=5;} //iMPROVE wORLD 2 Wall Avoiding
    else if (boundary(12)){}
	else if ( US_Front < 9){
        WheelLeft=-2;WheelRight=-2;//Duration=2;
    }
    else if (superObjAStar()){return;}
    else if (w2Obj.LoadedObjects >=6 || (Time > 420 && (w2Obj.LoadedObjects >=3 ||w2Obj.LoadedSuperObj>0))){
        printf("D");//moveDeposit(&location);
        moveAStar(&mapping, &location, 174,190);
    }
    else{
        cycle(collectBlue, collectRed, collectBlack);//moveAStar(&mapping, &location, 174,190);
    }
}
