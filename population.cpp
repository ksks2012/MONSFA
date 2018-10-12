#include "population.h"

#include <fstream>
#include <unistd.h>

Population::Population() {



}

Population::Population(Parameter parameter, int solSize) {

    this->parameter = parameter;

    sol = vector<Solution> (solSize, Solution(parameter));

    comparefunc = vector<Compare>(parameter.objectNum);

    comparefunc[0] = compareF1;
    comparefunc[1] = compareF2;

    alpha = parameter.alpha_0;

}

void Population::initial(Problem &func) {

    this->func = func;

    for(size_t i = 0; i < sol.size(); ++i) {
    
        sol[i].setDimension(func.dimension);
        sol[i].setRange(func.UL, func.LL);
        sol[i].initLocation();
        
        func.calFitness(sol[i]);
        
    }
    
}

void Population::genNewSol(double itr) {

    bool dominated = false;

    for(int i = 0; i < parameter.POPULATION; ++i) {
        
        dominated = false;
               
        for(int j = 0; j < parameter.POPULATION; ++j) {
        
            //I_j > I_i
            if(isDominate(j, i)) {
            
                dominated = true;
            
                moveFF(i, j);
                
                sol[i].feasible();
        
                func.calFitness(sol[i]);
        
            }    
            
        }   //end j
        
        if(!dominated) {
       
            moveRand(i);
            
            sol[i].feasible();
        
            func.calFitness(sol[i]);
       
        }    

    }   //end i

    //update alpha
    alpha = parameter.alpha_0 * pow(0.9, itr);

}

void Population::moveFF(int x, int y) {

    double distance = solutionDistance(x, y);
    
    double I = 1.0;   //difference of fitness
    
    for(int i = 0; i < parameter.objectNum; ++i)
        I *= sol[x].fitness[i] / sol[y].fitness[i];
    
    double beta = parameter.beta_0 * exp(-1 * parameter.LAC * pow(distance, 2.0));
        
    for(int i = 0; i < func.dimension; ++i) {    
    
        double range = abs(func.UL[i] - func.LL[i]);
    
		//double tmp = parameter.alpha_0 * gusDistribution() * range;
        double tmp = alpha * gusDistribution() * range;

        if(!(I == I)) {
        
            I = 0;
            
        }
        
        if(!(tmp == tmp)) {
        
            cout << "tmp error " << alpha << endl;
            fgetc(stdin);
        }

        //TODO I_{ij}^t 
        sol[x].location[i] = sol[x].location[i] + (sol[y].location[i] -  sol[y].location[i]) * beta + tmp;
        
    }
    
}

void Population::moveRand(int x) {

    for(int i = 0; i < func.dimension; ++i) {    
    
        double range = abs(func.UL[i] - func.LL[i]);
    
		double tmp = 0.01 * gusDistribution() * range;
        
        if(!(tmp == tmp)) {
        
            cout << "tmp error" << endl;
            fgetc(stdin);
        }
        
        //TODO I_{ij}^t 
        sol[x].location[i] = sol[x].location[i] + tmp;
        
    }
    
}

//Box-Muller
double Population::gusDistribution() {

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

void Population::UNIFORM(double *uni) {

    int seed;
    
    for (int i = 0, x = 0; i < 2; ++i, x = x + 666) {
    
	    seed = rand() + x;  //+ for short time random
	    seed = seed % 1000;
	    uni[i] = (double)seed;
	    uni[i] = uni[i] / 1000.0;
	    
    }
	
}

//Euclid distance
double Population::solutionDistance(int x, int y) {

    double distance = 0.0;
    
    for(int i = 0; i < func.dimension; ++i) {
    
        distance += (sol[x].location[i] - sol[y].location[i]) * (sol[x].location[i] - sol[y].location[i]);   
    
    }
    
    distance = sqrt(distance);

    return distance; 
    //return x.fitness - y.fitness;

}

void Population::copyPop(const Population &toRecord, int start, int end) {

    int size = end - start;

    if(end > (int) sol.size()) {

        cout << "out of copy size" << endl;
        return;

    }

    for(int i = 0; i < size; ++i) {

        sol[start + i] = toRecord.sol[i];

    }

}

void Population::sortPopLV() {

    //sort by level
    sort(sol.begin(), sol.end(), compareLV);
    /*
    for(size_t i = 0; i < sol.size(); ++i)
        cout << sol[i].level << " " << sol[i].fitness[0] << " " << sol[i].fitness[1]  << endl;

    fgetc(stdin);
    */
}

void Population::sortPopCDS() {

    sort(sol.begin(), sol.end(), compareCDS);

}

//compare
bool Population::compareF1(Solution &a, Solution &b) {

    return a.fitness[0] > b.fitness[0];

}

bool Population::compareF2(Solution &a, Solution &b) {

    return a.fitness[1] > b.fitness[1];

}

bool Population::compareLV(Solution &a, Solution &b) {

     return a.level < b.level;
      
}

bool Population::compareCDS(Solution &a, Solution &b) {

    if(a.crowdingDis == 0 || b.crowdingDis == 0)
        return a.level < b.level;

    //if(a.level < b.level)
        //return a.level < b.level;

    return (a.level <= b.level && a.crowdingDis > b.crowdingDis);
      
}


void Population::FNDSorting(size_t size) {

    vector< vector<Solution> > F = vector< vector<Solution> >(size + 1); 
    
    for(size_t i = 0; i < size; ++i) {
        
        sol[i].level = 0;
    
        for(size_t j = 0; j < size; ++j) {
    
            if(i != j) {
            
                if(isDominate(i, j)) {
                
                    sol[i].S_p.push_back(j);
                
                } 
                if(isDominate(j, i)) {
                
                    ++sol[i].n_p;
                    
                }
            
            }
        
        }   //end j
        
        if(sol[i].n_p == 0) {
        
            sol[i].level = 1;

            F[0].push_back(sol[i]);

        }
        
    }   //end i
    
    int i = 0;

    while(F[i].size() != 0) {
    
        vector <Solution> H;
    
        for(size_t j = 0; j < F[i].size(); ++j) {
        
            for(size_t k = 0; k < F[i][j].S_p.size(); ++k) {
            
                --sol[F[i][j].S_p[k]].n_p;
                
                if(sol[F[i][j].S_p[k]].n_p == 0) {
                
                    H.push_back(sol[F[i][j].S_p[k]]);   
                
                    sol[F[i][j].S_p[k]].level = i + 2;
                    
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
    
        sol[i].S_p.clear();
        sol[i].n_p = 0;
    
    }
        
}

void Population::CDS(int cutIndex) {

    int level = sol[cutIndex].level;

    //double d_ij, d_ik;

    //int index;

    int begin = 0, end = 0;
    bool first = true;
    
    for(size_t i = 0; i < sol.size(); ++i) {
    
        if(sol[i].level == level && first) {

            first = false;
            begin = i;
        
        } else if(sol[i].level != level && !first) {

            end = i - 1;
            break;
        
        }
        end = sol.size();
    }
    
    if(end - begin <= 1)
        return;

    //own method
    if(parameter.CD == 0) {

        sort(sol.begin() + begin, sol.begin() + end, compareF1);

        sol[begin].crowdingDis = sol[end - 1].crowdingDis = INT_MAX;
        
        for(int i = begin + 1; i < end - i; ++i) {
        
            sol[i].crowdingDis += solutionDistance(i + 1, i - 1);

        }

    } 
    //NSGA-II
    else if (parameter.CD == 1) {

        for(int i = 0; i < parameter.objectNum; ++i) {

            sort(sol.begin() + begin, sol.begin() + end, comparefunc[i]);

            sol[begin].crowdingDis = sol[end - 1].crowdingDis = INT_MAX;

            for(int j = begin + 1; j < end - 1; ++j) {
            
                sol[j].crowdingDis += (sol[j + 1].fitness[i] - sol[j - 1].fitness[i]) / 
                                                (sol[begin].fitness[i] - sol[end - 1].fitness[i]);

            }    
            
        }

    }
  
}

bool Population::isDominate(int x, int y) {

    int count = 0;

    for(int i = 0; i < parameter.objectNum; ++i) {
    
        if(sol[x].fitness[i] > sol[y].fitness[i])
            return false;
        
        if(sol[x].fitness[i] < sol[y].fitness[i])
            ++count;
        
    }
    
    if(count >= 1)
        return true;
        
    return false;
    
}

void Population::initialCD() {

    for(size_t i = 0; i < sol.size(); ++i) {
        
        sol[i].crowdingDis = 0;
        
    }

}

//~~~~~~~~~~~~~~~~~~~
void Population::checkInit() {

    for(int i = 0; i < parameter.POPULATION; ++i) {
    
        for(int j = 0; j < func.dimension; ++j) {
            if(sol[i].location[j] < func.LL[j] || sol[i].location[j] > func.UL[j])
                cout << i << " " << j << " x error" << endl;
                
            //if(sol[i].velocity[j] < (func.LL[j] * 2) || sol[i].velocity[j] > (func.UL[j]  * 2))
            //    cout << i << " " << j << " v error" << endl;
        }
        
    }

}

void Population::gnuplot() {

    fstream fout;
    fout.open("output.dat", ios::out);
    
    for(int i = 0; i < parameter.NDS; ++i) 
        fout << sol[i].fitness[0] << " " << sol[i].fitness[1] << endl;
    
    fout.close();

    FILE *fp = popen("gnuplot point.gp", "r"); 
    if(fp) {
        usleep(parameter.NDS * 150);
    }           
    pclose(fp);

}

void Population::printData() {

    fstream fout;
    fout.open("output.dat", ios::out);
    
    for(int i = 0; i < parameter.NDS; ++i) 
        fout << sol[i].fitness[0] << " " << sol[i].fitness[1] << endl;
    
    fout.close();

    //sol[0].printData();

}