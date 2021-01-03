///////////
// File: Movements/WallAvoiding.c
/*bool World1_dontcollide(){
	if (US_Front<15){    //obstable in front
	if (US_Right<20 && US_Left>30){
		//turn left 
		cout << "Front+Right" << endl;
		WheelRight = 2;
		WheelLeft = -1;
	}
	else if (US_Left<20 && US_Right>30){
		//turn right
		cout << "Front+Left" << endl;
		WheelLeft = 2;
		WheelRight = -1;
	}
	}
	else if (US_Left<15){  //obstacle on the left
		//smooth turn right
		WheelLeft = 2;
		WheelRight = 1;
		if (US_Front<20 && US_Right>25){
			//sharp turn right
			WheelLeft = 3;
			WheelRight = 1;
		}
	}
	else if (US_Right<15){     //obstacle on the right
		//smooth turn left
		WheelLeft = 1;
		WheelRight = 2;
		if (US_Front<20 && US_Left>25){
			//sharp turn left
			WheelRight = 3;
			WheelLeft = 1;
		}
	}
	else if (US_Right<14 && US_Left<14 && US_Front<20){   //corner
		if (Compass)
	}
} */
////////////////////////////////////////////////////////////
static bool W1WA(){
	if (US_Left<20){
		WheelRight = -1;
		WheelLeft = 4;
		if (US_Right<17){
			cout << "new movement running" << endl;
			WheelLeft = 1;
			WheelRight = 3;

		}
	}
	else if (US_Front<20){
		WheelLeft = -3;
		WheelRight = 4;
		if (US_Right<18 && US_Left<18){
			cout << "new movement running" << endl;
			WheelLeft = 4;
			WheelRight = -4;
		}
	}
	else if (US_Right<20){
		WheelRight = 4;
		WheelLeft = -1;
		if (US_Left<17){
			cout << "new movement running" << endl;
			WheelLeft = 3;
			WheelRight = 1;
		}
	}
}


