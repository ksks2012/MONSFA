#include "parameter.h"
#include <cmath>

Parameter::Parameter() {

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
