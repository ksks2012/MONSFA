#include "parameter.h"
#include <cmath>

Parameter::Parameter() {

}

Parameter::Parameter(char **argv) {

        
    setITERATION(atoi(argv[2]));
    
    setPopultion(atoi(argv[3]));
    
    setFuncNum(atoi(argv[4]));

    setObjectNum(atoi(argv[5]));
    
    setLAC(atof(argv[6]));
    
    setAlpha(atof(argv[7]));
        
    setBeta(atof(argv[8]));
    
    setNDS(atoi(argv[9]));
    
    setRTG(atoi(argv[10]));

    setCD(atoi(argv[11]));

}

Parameter::~Parameter() {

}

void Parameter::setITERATION(int ITERATION) {

    this->ITERATION = ITERATION;

}

void Parameter::setPopultion(int POPULATION) {

    this->POPULATION = POPULATION;

}

void Parameter::setFuncNum(int FUNC_NUM) {

    this->FUNC_NUM = FUNC_NUM;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Parameter::setObjectNum(int objectNum) {

    this->objectNum = objectNum;

}

void Parameter::setLAC(double LAC) {

    this->LAC = LAC;

}

void Parameter::setAlpha(double alpha_0) {

    this->alpha_0 = alpha_0;

} 

void Parameter::setBeta(double beta_0) {

    this->beta_0 = beta_0;

}

void Parameter::setNDS(int NDS) {

    this->NDS = NDS;

}

void Parameter::setRTG(int RTG) {

    this->RTG = RTG;

} 

void Parameter::setCD(int CD) {
    this->CD = CD;
}