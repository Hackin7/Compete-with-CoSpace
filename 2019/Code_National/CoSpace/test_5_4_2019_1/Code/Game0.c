
int timeout;
//only walltrace if walltrace = 1;
// wallfollowing
bool WallTracer_right(){
	timeout = 0;
	if (US_Right<30){
		WheelLeft = 0;
		WheelRight = 2;
		printf ("wall right");
		timeout++;
	}
	else if (US_Right>50){
		WheelLeft = 2;
		WheelRight = 0;
	}
	else if (timeout => 100){
		return;
	}
}
void Game0(){
	if (Duration){ //>0
		Duration--;
		return;
	}
	int timeout = 0;

	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = true;
	bool avoid = true;
	
	
	if (avoidTrap(avoid)){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (wallAvoiding()){}
	else if (WallTracer_right()){}
	else {
		WheelLeft=4;WheelRight=4;
	}

	if (Time > 180){
			Teleport = 1;
	}
}
