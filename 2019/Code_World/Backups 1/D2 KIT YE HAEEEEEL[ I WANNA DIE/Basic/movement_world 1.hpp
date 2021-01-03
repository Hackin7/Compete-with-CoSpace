///////////
// File: Movements/WallAvoiding.c
bool World1_dontcollide(){
	if (US_Front<15){    //obstable in front
	if (US_Right<20 && US_Left>30){
		//turn left
		cout << "Front+Right" << endl;
		WheelRight = 4;
		WheelLeft = 2;
	}
	else if (US_Left<20 && US_Right>30){
		//turn right
		cout << "Front+Left" << endl;
		WheelLeft = 4;
		WheelRight = 2;
	}
	}
	else if (US_Left<15){  //obstacle on the left
		//smooth turn right
		WheelLeft = 4;
		WheelRight = 2;
		if (US_Front<20 && US_Right>25){
			//sharp turn right
			WheelLeft = 4;
			WheelRight = 2;
		}
	}
	else if (US_Right<15){     //obstacle on the right
		//smooth turn left
		WheelLeft = 2;
		WheelRight = 4;
		if (US_Front<20 && US_Left>25){
			//sharp turn left
			WheelRight = 4;
			WheelLeft = 2;
		}
	}
	else if (US_Right<14 && US_Left<14 && US_Front<20){   //corner

	}
}
