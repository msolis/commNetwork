/*
*	Mauricio Solis
*	April 2013
*	Communication Networks Final Project
*	Encoding Schemes
*	Version - Final
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "functions.h"

int main()
{
	string line;		//Used to grab the input data from file
	int scheme;			//Var for selecting encoding scheme
	ifstream inputData;
	inputData.open("inputData.txt");	//Input Data
	
	//Encodeing Scheme Selection...
	cout<<"Choose scheme: \n\t0: NRZ-L\n\t1: NRZ-I\n\t2: B-AMI\n\t3: Manchester\n\t4: D-Manchester\n";
	cin>>scheme;
	cout<<"\t*******Borders are represtented by '|' characters*******\n";
	while(!inputData.eof())
	{
		getline(inputData, line);
		switch(scheme)
		{
			case 0: 
					NRZ_L(line);	//Non Return to Zero Line
					break;
			case 1: 
					NRZ_I(line);	//Non Return to Zero Line-Invert
					break;
			case 2: 
					B_AMI(line);	//Bipolar Alternate Mark Inversion
					break;	
			case 3: 
					manchester(line);	//Manchester encoding
					break;
			case 4: 
					D_Manchester(line);	//D Manchester
					break;
		}
	}
	inputData.close();
	return 0;
}