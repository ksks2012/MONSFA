#include "fa_algo.h"
#include <algorithm>    // std::sort
#include <stdio.h>

fa_algo::fa_algo() {

}

fa_algo::fa_algo(Parameter parameter) {

    srand(time(NULL));

    this->parameter = parameter;
    
    bestSol = vector<Solution>(parameter.POPULATION + parameter.NDS, Solution(parameter));
    candidateSol = vector<Solution>(parameter.POPULATION * 2, Solution(parameter));
    recordSol = vector<Solution>(parameter.POPULATION, Solution(parameter));
    
}

fa_algo::~fa_algo() {

}

bool fa_algo::isDominate(int i, int j) {

    int count = 0;

    for(int k = 0; k < 2; ++k) {
    
        if(candidateSol[i].fitness[k] > candidateSol[j].fitness[k])
            return false;
        
        if(candidateSol[i].fitness[k] < candidateSol[j].fitness[k])
            ++count;
        
    }
    
    if(count > 1)
        return true;
        
    return false;
    
}

// Fast Non-dominated Sorting
void fa_algo::FNDSorting(vector<Solution> &candidateSol, int size) {

    vector<int> L;
    vector< vector<Solution> > F = vector< vector<Solution> >(1000); 

    for(int i = 0; i < size; ++i) {
        
        candidateSol[i].level = 0;
    
        for(int j = 0; j < size; ++j) {
    
            if(i != j) {
            
                if(isDominate(i, j)) {
                
                    candidateSol[i].S_p.push_back(j);
                
                } else if(isDominate(j, i)) {
                
                    ++candidateSol[i].n_p;
                
                }
            
            }
        
        }   //end j
        
        if(candidateSol[i].n_p == 0) {
        
            candidateSol[i].level = 1;

            F[0].push_back(candidateSol[i]);

        }
        
    }   //end i
    
    int i = 0;

    while(F[i].size() != 0) {
    
        vector <Solution> H;
    
        for(int j = 0; j < F[i].size(); ++j) {
        
            for(int k = 0; k < F[i][j].S_p.size(); ++k) {
            
                --candidateSol[F[i][j].S_p[k]].n_p;
                
                if(candidateSol[F[i][j].S_p[k]].n_p == 0) {
                
                    H.push_back(candidateSol[F[i][j].S_p[k]]);   
                
                    candidateSol[F[i][j].S_p[k]].level = i + 2;
                    
                }
            
            }   //end k
        
        }   //end j
        
        ++i;

        if(H.size() != 0) {
        
            for(int j = 0; j < H.size(); ++j)
                F[i].push_back(H[j]);   
        
        }

    }
    
    for(int i = 0; i < size; ++i) {
    
        candidateSol[i].S_p.clear();
        candidateSol[i].n_p = 0;
    
    }
        
}

void fa_algo::initial() {
    
    for(int i = 0; i < parameter.POPULATION + parameter.NDS; ++i) {

        bestSol[i].setDimension(D);
        bestSol[i].setRange(UL, LL);
        bestSol[i].level = parameter.POPULATION + parameter.NDS;

        for(int j = 0; j < 2; ++j)
            bestSol[i].fitness[j] = INT_MAX;

    }
      
    FNDSorting(bestSol, parameter.POPULATION + parameter.NDS);
        
    for(int i = 0; i < parameter.POPULATION; ++i) {

        candidateSol[i].setDimension(D);
        candidateSol[i].setRange(UL, LL);
        candidateSol[i].initLocation();
        candidateSol[i].calFitness();
        //bestSol[i] = candidateSol[i];
        
    }

    FNDSorting(candidateSol, parameter.POPULATION);
    
    /*
    for(int i = 0; i < parameter.POPULATION; ++i) {    
    
        cout << i << " " << candidateSol[i].level << " " << candidateSol[i].n_p << " " << candidateSol[i].fitness[0] << " " << candidateSol[i].fitness[1] << " " << endl;
        
    }
    
    fgetc(stdin);
   */
}

void fa_algo::candidate(double itr) {
        
    this->itr = itr;
    
    for(int i = 0; i < parameter.POPULATION; ++i) {
    
        recordSol[i] = candidateSol[i];
    
    }
    
    bool dominated = false;
    
    //
    for(int i = 0; i < parameter.POPULATION; ++i) {
    
        for(int j = 0; j < parameter.POPULATION; ++j) {
        
            //I_j > I_i
            if(isDominate(j, i)) {
            
                dominated = true;
            
                moveFF(i, j);
            
                candidateSol[i].feasible();
        
                candidateSol[i].calFitness();
                         
            }    
            
        }   //end j
        
        if(!dominated) {
        
            //TODO random move : levy ?  
        
        }   
        
        dominated = false;
               
    }   //end i
    
    for(int i = 0; i < parameter.POPULATION; ++i) {
    
        candidateSol[parameter.POPULATION + i] = recordSol[i];
    
    }
    
    FNDSorting(candidateSol, parameter.POPULATION * 2);
    
    //sort by level
    sort(candidateSol.begin(), candidateSol.end(), compare);
    
    for(int i = 0; i < parameter.POPULATION; ++i) {
    
        bestSol[parameter.NDS + i] = candidateSol[i];
    
    }
    
    FNDSorting(bestSol, parameter.POPULATION + parameter.NDS);

    sort(bestSol.begin(), bestSol.end(), compare);

}

bool fa_algo::compare (Solution &a, Solution &b) {

     return a.level < b.level;
      
}

void fa_algo::moveFF(int i, int j) {

    double distance = 0.0;
    
    double I = 1.0;   //difference of fitness
    
    for(int k = 0; k < 2; ++k)
        I *= candidateSol[i].fitness[k] / candidateSol[j].fitness[k];
    
    for(int k = 0; k < D; ++k) {
    
        distance += (candidateSol[i].location[k] - candidateSol[j].location[k]) * (candidateSol[i].location[k] - candidateSol[j].location[k]);   
    
    }
    
    distance = sqrt(distance);
    
    double beta = parameter.beta_0 * exp(-1 * parameter.LAC * pow(distance, 2.0));
        
    for(int k = 0; k < D; ++k) {    
    
        double range = abs(UL[k] - LL[k]);
    
		double tmp = parameter.alpha_0 * gusDistribution() * range;

        //TODO I_{ij}^t 
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
