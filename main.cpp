#include <mpi.h>
#include <iostream>
#include <vector> 
#include <algorithm>
#include <math.h>
#include <fstream>
using namespace std;

#define MCW MPI_COMM_WORLD



//get the total travel distance between each city in the list
double fitness(vector<int> list){
    vector<vector<int>> cityList = {
        {1,   179140,   750703}, 
        {2,    78270,   737081}, 
        {3,   577860,   689926}, 
        {4,   628150,   597095}, 
        {5,   954030,   510314}, 
        {6,   837880,   811285}, 
        {7,   410640,   846947}, 
        {8,   287850,   600161}, 
        {9,   270030,   494359}, 
        {10,  559020,   199445}, 
        {11,  353930,   542989}, 
        {12,  515920,   497472}, 
        {13,  648080,   470280}, 
        {14,  594550,   968799}, 
        {15,  386690,   907669}, 
        {16,   93070,   395385}, 
        {17,   93620,   313966}, 
        {18,  426870,    39662}, 
        {19,  437000,   139949}, 
        {20,  789810,   488001}, 
        {21,  749130,   575522}, 
        {22,  481030,   286118}, 
        {23,  670720,   392925}, 
        {24,  273890,   892877}, 
        {25,  138430,   562658}, 
        {26,   85480,   465869}, 
        {27,  775340,   220065}, 
        {28,  862980,   312238}, 
        {29,  155180,   263662}, 
        {30,  274070,    74689}, 
        {31,  333340,   456245}, 
        {32,  822150,   399803}, 
        {33,  158880,   612518}, 
        {34,  815560,   707417}, 
        {35,  678240,   709341}, 
        {36,  394470,   679221}, 
        {37,  631300,   846813}, 
        {38,  528320,   824193}, 
        {39,  666940,   845130}, 
        {40,  298650,   816352}, 
        {41,  243750,   745443}, 
        {42,  220500,   654221}, 
        {43,  338920,   381007}, 
        {44,  313110,   201386}, 
        {45,  856380,   564703}, 
        {46,  549250,   565255}, 
        {47,  537400,   604425}, 
        {48,  502110,   435463}, 
        {49,  498840,   590729}, 
        {50,  482310,   571034}, 
        {51,  416930,   765126}, 
        {52,  418400,   638700}, 
        {53,  374170,   695851}, 
        {54,  412370,   570904}, 
        {55,  301090,   737412}, 
        {56,  235690,   782470}, 
        {57,  475940,   439645}, 
        {58,  268540,   609753}, 
        {59,  130500,   712663}, 
        {60,   81660,   732470}, 
        {61,   64520,   711936}, 
        {62,  264690,   529248}, 
        {63,   90230,   612484}, 
        {64,   38370,   610277}, 
        {65,   15430,   579032}, 
        {66,  138890,   482432}, 
        {67,  264580,   421188}, 
        {68,   86690,   394738}, 
        {69,  209190,   347661}, 
        {70,  425890,   376154}, 
        {71,  312480,   177450}, 
        {72,  373360,   142350}, 
        {73,  442850,   106198}, 
        {74,  505100,   189757}, 
        {75,  542610,   224170}, 
        {76,  566730,   262940}, 
        {77,  615970,   237922}, 
        {78,  612120,   303181}, 
        {79,  634410,   320152}, 
        {80,  879480,   239867}, 
        {81,  868760,   286928}, 
        {82,  807670,   334613}, 
        {83,  943060,   368070}, 
        {84,  827280,   387076}, 
        {85,  896040,   413699}, 
        {86,  920900,   454842}, 
        {87,  746380,   440559}, 
        {88,  734300,   452247}, 
        {89,  730780,   471211}, 
        {90,  870570,   549620}, 
        {91,  607060,   453077}, 
        {92,  926580,   669624}, 
        {93,  812660,   614479}, 
        {94,  701420,   559132}, 
        {95,  688600,   580646}, 
        {96,  743800,   669521}, 
        {97,  819700,   857004}, 
        {98,  683690,   682649}, 
        {99,  732680,   857362}, 
        {100, 685760,   866857},
    };                                                                                                                                                                                                                                                                                

    double totalDistance = 0;
    //get distance between each city
    for(int i = 0; i < list.size()-1; i++){
        //get the points from the city list
        int first = list[i]-1;
        int second = list[i+1]-1;

        double x = pow(cityList[first][1] - cityList[second][1],2);
        double y = pow(cityList[first][2] - cityList[second][2],2);

        double distance = sqrt(x+y);
        totalDistance += distance;
    }
    //return 1/total distance to get a score that is better the higher it is
    return totalDistance;
}

vector<int> PMX(vector<int> parentA, vector<int> parentB){
    int start = rand()%100;
    int stop = rand()%100;

    if(start > stop){
        int temp = stop;
        stop = start;
        start = temp;
    }

    vector<int> child = parentA;    

    for(int i = start; i < stop; i++){
        //swap child[i] with child[parentA[wherever the the number that shows up at parentB[i]]]
        int toFind = parentB[i];

        //search through the vector to find the value
        for(int j = 0; j < parentA.size(); j++){
            if(parentA[j] == toFind){
                //swap two values
                int temp = child[j];
                child[j] = child[i];
                child[i] = temp;
            }
        }
    }

    return child;
}

vector<vector<int>> sortGeneration(vector<vector<int>> generation){
    int size = generation.size();
    for(int i = 0; i < size-1; i++){
        for(int j = 0; j < size-i-1; j++){
            if(fitness(generation[j]) > fitness(generation[j+1])){
                vector<int> temp = generation[j];
                generation[j] = generation[j+1];
                generation[j+1] = temp;
            }
        }
    }
    vector<vector<int>> pool(generation.begin(),generation.begin()+size/3);
    return pool;
}

vector<int> mutate(vector<int> orig){
    vector<int> mutated = orig;
    int start = rand()%100;
    int stop = rand()%100;

    if(start > stop){
        int temp = stop;
        stop = start;
        start = temp;
    }

    //split them up
    vector<int> first(orig.begin(), orig.begin()+start);
    vector<int> mid(orig.begin()+start, orig.begin()+stop);
    vector<int> last(orig.begin()+stop, orig.end());

    //switch one segment at random
    int which = rand()%3;
    switch(which){
        case 0:
            reverse(first.begin(),first.end());
            break;
        case 1:
            reverse(mid.begin(),mid.end());
            break;
        case 2:
            reverse(last.begin(),last.end());
            break;
    }

    //put them back together
    mutated = first;
    mutated.insert(mutated.end(), mid.begin(), mid.end());
    mutated.insert(mutated.end(), last.begin(), last.end());
    return mutated;
}

int main(int argc, char **argv){
    //initialize variables
    int size, rank, length, data, dest;
    int numPerGen = 50;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);
    MPI_Status status;
    srand(time(0)*(rank+1));
    vector<vector<int>> pool;
    double genAvg;
    bool keepGoing = true;
    int numOfGens = 1000;
    double lastGen = 0;

    //set up to write results to file
    ofstream results;
    results.open("results.txt", ofstream::out | ofstream::trunc);    
    
    //worker leader configuration where 0 is the leader
    if(rank == 0){
        //initialize a vector filled with numbers from 1-100
        vector<int> cities;
        for(int i = 0; i < 100; i++){
            cities.push_back(i+1);
        }

        //create first generation
        vector<vector<int>> generation;

        //shuffle cities into generation
        for(int i = 0; i < numPerGen; i++){
            random_shuffle(cities.begin(),cities.end());
            generation.push_back(cities);
        }

        while(numOfGens > 0){
            // take most fit half of the generation and make them the breeding pool
            pool = sortGeneration(generation);

            //write best solution to file
            results << numOfGens << "," << fitness(pool[0]) << endl;

            // create new generation
            generation.clear();
            int toDo = numPerGen - generation.size();

            // send work to each process once
            for(int i = 1; i < size; i++){
                int data[100];
                vector<int> parentA = pool[rand()%pool.size()];
                vector<int> parentB = pool[rand()%pool.size()];

                copy(parentA.begin(), parentA.end(), data);
                MPI_Send(data, 100, MPI_INT, i, 1, MCW);
                copy(parentB.begin(), parentB.end(), data);
                MPI_Send(data, 100, MPI_INT, i, 1, MCW);
                toDo--;
            }

            //recieve work from process then send more work
            while(toDo > 0){
                // recieve results
                int recieved[100];
                MPI_Recv(recieved, 100, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &status);
                vector<int> child(recieved, recieved+100);
                generation.push_back(child);

                // send PMX work to other processes
                int data[100];
                vector<int> parentA = pool[rand()%pool.size()];
                vector<int> parentB = pool[rand()%pool.size()];

                copy(parentA.begin(), parentA.end(), data);
                MPI_Send(data, 100, MPI_INT, status.MPI_SOURCE, 1, MCW);
                copy(parentB.begin(), parentB.end(), data);
                MPI_Send(data, 100, MPI_INT, status.MPI_SOURCE, 1, MCW);
                toDo--;
            }

            //recieve remaining work
            for(int i = 1; i < size; i++){
                int recieved[100];
                MPI_Recv(recieved, 100, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &status);
                vector<int> child(recieved, recieved+100);
                generation.push_back(child);
            }

            //do work with only one process (for comparison)
            // while (toDo+5 > 0){
            //     vector<int> parentA = pool[rand()%pool.size()];
            //     vector<int> parentB = pool[rand()%pool.size()];
            //     vector<int> child = PMX(parentA, parentB);
            //     generation.push_back(child);
            //     toDo--;
            // }

            genAvg = 0;
            for(int i = 0; i < pool.size(); i++){
                // cout << fitness(pool[i]) << endl;
                genAvg = genAvg + fitness(pool[i]);
            }
            genAvg = genAvg/pool.size();
            // cout << "before:" << genAvg << endl;

            //if average for this generation and last generation are the same, mutate 3 times
            if(genAvg == lastGen){
                int mutationStrength = 30;
                for(int i = 0; i < mutationStrength; i++){
                    vector<int> mutated = mutate(pool[0]);
                    generation.push_back(mutated);
                }
                cout << "mutated" << endl;
            }

            lastGen = genAvg;
            cout << numOfGens << ":" << genAvg << endl;
            numOfGens--;
        }
        //send kill code
        for(int i = 1; i < size; i++){
            int data[100];
            data[0] = -1;
            MPI_Send(data, 100, MPI_INT, i, 1, MCW);
        }
        results.close();
    } 
    else{
        while(keepGoing){
            //recieve work and convert them to vectors
            int data[100];
            MPI_Recv(data, 100, MPI_INT, 0, MPI_ANY_TAG, MCW, &status);
            if(data[0] == -1){
                break;
            }
            vector<int> parentA(data, data+100);
            MPI_Recv(data, 100, MPI_INT, 0, MPI_ANY_TAG, MCW, &status);
            vector<int> parentB(data, data+100);

            //do work
            vector<int> child = PMX(parentA, parentB);

            //send results
            int kid[child.size()];
            copy(child.begin(), child.end(), kid);
            MPI_Send(kid, 100, MPI_INT, 0, 1, MCW);
        }
    }
    cout << "Process " << rank << " has ended" << endl;
	MPI_Finalize();
    return 0;
}  