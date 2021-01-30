#include "randgen.h"
#include <vector>
#include <queue>
#include <set>
#include <chrono>
#include <iostream>
#include <cmath>
#include <cmath>
#include <fstream>
using namespace std;
using namespace std::chrono;

int i,j;

struct cells
{
    int x ;
    int y ;

} ;

bool coordinateVisited ( vector <cells> storedcoordinates, int a , int b ) //func stores the visited coordinates in a vector built with a struct which contains x and y coordinates as integers
{
    for (int i=0 ; i< storedcoordinates.size(); i++ )
    {
        if ((storedcoordinates[i].x == a) && (storedcoordinates[i].y == b) ){
            return true ;
        }
    }

    return false ;
}


int checkSolution2(int ed[][3], int e){
    for(i = 0; i < e; i++) {
        if(ed[i][0] == -1 && ed[i][1] == -1) continue;
        for(j = 0; j < e; j++) {
            if(ed[i][0] == -1 && ed[i][1] == -1) continue;
            if(j == i)
                continue;
            if(ed[j][0] == ed[i][0] || ed[j][0] == ed[i][1] || ed[j][1] == ed[i][0] || ed[j][1] == ed[i][1]) {
                if(ed[j][2] == ed[i][2]) {
                    cout << "****" <<endl;
                    cout << "The solution is INCORRECT !!!!"<< endl;
                    cout << "****" <<endl;
                    return 0;
                }
            }
        }
    }
    cout << "****" <<endl;
    cout << "The solution is Correct !!!!"<< endl;
    cout << "****" <<endl;
    return 1;
}

int maxDegree(int ed[][3],int v,int randE){
    vector<int> edgeCount(v,0);

    for(i = 0; i < randE; i++) {
        edgeCount[ed[i][0]]++;
        edgeCount[ed[i][1]]++;
    }
    int max = 0;
    for (int k = 0; k < v; ++k) {
        if(edgeCount[k]>max){
            max = edgeCount[k];
        }
    }
    return max;
}

int maxColor(int ed[][3], int randE){
    int max = 0;
    for(i = 0; i < randE; i++) {
        if(ed[i][2]>max){
            max = ed[i][2];
        }
    }
    return max;
}

void EdgeColor(int ed[][3], int e) {
    int i, c, j;
    for(i = 0; i < e; i++) {
        if(ed[i][0] == -1 && ed[i][1] == -1) continue;
        c = 1; //assign color to current edge as c i.e. 1 initially.
        flag:
        ed[i][2] = c;
        //If the same color is occupied by any of the adjacent edges, then discard this color and go to flag again and try next color.
        for(j = 0; j < e; j++) {
            if(ed[i][0] == -1 && ed[i][1] == -1) continue;
            if(j == i)
                continue;
            if(ed[j][0] == ed[i][0] || ed[j][0] == ed[i][1] || ed[j][1] == ed[i][0] || ed[j][1] == ed[i][1]) {
                if(ed[j][2] == ed[i][2]) {
                    c++;
                    goto flag;
                }
            }
        }
    }
}


float STD (vector<float>&data)
{
    float sum =0.0, mean,std=0.0 ;
    for (int i=0; i<data.size(); i++)
    {
        sum += data[i];
    }
    mean=sum/data.size();
    for (int j=0 ; j< data.size(); j++)
    {
        std += pow (data[j]-mean,2);
    }
    std = sqrt(std/data.size());


    return std;
}

float StandardError(float std, int n)
{
    return std/ sqrt (n) ;
}


void RunningTime (vector <float> &all_times_observed,ofstream & out)
{
    float total_time= 0.0 ;
    int size= all_times_observed.size();
    for (int i=0 ; i <size ; i++)
    {
        total_time+= all_times_observed[i];
    }
    float std = STD(all_times_observed);
    float sample_mean= total_time/size; // sample mean

    const float tval90=1.645; // t-value %90 confidence
    const float tval95= 1.96 ; //t-val %95

    float std_error = StandardError(std, size) ;

    float uppermean_90 = sample_mean+tval90*std_error ;
    float lowermean_90 = sample_mean-tval90*std_error ;

    float uppermean_95 = sample_mean+tval95*std_error ;
    float lowermean_95 = sample_mean-tval95*std_error ;


    cout<< "Mean time: "<< sample_mean<<"ms" <<endl;
    cout<< "SD: "<< std<<endl  ;
    cout<<"standard error"<< std_error<<endl ;
    cout<< "with %90 confidence level error interval "<< lowermean_90<< "-" <<uppermean_90<<endl ;
    cout<< "with %95 confidence level error interval "<< lowermean_95<< "-" <<uppermean_95<<endl ;


    out << sample_mean << "," << std << "," << std_error<< "," << lowermean_90<<"-"<< uppermean_90 << "," << lowermean_95<<"-" <<uppermean_95<< endl;
}


void measure_correctness(vector<int> & correct){
    int sumcorrect=0;
    for (int k = 0; k < correct.size(); ++k) {
        if(correct[k]) sumcorrect++;
    }
    cout << "Correctness ratio is: %" << double(sumcorrect*100)/correct.size()<< endl;
}

void measure_optimality(vector<int> & degreeDifferences){
    int sumcorrect=0;
    for (int k = 0; k < degreeDifferences.size(); ++k) {
        if(degreeDifferences[k]<=1) sumcorrect++;
    }
    cout << "Optimality ratio is: %" << double(sumcorrect*100)/degreeDifferences.size()<< endl;
}



int main()
{


    ofstream out;
    out.open("measures.csv");
    out << "Size(E),Mean Time (ms),Standard Deviation,Standard Error,90% CL,%95 CL"<<endl;

    int iterations=250;
    //int vertex=50;
    //int edge= 300 ;
   // for (int l = 0; l < 7; ++l) {
  //      edge += 150;

        vector <int>correct_vec ;
        vector<int>optimal_vec ;
        vector<float> runtimes;
      //  for (int k = 0; k < iterations; ++k) {
           
            RandGen random ;
    int n ; //=e,i,j;
           // n= random.RandInt(5,100);
            cells cell ;
            cout<<"Enter number of vertices:" ; // and edges respectively:";
    cin>>n ; //>> e;
  

            vector <cells> storedcoordinates;

            int randE=random.RandInt(n,n*(n-1)/2);
            //int edge=floor(pow(vertex,14.0/9.0) );
           // int randE = edge ;
           // cout<< randE <<endl ;
            int ed[randE][3];

            int cnt=0;
            for(i = 1; i <= n; i++) {
                for(j = i+1; j <= n; j++) {
                    ed[cnt][0] = -1;
                    ed[cnt][1] = -1;
                    ed[cnt][2] = -1;
                    cnt++;
                    if(cnt == randE) break;
                }
                if(cnt == randE) break;
            }

            for(i=0;i<randE;i++)
            {
                cout<<"\nEnter edge vertices of edge "<<i+1<<" :";
                //cin>>x>>y; // if want to give edge inputs manually
                int x= random.RandInt(0,n-1);
                int y= random.RandInt(0,n-1);
                while (x==y || coordinateVisited(storedcoordinates, x, y) || coordinateVisited(storedcoordinates, y, x))
                {
                    x= random.RandInt(0,n-1);
                    y= random.RandInt(0,n-1);
                }
                cell.x = x;
                cell.y = y;

                ed[i][0]=x;
                ed[i][1]=y;

                cout<<"from "<< x <<" to "<<y<< endl;
                storedcoordinates.push_back(cell) ;
            }

            auto start = high_resolution_clock::now();
            EdgeColor(ed, randE);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
           // cout << duration.count()<< endl;
            runtimes.push_back(float(duration.count())/pow(10,3));

            for(i=0;i<randE;i++)
            {
                cout<<"Edge "<<i+1<<" is coloured "<<ed[i][2] <<"\n";
            }
            int result =checkSolution2(ed,randE);
            correct_vec.push_back(result);
            int max_c=maxColor(ed,randE) ;
            int max_d= maxDegree(ed,n,randE);
            optimal_vec.push_back(abs(max_c-max_d));
            cout << "The max color of this graph is " << maxColor(ed,randE) << " and the max degree is " << maxDegree(ed,n,randE)<< endl;

       // }
    // measure_correctness(correct_vec) ;
     //   measure_optimality(optimal_vec);
        //out << edge << ",";
    //    RunningTime(runtimes,out);
    //}
    return 0 ;
}
