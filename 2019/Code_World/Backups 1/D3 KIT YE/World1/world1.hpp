/* Deposit Conditions
Compass == 180
int Pink [3] = {216,66,254}
US_Front < 30
walltrace left: US_Left<40
walltrace right: US_right<40
*/
int Yellow[3] = {215,225,10};
int trapcol[3] = {215,225,20};
int traptimer=0;
int depottimer=0;
bool turnatstart=true;
int pinktimer=0;
bool turningpink=false;
int Pink[3] = {200,55,240};

bool turningeast=false;
bool turningwest=false;
bool turningdown = false;

void turndown()
{
	if (!(Compass>130 && Compass < 180))
	{WheelLeft=-2;WheelRight=2;}
	else{turningdown=false;}
}
void turneast()
{
	if (!(Compass>230 && Compass< 320)) // east/right
	{WheelLeft=2;WheelRight=-2;}
	else{turningeast=false;}
}
void turnwest()
{
	if (!(Compass<100 && Compass> 30))
	{WheelLeft=-2;WheelRight=2;}
	else{turningwest=false;}
}


bool turnpink()
{
	if (colorCheck(Pink,30) && (pinktimer==0) && w1Obj.LoadedObjects>=4)
	{
		pinktimer=400;
		if (Compass < 40 || Compass>320) // upwards
		{
			turningwest=true;
		}
		else
		{
			turningdown=true;
		}
		return true;
	}

	else {return false;}
}

bool turnpink1()
{
	if (colorCheck(Pink,20) && !(Compass>260 && Compass< 300) && !(Compass<100 && Compass> 70) && (pinktimer==0) && w1Obj.LoadedObjects>=0)
	{
		pinktimer=300;
		if (Compass < 90 || Compass>270) // upwards
		{
			if (US_Left<US_Right)// wall Left
			{
				turningeast=true;
			}
			else if (US_Right< US_Left)
			{
				turningwest=true;
			}
		}
	else // down
	{
		if (US_Right<US_Left)// wall right
		{
			turningeast=true;
		}
		else if (US_Right>US_Left)
		{
			turningwest=true;
		}
	}
	return true;
}
	else {return false;}
}



int w1minSpeed=5,w1maxSpeed=5;
int w1theta=-1,w1AngleDiff,w1CWAngleDiff,w1ACWAngleDiff;
void w1speed(int left, int right){
 WheelLeft=left;WheelRight=right;
}
 void w1turnToAngle(int targetAngle)
{
 //must have set minSpeed AND maxSpeed BEFORE CALLING THIS FUNC
 if(Compass>=targetAngle)
 {
	 w1CWAngleDiff=Compass-targetAngle;
	 w1ACWAngleDiff=360-(Compass-targetAngle);
 }
 else //Compass<targetAngle
 {
	 w1ACWAngleDiff=targetAngle-Compass;
	 w1CWAngleDiff=360-(targetAngle-Compass);
 }

 if(w1CWAngleDiff<=w1ACWAngleDiff) w1speed(w1maxSpeed,w1minSpeed);//turn clockwise
 else if(w1ACWAngleDiff<w1CWAngleDiff) w1speed(w1minSpeed,w1maxSpeed);//turn anti-clockwise
 else w1speed(w1maxSpeed,w1maxSpeed);//move forward
}

bool DepositW1D1(){
	int depositOrange[3] = {204,130,10};
	int depRange = 35;
	if (colorCheck(depositOrange,depRange))
	{
		//2 color sensors must be in orange
		if (! colorRightCheck(depositOrange,depRange)){ // Turn Right
			WheelLeft=0;WheelRight=3;
			return true;
		}
		if (! colorLeftCheck(depositOrange,depRange)){ // Turn Left
			WheelLeft=3;WheelRight=0;
			return true;
		}
		WheelLeft=0;WheelRight=0;
		LED_1 =2;
		Duration=60;
		LoadedObjects = 0;

	}
	else{return false;}
	return true;
}
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
	if (turnatstart)
	{
		WheelLeft=5;WheelRight=-5;
		Duration=3;
		turnatstart=false;
		return;
	}


	if (traptimer>0)
	{
		traptimer--;
		int loop =0;

	}


	if (Duration){ //>0
		Duration--;
		return;
	}
	if (pinktimer>0)
	{
		pinktimer--;
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



	if (w1Obj.Trap(avoid)){return;}
	else if (w1Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){pinktimer=0;return;}
	else if (depottimer>0)
	{
		if (!colorCheck(trapcol,40))
		{
			WheelLeft=5; WheelRight=5;
		}
		else
		{
			traptimer=60;
			depottimer=0;
		}
	}
	else if (traptimer>0)
	{
		traptimer=0;
		if (Compass< 220 && Compass> 160) // downwards
		{
			Duration=9;
			WheelLeft=5;WheelRight=5;
		}
		else
		{
			Duration=8;
			WheelLeft=5;WheelRight=4;
		}
	}


	 // If ran, let it do its thing



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
	else if (turningeast){turneast();}
	else if (turningwest){turnwest();}
	else if (turningdown){turndown();}
	else if (turnpink()){}
	/*else if (colorCheck(depositOrange,20) && LoadedObjects==0)
	{
		if ((Compass<105 && Compass> 75))
		{
			turningwest=true;
		}
		else if (!(Compass<190 && Compass> 170))
		{
			turningdown=true;
		}
		else
	}*/
	else if (colorCheck(depositOrange,20) && w1Obj.LoadedObjects==0)
	{
		pinktimer=0;
		depottimer=30;
	}

	else if (pinktimer>0 && w1Obj.LoadedObjects>0)
	{
		WheelLeft=5;WheelRight=5;
	}
	else if (wtrrunning){WT_R();}
	else if (wtlrunning){WT_L();}
	//else if (world1wallAvoiding()){}

	else {
		if (w1Obj.LoadedObjects==0){WheelLeft=5; WheelRight=5;}
		else {WheelLeft=3; WheelRight=3;}
		}


	if (Time > 180){
			Teleport = 4;
			LoadedObjects=0;
		}
	}
