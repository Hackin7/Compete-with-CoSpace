//////////////////////////////////////////////////////////////////////////////////

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

	int darkBlue [3] = {90,42,185};
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


	else if ((Compass>=90 && Compass<170) && (US_Front<20 && US_Left<20 && US_Right<20) && LoadedObjects>0){
		cout << "at bottom left corner" << endl;
		WheelRight = 2;
		WheelLeft = -2;
		if (Compass>=300 && Compass<=330){
			WheelLeft = 1;
			WheelRight = 1;
			cout << "To deposit" << endl;
		}
	}
	
	else if ((Compass>=120 && Compass<=150) && (US_Front<20 && US_Left<20 && US_Right<20) && LoadedObjects>0){
		cout << "at top right corner" << endl;
		WheelRight = -2;
		WheelLeft = 2;
		if (Compass>=300 && Compass<=330){
			WheelLeft = 1;
			WheelRight = 1;
			cout << "To deposit" << endl;
		}
		
	}
	//////////empty/////////////////
	/*else if (LoadedObjects==0 && colorCheck(darkBlue,30)){ 
		int compassPlus = Compass + 40;
		int compassMinus = Compass - 40;
		if ((Compass>=0 && Compass<=25) && (Compass>=335 && Compass<=359)) {
		cout << "empty, top left, from bottom" << endl;
		cout << "Compass: " << Compass << endl;
		WheelLeft = 1;
		WheelRight = -1;
		if ((Compass>= (compassPlus-5) && (Compass<=(compassPlus+5))) && US_Front>100){
			cout << "newCompass: " << Compass << endl;
			WheelLeft = 4;
			WheelRight = 4;
			cout << "to centre" << endl;
		}
	}
		else if(Compass>10 && Compass<100){
		cout << "empty, top left, from right" << endl;
		cout << "Compass: " << endl;
		WheelRight = 1;
		WheelLeft = -1;
		if ((Compass>= (compassMinus-5) && (Compass<=(compassMinus+5))) && US_Front>100){
			cout << "newCompass: " << Compass << endl;
			WheelLeft = 4;
			WheelRight = 4;
			cout << "to centre" << endl;
		}
		}
		else if (Compass>160 && Compass<200){
			cout << "empty, bottom right, from top" << endl;
			cout << "Compass: " << Compass << endl;
			WheelLeft = 1;
			WheelRight = -1;
			if ((Compass>=(compassMinus-5) && (Compass<=(compassMinus+5))) && US_Front>100){
				cout << "newCompass: " << Compass << endl;
				WheelLeft = 4;
				WheelRight = 4;
				cout << "to centre" << endl;
			}
		}
		else if (Compass>250 && Compass<290){
			cout << "empty, bottom right from left" << endl;
			cout << "Compass: " << Compass << endl;
			WheelRight = 1;
			WheelLeft = -1;
			if ((Compass>=(compassPlus-5) && Compass<=(compassPlus+5)) && US_Front>100){
				cout << "newCompass: " << Compass << endl;
				WheelLeft = 4;
				WheelRight = 4;
				cout << "to centre" << endl;
			}
		}
} */
////////////end of empty///////////////
	else if (colorCheck(darkBlue,30) && LoadedObjects>0){
		WT_L();
		cout << "WT_L to deposit" << endl;
	}
	
	 // If ran, let it do its thing
	 ///////////fully loaded////////////
	 else if (LoadedObjects==6 && colorCheck(zoneblue,30)){
	 	WT_L();
	 	cout << "Fully-loaded program running" << endl;
	 }
	
	


	else if (colorCheck(zoneblue,30) && LoadedObjects<6){
		cout << "Special Zone, slow down" << endl;
		WheelLeft = 3;
		WheelRight = 3;
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

