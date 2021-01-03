///////////
// File: Movements/WallAvoiding.c
static bool world1wallAvoiding(){
	if (US_Front < 15 && US_Left < 15 && US_Right < 20){
		WheelLeft=-4; WheelRight=4;
	}


	else if (US_Front < 15){

        if ((270 <= Compass && Compass < 360) &&
            (90 < Compass && Compass <= 180)){ //Slanted towards right
                WheelLeft=4;WheelRight=-4;//Turn Left
            }
        else{
            WheelLeft=-4;WheelRight=4;//Turn Right
        }
            //WheelLeft=-5;WheelRight=5;//Turn Right
		//printf("Front");
	}
	else if (US_Left < 20){
		WheelLeft=4;WheelRight=2;
		//printf("Left");
	}
	else if (US_Right < 20){
		WheelLeft=2;WheelRight=4;
		//printf("Right");
	}

	else{return false;}// No need to run
	return true; //Ran
}

static void reverse(){
    /*
    if ((270 <= Compass && Compass < 360) ||
            (90 < Compass && Compass <= 180)){ //Slanted towards right
                WheelLeft=4;WheelRight=0;//Turn Right
            }
        else{
            WheelLeft=0;WheelRight=4;//Turn Left
        }*/
        WheelLeft=-2;WheelRight=-1;
        Duration=2;
}


bool wallAvoiding(int dist)
{
	if (US_Front < dist+10 && US_Left < dist && US_Right < dist){
		//reverse();
		WheelLeft=4;WheelRight=-4; //Full Turn
		//printf("Corner");
	}
	/*
	else if (US_Left<40&&US_Right<40 &&US_Front>50) // go through wall
	{
		if (US_Left<15)
		{
			WheelLeft=5;
			WheelRight=4;
		}
		else if (US_Right<15)
		{
			WheelLeft=5;
			WheelRight=4;
		}
		else
		{
			WheelLeft=5;
			WheelRight=5;
		}

	}
	*/else if (US_Left < dist){
		//reverse();
		WheelLeft=4;WheelRight=2;
		//printf("Left");
	}
	else if (US_Right < dist){
		//reverse();
		WheelLeft=2;WheelRight=4;
		//printf("Right");
	}
	else if (US_Front < dist){
        //reverse();
        WheelLeft=-5;WheelRight=-5;//Turn Right
		//printf("Front");
	}

	else{return false;}// No need to run
	return true; //Ran
}
