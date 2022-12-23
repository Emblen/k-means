#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string>
#include <numeric>
#include <random>
#include <time.h>
using namespace std;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }


const int CountryNum = 30, ClassNum = 4;
vector<vector<vector<double>>> Data(ClassNum), NewData(2<<10);
vector<vector<double>> Average(ClassNum, vector<double>(3,0)), NewAverage(ClassNum, vector<double>(3));
vector<double> datamin(3,10000.0), datamax(3,-10000.0);
vector<vector<double>> InputData;

void CalcAverage(){
    for(int i=0; i<ClassNum; i++){
        for(int k=0; k<3; k++){
            double sum = 0;
            for(auto v:Data[i]){
                sum += v[k+1];
            }
            NewAverage[i][k] = sum/Data[i].size();
        }
    }
}

//calculate distance between data and centroid for each class
//return min_distance class
int ReturnMinDistClass(double x, double y, double z){
    int min_distclass = -1;
    double min_dist = 100000.0;
    double dist;
    for(int i=0; i<ClassNum; i++){
        dist = (x-Average[i][0])*(x-Average[i][0]) + (y-Average[i][1])*(y-Average[i][1]) + (z-Average[i][2])*(z-Average[i][2]);
        
        if(dist<min_dist){
            min_dist = dist;
            min_distclass = i;
        }
    }
    return min_distclass;
}

void ClassNewData(){
    for(int i=0; i<ClassNum; i++){
        for(auto v:Data[i]){
            int newclass = ReturnMinDistClass(v[1],v[2],v[3]);
            NewData[newclass].push_back(v);
        }
    }
}

//Delete Data ans copy New class Data
void CopyData(){
    for(int i=0; i<ClassNum; i++){
        Data[i].clear();
        for(auto v:NewData[i]) Data[i].push_back(v);
    }
}

//memorize average and judge is_equal
bool Is_SameAverge(){
    bool istrue = true;
    for(int i=0; i<ClassNum; i++){
        for(int j=0; j<3; j++){
            if(Average[i][j] != NewAverage[i][j]) istrue = false;
            Average[i][j] = NewAverage[i][j];
        }
    }
    return istrue;
}

// Check Class Data
void CheckInputData(){
    cout << "Check Input" << endl;
    for(auto v:InputData){
        cout << v[0] << " " << v[1] << " " << v[2];
        cout << endl;
    }
}

void OutputFinalData(){
    for(int i=0; i<ClassNum; i++){
        char filename[256];
        sprintf(filename,"class%.2d.txt",i);
        ofstream outputfile(filename);

        for(auto v:Data[i]){
            for(int k=0; k<4; k++) outputfile << v[k] << " ";
            outputfile << endl;
        }
        outputfile.close();
    }
}

double Random0(double min, double max){
	return min + (max - min) * rand() / (double)RAND_MAX;
}

double Random1(){
	return CountryNum * rand() / (double)RAND_MAX;
}

void GenerateFirstCentroid(){
    //random min~max 
    vector<double> rangepick(3);
    for(int i=0; i<ClassNum; i++){
        for(int j=0; j<3; j++){
            rangepick[j] = Random0(datamin[j],datamax[j]);
        }
        NewAverage[i] = rangepick;
    }


    // pick data random
    // for(int i=0; i<ClassNum; i++){
    //     vector<double> pickdata = InputData[(int)Random1()];
    //     NewAverage[i] = pickdata;
    // }
    
    ofstream firstcentroid("firstcentroid.txt");
    for(int i=0; i<ClassNum; i++){
        for(int j=0; j<3; j++){
            firstcentroid << NewAverage[i][j] << " ";
        }
        firstcentroid << endl;
    }
    firstcentroid.close();
}



int main(){
    srand((unsigned int)time(NULL));

    //Input Data and unimportant classification
    for(int i=0; i<CountryNum; i++){
        double gdp, popden, birthrate;
        cin >> gdp >> popden >> birthrate;

        vector<double> cmpdata={gdp,popden,birthrate};
        InputData.push_back(cmpdata);

        for(int j=0; j<3; j++){
            if(chmin(datamin[j],cmpdata[j])) datamin[j]=cmpdata[j];
            if(chmax(datamax[j],cmpdata[j])) datamax[j]=cmpdata[j];
        }

        int cnum = i%ClassNum;
        Data[cnum].push_back({(double)i, gdp,popden,birthrate});
    }
    
    GenerateFirstCentroid();
    for(auto v:NewAverage){
        for(int i=0; i<3; i++){
            cout << v[i] << " ";
        }
        cout << endl;
    }

    // CheckInputData();


    int step=0;
    while(!Is_SameAverge() && step<1){
        ClassNewData();
        CopyData();
        CalcAverage();
        cout << "step=" << step << endl;
        for(auto v:NewAverage){
            for(int i=0; i<3; i++){
                cout << v[i] << " ";
            }
            cout << endl;
        }        
        step++;
    }

    OutputFinalData();
    return 0;
}