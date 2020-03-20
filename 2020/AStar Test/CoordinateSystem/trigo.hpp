int PositionX1=0, PositionY1=0;

double dabs (double x){
    if (x<0){return -x;}
    return x;
}
bool xreached(int x,int range){
	return (x-range<=PositionX1 && PositionX1 <= x+range);
}
bool yreached(int y,int range){
	return (y-range<=PositionY1 && PositionY1 <= y+range);
}
bool reached(int x,int y,int rangex, int rangey){
	return ((x-rangex<=PositionX1 && PositionX1 <= x+rangex) &&
	    (y-rangey<=PositionY1 && PositionY1 <= y+rangey));
}

// void rotateTo(int x, int y){trigo(x, y, PositionX, PositionY);}
// int colorSensorX = PositionX, colorSensorY = PositionY;
// void rotateToSuper(int x, int y){trigo(x, y, colorSensorX, colorSensorY);}


//////Samuel's Trigo/////////////////////////////////////////////////////////////////////
class SamuelTrigo{
	public:

 int minSpeed=5,maxSpeed=5;
 int theta=-1,AngleDiff,CWAngleDiff,ACWAngleDiff;
void speed(int left, int right){
	WheelLeft=left;WheelRight=right;
}
  void turnToAngle(int targetAngle)
{
	//must have set minSpeed AND maxSpeed BEFORE CALLING THIS FUNC
	if(Compass>=targetAngle)
	{
		CWAngleDiff=Compass-targetAngle;
		ACWAngleDiff=360-(Compass-targetAngle);
	}
	else //Compass<targetAngle
	{
		ACWAngleDiff=targetAngle-Compass;
		CWAngleDiff=360-(targetAngle-Compass);
	}

	if(CWAngleDiff<=ACWAngleDiff) speed(maxSpeed,minSpeed);//turn clockwise
	else if(ACWAngleDiff<CWAngleDiff) speed(minSpeed,maxSpeed);//turn anti-clockwise
	else speed(maxSpeed,maxSpeed);//move forward
}

void reduceSpeeds(int& spd1, int& spd2)
{
	spd1 = spd1>=0 ? spd1/2+1 : spd1/2-1;
	spd2 = spd2>=0 ? spd2/2+1 : spd2/2-1;
}

  void calcTheta(int originX, int originY, int targetX, int targetY)
{
	const int deltaX = targetX - originX;
	const int deltaY = targetY - originY;
		 if (deltaX==0 && deltaY>0) theta = 0;
	else if (deltaX<0 && deltaY==0) theta = 90;
	else if (deltaX<0 && deltaY>0)  theta = 90 - (int)round(atan((double)abs(deltaY)/abs(deltaX))*180/PI);
	else if (deltaX<0 && deltaY<0)  theta = 90 + (int)round(atan((double)abs(deltaY)/abs(deltaX))*180/PI);
	else if (deltaX==0 && deltaY<0) theta = 180;
	else if (deltaX>0 && deltaY<0)  theta = 270 - (int)round(atan((double)abs(deltaY)/abs(deltaX))*180/PI);
	else if (deltaX>0 && deltaY==0) theta = 270;
	else if (deltaX>0 && deltaY>0)  theta = 270 + (int)round(atan((double)abs(deltaY)/abs(deltaX))*180/PI);
}
bool isOnSwamp(){
	return colorCheck(w2Obj.slowarea, 10);
}
 void trigo(int targetX, int targetY, int PositionX1, int PositionY1)
{
	calcTheta(PositionX1, PositionY1, targetX, targetY);
	AngleDiff=abs(Compass-theta);
	if(AngleDiff>180) AngleDiff=360-AngleDiff;
	if(AngleDiff>=130&&AngleDiff<=180)
	{
		minSpeed=-4;
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-4;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=80&&AngleDiff<130)
	{
		minSpeed=-3;
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-4;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=30&&AngleDiff<80)
	{
		minSpeed=1;//1
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-3;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=15&&AngleDiff<30)
	{
		minSpeed=2;
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-3;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=5&&AngleDiff<15)
	{
		minSpeed=4;
		maxSpeed=5;
	}
	else if(AngleDiff<5)
	{
		minSpeed=5;
		maxSpeed=5;
		if (w2Obj.LoadedObjects >3){
			minSpeed=3;
			maxSpeed=3;
		}
	}
	else //failsafe
	{
		minSpeed=-3;
		maxSpeed=-3;
	}
	//if(US_Front<=FRONT_MOVE_BACK+10) reduceSpeeds(minSpeed,maxSpeed);
	turnToAngle(theta);
}
};
SamuelTrigo st;

////Trigonometry///////////////////////////////////////////////
//Calculate angle from current position to target location
double angle(int x, int y,int posX, int posY){
	double Ychange = (y-posY); double Xchange = (x-posX);
	if (Xchange == 0 && Ychange > 0){return 0;}
	if (Xchange == 0 && Ychange < 0){return 180;}

	//Basic angle
	int theta = abs(atan(Ychange/Xchange)/(2*3.14159265358979323846) * 360);

    //Convert theta to Degress format output by the compass:
    //        0 degrees upward, goes anticlockwise to 359 degrees
	//First quadrant
	if (Ychange>0 && Xchange>0){theta = 270+theta;}
	//Second quadrant
	else if (Ychange>=0 && Xchange<0){theta = 90-theta;}
	//Third quadrant
	else if (Ychange<0 && Xchange<0){theta = 90+theta;}
	//Fourth quadrant
	else if (Ychange<=0 && Xchange>0){theta = 270-theta;}
	return theta;
}
//Turn and move at target angle
void rotateRobot(double theta){
	double AngleDiff = abs(Compass-theta);

    if(AngleDiff>180){AngleDiff=360-AngleDiff;}

    //Set the degree to turn to
    int faster = 0, smaller = 0;
    if (AngleDiff<5){faster=4;smaller=4;} // Go Straight
    else if (AngleDiff<15){faster=4;smaller=3;}
    else if (AngleDiff<30){faster=4;smaller=2;}
    else if (AngleDiff<80){faster=3;smaller=1;}
    else if (AngleDiff<130){faster=3;smaller=-3;}
    else if (AngleDiff<180){faster=5;smaller=-4;}
    else{faster=4;smaller=0;} //Failsafe

    //turn to theta
    //step 1: determine clockwise and anti-clockwise angle difference
    double CWAngleDiff, ACWAngleDiff; //Clockwise, Anticlockwise
    if(Compass>theta){
        CWAngleDiff=Compass-theta;
        ACWAngleDiff=360-(Compass-theta);
    }else if(theta>Compass){
        ACWAngleDiff=theta-Compass;
        CWAngleDiff=360-(theta-Compass);
    }else{
        ACWAngleDiff=0;
        CWAngleDiff=0;
    }

    //step 2: determine if CWAngleDiff or ACWAngleDiff is lower
    if(CWAngleDiff<ACWAngleDiff || CWAngleDiff==180){//turn clockwise
        WheelLeft=faster;WheelRight=smaller;//clockwise(theta);
    }
    else if(ACWAngleDiff<CWAngleDiff){ //turn anti-clockwise
        WheelLeft=smaller;WheelRight=faster;//aclockwise(theta);
    }
}

void rotateTo(int x, int y){
    //st.trigo(x, y, PositionX1, PositionY1);
    rotateRobot(angle(x,y, PositionX,PositionY));
}
int colorSensorX = PositionX1, colorSensorY = PositionY1;
void rotateToSuper(int x, int y){
    //if(reached(x,y,10,10)){WheelLeft=0;WheelRight=0;}
    //else{
	//rotateRobot(angle(x,y, PositionX1,PositionY1));
	st.trigo(x, y, PositionX1, PositionY1);
}
void rotateToFAST(int x, int y){
	//rotateRobot(angle(x, y, PositionX1, PositionY1));
    st.trigo(x, y, PositionX1, PositionY1);
}
