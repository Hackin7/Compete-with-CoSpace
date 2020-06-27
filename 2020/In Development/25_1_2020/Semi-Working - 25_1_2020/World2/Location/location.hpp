class Map{
	public:
	//Colour Values
	const int unexplored = -1;
	const int predictedEmpty = -2;
	const int empty = 0;
	const int deposit = 1;
	const int red = 2;
	const int blue = 3;
	const int black = 4;
	const int redBlue=10;
	const int redBlack = 11;
	const int blueBlack = 12;
	const int redBlueBlack = 13;
	const int wall = 5;
	const int border = 6;
	const int trapBorder = 7;
	const int trap = 8;
	const int slow = 9;

	bool toAvoidTrap = true;
	int map[width][height];
	bool visited[width][height];
	const int v = width*height;

	Map(){
		for (int i=0; i<width; i++){
			for (int j=0;j<height; j++)
				map[i][j] = unexplored;
		}
	}
	Map(int mapData[width][height]){
		for (int i=0; i<width; i++){
			for (int j=0;j<height; j++){
				map[i][j] = mapData[i][j];
				if (mapData[i][j] != unexplored){
					visited[i][j] = true;
				}
				else{visited[i][j] = false;}
			}
		}
	}

	////Getter////////////////////////////////////////////////////
	bool isVisited(int i, int j){return visited[i][j];}
	bool isRed(int val){
		return  val == red ||
				val == redBlue ||
				val == redBlack ||
				val == redBlueBlack;
	}
	bool isBlue(int val){
		return  val == blue ||
				val == redBlue ||
				val == blueBlack ||
				val == redBlueBlack;
	}
	bool isBlack(int val){
		return  val == black ||
				val == blueBlack ||
				val == redBlack ||
				val == redBlueBlack;
	}
	int getPixel(int i, int j){return map[i][j];}
	bool isVal(int i, int j, int val){return map[i][j] == val;}
	bool isWalkableVal(int val){
		return  val == unexplored ||
				val == empty ||
				val == deposit ||
				val == red ||
				val == blue ||
				val == black;
	}
	bool isWalkablePixel(int i, int j){
		return  isWalkableVal(getPixel(i,j));
	}
	int valCost(int val){
		if (isWalkableVal(val)){
				return 1;
			}
		if (val == wall){
			return v;
		}
		if (val == slow){
				return v/3;//50;
		}
		if (val == trap){
			if (toAvoidTrap){return v;}
			else{return 10;}
		}
		if (val == border){
			return v/3;//40;
		}
		return v;
	}
	////Setter////////////////////////////////////////////////////
	void reset(int mapData[width][height]){
		for (int i=0; i<width; i++){
			for (int j=0;j<height; j++)
				map[i][j] = mapData[i][j];
		}
	}
	void setPixel(int i, int j, int val){
		map[i][j] = val;
	}
	void rectfill(int x1,int x2,int y1,int y2, int color)
	{
		for (int x=x1; x <= x2; x++){
			for (int y=y1; y<= y2; y++){
			map[x][y]=color;
			visited[x][y] = true;
			}
		}
	}

	void squareFill(int x, int y, int val,int len)
	{
	  int x1=x - len;
	  int x2=x + len;
	  int y1=y - len;
	  int y2=y + len;
	  if (x1 < 0){x1=0;}
	  if (x2 > 480){x2=480;}
	  if (y1 < 0){y1=0;}
	  if (y2 > 270){y2=270;}
	  rectfill(x1,x2,y1,y2,val);
	}

};

Map location(layout);
//Map location;