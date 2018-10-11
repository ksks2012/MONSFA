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

bool fa_algo::isDominate(Solution &a, Solution &b) {

    int count = 0;

    for(int i = 0; i < 2; ++i) {
    
        if(a.fitness[i] > b.fitness[i])
            return false;
        
        if(a.fitness[i] < b.fitness[i])
            ++count;
        
    }
    
    if(count >= 1)
        return true;
        
    return false;
    
}

// Fast Non-dominated Sorting
void fa_algo::FNDSorting(vector<Solution> &candidateSol, size_t size) {

    vector< vector<Solution> > F = vector< vector<Solution> >(candidateSol.size() + 1); 
    
    for(size_t i = 0; i < size; ++i) {
        
        candidateSol[i].level = 0;
    
        for(size_t j = 0; j < size; ++j) {
    
            if(i != j) {
            
                if(isDominate(candidateSol[i], candidateSol[j])) {
                
                    candidateSol[i].S_p.push_back(j);
                
                } 
                if(isDominate(candidateSol[j], candidateSol[i])) {
                
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
    
        for(size_t j = 0; j < F[i].size(); ++j) {
        
            for(size_t k = 0; k < F[i][j].S_p.size(); ++k) {
            
                --candidateSol[F[i][j].S_p[k]].n_p;
                
                if(candidateSol[F[i][j].S_p[k]].n_p == 0) {
                
                    H.push_back(candidateSol[F[i][j].S_p[k]]);   
                
                    candidateSol[F[i][j].S_p[k]].level = i + 2;
                    
                }
            
            }   //end k
        
        }   //end j
        
        ++i;

        if(H.size() != 0) {
        
            for(size_t j = 0; j < H.size(); ++j)
                F[i].push_back(H[j]);   
        
        }

    }
    
    for(size_t i = 0; i < size; ++i) {
    
        candidateSol[i].S_p.clear();
        candidateSol[i].n_p = 0;
    
    }
        
}

void fa_algo::initial() {
    
    for(size_t j = 0; j < bestSol.size(); ++j) {

        bestSol[j].setDimension(func.dimension);
        bestSol[j].setRange(func.UL, func.LL);
        bestSol[j].initLocation();
        func.calFitness(bestSol[j]);

    }    

    FNDSorting(bestSol, bestSol.size());
        
    for(int j = 0; j < parameter.POPULATION; ++j) {

        candidateSol[j].setDimension(func.dimension);
        candidateSol[j].setRange(func.UL, func.LL);
        candidateSol[j].initLocation();
        func.calFitness(candidateSol[j]);
    }

    FNDSorting(candidateSol, parameter.POPULATION);

}

void fa_algo::candidate(double itr) {
        
    this->itr = itr;
    
    for(int j = 0; j < parameter.POPULATION; ++j) {
    
        recordSol[j] = candidateSol[j];
    
    }
    
    bool dominated = false;
    
    //FA
    for(int j = 0; j < parameter.POPULATION; ++j) {
        
        dominated = false;
               
        for(int i = 0; i < parameter.POPULATION; ++i) {
        
            //I_j > I_i
            if(isDominate(candidateSol[i], candidateSol[j])) {
            
                dominated = true;
            
                moveFF(j, i);
                
                candidateSol[j].feasible();
        
                func.calFitness(candidateSol[j]);

            }    
            
        }   //end i
        
        if(!dominated) {
       
            moveRand(j);
            
            candidateSol[j].feasible();

            func.calFitness(candidateSol[j]);

        }    

    }   //end j
    
    //P_t + Q_t
    for(int j = 0; j < parameter.POPULATION; ++j) {
    
        candidateSol[parameter.POPULATION + j] = recordSol[j];
    
    }
    
    for(int j = 0; j < parameter.POPULATION; ++j) {

        bestSol[parameter.NDS + j] = candidateSol[j];
    
    }
    
    FNDSorting(candidateSol, parameter.POPULATION * 2);
    
    //sort by level
    sort(candidateSol.begin(), candidateSol.end(), compareLV);

    CDS(candidateSol, candidateSol[parameter.POPULATION - 1].level);
    
    sort(candidateSol.begin(), candidateSol.end(), compareCDS);

    //non-dominated sets <- P_t
    /*
    for(int j = 0; j < parameter.POPULATION; ++j) {

        bestSol[parameter.NDS + j] = candidateSol[j];
    
    }
    */
    FNDSorting(bestSol, bestSol.size());

    sort(bestSol.begin(), bestSol.end(), compareLV);
    
    CDS(bestSol, bestSol[parameter.NDS - 1].level);
    
    sort(bestSol.begin(), bestSol.end(), compareCDS);

    /*
    for(int j = 0; j < bestSol.size(); ++j) {    
    
        cout << j << " " << bestSol[j].level << " " << bestSol[j].n_p << " " << bestSol[j].fitness[0] << " " << bestSol[j].fitness[1] << " " << bestSol[j].crowdingDis << endl;
        
    }  */  
    //fgetc(stdin);

    //init crowdingDis 
    for(size_t j = 0; j < candidateSol.size(); ++j) {
        
        candidateSol[j].crowdingDis = 0;
        
    }
    
    for(size_t j = 0; j < bestSol.size(); ++j) {
        
        bestSol[j].crowdingDis = 0;
        
    }
    
}

void fa_algo::CDS(vector<Solution> &candidateSol, int level) {

    //double d_ij, d_ik;

    //int index;

    int begin = 0, end = 0;
    bool first = true;
    
    for(size_t j = 0; j < candidateSol.size(); ++j) {
    
        if(candidateSol[j].level == level && first) {

            first = false;
            begin = j;
        
        } else if(candidateSol[j].level != level && !first) {

            end = j - 1;
            break;
        
        }
        end = candidateSol.size();
    }
    
    if(end - begin <= 1)
        return;

    //own method
    if(parameter.CD == 0) {
        sort(candidateSol.begin() + begin, candidateSol.begin() + end, compareF1);

        candidateSol[begin].crowdingDis = candidateSol[end - 1].crowdingDis = INT_MAX;
        
        for(int j = begin + 1; j < end - 1; ++j) {
        
            candidateSol[j].crowdingDis += solutionDistance(candidateSol[j + 1], candidateSol[j - 1]);

        }

    } 
    //NSGA-II
    else if (parameter.CD == 1) {

        for(int i = 0; i < 2; ++i) {

            switch(i) {
                case 0:
                    sort(candidateSol.begin() + begin, candidateSol.begin() + end, compareF1);
                    break;
                case 1:
                    sort(candidateSol.begin() + begin, candidateSol.begin() + end, compareF2);
                    break;
                default:
                    break;
            }         

            candidateSol[begin].crowdingDis = candidateSol[end - 1].crowdingDis = INT_MAX;

            for(int j = begin + 1; j < end - 1; ++j) {
            
                candidateSol[j].crowdingDis += (candidateSol[j + 1].fitness[i] - candidateSol[j - 1].fitness[i]) / 
                                                (candidateSol[begin].fitness[i] - candidateSol[end - 1].fitness[i]);

            }    
            
        }

    }
  
}

bool fa_algo::compareF1(Solution &a, Solution &b) {

    return a.fitness[0] > b.fitness[0];

}

bool fa_algo::compareF2(Solution &a, Solution &b) {

    return a.fitness[1] > b.fitness[1];

}

bool fa_algo::compareLV(Solution &a, Solution &b) {

     return a.level < b.level;
      
}

bool fa_algo::compareCDS(Solution &a, Solution &b) {

    if(a.crowdingDis == 0 || b.crowdingDis == 0)
        return a.level < b.level;

    //if(a.level < b.level)
        //return a.level < b.level;

    return (a.level <= b.level && a.crowdingDis > b.crowdingDis);
      
}

//Euclid distance
double fa_algo::solutionDistance(Solution &x, Solution &y) {

    double distance = 0.0;
    
    for(int j = 0; j < func.dimension; ++j) {
    
        distance += (x.location[j] - y.location[j]) * (x.location[j] - y.location[j]);   
    
    }
    
    distance = sqrt(distance);

    return distance; 
    //return x.fitness - y.fitness;

}

void fa_algo::moveFF(int j, int i) {

    double distance = solutionDistance(candidateSol[j], candidateSol[i]);
    
    double I = 1.0;   //difference of fitness
    
    for(int i = 0; i < 2; ++i)
        I *= candidateSol[j].fitness[i] / candidateSol[i].fitness[i];
    
    double beta = parameter.beta_0 * exp(-1 * parameter.LAC * pow(distance, 2.0));
        
    for(int i = 0; i < func.dimension; ++i) {    
    
        double range = abs(func.UL[i] - func.LL[i]);
    
		double tmp = parameter.alpha_0 * gusDistribution() * range;
        
        if(!(I == I)) {
        
            I = 0;
            
        }
        
        if(!(tmp == tmp)) {
        
            cout << "tmp error" << endl;
            fgetc(stdin);
        }

        //TODO I_{ij}^t 
        candidateSol[j].location[i] = candidateSol[j].location[i] + (candidateSol[i].location[i] -  candidateSol[j].location[i]) * beta + tmp;
        
    }
    
}

void fa_algo::moveRand(int j) {

    for(int i = 0; i < func.dimension; ++i) {    
    
        double range = abs(func.UL[i] - func.LL[i]);
    
		double tmp = 0.01 * gusDistribution() * range;
        
        if(!(tmp == tmp)) {
        
            cout << "tmp error" << endl;
            fgetc(stdin);
        }
        
        //TODO I_{ij}^t 
        candidateSol[j].location[i] = candidateSol[j].location[i] + tmp;
        
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
    
    for (int j = 0, x = 0; j < 2; ++j, x = x + 666) {
    
	    seed = rand() + x;  //+ for short time random
	    seed = seed % 1000;
	    uni[j] = (double)seed;
	    uni[j] = uni[j] / 1000.0;
	    
    }
	
}

//~~~~~~~~~~~~~~~~~~~
void fa_algo::checkInit() {

    for(int j = 0; j < parameter.POPULATION; ++j) {
    
        for(int i = 0; i < func.dimension; ++i) {
            if(candidateSol[j].location[i] < func.LL[i] || candidateSol[j].location[i] > func.UL[i])
                cout << j << " " << i << " x error" << endl;
                
            //if(candidateSol[j].velocity[i] < (func.LL[i] * 2) || candidateSol[j].velocity[i] > (func.UL[i]  * 2))
            //    cout << j << " " << i << " v error" << endl;
        }
        
    }

}

/**
  * set benchmark function
  */ 
void fa_algo::setBF() {

    //cout << "function " << parameter.FUNC_NUM << endl;

    func = Problem(parameter.FUNC_NUM);

}
