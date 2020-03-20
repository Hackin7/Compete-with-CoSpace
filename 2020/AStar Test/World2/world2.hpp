class PresetMovement{
	public:
	deque<pair<pair<int,int>,int> > steps;
	void addStep(int left, int right, int delay){
		pair<pair<int,int>,int> step;
		step.first.first=left;
		step.first.second=right;
		step.second=delay;
		steps.push_back(step);
	}
	bool run(){
		if (!steps.empty()){
			WheelLeft = steps[0].first.first;
			WheelRight = steps[0].first.second;
			Duration = steps[0].second;
			steps.pop_front();
			cout<<"Move Like An Idiot:"<<WheelLeft<<","<<WheelRight<<","<<Duration<<endl;
			return true;
		}
		return false;
	}
};
PresetMovement moveFixed;

void addTempBarrier(int us, double uscomp){
    if (us<15){
        int boundary=8;
        int x = PositionX1 + (us+5)*cos(uscomp); //Offset
        int y = PositionY1 + (us+5)*sin(uscomp);
        location.addTempZone(x-boundary,y-boundary,x+boundary,y+boundary);
    }
}

void boxOut(int box, int x, int y){
    for(int j=max(0,x-box);j<x;j++){
        for(int k=max(0,y-box);k<y;k++){
            pathFile<<j<<" "<<k<<"\n";//count++;
    }}
}

int prevX; int prevY;
static void Game1(){
    PositionX1 = PositionX;PositionY1 = PositionY;
    posInfoLost();
    colorSensorX = PositionX1+(int)round(cos((Compass+90.0)*PI/180)*5);
	colorSensorY = PositionY1+(int)round(sin((Compass+90.0)*PI/180)*5);
	if (PositionX1 == 0 || PositionY1 == 0){PositionX1=tx;PositionY1=ty;}
    cout<<"X:"<<PositionX1<<" Y:"<<PositionY1<<" TX:"<<tx<<" TY:"<<ty<<endl;

	if (Duration){ //>0
		Duration--;
		return;
	}if (moveFixed.run()){return;};

	///File IO/////////////////////////////////////////////////////////////
    /*
	if (!outfile.is_open()){
        outfile.open("CoSpace_Output.txt"); //Check the Robotics Dev Studio Folder
    }else{
        outfile<<"Time:"<<Time<<endl;
        outfile<<cycle.zoneToCollect;
        //outfile<<data;
        outfile.flush();
        outfile.seekp(0, ios::beg);
    }*/
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
        //outfile<<data;
        mapFile.flush();
        mapFile.seekp(0, ios::beg);
        //mapFile.close();
    }
    z.fileOut();

    if (!pathFile.is_open()){
        pathFile.open("path.txt"); //Check the Robotics Dev Studio Folder
    }else{
        for (auto i:mapping.path){
            boxOut(5,i.pos[0],i.pos[1]);
            pathFile<<i.pos[0]<<" "<<i.pos[1]<<endl;
        }
        //outfile<<data;
        pathFile.flush();
        pathFile.seekp(0, ios::beg);
    }

    /// //////////////////////////////////////////////////////////////////////

	bool collectBlue = w2Obj.LoadedObjects<6 && (w2Obj.LoadedBlue + w2Obj.LoadedSuperObj + w2Obj.noSuperObj)<2;//true;
	bool collectRed = w2Obj.LoadedObjects<6 && w2Obj.LoadedRed<2;//true;
	bool collectBlack = w2Obj.LoadedObjects<6 && w2Obj.LoadedBlack<2;//true;
	bool deposit = w2Obj.LoadedObjects>=3 ||  w2Obj.LoadedSuperObj > 0;//true;
	bool avoid = w2Obj.LoadedObjects>=2|| w2Obj.LoadedSuperObj > 0;//true;


    //Temporary Barrier
    if (Time%2==0){
            //cout<<"TTTTTTTTTT";
            double pi=3.1415926535;double usfcomp=0;double usrcomp=0;double uslcomp=0;
            int usfcomptemp=((Compass+90)%360);
            usfcomp=usfcomptemp;
            uslcomp=(usfcomptemp-40)%360;
            usrcomp=(usfcomptemp+40)%360;
          // convert to rad
            usfcomp=usfcomp*pi/180;
            usrcomp=usrcomp*pi/180;
            uslcomp=uslcomp*pi/180;
            addTempBarrier(US_Front, usfcomp);
            addTempBarrier(US_Right, usrcomp);
            addTempBarrier(US_Left, uslcomp);
    }
    if (Time%7==0){
        for(int i=0;i<10;i++){location.removeTempZone();}
    }
    //mappingMode();
	//if (w2Obj.Trap(avoid)){return;}else
    if (w2Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	//else if (colorCheck(w2Obj.slowarea,20) && Time>60){WheelLeft=-3;WheelRight=-4;Duration=2;}
    //else if ( US_Front < 15){WheelLeft=-2;WheelRight=-3;Duration=5;} //iMPROVE wORLD 2 Wall Avoiding
    else if (boundary(12)){}
	else if ( US_Front < 9){
        WheelLeft=-2;WheelRight=-2;//Duration=2;
    } //IMPROVE wORLD 2 Wall Avoiding
    //else if (wallAvoiding(7)){}
	//else if (PositionX==0 || PositionY==0){WheelLeft=3;WheelRight=3;return;}
	else if (superObjAStar()){return;}
	else if (w2Obj.LoadedObjects >=6 || (Time > 420 && (w2Obj.LoadedObjects >=3 ||w2Obj.LoadedSuperObj>0))){cout<<"D";cycle.moveDeposit();}
	//else
	//else if (PositionX==0 || PositionY==0){WheelLeft=3;WheelRight=3;return;}
    else cycle.collectObjects(!collectRed,!collectBlue, !collectBlack);
    //{WheelLeft=0;WheelRight=0;}//

    //rotateTo(47,106);
    //else moveAStar(174,190);

	prevX = PositionX;prevY=PositionY;
}
