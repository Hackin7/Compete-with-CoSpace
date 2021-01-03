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
//deflection = how big zigzag will be
//l_value = initial US_Left value, r_value = initial US_Right value
//init_d = initial Compass value
bool Sweeper(int deflection, int L_value, int R_value, int init_d){
	int opp_d = abs(deflection - init_d);
	int side = L_value - R_value // >0 right side (towards left).<0 left side (towards right)
	if (US_Left<20 && US Front>40){
		//turn right
		WheelLeft = 3;
		WheelRight = 2;
		if (Compass == init_d){
			WheelLeft = 4;
			WheelRight = 4;
		}
	}
	else if (US_Right<20 && US_Front>40){
		//turn left
		WheelRight = 3;
		WheelLeft = 2;
		if (Compass == init_d){
			WheelLeft = 4;
			WheelRight = 4;
		}
	}
	else if(US_Front<15 && US_Left<15 && US_Right<20){
		WheelLeft=-3; WheelRight=3;
		if (Compass == init_d){
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
