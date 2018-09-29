#include "fa_algo.h"
#include <algorithm>    // std::sort

fa_algo::fa_algo() {

}

fa_algo::fa_algo(Parameter parameter) {

    srand(time(NULL));

    this->parameter = parameter;
    
    candidateSol = vector<Solution>(parameter.POPULATION, Solution(parameter));
    tmpSol = vector<Solution>(parameter.POPULATION, Solution(parameter));
    
}

fa_algo::~fa_algo() {

}


void fa_algo::initial() {
    
    //TODO fitness
    bestSol.setDimension(D);
    
    for(int i = 0; i < 2; ++i)
        bestSol.fitness[i] = INT_MAX;
    
    localBest.setDimension(D);
    
    //UL[0] - LL[0]; 
        
    for(int i = 0; i < parameter.POPULATION; ++i) {
    
        candidateSol[i].setDimension(D);
        candidateSol[i].setRange(UL, LL);
        candidateSol[i].initLocation();
        candidateSol[i].calFitness();
    
        //TODO fitness
           
    }
    
}

void fa_algo::candidate(double itr) {
        
    this->itr = itr;
    
    for(int i = 0; i < parameter.POPULATION; ++i) {
    
        tmpSol[i] = candidateSol[i];
    
    }
    
    //
    for(int i = 0; i < parameter.POPULATION; ++i) {
    
        for(int j = 0; j < parameter.POPULATION; ++j) {
        
            //I_j > I_i
            //TODO fitness
            if(1) {
            
                moveFF(i, j);
            
                candidateSol[i].feasible();
        
                candidateSol[i].calFitness();

                //TODO fitness

                         
            }
 
        }
               
    }
    
}

void fa_algo::moveFF(int i, int j) {

    double range = abs(UL[0]-LL[0]);
    
    double distance = 0.0;
    
    for(int k = 0; k < D; ++k) {
    
        distance += (candidateSol[i].location[k] - candidateSol[j].location[k]) * (candidateSol[i].location[k] - candidateSol[j].location[k]);   
    
    }
    
    distance = sqrt(distance);
    
    double beta = 0.8 * exp(-1 * parameter.LAC * pow(distance, 2.0)) + 0.2;
        
    for(int k = 0; k < D; ++k) {
    
		double tmp = 0.5 * gusDistribution() * range;

        candidateSol[i].location[k] = candidateSol[i].location[k] + (candidateSol[j].location[k] -  candidateSol[i].location[k]) * beta + tmp;
    
    }

}

//Box-Muller
double fa_algo::gusDistribution() {

    double E = 0;       //Expected value
    double D = 0.1;     //TODO

    double uni[2];
    UNIFORM(uni);  //generate two normal distribution number
    
	double A, B, C, r;
    	
    A = sqrt((-2) * log(uni[0]));
    B = 2 * PI * uni[1];
    C = A * cos(B);
    r = E + C * D;    //E,D分别是期望和方差 

    return r;

}

void fa_algo::UNIFORM(double *uni) {

    int seed;
    
    for (int i = 0, x; i < 2; ++i, x = x + 666) {
    
	    seed = rand() + x;  //+666 for short time random
	    seed = seed % 1000;
	    uni[i] = (double)seed;
	    uni[i] = uni[i] / 1000.0;
	    
    }
	
}

//~~~~~~~~~~~~~~~~~~~
void fa_algo::checkInit() {
 
    for(int i = 0; i < parameter.POPULATION; ++i) {
    
        for(int j = 0; j < D; ++j) {
            if(candidateSol[i].location[j] < LL[j] || candidateSol[i].location[j] > UL[j])
                cout << i << " " << j << " x error" << endl;
                
            //if(candidateSol[i].velocity[j] < (LL[j] * 2) || candidateSol[i].velocity[j] > (UL[j]  * 2))
            //    cout << i << " " << j << " v error" << endl;
        }
        
    }

}


/**
  * set benchmark function
  */ 
void fa_algo::setBF() {

    //cout << "function " << parameter.FUNC_NUM << endl;
    
    switch(parameter.FUNC_NUM) {

        case 1:
            D = 1;
            LL = vector<double>(D, -1000);
            UL = vector<double>(D, 1000);
            
            break;
            
        default:
            cout << "unknown function" << endl;
            break;
    }

}
