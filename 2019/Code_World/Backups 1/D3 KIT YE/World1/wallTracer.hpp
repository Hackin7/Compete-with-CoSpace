// File: Movements/WallTracer.c
int timeout=0;

//only walltrace if walltrace = 1;
// wallfollowing
bool WallTracer_right(){
	timeout = 0;
	if (US_Right<17){
		WheelLeft = 0;   //turn left
		WheelRight = 2;
		cout << "WT_R running" << endl;
		timeout = timeout + 1;
		if (US_Left<11){
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
bool WallTracer_left(){
	timeout = 0;
	if (US_Left<17){
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
