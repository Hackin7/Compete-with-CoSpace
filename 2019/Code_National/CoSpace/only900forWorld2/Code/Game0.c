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
	else if (wallAvoiding(20)){}
	else if (WallTracer_right()){}
	else {
		WheelLeft=4;WheelRight=4;
	}

	if (Time > 180){
			Teleport = 1;
	}
}
