//Jason Hui
//Fall Quarter 2016
//Project 1-5 - ECS175


#include <GL/glut.h>
#include <iostream> 
#include <vector>
#include <string>
#include <stdio.h>
#include <math.h>
#include <cstdlib> 
#include <fstream>

using namespace std; 

float *PixelBuffer; 
float *PixelBufferBlank; 

//subwindows
float *PixelBufferXY;
float *PixelBufferXZ;
float *PixelBufferYZ;

void display(); 
//Jason Hui GLOBAL VARIABLES START
int PixelSize = 3; 
int counting = 0; 
int sidelining = 0; 
int x =0; 
int y = 0; 
int lineStartX = 0; 
int lineStartY = 0; 
int lineEndX = 0; 
int lineEndY = 0; 

int mainWindowSizeWidth = 0;
int mainWindowSizeHeight = 0; 
int TotalSize = (mainWindowSizeWidth * mainWindowSizeHeight* 3 ) ;

bool colorShortCut = false;

int polygonStorageSize = 29;
//readText *readTextArray[200]; //up to 200 commands at once if needed. 
//readTextArraySize = 200; 
class readText
{
	public: 
	int integer;
	string words; 
	bool status; 
	readText()
	{
		integer = 0;
		words = "";
		status = false; 
	}



};
//Jason Hui GLOBAL VARIABLES END
//Jason Functions: START


//***************************OnScreen PixelXZ**********************************
//********************                          *******************************
//**********                                                   ****************
//*****************************************************************************
class onScreenPixelXZ
{//Start onScreenPixel
					public: 
						int x; 
						int y; 	
						int z; 
						int	screenWidth;
						int	screenHeight;
						//for later to match shape ID's
						string belongToPoly;
						bool turnStatus;
						bool isEdge;
						bool isInnerLining;
						

						int intensity; 
						bool isPoint;
						bool isColor; 
						onScreenPixelXZ()
						{
							x=0;
							y=0;
							z = 0; 
							turnStatus= false; 
							isEdge = false;
							isInnerLining = false; 
							isColor = false; 
							screenWidth = 0;
							screenHeight = 0;//may want to default it, to Screen size and width 
							belongToPoly = "";
							isColor = false;
							//proj3 
							intensity = 0; 
						};
												onScreenPixelXZ(int setX, int setY, bool onOrOff, int WindowWidth, int WindowHeight)
												{   //This defaults turns it to White
													x = setX;
													y = setY;
													turnStatus = onOrOff; 
													//because it becomes an edge //needs to set as Edge. 
													isEdge = false; 
													//only can be infected, by the infected algorithm
													isInnerLining = false;
													screenWidth = WindowWidth; 
													screenHeight = WindowHeight; 
												//	belongToPoly = inputName; 
													PixelBufferXZ[(  getX() * 3       ) + (   getY()* WindowWidth * 3  )  ] = 1 ; //for just red, 
													PixelBufferXZ[(  (getX()*3)+1   ) + (   getY()* WindowWidth * 3  )  ] = 1 ; // green
													PixelBufferXZ[(  (getX()*3)+2   ) + (   getY()* WindowWidth  * 3 )  ] = 1 ; //blue 
												};
												onScreenPixelXZ(int setX, int setY, bool onOrOff, int WindowWidth, int WindowHeight, string inputName)
												{   //This defaults turns it to White
													x = setX;
													y = setY;
													turnStatus = onOrOff; 
													//because it becomes an edge //needs to set as Edge. 
													isEdge = false; 
													//only can be infected, by the infected algorithm
													isInnerLining = false;
													screenWidth = WindowWidth; 
													screenHeight = WindowHeight; 
													belongToPoly = inputName; 
													PixelBufferXZ[(  getX() * 3       ) + (   getY()* WindowWidth * 3  )  ] = 1 ; //for just red, 
													PixelBufferXZ[(  (getX()*3)+1   ) + (   getY()* WindowWidth * 3  )  ] = 1 ; // green
													PixelBufferXZ[(  (getX()*3)+2   ) + (   getY()* WindowWidth  * 3 )  ] = 1 ; //blue 
												};
						int getX();
						int getY();

						void turnOFF(); 
						void turnRed();
						void turnGreen();
						void turnBlue();
						void turnPurple();
						void turnYellow(); 
						void turnCyan(); 
						void turnWhite(); 
						void setBelongToPoly(string inputName); 

						string getBelongToPoly();

						void setIsEdge(bool trueFalse);
						void setIsInnerLining(bool setIt); 
						bool getIsEdge();
						bool getIsInnerLining(); 

};//End onScreenPixel
int onScreenPixelXZ::getX()
					{return x;};
int onScreenPixelXZ::getY()
					{return y;};

void onScreenPixelXZ::turnWhite()
					{
						turnStatus = false; 
						PixelBufferXZ[(  getX()*3           ) + (   getY()* screenWidth * 3  )  ] = 1 ; //for just red, 
						PixelBufferXZ[(  (getX()*3)+1       ) + (   getY()* screenWidth * 3  )  ] = 1 ; // green
						PixelBufferXZ[(  (getX()*3)+2       ) + (   getY()* screenWidth  * 3 )  ] = 1 ; //blue 
					}
void onScreenPixelXZ::turnOFF()
					{
						turnStatus = false; 
						PixelBufferXZ[(  getX()*3           ) + (   getY()* screenWidth * 3  )  ] = 0 ; //for just red, 
						PixelBufferXZ[(  (getX()*3)+1       ) + (   getY()* screenWidth * 3  )  ] = 0 ; // green
						PixelBufferXZ[(  (getX()*3)+2       ) + (   getY()* screenWidth  * 3 )  ] = 0 ; //blue 
					}
void onScreenPixelXZ::turnRed()
					{
						turnStatus = true; 
						isColor = true; 
						PixelBufferXZ[(  getX()*3           ) + (   getY()* screenWidth * 3  )  ] = 1 ; //for just red, 
						PixelBufferXZ[(  (getX()*3)+1       ) + (   getY()* screenWidth * 3  )  ] = 0; // green
						PixelBufferXZ[(  (getX()*3)+2       ) + (   getY()* screenWidth  * 3 )  ] = 0 ; //blue 
					}

void onScreenPixelXZ::turnGreen()
					{

					//	cout<<"turning blue at point "<< getX() <<","<<getY() <<endl; 
						turnStatus = true; 
							isColor = true; 
						PixelBufferXZ[(  getX() * 3           ) + (   getY()* screenWidth * 3  )  ] = 0 ; //for just red, 
						PixelBufferXZ[(  (getX() *3) +1       ) + (   getY()* screenWidth * 3  )  ] = 1 ; // green
						PixelBufferXZ[(  (getX() *3) +2       ) + (   getY()* screenWidth  * 3 )  ] = 0 ; //blue 
					}

void onScreenPixelXZ::turnBlue()
					{

					//	cout<<"turning blue at point "<< getX() <<","<<getY() <<endl; 
						turnStatus = true; 
							isColor = true; 
						PixelBufferXZ[(  getX() * 3           ) + (   getY()* screenWidth * 3  )  ] = 0 ; //for just red, 
						PixelBufferXZ[(  (getX() *3) +1       ) + (   getY()* screenWidth * 3  )  ] = 0 ; // green
						PixelBufferXZ[(  (getX() *3) +2       ) + (   getY()* screenWidth  * 3 )  ] = 1 ; //blue 
					}

void onScreenPixelXZ::turnPurple()
					{

						//cout<<"turning blue at point "<< getX() <<","<<getY() <<endl; 
						turnStatus = true; 
							isColor = true; 
						PixelBufferXZ[(  getX() * 3           ) + (   getY()* screenWidth * 3  )  ] = 1 ; //for just red, 
						PixelBufferXZ[(  (getX() *3) +1       ) + (   getY()* screenWidth * 3  )  ] = 0 ; // green
						PixelBufferXZ[(  (getX() *3) +2       ) + (   getY()* screenWidth  * 3 )  ] = 1 ; //blue 
					}

void onScreenPixelXZ::turnYellow()
					{

					//	cout<<"turning blue at point "<< getX() <<","<<getY() <<endl; 
						//turnStatus = true; 
						//	isColor = true; 
						PixelBufferXZ[(  getX() * 3           ) + (   getY()* screenWidth * 3  )  ] = 1 ; //for just red, 
						PixelBufferXZ[(  (getX() *3) +1       ) + (   getY()* screenWidth * 3  )  ] = 1 ; // green
						PixelBufferXZ[(  (getX() *3) +2       ) + (   getY()* screenWidth  * 3 )  ] = 0 ; //blue 
					}
void onScreenPixelXZ::turnCyan()
					{

					//	cout<<"turning blue at point "<< getX() <<","<<getY() <<endl; 
						turnStatus = true; 
							isColor = true; 
						PixelBufferXZ[(  getX() * 3           ) + (   getY()* screenWidth * 3  )  ] = 0 ; //for just red, 
						PixelBufferXZ[(  (getX() *3) +1       ) + (   getY()* screenWidth * 3  )  ] = 1 ; // green
						PixelBufferXZ[(  (getX() *3) +2       ) + (   getY()* screenWidth  * 3 )  ] = 1 ; //blue 
					}

void onScreenPixelXZ::setIsEdge(bool trueFalse)
{
	isEdge = trueFalse; 
}
void onScreenPixelXZ::setIsInnerLining(bool setIt)
{
	isInnerLining = setIt; 
}
bool onScreenPixelXZ::getIsEdge()
{   
	return isEdge; 
}
bool onScreenPixelXZ::getIsInnerLining()
{
	return isInnerLining; 
}
void onScreenPixelXZ::setBelongToPoly(string inputName)
{
	belongToPoly = inputName; 
}

string onScreenPixelXZ::getBelongToPoly()
{
	return belongToPoly; 
}

//********************     *OnScreen PixelYZ                     *******************************
//**********                                                   ****************
//*****************************************************************************//********************                          *******************************
//**********                                                   ****************
//*****************************************************************************

//***************************OnScreen PixelYZ**********************************
//********************                          *******************************
//**********                                                   ****************
//*****************************************************************************

class onScreenPixelYZ
{//Start onScreenPixel
					public: 
						int x; 
						int y; 	
						int z; 
						int	screenWidth;
						int	screenHeight;
						//for later to match shape ID's
						string belongToPoly;
						bool turnStatus;
						bool isEdge;
						bool isInnerLining;
						bool isPoint;
						bool isColor; 
						onScreenPixelYZ()
						{
							x=0;
							y=0;
							z = 0; 
							turnStatus=false; 
							isEdge = false;
							isInnerLining = false; 
							screenWidth = 0;
							screenHeight = 0;//may want to default it, to Screen size and width 
							belongToPoly = "";
							isColor = false; 
						};
												onScreenPixelYZ(int setX, int setY, bool onOrOff, int WindowWidth, int WindowHeight)
												{   //This defaults turns it to White
													x = setX;
													y = setY;
													turnStatus = onOrOff; 
													//because it becomes an edge //needs to set as Edge. 
												
													isEdge= false; 
													//only can be infected, by the infected algorithm
													isInnerLining = false;
													isColor = false; 
													screenWidth = WindowWidth; 
													screenHeight = WindowHeight; 
												//	belongToPoly = inputName; 
													PixelBufferYZ[(  getX() * 3       ) + (   getY()* WindowWidth * 3  )  ] = 1 ; //for just red, 
													PixelBufferYZ[(  (getX()*3)+1   ) + (   getY()* WindowWidth * 3  )  ] = 1 ; // green
													PixelBufferYZ[(  (getX()*3)+2   ) + (   getY()* WindowWidth  * 3 )  ] = 1 ; //blue 
												};
												onScreenPixelYZ(int setX, int setY, bool onOrOff, int WindowWidth, int WindowHeight, string inputName)
												{   //This defaults turns it to White
													x = setX;
													y = setY;
													turnStatus = onOrOff; 
													//because it becomes an edge //needs to set as Edge. 
														
													isEdge= false; 
													//only can be infected, by the infected algorithm
													isInnerLining = false;
													screenWidth = WindowWidth; 
													screenHeight = WindowHeight; 
													belongToPoly = inputName; 
													PixelBufferYZ[(  getX() * 3       ) + (   getY()* WindowWidth * 3  )  ] = 1 ; //for just red, 
													PixelBufferYZ[(  (getX()*3)+1   ) + (   getY()* WindowWidth * 3  )  ] = 1 ; // green
													PixelBufferYZ[(  (getX()*3)+2   ) + (   getY()* WindowWidth  * 3 )  ] = 1 ; //blue 
												};
						int getX();
						int getY();

						void turnOFF(); 
						void turnRed();
						void turnGreen();
						void turnBlue();
						void turnPurple();
						void turnYellow(); 
						void turnCyan(); 

						void setBelongToPoly(string inputName); 

						string getBelongToPoly();

						void setIsEdge(bool trueFalse);
						void setIsInnerLining(bool setIt); 
						bool getIsEdge();
						bool getIsInnerLining(); 

};//End onScreenPixel
int onScreenPixelYZ::getX()
					{return x;};
int onScreenPixelYZ::getY()
					{return y;};
void onScreenPixelYZ::turnOFF()
					{
						turnStatus = false; 
						PixelBufferYZ[(  getX()*3           ) + (   getY()* screenWidth * 3  )  ] = 0 ; //for just red, 
						PixelBufferYZ[(  (getX()*3)+1       ) + (   getY()* screenWidth * 3  )  ] = 0 ; // green
						PixelBufferYZ[(  (getX()*3)+2       ) + (   getY()* screenWidth  * 3 )  ] = 0 ; //blue 
					}
void onScreenPixelYZ::turnRed()
					{
						turnStatus = true; 
						isColor = true; 
						PixelBufferYZ[(  getX()*3           ) + (   getY()* screenWidth * 3  )  ] = 1 ; //for just red, 
						PixelBufferYZ[(  (getX()*3)+1       ) + (   getY()* screenWidth * 3  )  ] = 0; // green
						PixelBufferYZ[(  (getX()*3)+2       ) + (   getY()* screenWidth  * 3 )  ] = 0 ; //blue 
					}

void onScreenPixelYZ::turnGreen()
					{

					//	cout<<"turning blue at point "<< getX() <<","<<getY() <<endl; 
						turnStatus = true; 
							isColor = true; 
						PixelBufferYZ[(  getX() * 3           ) + (   getY()* screenWidth * 3  )  ] = 0 ; //for just red, 
						PixelBufferYZ[(  (getX() *3) +1       ) + (   getY()* screenWidth * 3  )  ] = 1 ; // green
						PixelBufferYZ[(  (getX() *3) +2       ) + (   getY()* screenWidth  * 3 )  ] = 0 ; //blue 
					}

void onScreenPixelYZ::turnBlue()
					{

					//	cout<<"turning blue at point "<< getX() <<","<<getY() <<endl; 
						turnStatus = true; 
							isColor = true; 
						PixelBufferYZ[(  getX() * 3           ) + (   getY()* screenWidth * 3  )  ] = 0 ; //for just red, 
						PixelBufferYZ[(  (getX() *3) +1       ) + (   getY()* screenWidth * 3  )  ] = 0 ; // green
						PixelBufferYZ[(  (getX() *3) +2       ) + (   getY()* screenWidth  * 3 )  ] = 1 ; //blue 
					}

void onScreenPixelYZ::turnPurple()
					{

						//cout<<"turning blue at point "<< getX() <<","<<getY() <<endl; 
						turnStatus = true; 
							isColor = true; 
						PixelBufferYZ[(  getX() * 3           ) + (   getY()* screenWidth * 3  )  ] = 1 ; //for just red, 
						PixelBufferYZ[(  (getX() *3) +1       ) + (   getY()* screenWidth * 3  )  ] = 0 ; // green
						PixelBufferYZ[(  (getX() *3) +2       ) + (   getY()* screenWidth  * 3 )  ] = 1 ; //blue 
					}

void onScreenPixelYZ::turnYellow()
					{

					//	cout<<"turning blue at point "<< getX() <<","<<getY() <<endl; 
					//	turnStatus = true; 
					//		isColor = true; 
						PixelBufferYZ[(  getX() * 3           ) + (   getY()* screenWidth * 3  )  ] = 1 ; //for just red, 
						PixelBufferYZ[(  (getX() *3) +1       ) + (   getY()* screenWidth * 3  )  ] = 1 ; // green
						PixelBufferYZ[(  (getX() *3) +2       ) + (   getY()* screenWidth  * 3 )  ] = 0 ; //blue 
					}
void onScreenPixelYZ::turnCyan()
					{

					//	cout<<"turning blue at point "<< getX() <<","<<getY() <<endl; 
						turnStatus = true; 
							isColor = true; 
						PixelBufferYZ[(  getX() * 3           ) + (   getY()* screenWidth * 3  )  ] = 0 ; //for just red, 
						PixelBufferYZ[(  (getX() *3) +1       ) + (   getY()* screenWidth * 3  )  ] = 1 ; // green
						PixelBufferYZ[(  (getX() *3) +2       ) + (   getY()* screenWidth  * 3 )  ] = 1 ; //blue 
					}

void onScreenPixelYZ::setIsEdge(bool trueFalse)
{
	isEdge = trueFalse; 
}
void onScreenPixelYZ::setIsInnerLining(bool setIt)
{
	isInnerLining = setIt; 
}
bool onScreenPixelYZ::getIsEdge()
{   
	return isEdge; 
}
bool onScreenPixelYZ::getIsInnerLining()
{
	return isInnerLining; 
}
void onScreenPixelYZ::setBelongToPoly(string inputName)
{
	belongToPoly = inputName; 
}

string onScreenPixelYZ::getBelongToPoly()
{
	return belongToPoly; 
}


//Keeps track, of All the pixels that are turned on/their color, maybe which shape it belongs too. 

//***************************OnScreen PixelXY- or normal display**********************************
//********************											   *******************************
//**********													                  ****************
//************************************************************************************************

class onScreenPixel
{//Start onScreenPixel
					public: 
						int x; 
						int y; 
						int z; 

						int normalX;
						int normalY;
						int normalZ; 
						int	screenWidth;
						int	screenHeight;
						//for later to match shape ID's
						string belongToPoly;

							bool turnStatus;


						bool isEdge;
						bool isInnerLining;
						bool isPoint;
						bool isColor; 
						onScreenPixel()
						{
							x=0;
							y=0;
							z=0; 
							normalX = 0; 
							normalY = 0;
							normalZ = 0; 
							turnStatus=false; 
							isEdge = false;
							isInnerLining = false; 
							screenWidth = 0;
							screenHeight = 0;//may want to default it, to Screen size and width 
							belongToPoly = "";
							isColor = false; 
						};
						onScreenPixel(int setX, int setY, int setZ, bool onOrOff, int WindowWidth, int WindowHeight)
						{   //This defaults turns it to White
							x = setX;
							y = setY;
							z = setZ; 
							turnStatus = onOrOff; 
								normalX = 0; 
							normalY = 0;
							normalZ = 0; 
							//because it becomes an edge 
							isEdge= false; 
							//only can be infected, by the infected algorithm
							isInnerLining = false;
							screenWidth = WindowWidth; 
							screenHeight = WindowHeight; 
							//this one is for normal, X-Y
							PixelBuffer[(  getX() * 3     ) + (   getY()* WindowWidth * 3  )  ] = 1 ; //for just red, 
							PixelBuffer[(  (getX()*3)+1   ) + (   getY()* WindowWidth * 3  )  ] = 1 ; // green
							PixelBuffer[(  (getX()*3)+2   ) + (   getY()* WindowWidth  * 3 )  ] = 1 ; //blue 

							//this one is for, XZ axis
					//		PixelBufferXZ[(  getX() * 3     ) + (   z* WindowWidth * 3  )  ] = 1 ; //for just red, 
						//	PixelBufferXZ[(  (getX()*3)+1   ) + (   z* WindowWidth * 3  )  ] = 1 ; // green
						//	PixelBufferXZ[(  (getX()*3)+2   ) + (   z* WindowWidth  * 3 )  ] = 1 ; //blue 
							isColor = false; 
						};

						onScreenPixel(int setX, int setY, bool onOrOff, int WindowWidth, int WindowHeight)
						{   //This defaults turns it to White
							x = setX;
							y = setY;
							turnStatus = onOrOff; 
							//because it becomes an edge 
							isEdge= false; 
							//only can be infected, by the infected algorithm
							isInnerLining = false;
							screenWidth = WindowWidth; 
							screenHeight = WindowHeight; 
							PixelBuffer[(  getX() * 3     ) + (   getY()* WindowWidth * 3  )  ] = 1 ; //for just red, 
							PixelBuffer[(  (getX()*3)+1   ) + (   getY()* WindowWidth * 3  )  ] = 1 ; // green
							PixelBuffer[(  (getX()*3)+2   ) + (   getY()* WindowWidth  * 3 )  ] = 1 ; //blue 
							isColor = false; 
						};
													onScreenPixel(int setX, int setY, bool onOrOff, int WindowWidth, int WindowHeight, string inputName)
												{   //This defaults turns it to White
													x = setX;
													y = setY;
													turnStatus = onOrOff; 
													//because it becomes an edge //needs to set as Edge. 
													isEdge= false; 
																//only can be infected, by the infected algorithm
													isInnerLining = false;
													screenWidth = WindowWidth; 
													screenHeight = WindowHeight; 
													belongToPoly = inputName; 
													PixelBuffer[(  getX() * 3       ) + (   getY()* WindowWidth * 3  )  ] = 1 ; //for just red, 
													PixelBuffer[(  (getX()*3)+1   ) + (   getY()* WindowWidth * 3  )  ] = 1 ; // green
													PixelBuffer[(  (getX()*3)+2   ) + (   getY()* WindowWidth  * 3 )  ] = 1 ; //blue 
												};
						int getX();
						int getY();

						void turnOFF(); 
						void turnRed();
						void turnGreen();
						void turnBlue();
						void turnPurple();
						void turnYellow(); 
						void turnCyan(); 
						void turnWhite(); 
						void setBelongToPoly(string inputName); 
						string getBelongToPoly();

						void setIsEdge(bool trueFalse);
						void setIsInnerLining(bool setIt); 
						bool getIsEdge();
						bool getIsInnerLining(); 

};//End onScreenPixel
int onScreenPixel::getX()
					{return x;};
int onScreenPixel::getY()
					{return y;};

void onScreenPixel::turnWhite()
					{
						turnStatus = false; 
						PixelBuffer[(  getX()*3           ) + (   getY()* screenWidth * 3  )  ] = 1 ; //for just red, 
						PixelBuffer[(  (getX()*3)+1       ) + (   getY()* screenWidth * 3  )  ] = 1 ; // green
						PixelBuffer[(  (getX()*3)+2       ) + (   getY()* screenWidth  * 3 )  ] = 1 ; //blue 
					}


void onScreenPixel::turnOFF()
					{
						turnStatus = false; 
						PixelBuffer[(  getX()*3           ) + (   getY()* screenWidth * 3  )  ] = 0 ; //for just red, 
						PixelBuffer[(  (getX()*3)+1       ) + (   getY()* screenWidth * 3  )  ] = 0 ; // green
						PixelBuffer[(  (getX()*3)+2       ) + (   getY()* screenWidth  * 3 )  ] = 0 ; //blue 
					}
void onScreenPixel::turnRed()
					{
						turnStatus = true; 
						isColor = true; 
						PixelBuffer[(  getX()*3           ) + (   getY()* screenWidth * 3  )  ] = 1 ; //for just red, 
						PixelBuffer[(  (getX()*3)+1       ) + (   getY()* screenWidth * 3  )  ] = 0; // green
						PixelBuffer[(  (getX()*3)+2       ) + (   getY()* screenWidth  * 3 )  ] = 0 ; //blue 
					}
void onScreenPixel::turnGreen()
					{

					//	cout<<"turning blue at point "<< getX() <<","<<getY() <<endl; 
						turnStatus = true; 
							isColor = true; 
						PixelBuffer[(  getX() * 3           ) + (   getY()* screenWidth * 3  )  ] = 0 ; //for just red, 
						PixelBuffer[(  (getX() *3) +1       ) + (   getY()* screenWidth * 3  )  ] = 1 ; // green
						PixelBuffer[(  (getX() *3) +2       ) + (   getY()* screenWidth  * 3 )  ] = 0 ; //blue 
					}

void onScreenPixel::turnBlue()
					{

					//	cout<<"turning blue at point "<< getX() <<","<<getY() <<endl; 
						turnStatus = true; 
							isColor = true; 
						PixelBuffer[(  getX() * 3           ) + (   getY()* screenWidth * 3  )  ] = 0 ; //for just red, 
						PixelBuffer[(  (getX() *3) +1       ) + (   getY()* screenWidth * 3  )  ] = 0 ; // green
						PixelBuffer[(  (getX() *3) +2       ) + (   getY()* screenWidth  * 3 )  ] = 1 ; //blue 
					}

void onScreenPixel::turnPurple()
					{

						//cout<<"turning blue at point "<< getX() <<","<<getY() <<endl; 
						turnStatus = true; 
							isColor = true; 
						PixelBuffer[(  getX() * 3           ) + (   getY()* screenWidth * 3  )  ] = 1 ; //for just red, 
						PixelBuffer[(  (getX() *3) +1       ) + (   getY()* screenWidth * 3  )  ] = 0 ; // green
						PixelBuffer[(  (getX() *3) +2       ) + (   getY()* screenWidth  * 3 )  ] = 1 ; //blue 
					}

void onScreenPixel::turnYellow()
					{

					//	cout<<"turning blue at point "<< getX() <<","<<getY() <<endl; 
						turnStatus = true; 
							isColor = true; 
						PixelBuffer[(  getX() * 3           ) + (   getY()* screenWidth * 3  )  ] = 1 ; //for just red, 
						PixelBuffer[(  (getX() *3) +1       ) + (   getY()* screenWidth * 3  )  ] = 1 ; // green
						PixelBuffer[(  (getX() *3) +2       ) + (   getY()* screenWidth  * 3 )  ] = 0 ; //blue 
					}
void onScreenPixel::turnCyan()
					{

					//	cout<<"turning blue at point "<< getX() <<","<<getY() <<endl; 
						turnStatus = true; 
							isColor = true; 
						PixelBuffer[(  getX() * 3           ) + (   getY()* screenWidth * 3  )  ] = 0 ; //for just red, 
						PixelBuffer[(  (getX() *3) +1       ) + (   getY()* screenWidth * 3  )  ] = 1 ; // green
						PixelBuffer[(  (getX() *3) +2       ) + (   getY()* screenWidth  * 3 )  ] = 1 ; //blue 
					}

void onScreenPixel::setIsEdge(bool trueFalse)
{
	isEdge = trueFalse; 
}
void onScreenPixel::setIsInnerLining(bool setIt)
{
	isInnerLining = setIt; 
}
bool onScreenPixel::getIsEdge()
{   
	return isEdge; 
}
bool onScreenPixel::getIsInnerLining()
{
	return isInnerLining; 
}
void onScreenPixel::setBelongToPoly(string inputName)
{
	belongToPoly = inputName; 
}

string onScreenPixel::getBelongToPoly()
{
	return belongToPoly; 
}
//Keeps track, of All the pixels that are turned on/their color, maybe which shape it belongs too. 




class polygoning
{
public:

	string Name; 
	int centerX;
	int centerY; 
	onScreenPixel *storage[2000][1200];
	onScreenPixel *vertices[500];
	int verticesSize; 

	polygoning(string name )
	{
		Name = name;
		
	}
	
	void erasepolygoning(); 
	void eraseVertices();
};

void polygoning::erasepolygoning()
{

		cout<<"...Erasing..Polygoning:"<<Name<<" ' " <<endl; 
		for(int i= 0; i < mainWindowSizeWidth; i++)
		   {
						for(int j= 0; j< mainWindowSizeHeight ; j++)
						{
							storage[i][j] = new onScreenPixel(i, j, false, mainWindowSizeWidth, mainWindowSizeHeight);
							storage[i][j]->turnOFF(); 
							storage[i][j]->setIsInnerLining(false);
							//cout<<" x test: "<<i <<" j test: " <<j<<endl; 
						};

				     };
				     //clearing up vertices
				     for(int i = 0; i < 30; i ++)
				     {
				     		vertices[i] =  new onScreenPixel(0,0, false, mainWindowSizeWidth, mainWindowSizeHeight); 
				     }
		cout<<"...Erasing..Poly. Finished! "<<endl; 
}


void polygoning::eraseVertices()
{    cout<<Name<< "-erasingVertices "<<endl; 
	  for(int i = 0; i < 30; i++)
			     {
			     		vertices[i] =  new onScreenPixel(0,0, false, mainWindowSizeWidth, mainWindowSizeHeight); 
			     }
}

onScreenPixel *PixelTracker[2000][1200];  
onScreenPixelXZ *PixelTrackerXZ[2000][1200];  
onScreenPixelYZ *PixelTrackerYZ[2000][1200];  



onScreenPixel *polyStorageOld[2000][1200]; 

polygoning *polygonStorage[30]; //stores up to 30 shapes
//This is for GratenHAMs???


//perfect bresenham!!! YAYYYYYYYYYYY 
void bresenhamLine(int beginX, int beginY, int endX, int endY)
				{			    //Makes background Blue for now.  
								//added same function to load initial. 
				
				lineStartX = beginX;
				lineStartY = beginY;
				lineEndX = endX;
				lineEndY = endY; 

								cout<<" line start is ("<<lineStartX <<","<<lineStartY<<")... lineEnd is: ("<<lineEndX<<","<<lineEndY<<")"<<endl; 
								PixelTracker[lineStartX][lineStartY] = new onScreenPixel(lineStartX, lineStartY, true, mainWindowSizeWidth, mainWindowSizeHeight); 
								PixelTracker[lineStartX][lineStartY]->turnRed(); 
							
								PixelTracker[ lineEndX ][ lineEndY ] = new onScreenPixel(lineEndX  , lineEndY  , true, mainWindowSizeWidth, mainWindowSizeHeight); 
								PixelTracker[ lineEndX ][ lineEndY ]->turnRed(); 
									
							cout<<" just checking that they made it"<<endl; 
							string blanking;
							glutPostRedisplay(); 
						

									double deltaY = ( lineEndY - lineStartY );
									double deltaX = ( lineEndX - lineStartX );		
									//this is the official P1 starting point 
							//		PNext = (2*deltaY)-  deltaX;
								//	PNow = (2*deltaY) -  deltaX; 
			
									double m;
									m = (double)(deltaY) / (double)deltaX; //putting doubles at the front help with the slope. 
									cout<< " m is: " << m <<endl;    
									//double PKplusone = 0;
									double PK = 0;

						
									double  Xnow;
									double Ynow; 







if(deltaY == 0)//horizontal line
{			int moveX, start_X, stopX; 
			if(deltaX < 0)
			{
				moveX = lineEndX;
				start_X = lineEndX; 

				stopX = lineStartX;


			}else
			{
				moveX = lineStartX;
				start_X = lineStartX; 

				stopX = lineEndX; 
			}

				for(moveX = start_X;moveX < stopX; moveX++)
				{
				PixelTracker[moveX][lineStartY] =  new onScreenPixel(moveX,lineStartY, true, mainWindowSizeWidth, mainWindowSizeHeight); 
				}
			
}

else if( deltaX == 0)//Vertical Line
{
		int moveY, start_Y,  stopY;
		if(deltaY<0)
		{

			moveY = lineEndY;
			start_Y = lineEndY; 
			stopY = lineStartY; 
		}else
		{

			moveY = lineStartY;
			start_Y = lineStartY; 
			stopY = lineEndY; 
		}

		for( moveY = start_Y ;moveY < stopY ; moveY++)
		{
PixelTracker[lineStartX][moveY] =  new onScreenPixel(lineStartX,moveY, true, mainWindowSizeWidth, mainWindowSizeHeight);
		}


}
else if(deltaX == 0 && deltaY == 0)//basically make a single point 
{


}
else if( m ==1)// diagonal lines??
{
	cout<<"trying out m== +1" <<endl; 
	int moveX, moveY, start_Y, start_X, stopX, stopY;

	if(lineStartX < lineEndX ) // covers TOP RIGHT
	{
		moveX = lineStartX;
		moveY = lineStartY;
		start_X = lineStartX;
		start_Y = lineStartY;
		stopX = lineEndX;
		stopY = lineEndY; 
	}
	else //covers bottom left
	{
			moveX = lineEndX;
		moveY = lineEndY;
		start_X = lineEndX;
		start_Y = lineEndY;
		stopX = lineStartX;
		stopY = lineStartY; 
	
	}

	moveY = start_Y; 
	for(moveX = start_X; moveX < stopX ; moveX++)
	{
	
		PixelTracker[moveX][moveY] =  new onScreenPixel(moveX,moveY, true, mainWindowSizeWidth, mainWindowSizeHeight);
		moveY++;
	}
	



}// end m = 1

else if (m == -1 )
{
	
cout<<" trying out m == -1"<<endl; 

		int moveX, moveY, start_Y, start_X, stopX, stopY;

	if(lineStartX < lineEndX ) // covers bottom right
	{
		moveX = lineStartX;
		moveY = lineStartY;
		start_X = lineStartX;
		start_Y = lineStartY;
		stopX = lineEndX;
		stopY = lineEndY; 
	}
	else //covers top Left
	{
		moveX = lineEndX;
		moveY = lineEndY;
		start_X = lineEndX;
		start_Y = lineEndY;
		stopX = lineStartX;
		stopY = lineStartY; 
	
	}

	moveY = start_Y; 
	for(moveX = start_X; moveX < stopX ; moveX++)
	{
	
		PixelTracker[moveX][moveY] =  new onScreenPixel(moveX,moveY, true, mainWindowSizeWidth, mainWindowSizeHeight);
		moveY--;
	}
	




}
//*********IF lineStartX is Smaller Than lineEndX************************
//*********              Forward the X's*         ********************
//*********IF lineStartX is Smaller Than lineEndX************************

else if(deltaX > 0 )
{		//START if deltaX > 0; 

		 if( m > 0 && m <1 )
		{//START - m > 0 && m <1 
					PK = (2*deltaY)-  deltaX;			
			
					if( lineStartX > lineEndX)
					{
						Xnow = lineEndX;
						Ynow  = lineEndY; 
						lineEndX = lineStartX; 
					}else
					{
						Xnow = lineStartX;
						Ynow = lineStartY; 
					}			 
						//This takes care of 0< x< 1 
						for(Xnow = lineStartX; Xnow < lineEndX; Xnow++)
						{											
								if( PK < 0 )
								{
									PK = PK + (2* deltaY); 
								}else
								{
									Ynow++; 
									PK = PK +  2* (deltaY - deltaX); 								
								}
		PixelTracker[(int)Xnow][(int)Ynow] =  new onScreenPixel((int)Xnow,(int) Ynow, true, mainWindowSizeWidth, mainWindowSizeHeight); 
						}//end For loop 
		}//end - m > 0 && m <1 								
										
		else if( m >1 )
		{//START - m <1 

						
			cout<<" tried to come here?  m > 1 "<<endl; 
			  int tempStartX = lineStartX, tempStartY = lineStartY, tempEndX = lineEndX,tempEndY =lineEndY; 

				  lineStartX = tempStartY;
				  lineStartY = tempStartX;
				  lineEndX = tempEndY; 
				  lineEndY = tempEndX; 	  
				  double tempDeltaY = deltaY, tempDeltaX = deltaX; 
				  deltaY = tempDeltaX; 
				  deltaX = tempDeltaY; 
				  PK = (2*deltaY)-  deltaX;
										if( lineStartX > lineEndX)
										{
											Xnow = lineEndX;
											Ynow  = lineEndY; 
											lineEndX = lineStartX; 

										}else
										{
											Xnow = lineStartX;
											Ynow = lineStartY; 
										}

										//This takes care of 0< x< 1 
										//while(Xnow < lineEndX)
										for(Xnow = lineStartX ; Xnow < lineEndX; Xnow++)
										{
															if( PK < 0 )
															{
																PK = PK + (2* deltaY); 
															}else
															{
																Ynow++; 
																PK = PK + (  2* (deltaY - deltaX) ); 
															}
															//Here remember to change because Ynow is Xnow, and Xnow is Y now
															// so everthing here is the same, but MUST flip here 
				PixelTracker[(int)Ynow][(int)Xnow] =  new onScreenPixel((int)Ynow,(int) Xnow, true, mainWindowSizeWidth, mainWindowSizeHeight); 
										}//end For loop
										
				}// End M > 1 			
										
										
		else if( m <  0 && m > (-1) )
		{//START - m > 0 && m <1 


						PK = (2*(-deltaY))-  deltaX;
			cout<<"activate negative steap slope thing"<<endl; 
		/*							
			if( lineStartX > lineEndX)
										{
											Xnow = lineEndX;
											Ynow  = lineEndY; 
											lineEndX = lineStartX; 

										}else
										{
											Xnow = lineStartX;
											Ynow = lineStartY; 
										}
										*/

										Xnow = lineEndX;
										Ynow = lineEndY; 
										//This takes care of 0< x< 1 
										// this will make it go backwards, and switching Xnow starting at X lineEndX
										for(Xnow = lineEndX ; Xnow >lineStartX ; Xnow--)
										{			
															if( PK < 0 )
															{
																PK  = PK + ( 2* (-deltaY)); 
															}else
															{
																//here is the main change from   0<m<1
																Ynow++; 
																PK  = PK +  ( 2* (  (-deltaY) - deltaX) ); 
															}
		PixelTracker[(int)Xnow][(int)Ynow] =  new onScreenPixel((int)Xnow,(int) Ynow, true, mainWindowSizeWidth, mainWindowSizeHeight); 
										}//end For loop
		}//end - m > 0 && m <1 								
													
					
		else if( m <1  )
		{//START - M <1 so m is a STEEP negative slope
									cout<<" Steep Negative Slope "<<endl; 
									PK = (2*deltaX)-  (- deltaY);
									//This takes care of 0< x< 1 
									Ynow = lineEndY; 
									Xnow = lineEndX; 
					
									for(Ynow = lineEndY; Ynow < lineStartY; Ynow++)
										{
															if( PK < 0 )
															{
																PK = PK + (2* deltaX); 
										
															}else
															{
																Xnow--; 
																PK = PK + ( 2* (deltaX - (-deltaY)) ); 
															}
															//Here remember to change because Ynow is Xnow, and Xnow is Y now
															// so everthing here is the same, but MUST flip here 
		PixelTracker[(int)Xnow][(int)Ynow] =  new onScreenPixel((int)Xnow,(int) Ynow, true, mainWindowSizeWidth, mainWindowSizeHeight); 
										}//end For loop
				}// End M < -1 Super Steep Negative Slope 		
										
}//END if deltaX > 0 


//*********IF lineEndX is Small Thank lineStartX************************
//*********               Reverse the X's*         *********************
//*********               Reverse the X's*         *********************
//*********               Reverse the X's*         *********************
//*********IF lineEndX is Small Thank lineStartX************************
//*********IF lineEndX is Small Thank lineStartX************************
else if( deltaX < 0 )
{ //START if deltaX < 0 
					//deltaX = (-deltaX); //make it positive, 
				//then execute all of the same algorithms above, but switch lineStartX lineStart Y with lineEndX lineEndY
								int tempLineStartX = lineStartX;
								int tempLineStartY = lineStartY;
								int tempLineEndX   = lineEndX;
							   	int tempLineEndY   = lineEndY; 

								 lineStartX = tempLineEndX;
								 lineStartY = tempLineEndY; 
								 lineEndX   = tempLineStartX; 
								 lineEndY   = tempLineStartY; 

								double deltaY = ( lineEndY - lineStartY );
								double deltaX = ( lineEndX - lineStartX );

							    m = (double)(deltaY) / (double)deltaX; //putting doubles at the front help with the slope. 
								cout<< " after deltaX < 0 flip it, m is: " << m <<endl; 


	if( m > 0 && m <1 )
		{//START - m > 0 && m <1 
				PK = (2*deltaY)-  deltaX;			
										 
				Xnow = lineStartX;
				Ynow = lineStartY; 
																		//This takes care of 0< x< 1 
				//while(Xnow < lineEndX)
				for(Xnow = lineStartX; Xnow <lineEndX; Xnow++)
				{
				
					if( PK < 0 )
					{
						PK = PK + (2* deltaY); 
									
					}else
						{
						Ynow++; 
						PK = PK + ( 2* (deltaY - deltaX)); 
									
						}
	PixelTracker[(int)Xnow][(int)Ynow] =  new onScreenPixel((int)Xnow,(int) Ynow, true, mainWindowSizeWidth, mainWindowSizeHeight); 

				}//end For loop
			}//end - m > 0 && m <1 								
				


	else if( m >1 )
		{//START - m <1 										
			cout<<" Steep positive -reverse X's -   m > 1 "<<endl; 
		 int tempStartX = lineStartX, tempStartY = lineStartY, tempEndX = lineEndX,tempEndY =lineEndY; 

			lineStartX = tempStartY;
			lineStartY = tempStartX;
		  lineEndX = tempEndY; 
			 lineEndY = tempEndX; 
		  
		  double tempDeltaY = deltaY, tempDeltaX = deltaX; 

		  deltaY = tempDeltaX; 
		  deltaX = tempDeltaY; 

			PK = (2*deltaY)-  deltaX;

				if( lineStartX > lineEndX)
					{
					Xnow = lineEndX;
					Ynow  = lineEndY; 
					lineEndX = lineStartX; 

					}else
					{
					Xnow = lineStartX;
					Ynow = lineStartY; 
					}
					//This takes care of 0< x< 1 
				for(Xnow = lineStartX; Xnow < lineEndX; Xnow++)
				{	
					if( PK < 0 )
					{
					PK = PK + (2* deltaY); 
									
					}else
					{
						Ynow++; 
						PK = PK +  ( 2* (deltaY - deltaX) ); 
									
					}
		//Here remember to change because Ynow is Xnow, and Xnow is Y now
		// so everthing here is the same, but MUST flip here 
	PixelTracker[(int)Ynow][(int)Xnow] =  new onScreenPixel((int)Ynow,(int) Xnow, true, mainWindowSizeWidth, mainWindowSizeHeight); 

			}//end For loop	
	}// End M > 1 			
									
									
	else if( m <  0 && m > (-1) )
		{//START - m > 0 && m <1 

					PK = (2*(-deltaY))-  deltaX;
					cout<<"Reverse X's -  negative steap slope -  where it is between  -1 < m < 0"<<endl; 
					Xnow = lineEndX;
					Ynow = lineEndY; 
						//This takes care of 0< x< 1 
				
							// this will make it go backwards, and switching Xnow starting at X lineEndX
					for(Xnow = lineEndX ; Xnow > lineStartX ; Xnow--)
					{
											
							if( PK < 0 )
							{
							PK  = PK + ( 2* (-deltaY)); 
									
							}else
							{
							//here is the main change from   0<m<1
							Ynow++; 
							PK  = PK + ( 2* (  (-deltaY) - deltaX) ); 	
							}
	PixelTracker[(int)Xnow][(int)Ynow] =  new onScreenPixel((int)Xnow,(int) Ynow, true, mainWindowSizeWidth, mainWindowSizeHeight); 

					}//end For loop 
	}//end - m > 0 && m <1 								
												
				
	else if( m <1  )
	{//START - M <1 so m is a STEEP negative slope

			
		cout<<" Reverse X's ,  Steep Negative Slope "<<endl; 
		

			PK = (2*deltaX)-  (- deltaY);
																		//This takes care of 0< x< 1 
					Ynow = lineEndY; 
					Xnow = lineEndX; 
		//while(Ynow< lineStartY)
		for(Ynow = lineEndY; Ynow < lineStartY ; Ynow++)
			{
					if( PK < 0 )
					{
						PK  = PK + (2* deltaX); 
					}else
					{
						Xnow--; 
						PK = PK + ( 2* (deltaX - (-deltaY)) ); 
					}
					//Here remember to change because Ynow is Xnow, and Xnow is Y now
					// so everthing here is the same, but MUST flip here 
	PixelTracker[(int)Xnow][(int)Ynow] =  new onScreenPixel((int)Xnow,(int) Ynow, true, mainWindowSizeWidth, mainWindowSizeHeight); 

			}//end For loops 
		}// End M < -1 Super Steep Negative Slope 		
									

}//END if deltaX < 0 
//END if deltaX < 0 
//END if deltaX < 0 
//END if deltaX < 0 
//END if deltaX < 0 
//END if deltaX < 0 


}//end Bresenham 
//end Bresenham 
//end Bresenham 

//POLYLINE-DDA 3D VERSION

template<typename T>
void DDAxyz(int beginX, int beginY, int finishX, int finishY, string polyName, T *(*Tracker)[1200])   
{
		//lineDDA - START			   
					
					int usingthisPoly = 0; 
					for(int i=0; i < polygonStorageSize; i++)
					{
						if(polygonStorage[i]->Name == polyName)
						{ 
							usingthisPoly = i; 
						}

					}
				//	cout<<" did it get here to DDAxyz?"<<endl; 
			//		string blank; 
			//		cin>>blank; 

				//	onScreenPixel *PolyStorage[][] = polygonStorage[0]->storage; 

								lineStartX = beginX ;
								lineStartY = beginY; 
								lineEndX = finishX ; 
								lineEndY =  finishY; 
							//	cout<<" line start is ("<<lineStartX <<","<<lineStartY<<")... lineEnd is: ("<<lineEndX<<","<<lineEndY<<")"<<endl; 
								Tracker[lineStartX][lineStartY] = new T(lineStartX, lineStartY, true,mainWindowSizeWidth, mainWindowSizeHeight); 
								Tracker[ lineEndX ][ lineEndY ] = new T(lineEndX  , lineEndY  , true, mainWindowSizeWidth, mainWindowSizeHeight);
								
							//set Edge YES
								Tracker[lineStartX][lineStartY]->setIsEdge(true);
								Tracker[ lineEndX ][ lineEndY ]->setIsEdge(true);

							//for storing the shape! if you call it later, it should show 
							/*
							polyStorage[lineStartX][lineStartY] = new onScreenPixel(lineStartX, lineStartY, true,mainWindowSizeWidth, mainWindowSizeHeight, polyName); 
							polyStorage[ lineEndX ][ lineEndY ] = new onScreenPixel(lineEndX  , lineEndY  , true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
										
							//set Edge YES
								polyStorage[lineStartX][lineStartY]->setIsEdge(true);
								polyStorage[ lineEndX ][ lineEndY ]->setIsEdge(true);
							*/
							
							//*****************************PolygonStorage********************************START


						//	polygonStorage[usingthisPoly]->storage[lineStartX][lineStartY] = new onScreenPixel(lineStartX, lineStartY, true,mainWindowSizeWidth, mainWindowSizeHeight, polyName); 
						//	polygonStorage[usingthisPoly]->storage[ lineEndX ][ lineEndY ] = new onScreenPixel(lineEndX  , lineEndY  , true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
						//	polygonStorage[usingthisPoly]->storage[lineStartX][lineStartY]->setIsEdge(true);
						//	polygonStorage[usingthisPoly]->storage[ lineEndX ][ lineEndY ]->setIsEdge(true);
							
							//This is for Point 1, and Point 2, for start and end. Not the lines in between, this maybe needed for translating/rotation also? 
						//	polygonStorage[usingthisPoly]->storage[lineStartX][lineStartY]->isPoint = true;
						//	polygonStorage[usingthisPoly]->storage[ lineEndX ][ lineEndY ]->isPoint = true; 
						

							//*****************************PolygonStorage********************************END


								//NEED TO ACCOUNT FOR VERITCAL LINES!!!!!!!!!!!!!!!!!!!!!
								//NEED TO ACCOUNT FOR HORIZONTAL LINES!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

							//this below should account for horizontal? 
			if(lineStartY == lineEndY)
			{   
			if(lineEndX < lineStartX )
			{ // 	cout<<"*************Horizontal Line*************FROM RIGHT TO LEFT*"<<endl; 
				
				int tempLineStartX = lineStartX;
				 lineStartX = lineEndX;
				lineEndX = tempLineStartX; 
			}

			//	cout<<"*************Horizontal Line**************"<<endl; 
				for( int Move = lineStartX; Move < lineEndX ; Move++)
				{

					Tracker[Move][lineStartY] = new T(Move, lineStartY, true, mainWindowSizeWidth, mainWindowSizeHeight); 
					Tracker[Move][lineStartY]->setIsEdge(true); 
					//*****************************PolygonStorage********************************END
					//polygonStorage[usingthisPoly]->storage[ Move ][ lineStartY ] =new onScreenPixel( Move, lineStartY , true, mainWindowSizeWidth, mainWindowSizeHeight,polyName);
					//polygonStorage[usingthisPoly]->storage[ Move ][ lineStartY  ]->setIsEdge(true);
					//*****************************PolygonStorage********************************END
				}
			}
			else if (lineStartX == lineEndX )
			{
				if(lineEndY < lineStartY)
				{ // 	cout<<"*************Vertical Line**********TOP to BOTTOM ****"<<endl; 

					int tempLineStartY = lineStartY;
					lineStartY = lineEndY;
					lineEndY = tempLineStartY; 
				}


					//	cout<<"*************Vertical Line**************"<<endl; 

					for( int Move = lineStartY; Move < lineEndY ; Move++)
					{

					
					Tracker[lineStartX][ Move] = new T(lineStartX, Move , true, mainWindowSizeWidth, mainWindowSizeHeight); 
					Tracker[lineStartX][ Move]->setIsEdge(true); 

						//*****************************PolygonStorage********************************END
					//polygonStorage[usingthisPoly]->storage[ lineStartX ][ Move ] =new onScreenPixel( lineStartX, Move , true, mainWindowSizeWidth, mainWindowSizeHeight,polyName);
					//polygonStorage[usingthisPoly]->storage[ lineStartX ][ Move ]->setIsEdge(true);
						//*****************************PolygonStorage********************************END
					}
			}							
			else 
			{//line is NOT horizontal OR vertical - STart
								if(lineEndX < lineStartX )
								{
									int tempEndX, tempStartX;
									tempEndX = lineEndX;
									tempStartX = lineStartX;
									int tempEndY = lineEndY;
									int tempStartY = lineStartY;
									lineEndX = tempStartX;
									lineStartX = tempEndX; 
									lineEndY = tempStartY;
									lineStartY = tempEndY; 

								}
									int YNow, YNext, PNow, PNext; 
									int deltaY = ( lineEndY - lineStartY );
									int deltaX = ( lineEndX - lineStartX );
									YNow = lineStartY; 
									PNext = (2*deltaY)-  deltaX;
									PNow = (2*deltaY) -  deltaX; 
									YNext = lineStartY; 
									double m;
									m = (double)(deltaY) / (double)deltaX; //putting doubles at the front help with the slope. 
								double b = lineEndY - m*lineEndX; 
								bool aboveOne = false; 
								bool belowOne = false; 
								int startingPoint;
								int endingPoint; 
								if(m > 1 )
								{
									aboveOne = true; 
								}
								if( m < (-1) )
								{
									belowOne = true; 
								//	cout<<"belowOne is true"<<endl; 
								}
							

						if(  aboveOne == true && belowOne == false ) //this fixes steep slopes
						{   //for   0 < 1 < m					
							startingPoint = lineStartY; 
							endingPoint = lineEndY; 
						}
						else if(aboveOne == false && belowOne == true)
						{   //for  m < -1  < 0 
						//	cout<<" m is less than -1 belowOne is true "<<endl; 

							startingPoint = lineEndY;
							endingPoint = lineStartY;
						}
						else if( m < 0 )
						{
							   //for   -1 <  m   < 0 
							startingPoint = lineStartX;
							endingPoint = lineEndX;
						}
						else 
						{   //for   0  < m< 1 
							startingPoint = lineStartX;
							endingPoint = lineEndX; 
						}

							if( m > 0 && (lineStartY != lineEndY) )
							{ //for Negative slopes  0 - 1 
								
							//	   cout<<"B intersection is "<< b << endl; 

										for(int Move = startingPoint; Move <= endingPoint; Move++)
										{    
											

									  	if(aboveOne == false)
											{
										     double yDouble = m*((double)Move) + b; 
											 int roundY = (int)yDouble; 

											// cout<<"( " <<Move<<" , " << yDouble <<" ) " <<  "is there an int rounder? : y : "<< roundY<<endl; 
											Tracker[ Move ][ roundY ] =new T( Move, roundY, true, mainWindowSizeWidth, mainWindowSizeHeight);
											PixelTracker[ Move ][ roundY ]->setIsEdge(true); 
											/*
											polyStorage[ Move ][ roundY ] =new onScreenPixel( Move, roundY, true, mainWindowSizeWidth, mainWindowSizeHeight,polyName);
											polyStorage[ Move ][ roundY ]->setIsEdge(true);
											*/

					//*****************************PolygonStorage********************************START
				
										//	polygonStorage[usingthisPoly]->storage[ Move ][ roundY ] =new onScreenPixel( Move, roundY, true, mainWindowSizeWidth, mainWindowSizeHeight,polyName);
										//	polygonStorage[usingthisPoly]->storage[ Move ][ roundY ]->setIsEdge(true);
					//*****************************PolygonStorage********************************END
							
				

											}
											else
											{
												double xDouble = ( (double)(Move) - b)/m; 
												 int roundX = (int)xDouble; 
											// cout<<"( " <<roundX<<" , " << Move <<" ) " <<  "is there an int rounder? : y : "<< Move<<endl; 
											Tracker[ roundX ][ Move  ] =new T( roundX, Move, true, mainWindowSizeWidth, mainWindowSizeHeight);
											Tracker[ roundX ][ Move  ]->setIsEdge(true); 
										//	polyStorage[ roundX ][ Move  ] =new onScreenPixel( roundX, Move, true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
										//	polyStorage[ roundX ][ Move  ]->setIsEdge(true); 
										//*****************************PolygonStorage********************************START
												//polygonStorage[usingthisPoly]->storage
									//	polygonStorage[usingthisPoly]->storage[ roundX ][ Move  ] =new onScreenPixel( roundX, Move, true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
									//	polygonStorage[usingthisPoly]->storage[ roundX ][ Move  ]->setIsEdge(true); 

							//*****************************PolygonStorage********************************END

											}//end else
											}//for positive slopes  0 - 1 end
												//yMove++; //eventually need to see the slope to either be ++ or --; //coordinates transfer basically. 
							} //for Negative slopes  0 - 1 
							if( m < 0 )
							{ //for Negative slopes  0 - 1 
								double b = lineEndY - m*lineEndX  ; 
							//	cout<<" m is less than 0 B intersection is "<< b << endl; 


										for(int Move = endingPoint; Move >= startingPoint; Move--)
										{    /*
											 double yDouble = m*((double)Move) + b; 
											 int roundY = (int)yDouble; 
											 cout<<"( " <<Move<<" , " << yDouble <<" ) " <<  "is there an int rounder? : y : "<< roundY<<endl; 
											 PixelTracker[ Move ][ roundY ] =new onScreenPixel( Move, roundY, true, mainWindowSizeWidth, mainWindowSizeHeight);

											 */
								
									  	if(belowOne == false)
											{
										     double yDouble = m*((double)Move) + b; 
											 int roundY = (int)yDouble; 
											// cout<<" negative slope,  between -1 -> 0 "<<endl; 
											// cout<<"( " <<Move<<" , " << yDouble <<" ) " <<  "is there an int rounder? : y : "<< roundY<<endl; 
											Tracker[ Move ][ roundY ] =new T( Move, roundY, true, mainWindowSizeWidth, mainWindowSizeHeight);
											Tracker[ Move ][ roundY ]->setIsEdge(true); 
											//polyStorage[ Move ][ roundY ] =new onScreenPixel( Move, roundY, true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
											//polyStorage[ Move ][ roundY ]->setIsEdge(true); 
												//*****************************PolygonStorage********************************START
						//polygonStorage[usingthisPoly]->storage
					//	polygonStorage[usingthisPoly]->storage[ Move ][ roundY ] =new onScreenPixel( Move, roundY, true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
					//	polygonStorage[usingthisPoly]->storage[ Move ][ roundY ]->setIsEdge(true); 
						//*****************************PolygonStorage********************************END

								
						//*****************************PolygonStorage********************************START
						//polygonStorage[usingthisPoly]->storage
						//*****************************PolygonStorage********************************END

											}
											else
											{ //  cout<<" negative slope,  LESS THAN -1 "<<endl; 
												double xDouble = ( (double)(Move) - b)/m; 
												int roundX = (int)xDouble; 
											// cout<<"( " <<roundX<<" , " << Move <<" ) " <<  "is there an int rounder? : y : "<< Move<<endl; 
											Tracker[ roundX ][ Move  ] =new T( roundX, Move, true, mainWindowSizeWidth, mainWindowSizeHeight);
											Tracker[ roundX ][ Move  ]->setIsEdge(true); 
											//polyStorage[ roundX ][ Move  ] =new onScreenPixel( roundX, Move, true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
											//polyStorage[ roundX ][ Move  ]->setIsEdge(true); 

													//*****************************PolygonStorage********************************START
						//polygonStorage[usingthisPoly]->storage

					//polygonStorage[usingthisPoly]->storage[ roundX ][ Move  ] =new onScreenPixel( roundX, Move, true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
					//polygonStorage[usingthisPoly]->storage[ roundX ][ Move  ]->setIsEdge(true); 
						//*****************************PolygonStorage********************************END
											}//end else

										}//for positive slopes  0 - 1 end

										belowOne = true; 
														//yMove++; //eventually need to see the slope to either be ++ or --; //coordinates transfer basically. 
							} //for Negative slopes  0 -1 
						//}// see if slope is "steep" 
							if( lineStartY == lineEndY )
							{// cout<<" \n \n m is 0, it makes horizontal line"<<endl; 
								for(int Move = lineStartX ; Move < lineEndX ; Move++)
								{
										Tracker[ Move ][ lineEndY  ] =new T( Move, lineEndY , true, mainWindowSizeWidth, mainWindowSizeHeight);
										Tracker[ Move ][ lineEndY  ]->setIsEdge(true); 
										//polyStorage[ Move ][ lineEndY  ] =new onScreenPixel( Move, lineEndY , true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
										//polyStorage[ Move ][ lineEndY  ]->setIsEdge(true); 
						//*****************************PolygonStorage********************************START
						//polygonStorage[usingthisPoly]->storage
					//	polygonStorage[usingthisPoly]->storage[ Move ][ lineEndY  ] =new onScreenPixel( Move, lineEndY , true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
					//	polygonStorage[usingthisPoly]->storage[ Move ][ lineEndY  ]->setIsEdge(true); 
						//*****************************PolygonStorage********************************END

								}
							}
					
							
							if( lineStartX == lineEndX )
							{ //cout<<" \n \n m is 0, it makes VERTICAL line"<<endl; 
								for(int Move = lineStartY ; Move < lineEndY ; Move++)
								{
										Tracker[ lineEndX ][ Move  ] =new T( lineEndX, Move , true, mainWindowSizeWidth, mainWindowSizeHeight);
										Tracker[ lineEndX ][ Move  ]->setIsEdge(true); 
										//polyStorage[ lineEndX ][ Move  ] =new onScreenPixel( lineEndX, Move , true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
										//polyStorage[ lineEndX ][ Move  ] ->setIsEdge(true); 

													//*****************************PolygonStorage********************************START
						//polygonStorage[usingthisPoly]->storage
					//	polygonStorage[usingthisPoly]->storage[ lineEndX ][ Move  ] =new onScreenPixel( lineEndX, Move , true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
					//	polygonStorage[usingthisPoly]->storage[ lineEndX ][ Move  ] ->setIsEdge(true); 

						//*****************************PolygonStorage********************************END



								}
							}
										if( lineStartX == lineEndX && m < (-1))
								{
						
						for(int Move =  lineEndY ; Move < lineStartY ; Move++)
								{
										Tracker[ lineEndX ][ Move  ] =new T( lineEndX, Move , true, mainWindowSizeWidth, mainWindowSizeHeight);
										Tracker[ lineEndX ][ Move  ]->setIsEdge(true); 
									//	polyStorage[ lineEndX ][ Move  ] =new onScreenPixel( lineEndX, Move , true, mainWindowSizeWidth, mainWindowSizeHeight,polyName);
										//polyStorage[ lineEndX ][ Move  ]->setIsEdge(true);


															
						//*****************************PolygonStorage********************************START
						//polygonStorage[usingthisPoly]->storage
					//	polygonStorage[usingthisPoly]->storage[ lineEndX ][ Move  ] =new onScreenPixel( lineEndX, Move , true, mainWindowSizeWidth, mainWindowSizeHeight,polyName);
					//	polygonStorage[usingthisPoly]->storage[ lineEndX ][ Move  ]->setIsEdge(true);

						//*****************************PolygonStorage********************************END
								}
							}

}//line is NOT horizontal OR vertical - End
				glutPostRedisplay(); 
}//polylineDDA - END
 //polylineDDA - END
//polylineDDA - END















	//Horizontal and vertical is fixed now 
void polyLineDDA(int beginX, int beginY, int finishX, int finishY, string polyName)  
{
		//lineDDA - START			   
					
					int usingthisPoly = 0; 
					for(int i=0; i < polygonStorageSize; i++)
					{
						if(polygonStorage[i]->Name == polyName)
						{ 
							usingthisPoly = i; 
						}

					}


				//	onScreenPixel *PolyStorage[][] = polygonStorage[0]->storage; 

								lineStartX = beginX ;
								lineStartY = beginY; 
								lineEndX = finishX ; 
								lineEndY =  finishY; 
							//	cout<<" line start is ("<<lineStartX <<","<<lineStartY<<")... lineEnd is: ("<<lineEndX<<","<<lineEndY<<")"<<endl; 
								PixelTracker[lineStartX][lineStartY] = new onScreenPixel(lineStartX, lineStartY, true,mainWindowSizeWidth, mainWindowSizeHeight); 
								PixelTracker[ lineEndX ][ lineEndY ] = new onScreenPixel(lineEndX  , lineEndY  , true, mainWindowSizeWidth, mainWindowSizeHeight);
								
							//set Edge YES
								PixelTracker[lineStartX][lineStartY]->setIsEdge(true);
								PixelTracker[ lineEndX ][ lineEndY ]->setIsEdge(true);

							//for storing the shape! if you call it later, it should show 
							/*
							polyStorage[lineStartX][lineStartY] = new onScreenPixel(lineStartX, lineStartY, true,mainWindowSizeWidth, mainWindowSizeHeight, polyName); 
							polyStorage[ lineEndX ][ lineEndY ] = new onScreenPixel(lineEndX  , lineEndY  , true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
										
							//set Edge YES
								polyStorage[lineStartX][lineStartY]->setIsEdge(true);
								polyStorage[ lineEndX ][ lineEndY ]->setIsEdge(true);
							*/
							
							//*****************************PolygonStorage********************************START


						//	polygonStorage[usingthisPoly]->storage[lineStartX][lineStartY] = new onScreenPixel(lineStartX, lineStartY, true,mainWindowSizeWidth, mainWindowSizeHeight, polyName); 
						//	polygonStorage[usingthisPoly]->storage[ lineEndX ][ lineEndY ] = new onScreenPixel(lineEndX  , lineEndY  , true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
						//	polygonStorage[usingthisPoly]->storage[lineStartX][lineStartY]->setIsEdge(true);
						//	polygonStorage[usingthisPoly]->storage[ lineEndX ][ lineEndY ]->setIsEdge(true);
							
							//This is for Point 1, and Point 2, for start and end. Not the lines in between, this maybe needed for translating/rotation also? 
						//	polygonStorage[usingthisPoly]->storage[lineStartX][lineStartY]->isPoint = true;
						//	polygonStorage[usingthisPoly]->storage[ lineEndX ][ lineEndY ]->isPoint = true; 
						

							//*****************************PolygonStorage********************************END


								//NEED TO ACCOUNT FOR VERITCAL LINES!!!!!!!!!!!!!!!!!!!!!
								//NEED TO ACCOUNT FOR HORIZONTAL LINES!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

							//this below should account for horizontal? 
			if(lineStartY == lineEndY)
			{   
			if(lineEndX < lineStartX )
			{  //	cout<<"*************Horizontal Line*************FROM RIGHT TO LEFT*"<<endl; 
				
				int tempLineStartX = lineStartX;
				 lineStartX = lineEndX;
				lineEndX = tempLineStartX; 
			}
			
			//	cout<<"*************Horizontal Line**************"<<endl; 
				for( int Move = lineStartX; Move < lineEndX ; Move++)
				{

					PixelTracker[Move][lineStartY] = new onScreenPixel(Move, lineStartY, true, mainWindowSizeWidth, mainWindowSizeHeight); 
					PixelTracker[Move][lineStartY]->setIsEdge(true); 
					//*****************************PolygonStorage********************************END
					//polygonStorage[usingthisPoly]->storage[ Move ][ lineStartY ] =new onScreenPixel( Move, lineStartY , true, mainWindowSizeWidth, mainWindowSizeHeight,polyName);
					//polygonStorage[usingthisPoly]->storage[ Move ][ lineStartY  ]->setIsEdge(true);
					//*****************************PolygonStorage********************************END
				}
			}
			else if (lineStartX == lineEndX )
			{
				if(lineEndY < lineStartY)
				{ // 	cout<<"*************Vertical Line**********TOP to BOTTOM ****"<<endl; 

					int tempLineStartY = lineStartY;
					lineStartY = lineEndY;
					lineEndY = tempLineStartY; 
				}


					//	cout<<"*************Vertical Line**************"<<endl; 

					for( int Move = lineStartY; Move < lineEndY ; Move++)
					{

					
					PixelTracker[lineStartX][ Move] = new onScreenPixel(lineStartX, Move , true, mainWindowSizeWidth, mainWindowSizeHeight); 
					PixelTracker[lineStartX][ Move]->setIsEdge(true); 

						//*****************************PolygonStorage********************************END
					//polygonStorage[usingthisPoly]->storage[ lineStartX ][ Move ] =new onScreenPixel( lineStartX, Move , true, mainWindowSizeWidth, mainWindowSizeHeight,polyName);
					//polygonStorage[usingthisPoly]->storage[ lineStartX ][ Move ]->setIsEdge(true);
						//*****************************PolygonStorage********************************END
					}
			}							
			else 
			{//line is NOT horizontal OR vertical - STart
								if(lineEndX < lineStartX )
								{
									int tempEndX, tempStartX;
									tempEndX = lineEndX;
									tempStartX = lineStartX;
									int tempEndY = lineEndY;
									int tempStartY = lineStartY;
									lineEndX = tempStartX;
									lineStartX = tempEndX; 
									lineEndY = tempStartY;
									lineStartY = tempEndY; 

								}
									int YNow, YNext, PNow, PNext; 
									int deltaY = ( lineEndY - lineStartY );
									int deltaX = ( lineEndX - lineStartX );
									YNow = lineStartY; 
									PNext = (2*deltaY)-  deltaX;
									PNow = (2*deltaY) -  deltaX; 
									YNext = lineStartY; 
									double m;
									m = (double)(deltaY) / (double)deltaX; //putting doubles at the front help with the slope. 
								double b = lineEndY - m*lineEndX; 
								bool aboveOne = false; 
								bool belowOne = false; 
								int startingPoint;
								int endingPoint; 
								if(m > 1 )
								{
									aboveOne = true; 
								}
								if( m < (-1) )
								{
									belowOne = true; 
								//	cout<<"belowOne is true"<<endl; 
								}
							

						if(  aboveOne == true && belowOne == false ) //this fixes steep slopes
						{   //for   0 < 1 < m					
							startingPoint = lineStartY; 
							endingPoint = lineEndY; 
						}
						else if(aboveOne == false && belowOne == true)
						{   //for  m < -1  < 0 
						//	cout<<" m is less than -1 belowOne is true "<<endl; 

							startingPoint = lineEndY;
							endingPoint = lineStartY;
						}
						else if( m < 0 )
						{
							   //for   -1 <  m   < 0 
							startingPoint = lineStartX;
							endingPoint = lineEndX;
						}
						else 
						{   //for   0  < m< 1 
							startingPoint = lineStartX;
							endingPoint = lineEndX; 
						}

							if( m > 0 && (lineStartY != lineEndY) )
							{ //for Negative slopes  0 - 1 
								
							//	   cout<<"B intersection is "<< b << endl; 

										for(int Move = startingPoint; Move <= endingPoint; Move++)
										{    
											

									  	if(aboveOne == false)
											{
										     double yDouble = m*((double)Move) + b; 
											 int roundY = (int)yDouble; 

											// cout<<"( " <<Move<<" , " << yDouble <<" ) " <<  "is there an int rounder? : y : "<< roundY<<endl; 
											PixelTracker[ Move ][ roundY ] =new onScreenPixel( Move, roundY, true, mainWindowSizeWidth, mainWindowSizeHeight);
											PixelTracker[ Move ][ roundY ]->setIsEdge(true); 
											/*
											polyStorage[ Move ][ roundY ] =new onScreenPixel( Move, roundY, true, mainWindowSizeWidth, mainWindowSizeHeight,polyName);
											polyStorage[ Move ][ roundY ]->setIsEdge(true);
											*/

					//*****************************PolygonStorage********************************START
				
										//	polygonStorage[usingthisPoly]->storage[ Move ][ roundY ] =new onScreenPixel( Move, roundY, true, mainWindowSizeWidth, mainWindowSizeHeight,polyName);
										//	polygonStorage[usingthisPoly]->storage[ Move ][ roundY ]->setIsEdge(true);
					//*****************************PolygonStorage********************************END
							
				

											}
											else
											{
												double xDouble = ( (double)(Move) - b)/m; 
												 int roundX = (int)xDouble; 
											// cout<<"( " <<roundX<<" , " << Move <<" ) " <<  "is there an int rounder? : y : "<< Move<<endl; 
											PixelTracker[ roundX ][ Move  ] =new onScreenPixel( roundX, Move, true, mainWindowSizeWidth, mainWindowSizeHeight);
											PixelTracker[ roundX ][ Move  ]->setIsEdge(true); 
										//	polyStorage[ roundX ][ Move  ] =new onScreenPixel( roundX, Move, true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
										//	polyStorage[ roundX ][ Move  ]->setIsEdge(true); 
										//*****************************PolygonStorage********************************START
												//polygonStorage[usingthisPoly]->storage
									//	polygonStorage[usingthisPoly]->storage[ roundX ][ Move  ] =new onScreenPixel( roundX, Move, true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
									//	polygonStorage[usingthisPoly]->storage[ roundX ][ Move  ]->setIsEdge(true); 

							//*****************************PolygonStorage********************************END

											}//end else
											}//for positive slopes  0 - 1 end
												//yMove++; //eventually need to see the slope to either be ++ or --; //coordinates transfer basically. 
							} //for Negative slopes  0 - 1 
							if( m < 0 )
							{ //for Negative slopes  0 - 1 
								double b = lineEndY - m*lineEndX  ; 
							//	cout<<" m is less than 0 B intersection is "<< b << endl; 


										for(int Move = endingPoint; Move >= startingPoint; Move--)
										{    /*
											 double yDouble = m*((double)Move) + b; 
											 int roundY = (int)yDouble; 
											 cout<<"( " <<Move<<" , " << yDouble <<" ) " <<  "is there an int rounder? : y : "<< roundY<<endl; 
											 PixelTracker[ Move ][ roundY ] =new onScreenPixel( Move, roundY, true, mainWindowSizeWidth, mainWindowSizeHeight);

											 */
								
									  	if(belowOne == false)
											{
										     double yDouble = m*((double)Move) + b; 
											 int roundY = (int)yDouble; 
											// cout<<" negative slope,  between -1 -> 0 "<<endl; 
											// cout<<"( " <<Move<<" , " << yDouble <<" ) " <<  "is there an int rounder? : y : "<< roundY<<endl; 
											PixelTracker[ Move ][ roundY ] =new onScreenPixel( Move, roundY, true, mainWindowSizeWidth, mainWindowSizeHeight);
											PixelTracker[ Move ][ roundY ]->setIsEdge(true); 
											//polyStorage[ Move ][ roundY ] =new onScreenPixel( Move, roundY, true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
											//polyStorage[ Move ][ roundY ]->setIsEdge(true); 
												//*****************************PolygonStorage********************************START
						//polygonStorage[usingthisPoly]->storage
					//	polygonStorage[usingthisPoly]->storage[ Move ][ roundY ] =new onScreenPixel( Move, roundY, true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
					//	polygonStorage[usingthisPoly]->storage[ Move ][ roundY ]->setIsEdge(true); 
						//*****************************PolygonStorage********************************END

								
						//*****************************PolygonStorage********************************START
						//polygonStorage[usingthisPoly]->storage
						//*****************************PolygonStorage********************************END

											}
											else
											{ //  cout<<" negative slope,  LESS THAN -1 "<<endl; 
												double xDouble = ( (double)(Move) - b)/m; 
												int roundX = (int)xDouble; 
											// cout<<"( " <<roundX<<" , " << Move <<" ) " <<  "is there an int rounder? : y : "<< Move<<endl; 
											PixelTracker[ roundX ][ Move  ] =new onScreenPixel( roundX, Move, true, mainWindowSizeWidth, mainWindowSizeHeight);
											PixelTracker[ roundX ][ Move  ]->setIsEdge(true); 
											//polyStorage[ roundX ][ Move  ] =new onScreenPixel( roundX, Move, true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
											//polyStorage[ roundX ][ Move  ]->setIsEdge(true); 

													//*****************************PolygonStorage********************************START
						//polygonStorage[usingthisPoly]->storage

					//polygonStorage[usingthisPoly]->storage[ roundX ][ Move  ] =new onScreenPixel( roundX, Move, true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
					//polygonStorage[usingthisPoly]->storage[ roundX ][ Move  ]->setIsEdge(true); 
						//*****************************PolygonStorage********************************END
											}//end else

										}//for positive slopes  0 - 1 end

										belowOne = true; 
														//yMove++; //eventually need to see the slope to either be ++ or --; //coordinates transfer basically. 
							} //for Negative slopes  0 -1 
						//}// see if slope is "steep" 
							if( lineStartY == lineEndY )
							{// cout<<" \n \n m is 0, it makes horizontal line"<<endl; 
								for(int Move = lineStartX ; Move < lineEndX ; Move++)
								{
										PixelTracker[ Move ][ lineEndY  ] =new onScreenPixel( Move, lineEndY , true, mainWindowSizeWidth, mainWindowSizeHeight);
										PixelTracker[ Move ][ lineEndY  ]->setIsEdge(true); 
										//polyStorage[ Move ][ lineEndY  ] =new onScreenPixel( Move, lineEndY , true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
										//polyStorage[ Move ][ lineEndY  ]->setIsEdge(true); 
						//*****************************PolygonStorage********************************START
						//polygonStorage[usingthisPoly]->storage
					//	polygonStorage[usingthisPoly]->storage[ Move ][ lineEndY  ] =new onScreenPixel( Move, lineEndY , true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
					//	polygonStorage[usingthisPoly]->storage[ Move ][ lineEndY  ]->setIsEdge(true); 
						//*****************************PolygonStorage********************************END

								}
							}
					
							
							if( lineStartX == lineEndX )
							{ //cout<<" \n \n m is 0, it makes VERTICAL line"<<endl; 
								for(int Move = lineStartY ; Move < lineEndY ; Move++)
								{
										PixelTracker[ lineEndX ][ Move  ] =new onScreenPixel( lineEndX, Move , true, mainWindowSizeWidth, mainWindowSizeHeight);
										PixelTracker[ lineEndX ][ Move  ]->setIsEdge(true); 
										//polyStorage[ lineEndX ][ Move  ] =new onScreenPixel( lineEndX, Move , true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
										//polyStorage[ lineEndX ][ Move  ] ->setIsEdge(true); 

													//*****************************PolygonStorage********************************START
						//polygonStorage[usingthisPoly]->storage
					//	polygonStorage[usingthisPoly]->storage[ lineEndX ][ Move  ] =new onScreenPixel( lineEndX, Move , true, mainWindowSizeWidth, mainWindowSizeHeight, polyName);
					//	polygonStorage[usingthisPoly]->storage[ lineEndX ][ Move  ] ->setIsEdge(true); 

						//*****************************PolygonStorage********************************END



								}
							}
										if( lineStartX == lineEndX && m < (-1))
								{
						
						for(int Move =  lineEndY ; Move < lineStartY ; Move++)
								{
										PixelTracker[ lineEndX ][ Move  ] =new onScreenPixel( lineEndX, Move , true, mainWindowSizeWidth, mainWindowSizeHeight);
										PixelTracker[ lineEndX ][ Move  ]->setIsEdge(true); 
									//	polyStorage[ lineEndX ][ Move  ] =new onScreenPixel( lineEndX, Move , true, mainWindowSizeWidth, mainWindowSizeHeight,polyName);
										//polyStorage[ lineEndX ][ Move  ]->setIsEdge(true);


															
						//*****************************PolygonStorage********************************START
						//polygonStorage[usingthisPoly]->storage
					//	polygonStorage[usingthisPoly]->storage[ lineEndX ][ Move  ] =new onScreenPixel( lineEndX, Move , true, mainWindowSizeWidth, mainWindowSizeHeight,polyName);
					//	polygonStorage[usingthisPoly]->storage[ lineEndX ][ Move  ]->setIsEdge(true);

						//*****************************PolygonStorage********************************END
								}
							}

}//line is NOT horizontal OR vertical - End
				glutPostRedisplay(); 
}//polylineDDA - END
 //polylineDDA - END
//polylineDDA - END

void checkEdge(); 
void drawAllPolygons(); 
void drawPolygonVerticesBresenham(string polyName);
void makePolyBresenham()
{
						string polyName = "";
						cout<<"\n \n \n Bresenham algorithm, what would you like to name your Poly?"<<endl; 
						cin>>polyName;
						cout<<"your poly is now called:* "<<polyName << " * "<<endl;
						
						int movePoly;
						for(movePoly=0; movePoly <polygonStorageSize ; movePoly++)
						{
							if(polygonStorage[movePoly]->Name == "" )
								{
								polygonStorage[movePoly]->Name = polyName; 
								polygonStorage[movePoly]->erasepolygoning(); 
									cout<<"Break from loop, found at polygonStorage["<<movePoly<<"]"<<endl; 
									break;
								}

						}
	

						cout<<"\n your polyGon Name confirm: ' " << polygonStorage[movePoly]->Name<<"'"<<endl;
						cout<<"at polygonStorage["<<movePoly<<"]"<<endl; 

						int oneX,oneY,twoX,twoY,threeX,threeY,fourX,fourY; 
					bool isFinishPoly = false; 
					int countPoints = 0; 
					int initialX, initialY; 
					int firstX, firstY;
					int secondX, secondY; 
 						cout<<"type in point "<<countPoints<<endl; 
 						cout<<"x:"<<endl;
 						cin>>firstX; 
 						cout<<"y:"<<endl;
 						cin>>firstY; 

						int verticeMove = 0; 
				
						countPoints++;
					 
						cout<<"want to add more points? Type yes or no"<<endl; 
 						string yesNo;
 						cin>>yesNo; 
 						if(yesNo == "No" || yesNo == "n" || yesNo =="no" || yesNo == "N")
 						{	isFinishPoly = true; 
 						
 						}

						initialX = firstX;
						initialY =firstY; 

						polygonStorage[movePoly]->vertices[verticeMove] = new onScreenPixel(initialX, initialY, false, mainWindowSizeWidth, mainWindowSizeHeight); 
						verticeMove++; 
					while(isFinishPoly == false)
					{  

						cout<<"type in points below... # of points so far: "<<countPoints<<endl; 
						cout<<"x:"<<endl;
 						cin>>secondX; 
 						cout<<"y:"<<endl;
 						cin>>secondY; 
 						
 					//	polyLineDDA(firstX, firstY, secondX, secondY, polyName);

						polygonStorage[movePoly]->vertices[verticeMove] = new onScreenPixel(secondX, secondY, false, mainWindowSizeWidth, mainWindowSizeHeight); 
							polygonStorage[movePoly]->vertices[verticeMove]->isPoint =true; 
 						cout<<"want to add more points? Type yes or no"<<endl; 
 						string yesNo;
 						cin>>yesNo; 

 						
 						
 						if(yesNo == "No" || yesNo == "n" || yesNo =="no" || yesNo == "N")
 						{	isFinishPoly = true; 
 							break; 
 						}
 						
 						firstX = secondX;
 						firstY = secondY; 
 
 						countPoints++; 
						verticeMove++; 
							
							polygonStorage[movePoly]->verticesSize = verticeMove+1 ; 
					}
					//	polyLineDDA(initialX, initialY, secondX, secondY, polyName);
									//need to refrest
									//so we do a check edges

					cout<<" checking out shape vertices, see if it worked, and vertices size is:"<<polygonStorage[movePoly]->verticesSize<<endl;

					for(int i = 0; i <polygonStorage[movePoly]->verticesSize; i ++)
					{
						cout<< polygonStorage[movePoly]->vertices[i]->getX() <<" , " << polygonStorage[movePoly]->vertices[i]->getY()<<endl;  
					}


					for(int i = 0; i< polygonStorage[movePoly]->verticesSize; i ++)
					{

						cout<<" getting vertices and looping em into polyLinDDA "<<endl; 
						if( i < polygonStorage[movePoly]->verticesSize-1  )
						{	polyLineDDA( polygonStorage[movePoly]->vertices[i]->getX(), polygonStorage[movePoly]->vertices[i]->getY() ,polygonStorage[movePoly]->vertices[i+1]->getX(), polygonStorage[movePoly]->vertices[i+1]->getY() , polyName);
						
						cout<< polygonStorage[movePoly]->vertices[i]->getX() <<" , " << polygonStorage[movePoly]->vertices[i]->getY()<< " ";
						cout<< polygonStorage[movePoly]->vertices[i+1]->getX() <<" , " << polygonStorage[movePoly]->vertices[i+1]->getY()<<endl;
						}
						else if ( i == polygonStorage[movePoly]->verticesSize-1 )
						{		polyLineDDA( polygonStorage[movePoly]->vertices[i]->getX(), polygonStorage[movePoly]->vertices[i]->getY() ,polygonStorage[movePoly]->vertices[0]->getX(), polygonStorage[movePoly]->vertices[0]->getY() , polyName);
							cout<< polygonStorage[movePoly]->vertices[i]->getX() <<" , " << polygonStorage[movePoly]->vertices[i]->getY()<<" ";
							cout<< polygonStorage[movePoly]->vertices[0]->getX() <<" , " << polygonStorage[movePoly]->vertices[0]->getY();
							cout<<" last point match with start"<<endl; 
							

						}
					}


						//		checkEdge(); 
					//this is MakePoly btw, keep in mind 
				//	drawAllPolygons(); 

					drawPolygonVerticesBresenham(polyName);
					glutPostRedisplay();

}
void makePoly()
{
						string polyName = "";
						cout<<"\n \n \n what would you like to name your Poly?"<<endl; 
						cin>>polyName;
						cout<<"your poly is now called:* "<<polyName << " * "<<endl;
						
						int movePoly;
						for(movePoly=0; movePoly <polygonStorageSize ; movePoly++)
						{
							if(polygonStorage[movePoly]->Name == "" )
								{
								polygonStorage[movePoly]->Name = polyName; 
								polygonStorage[movePoly]->erasepolygoning(); 
									cout<<"Break from loop, found at polygonStorage["<<movePoly<<"]"<<endl; 
									break;
								}

						}
	

						cout<<"\n your polyGon Name confirm: ' " << polygonStorage[movePoly]->Name<<"'"<<endl;
						cout<<"at polygonStorage["<<movePoly<<"]"<<endl; 

						int oneX,oneY,twoX,twoY,threeX,threeY,fourX,fourY; 
					bool isFinishPoly = false; 
					int countPoints = 0; 
					int initialX, initialY; 
					int firstX, firstY;
					int secondX, secondY; 
 						cout<<"type in point "<<countPoints<<endl; 
 						cout<<"x:"<<endl;
 						cin>>firstX; 
 						cout<<"y:"<<endl;
 						cin>>firstY; 

						int verticeMove = 0; 
				
						countPoints++;
					 
						cout<<"want to add more points? Type yes or no"<<endl; 
 						string yesNo;
 						cin>>yesNo; 
 						if(yesNo == "No" || yesNo == "n" || yesNo =="no" || yesNo == "N")
 						{	isFinishPoly = true; 
 						
 						}

						initialX = firstX;
						initialY =firstY; 

						polygonStorage[movePoly]->vertices[verticeMove] = new onScreenPixel(initialX, initialY, false, mainWindowSizeWidth, mainWindowSizeHeight); 
						verticeMove++; 
					while(isFinishPoly == false)
					{  

						cout<<"type in points below... # of points so far: "<<countPoints<<endl; 
						cout<<"x:"<<endl;
 						cin>>secondX; 
 						cout<<"y:"<<endl;
 						cin>>secondY; 
 						
 					//	polyLineDDA(firstX, firstY, secondX, secondY, polyName);

						polygonStorage[movePoly]->vertices[verticeMove] = new onScreenPixel(secondX, secondY, false, mainWindowSizeWidth, mainWindowSizeHeight); 
							polygonStorage[movePoly]->vertices[verticeMove]->isPoint =true; 
 						cout<<"want to add more points? Type yes or no"<<endl; 
 						string yesNo;
 						cin>>yesNo; 

 						
 						
 						if(yesNo == "No" || yesNo == "n" || yesNo =="no" || yesNo == "N")
 						{	isFinishPoly = true; 
 							break; 
 						}
 						
 						firstX = secondX;
 						firstY = secondY; 
 
 						countPoints++; 
						verticeMove++; 
							
							polygonStorage[movePoly]->verticesSize = verticeMove+1 ; 
					}
					//	polyLineDDA(initialX, initialY, secondX, secondY, polyName);
									//need to refrest
									//so we do a check edges

					cout<<" checking out shape vertices, see if it worked, and vertices size is:"<<polygonStorage[movePoly]->verticesSize<<endl;

					for(int i = 0; i <polygonStorage[movePoly]->verticesSize; i ++)
					{
						cout<< polygonStorage[movePoly]->vertices[i]->getX() <<" , " << polygonStorage[movePoly]->vertices[i]->getY()<<endl;  
					}


					for(int i = 0; i< polygonStorage[movePoly]->verticesSize; i ++)
					{

						cout<<" getting vertices and looping em into polyLinDDA "<<endl; 
						if( i < polygonStorage[movePoly]->verticesSize-1  )
						{	polyLineDDA( polygonStorage[movePoly]->vertices[i]->getX(), polygonStorage[movePoly]->vertices[i]->getY() ,polygonStorage[movePoly]->vertices[i+1]->getX(), polygonStorage[movePoly]->vertices[i+1]->getY() , polyName);
						
						cout<< polygonStorage[movePoly]->vertices[i]->getX() <<" , " << polygonStorage[movePoly]->vertices[i]->getY()<< " ";
						cout<< polygonStorage[movePoly]->vertices[i+1]->getX() <<" , " << polygonStorage[movePoly]->vertices[i+1]->getY()<<endl;
						}
						else if ( i == polygonStorage[movePoly]->verticesSize-1 )
						{		polyLineDDA( polygonStorage[movePoly]->vertices[i]->getX(), polygonStorage[movePoly]->vertices[i]->getY() ,polygonStorage[movePoly]->vertices[0]->getX(), polygonStorage[movePoly]->vertices[0]->getY() , polyName);
							cout<< polygonStorage[movePoly]->vertices[i]->getX() <<" , " << polygonStorage[movePoly]->vertices[i]->getY()<<" ";
							cout<< polygonStorage[movePoly]->vertices[0]->getX() <<" , " << polygonStorage[movePoly]->vertices[0]->getY();
							cout<<" last point match with start"<<endl; 
							

						}
					}


						//		checkEdge(); 
					//this is MakePoly btw, keep in mind 
					drawAllPolygons(); 
					glutPostRedisplay();

}

int returnPolyFind(string polyName); 
/*
void makePolyAppear(string polyName)
{
	bool found = false; 
	int polyFind; 
	for(int i = 0; i <polygonStorageSize; i++)
	{
		if(polygonStorage[i]->Name == polyName)
		{

			cout<<" found in looop name "<< polyName<<endl; 
			polyFind = i; 
			found = true; 
			
			break; 
		} 
		else if( i == 18)
		{
			cout<<" Sorry, polyogn Name does not Exist in database "<<endl;
			break;
		}
	}

	if(found == true)
	{

	
		polyFind = returnPolyFind(polyName); 

		

		
	}

}
*/

void checkEdge()
{
	cout<<"Scanning for edge, and turning them blue"<<endl; 
	for(int i= 0; i < mainWindowSizeWidth; i++)
	   {
					for(int j= 0; j< mainWindowSizeHeight ; j++)
					{
						if(PixelTracker[i][j]->getIsEdge() == true)
						{
							PixelTracker[i][j]->turnCyan(); 
						}
					};

			     };
	cout<<"..Finishing, checking if edge is istrue, only works for Poly atm "<<endl; 
}

void eraseMainPixels()
{
	cout<<"...Erasing..main pixels."<<endl; 
	for(int i= 0; i < mainWindowSizeWidth; i++)
	   {
					for(int j= 0; j< mainWindowSizeHeight ; j++)
					{ 
					
						PixelTracker[i][j] = new onScreenPixel(i, j, false, mainWindowSizeWidth, mainWindowSizeHeight);
						PixelTracker[i][j]->turnOFF(); 
						//cout<<" x test: "<<i <<" j test: " <<j<<endl; 
					};

			     };
	cout<<"...Erasing... Finished! "<<endl; 
}


void eraseMainPixelsXYZ()
{
	cout<<"...Erasing..main pixels."<<endl; 
	for(int i= 0; i < mainWindowSizeWidth; i++)
	   {
					for(int j= 0; j< mainWindowSizeHeight ; j++)
					{ 
					
						PixelTracker[i][j] = new onScreenPixel(i, j, false, mainWindowSizeWidth, mainWindowSizeHeight);
						PixelTracker[i][j]->turnOFF(); 
						PixelTrackerXZ[i][j] = new onScreenPixelXZ(i, j, false, mainWindowSizeWidth, mainWindowSizeHeight);
						PixelTrackerXZ[i][j]->turnOFF(); 
								PixelTrackerYZ[i][j] = new onScreenPixelYZ(i, j, false, mainWindowSizeWidth, mainWindowSizeHeight);
						PixelTrackerYZ[i][j]->turnOFF(); 
						//cout<<" x test: "<<i <<" j test: " <<j<<endl; 
					};

			     };
	cout<<"...Erasing... Finished! "<<endl; 
}




//recursive for small shapes
int testlimit = 20; 
//pas test limit in here:
bool go1 = false, go2 = false, go3 = false, go4 = false; 


//recursive for tight boundaries. 
void colorPoint(int inX, int inY, int limiting )
{

	int x = inX;
	int y = inY; 
	testlimit -= 1; 
	cout<<"test limit is currently at "<< testlimit <<endl; 
	PixelTracker[x][y]->turnBlue(); 

	// Right, DOwn Left, Up 
	if( PixelTracker[x+1][y]->turnStatus == false &&  PixelTracker[x+1][y]!=NULL &&  PixelTracker[x+1][y]->getIsEdge() == false)
    {   
		PixelTracker[x+1][y]->turnStatus = true; 

		
		colorPoint(x+1, y,limiting - 1 ); 
		go1 = false; 
	}
		// 


	if( PixelTracker[x][y-1]->turnStatus == false && PixelTracker[x][y-1] !=NULL &&  PixelTracker[x][y-1]->getIsEdge() == false )
    {   
		PixelTracker[x][y-1]->turnStatus = true;
		colorPoint(x, y-1, limiting - 1); 
		go2 = false; 
	}


	if( PixelTracker[x-1][y]->turnStatus == false && PixelTracker[x-1][y] !=NULL &&  PixelTracker[x-1][y]->getIsEdge() == false )
	{  PixelTracker[x][y-1]->turnStatus = true;
		colorPoint(x-1, y, limiting - 1); 
		go3 = false; 
	}
	if( PixelTracker[x][y+1]->turnStatus == false && PixelTracker[x][y+1] !=NULL &&  PixelTracker[x][y+1]->getIsEdge() == false )
		{

			PixelTracker[x-1][y]->turnStatus = true;
		colorPoint(x, y+1, limiting - 1); 

		//testlimit = 20; 
		go4 = false; 
		}



 }
 
 //This individually draws polygons when name is typed in 
void drawPolygonVertices(string polyName); 



void rotatePoly_findAvereage(string polyName); 
/*
void colorPoint(string polyName)
{
cout<<"empty go to proper rasterizing "<<endl; 
}
*/

//BROKEN
void checkInnerLining()
{
	cout<<"Scanning for inner lining and turning them Yellow"<<endl; 
	for(int i= 0; i < mainWindowSizeWidth; i++)
	   {
					for(int j= 0; j< mainWindowSizeHeight ; j++)
					{
						if(PixelTracker[i][j]->getIsInnerLining() == true)
						{
							PixelTracker[i][j]->turnPurple(); 
						}
					};

			     };
	cout<<"..Finished, INNERLINING IS YELLOW.  only works for Poly atm "<<endl; 
}

bool findEdgeRight = false; 


//BROKEN 
void colorInnerLining(int inX, int inY, string direction)
{

	int x = inX;
	int y = inY; 

	string top = "";
	string topRight = "";
	string right = "";
	string rightBottom = "";
	string bottom = "";
	string bottomLeft = "";
	string left = "";
	string leftTop = ""; 

	string go = direction; 


	//direction going hugging 
	
				if(findEdgeRight == false)
					{	
												if(PixelTracker[x+1][y]->getIsEdge() == false)
												{
													PixelTracker[x+1][y]->turnGreen(); 
													colorInnerLining(x+1, y, "east") ;

												}
												else if( PixelTracker[x+1][y]->getIsEdge() == true)
												{  

													findEdgeRight = true; //found the right edge to start.
													colorInnerLining(x,y, "south");
												}

					}
					else //meaning it found the right Edge ... 
							{ //start Edge Cycle 

							if( x == 179 && y == 267 )
							{

								cout<<"WHY STOP HEREEEEEEEEEEEEEEEEEE"<<x<<"..."<<y<<endl; 
							}




												if(PixelTracker[x][y+1]->getIsEdge() ==true ) 
												{  top = "edge";
												}
												if(PixelTracker[x+1][y+1]->getIsEdge() ==true ) 
												{ topRight = "edge";
												}
												if(PixelTracker[x+1][y]->getIsEdge() ==true ) 
												{ right = "edge";
												}
												if(PixelTracker[x+1][y-1]->getIsEdge() ==true ) 
												{ rightBottom = "edge";
												}
												if(PixelTracker[x][y-1]->getIsEdge() ==true ) 
												{ bottom = "edge";
												}
												if(PixelTracker[x-1][y-1]->getIsEdge() ==true ) 
												{  bottomLeft = "edge";
												}
												if(PixelTracker[x-1][y]->getIsEdge() ==true ) 
												{  left = "edge";
												}
												if(PixelTracker[x-1][y+1]->getIsEdge() ==true ) 
												{ leftTop = "edge";
												}




												if(PixelTracker[x][y+1]->getIsInnerLining() ==true ) 
												{  top = "lining";
												}
												if(PixelTracker[x+1][y+1]->getIsInnerLining() ==true ) 
												{ topRight =  "lining";
												}
												if(PixelTracker[x+1][y]->getIsInnerLining() ==true ) 
												{ right =  "lining";
												}
												if(PixelTracker[x+1][y-1]->getIsInnerLining() ==true ) 
												{ rightBottom =  "lining";
												}
												if(PixelTracker[x][y-1]->getIsInnerLining() ==true ) 
												{ bottom =  "lining";
												}
												if(PixelTracker[x-1][y-1]->getIsInnerLining() ==true ) 
												{  bottomLeft =  "lining";
												}
												if(PixelTracker[x-1][y]->getIsInnerLining() ==true ) 
												{  left =  "lining";
												}
												if(PixelTracker[x-1][y+1]->getIsInnerLining() ==true ) 
												{ leftTop =  "lining";
												}


		

												//triple Corner Edge
												//Double Corner Edge
												//Singe Corner edge
												//Double Edge (tube)
												//Single Edge 


							
											//Single Corner Cases, 



						/////////////////////////////////////////////CONER CASES!!!!!!!!!!//////////////////////////////

					if( bottomLeft == "edge" && left != "edge" && bottom!="edge" && left != "lining"  )
												{   
													cout<<"           westtt!!! botLeft Corner  "<<endl; 
													PixelTracker[x][y]->turnGreen(); 
										           	PixelTracker[x][y]->setIsInnerLining(true); 
													colorInnerLining(x-1,y, "blank");
												}

						  else if( leftTop == "edge" && top != "edge" && left!= "edge" && top != "lining"  )
												{   
													cout<<"           NORTh topLeft Corner  "<<endl; 
													PixelTracker[x][y]->turnGreen(); 
										           	PixelTracker[x][y]->setIsInnerLining(true); 
													colorInnerLining(x,y+1, "blank");
												}

						 else if( rightBottom == "edge" && bottom != "edge" && right != "edge" && bottom != "lining" )
												{   
													cout<<"           South corner bottom right   "<<endl; 
													PixelTracker[x][y]->turnGreen(); 
										           	PixelTracker[x][y]->setIsInnerLining(true); 
													colorInnerLining(x,y-1, "blank");
												}
							 else	 if( topRight == "edge" && right != "edge" && top != "edge" && right != "lining" )
												{   
													cout<<"            EAST!  top right corner EDGE    "<<endl; 
													PixelTracker[x][y]->turnGreen(); 
										           	PixelTracker[x][y]->setIsInnerLining(true); 
													colorInnerLining(x+1,y, "blank");
												}
																														//Single Edge Case, 
							 else if( right == "edge" && bottom != "edge" )
																															{   
																																cout<<"            SOUTH!       "<<endl; 
																																PixelTracker[x][y]->turnRed(); 
										           																				PixelTracker[x][y]->setIsInnerLining(true); 
																																colorInnerLining(x,y-1, "blank");
																															}
							else	if( bottom == "edge" && left != "edge" )
																															{   
																																cout<<"            WEST!       "<<endl; 
																																PixelTracker[x][y]->turnBlue(); 
										           																				PixelTracker[x][y]->setIsInnerLining(true); 
																																colorInnerLining(x-1,y, "blank");
																															}
							else if( left == "edge" && top != "edge" )
																															{   
																																cout<<"            NORTH!      "<<endl; 
																																PixelTracker[x][y]->turnYellow(); 
										           																				PixelTracker[x][y]->setIsInnerLining(true); 
																																colorInnerLining(x,y+1, "blank");
																															}
							else	 if( top == "edge" && right != "edge" )
																															{   
																																cout<<"            EAST!      "<<endl; 

																																if(x == 179 && y == 267 )
																																{
																																	cout<<" got here, why didn't go ? "<<endl; 
																																}

																																cout<<" x+1 y " << x+1 << ", " << y<<endl; 
																																PixelTracker[x][y]->turnGreen(); 
										           																				PixelTracker[x][y]->setIsInnerLining(true); 
																																colorInnerLining(x+1,y, "blank");
																															}
										else
												{
													cout<<" i stopped here at purple why?? "<< x << " , " << y <<endl;
													PixelTracker[x][y]->turnPurple(); 
										           	PixelTracker[x][y]->setIsInnerLining(true);
												}

						  }//end cycle??

}



int returnPolyFind(string polyName)
{
	int polyFind = 0; 
					for(int i=0; i < polygonStorageSize; i++)
					{
						if(polygonStorage[i]->Name == polyName)
						{ 
							polyFind = i; 
							break; 
						}

					}

					return polyFind; 	
}


void drawPolygonVertices(string polyName)
	{
					int polyFind = 0; 


					polyFind =	returnPolyFind(polyName); 
					int movePoly = polyFind;
					//draws polygon with polylineDDA 
					cout<<"starting vertice"<<polygonStorage[polyFind]->vertices[0]->x<<","<<polygonStorage[polyFind]->vertices[0]->y<<endl; 
									
					for(int i = 0; i< polygonStorage[polyFind]->verticesSize; i ++)
					{

						cout<<" DRrawPolygonVertices-getting vertices and looping em into polyLinDDA "<<endl; 
						if( i < polygonStorage[movePoly]->verticesSize-1  )
						{	
		polyLineDDA( polygonStorage[movePoly]->vertices[i]->getX(), polygonStorage[movePoly]->vertices[i]->getY() ,polygonStorage[movePoly]->vertices[i+1]->getX(), polygonStorage[movePoly]->vertices[i+1]->getY() , polyName);
			
						cout<< polygonStorage[movePoly]->vertices[i]->getX() <<" , " << polygonStorage[movePoly]->vertices[i]->getY()<< " ";
						cout<< polygonStorage[movePoly]->vertices[i+1]->getX() <<" , " << polygonStorage[movePoly]->vertices[i+1]->getY()<<endl;
						}
						else if ( i == polygonStorage[movePoly]->verticesSize-1 )
						{		
		polyLineDDA( polygonStorage[movePoly]->vertices[i]->getX(), polygonStorage[movePoly]->vertices[i]->getY() ,polygonStorage[movePoly]->vertices[0]->x, polygonStorage[movePoly]->vertices[0]->y , polyName);
							cout<< polygonStorage[movePoly]->vertices[i]->getX() <<" , " << polygonStorage[movePoly]->vertices[i]->getY()<<" ";
							cout<< polygonStorage[movePoly]->vertices[0]->getX() <<" , " << polygonStorage[movePoly]->vertices[0]->getY();
							cout<<"\n DrawPolygonVertices- last point match with start"<<endl; 			
						}
					}						
	}

void drawPolygonVerticesBresenham(string polyName)
	{
					int polyFind = 0; 


					polyFind =	returnPolyFind(polyName); 
					int movePoly = polyFind;
					//draws polygon with polylineDDA 
					cout<<"starting vertice"<<polygonStorage[polyFind]->vertices[0]->x<<","<<polygonStorage[polyFind]->vertices[0]->y<<endl; 
									
					for(int i = 0; i< polygonStorage[polyFind]->verticesSize; i ++)
					{

						cout<<" DRrawPolygonVertices-getting vertices and looping em into polyLinDDA "<<endl; 
						if( i < polygonStorage[movePoly]->verticesSize-1  )
						{	
		bresenhamLine( polygonStorage[movePoly]->vertices[i]->getX(), polygonStorage[movePoly]->vertices[i]->getY() ,polygonStorage[movePoly]->vertices[i+1]->getX(), polygonStorage[movePoly]->vertices[i+1]->getY());
			
						cout<< polygonStorage[movePoly]->vertices[i]->getX() <<" , " << polygonStorage[movePoly]->vertices[i]->getY()<< " ";
						cout<< polygonStorage[movePoly]->vertices[i+1]->getX() <<" , " << polygonStorage[movePoly]->vertices[i+1]->getY()<<endl;
						}
						else if ( i == polygonStorage[movePoly]->verticesSize-1 )
						{		
	bresenhamLine( polygonStorage[movePoly]->vertices[i]->getX(), polygonStorage[movePoly]->vertices[i]->getY() ,polygonStorage[movePoly]->vertices[0]->x, polygonStorage[movePoly]->vertices[0]->y);
							cout<< polygonStorage[movePoly]->vertices[i]->getX() <<" , " << polygonStorage[movePoly]->vertices[i]->getY()<<" ";
							cout<< polygonStorage[movePoly]->vertices[0]->getX() <<" , " << polygonStorage[movePoly]->vertices[0]->getY();
							cout<<"\n DrawPolygonVertices- last point match with start"<<endl; 			
						}
					}						
	}

//hopefully can check, if "shape is ON or of", can do polygonOnOff variable later !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void drawAllPolygons()
{
							eraseMainPixels(); 
							cout<<" this is draw all polygons"<<endl; 
							for(int i = 0 ; i < polygonStorageSize ; i++)
							{
								cout<< " name:"<< polygonStorage[i]->Name<<endl; 
								if(polygonStorage[i]->Name != "" ) 
								drawPolygonVertices(polygonStorage[i]->Name); 
							}

}



//ROTATING******************//ROTATING******************//ROTATING******************//ROTATING******************
//For Rotating the Polygon, we use all the rotate functions below: 
int rotatePoly_xy_X;
int rotatePoly_xy_Y; 
void rotatePoly(int degrees, string polyName)
{
	int byDegrees = degrees; 
	//take all the points, find the averate


	double d_someX;
	double  d_someY; 

	double xOne;
	double xZero;
	double yOne;
	double yZero; 

	double radian = 0.0174533; 
	double degreestoRadian = degrees * (3.14159265359 / 180 ); 
	onScreenPixel *newLocation[30]; 
	int polyFind = 0; 
					for(int i=0; i < polygonStorageSize; i++)
					{
						if(polygonStorage[i]->Name == polyName)
						{ 
							polyFind = i; 
							break; 
						}

					}
						

					for(int i = 0; i < polygonStorage[polyFind]->verticesSize ; i++) 
					{
						xOne = polygonStorage[polyFind]->vertices[i]->getX() ;
						xZero = polygonStorage[polyFind]->centerX ;

						yOne = polygonStorage[polyFind]->vertices[i]->getY() ;
						yZero =  polygonStorage[polyFind]->centerY ;


		d_someX = (  cos(degreestoRadian)*(xOne - xZero)  ) - ( sin(degreestoRadian) *  (yOne - yZero)  ) + xZero; 
		d_someY = (  sin(degreestoRadian)*(xOne - xZero)  ) + ( cos(degreestoRadian) *  (yOne - yZero)  ) + yZero; 

					cout<<" new points d_some.... :" <<(int)d_someX << " , " << (int)d_someY <<endl; 
					cout<<"cos(degreestoRadian is)"<<cos(degreestoRadian)<<endl; 
					polygonStorage[polyFind]->vertices[i]->x = (int)d_someX; 
					polygonStorage[polyFind]->vertices[i]->y = (int)d_someY; 

				//	newLocation[i] = new onScreenPixel((int)d_someX, (int)d_someY, false, mainWindowSizeWidth, mainWindowSizeHeight, polyName); 
					}			
					//drawPolygonVertices(polygonStorage[polyFind]->Name); 
					drawAllPolygons(); 
					drawPolygonVertices(polygonStorage[polyFind]->Name);
}


void rotatePoly_findAvereage(string name)
{
	string polygonName = name;
	int polyFind = 0;
	polyFind = returnPolyFind(name); 
	//int totalX;
	//int totalY;
	rotatePoly_xy_X = 0; 
	rotatePoly_xy_Y = 0;
	int countX=0;
	int countY=0; 
	double averageX=0;
	double averageY=0; 
	double totalX=0;
	double totalY=0; 
	cout<<" is this the right Polygon, to find center average of?: " << polygonStorage[polyFind]->Name <<endl; 

	int countXCheck = 0; 
	for(int i = 0; i < polygonStorage[polyFind]->verticesSize; i ++)
	{
		cout<<polygonStorage[polyFind]->vertices[i]->getX()<<" , "<<polygonStorage[polyFind]->vertices[i]->getY() <<endl; 
		totalX = totalX + polygonStorage[polyFind]->vertices[i]->getX(); 
		totalY = totalY + polygonStorage[polyFind]->vertices[i]->getY(); 
		countX++;
		countY++; 

	}
	
	averageX = totalX / countX;


	averageY = totalY / countY;

	//now saving rotateX and rotateY
	rotatePoly_xy_X = (int)averageX;
	rotatePoly_xy_Y = (int)averageY; 
	std::cout<<" the countX is "<< countX <<" the count Y is :" << countY <<endl; 
	std::cout<<" okay average dot is : ( " <<rotatePoly_xy_X <<" , " << rotatePoly_xy_Y <<")"<<endl;

	polygonStorage[polyFind]->storage[rotatePoly_xy_X][rotatePoly_xy_X] = new onScreenPixel(rotatePoly_xy_X, rotatePoly_xy_Y, false, mainWindowSizeWidth, mainWindowSizeHeight );
	polygonStorage[polyFind]->storage[rotatePoly_xy_X][rotatePoly_xy_X]->turnGreen(); 
	polygonStorage[polyFind]->centerX = rotatePoly_xy_X; 
	polygonStorage[polyFind]->centerY = rotatePoly_xy_Y; 
}


//TRANSLATING****************TRANSLATING****************TRANSLATING****************TRANSLATING****************
//***																									******
//**																									  ****
//TRANSLATING****************TRANSLATING****************TRANSLATING****************TRANSLATING****************

void translatePolygon(int X, int Y, string polyName)
{ 
		int translateX = X;
		int translateY = Y; 

		rotatePoly_findAvereage(polyName);
		int polyFind = returnPolyFind(polyName); 
		cout<<"here is center: "<<polygonStorage[polyFind]->centerX << " , " << polygonStorage[polyFind]->centerY <<endl; 

		int differenceX = translateX - polygonStorage[polyFind]->centerX ;
		int differenceY = translateY - polygonStorage[polyFind]->centerY ;

		for(int i = 0; i < polygonStorage[polyFind]->verticesSize ; i++)
		{


				cout<<" old x and y: "<< 	polygonStorage[polyFind]->vertices[i]->x << " , " << 	polygonStorage[polyFind]->vertices[i]->y <<endl; 
			polygonStorage[polyFind]->vertices[i]->x =polygonStorage[polyFind]->vertices[i]->x + differenceX; 
			polygonStorage[polyFind]->vertices[i]->y =polygonStorage[polyFind]->vertices[i]->y + differenceY; 
			cout<<" new x and y: "<< 	polygonStorage[polyFind]->vertices[i]->x << " , " << 	polygonStorage[polyFind]->vertices[i]->y <<endl; 

		}
		drawPolygonVertices(polyName); 
		//drawPolygonVertices(polygonStorage[polyFind]->Name); 
		drawAllPolygons(); 
}


//SCALING****************SCALING****************SCALING****************SCALING**********SCALING**********************
//***																									******
//**																									  ****
//SCALING****************SCALING****************SCALING****************SCALING**********SCALING**********************


void scalePolygon(int X,int Y,string polyName)
{
		double scaleX = X;
		double scaleY = Y; 

		//okay so does find middle
		rotatePoly_findAvereage(polyName);
		int polyFind = returnPolyFind(polyName); 

		//
		//!!!!!!ATENTION, still need to be able to scale doubles, like 0.5!!! 
		for(int i = 0; i < polygonStorage[polyFind]->verticesSize ; i++)
			{
			double fromCenterX = polygonStorage[polyFind]->vertices[i]->x - polygonStorage[polyFind]->centerX;
			double fromCenterY = polygonStorage[polyFind]->vertices[i]->y - polygonStorage[polyFind]->centerY;

			//if( fromCenterX >= 0 ) //directly top, or top right 
			//{
					//if(fromCenterY >= 0 ) //top right corner square
					//{
						polygonStorage[polyFind]->vertices[i]->x = (int)( (fromCenterX *scaleX) +  polygonStorage[polyFind]->centerX);
						polygonStorage[polyFind]->vertices[i]->y = (int)( (fromCenterY *scaleY) +  polygonStorage[polyFind]->centerY);
				//	}
				//	else if (fromCenterY < 0) //if Y is below 
			
			//}
						
			}
		cout<<"hopefully things go well"<<endl; 
		drawAllPolygons(); 
		rotatePoly_findAvereage(polyName);
}



//Rasterize******************Rasterize*******************Rasterize*********************Rasterize********************
//***																									******
//**																									  ****
//Rasterize******************Rasterize*******************Rasterize*********************Rasterize********************


void rasterizePolygon(string polyName, string color)
{

int polyFind = returnPolyFind(polyName);

eraseMainPixels();
drawPolygonVertices(polyName); 
bool isPaint = false; 

	cout<<"     ^^^^^Vertical Scan Line Algorithm^^^^^^^^"<<endl; 
	for(int i= 0; i < mainWindowSizeWidth; i++)
	   {		 isPaint = false; 
					for(int j= 0; j< mainWindowSizeHeight ; j++)
					{
						
						 if(isPaint == true && PixelTracker[i][j]->getIsEdge() == false)
						 {

						 
							 PixelTracker[i][j]->turnStatus = true; 
							 
							 PixelTracker[i][j]->isColor = true; 

							 if(color == "purple")
								PixelTracker[i][j]->turnPurple(); 
							 else if(color == "green")
									PixelTracker[i][j]->turnGreen(); 
							 else if(color == "red")
									PixelTracker[i][j]->turnRed(); 
							 		 else if(color == "blue")
									PixelTracker[i][j]->turnBlue();
									 else
										 PixelTracker[i][j]->turnYellow(); 
							}

				
						else if(PixelTracker[i][j]->getIsEdge() == true && isPaint == false )
						{
							isPaint = true; 
					
						}
						 /*
						else if(PixelTracker[i][j]->getIsEdge() == true && isPaint == true )
						{
							isPaint = false; 
						
						}
						*/
						  if( (PixelTracker[i][j]->getIsEdge() == true && isPaint == true && PixelTracker[i][j-1]->getIsEdge() == true)  )
						{
							isPaint = false; 
						
						}
						  
						  	  if( (PixelTracker[i][j]->getIsEdge() == true && isPaint == false && PixelTracker[i][j-1]->getIsEdge() == true)  )
						{
							isPaint = true; 
						
						}
						  

					};//end for loop


					if(PixelTracker[i][mainWindowSizeHeight-1]->getIsEdge() != true && PixelTracker[i][mainWindowSizeHeight-1]->turnStatus == true)
					{
					
								for(int j = mainWindowSizeHeight-1; j> 0 ; j--)
								{
									if(PixelTracker[i][j]->getIsEdge() == true)
									{
										break; 
									}
									PixelTracker[i][j]->turnStatus = false; 
									PixelTracker[i][j]->turnOFF(); 
									
									//PixelTracker[i][j]->turnYellow(); 
								}


					}//end if hits end
					
					
					
					
			
			     };
		cout<<"DONE ^^^^^Vertical Scan Line Algorithm^^^^^^^^^^^"<<endl<<endl; 

		for(int i = 0; i< polygonStorageSize; i++)
		{
		
			drawPolygonVertices(polygonStorage[i]->Name);
		
		}
							cout<<"autoredrawALL" <<endl; 
							for(int i = 0 ; i < polygonStorageSize ; i++)
							{
								cout<< " name:"<< polygonStorage[i]->Name<<endl; 
								if(polygonStorage[i]->Name != "" ) 
								drawPolygonVertices(polygonStorage[i]->Name); 
							}
		glutPostRedisplay(); 


}


//CLIPPING*************CLIPPING*************CLIPPING*************CLIPPING*************CLIPPING*************CLIPPING*************
//***																									******
//**																									  ****
//CLIPPING*************CLIPPING*************CLIPPING*************CLIPPING*************CLIPPING*************CLIPPING*************

void clipBelowY(int beginY, string polyName)
{

	eraseMainPixels();
	drawPolygonVertices(polyName); 

	//cout<<" type the y"<<endl; 
	int clipY = beginY;
	bool grabOne = false;
	bool grabTwo= false;
	int verticeOneX;
	int verticeOneY;
	int verticeTwoX;
	int verticeTwoY; 
	//cin>>clipY; 
	int polyFind = returnPolyFind(polyName); 
	int newX[10];
	int newY[10];
	int newCount = 0; 


	for(int i = 0; i < mainWindowSizeWidth; i++)
	{ //cout<<" did it get here?? "<<i<<endl; 
		if(PixelTracker[i][clipY]->isEdge == true && grabOne == false)
		{
		
				verticeOneX = PixelTracker[i][clipY]->x;
				verticeOneY = PixelTracker[i][clipY]->y;
				cout<<"grabbed at "<<verticeOneX<<","<<verticeOneY<<endl; 
				grabOne = true; 

		
		}
		else if(PixelTracker[i][clipY]->isEdge == true && grabTwo == false)
		{
		
				verticeTwoX = PixelTracker[i][clipY]->x;
				verticeTwoY = PixelTracker[i][clipY]->y;
					cout<<"grabbed at "<<verticeTwoX<<","<<verticeTwoY<<endl; 
				grabTwo = true; 

		
		}

					}//grabOne End


	
					if(grabOne == true && grabTwo == true)
					{//grabOne Start 
					
					bool firstPointBreak = false;
					bool secondPointBreak = false;
					newCount = 0; 
						for(int i = 0; i < polygonStorage[polyFind]->verticesSize; i++)
						{
							
							if(polygonStorage[polyFind]->vertices[i]->y < clipY && firstPointBreak == false)
							{
							newX[newCount] = verticeOneX;
							newY[newCount] = verticeOneY;
										cout<<"just adding to newcount :"<<newX[newCount]<<","<< 	newY[newCount]<< "new Count at "<<newCount<<endl; 
							newCount++;
						
							newX[newCount] = verticeTwoX;
							newY[newCount] = verticeTwoY;
									cout<<"just adding to newcount :"<<newX[newCount]<<","<< 	newY[newCount]<< "new Count at "<<newCount<<endl; 
									newCount++;
							cout<<"new Count at "<<newCount<<endl; 
							
							firstPointBreak = true; 
							//ignore basically 
							}
							else if(polygonStorage[polyFind]->vertices[i]->y < clipY && firstPointBreak == true)
							{
							cout<<"ignoreMoveOne"<<endl; 
							}
							else
							{
							newX[newCount] = polygonStorage[polyFind]->vertices[i]->x;
							newY[newCount] = polygonStorage[polyFind]->vertices[i]->y; 
							cout<<"just adding to newcount :"<<newX[newCount]<<","<< 	newY[newCount]<< "new Count at "<<newCount<<endl; 
							newCount++; 
							}
						
						}


						polygonStorage[polyFind]->verticesSize = newCount ; 
						cout<<"...check vertices size "<< polygonStorage[polyFind]->verticesSize <<endl; 
						for(int i = 0 ; i < polygonStorage[polyFind]->verticesSize; i++)
						{
							
							polygonStorage[polyFind]->vertices[i]->x = newX[i];
							polygonStorage[polyFind]->vertices[i]->y =newY[i]; 
						
						
						}
						eraseMainPixels();
						drawAllPolygons();
						//drawPolygonVertices(polyName); 
	}
	//polygon 28 is for clipping





}

void clipAboveY(int beginY, string polyName)
{

	eraseMainPixels();
	drawPolygonVertices(polyName); 

	//cout<<" type the y"<<endl; 
	int clipY = beginY;
	bool grabOne = false;
	bool grabTwo= false;
	int verticeOneX;
	int verticeOneY;
	int verticeTwoX;
	int verticeTwoY; 
	//cin>>clipY; 
	int polyFind = returnPolyFind(polyName); 
	int newX[10];
	int newY[10];
	int newCount = 0; 


	for(int i = 0; i < mainWindowSizeWidth; i++)
	{ //cout<<" did it get here?? "<<i<<endl; 
		if(PixelTracker[i][clipY]->isEdge == true && grabOne == false)
		{
		
				verticeOneX = PixelTracker[i][clipY]->x;
				verticeOneY = PixelTracker[i][clipY]->y;
				cout<<"grabbed at "<<verticeOneX<<","<<verticeOneY<<endl; 
				grabOne = true; 

		
		}
		else if(PixelTracker[i][clipY]->isEdge == true && grabTwo == false)
		{
		
				verticeTwoX = PixelTracker[i][clipY]->x;
				verticeTwoY = PixelTracker[i][clipY]->y;
					cout<<"grabbed at "<<verticeTwoX<<","<<verticeTwoY<<endl; 
				grabTwo = true; 

		
		}

					}//grabOne End


	
					if(grabOne == true && grabTwo == true)
					{//grabOne Start 
					
					bool firstPointBreak = false;
					bool secondPointBreak = false;
					newCount = 0; 
						for(int i = 0; i < polygonStorage[polyFind]->verticesSize; i++)
						{
							
							if(polygonStorage[polyFind]->vertices[i]->y > clipY && firstPointBreak == false)
							{
					
								newX[newCount] = verticeTwoX;
							newY[newCount] = verticeTwoY;
										cout<<"just adding to newcount :"<<newX[newCount]<<","<< 	newY[newCount]<< "new Count at "<<newCount<<endl; 
							newCount++;
								newX[newCount] = verticeOneX;
							newY[newCount] = verticeOneY;
						
									cout<<"just adding to newcount :"<<newX[newCount]<<","<< 	newY[newCount]<< "new Count at "<<newCount<<endl; 
									newCount++;
							cout<<"new Count at "<<newCount<<endl; 
							
							firstPointBreak = true; 
							//ignore basically 
							}
							else if(polygonStorage[polyFind]->vertices[i]->y > clipY && firstPointBreak == true)
							{
							cout<<"ignoreMoveOne"<<endl; 
							}
							else
							{
							newX[newCount] = polygonStorage[polyFind]->vertices[i]->x;
							newY[newCount] = polygonStorage[polyFind]->vertices[i]->y; 
							cout<<"just adding to newcount :"<<newX[newCount]<<","<< 	newY[newCount]<< "new Count at "<<newCount<<endl; 
							newCount++; 
							}
						
						}


						polygonStorage[polyFind]->verticesSize = newCount ; 


						cout<<"...check vertices size "<< polygonStorage[polyFind]->verticesSize <<endl; 
						for(int i = 0 ; i < polygonStorage[polyFind]->verticesSize; i++)
						{
							
							polygonStorage[polyFind]->vertices[i]->x = newX[i];
							polygonStorage[polyFind]->vertices[i]->y =newY[i]; 
						
						
						}
						eraseMainPixels();
						drawAllPolygons();
						//drawPolygonVertices(polyName); 
	}
	//polygon 28 is for clipping





}

void clipLeftX(int beginX, string polyName)
{

	eraseMainPixels();
	drawPolygonVertices(polyName); 

	//cout<<" type the y"<<endl; 
	int clipY = beginX;
	bool grabOne = false;
	bool grabTwo= false;
	int verticeOneX;
	int verticeOneY;
	int verticeTwoX;
	int verticeTwoY; 
	//cin>>clipY; 
	int polyFind = returnPolyFind(polyName); 
	int newX[10];
	int newY[10];
	int newCount = 0; 


	for(int i = 0; i < mainWindowSizeHeight; i++)
	{ //cout<<" did it get here?? "<<i<<endl; 
		if(PixelTracker[clipY][i]->isEdge == true && grabOne == false)
		{
		
				verticeOneX = PixelTracker[clipY][i]->x;
				verticeOneY = PixelTracker[clipY][i]->y;
				cout<<"grabbed at "<<verticeOneX<<","<<verticeOneY<<endl; 
				grabOne = true; 

		
		}
		else if(PixelTracker[clipY][i]->isEdge == true && grabTwo == false)
		{
		
				verticeTwoX = PixelTracker[clipY][i]->x;
				verticeTwoY = PixelTracker[clipY][i]->y;
					cout<<"grabbed at "<<verticeTwoX<<","<<verticeTwoY<<endl; 
				grabTwo = true; 

		
		}

					}//grabOne End


	
					if(grabOne == true && grabTwo == true)
					{//grabOne Start 
					
					bool firstPointBreak = false;
					bool secondPointBreak = false;
					newCount = 0; 
						for(int i = 0; i < polygonStorage[polyFind]->verticesSize; i++)
						{
							
							if(polygonStorage[polyFind]->vertices[i]->x   < clipY && firstPointBreak == false)
							{

								newX[newCount] = verticeOneX;
								newY[newCount] = verticeOneY;
								cout<<"just adding to newcount :"<<newX[newCount]<<","<< 	newY[newCount]<< "new Count at "<<newCount<<endl; 
								newCount++;

								newX[newCount] = verticeTwoX;
								newY[newCount] = verticeTwoY;
								cout<<"just adding to newcount :"<<newX[newCount]<<","<< 	newY[newCount]<< "new Count at "<<newCount<<endl; 
								newCount++;
								cout<<"new Count at "<<newCount<<endl; 
							
							firstPointBreak = true; 
							//ignore basically 
							}
							else if(polygonStorage[polyFind]->vertices[i]->x < clipY && firstPointBreak == true)
							{
							cout<<"ignoreMoveOne"<<endl; 
							}
						
							else
							{
							newX[newCount] = polygonStorage[polyFind]->vertices[i]->x;
							newY[newCount] = polygonStorage[polyFind]->vertices[i]->y; 
							cout<<"just adding to newcount :"<<newX[newCount]<<","<< 	newY[newCount]<< "new Count at "<<newCount<<endl; 
							newCount++; 
							}
						
						}


						polygonStorage[polyFind]->verticesSize = newCount ; 


						cout<<"...check vertices size "<< polygonStorage[polyFind]->verticesSize <<endl; 
						for(int i = 0 ; i < polygonStorage[polyFind]->verticesSize; i++)
						{
							
							polygonStorage[polyFind]->vertices[i]->x = newX[i];
							polygonStorage[polyFind]->vertices[i]->y =newY[i]; 
							cout<<"polygon vertices : "<<	polygonStorage[polyFind]->vertices[i]->x  << ", " << 		polygonStorage[polyFind]->vertices[i]->y <<endl; 
						
						}
						eraseMainPixels();
						drawAllPolygons();
						//drawPolygonVertices(polyName); 
	}
	//polygon 28 is for clipping left of X





}
void clipRightX(int beginX, string polyName)
{

	eraseMainPixels();
	drawPolygonVertices(polyName); 

	//cout<<" type the y"<<endl; 
	int clipY = beginX;
	bool grabOne = false;
	bool grabTwo= false;
	int verticeOneX;
	int verticeOneY;
	int verticeTwoX;
	int verticeTwoY; 
	//cin>>clipY; 
	int polyFind = returnPolyFind(polyName); 
	int newX[10];
	int newY[10];
	int newCount = 0; 


	for(int i = 0; i < mainWindowSizeHeight; i++)
	{ //cout<<" did it get here?? "<<i<<endl; 
		if(PixelTracker[clipY][i]->isEdge == true && grabOne == false)
		{
		
				verticeOneX = PixelTracker[clipY][i]->x;
				verticeOneY = PixelTracker[clipY][i]->y;
				cout<<"grabbed at "<<verticeOneX<<","<<verticeOneY<<endl; 
				grabOne = true; 

		
		}
		else if(PixelTracker[clipY][i]->isEdge == true && grabTwo == false)
		{
		
				verticeTwoX = PixelTracker[clipY][i]->x;
				verticeTwoY = PixelTracker[clipY][i]->y;
					cout<<"grabbed at "<<verticeTwoX<<","<<verticeTwoY<<endl; 
				grabTwo = true; 

		
		}

					}//grabOne End


	
					if(grabOne == true && grabTwo == true)
					{//grabOne Start 
					
					bool firstPointBreak = false;
					bool secondPointBreak = false;
					newCount = 0; 
						for(int i = 0; i < polygonStorage[polyFind]->verticesSize; i++)
						{
							
							if(polygonStorage[polyFind]->vertices[i]->x   > clipY && firstPointBreak == false)
							{

								newX[newCount] = verticeOneX;
								newY[newCount] = verticeOneY;
								cout<<"just adding to newcount :"<<newX[newCount]<<","<< 	newY[newCount]<< "new Count at "<<newCount<<endl; 
								newCount++;

								newX[newCount] = verticeTwoX;
								newY[newCount] = verticeTwoY;
								cout<<"just adding to newcount :"<<newX[newCount]<<","<< 	newY[newCount]<< "new Count at "<<newCount<<endl; 
								newCount++;
								cout<<"new Count at "<<newCount<<endl; 
							
							firstPointBreak = true; 
							//ignore basically 
							}
							else if(polygonStorage[polyFind]->vertices[i]->x > clipY && firstPointBreak == true)
							{
							cout<<"ignoreMoveOne"<<endl; 
							}
						
							else
							{
							newX[newCount] = polygonStorage[polyFind]->vertices[i]->x;
							newY[newCount] = polygonStorage[polyFind]->vertices[i]->y; 
							cout<<"just adding to newcount :"<<newX[newCount]<<","<< 	newY[newCount]<< "new Count at "<<newCount<<endl; 
							newCount++; 
							}
						
						}


						polygonStorage[polyFind]->verticesSize = newCount ; 


						cout<<"...check vertices size "<< polygonStorage[polyFind]->verticesSize <<endl; 
						for(int i = 0 ; i < polygonStorage[polyFind]->verticesSize; i++)
						{
							
							polygonStorage[polyFind]->vertices[i]->x = newX[i];
							polygonStorage[polyFind]->vertices[i]->y =newY[i]; 
							cout<<"polygon vertices : "<<	polygonStorage[polyFind]->vertices[i]->x  << ", " << 		polygonStorage[polyFind]->vertices[i]->y <<endl; 
						
						}
						eraseMainPixels();
						drawAllPolygons();
						//drawPolygonVertices(polyName); 
	}
	//polygon 28 is for clipping left of X





}

//*****************************************************************PROJECTTWO FUNCTIONS********************************************************************
//*****************************************************************PROJECTTWO FUNCTIONS********************************************************************
//*****************************************************************PROJECTTWO FUNCTIONS********************************************************************
//*****************************************************************PROJECTTWO FUNCTIONS********************************************************************
//*****************************************************************PROJECTTWO FUNCTIONS********************************************************************


//*****************************************************************/ MakeXYZPolygon /*****************************************************************
//*****************************************************************/                /*****************************************************************
//*****************************************************************/                /*****************************************************************
//*****************************************************************/				/*****************************************************************
//*****************************************************************/				/*****************************************************************










class xyzVertice
{
public: 

	int pointNumber; 
	int x;
	int y;
	int z;
		xyzVertice()
		{

		pointNumber = 0;//fornow might not need it? 

			x= 0; y = 0 ; z = 0; 
		}
	xyzVertice(int xx, int yy, int zz, int arrayPosition)
	{

	//	cout<<" testing get here? array position and intitialize"<<endl; 

	pointNumber = arrayPosition;//fornow might not need it? 

			x= xx; y = yy ; z = zz; 

		//	cout<<"x is "<<x<<endl; 
	}
};

class xyzEdge
{
public: 


	int  arrayStart;//gets directly set in the array's vertices. 
	int arrayEnd; //so it just directly, gets set in the array of the Vertices
	
				xyzEdge()
		{
			arrayStart =0;
			arrayEnd = 0;

		}
	xyzEdge(int starting, int ending)
		{
			arrayStart = starting; 
			arrayEnd = ending; 

		}



};



class xyzSurface
{
public: 
	string belongToPoly; 

	int surfaceNumber; 
	
	int centerX; 
	int centerY; 
	int centerZ; 
	int normalX;
	int normalY; 
	int normalZ; 

	int surfaceEdgesSize; 
	xyzEdge	*surfaceEdges[5];

	xyzSurface()
	{
	surfaceNumber = 0; 
	surfaceEdgesSize = 0; 
		
	int centerX=0; 
	int centerY=0; 
	int centerZ=0; 
	int normalX=0;
	int normalY=0; 
	int normalZ=0; 
	surfaceEdges[0] = new xyzEdge(0,0); 
		surfaceEdges[1] = new xyzEdge(0,0); 
			surfaceEdges[2] = new xyzEdge(0,0); 
				surfaceEdges[3] = new xyzEdge(0,0); 
					surfaceEdges[4] = new xyzEdge(0,0); 
	}
	xyzSurface(int sn)
	{
	surfaceNumber = sn; 

	}


};

class xyzPolygon
{
public:



	string Name;
	int centerX;
	int centerY;
	int centerZ; 

	int verticesSize; 
	int edgesSize; 
	//may not need these!
	onScreenPixel  *XY[50];
	onScreenPixelXZ *XZ[50];
	onScreenPixelYZ *YZ[50];


	xyzVertice *vertices[15];
	xyzEdge       *edges[50];  //which contains 2 vertices class, called starting and ending. 

	int surfacesSize; 
		xyzSurface    *surfaces[10];
			xyzPolygon(string n)
			{
				Name = n; 
				 centerX;
				 centerY=0;
				centerZ=0; 

	 			verticesSize=0; 
 				edgesSize=0; 
				surfacesSize=0; 
			}

			void eraseVertices(); 
			void findCenter(); 
};


void xyzPolygon::eraseVertices()
{
	cout<<"erasing vertices for XYZ"<<endl; 
		  for(int i = 0; i < 15; i++)
			     {   

					 vertices[i] =  new xyzVertice(0,0,0,i); 

					//cout<<"point number? lol"<< vertices[i]->pointNumber <<endl; 
			     }
		 		  for(int i = 0; i < 50; i++)
			     {   

					 edges[i] =  new xyzEdge(0,0); 

					//cout<<"point number? lol"<< vertices[i]->pointNumber <<endl; 
			     }
		 for(int i = 0; i < 10; i++)
			     {   

					 surfaces[i] = new xyzSurface(); 
						
					//cout<<"point number? lol"<< vertices[i]->pointNumber <<endl; 
			     }



}


void  xyzPolygon::findCenter()
{

						cout<<"going to average all the points, and find center of polygon!"<<endl; 
 
							 double totalX = 0; 
							 double  totalY = 0; 
							 double  totalZ = 0; 

								for(int i=0; i < verticesSize; i++)
								{
									totalX = totalX + vertices[i]->x; 
									totalY =  totalY +	vertices[i]->y;
									totalZ =  totalZ + vertices[i]->z; 

									cout<<" currently totalX "<<totalX << " currently totalY " <<totalY << "currently totalZ "<<totalZ <<endl; 
								}

								centerX = (int)(totalX/verticesSize); 
								centerY = (int)(totalY/verticesSize); 
								centerZ = (int)(totalZ/verticesSize); 
								cout<<" new centerX :"<<centerX << " new centerY: " <<centerY << " new centerZ: "<<centerZ<<endl; 

								DDAxyz(centerX, centerY, centerX, centerY, Name, PixelTracker); 
									DDAxyz(centerX, centerZ, centerX, centerZ, Name, PixelTrackerXZ); 
									DDAxyz(centerY, centerZ, centerY, centerZ, Name, PixelTrackerYZ); 

									PixelTracker[centerX][centerY]->turnRed(); 
									PixelTrackerXZ[centerX][centerZ]->turnRed(); 
									PixelTrackerYZ[centerY][centerZ]->turnRed(); 

}//end - findCenter()

class rotateLine
{

public:
	string belongToPoly; 
	int startX;
	int startY; 
	int startZ; 
	int endX; 
	int endY; 
	int endZ; 
	
	rotateLine()
	{
	startX = 0; startY = 0; startZ = 0; endX = 0; endY = 0; endZ = 0; 
	
	}

	rotateLine(int x, int y, int z, int xx, int yy, int zz)
	{
	startX = x; startY = y; startZ = z; endX = xx; endY = yy; endZ = zz; 
	
	}

	void eraseLine(); 
	void setLine(int x, int y, int z, int xx, int yy, int zz);
	void drawLine(); 
};
void rotateLine::eraseLine()
{

	startX = 0; startY = 0; startZ = 0; endX = 0; endY = 0; endZ = 0; 
}
void rotateLine::setLine(int x, int y, int z, int xx, int yy, int zz)
{
		startX = x; startY = y; startZ = z; endX = xx; endY = yy; endZ = zz; 
	
}

void rotateLine::drawLine()
{
	DDAxyz(startX, startY, endX, endY, "line", PixelTracker); 
	DDAxyz(startX, startZ, endX, endZ, "line",PixelTrackerXZ);
	DDAxyz(startY, startZ, endY, endZ, "line", PixelTrackerYZ); 


}
int xyzPolygonStorageSize =20; 
void xyzDrawVertices();
xyzPolygon *xyzPolygonStorage[25];


//CREATES a 3D Polygon, asks for inputs and edges that are connecting 
void makePyramidtesting()
													{   
														//initiate Polygons 


														cout<<"type in xyzPolygon Name"<<endl; 
														string polyName; 
														cin>>polyName; 
														int xyzFind;

														for(int i=0; i < xyzPolygonStorageSize; i++)
														{
														if(xyzPolygonStorage[i]->Name == "")
															{
																xyzPolygonStorage[i]->Name = polyName;
																xyzFind = i; 
																break; 
															}
														}
														//remember to make a xyzPolyFinder, 


														int countVerticeSize = 0; 
														int Vmove = 0; 
														bool breakVertices = false; 
														while(breakVertices == false )
														{	
															//omg hope this works Dear god please help me 
															countVerticeSize++; //this will always be 1 more than the "move"
															cout<<xyzPolygonStorage[xyzFind ]->Name <<" enter first 3, coordinates"<<endl;
																	cout<<"x:"<<xyzPolygonStorage[xyzFind ]->vertices[Vmove]->x<<endl; 
																	int inX; 
																	cin >> inX; 
																	xyzPolygonStorage[xyzFind ]->vertices[Vmove]->x = inX; 
																	cout<<"y:"<<endl; 
																	cin >> xyzPolygonStorage[xyzFind ]->vertices[Vmove]->y; 
																	cout<<"z:"<<endl; 
																	cin >> xyzPolygonStorage[xyzFind ]->vertices[Vmove]->z; 
																	cout<<" type yes, for more "<<endl; 
																	string answer; 
																	cin>>answer; 
																	if(answer == "yes" || answer =="Yes")
																	{  
																		Vmove++; 
																		cout<<"continuing right now..."<<endl;
																	}
																	else 
																	{
																		breakVertices = true; 
																		break; 
																	}
														}
														//once out of while loop, vertiSize should match...
														cout<<" Double Check verticeSize is correct...: "<< countVerticeSize<<"...Vmove, 1 less? : "<<Vmove<<endl; 
														xyzPolygonStorage[xyzFind]->verticesSize = countVerticeSize ; 

														int countEdgeSize = 0; 
														int EMove = 0; 
														bool breakEdges = false; 

														while(breakEdges == false)
														{
															countEdgeSize++; 
															cout<<"type the array ppoints connected, first one being *0* "<<endl; 
															cout<<"type first array point it connects to: "<<endl; 
															cin>>xyzPolygonStorage[xyzFind]->edges[EMove]->arrayStart; 
															cout<<"type, second array point it connects to:"<<endl; 
															cin>> xyzPolygonStorage[xyzFind]->edges[EMove]->arrayEnd; 

																cout<<" type yes, for more "<<endl; 
																	string answer; 
																	cin>>answer; 
																	if(answer == "yes" || answer =="Yes")
																	{  
																		EMove++; 
																		cout<<"\ncontinuing right now..."<<endl;
																	}
																	else 
																	{
																		breakVertices = true; 
																		break; 
																	}

														}
														cout<<" Checking, edgesSize is correct...:"<<countEdgeSize<<"...EMove 1 less?:"<<EMove<<endl; 
														xyzPolygonStorage[xyzFind]->edgesSize = countEdgeSize; 

														for(int i = 0; i < xyzPolygonStorage[xyzFind]->verticesSize; i++)
														{
															cout<<" Poly name is : "<< xyzPolygonStorage[xyzFind]->Name<<endl; 
															cout<<"vertices: "<<endl; 
															cout<<"( "<< xyzPolygonStorage[xyzFind]->vertices[i]->x<<","<<xyzPolygonStorage[xyzFind]->vertices[i]->y<<","; 
															cout<< xyzPolygonStorage[xyzFind]->vertices[i]->z<< " )"<<endl; 
														}

														for(int i = 0; i < xyzPolygonStorage[xyzFind]->edgesSize; i++)
														{
															cout<<" Poly name is : "<< xyzPolygonStorage[xyzFind]->Name<<endl; 
															cout<<"edges connect: "<<endl; 
															cout<<"here:  "<< xyzPolygonStorage[xyzFind]->edges[i]->arrayStart<<" to "<<xyzPolygonStorage[xyzFind]->edges[i]->arrayEnd<<endl; 

														}
													//initiate
												
													}

void readXYZ()
{
}
void xyzClearBoards(); 
void xyzDrawVertices(string polyName); 

rotateLine *rotateLineTemp; 

void xyzDrawAll()
{
	xyzClearBoards(); 
	//proj3 temperary take out 	
	//rotateLineTemp->drawLine(); 

	for(int i = 0; i < xyzPolygonStorageSize-1; i++)
	{
	
	if(xyzPolygonStorage[i]->Name != "")
		{
			cout<<" xyzPolygonStorage[i]->Name being drawnALL " << xyzPolygonStorage[i]->Name<<endl; 
			xyzDrawVertices(xyzPolygonStorage[i]->Name); 
			xyzPolygonStorage[i]->findCenter(); 
		}
	
	}

}

void xyzClearBoards()
{
cout<<" clearing all three boards"<<endl; 

	
for(int i= 0; i < mainWindowSizeWidth; i++)
{
	for(int j= 0; j< mainWindowSizeHeight ; j++)
	{
		if(PixelTracker[i][j]->turnStatus != true)
		{
		PixelTracker[i][j]->turnOFF(); 
		PixelTrackerXZ[i][j]->turnOFF(); 
		PixelTrackerYZ[i][j]->turnOFF(); 
		}
		if( j == 0 || i == 399 )
		{
		PixelTracker[i][j]->turnYellow(); 
		PixelTrackerXZ[i][j]->turnYellow(); 
		PixelTrackerYZ[i][j]->turnYellow(); 
		
		}
	};
	//cout<<" x test: "<<i <<" j test: " <<j<<endl; 
};


}
void xyzDrawVertices(string polyName)
{
	cout<<"attempt to draw after, storing all polygons, type polyname to be drawm: "<<endl; 
		int xyzFind = 0; 
		//string polyName; 
		//cin>>polyName; 
		for(int i=0; i < xyzPolygonStorageSize; i++)
		{
			if(xyzPolygonStorage[i]->Name == polyName)
			{  
				xyzFind = i; 
			}
		}

		for(int i = 0; i < xyzPolygonStorage[xyzFind]->edgesSize; i++)
		{
			//cout<<"here:  "<< xyzPolygonStorage[xyzFind]->edges[i]->arrayStart<<" to "<<xyzPolygonStorage[xyzFind]->edges[i]->arrayEnd<<endl; 
			cout<<" xyzFind is : "<< xyzFind << "name??"<<xyzPolygonStorage[xyzFind]->Name <<endl; 
			int aStart =xyzPolygonStorage[xyzFind]->edges[i]->arrayStart;
			int aEnd = xyzPolygonStorage[xyzFind]->edges[i]->arrayEnd; 
			//DDAxyz(x,y,x,y,polyName,pixelbuffer? 	); 
			DDAxyz(xyzPolygonStorage[xyzFind]->vertices[aStart]->x , xyzPolygonStorage[xyzFind]->vertices[aStart]->y ,xyzPolygonStorage[xyzFind]->vertices[aEnd]->x , xyzPolygonStorage[xyzFind]->vertices[aEnd]->y ,polyName, PixelTracker); // for XY plane
			cout<<" did it get to XZ?"<<endl; 
			DDAxyz(xyzPolygonStorage[xyzFind]->vertices[aStart]->x , xyzPolygonStorage[xyzFind]->vertices[aStart]->z ,xyzPolygonStorage[xyzFind]->vertices[aEnd]->x , xyzPolygonStorage[xyzFind]->vertices[aEnd]->z ,polyName, PixelTrackerXZ); // for XZ plane
			cout<<" did it get to YZ?"<<endl; 
			//did this break? it seems the edges are not recognized. lol. 
			DDAxyz(xyzPolygonStorage[xyzFind]->vertices[aStart]->y , xyzPolygonStorage[xyzFind]->vertices[aStart]->z ,xyzPolygonStorage[xyzFind]->vertices[aEnd]->y , xyzPolygonStorage[xyzFind]->vertices[aEnd]->z ,polyName, PixelTrackerYZ); // for YZ plane

		}

		//maybe add a line -redraw for rotating

glutPostRedisplay(); 


}//end xyzDrawVertices()
int xyzReturnFind(string name); 

void xyzClip() //how you choose to clip? 
{


}

void xyzScale()
{
	cout<<"polyName to be scaled"<<endl; 
	string polyName; 
	int xyzFind; 
	cin>>polyName; 
	xyzFind = xyzReturnFind(polyName); 
	cout<<" type the X scale factor"<<endl; 
	double X; 
	cin>>X; 
	cout<<" type in the Y scale factor"<<endl; 
	double Y; 
	cin>>Y; 
	cout<<"Type in the Z scale factor"<<endl; 
	double Z; 
	cin>>Z; 

	double scaleX = X;
		double scaleY = Y; 
		double scaleZ = Z; 
		//okay so does find middle
	
		xyzPolygonStorage[xyzFind]->findCenter(); 
		//
		//!!!!!!ATENTION, still need to be able to scale doubles, like 0.5!!! 
		for(int i = 0; i < xyzPolygonStorage[xyzFind]->verticesSize ; i++)
			{
			double fromCenterX =  xyzPolygonStorage[xyzFind]->vertices[i]->x -  xyzPolygonStorage[xyzFind]->centerX;
			double fromCenterY =  xyzPolygonStorage[xyzFind]->vertices[i]->y -  xyzPolygonStorage[xyzFind]->centerY;
			double fromCenterZ =  xyzPolygonStorage[xyzFind]->vertices[i]->z -  xyzPolygonStorage[xyzFind]->centerZ;

			 xyzPolygonStorage[xyzFind]->vertices[i]->x = (int)( (fromCenterX *scaleX) +   xyzPolygonStorage[xyzFind]->centerX);
			 xyzPolygonStorage[xyzFind]->vertices[i]->y = (int)( (fromCenterY *scaleY) +   xyzPolygonStorage[xyzFind]->centerY);
			xyzPolygonStorage[xyzFind]->vertices[i]->z = (int)( (fromCenterZ *scaleZ) +   xyzPolygonStorage[xyzFind]->centerZ);

						
			}

	//	xyzDrawAll(); 
}// End xyzScale


void xyzTranslate()
{
	
	cout<<" type in PolyName"<<endl; 
	string polyName; 
	cin>> polyName; 
	int xyzFind = xyzReturnFind(polyName); 

	xyzPolygonStorage[xyzFind]->findCenter(); 
	cout<<" the center coordinates are: "<<endl; 
	cout<<"( "<<xyzPolygonStorage[xyzFind]->centerX<<" , "<<xyzPolygonStorage[xyzFind]->centerY<<" , "<<xyzPolygonStorage[xyzFind]->centerZ << " ) " <<endl; 
	cout<<" type the x y z where you want the polygon to translate to"<<endl; 
	int newCenterX;
	int newCenterY;
	int newCenterZ; 
	cin>>newCenterX;
	cin>>newCenterY;
	cin>>newCenterZ; 


	int differenceX = newCenterX - xyzPolygonStorage[xyzFind]->centerX; 
	int differenceY = newCenterY - xyzPolygonStorage[xyzFind]->centerY; 
	int differenceZ = newCenterZ - xyzPolygonStorage[xyzFind]->centerZ; 
		for(int i = 0; i < xyzPolygonStorage[xyzFind]->verticesSize ; i++)
		{

			xyzPolygonStorage[xyzFind]->vertices[i]->x = xyzPolygonStorage[xyzFind]->vertices[i]->x + differenceX; 
			xyzPolygonStorage[xyzFind]->vertices[i]->y = xyzPolygonStorage[xyzFind]->vertices[i]->y + differenceY; 
					
			xyzPolygonStorage[xyzFind]->vertices[i]->z = xyzPolygonStorage[xyzFind]->vertices[i]->z + differenceZ; 
		}

		xyzDrawVertices(polyName); 

}


int xyzReturnFind(string name)
{
	cout<<" using returnFind "<<endl; 
	int polyNumber=0; 
	for(int i = 0; i < polygonStorageSize; i++)
	{
			if(xyzPolygonStorage[i]->Name == name)
			{
			
			polyNumber = i; 
			break; 
			}
	
	}

	return polyNumber; 

}

void xyzRotate()
{

// source: http://inside.mines.edu/fs_home/gmurray/ArbitraryAxisRotation/ 

string polyName; 
cout<<" type in polyName to be rotated"<<endl; 
cin>>polyName; 
int polyFind; 

for(int i = 0; i < xyzPolygonStorageSize; i++)
{
		if(xyzPolygonStorage[i]->Name == polyName)
		{
			polyFind = i ; 
			break; 
		}
}
double oneX,oneY,oneZ;
double twoX,twoY,twoZ; 
double u, v, w; 

double newX, newY, newZ; 
double tempX, tempY, tempZ; 
double degrees;//remember to CHANCE TO RADIANS
	double degreesIn;

for( int Cmove = 0; Cmove <3; Cmove++)
					{			
						cout<<" type in the two points to rotate around the axis"<<endl; 
						cin>>oneX; 
						cin>>oneY;
						cin>>oneZ;
						cout<<" next coordinates for second point:"<<endl;
						cin>>twoX;
						cin>>twoY;
						cin>>twoZ; 
					//DDAxyz(oneX, oneY, twoX,twoY, "line", PixelTracker); 
					//	DDAxyz(oneX, oneZ, twoX,twoZ, "line", PixelTrackerXZ); 
					//	DDAxyz(oneY, oneZ, twoY,twoZ, "line", PixelTrackerYZ); 
						//rotateLineTemp->startX; 
						rotateLineTemp->setLine(oneX, oneY,oneZ,twoX,twoY,twoZ); 
						rotateLineTemp->drawLine(); 
						glutPostRedisplay(); 

						cout<<"type in how many degrees to roate around"<<endl; 
					
						cin>>degreesIn; 

						cout<<"does this axis look good? yes to continue"<<endl; 
						string yesNo; 

						//cin>>yesNo; 
						yesNo = "yes"; //force break for now, because line doesn't show up imediately, but it will show up later. 
						if(yesNo == "yes" || yesNo == "Yes")
						{
						cout<<"confirm rotate, now drawing"<<endl; 
						break; 
						}
					}//end for loop for changing axis option
u =twoX-oneX; 
v = twoY - oneY; 
w = twoZ - oneZ; 
cout<<" u,v, w :" << u<<"   "<<v<< "   "<< w <<endl; 
degrees = ( ( degreesIn * 3.14159 ) / 180); 
cout<<"degrees is : "<< degrees <<endl; 
//newX = oneX; 
double L = u*u + v*v + w*w; 
double squareL = sqrt(L); 
for(int i = 0; i < xyzPolygonStorage[polyFind]->verticesSize; i++)
{
	tempX = (double)xyzPolygonStorage[polyFind]->vertices[i]->x; 
	tempY = (double)xyzPolygonStorage[polyFind]->vertices[i]->y; 
	tempZ = (double)xyzPolygonStorage[polyFind]->vertices[i]->z; 
	newX =(    ( ( (oneX*(v*v + w*w )) - ( u*(oneY*v + oneZ*w - u*tempX - v*tempY - w*tempZ))  )*(1 - cos(degrees))  )  + L*(tempX*cos(degrees)) +   squareL* ((-oneZ)*v + oneY*w - w*tempY + v*tempZ)*sin(degrees)      )/L; 

	newY =(		((  (oneY*(u*u + w*w )) - ( v*(oneX*u + oneZ*w - u*tempX - v*tempY - w*tempZ)) )    *     (1 - cos(degrees)) ) + L*(tempY*cos(degrees)) +  squareL*  (oneZ*u - oneX*w + w*tempX - u*tempZ )*sin(degrees)    )/L;

	newZ =(		((  (oneZ*(u*u + v*v )) - ( w*(oneX*u + oneY*v - u*tempX - v*tempY - w*tempZ)) )    *      (1 - cos(degrees)) ) + L*(tempZ*cos(degrees)) +   squareL*((-oneY*u) + oneX*v - v*tempX + u*tempY )*sin(degrees)     )/L;
		
	
	
	cout<<" doubles from temps, new coordinates?..."<<  i <<"... ( "<< newX<<" , " << newY << " , "<<newZ<<" )"<<endl;  
	cout<<" ints temps, new coordinates?..."<<  i <<"... ( "<< (int)newX<<" , " << (int)newY << " , "<<(int)newZ<<" )"<<endl;  
xyzPolygonStorage[polyFind]->vertices[i]->x =   (int)newX; 
xyzPolygonStorage[polyFind]->vertices[i]->y =   (int)newY;
xyzPolygonStorage[polyFind]->vertices[i]->z =   (int)newZ;


}
//omg i hope this works. 

cout<<" type anything to continue after done seeing the rotate line "<<endl; 
//string anything; 
//cin>> anything; 


}



//*******************PROJECT 3*********************
//*************       START       *****************
//*************                   *****************
//*************************************************
//*************************************************

// Things to include, Phong Model, Gouraud Shading, Painter’s Algorithm  , Halftone

//recursive for tight boundaries.
void colorRecursive(int inX, int inY, int Num)
{
    
    int x = inX;
    int y = inY;
    // testlimit -= 1;
    cout<<"test limit is currently at "<< testlimit <<endl;
    PixelTracker[x][y]->turnGreen();
    
    // Right, DOwn Left, Up
    if( PixelTracker[x+1][y]->turnStatus == false &&  PixelTracker[x+1][y]!=NULL &&  PixelTracker[x+1][y]->getIsEdge() == false)
    {
        PixelTracker[x+1][y]->turnStatus = true;
        colorRecursive(x+1, y,Num );
        go1 = false;
    }
    //
    
    
    if( PixelTracker[x][y-1]->turnStatus == false && PixelTracker[x][y-1] !=NULL &&  PixelTracker[x][y-1]->getIsEdge() == false )
    {
        PixelTracker[x][y-1]->turnStatus = true;
        colorRecursive(x, y-1, Num );
        go2 = false;
    }
    
    
    if( PixelTracker[x-1][y]->turnStatus == false && PixelTracker[x-1][y] !=NULL &&  PixelTracker[x-1][y]->getIsEdge() == false )
    {
        PixelTracker[x][y-1]->turnStatus = true;
        colorRecursive(x-1, y, Num );
        go3 = false;
    }
    if( PixelTracker[x][y+1]->turnStatus == false && PixelTracker[x][y+1] !=NULL &&  PixelTracker[x][y+1]->getIsEdge() == false )
    {
        
        PixelTracker[x-1][y]->turnStatus = true;
        colorRecursive(x, y+1, Num  );
        
        //testlimit = 20;
        go4 = false;
    }
    
    
    
}


double lightX, lightY, lightZ; 
double lightFX, lightFY, lightFZ; 




void phongFunction()
{
	cout<<" type in light X - light source position"<<endl; 
	cin>> lightX; 
	cout<<" type in light Y - light source position"<<endl; 
	cin>> lightY;
	cout<<" type in light Z - light source position"<<endl; 
	cin>> lightZ;

	cout<<" type in the light point f, X " <<endl; 
	cin>> lightFX;
	cout<<" type in the light point f, Y " <<endl; 
	cin>> lightFY;
	cout<<" type in the light point f, Z " <<endl; 
	cin>> lightFZ;

	//used for calculating normals I hope 
	http://onlinemschool.com/math/assistance/cartesian_coordinate/plane/


	//returns intensity; 
	
	double Ip=0, Ka=0, Ia=0, Il=0, f=0, p=0, K=0, Kd=0, l_vector=0, n_vector=0, Ks=0, r_vector=0, v_vector=0, n=1; 
	double l_vectorX=0, l_vectorY=0, l_vectorZ=0; //light vector can be standard, to the origin, 
	double n_vectorX=0, n_vectorY=0, n_vectorZ=0;  //THIS one is calculated, for EACH surface. 
	double r_vectorX=0, r_vectorY=0, r_vectorZ=0; //CALCULATE THIS - this is the same ANGLE, as the light ANGLE to the NORMAL 
	double v_vectorX=0, v_vectorY=0, v_vectorZ=0; // this depends, on EACH SCREEN, where it is basically viewed from XY, XZ, YZ etc; 
	//first calculate two vectors with two vertices on a surface. 
    double partOne=0, partTwo=0, partThree=0, partFour=0; 
	double dotOne=0, dotTwo=0;
	double degrees=0, radians=0; 
	//dot product is done by, |a| x |b| x cos(theta) ; where theta is the angle between the vectors. and its maginitude of A and B
	int verticeA_X=0, verticeA_Y=0, verticeA_Z=0, verticeB_X=0, verticeB_Y=0, verticeB_Z=0, verticeC_X=0, verticeC_Y=0, verticeC_Z=0, verticeD_X=0, verticeD_Y=0, verticeD_Z=0;
	//*****Set verticeA, B, C, D ; 
	// for Light Vectors, and Normal
	double magLight =  sqrt(  ((verticeB_X - verticeA_X )^2) + ((verticeB_Y - verticeA_Y )^2) +((verticeB_Z - verticeA_Z )^2)   ) ; //could be used for Light? 
	double magNormal =  sqrt(  ((verticeD_X - verticeC_X )^2) + ((verticeD_Y - verticeC_Y )^2) +((verticeD_Z - verticeC_Z )^2)   ) ; // tihs one saved for normal?? 
	degrees = 0; 
	radians =  (degrees*3.14)/180; 
	dotOne = magLight * magNormal * cos(radians); //hopefully this is correct... cosRadians would be in relation to the plane, where the plane is the origin. wher Vertice A is the origin, 
												//there for example if vertice a is 45, 60, 30, then i believe you add those? to the vertices? 45+verticeBX , 60+verticeBY, 30+verticeBZ? 
												//****set VerticeA,B,C,D; 
											// for reflect Vector, and View Vector. 



		double magReflection  =  sqrt(  ((verticeB_X - verticeA_X )^2) + ((verticeB_Y - verticeA_Y )^2) +((verticeB_Z - verticeA_Z )^2)   ) ; //could be used for Light? 
		double magView  =  sqrt(  ((verticeD_X - verticeC_X )^2) + ((verticeD_Y - verticeC_Y )^2) +((verticeD_Z - verticeC_Z )^2)   ) ; // tihs one saved for normal?? 
		degrees = 0; 
		radians = (degrees*3.14)/180; 
		dotTwo  = magReflection * magView * cos(radians); 



	partOne = Ka*Ia;
	partTwo = (Il) / ( (f - p ) + K         );
	partThree = Kd*( dotOne); // need to fix, it needs to be dot product, so whatever that means
   // partFour = Ks* (dotTwo^n) ; //this power sign might be off? maybe it isn't ^ 

	Ip = partOne + (partTwo * ( partThree + partFour ) ); 

}

void gauraudShading()
{


}


void hiddenSurface()
{
//first work on this to remove all hidden surfaces. 
//may have to modify pixel properties? to overlap each other? 
//looks like just remove the vertices that are behind, the other vertices. each time . then even after you rotate, simply check if there is a vertice behind all the other vertices. 
}


		onScreenPixel	*RasTracker[2000][1200]; 
template<typename T>
void rasterizeXYZ(string polyName, string color,  T *(*RasTracker)[1200] ) // pass in surface, and color, and polygon. // 
{

//copy paste on to temp, PixelTracker, and then paste it ON TOP of selectTracker
	/*
	for(int i= 0; i < mainWindowSizeWidth; i++)
	{

		for(int j= 0; j< mainWindowSizeHeight ; j++)
		{



			if(selectTracker[i][j]->isEdge == true)
			{
				RasTracker[i][j]->isEdge = true; 

			}
		}
	}
	*/
int polyFind = xyzReturnFind(polyName);

//eraseMainPixels();
//drawPolygonVertices(polyName); 
bool isPaint = false; 

		for(int i= 1; i < mainWindowSizeWidth; i++)
	   {	
		   for(int j= 1; j<35 ; j++)
					{
						  PixelTracker[i][j]->turnStatus = false;
						  PixelTracker[i][j]->isEdge = false; 
						   PixelTracker[i][j]->turnOFF();  

		   }

}

	

	cout<<"   Vertical Scan line - alogorithm "<<endl; 
	for(int i= 1; i < mainWindowSizeWidth; i++)
	   {			isPaint = false; 
					bool backTrack = false; 
					bool edgeHit = false; 
					for(int j= 1; j< mainWindowSizeHeight ; j++)
					{
						if(RasTracker[i][j]->getIsEdge() == true )
						{
						  RasTracker[i][j]->turnRed(); 
						  RasTracker[i][j]->turnStatus = true; 
						}

						if(isPaint == false && edgeHit == false)
						{
						
						 //PTracker[i][j]->turnStatus = true; 
							// PTracker[i][j]->isColor = true; 
							//PTracker[i][j]->turnGreen(); 
						}
							//cout<<" grabbing at this location "<< i <<", "<< j <<endl; 
						 if(isPaint == true && RasTracker[i][j]->getIsEdge() == false && backTrack == false)
						 {
							 RasTracker[i][j]->turnStatus = true; 
							 RasTracker[i][j]->isColor = true; 
							 if(color == "purple")
								 RasTracker[i][j]->turnPurple(); 
							 else if(color == "green")
								 RasTracker[i][j]->turnGreen(); 
							 else if(color == "red")
								 RasTracker[i][j]->turnRed(); 
							 else if(color == "blue")
								 RasTracker[i][j]->turnBlue();
							  else if(color == "cyan")
								 RasTracker[i][j]->turnCyan(); 
							 else
								 RasTracker[i][j]->turnYellow(); 
						 }
						 
						 else if(RasTracker[i][j]->getIsEdge() == true && isPaint == false  && backTrack == false)
						 {
							 isPaint = true; 
							 edgeHit = true; 
							 RasTracker[i][j]->turnRed(); 

						 }
						 else if (backTrack == true )
						 {
						  break; 
						 
						 }
						  /*
						  if( (PTracker[i][j]->getIsEdge() == true && isPaint == true && PTracker[i][j-1]->getIsEdge() == true)  )
						{
							isPaint = false; 
						
						}
						 if( (PTracker[i][j]->getIsEdge() == true && isPaint == false && PTracker[i][j-1]->getIsEdge() == true)  )
						{
							isPaint = true; 
						
						}
						*/  

					};//end for loop
					if(RasTracker[i][mainWindowSizeHeight-1]->getIsEdge() != true && RasTracker[i][mainWindowSizeHeight-1]->turnStatus == true)
					{
					
								for(int j = mainWindowSizeHeight-1; j> 0 ; j--)
								{
									if(RasTracker[i][j]->getIsEdge() == true)
									{
										break; 
										isPaint = false; 
										backTrack = true; 
									}
									
									PixelTracker[i][j]->turnOFF(); 
									RasTracker[i][j]->turnStatus = false; 
									//RasTracker[i][j]->turnYellow(); 
									RasTracker[i][j]->isColor = false; 
								}
					}//end if hits end			
			     };

		cout<<"DONE ---------XYZ   Vertical Scan Line Algorithm----------"<<endl<<endl; 

		string blank;
		//cin>>blank; 

		//copies paste RasTracker ontop, on whatever pixel buffer is being passed through
		/*
			for(int i= 0; i < mainWindowSizeWidth; i++)
			{

				for(int j= 0; j< mainWindowSizeHeight ; j++)
				{



					if(RasTracker[i][j]->isColor == true)
					{  

						//cout<<"work at all? is color?"<<endl; 
						selectTracker[i][j]->turnGreen(); 
						selectTracker[i][j]->turnStatus = true; 

					}
					RasTracker[i][j]->isEdge = false;
					RasTracker[i][j]->turnOFF(); 
					RasTracker[i][j]->isColor = false;
					RasTracker[i][j]->turnStatus = false;
				}
			}
			*/










		//might, have to directly fix this in isolate. function, where it turns the edges to "isColor" so, it knows which edges to color is 
/*
		for(int i= 1; i < mainWindowSizeWidth; i++)
	   {	
		   for(int j= 1; j< mainWindowSizeHeight ; j++)
					{    
						 
						if(PTracker[i][j]->isEdge == true)
						{
							PTracker[i][j]->turnStatus = false;
						  PTracker[i][j]->isEdge = false; 
						}
					

					}
	

			}
		*/
		

		glutPostRedisplay(); 


}
void DDAxyzBetter(string name, xyzVertice *start, xyzVertice *end); 

void isolateSurface(string name, int surfaceNumber)
{

	int polyFind = xyzReturnFind(name); 
		xyzVertice *starting;
		xyzVertice *ending  ;

	for(int i = 0; i < xyzPolygonStorage[polyFind]->surfaces[surfaceNumber]->surfaceEdgesSize ; i++)
	{
			starting = xyzPolygonStorage[polyFind]->vertices[xyzPolygonStorage[polyFind]->surfaces[surfaceNumber]->surfaceEdges[i]->arrayStart];
			ending   =	xyzPolygonStorage[polyFind]->vertices[xyzPolygonStorage[polyFind]->surfaces[surfaceNumber]->surfaceEdges[i]->arrayEnd]; 
		    DDAxyzBetter(name, starting, ending); 

	}



	
	

}

void DDAxyzBetter(string name, xyzVertice *start, xyzVertice *end)
{

	int polyFind = xyzReturnFind(name); 
	DDAxyz(start->x, start->y, end->x, end->y,name ,PixelTracker); 
	DDAxyz(start->x, start->z, end->x, end->z,name ,PixelTrackerXZ); 
	DDAxyz(start->y, start->z, end->y, end->z,name ,PixelTrackerYZ); 
	
}



//*************************************************
//*************************************************
//*************                   *****************
//*************        END        *****************
//*******************PROJECT 3*********************






//*************************************************//*******************PROJECT 4 *********************//*******************PROJECT 4 *********************//*******************PROJECT 4 *********************
//*************************************************
//*************                   *****************//*******************PROJECT 4 *********************//*******************PROJECT 4 *********************//*******************PROJECT 4 *********************
//*************        START        *****************
//*******************PROJECT 4 *********************//*******************PROJECT 4 *********************//*******************PROJECT 4 *********************//*******************PROJECT 4 *********************




class controlPoint
{
public: 

	int x;
	int y;

	controlPoint()
	{
		x=0; 
		y=0; 
	}
	
	controlPoint(int xx, int yy, string name)
	{
		x = xx;
		y = yy;
	}
};


class bezierCurve
{
public:
	string curveName; 
	int startX; 
	int startY;
	int endX;
	int endY;
	int controlPointsSize; 
	controlPoint *controlPoints[20];
	bezierCurve()
	{
		startX = 0; startY = 0; endX = 0; endY = 0; curveName = ""; 
		controlPointsSize = 0; 
	}
	bezierCurve(string name)
	{

		startX = 0; startY = 0; endX = 0; endY = 0; curveName = name; 
		controlPointsSize = 0; 
	}
	void initiate(); 

};

void bezierCurve::initiate()
{
		for(int i = 0; i < 20; i ++)
		{
		controlPoints[i] = new controlPoint(); 
		}

}


bezierCurve *storageBezierCurves[10];



//Maybe this is Total, after ALLL control points? //textbook page 421. 
//Cite: http://www.malinc.se/m/DeCasteljauAndBezier.php

void bezierCurveFunction(string Name); 
void drawControlPointsLines(string CName);
void drawControlPoint(int x, int y);
void makeCurve()
{
	cout<<"type in CurveName"<<endl; 
	string selectedName; 
	cin>>selectedName; 
	int bezierCurveFind=0; 
				for(int i = 0 ; i < 10; i++)
				{
					if(storageBezierCurves[i]->curveName != "")
					{			
					bezierCurveFind = i; 
					storageBezierCurves[i]->curveName = selectedName; 	
					}
				}
	

		cout<<"type in number of control points:"<<endl; 
		int controlP;
		cin>>controlP; 
		storageBezierCurves[bezierCurveFind]->controlPointsSize = controlP; 

						for(int i = 0; i < storageBezierCurves[bezierCurveFind]->controlPointsSize ; i++)
						{
						cout<<" type in points for arrayPosition: "<<i<<endl; 
						cout<<"for x: "; 
						int xx; 
						cin>>xx;
						storageBezierCurves[bezierCurveFind]->controlPoints[i]->x = xx; 
						cout<<"for y: "; 
						int yy; 
						cin>>yy;
						storageBezierCurves[bezierCurveFind]->controlPoints[i]->y = yy; 
						 DDAxyz(xx,yy,xx,yy,"testing",PixelTracker); 
						 drawControlPoint(xx,yy); 
						}

	for(int i = 0; i < storageBezierCurves[bezierCurveFind]->controlPointsSize ; i++)
	{
		cout<<"final array Positions and their x and y's. ["<<i<<"] x:"<<storageBezierCurves[bezierCurveFind]->controlPoints[i]->x<<" y:"<<storageBezierCurves[bezierCurveFind]->controlPoints[i]->y<<endl; 
	}
	drawControlPointsLines(storageBezierCurves[bezierCurveFind]->curveName); 

	cout<<" continute with trying to draw curve? "<<endl; 
	string blank;
	cin>>blank; 
	bezierCurveFunction(storageBezierCurves[bezierCurveFind]->curveName); 



}//end makeCurve()

void initiateAllCurves()
{
	for(int i = 0 ; i < 10; i++)
	{
		storageBezierCurves[i] = new bezierCurve(""); 
		storageBezierCurves[i]->initiate(); 
	}

}

//this makes a cross, where the control points are selected. 
void drawControlPoint(int x, int y)
{

	DDAxyz(x-3,y+3,x+3,y-3,"points",PixelTracker); 
	
	DDAxyz(x+3,y+3,x-3,y-3,"points",PixelTracker); 

}

int returnCurveFind(string name);

void drawControlPointsLines(string CName)
{
	int curveFind = returnCurveFind(CName); 
	int x=0, y=0, xx=0, yy=0; 

	for(int i=0; i<storageBezierCurves[curveFind]->controlPointsSize-1;i++)
	{

		drawControlPoint(storageBezierCurves[curveFind]->controlPoints[i]->x,storageBezierCurves[curveFind]->controlPoints[i]->y); 
		drawControlPoint(storageBezierCurves[curveFind]->controlPoints[i+1]->x,storageBezierCurves[curveFind]->controlPoints[i+1]->y); 
		x = storageBezierCurves[curveFind]->controlPoints[i]->x;
		y = storageBezierCurves[curveFind]->controlPoints[i]->y;
		xx = storageBezierCurves[curveFind]->controlPoints[i+1]->x;
		yy = storageBezierCurves[curveFind]->controlPoints[i+1]->y;

		DDAxyz(x,y,xx,yy, storageBezierCurves[curveFind]->curveName, PixelTracker);


	}


}


int returnCurveFind(string name)
{
	int curveFind=0; 
	for(int i=0; i < 10; i++)
	{
		if(storageBezierCurves[i]->curveName == name)
		{
		curveFind = i; 
		break; 
		}
	}

	return curveFind; 

}


double factorialize(double n);

void bezierCurveFunction(string CName)
{
	int curveFind= returnCurveFind(CName);
	storageBezierCurves[curveFind]->controlPoints[0]->x; 
	//no for the algorithem LOLOL what to do

	//Quadratic bezier curves, so 3 points
	int newX = 0;
	int newY = 0; 
	double tX = 0; 
	double tY = 0; 
	double tMove = 0; // for 0 -> 1 

	//the whole algorithm for beizerCurve, recursive is done here:
																													
	for( tMove = 0; tMove < 1; tMove = tMove+0.001)
	{

		tX = 0; 
		tY = 0; 
		for( double pointMove = 0 ; pointMove < storageBezierCurves[curveFind]->controlPointsSize; pointMove++) // this is for each point, in the array. p0, p1, etc
		{
			double n = storageBezierCurves[curveFind]->controlPointsSize-1; 
			double xX = storageBezierCurves[curveFind]->controlPoints[(int)pointMove]->x; 
			double yY  = storageBezierCurves[curveFind]->controlPoints[(int)pointMove]->y; 

			double BinomialCo =  factorialize(n) / (  factorialize(pointMove)*factorialize(n-pointMove)  ) ;  // this is  

			tX += BinomialCo* pow((1 - tMove),(n - pointMove)) * pow((tMove),pointMove ) *  xX   ;

			tY +=  BinomialCo* pow((1 - tMove),(n - pointMove)) * pow((tMove),pointMove ) *  yY   ;


			//	cout<<"curve coordinates? :"<<tX<<","<<tY<<endl; 



		}


		PixelTracker[(int)tX][(int)tY]->turnRed(); 
		PixelTracker[(int)tX][(int)tY]->turnYellow(); 
	}




}

//cite: http://stackoverflow.com/questions/5721796/how-do-you-implement-the-factorial-function-in-c
double factorialize(double n)
{
	double answer = 0;

	if(n != 0 )
	{
		answer = n*factorialize( n-1 );
		return  answer; 
	}
	else if( n == 0)
	{

		return 1; 
	}

}

//This would be a continuues, algorithm, for every 4 points of a beziercurve control points. 

void bezierFourPointJoin()
{


}

void BSplineCurve(string CName)
{

	int CurveFind = returnCurveFind(CName); 
	double p = 0; 
	double k = 0;  

	double bX = 0; 
	double bY = 0; 
	double u = 0; 
	double uK = 0; //U might be points? dl points? demoor points?? 

	double UsegmentX[10]; //so k can devide up to 10 maybe?
	double DLJI[10];

	//storageBezierCurves[returnCurveFind]->


}


class XAndY
{
public: 

	double x; 
	double y; 

	XAndY()
	{
	x=0; 
	y=0; 
	};


};


void deBoorsMake(string CName);
void deBoors()
{
cout<<"type in curveName to make DeBoors with"<<endl; 
string name; 
cin>>name; 
deBoorsMake(name);


}

void deBoorsMake(string CName)
{
int curveFind =	returnCurveFind(CName); 
	cout<<"\n\n\n\n start deboors"<<endl; 
	//inputs: K, N, dl's , and segments U
	// and also U-bar
	// out put you get a curve, with U-bar? 
	//Algorithm " determine I, such that U-bar is within, the U segments?
	double k = 3; //for now let it be 4? 
	double n = 4; 
	double U[20];
	n = storageBezierCurves[curveFind]->controlPointsSize -1 ; 
	cout<<"choose k value, bigger than 1 and less than n: "<<n <<endl; 
	double kK; 
	cin>>kK; 
	k = kK; 
	double ksegments = 1/(k+n+1); 
	for(int i = 0; i < k+n+1; i++)
	{
		U[i] = i * ksegments; 
		cout<<" U["<<i<<"] :"<<U[i]<<endl; 
	}
	//so...... "increments is 0.875-0.25 = 0.625 which is ubar?? LOL
	//U[7] = 1.00; 
	//doubleU[5] = 0.25; 					
	//double Ubar = 0.625; // what is Ubar?? LOLOLOL i believe UBar, is current segment being passed through??  Ubar is a point, inside the
	//double bigI = 5;  //bigI and Ubar are related, so try that. 
	//calculate ubar, with the increments  U[n+1] and U[k-1]... so in this case...U[5] and U[2]
	//Therefore,   ( 0.625 - 0.25 ) / incrementChoice... maybe 3? 
	// making it 0.125 
	// 0.125*3, so 0.375 is the Ubar
	//double Ubar = 0.375;
	double Ubar = 0; 
	double bigI = 0; //BigI follows, the arrayNumber the Ubar falls in 
//calculating Ubar
Ubar = (U[ (int)(n+1) ]-U[ (int)(k-1) ]); 
	for(int i = 0; i < (k+n+1)-1; i++)
	{
		if(Ubar >= U[i] && Ubar < U[i+1])
		{
		cout<<"bigI is now: "<< i <<endl; 
		bigI = i; 
		break; 
		}
	}
cout<<" Ubar after calculation is now: "<<Ubar<<endl;  
string blankforcontinue; 
cout<<"type anything to continue"<<endl; 
cin>>blankforcontinue; 
	XAndY DL_ij[10][10]; 
					double partOne = 0;
					double partTwo = 0; 

					for(int i=0; i < storageBezierCurves[curveFind]->controlPointsSize; i++)
					{
						DL_ij[i][0].x  = storageBezierCurves[curveFind]->controlPoints[i]->x;					
						DL_ij[i][0].y  = storageBezierCurves[curveFind]->controlPoints[i]->y;		
					}
//remember, to initiate the pyramids to 0? 
for(int increment = 0; increment<1000; increment++)
{  

	if(increment!=0)
	{
		Ubar += (ksegments/1000); 
	}
	//cout<<"\n\n\n\n UBAR IS NOW: "<<Ubar<<endl; 
						for( int j = 1 ; j <= (k-1) ; j++) //apparently k steps, and j is column? 
						{
								//cout<<" did we get here to j?"<<endl; 
							for( int i =(bigI - (k-1)) ; i <= (bigI - j); i++) //this one apparently deals with "rows" 
							{
								//so maybe at the beggining initiate it for , i 0 to 10, and j = 0, for starting DL-control-points (they are given at the start)
								// so k is 2, and can increment to by 1 each time for segments? so if n = 5, then 2,3,4,5ishhh? 
								// cout<<"partOne-before:"<<partOne<<endl; 
								// cout<<"partTwo-before:"<<partTwo<<endl; 
								partOne = ( (   U[(int)(i+k)] - Ubar ) /  (U[(int)(i+k)] - U[(int)(i+j)] )    ) * DL_ij[i][j-1].x; 

								partTwo =  ( (Ubar - U[(int)(i+j)] ) / ( U[(int)(i+k)] - U[(int)(i+j)])       ) * DL_ij[i+1][j-1].x ;
								DL_ij[i][j].x = partOne + partTwo ; 

								partOne = 0; 
								partTwo = 0;
								partOne = ( (   U[(int)(i+k)] - Ubar ) /  (U[(int)(i+k)] - U[(int)(i+j)] )    ) * DL_ij[i][j-1].y; 
								partTwo =  ( (Ubar - U[(int)(i+j)] ) / ( U[(int)(i+k)] - U[(int)(i+j)])       ) * DL_ij[i+1][j-1].y ;
								DL_ij[i][j].y = partOne + partTwo ; 
								//	cout<<"partOne: "<<partOne<<endl; 
								//	cout<<"partTwo: "<<partTwo<<endl; 
								//	cout<<" lets see what DL_ij gives us?: i: "<< i<<"  j:"<<j<<"... " <<	DL_ij[i][j] <<endl; 
							}
						 
							partOne = 0; 
							partTwo = 0; 
						//	DL_ij[(int)(bigI-(k-1))][(int)(k-1)].x = 0; 
					//		DL_ij[(int)(bigI-(k-1))][(int)(k-1)].y = 0; 
						}
//cout<<" ONLY look at the LAST one DL_ij[k-1][bigI-(k-1)] :"<<DL_ij[(int)(bigI-(k-1))][(int)(k-1)].x<<" , "<<DL_ij[(int)(bigI-(k-1))][(int)(k-1)].y<<endl<<endl;

int xDraw = (int)DL_ij[  (int)(bigI-(k-1))  ][  (int)(k-1)  ].x;
int yDraw = (int)DL_ij[  (int)(bigI-(k-1))  ][  (int)(k-1)  ].y;
//drawControlPoint(xDraw ,yDraw ) ; 

PixelTrackerXZ[xDraw][yDraw]->turnRed();
PixelTracker[xDraw][yDraw]->turnRed();
}

}
void modifyControlPointsFunctionDelete(string CName);
void modifyControlPointsFunctionMove(string CName);
void modifyControlPointsFunctionADD(string CName);

void modifyControlPoints()
{
cout<<"Type in curve Name to modify"<<endl; 
string curveName; 
cin>>curveName; 
cout<<"Select which choice to use: " <<endl; 
cout<<"1: Add control points"<<endl; 
cout<<"2: INPROGRESS Move control Points"<<endl; 
cout<<"3: INPROGRESS delete Control Points"<<endl; 
string Choice; 
cin>>Choice; 

				if(Choice =="1")
				{
				modifyControlPointsFunctionADD(curveName);
				}
				else if (Choice == "2")
				{
				 modifyControlPointsFunctionMove( curveName);
				}
				else if (Choice =="3")
				{
					 modifyControlPointsFunctionDelete( curveName);
				
				}

}

void modifyControlPointsFunctionMove(string CName)
{  
	
	int curveFind = returnCurveFind(CName);
	cout<<"Which contorl point do you want to modify?"<<endl; 
	for(int i = 0 ; i <storageBezierCurves[curveFind]->controlPointsSize; i++ )
	{
cout<<"contrlpoints["<<i<<"] :"<<storageBezierCurves[curveFind]->controlPoints[i]->x<<" , "<<storageBezierCurves[curveFind]->controlPoints[i]->y <<endl; 

	}
	int arrayPositionChosen; 
	cin>> arrayPositionChosen; 
	cout<<"type in new X and Y"<<endl; 
	int xx;
	int yy;
	cin>> xx;
	cin>> yy; 
	storageBezierCurves[curveFind]->controlPoints[arrayPositionChosen]->x = xx; 
	storageBezierCurves[curveFind]->controlPoints[arrayPositionChosen]->y = yy; 
	cout<<"new Control Points:"<<endl; 
		for(int i = 0 ; i <storageBezierCurves[curveFind]->controlPointsSize; i++ )
	{
cout<<"contrlpoints["<<i<<"] :"<<storageBezierCurves[curveFind]->controlPoints[i]->x<<" , "<<storageBezierCurves[curveFind]->controlPoints[i]->y <<endl; 

	}
	eraseMainPixels(); 

}

void modifyControlPointsFunctionADD(string CName)
{
	int curveFind = returnCurveFind(CName);

	cout<<"Which array do you want to insert the point at?"<<endl; 
	for(int i = 0 ; i <storageBezierCurves[curveFind]->controlPointsSize; i++ )
	{
cout<<"contrlpoints["<<i<<"] :"<<storageBezierCurves[curveFind]->controlPoints[i]->x<<" , "<<storageBezierCurves[curveFind]->controlPoints[i]->y <<endl; 

	}
	int arrayPositionChosen; 
	cin>> arrayPositionChosen; 



		storageBezierCurves[curveFind]->controlPointsSize += 1 ; 
	for(int i = (storageBezierCurves[curveFind]->controlPointsSize-1)-1 ; i >= arrayPositionChosen ; i--)
	{
	
		int tempFX, tempFY, tempDX, tempDY; 
	    tempFX =	storageBezierCurves[curveFind]->controlPoints[i]->x ;
		tempFY = storageBezierCurves[curveFind]->controlPoints[i]->y;

		storageBezierCurves[curveFind]->controlPoints[i+1]->x = tempFX; 
		storageBezierCurves[curveFind]->controlPoints[i+1]->y = tempFY; 
	}
	cout<<"type in x and y for chosenPositionArray "<<endl; 
	int xx; 
	int yy; 
	cin>>xx; 
	cin>>yy; 
	storageBezierCurves[curveFind]->controlPoints[arrayPositionChosen]->x = xx; 
	storageBezierCurves[curveFind]->controlPoints[arrayPositionChosen]->y = yy; 
	cout<<"New Points: " <<endl; 
		for(int i = 0 ; i <storageBezierCurves[curveFind]->controlPointsSize; i++ )
	{
cout<<"contrlpoints["<<i<<"] :"<<storageBezierCurves[curveFind]->controlPoints[i]->x<<" , "<<storageBezierCurves[curveFind]->controlPoints[i]->y <<endl; 

	}
		eraseMainPixels(); 
		//eraseMainPixelsXYZ(); 
		
}

void modifyControlPointsFunctionDelete(string CName)
{
	int curveFind = returnCurveFind(CName);

	for(int i = 0 ; i <storageBezierCurves[curveFind]->controlPointsSize; i++ )
	{
cout<<"contrlpoints["<<i<<"] :"<<storageBezierCurves[curveFind]->controlPoints[i]->x<<" , "<<storageBezierCurves[curveFind]->controlPoints[i]->y <<endl; 

	}
	
	cout<<"Please type in whichcontrol point would you like to delete: "<<endl; 
	int arrayPositionChosen; 
	cin>> arrayPositionChosen; 



		//storageBezierCurves[curveFind]->controlPointsSize -= 1 ; 
	for(int i = arrayPositionChosen ; i < (storageBezierCurves[curveFind]->controlPointsSize-1) ; i++)
	{
	
		int tempFX, tempFY, tempDX, tempDY; 
	    tempFX =	storageBezierCurves[curveFind]->controlPoints[i+1]->x ;
		tempFY = storageBezierCurves[curveFind]->controlPoints[i+1]->y;

		storageBezierCurves[curveFind]->controlPoints[i]->x = tempFX; 
		storageBezierCurves[curveFind]->controlPoints[i]->y = tempFY; 
	}
	storageBezierCurves[curveFind]->controlPointsSize -= 1; 
	cout<<"New Points: " <<endl; 
		for(int i = 0 ; i <storageBezierCurves[curveFind]->controlPointsSize; i++ )
	{
cout<<"contrlpoints["<<i<<"] :"<<storageBezierCurves[curveFind]->controlPoints[i]->x<<" , "<<storageBezierCurves[curveFind]->controlPoints[i]->y <<endl; 

	}
		eraseMainPixels(); 
		//eraseMainPixelsXYZ(); 
		
}




//*************************************************//*******************PROJECT 4 *********************//*******************PROJECT 4 *********************//*******************PROJECT 4 *********************
//*************************************************
//*************                   *****************//*******************PROJECT 4 *********************//*******************PROJECT 4 *********************//*******************PROJECT 4 *********************
//*************        END     *****************
//*******************PROJECT 4 *********************//*******************PROJECT 4 *********************//*******************PROJECT 4 *********************//*******************PROJECT 4 *********************






//***************************************PROJECT 5 START**************************************************

//***************************************PROJECT 5 START**************************************************

//***************************************PROJECT 5 START**************************************************

//***************************************PROJECT 5 START**************************************************

//***************************************PROJECT 5 START**************************************************

void phongProjFive()
{  

	//think these might be unused atm because of light vector set at default 0 underneath; 
	cout<<" type in light X - light source position"<<endl; 
	//cin>> lightX; 
	cout<<" type in light Y - light source position"<<endl; 
	//cin>> lightY;
	cout<<" type in light Z - light source position"<<endl; 
//	cin>> lightZ;

	cout<<" type in the light point f, X " <<endl; 
//	cin>> lightFX;
	cout<<" type in the light point f, Y " <<endl; 
//	cin>> lightFY;
	cout<<" type in the light point f, Z " <<endl; 
//	cin>> lightFZ;


	 lightX = 300; 
	lightY = 300; 
	lightZ = 300; 
	//used for calculating normals I hope 
	http://onlinemschool.com/math/assistance/cartesian_coordinate/plane/


	//returns intensity; 
	
	double Ip=0, Ka=0, Ia=0, Il=0, f=0, p=0, K=0, Kd=0, l_vector=0, n_vector=0, Ks=0, r_vector=0, v_vector=0, n=1; 
	
	//Fixed values for testing; 

	Ka = 0.7;
	Il = 0.7; 
	Ia = 0.7;
	f = 100; 

	
	


	int testCount = 0; 
	//modified fixed value for light bector
	double l_vectorX=0, l_vectorY=0, l_vectorZ=-1; //light vector can be standard, to the origin, 

			for(int j= 2; j <300; j++)
		{  
			
	
		for(int i= 2; i < 300; i++)
		{  
			

	
								//herebelow depends on the normal for each PIXEL of the sphere. 
			if(PixelTracker[i][j]->isEdge == true && testCount < 400)
			{
								double n_vectorX=PixelTracker[i][j]->normalX, n_vectorY=PixelTracker[i][j]->normalY, n_vectorZ=PixelTracker[i][j]->normalZ;  //THIS one is calculated, for EACH surface. 


								cout<<" X " << n_vectorX <<" Y " << n_vectorY << " Z " << n_vectorZ ;
								

								double r_vectorX=30, r_vectorY=30, r_vectorZ=50; //CALCULATE THIS - this is the same ANGLE, as the light ANGLE to the NORMAL 
								double v_vectorX=90, v_vectorY=90, v_vectorZ=90; // this depends, on EACH SCREEN, where it is basically viewed from XY, XZ, YZ etc; 
								//first calculate two vectors with two vertices on a surface. 
								double partOne=0, partTwo=0, partThree=0, partFour=0; 
								double dotOne=0, dotTwo=0;
								double degrees=0, radians=0; 
								

								//dot product is done by, |a| x |b| x cos(theta) ; where theta is the angle between the vectors. and its maginitude of A and B

								double verticeA_X=0, verticeA_Y=0, verticeA_Z=0; // zerobecause from origin
								double	verticeB_X=50, verticeB_Y=50, verticeB_Z=50;  //light vector from orign 
								double verticeC_X=0, verticeC_Y=0, verticeC_Z=0;// zerobecause from origin
								double verticeD_X = n_vectorX , verticeD_Y= n_vectorY, verticeD_Z= n_vectorZ; //normal vector
							
								//*****Set verticeA, B, C, D ; 
								// for Light Vectors, and Normal


double magLight =  sqrt(  ( (verticeB_X - verticeA_X ) *(verticeB_X - verticeA_X )) + ((verticeB_Y - verticeA_Y )*(verticeB_Y - verticeA_Y )) +( (verticeB_Z - verticeA_Z )*(verticeB_Z - verticeA_Z ) )   ) ; //could be used for Light? 
double magNormal =  sqrt(  ((verticeD_X - verticeC_X )*(verticeD_X - verticeC_X )) + ((verticeD_Y - verticeC_Y )*(verticeD_Y - verticeC_Y )) +((verticeD_Z - verticeC_Z )*(verticeD_Z - verticeC_Z ))   ) ; // tihs one saved for normal?? 
								
								//degrees depend on the light vector hitting the normal, so calculate a degree between two vectors
								degrees = ( (verticeB_X*verticeD_X )+  (verticeB_Y*verticeD_Y )+  (verticeB_Z*verticeD_Z )     ) / (magLight * magNormal);
								cout<<"\n magLight: " << magLight << " magNormal " << magNormal << endl; 
								//cout<<"\n degrees:" <<degrees<< endl; 
								radians =  (degrees*3.14)/180; 

								if(radians < 0 )
								{
								 radians =  radians * (-1); 
								cout <<"radians " <<radians<< endl; 
								}
								dotOne = magLight * magNormal * cos(radians); //hopefully this is correct... cosRadians would be in relation to the plane, where the plane is the origin. wher Vertice A is the origin, 
																			//there for example if vertice a is 45, 60, 30, then i believe you add those? to the vertices? 45+verticeBX , 60+verticeBY, 30+verticeBZ? 
																			//****set VerticeA,B,C,D; 
																		// for reflect Vector, and View Vector. 



									double magReflection  =  sqrt(  ( (verticeB_X - verticeA_X ) *(verticeB_X - verticeA_X )) + ((verticeB_Y - verticeA_Y )*(verticeB_Y - verticeA_Y )) +( (verticeB_Z - verticeA_Z )*(verticeB_Z - verticeA_Z ) )   ) ;  //could be used for Light? 
									double magView  = sqrt(  ((verticeD_X - verticeC_X )*(verticeD_X - verticeC_X )) + ((verticeD_Y - verticeC_Y )*(verticeD_Y - verticeC_Y )) +((verticeD_Z - verticeC_Z )*(verticeD_Z - verticeC_Z ))   ) ;  // tihs one saved for normal?? 
		
									//default set it to 45 for now; 
									//degrees = 45; 
									//radians = (degrees*3.14)/180; 
							dotTwo  = magReflection * magView * cos(radians); 

					
									double dotTwoPowered = 0;
								partOne = Ka*Ia;
								partTwo = (Il) / ( (f - p ) + K  );
								partThree = Kd*( dotOne); // need to fix, it needs to be dot product, so whatever that means


							//	cout<<" partOne " << partOne<<endl;
							//	cout<<" partTwo " <<partTwo <<endl;
							//	cout<<" partThree " <<partThree<<endl; 
								n = 5; 
								for(int i = 0; i < n; i++)
								{
	
								 dotTwoPowered = dotTwo * dotTwo; 
								}
							   partFour = Ks* (dotTwoPowered) ; //this power sign might be off? maybe it isn't ^ 

								Ip = partOne + (partTwo * ( partThree + partFour ) ); 

								cout<<" Ip intensity is now: " <<Ip <<endl; 

								testCount++; 
			}
								
		};
		};




}

//Cite: http://mathworld.wolfram.com/Sphere.html
void ballCreate(int cooX, int cooY, double rr)
{

double r = 0;
double u = 0;
double x = 0;
double y = 0;
double z = 0; 
 
double countOne = 0;
double countTwo = 0;
double countThree = 0; 

r = rr;

countTwo = r*(-1); 

while(countOne < 6.28)
{
	countTwo = - 50; 

				while(countTwo <r)
				{
					countThree = 0; 
					while(countThree < (3.14)) 
					{   

						u = countTwo*cos(countThree);  
						//cout<<"u " << u + 200<<endl; 
						 x = sqrt((r*r) - (u * u) )* cos(countOne) +cooX;
						 y = sqrt((r*r) -( u *u) )* sin(countOne) + cooY;
						 z = u + cooY - 20; 


						 PixelTracker[(int)x][(int)y]->normalX = (int)(x - cooX); 
						
						 PixelTracker[(int)x][(int)y]->normalY = (int)(y - cooY);
						 
						 PixelTracker[(int)x][(int)y]->normalZ = (int)(z  - cooY +20); 

						 PixelTracker[(int)x][(int)y]->turnBlue(); 
						 PixelTracker[(int)x][(int)y]->isEdge = true; 
						 PixelTrackerXZ[(int)x][(int)z]->turnBlue(); 
						 PixelTrackerXZ[(int)x][(int)z]->isEdge = true; 
							 PixelTracker[(int)x][(int)y]->z = z ; 


							 //this is for top shading of the sphere; 
							 if( ((int)z%3) == 0  &&  countTwo < (r/4))
							 {
								
								 for(int i = 0; i <3; i++)
								 {

									

									 PixelTracker[(int)x+i][(int)y+i]->turnWhite(); 
							 		 PixelTrackerXZ[(int)x+i][(int)z+i]->turnWhite(); 
								 }
							 }
							 		 if( ((int)z%10) == 0  &&  countTwo < (r/1.9))
							 {
								
								 for(int i = 0; i <5; i++)
								 {

									

									 PixelTracker[(int)x+i][(int)y+i]->turnOFF(); 
							 		 PixelTrackerXZ[(int)x][(int)z]->turnWhite(); 
								 }
							 }

						 //ut<<"x" << x <<"    ,    "<< y <<endl; 

						
						 countThree += 0.02; 
						}
					countTwo += 0.5; 
				}
				countOne += 0.02; 
}





}

void shootRayLine()
{

int xRay = 200;
int yRay = 200;
int zRay = 200;

//this is for jsut the 400*400 part of the screen where you can see the pixels 
	for(int i= 0; i < 400*3*400; i++)
		{  
			

		};


}

void travelRays()
{




}

void intersectPixel()
{

	





}

//************************************END PROJECT 5 *****************************************
//************************************END PROJECT 5 *****************************************
//************************************END PROJECT 5 *****************************************
//************************************END PROJECT 5 *****************************************
//************************************END PROJECT 5 *****************************************
//************************************END PROJECT 5 *****************************************
//************************************END PROJECT 5 *****************************************
//************************************END PROJECT 5 *****************************************
//************************************END PROJECT 5 *****************************************

	ifstream fileGoIn;
	string readText; 
	int readInt; 
	bool isReadFile;
	//void printToText();
	void printToTextXYZ(); 

	int drawAllStart = false; 
	int drawAllStartCount = 0; 
void allFunctions()
{
					string Choice = "" ;	
						//eraseMainPixels(); 
						findEdgeRight = false; 
							cout<<" Which Function would you like to use? \n "<<endl;
							/*
							cout<<"0: read input file"<<endl; 
						
							cout<<" 1: ***BRESENHAM*** Make Polygon with Bresenham "<<endl; 
							cout<<" 2: ***DDA*** Make Polygon with DDA "<<endl; 
							cout<<" 3: Erase Main Board "<<endl; 
							cout<<" 4: BROKEN-Make first poly appear "<<endl; 
							cout<<" 5: BROKEN color-recursive"<<endl; 
							cout<<" 6: BRKOEN- CheckEdge -turnCyan - go to choice 11 "<<endl; 
							cout<<" 7: BROKEN - colorfill step 1.5 check choice after 8. "<<endl; 
							cout<<" 8: BROKEN - colorFill Step 1 -innerLining"<<endl; 
							cout<<" 9: BROKEN - ColoFill step2 - fills red"<<endl; 



							cout<<" 10: Check PolygonStorage[i] at i "<<endl; 
							cout<<" 11: Check-POLYGON-Exist-turn-color "<<endl; 
							cout<<" 12: findPolygon Center coordinates "<<endl; 
							cout<<" 13: ***ROTATE*** Polygon "<<endl; 
							cout<<" 14: ***TRANSLATE*** this polygon to this point"<<endl; 
							cout<<" 15:	Redraw chosen Polygon - drawPolygonVertices "<<endl; 
							cout<<" 16: AutoRedrawFunctionPolyGon"<<endl; 
							cout<<" 17: ***SCALE*** Polygon attempt draft 1"<<endl; 
							cout<<" 18: **RASTERIZE*** polyName"<<endl; 
							cout<<" 19: ***CLIP*** polygon"<<endl; 
							cout<<" 20: Project 2 ****Make an XYZ Polygon****"<<endl; 
							cout<<" 21: Project 2 ****draw xyz Polygon    ***"<<endl; 
							cout<<" 22: Project 2 ****rotate XYZ Polygon  ***"<<endl; 
							cout<<" 23: Project 2 ***find Centroid  *********"<<endl; 
							cout<<" 24: Project 2**translate XyzPolygon******"<<endl; 
							cout<<" 25: Project 2 ** clear, and redraw all XYZ polygons"<<endl; 
							cout<<" 26: Project 2 ** Scale a XYZ polygon ****"<<endl; 

							cout<<" 27: Project 3 ** ColorRecursive ***"<<endl;
							cout<<" 28: Project 3 ** scanline-Color ***"<<endl; 
							cout<<" 29: Project 3 ** isolateSurface ***"<<endl; 
							cout<<" 30: Project 3 ** Erase All Pixel boards - usually used for isolating surfaces for rasterization "<<endl; 
							*/
							cout<<" 31: Project 4 ** Create Bezier Control Points"<<endl; 
							cout<<" 32: Project 4 ** Use De-Boor on control Points:"<<endl;
							cout<<" 33: Project 4 ** Add,delete Or Modify Control Points"<<endl; 
							cout<<" 34: Project 5 ** make spheres" <<endl; 
								cout<<" 35: Project 5 ** phong model Test**" <<endl; 
						//	cin>>Choice; 

							if(drawAllStart == false && drawAllStartCount < 1)
							{
								//forces to draw all shape atleast once. 
								cout<<"\n \n DRAWING ALL SHAPES FROM FILE ONCE \n \n"<<endl;  
								drawAllStartCount++; 
								Choice = "25"; 
								drawAllStart = true; 
							
							}
							else
							{  
								cin>>Choice; 

							}
							if(Choice == "1")
							{   
					
								makePolyBresenham(); 
								
							}
						else if (Choice == "2")
							{
							cout<<"\n please adjust lineDDA to set edge also, currently only Poly has Edges "<<endl; 
							makePoly(); 
							}
						else if(Choice == "3")
							{
							eraseMainPixels(); 
							}
						else if(Choice == "4")
							{
					//		polyOneAppear(); 
							}
						else if(Choice == "5")
							{
							cout<<" BROKEN color this point blue -> using Weird Recursion, WARNING BROKEN!!!"<<endl; 
							int x, y; 
							cout<<"type in X, y "<<endl; 
							//string polyName; 
							//cout<<"type testlimit"<<endl;
							cin>>x;
							cin>>y; 
							colorPoint(x,y, testlimit); 
							}
						else if(Choice == "6")
							{   
							cout<<"Check, Edge, turns all edges CYAN if they are true"<<endl; 
							checkEdge(); 
							}
						else if(Choice == "7")
							{   
							cout<<" Sorry, Broken \n Check, INNER LINING turns all inside shape lining - YELLOW if they are true"<<endl; 
						//	checkInnerLining(); 
							}
						else if(Choice == "8")
							{   
							cout<<"Sorry Broken \n - Color InnerLining"<<endl; 
					int x, y; 
							cin>> x;
							cin >>y; 
							colorInnerLining(x,y, "start"); 
							//need to reset this for next polygon. 
							
							}
						else if(Choice == "9")
							{   
							cout<<" Sorry Broken \n - Color fill startining"<<endl; 
						//	colorFillInnerLining(); 

							}
						else if( Choice =="10")
							{	//10: Check PolygonStorage[i] at i 
								cout<<"type between 0 - " << polygonStorageSize<<endl;
								int i=0;
								cin>>i;
								if( i < polygonStorageSize)
								{
									cout<<"PolyStorage Name:" <<polygonStorage[i]->Name<<endl; 
								}
								else
								{
									cout<<"sorry out of size range"<<endl; 
								}
							}
						else if( Choice == "11")
							{	//11: Check-POLYGON-Exist-turn-color
								cout<<"BROKEN-UNEEDED-type ploygon name to make appear" <<endl;
								string name;
								cin>>name; 
							//	makePolyAppear(name);
							}
						else if (Choice == "12")
							{	//12: findPoly-Center-x-y-average
								cout<<" type in PolyName to find center of Poly"<<endl; 
								string polyNaming; 
								cin>>polyNaming; 
								rotatePoly_findAvereage(polyNaming); 
								cout<<" did average out work? lol"<<endl; 
							}
						else if (Choice == "13")
							{	//13: Rotate PolygonStorage[findPoly]
								cout<<" roate poly type in name"<<endl; 
								string name;
								cin>> name;
								rotatePoly_findAvereage(name);
								cout<<"rotate clockwise by how many degrees?"<<endl; 
								int degrees;
								cin>>degrees;
								rotatePoly(degrees, name); 
								cout<<" done rotating poly"<<endl; 
							}

						else if (Choice == "14")
						{
							cout<<"type in name for polygon to be translated"<<endl; 
							string name; 
							cin>>name; 
							int translateX, translateY;
							cout<<" type in x and y for translating - in relationed to the center:"<<endl; 
							rotatePoly_findAvereage(name);
							int polyFind = returnPolyFind(name); 
							cout<<"here is center: "<<polygonStorage[polyFind]->centerX << " , " << polygonStorage[polyFind]->centerY <<endl; 
							cout<<"translate to x:"<<endl; 
							cin>>translateX;
							cout<<"translate to y:"<<endl; 
							cin>>translateY; 
							translatePolygon(translateX, translateY, name); 
						}
						else if (Choice == "15")
						{
							cout<<"Redraw chosen Polygon Type in name, to be redrawn"<<endl; 
							string polyName;
							cin>>polyName; 
							drawPolygonVertices(polyName); 
						}
							else if (Choice == "16")
						{
							cout<<"autoredraw ALL" <<endl; 
							for(int i = 0 ; i < polygonStorageSize ; i++)
							{
								cout<< " name:"<< polygonStorage[i]->Name<<endl; 
								if(polygonStorage[i]->Name != "" ) 
								drawPolygonVertices(polygonStorage[i]->Name); 
							}
						}
							else if(Choice == "17")
							{
							cout<<"Attempt to scale, type in polygon name"<<endl; 
							string polyName;
							int scaleX;
							int scaleY;
							cin>>polyName; 
									cout<<" type in X:"<<endl; 
							cin>>scaleX;
							cout<<" type in Y:"<<endl; 
							cin>>scaleY;
							scalePolygon(scaleX, scaleY, polyName); 
							
							}
							else if (Choice == "18")
							{

								cout<<" rasterize polyName"<<endl; 
								string polyName;
								cin>>polyName; 
								cout<<" enter, either: green, purple, blue, yellow"<<endl; 
								string color;
								cin>>color; 
								rasterizePolygon(polyName,color); 
							}
							else if (Choice == "19")
							{

																	cout<<" clip lines, below \n 1: Clip Below Y \n 2: Clip Above Y \n 3: Clip Left X \n 4: Clip Right X"<<endl; 
																	int clipChoice; 
																	cin>>clipChoice; 

																	if(clipChoice == 1 )
																	{
																		cout<<" type in poly name to be clipped, currently clips below Y"<<endl;
																		string polyName;
																		cin>>polyName; 
																		cout<<" type in Y, to be clipped BELOW"<<endl; 
																		int y;
																		cin>>y; 
																		clipBelowY(y,polyName);//arbitrary numbers atm need to fix later
																	}
																	else if (clipChoice == 2 )
																	{
																		cout<<" type in poly name to be clipped, currently clips ABOVE Y"<<endl;
																		string polyName;
																		cin>>polyName; 
																		cout<<" type in Y, to be clipped ABOVE"<<endl; 
																		int y;
																		cin>>y; 
																		clipAboveY(y,polyName);//arbitrary numbers atm need to fix later
																	}
																	else if (clipChoice == 3 )
																	{
																		cout<<" type in poly name to be clipped, currently clips left of X"<<endl;
																		string polyName;
																		cin>>polyName; 
																		cout<<" type in X, to be clipped LEFT"<<endl; 
																		int y;
																		cin>>y; 
																		clipLeftX(y,polyName);
																	}
																	else if (clipChoice == 4 )
																	{
																		cout<<" type in poly name to be clipped, currently clips Right if X"<<endl;
																		string polyName;
																		cin>>polyName; 
																		cout<<" type in X, to be clipped RIGHT"<<endl; 
																		int y;
																		cin>>y; 
																		clipRightX(y,polyName);//arbitrary numbers atm need to fix later
																	}
							}
										else if (Choice == "20")
							{

													makePyramidtesting();
													xyzDrawAll(); 
													glutPostRedisplay(); 
							}
										else if (Choice =="21")
										{
												cout<<"\n \n gonna try draw vertices "<<endl; 
													cout<<"attempt to draw after, storing all polygons, type polyname to be drawm: "<<endl; 
		int xyzFind = 0; 
		string polyName; 
		cin>>polyName; 
												xyzDrawVertices(polyName);
												glFlush();
													xyzDrawAll(); 
												glutPostRedisplay(); 

										}
										else if (Choice == "22") 
										{
										
										cout<<" selecting polygon for rotate"<<endl; 
										xyzRotate(); 

										
											xyzDrawAll(); 
										
										
										}
										else if (Choice == "23")
										{
										cout<<" select Polygon to find center"<<endl; 
										int polyFind; 
										string polyName; 
										cin>>polyName; 
										
										for(int i = 0; i < xyzPolygonStorageSize; i++)
										{
											if(xyzPolygonStorage[i]->Name ==polyName)
											{
											
												polyFind = i; 
												break; 
											}

										}
										
										xyzPolygonStorage[polyFind]->findCenter(); 
											xyzDrawAll(); 

										}
										else if(Choice =="24")
										{
											cout<<" translate polygon in 3D"<<endl; 
											xyzTranslate(); 
											xyzDrawAll();
										
										}
										else if (Choice == "25")
										{
										
										cout<<" clearing and redrawing, "<<endl; 
										xyzDrawAll(); 
										}
													else if (Choice == "26")
										{
										
											cout<<"Choice is Scaling Polygon "<<endl; 
											xyzScale(); 
											xyzDrawAll(); 
										}
													else if ( Choice == "27")
													{

														cout<<" type in x and y "<<endl;
														int xx;
														int yy;
														cin>>xx;
														cin>>yy;
														colorRecursive(xx, yy, 500);

													}
													else if ( Choice == "28")
													{
														cout<<"choose color to rasterize peter the polygon: blue, green, purple,cyan"<<PixelTracker[0][0]->isEdge<<endl; 
														string blank;
														cin>>blank; 
														rasterizeXYZ("peter", blank, PixelTracker); 
															rasterizeXYZ("peter", blank, PixelTrackerXZ); 
														rasterizeXYZ("peter", blank, PixelTrackerYZ); 

													}
													else if ( Choice == "29")
													{
														cout<<"Iosolating surfaces, from back to front? currently, type in number to isolate, recommended 4, choice 28, then 1, choice 28"<<endl; 

														int isolateNum;
														cin>>isolateNum; 
														isolateSurface("peter", isolateNum); //at surface number 0, atm 

													}
													else if ( Choice == "30")
													{
														cout<<"erasing all pixel boards xyz "<<endl; 
														eraseMainPixelsXYZ(); 

													}

													else if (Choice == "31")
													{

													makeCurve(); 
													
													}

															else if (Choice == "32")
													{

														cout<<"lets try deboors see what happens "<<endl; 
														deBoors(); 
													
													}

																				else if (Choice == "33")
													{

														cout<<"ModifyControlPoints "<<endl; 
														modifyControlPoints(); 
														printToTextXYZ(); 
													
													}
																				else if (Choice == "34")
																				{
																				
																				ballCreate(100,300,30); 
																					ballCreate(250,100, 50);
																						
																				ballCreate(350,300,20); 
																					ballCreate(330,200, 10);
																				
																				
																				}

				else if (Choice == "35")
																				{
																					phongProjFive(); 

																				}






													else
													{
														cout<<"Sorry, wrong choice select again"<<endl; 
														Choice = ""; 
													}
													cout<<"********PLEASE CLICK WINDOW TO REFRESH**************\n \n " <<endl; 
													//taken out, replace with the XYZ version later: 
													//printToText();
												//	xyzDrawAll();
												//	printToTextXYZ(); 
//Project 4							
	   for(int i = 0; i < 8; i++)
	   {
	   
		   if(storageBezierCurves[i]->curveName != "")
		   {
			bezierCurveFunction(storageBezierCurves[i]->curveName); 
			drawControlPointsLines(storageBezierCurves[i]->curveName); 
		//	drawControlPoint( ); 
				cout<<" did we make it here? "<<endl; 
		   }
	   
	   }

													glFlush();
													glutPostRedisplay(); 

	
}//end all functions


   bool isStop = false; 
 

   bool isStopFunctions = false; 

//PROJECT 4 READCURVES - START
 void readMakeCurvesText()
 {

	   int countingWhile = 0; 
	   while(isStop == false)
	   {//start while loop
		   //check if it is stop or polygon 	
		   countingWhile++; 
		   if(countingWhile > 10)
		   {
			   break; 
			   isStop =true; 
			   cout<<"while loop is BROKEN, sorry please restart, and select no, to manually type in curves"<<endl; 
		   }
		   int curveFind=0 ;
		   string polyName; 
		   //getting polyName
		   getline(fileGoIn, readText);
		   cout<<"\n \n \n \n curves->reading should say 'curvename' match? : "<<readText<<endl;

		   if(readText == "stop")
		   {
			   isStop = true; 
			   break; 
		   }
		   if(readText == "curvename")
		   {

			   getline(fileGoIn, readText);
			   cout<<" readText-Name of curve: "<<readText<<endl; 

			   for(int i = 0; i < 8; i++)
			   {

				   if( storageBezierCurves[i]->curveName == "")
				   {

					   storageBezierCurves[i]->curveName = readText; 
					   curveFind = i;
					   break; 

				   }
			   }

		   }

		   getline(fileGoIn, readText);
		   //numberofvertices
		   cout<<"curves, it should read 'numberofcontrolpoints', match?: "<<readText<<endl; 
		   getline(fileGoIn, readText);
		   storageBezierCurves[curveFind]->controlPointsSize = atoi(readText.c_str());
		   cout<<"curves, this is the number of control points: "<<storageBezierCurves[curveFind]->controlPointsSize <<endl; 										
		   getline(fileGoIn, readText);
		   cout<<"curves, it should read 'controlpoints', match?: "<<readText<<endl; 
		   //Cmove, is controlpoints moves, and it moves in the array to add the points for control points. 
		   for(int Cmove = 0; Cmove < storageBezierCurves[curveFind]->controlPointsSize; Cmove++)
		   {
			   getline(fileGoIn, readText);
			   storageBezierCurves[curveFind]->controlPoints[Cmove]->x = atoi( readText.c_str());
			   getline(fileGoIn, readText);
			      storageBezierCurves[curveFind]->controlPoints[Cmove]->y = atoi( readText.c_str());
		
			   cout<<" controlpoint at ["<<Cmove<<"] "<< storageBezierCurves[curveFind]->controlPoints[Cmove]->x<<","<<storageBezierCurves[curveFind]->controlPoints[Cmove]->y <<endl; 

		   }

	  

	   }//end while loop 

   }

//PROJECT 4 READCURVES - END


//Modified for project 3, to read surfaces and Surface properties, such as edges, normals? etc etc
void readTextMakePolygonsXYZ()
{

																								int countingWhile = 0; 
																								while(isStop == false)
																								{//start while loop
																								//check if it is stop or polygon 	
																								countingWhile++; 
																								if(countingWhile > 10)
																								{
																								break; 
																								isStop =true; 
																								cout<<"while loop is BROKEN, sorry please restart, and select no, to manually type in shapes"<<endl; 
																								}
																								int polyFind=0 ;
																								string polyName; 
																								//getting polyName
																								getline(fileGoIn, readText);
																														cout<<"\n \n \n \n XYZ!!!in-while-loop-readText"<<readText<<endl;
						
																																			if(readText == "stop")
																																				{
																																				isStop = true; 
																																				break; 
																																				}
																																				if(readText == "polygon")
																																				{
												
																								getline(fileGoIn, readText);
																																					cout<<"XYZ!!!  readText-Name:"<<readText<<endl; 

																																					for(int i = 0; i < xyzPolygonStorageSize; i++)
																																					{

																																						if( xyzPolygonStorage[i]->Name == "")
																																						{

																																							xyzPolygonStorage[i]->Name = readText; 
																																							polyFind = i;
																																							break; 

																																						}
																																					}

																																				}
																								getline(fileGoIn, readText);
																								//numberofvertices
																								cout<<"XYZ!!!  readText-Number of Vertices-"<<readText<<endl; 
																								getline(fileGoIn, readText);
																								xyzPolygonStorage[polyFind]->verticesSize = atoi(readText.c_str());
																								cout<<"XYZ!!!  readText- grabbed Number of Vertices:"<<xyzPolygonStorage[polyFind]->verticesSize<<endl; 										
																								getline(fileGoIn, readText);
																								cout<<"XYZ!!!  readText- start vertices-"<<readText<<endl; 

																								for(int Vmove = 0; Vmove < xyzPolygonStorage[polyFind]->verticesSize; Vmove++)
																											{
																													getline(fileGoIn, readText);
																													xyzPolygonStorage[polyFind]->vertices[Vmove]->x = atoi( readText.c_str());
																													getline(fileGoIn, readText);
																													xyzPolygonStorage[polyFind]->vertices[Vmove]->y = atoi( readText.c_str());
																													getline(fileGoIn, readText);
																													xyzPolygonStorage[polyFind]->vertices[Vmove]->z = atoi( readText.c_str());
																													cout<<" at ["<<Vmove<<"] "<<xyzPolygonStorage[polyFind]->vertices[Vmove]->x<<","<<xyzPolygonStorage[polyFind]->vertices[Vmove]->y<<","<<xyzPolygonStorage[polyFind]->vertices[Vmove]->z<<endl; 

																											}
																												getline(fileGoIn, readText);
																												//numberOfEdges
																												cout<<"XYZ!!!  readText-Number of Edges-"<<readText<<endl; 
																												getline(fileGoIn, readText);
																												xyzPolygonStorage[polyFind]->edgesSize = atoi(readText.c_str() ); 
																												cout<<"readText- Grabbed Number of Edges:"<<xyzPolygonStorage[polyFind]->edgesSize<<endl; 
																												getline(fileGoIn, readText);
																												cout<<"XYZ!!!  readText- start Edges-"<<readText<<endl; 

																												for(int Emove = 0; Emove < xyzPolygonStorage[polyFind]->edgesSize; Emove++)
																												{
																													getline(fileGoIn, readText);
																													xyzPolygonStorage[polyFind]->edges[Emove]->arrayStart = atoi(readText.c_str() ); ; 
																													getline(fileGoIn, readText);
																													xyzPolygonStorage[polyFind]->edges[Emove]->arrayEnd = atoi(readText.c_str() ); ; 
																													cout<<" at ["<<Emove<<"] start: "<<		xyzPolygonStorage[polyFind]->edges[Emove]->arrayStart<<" end:"<<	xyzPolygonStorage[polyFind]->edges[Emove]->arrayEnd<<endl; 

																												}


																												getline(fileGoIn, readText); 
																												//numberofsurfaces
																												cout<<"Project 3... readtext-number of Surfaces"<<readText<<endl; 
																												getline(fileGoIn, readText); 
																												xyzPolygonStorage[polyFind]->surfacesSize = atoi(readText.c_str() ); 
																												cout<<" checking, surfacesSize = "<<xyzPolygonStorage[polyFind]->surfacesSize <<endl; 
																												//sMove is for each individual surface, like if there was 6 surfaces on a cube, Smove would move through all of them, starting at 0, 
																												for(int Smove = 0; Smove < xyzPolygonStorage[polyFind]->surfacesSize ; Smove++)
																												{
																															//readtext - surfaceNumber
																															getline(fileGoIn, readText); 
																															cout<<" readtext- surfaceNumber?? : "<< readText <<endl; 
																															//actual surface number 
																															getline(fileGoIn, readText); 
																																cout<<" actual surfaceNumber?? : "<< readText <<endl; 
																															xyzPolygonStorage[polyFind]->surfaces[Smove]->surfaceNumber = atoi(readText.c_str() ); 
																															//readtext - numberofsurfaceedges
																															getline(fileGoIn, readText); 
																															//actual number of surface edges
																															getline(fileGoIn, readText); 
																															xyzPolygonStorage[polyFind]->surfaces[Smove]->surfaceEdgesSize = atoi(readText.c_str() ) ; 
																															//readText - surfaceEdges; 
																															getline(fileGoIn, readText); 
																															//cout<<" readtext Surface Edges: 
																															for(int Emove = 0; Emove < xyzPolygonStorage[polyFind]->surfaces[Smove]->surfaceEdgesSize ; Emove++)
																															{
							
																															getline(fileGoIn, readText);
																															xyzPolygonStorage[polyFind]->surfaces[Smove]->surfaceEdges[Emove]->arrayStart = atoi(readText.c_str() ); ; 
																															getline(fileGoIn, readText);
																															xyzPolygonStorage[polyFind]->surfaces[Smove]->surfaceEdges[Emove]->arrayEnd = atoi(readText.c_str() ); ; 
																															cout<<" surfaceEdges at ["<<Emove<<"] start: "<<		xyzPolygonStorage[polyFind]->edges[Emove]->arrayStart<<" end:"<<	xyzPolygonStorage[polyFind]->edges[Emove]->arrayEnd<<endl; 
																															}
																															int nX, nY, nZ; 

																															getline(fileGoIn, readText);
																															cout<<"readText - normalsurfacevector :" <<readText<<endl; 
																															getline(fileGoIn, readText);
																															nX = atoi(readText.c_str()); 
																															getline(fileGoIn, readText);
																															nY = atoi(readText.c_str()); 
																															getline(fileGoIn, readText);
																															nZ = atoi(readText.c_str()); 
																															xyzPolygonStorage[polyFind]->surfaces[Smove]->normalX = nX; 
																															xyzPolygonStorage[polyFind]->surfaces[Smove]->normalY = nY;
																																xyzPolygonStorage[polyFind]->surfaces[Smove]->normalZ = nZ;
				cout<<" normal vector: " << xyzPolygonStorage[polyFind]->surfaces[Smove]->normalX <<","<<xyzPolygonStorage[polyFind]->surfaces[Smove]->normalY<<","<<	xyzPolygonStorage[polyFind]->surfaces[Smove]->normalZ <<endl; 
						
				
																												}




																								}//end while loop 

																								}



string fileName; 

void printToTextXYZ()
{


	ofstream writeOut(fileName); 
	writeOut<<mainWindowSizeWidth<<endl; 
	writeOut<<mainWindowSizeHeight<<endl; 
	int curveFind = 0; 
	for(int i = 0; i < 8; i++)
	{
		if(storageBezierCurves[i]->curveName != "")
		{
				

			writeOut<<"curvename"<<endl; 
			writeOut<<storageBezierCurves[i]->curveName<<endl; 
			writeOut<<"numberofcontrolpoints"<<endl; 
			writeOut<<storageBezierCurves[i]->controlPointsSize<<endl; 
			writeOut<<"controlpoints"<<endl; 

			for(int CMove = 0; CMove < storageBezierCurves[i]->controlPointsSize; CMove++)
			{
			
				writeOut<<storageBezierCurves[i]->controlPoints[CMove]->x<<endl; 
				writeOut<<storageBezierCurves[i]->controlPoints[CMove]->y<<endl; 
			
			}
		
		
		
		}
	
	}
	writeOut<<"stop"<<endl; 




	/*
	ofstream writeOut(fileName);
	int xyzFind = 0; 

	writeOut<<mainWindowSizeWidth<<endl; 
	writeOut<<mainWindowSizeHeight<<endl; 
	
	for(int i = 0 ; i < xyzPolygonStorageSize ; i++)
	{

		if(xyzPolygonStorage[i]->Name != "" ) 
		{

		writeOut<<"polygon"<<endl; 

			writeOut<<xyzPolygonStorage[i]->Name<<endl; ; 	
			writeOut<<"numberofvertices"<<endl; 
			writeOut<<xyzPolygonStorage[i]->verticesSize<<endl; 
			writeOut<<"vertices"<<endl; 
			for(int Vmove = 0; Vmove<xyzPolygonStorage[i]->verticesSize; Vmove++)
			{

					writeOut<<xyzPolygonStorage[i]->vertices[Vmove]->x<<endl; 
					writeOut<<xyzPolygonStorage[i]->vertices[Vmove]->y<<endl; 
					writeOut<<xyzPolygonStorage[i]->vertices[Vmove]->z<<endl; 
			
			}
			writeOut<<"numberofedges"<<endl; 
			writeOut<<xyzPolygonStorage[i]->edgesSize<<endl; 
			writeOut<<"edges"<<endl; 
				for(int Emove = 0; Emove<xyzPolygonStorage[i]->edgesSize; Emove++)
			{

				writeOut<<xyzPolygonStorage[i]->edges[Emove]->arrayStart<<endl; 
				writeOut<<xyzPolygonStorage[i]->edges[Emove]->arrayEnd<<endl; 
			
			}


		}
		else if(xyzPolygonStorage[i]->Name != "" )
		{
		break; 
		}

	}
	writeOut<<"stop"<<endl; 
	*/
}



void displayMain(); 
void displayXY(); 
void displayYZ(); 
void displayXZ();
int main(int argc, char *argv[])
{       
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);

	cout<<"type yes to start fileInput"<<endl;

	string fileYesNo = "";
	cin>>fileYesNo;  


	if(fileYesNo=="yes" || fileYesNo=="Yes" || fileYesNo=="Y" || fileYesNo=="y" )
	{
		isReadFile = true; 
		cout<<"type fileName to run input"<<endl;
	
		cin>>fileName;
		fileGoIn.open(fileName);

		//set up Window Size. 
		//cout<<"readtext: "<<readText<<endl;

		getline(fileGoIn, readText); 
		mainWindowSizeWidth = atoi( readText.c_str()); 
		cout<<"readtext: "<<readText<<endl; 

		getline(fileGoIn, readText); 
		mainWindowSizeHeight = atoi( readText.c_str()); 
		cout<<"readtext: "<<readText<<endl; 




	}//end FileYesNo
	else
	{
			isReadFile = false;
	}


	if(isReadFile == false)
	{
		/*cout<<" Type in window size width: ";	
		cin>>mainWindowSizeWidth;
		cout<<"\n Type in window size height: "; 
		cin>>mainWindowSizeHeight; 
		*/
		mainWindowSizeWidth = 900;
		mainWindowSizeHeight = 900;
	}

	//cout<<"how many polygons are you planning to make? "<<endl;
	//cin>>polygonStorageSize; 
	//expanded till 19, but probably really just use less than 5 shapes. 
	polygonStorageSize = 20; 
	
	//Making only 3 shapes at them momment, testing the initialization
	xyzPolygonStorageSize = 20; 
	cout<<" confirm polygonStorageSize: "<< polygonStorageSize<<endl; 

		PixelBufferBlank = new float[mainWindowSizeWidth * mainWindowSizeHeight * 3];
	PixelBuffer = new float[mainWindowSizeWidth * mainWindowSizeHeight * 3];
	PixelBufferXZ =new float[mainWindowSizeWidth * mainWindowSizeHeight * 3];
	PixelBufferYZ = new float[mainWindowSizeWidth * mainWindowSizeHeight * 3];

	glutInitWindowSize( mainWindowSizeWidth,mainWindowSizeHeight);
	glutInitWindowPosition(100, 160);



		int MainWindow = glutCreateWindow("Jason's ECS175 Project TWO - Top Right corner *XY*, Top Left corner *XZ* Bottom Left coner *YZ* ");
		//subwindow
	
		glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
		glEnable ( GL_COLOR_MATERIAL );

//Jason Hui - start //Jason Hui - start //Jason Hui - start //Jason Hui - start //Jason Hui - start //Jason Hui - start //Jason Hui - start //Jason Hui - start
//!!!IMPORTANT!!! Make sure the additional, beggining dll in project folder is the one being called, and not the one on windows. 
//Careful, may need to Change to GLUTZ 3, from GLUTZ 4
//This creates a menu i hope:
//Need PixelTracker Initiator:

//BUFFER XY testing
			for(int i= 0; i < 400*3*400; i++)
		{  
				if(i%37 == 0)
			PixelBufferXZ[i] = 1;

		};
			for(int i= 0; i < 400*3*400; i++)
			{

			
			if(i%20 == 0)
			PixelBufferYZ[i] = 1;

		};
		cout<<"     ^^^^^INTIALIZING MAIN BOARD PIXELS^^^^^^^^^^^^^^^^"<<endl; 
		for(int i= 0; i < mainWindowSizeWidth; i++)
		{
			for(int j= 0; j< mainWindowSizeHeight ; j++)
			{
				PixelTracker[i][j] = new onScreenPixel(i, j, false, mainWindowSizeWidth, mainWindowSizeHeight);
				PixelTracker[i][j]->turnOFF(); 
				RasTracker[i][j] = new onScreenPixel(i, j, false, mainWindowSizeWidth, mainWindowSizeHeight);
				RasTracker[i][j]->turnOFF(); 

				PixelTrackerXZ[i][j] = new onScreenPixelXZ(i,j,false,mainWindowSizeWidth, mainWindowSizeHeight);

					PixelTrackerXZ[i][j]->turnBlue(); 
					PixelTrackerXZ[i][j]->isEdge = false; 
					PixelTrackerYZ[i][j] = new onScreenPixelYZ(i,j,false,mainWindowSizeWidth, mainWindowSizeHeight);
					PixelTrackerYZ[i][j]->turnPurple(); 
					PixelTrackerYZ[i][j]->isEdge = false;

			};
			//cout<<" x test: "<<i <<" j test: " <<j<<endl; 
		};
		cout<<"DONE ^^^^^INTIALIZING MAIN BOARD PIXELS^^^^^^^"<<"^^^^^^^^^"<<endl<<endl; 

		// polygoning *polygonStorage[10]; //stores up to 10 shapes

			cout<<"^^^^^ initializing PolygonStorage ^^^"<<endl; 
		for(int i= 0; i < polygonStorageSize; i++)
			  {	
				polygonStorage[i] = new polygoning(""); 
				polygonStorage[i]->eraseVertices();
				//cout<<" x test: "<<i <<" j test: " <<j<<endl; 
			     };
		cout<<"\n \n \n DONE^^^^^ initializing PolygonStorage ^^^"<<endl;
		//xyz-ini
				cout<<"^^^^^ initializing XYZ PolygonStorage ^^^"<<endl; 

		for(int i= 0; i < xyzPolygonStorageSize; i++)
			  {	
				  xyzPolygonStorage[i] = new xyzPolygon(""); 
					xyzPolygonStorage[i]->eraseVertices();
				//cout<<" x test: "<<i <<" j test: " <<j<<endl; 
			     };
		cout<<"\n \n \n XYZ is DONE! "<<endl; 
		cout<<"^^^^^^^initiating bezierCurves^^^^^^"<<endl; 

		initiateAllCurves(); 

		rotateLineTemp = new rotateLine(); 


		if(isReadFile==true)
		{
			//readTextMakePolygons();
			//ReadTextFunctions();

			//readTextMakePolygonsXYZ(); 
			readMakeCurvesText();
			//printToText();
		}
		
glutDisplayFunc(displayMain);//for the main window apparently? 		
	
	
int subWindowXY = glutCreateSubWindow(MainWindow,400,0,400,400); 
glutDisplayFunc(display); //for somereasion this loops twice?? 
	//allFunctions(); 

			//	
int subWindowYZ = glutCreateSubWindow(MainWindow,0, 400,400,400); 
glutDisplayFunc(displayYZ);
	//allFunctions(); 

int subWindowXZ = glutCreateSubWindow(MainWindow,0,0,400,400); 
glutDisplayFunc(displayXZ);
	//allFunctions(); 


glutMainLoop();

//friday tag added 0 instead of 1, see if it works
return 0;
} 


void displayMain() {
	

	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();
	glDrawPixels(mainWindowSizeWidth, mainWindowSizeHeight, GL_RGB, GL_FLOAT, PixelBuffer);
}
void display() {
	

	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();
	glDrawPixels(mainWindowSizeWidth, mainWindowSizeHeight, GL_RGB, GL_FLOAT, PixelBuffer);
	

	glFlush();
	//Jason Hui
	 
	if(isReadFile==true)
	{
		drawAllPolygons(); 
		isReadFile=false; 
	}else
	{
	allFunctions(); 
	}
	glutPostRedisplay(); 





	//Jason Hui
}// end Display
void displayXZ() {
	

	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();
	glDrawPixels(mainWindowSizeWidth, mainWindowSizeHeight, GL_RGB, GL_FLOAT, PixelBufferXZ);
	glFlush();
	//Jason Hui
	//	allFunctions(); 
	cout<<"displayXZ refresh, type anything and enter"<<endl; 
	//string something;
	//cin>>something; 
		glutPostRedisplay(); 
	//xyzDrawVertices(); 
							
	   
}// end Display
void displayYZ() {
	

	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();
	glDrawPixels(mainWindowSizeWidth, mainWindowSizeHeight,  GL_RGB, GL_FLOAT, PixelBufferYZ);
	glFlush();
		cout<<"display                    YZ refresh, type anything and enter"<<endl; 
	//string something;
	//cin>>something; 
			glutPostRedisplay(); 
	//Jason Hui
	   
}// end Display

//Jason Functions: END
//Jason Functions: END
//Jason Functions: END




