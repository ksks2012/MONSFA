#include "solution.h"
#include "stdio.h"

Solution::Solution() {


}

Solution::Solution(Parameter parameter) {

    this->parameter = parameter;
    this->localFitness = INT_MAX;
    
    this->n_p = 0;
    this->level = 0;
    this->crowdingDis = 0;

}

Solution::~Solution() {


}

void Solution::setDimension(int D) {
    
    dimension = D;
    location = vector<double>(dimension, 0.0);

}

void Solution::setRange(vector<double> &UL, vector<double> &LL) {

    this->UL = UL;
    this->LL = LL;
    
    
    //TODO 
    this->range = UL[0] - LL[0];

}

void Solution::initLocation() {


    for(int i = 0; i < dimension; ++i) {
    
        genLocation(i);
    
    }

}

void Solution::genLocation(int idx) {

    double r =  (double) rand() / RAND_MAX;
    
    location[idx] = r * range + LL[idx];

}

void Solution::feasible() {

    for (int i = 0; i < dimension; ++i) {
		
        if(checkLocation(i)) {
        
            location[i] = max(location[i], LL[i]);
            location[i] = min(location[i], UL[i]);  
        
        }
		
	}

}

double Solution::RAND() {

    return (double) rand() / RAND_MAX;

}

double Solution::RAND(double lowwer, double upper) {
	
	return lowwer + (upper - lowwer) * rand() / (RAND_MAX + 1.0);

}

bool Solution::checkLocation(int idx) {

    if(location[idx] > UL[idx] || location[idx] < LL[idx])
        return true;
        
    return false;

}

void Solution::printData() {

    for(int i = 0; i < dimension; ++i) {
    
        cout << location[i] << " " ; 
    
    }
    
    cout << endl;

}

void Solution::calFitness() {

    double g = 0;

    for(int i = 0; i < 2; ++i)
        fitness[i] = 0;
    
    switch(parameter.FUNC_NUM) {
        
        case 1:

            for(int i = 0; i < dimension; ++i)
                fitness[0] += pow(location[i], 2.0);
            
            for(int i = 0; i < dimension; ++i)
                fitness[1] += pow((location[i] - 2), 2.0);
                       
            break;
            
        case 2:
            
            for(int i = 0; i < dimension; ++i)
                fitness[0] += pow(location[i] - (1.0 / sqrt(3)), 2.0);
                
            fitness[0] = 1 - exp(-1 * fitness[0]);
            
            for(int i = 0; i < dimension; ++i)
                fitness[1] += pow(location[i] + (1.0 / sqrt(3)), 2.0);
                
            fitness[1] = 1 - exp(-1 * fitness[1]);
                       
            break;
            
        case 3:
                
            fitness[0] = location[0];
                     
            for(int i = 1; i < dimension; ++i) {
                g += location[i];
            }

            g = 1.0 + ((9.0 * g) / (dimension - 1.0));

            fitness[1] = g * (1.0 - sqrt(location[0] / g));
            
            break;
            
        case 4:
                
            fitness[0] = location[0];
                     
            for(int i = 1; i < dimension; ++i) {
                g += location[i];
            }

            g = 1.0 + ((9.0 * g) / (dimension - 1.0));

            fitness[1] = g * (1.0 - pow(location[0] / g, 2.0));
            
            break;
            
        case 5:
                
            fitness[0] = location[0];
                     
            for(int i = 1; i < dimension; ++i) {
                g += location[i];
            }

            g = 1.0 + ((9.0 * g) / (dimension - 1.0));

            fitness[1] = g * (1.0 - sqrt(location[0] / g)) - location[0] / g * sin(10 * PI * location[0]);
            
            break;
            
        case 6:
                
            fitness[0] = location[0];
                     
            for(int i = 1; i < dimension; ++i) {
                g += (location[i] * location[i] - 10 * cos(4 * PI * location[i]));
            }

            g = 1.0 + (10 * (dimension - 1.0) + g);

            fitness[1] = g * (1.0 - sqrt(location[0] / g));
            
            break;

        default:
            cout << "unknown function" << endl;
            break;
    }

    //NAN
    if(!(fitness[0] == fitness[0] && fitness[1] == fitness[1])) {
    
        cout << "NAN " << fitness[0] << " " << fitness[1] << " " << location[0] << endl;
        fgetc(stdin);
    
    }


}

