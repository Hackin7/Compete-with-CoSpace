/* Deposit Conditions
Compass == 180
int Pink [3] = {216,66,254}
US_Front < 30
walltrace left: US_Left<40
walltrace right: US_right<40
*/

bool color_LeftCheck(int *objBlue, int objRange)
{
	return (objBlue[0] - objRange <= CSLeft_R && CSLeft_R <= objBlue[0] + objRange &&
	      objBlue[1] - objRange <= CSLeft_G && CSLeft_G <= objBlue[1] + objRange &&
	      objBlue[2] - objRange <= CSLeft_B && CSLeft_B <= objBlue[2] + objRange
		);
}
bool color_RightCheck(int *objBlue, int objRange)
{
	return (objBlue[0] - objRange <= CSRight_R && CSRight_R <= objBlue[0] + objRange &&
	      objBlue[1] - objRange <= CSRight_G && CSRight_G <= objBlue[1] + objRange &&
	      objBlue[2] - objRange <= CSRight_B && CSRight_B <= objBlue[2] + objRange
		);
}
bool color_Check(int *objBlue, int objRange)
{return ( color_LeftCheck(objBlue, objRange) || color_RightCheck(objBlue, objRange));}

bool Mass_collection(){
	WheelLeft=0;WheelRight=0;
	LED_1 =1;
	Duration=41;
	LoadedObjects++;
}

bool avoid_Trap(){
	
	int trapYellow[3] = {215,225,10};
	int trapBlue[3] = {56,100,225};
	int trapRange = 40;
	
	if (LoadedObjects > 0){//objRange ) &&)){

	    WheelLeft=-3;WheelRight=-4; // Turn
            //Duration=5;

		if (! color_RightCheck(trapYellow,trapRange*2)){ // Turn Right
			WheelLeft=3;WheelRight=-1;
			//Duration = 5;
		}
		else if (! color_LeftCheck(trapYellow,trapRange*2)){ // Turn Left
			WheelLeft=-1;WheelRight=3;
			//Duration = 5;
		}
		else{
            WheelLeft=-2;WheelRight=-4; // Turn
            Duration=5;
		}
		printf("Danger\n");
		return true;
	}
		//Duration=41;
	else{ return false;}
	return true;
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
	int depRange = 35;
	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = true;
	bool avoid = true;
	
	
	if (((color_Check(objBlue,30)) || color_Check(objBlack,30) || color_Check(objRed,30)) && LoadedObjects<6){
		Mass_collection();
	}
	/////////////DEPOSIT MAIN///////////////////////////////////////
	else if (color_Check(depositOrange,30) && LoadedObjects>0){
		////////DEPOSIT MAIN////////////////////
			w1Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit);
	}
	else if (colorCheck(trapYellow,30)||colorCheck(trapBlue,30)){
		avoid_Trap();
	} // If ran, let it do its thing

	else if ((color_Check(zoneblue,30) && LoadedObjects<6)&& (US_Right<35 && (Compass>=70 && Compass<=110))){
		WT_L();
	}
	else if ((color_Check(zoneblue,30) && LoadedObjects<6)&& (US_Left<35 && (Compass>=250 && Compass<=290))){
		WT_R();
	}
	else if ((color_Check(Pink,30) && LoadedObjects>1) && (Compass>55 && Compass<135)){
		cout << "#CodePink_Left" << endl;
		WheelLeft = 1;
		WheelRight = -1;
		if (Compass>85 && Compass<95){
			WheelLeft = 2;
			WheelRight = 2;
			if (color_Check(depositOrange,30)){
	////////////////////////////////DEPOSIT SUB-1///////////////////////////////////////
			w1Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit);
			}
		}
	}
	else if ((color_Check(Pink,30) && LoadedObjects>1) && (Compass>235 && Compass<305)){
		cout << "#CodePink_Right" << endl;
		WheelLeft = 1;
		WheelRight = -1;
		if (Compass>265 && Compass<285){
			WheelLeft = 2;
			WheelRight = 2;
			if (color_Check(depositOrange,30)){
	/////////////////////DEPOSIT SUB 2///////////////////////////////
				w1Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit);
			}
		}
	}
	//fully loaded
	/*else if (LoadedObjects==6){
		if ((Compass>=135 && Compass<=190)&& (US_Right<20 &&(US_Left>30 && US_Left<120)||(US_Front>30 && US_Front<120))){
			WT_R();
			if (colorCheck(Pink,30)){
				WheelLeft = 1;
				WheelRight = 1;
				if (US_Front<18){
					WT_R();
						if (colorCheck(depositOrange,30) && LoadedObjects>0){
							DepositW1D1();
							LoadedObjects = 0;
						}
					}
				}
			}
		
	else if ((Compass>=170 && Compass<=230)&& (US_Left<20 &&(US_Right>30 && US_Right<120)||(US_Front>30 && US_Front<120))){
		WT_L();
		if (colorCheck(Pink,30)){
			WheelLeft = 1;
			WheelRight = 1;
			if (US_Front<18){
				WT_L();
					if (colorCheck(depositOrange,30) && LoadedObjects>0){
						DepositW1D1();
						LoadedObjects = 0;
					}
				}
			}
		}
	} */
		

	
	
	else if (world1wallAvoiding()){}
	else {
		WT_L();
		
		}
		
	
		//optimise, dont waste time wandering around
		/*if (LoadedObjects==0 || colorCheck(w1Obj.specialZone,w1Obj.objRange)){
		WheelLeft=4; 
		WheelRight=4;
		}
		else if (Time<10 && (Compass>=80 && Compass<=100)){
			WT_R();
		}
		else if (Time<10 && (Compass>=260 && Compass<=280)){
			WT_L();
		}
		else{
		WheelLeft = 3;
		WheelRight = 3;
		}*/
		
	


	if (Time > 180){
			Teleport = 4;
			LoadedObjects=0;
		}
		 
}
