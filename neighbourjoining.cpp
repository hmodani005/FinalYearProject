#include<stdio.h>
#include<iostream>
#include<vector>
#include<math.h>
#include<string>
#include<conio.h>
using namespace std;
double dist[742][742],qmatrix[742][742];
double newdist[742][742];
int n,counter;
vector<int> nodes;
void getinput()
{
    int i,j;
    cin>>n;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            cin>>dist[i][j];
        }
        nodes.push_back(i);
    }
}
pair<int, int> calculateqmatrix(vector<double> sumarr)
{
    int i,j;
    pair<int,int> minpair;
    double min= 100000;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(i!=j)
            {
                qmatrix[i][j]= ( (n-2)*(dist[i][j]) )- sumarr[i] - sumarr[j];
                if(qmatrix[i][j] < min)
                {
                    min=  qmatrix[i][j];
                    minpair= make_pair(i,j);
                }
            }
            else
            {
                qmatrix[i][j]=0;
            }
        }
    }
    return minpair;
}
void calculatesum(vector<double> &sumarr)
{
    sumarr.clear();
    double sum;
    int i,j;
    for(i=0; i<n; i++)
    {
        sum=0;
        for(j=0; j<n; j++)
        {
            sum += dist[i][j];
        }
        sumarr.push_back(sum);
    }
}

void updatedist(pair<int,int> minpair)
{
//    cout<<minpair.first<<" "<<minpair.second<<endl;
    int i,j,in=0,jn;
    double tempvec[742] = {0.0};
    for(i=0; i<n; i++)
    {
        jn=0;
        if(i!=minpair.first && i!=minpair.second)
        {
            for(j=0; j<n; j++)
            {
                if(j!= minpair.second  && j!= minpair.first)
                {
//                    cout<<i<<"<"<<j<<"<"<<in<<"<"<<j;
//                    cout<<endl;
                    newdist[in][jn++] = dist[i][j];
                }
                else
                {
                    tempvec[in] += dist[i][j];
//                    cout<<tempvec[in]<<"- "<<endl;
                }
            }
            in++;
        }
    }

    for(j=0; j<in; j++)
    {
        newdist[j][in] = newdist[in][j] = (tempvec[j]- dist[minpair.first][minpair.second])/2;
//        cout<<j<<">"<<in<<">>"<<newdist[j][in]<<endl;
    }
    for(i=0; i<=in; i++)
    {
        for(j=0; j<=in; j++)
        {
            dist[i][j]= newdist[i][j];
        }
    }
}
void print(double mat[800][800])
{
    for(int i=0 ; i<n ; i++)
    {
        for(int j=0 ; j<n ; j++)
        {
            cout<<mat[i][j]<<" ";
        }
        cout<<endl<<endl;
    }
    return;
}
void print(vector<int> nodes)
{
    for(int i=0 ; i<nodes.size() ; i++)
    {
        cout<<nodes[i]<<" ";
    }
    cout<<endl<<endl;
}
void print(vector<double> nodes)
{
    for(int i=0 ; i<nodes.size() ; i++)
    {
        cout<<nodes[i]<<" ";
    }
    cout<<endl<<endl;
}
void print(vector< pair<pair<int, int>,int> > gt)
{
    for(int i=0 ; i<gt.size() ; i++)
    {
        cout<<gt[i].first.first<<" "<<gt[i].first.second<<" "<<gt[i].second<<"\n";
    }
    cout<<endl<<endl;
}
int main()
{
    int i,j;
    double sum;
    vector<double> sumarr;
    pair<int,int> minpair;
    vector< pair<pair<int, int>,int> > guidetree;
    getinput();
    counter=n;
    int error=0;
    while(n!=1 && error!=1)
    {
        calculatesum(sumarr);
        minpair= calculateqmatrix(sumarr);
        i=minpair.first;
        j=minpair.second;
        error=0;
        if(i==j)
        {
            error=1;
        }
        else if(j<i)
        {
            int temp =i;
            i=j;
            j=temp;
        }
        if(error==1)
        {
            cout<<"Error, i becomes equal j\n";
        }
        else
        {
            guidetree.push_back(make_pair(make_pair(nodes[minpair.first],nodes[minpair.second]),counter));
            nodes.erase(nodes.begin()+i);
            nodes.erase(nodes.begin()+j-1);
            nodes.push_back(counter);
            counter++;
            double delfu,delgu;//f-> i // g-> j
            delfu= (dist[minpair.first][minpair.second])/2 + (sumarr[minpair.first] - sumarr[minpair.second] )/( 2*(n-2) );
            delgu= dist[minpair.first][minpair.second] - delfu;
            updatedist(minpair);
            n--;
        }
    }
    print(guidetree);

}

/*
Input case:
5
0 	5 	9 	9 	8
5 	0 	10 	10 	9
9 	10 	0 	8 	7
9 	10 	8 	0 	3
8 	9 	7 	3 	0

source: Wiki

expected output:
0 1 5
2 5 6
3 4 7
6 7 8

for output to be of form A B C
A is the Ath string, B is Bth string and
C is the new string that is made after aligning A with B
Initially all n strings are numbered from 0 to n-1.
Change the output for the guide tree from the function print mentioned at line 136
*/
