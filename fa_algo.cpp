#include "fa_algo.h"
#include <stdio.h>

fa_algo::fa_algo() {

}

fa_algo::fa_algo(Parameter parameter) {

    srand(time(NULL));

    this->parameter = parameter;
    
    bestSol = Population(parameter, parameter.POPULATION + parameter.NDS);
    candidateSol = Population(parameter, parameter.POPULATION * 2);
    recordSol = Population(parameter, parameter.POPULATION);

}

fa_algo::~fa_algo() {

}

void fa_algo::initial() {
  
    bestSol.initial(func);
    bestSol.FNDSorting(parameter.POPULATION + parameter.NDS);
    
    candidateSol.initial(func);
    candidateSol.FNDSorting(parameter.POPULATION);
    
}

void fa_algo::candidate(double itr) {
        
    this->itr = itr;

    //record P_{t-1}
    recordSol.copyPop(candidateSol, 0, parameter.POPULATION);
    
    //FA
    candidateSol.genNewSol(itr);
    
    //P_t + Q_t
    candidateSol.copyPop(recordSol, parameter.POPULATION, parameter.POPULATION * 2);

    //non-dominated sets <- P_t
    bestSol.copyPop(candidateSol, parameter.NDS, parameter.NDS + parameter.POPULATION);
    
    candidateSol.FNDSorting(parameter.POPULATION * 2);
    candidateSol.sortPopLV();
    
    candidateSol.CDS(parameter.POPULATION - 1);
    candidateSol.sortPopCDS();


    bestSol.FNDSorting(parameter.NDS + parameter.POPULATION);
    bestSol.sortPopLV();

    bestSol.CDS(parameter.NDS - 1);
    bestSol.sortPopCDS();

    //init crowdingDis 
    candidateSol.initialCD();
    bestSol.initialCD();

}

/**
  * set benchmark function
  */ 
void fa_algo::setBF() {

    //cout << "function " << parameter.FUNC_NUM << endl;

    func = Problem(parameter);

}
