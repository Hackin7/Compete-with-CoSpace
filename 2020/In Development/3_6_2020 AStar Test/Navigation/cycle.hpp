Map location(layout);
AStar mapping(&location);
///Move to coordinates////////////////////////////////////////////
class CheckReached:public FindNode{
    private: int x1, y1;
public:
     CheckReached(int x, int y) {x1 = x; y1 = y;};
     virtual bool operator() (int x, int y){return (x == x1 && y == y1);};
};
void moveAStar(int x, int y){
    if(reached(x,y,10,10)){WheelLeft=0;WheelRight=0;return;}
	FindNode* go = new CheckReached(x,y);
	mapping.getPath(PositionX,PositionY,go);
	moveTo(&location,mapping.path,10);
}
///Move to zones////////////////////////////////////////////////
class Zoning{
private:
    //Strategy
	OneTime onetime;
	Timer nodeTime;

public:
    //Constructor
    Map *currlocation;
    ZoneNodes *zn;
    AStar *mapping;
    Zoning(Map *ll,ZoneNodes *zz,AStar *mp){
        currlocation=ll;zn=zz;mapping=mp;
        zn->zones();cout<<"ZoneNumber:"<<zn->zoneNumber<<endl;
    }

    //Random Point to Travel To
    coordinates point = createCoordinates(0,0);
    //AStar to
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

    void moveZone(int val){
        if (currlocation->getPixel(PositionX1,PositionY1) != val ){
            FindNode* go = new FindZone(currlocation,zn,val);
            mapping->path=mapping->getPath(PositionX1,PositionY1,go);
            moveTo(currlocation,mapping->path,1);
            if (!onetime.toRun()){onetime.reset();nodeTime.reset();}
        }//Random Points
        else{
            //WheelLeft=0;WheelRight=0;
            /*
            cout<<"ZoneSearch";
            if (reached(point.pos[0],point.pos[1],10,10) ||
                currlocation->getPixel(point.pos[0],point.pos[1])!=val ||
                (point.pos[0]==0&&point.pos[1]==0)
                ){
                coordinates newpoint = zn->randomNode(zn->getZoneNo(PositionX1,PositionY1));
                point.pos[0] = newpoint.pos[0];
                point.pos[1] = newpoint.pos[1];
                cout<<"Change Coordinates: ";showCoordinates(newpoint);
                WheelLeft=3;WheelRight=3; Duration=1;return;
            }
            moveAStar(point.pos[0],point.pos[1]);
            */
            int choice = random(1);//7);
            cout<<"Choice:" <<choice<<endl;
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
            //Duration=2;
            //WheelLeft=4;WheelRight=3;
        }
    }
    void moveRed(){moveZone(currlocation->red);}
    void moveBlue(){moveZone(currlocation->blue);}
    void moveBlack(){moveZone(currlocation->black);}
    void moveDeposit(){moveZone(currlocation->deposit);}

};

////////////////////////
class Cycle:public Zoning{
private:
    Timer Timing;
    bool cycle[3] = {false, false, false};

    bool cycleFull(){
        for (int i=0; i<3; i++){
            if (!cycle[i])return false;
        }
        return true;
    }
    void cycleReset(){
        for (int i=0; i<3; i++){
            cycle[i] = false;
        }
    }
    int AppropriateZone(){
        //Reset
        if (cycleFull()){
            cycleReset();
        }

        moveRed();
        int redPath = (int)mapping->path.size();
        moveBlue();
        int bluePath = (int)mapping->path.size();
        moveBlack();
        int blackPath = (int)mapping->path.size();

        int zone = 2;//Black
        int minPath = blackPath;
        if ( (bluePath <= minPath && !cycle[1]) || cycle[2]){minPath = bluePath;zone = 1;}//Blue
        if ( (redPath <= minPath && !cycle[0]) ){minPath = redPath;zone = 0;}//Red
        return zone;
    }

    int timeToCollect = 15;//20;
    int consecutive = 0;
    int additionalTime = 10;

public:
    int zoneToCollect = -1;
    //int currZoneNo = 0;
    Cycle(Map *ll,ZoneNodes *zz,AStar* mp):Zoning(ll,zz,mp){}

    void changeZone(){
        zoneToCollect = AppropriateZone();
        consecutive = 0;
        Timing.reset();
    }

    int prevZone = -1;
    void collectObjects(bool red, bool blue, bool black){
        //cout<<red<<","<<blue<<","<<black<<endl;
        //z.currZoneNo=max(z.currZoneNo,z.getZoneNo(PositionX1,PositionY1));
        if (red&&blue&&black){zoneToCollect = 4;}
        else if (blue&&black){zoneToCollect=0;}
        else if (red&&black){zoneToCollect=1;}
        else if (red&&blue){zoneToCollect=2;}

        if (Time>465 && w2Obj.LoadedObjects>0){cout<<"FORCE DEPOSIT";zoneToCollect = 4;}
        switch(zoneToCollect){
            case 0: //Red
                moveRed();cout<<"Red";
                cycle[0] = true;
                if (red) zoneToCollect = -1;
                break;
            case 1: //Blue
                moveBlue();cout<<"Blue";
                cycle[1] = true;
                if (blue) zoneToCollect = -1;
                break;
            case 2: //Black
                moveBlack();cout<<"Black";
                cycle[2] = true;
                if (black) zoneToCollect = -1;
                break;
            case 4:
                moveDeposit();cout<<"Deposit";
                if (!red || !blue || !black){zoneToCollect=-1;}
                break;

        }
        if (Time>465 && w2Obj.LoadedObjects>0){return;}


        int currZoneNo = zn->getZoneNo(createCoordinates(PositionX1,PositionY1));//mapping->path[mapping->path.size()-1]);
        cout<<" Zone to Collect:"<<zoneToCollect<<" Current Zone: "<<currZoneNo<<" ";
        //if (w2Obj.isCollectedRed() || w2Obj.isCollectedBlue() || w2Obj.isCollectedBlack()){consecutive++;}
        if (Timing.timeout(timeToCollect+consecutive*additionalTime) || zoneToCollect == -1){
            changeZone();
            cout<<"Set Zone:";
            zn->setVisitedZone(currZoneNo);
        }else if (prevZone != zoneToCollect){
            zn->setVisitedZone(currZoneNo);
            cout<<endl<<"Set Zone: "<<currZoneNo<<" ";
            prevZone=zoneToCollect;
        }
        //cout<<zoneToCollect;
    }

};
