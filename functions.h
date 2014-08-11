#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

void NRZ_L(string line)
{
	int enc[8];//Set array for an 8 bit input
	cout<<"\nNRZ-L:\n\t";
	cout<<"Data:\t\t";
	for(int i=0; i<line.size(); i++) //Only iterate for the line size, 8 bit input.
	{
			cout<<setw(3)<<line[i]; //Used to view the input data.
			if(line[i] == '1') //Check if the input bit is a 1
				enc[i] = -5; //If so, set to -5
			else
				enc[i] = 5; //Else if it is 0, change polarity, 5.
	}
	cout<<"\n\tEncoded:\t";
	for(int k=0; k<line.size(); k++)
		cout<<"|"<<setw(2)<<enc[k]; //Cout the output and border
	cout<<"|\n"; //Set final border
}

void NRZ_I(string line)
{
	int enc[8];
	cout<<"\nNRZ-I:\n\t";
	cout<<"Data:\t\t";
	for(int i=0; i<line.size(); i++)
		{
			cout<<setw(3)<<line[i];
			if(line[i] == '1') //If the input bit is 1.
				enc[i] = -5; //Set output to -5.
			else
				enc[i] = 5; //Else if it's 0, set it to 5. (Change polarities
		}
	//This below checks the output to see whether the next bit is a
	// 0 or 1. This is required for NRZ-I. When the next bit is a 0, the
	//output remains the same.
	for(int j=0; enc[j+1] != NULL; j++)
	{
		if(enc[j+1] == 0)  //If the next bit is a 0
			enc[j+1] = enc[j];	//Set the previous bit to the current.
		if(enc[j+1] == enc[j]) //If the next bit is equal to the current bit
		{
			if(enc[j+1] = -5) //If the next bit is -5
				enc[j+1] = 5; //change polarities, 5
			else
				enc[j+1] = -5;//Else if it's 5, change it to -5
		}
	}
	cout<<"\n\tEncoded:\t";
	for(int k=0; k<line.size(); k++)
		cout<<"|"<<setw(2)<<enc[k];
	cout<<"|\n";
}

void B_AMI(string line)
{
	int enc[8];
	int prev_1bit = 0; //Counter for checking the previous 1bit. This is used to change the polarity of the 1bits.
	cout<<"\nB-AMI:\n\t";
	cout<<"Data:\t\t";
	for(int i=0; i<line.size(); i++)
	{
		cout<<setw(3)<<line[i];
		if(line[i] == '1')
		{
			if(prev_1bit == -5)//Check if the previous 1 bit is -5
			{
				enc[i] = 5; //If so, set the output to a different polarity, 5
				prev_1bit = 5; //Set previous 1 bit to current, 5
			}
			else if(prev_1bit == 5) //Check if the previous 1 bit is 5
			{
				enc[i] = -5; //If so, set the output to a different polarity, -5
				prev_1bit = -5; //Set previous 1 bit to current, -5
			}
			else// This statement ONLY runs once. It is used to set the intial value in case the first bit
				//of the input is 1. It will be intialized as 5.
			{
				enc[i] = 5;
				prev_1bit = 5;
			}
		}
		else
			enc[i] = 0; //If there is a 0 bit, give a no line(neutral) output
	}
	cout<<"\n\tEncoded:\t";
	for(int k=0; k<line.size(); k++)
		cout<<"|"<<setw(2)<<enc[k];
	cout<<"|\n";
}
void manchester(string line)
{
	int enc[8];
	int trans[8];//Set array to handle transition in between borders.
	cout<<"\nManchester:\n\t";
	cout<<"Data:\t\t";//Cout the input data with good format
		cout<<setw(4)<<line[0]<<setw(4)<<" "<<line[1];
		cout<<setw(5)<<line[2]<<setw(5)<<"  "<<line[3];
		cout<<setw(6)<<line[4]<<setw(5)<<"  "<<line[5];
		cout<<setw(5)<<line[6]<<setw(4)<<"  "<<line[7];
	for(int i=0; i<line.size(); i++) //Only iterate for the line size, 8 bit input.
	{
		if(line[i] == '1')
		{//If input bit is 1, go from Low to High
			enc[i] = -5;
			trans[i] = 5;
		}
		else//If input bit is 0, go from High to Low
		{
			enc[i] = 5;
			trans[i] = -5;
		}
	}
	cout<<"\n\tEncoded:\t";
	for(int k=0; k<line.size(); k++)
		cout<<"|"<<setw(2)<<enc[k]<<" "<<trans[k];
	cout<<"|\n";
}
void D_Manchester(string line)
{
	int enc[8];
	int trans[8];//Set array to handle transition in between borders.
	cout<<"\nD-Manchester: Starting at 5.\n\t";
	cout<<"Data:\t\t";//Cout the input data with good format
		cout<<setw(4)<<line[0]<<setw(4)<<" "<<line[1];
		cout<<setw(5)<<line[2]<<setw(5)<<"  "<<line[3];
		cout<<setw(6)<<line[4]<<setw(5)<<"  "<<line[5];
		cout<<setw(5)<<line[6]<<setw(4)<<"  "<<line[7];
	enc[0] = 5;
	trans[0] = -5;
	for(int i=1; i<line.size(); i++) //Only iterate for the line size, 8 bit input.
	{
		if(line[i] == '1')
		{//If input bit is 1, change polarity in the middle of the bit.
			if(trans[i-1] == -5)
			{
				enc[i] = -5;
				trans[i] = 5;
			}
			else if(trans[i-1] == 5)
			{
				enc[i] = 5;
				trans[i] = -5;
			}
		}
		else if (line[i] == '0')//If input bit is 0, switch at the beginning of bit. 
		{
			if(trans[i-1] == 5)
			{
				enc[i] = -5;
				trans[i] = 5;
			}
			else
			{
				enc[i] = 5;
				trans[i] = -5;
			}
		}
	}
	cout<<"\n\tEncoded:\t";
	for(int k=0; k<line.size(); k++)
		cout<<"|"<<setw(2)<<enc[k]<<" "<<trans[k];
	cout<<"|\n";
}
