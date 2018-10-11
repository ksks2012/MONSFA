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

    fitness = vector<double>(parameter.objectNum, 0.0);

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
            //genLocation(i);
            
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
