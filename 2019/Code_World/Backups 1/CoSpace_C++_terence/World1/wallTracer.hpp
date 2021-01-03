// File: Movements/WallTracer.c
int timeout=0;
//only walltrace if walltrace = 1;
// wallfollowing
bool WallTracer_right(){
	timeout = 0;
	if (US_Right<20){
		WheelLeft = 1;
		WheelRight = 3;
		printf ("wall right");
		timeout++;
	}
	else if (US_Right>40){
		WheelLeft = 3;
		WheelRight = 1;
	}
	else if (timeout >= 100){
		return false;
	}
	else{WheelLeft=4;WheelRight=4;}
	return true;
}
bool WT_R(){
	timeout = 0;
	if (US_Right>= 15 && US_Right<20){
		WheelLeft = 0;   //turn left
		WheelRight = 2;
		cout << "WT_R running" << endl;
		timeout = timeout + 1;
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
	timeout = 0;
	if (US_Left<20){
		WheelLeft = 2;   //turn left
		WheelRight = 0;
		cout << "WT_L running" << endl;
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
