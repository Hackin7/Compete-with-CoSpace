// File: Movements/WallTracer.c

//only walltrace if walltrace = 1;
// wallfollowing
bool WT_R(){
	int timeout = 0;
	cout << timeout << endl;
	if (US_Right<25 && US_Right>=20){
		timeout++;
		WheelLeft = 0;   //turn left
		WheelRight = 2;
		cout << "WT_R running" << timeout <<  endl;
		if (US_Left<11){   //senses wall on the left
			WheelLeft = 2;
			WheelRight = 0;
		}
	}
	else if (US_Right>30){
		WheelLeft = 2;
		WheelRight = 0;
		if (US_Left<15){
			WheelLeft = 2;
			WheelRight = 0;
			cout << "crap" << endl;
		}
	}
	else if (timeout >= 100){
		cout << "loop exit";
		return false;
	}
	return true;
}
bool WT_L(){
	int timeout = 0;
	if (US_Left<25 && US_Left>=20){
		timeout++;
		WheelLeft = 2;   //turn left
		WheelRight = 0;
		cout << "WT_L running" << timeout << endl;
		timeout = timeout + 1;
		if (US_Right<11){
			WheelLeft = 0;
			WheelRight = 2;
		}
	}
	else if (US_Left>30){
		WheelLeft = 0;
		WheelRight = 2;
		if (US_Right<15){
			WheelLeft = 0;
			WheelRight = 2;
			cout << "crap" << endl;
		}
	}
	else if (timeout >= 100){
		cout << "loop exit";
		return false;
	}
	return true;
}
//deflection = how big zigzag will be
//l_value = initial US_Left value, r_value = initial US_Right value
//init_d = initial Compass value
bool Sweeper(int deflection, int L_value, int R_value, int init_d){
	int opp_d = abs(deflection - init_d);
	int side = L_value - R_value; // >0 right side (towards left).<0 left side (towards right)
	if (US_Left<20){
		//turn right
		WheelLeft = 3;
		WheelRight = 2;
		if (Compass != init_d){ //turn left to correct error
			cout << "Error: " << abs(Compass-init_d) << endl;
			WheelLeft = -2;
			WheelRight = 2;
			if (Compass == init_d){
				WheelLeft = 4;
				WheelRight = 4;
				cout <<"Corrected" << endl;
			}
		}
		else if (Compass != opp_d){
			cout << "Error: " << abs(Compass-opp_d) << endl;
			WheelLeft = -2;
			WheelRight = 2;
			if (Compass == opp_d){
				WheelLeft = 4;
				WheelRight = 4;
				cout << "Corrected" << endl;
			}
		}
		
	}
	else if (US_Right<20){
		//turn left
		WheelRight = 3;
		WheelLeft = 2;
		if (Compass != init_d){ //turn right to correct error
			cout << "Error: " << abs(Compass-init_d) << endl;
			WheelLeft = 2;
			WheelRight = -2;
			if (Compass == init_d){
				WheelLeft = 4;
				WheelRight = 4;
				cout <<"Corrected" << endl;
			}
		}
		else if (Compass != opp_d){
			cout << "Error: " << abs(Compass-opp_d) << endl;
			WheelLeft = 2;
			WheelRight = -2;
			if (Compass == opp_d){
				WheelLeft = 4;
				WheelRight = 4;
				cout << "Corrected" << endl;
			}
		}
		
		
	}
	else if(US_Front<15 && US_Left<15 && US_Right<20){
		WheelLeft=-3; WheelRight=3;
		if (Compass == init_d){
			cout << "Set point (Front)" << endl;
			WheelLeft = 4;
			WheelRight = 4;
			
		}
	}
	else if (US_Front<20 && (US_Left>40 && US_Right>40) && (Compass==init_d || Compass==opp_d)){ //(reached a wall about to turn)
		if (side>0){
			//turn left wrt robot
			WheelRight = 3;
			WheelLeft = -3;
		}
		else if (side<0){
			//turn right wrt robot
			WheelRight = -3;
			WheelLeft = 3;
		}
		else { //robot wedged between 2 walls, so cannot determine side
		// by default turn right
			WheelRight = -3;
			WheelLeft = 3;
		}
		
	}
	return false;
	
}
///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////line-tracing//////////////////////////////////////////////////////
/*bool LT_R(){
	if (right detected trap){
		//turn left a bit
		if (right falls slightly smaller than trap values){
			//turn right less than a bit
		}
	}
	else {
		//turn right a bit
		if (right detected white){
			//turn left by more than a bit
		}
		
		
	}
} */


//////////////////////////////////////////////////////////////////////////////////
bool LT_R(){
	int trapYellow[3] = {220,235,20};
	int White[3] = {235,248,255};
	if (colorRightCheck(trapYellow,37)){
		//turn left a bit
		WheelRight = 2;
		WheelLeft = 0;
		if (colorRightCheck(White,30)){      //right detedted white
			//turn right less than a bit
			cout << "LT_R running" << endl;
			WheelLeft = 1;
			WheelRight = 0;
		}
	}
	else {
		//turn right a bit
		WheelLeft = 2;
		WheelRight = 0;
		if (colorLeftCheck(trapYellow,30)){  //right detected white or left detected yellow
			//turn left by more than a bit
			cout << "LT_R running" << endl;
			WheelRight = 3;
			WheelLeft = -1;
		}
		
		
	}
}
//////////////////////////////////////////////////////////////////////////////////

static void Game0(){
	if (Duration){ //>0
		Duration--;
		return;
	}
	
	class PresetMovement{
	public:
	deque<pair<pair<int,int>,int> > steps;
	void addStep(int wheel_left, int wheel_right, int delay){
		pair<pair<int,int>,int> step;
		step.first.first=wheel_left;
		step.first.second=wheel_right;
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

	int Pink [3] = {216,66,254};
	int zoneblue[3] = {0, 160,245};
	int trapYellow[3] = {215,225,20};
	int trapBlue[3] = {56,100,225};
	int depositOrange[3] = {204,130,10};
	int objBlue[3] = {29,249,255};
	int objRed[3] = {235,29,29};
	int objBlack[3] = {20,20,20};

	int zonebluerange=30;
	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = true;
	bool avoid = true;
	
	
	if (w1Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;}
	else if (w1Obj.Trap(avoid)){return;}
	else if (world1wallAvoiding()){}
	else if (colorCheck(depositOrange,30) && LoadedObjects>0){
		WheelLeft = 0;
		WheelRight = 0;
		Duration = 60;
		cout << "At Deposit" << endl;
		w1Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit);
		LoadedObjects = 0;
	}
	
	 // If ran, let it do its thing
	else if ((Compass>=0 && Compass<75) && (US_Front<30 && US_Right<25 && US_Left<25)){
		WheelLeft = 2;
		WheelRight = -2;
		if (Compass>53){
			cout << Compass << "," << "To deposit" << endl;
			WheelLeft= 3;
			WheelRight = 3;
		}
	}
	
	else if (LoadedObjects>0 && colorCheck(trapYellow,35) && US_Left<10 && (Compass>205 && Compass<245)){
		//turn left + move foward until detect pink
		cout <<"Stuck near Deposit" << endl;
		WheelRight = 3;
		WheelLeft = -1;
		if (colorCheck(Pink,30)){
			cout << "#CodePink_ter" << endl;
			WT_L();
			if (colorCheck(depositOrange,30) && LoadedObjects>0){
				w1Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit);
				
			
			}
		}
	}
	
	else if (colorCheck(Pink,30) && (Compass>35 && Compass<125) && US_Front>15 && LoadedObjects>0){
		cout << "#CodePink_ter" << endl;
		WheelLeft = 2;
		WheelRight = -2;
		if (Compass>85 && Compass<95){
			WheelLeft = 2;
			WheelRight = 2;
			if (colorCheck(depositOrange,30) && LoadedObjects>0){
				w1Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit);
				
				
			}
		}
	}
	
		else if ((colorRightCheck(Pink,30)) && (US_Left<19 && US_Front<19) && (Compass>=270 && Compass<=259)){
			cout << Compass << endl;
			cout << "Deposit1 turn right" << endl;
			WheelLeft = 2;
			WheelRight = -2;
			if (Compass>=178 && Compass<=182){
				WheelLeft = 2;
				WheelRight = 2;
			}
		}
		else if ((colorRightCheck(Pink,30)) && (US_Right<19 && US_Front<19) && (Compass>=0 && Compass<=90)){
			cout << Compass << endl;
			cout << "Deposit1 turn left" << endl;
			WheelRight = 2;
			WheelLeft = -2;
			if (Compass>=178 && Compass<=182){
				WheelLeft = 2;
				WheelRight = 2;
			}
		}
	
	////////////////line trace to deposit///////////////////////////
	else if (colorRightCheck(trapYellow,30) && LoadedObjects>0 && LoadedObjects<5){
		cout << "test success" << endl;
		LT_R();
	
	} 
	

	else if ((colorCheck(zoneblue,30) && LoadedObjects<6)&& (US_Right<30 && (Compass>=250 && Compass<=290))){
		cout << "SpecialZone" << endl;
		WT_R();
	}
	else if ((colorCheck(zoneblue,30) && LoadedObjects<6)&& (US_Left<30 && (Compass>=70 && Compass<=110))){
		cout << "Specialzone" << endl;
		WT_L();
	}
	//fully loaded

	//#codepink
	else if (LoadedObjects>2 && colorCheck(Pink,30) && US_Front<20){
		cout << "compass: " << Compass << endl;
		cout << "#CodePink" << endl;
		WheelLeft = 2;
		WheelRight = -2;
		
		if ((Compass>=0 && Compass<=2) || (Compass>=358 && Compass<=359) || (Compass>=268 && Compass<=272)){
			cout << "Reverse to Deposit" << endl;
			WheelLeft = -2;
			WheelRight = -2;
		}
		/////////////DETECTED PINK ON TOP/////////////////
		else if ((colorRightCheck(Pink,30)) && (US_Left<19 && US_Front<19) && (Compass>=270 && Compass<=259)){
			cout << Compass << endl;
			cout << "Deposit1 turn right" << endl;
			WheelLeft = 2;
			WheelRight = -2;
			if (Compass>=178 && Compass<=182){
				WheelLeft = 2;
				WheelRight = 2;
			}
		}
		else if ((colorRightCheck(Pink,30)) && (US_Right<19 && US_Front<19) && (Compass>=0 && Compass<=90)){
			cout << Compass << endl;
			cout << "Deposit1 turn left" << endl;
			WheelRight = 2;
			WheelLeft = -2;
			if (Compass>=178 && Compass<=182){
				WheelLeft = 2;
				WheelRight = 2;
			}
		}
		////////////////DETECTED PINK ON RIGHT/////////////////
		/*else if ((color_RightCheck(Pink,30)) && ((US_Left>=19 && US_Left<=)))*/
		
		
	
	}
	
	

	

	
	//else if (W1WA()){}
	
	else {
	
		
			WheelLeft = 4;
			WheelRight = 4;
		
	}
		
		
		
	
		
	


	if (Time > 180){
			Teleport = 2;
			LoadedObjects=0;
		}
	} 

