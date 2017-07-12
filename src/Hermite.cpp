#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;
typedef unsigned long ULONG;
double Hermite(bool bFlag, double position, ULONG numInterval, ULONG& iPos)
{
	double result;
	static double nextPosition=0,curPosition=0,lastPosition = 0,curVeloc=0,lastVeloc=0;
	static int index=0;
	if (bFlag) {
		nextPosition = position;
		curVeloc = (nextPosition - lastPosition) / 40.0;
		index += 2;

		result = (20 + 2 * index)*pow(index - 20.0,2)*lastPosition / 8000.0 +
			(60 - 2 * index)*pow(index,2)*curPosition / 8000.0 +
			index*pow(index - 20.0,2)*lastVeloc / 400.0 + (index - 20.0)*pow(index,2)*curVeloc / 400.0;
		if (index >= 2*numInterval) {
			index = 0;
			lastPosition = curPosition;
			curPosition = nextPosition;
			lastVeloc = curVeloc;
			iPos++;
		}
	}
	else
		result = 0;

	return result;
}
double Hermite2(bool bFlag, double position, ULONG numInterval, ULONG& iPos)
{
	double result;
	static double nextPosition=0,curPosition=0,lastPosition = 0,curVeloc=0,lastVeloc=0;
	static int index=0;
	if (bFlag) {
		nextPosition = position;
		curVeloc = (nextPosition - lastPosition) / 20.0;
		index += 1;

		result = (10 + 2 * index)*pow(index - 10.0,2)*lastPosition / 1000.0 +
			(30 - 2 * index)*pow(index,2)*curPosition / 1000.0 +
			index*pow(index - 10.0,2)*lastVeloc / 100.0 + (index - 10.0)*pow(index,2)*curVeloc / 100.0;
		if (index >= numInterval) {
			index = 0;
			lastPosition = curPosition;
			curPosition = nextPosition;
			lastVeloc = curVeloc;
			iPos++;
		}
	}
	else
		result = 0;

	return result;
}
int Hermite3(bool bFlag, int position, ULONG numInterval, ULONG& iPos)
{
	int result;
	static int nextPosition=0,curPosition=0,lastPosition = 0,curVeloc=0,lastVeloc=0;
	static int index=0;
	if (bFlag) {
		nextPosition = position;
		curVeloc = (nextPosition - lastPosition) / 20.0;
		index += 1;

		result = (10 + 2 * index)*pow(index - 10.0,2)*lastPosition / 1000.0 +
			(30 - 2 * index)*pow(index,2)*curPosition / 1000.0 +
			index*pow(index - 10.0,2)*lastVeloc / 100.0 + (index - 10.0)*pow(index,2)*curVeloc / 100.0;
		if (index >= numInterval) {
			index = 0;
			lastPosition = curPosition;
			curPosition = nextPosition;
			lastVeloc = curVeloc;
			iPos++;
		}
	}
	else
		result = 0;

	return result;
}
int linear(int position, ULONG numInterval, ULONG& iPos){
	static int lastP=0,curP=0;
	static int i=0;
	curP = position;
	i++;
	int result = (int)(lastP+(curP-lastP)/(double)numInterval*(double)i);
	if(i>=numInterval){
		iPos++;
		i=0;
		lastP = curP;
	}
	return result;
}
int main(){
    ofstream wrFile("Hermite.txt");
	ofstream wrFile2("Hermite3.txt");
	ofstream wrFile3("linear.txt");
	ifstream rdFile("sin.mak");
	if(!rdFile.is_open()){
		cout<<"file can't open!"<<endl;
	}
	string strnum;
	int *originData = new int[16384] ;
	double *waveData = new double[16384];
	int i=0,len = 0;
	while(getline(rdFile,strnum)){
		originData[i++] = stoi(strnum);
	}
	len = i -16;
	for(int j = 0; j<len; j++){
		waveData[j] = originData[j+15]/250.0;
	}
	ULONG index = 0;
	ULONG index2 = 0;
	ULONG index3 = 15;
	ULONG index4 = 15;
	wrFile.precision(10);
	while(index < len){
		wrFile<<Hermite(true,waveData[index],10,index)<<"\t\t"
			<<Hermite2(true,waveData[index2],10,index2)<<endl;
	}
	while(index3 < len ){
		wrFile2<<Hermite3(true,originData[index3],10,index3)<<endl;
		wrFile3<<linear(originData[index4],10,index4)<<endl;
	}

    wrFile.close();
	rdFile.close();
	delete [] originData;
	delete [] waveData;
    return 0;
}