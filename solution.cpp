#include "solution.h"

Solution::Solution() {


}

Solution::Solution(Parameter parameter) {

    this->parameter = parameter;
    this->localFitness = INT_MAX;
    
    this->n_p = 0;
    this->level = 0;

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
    
    location[idx] = r * range + LL[0];

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

    for(int i = 0; i < 2; ++i)
        fitness[i] = 0;
    
    switch(parameter.FUNC_NUM) {
        
        case 1:

            for(int i = 0; i < dimension; ++i)
                fitness[0] += pow(location[i], 2.0);
            
            for(int i = 0; i < dimension; ++i)
                fitness[1] += pow((location[i] - 2), 2.0);
                       
            break;

        default:
            cout << "unknown function" << endl;
            break;
    }

}

