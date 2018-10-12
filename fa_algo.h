#ifndef __FA_ALGO_H__
#define __FA_ALGO_H__

#include <vector>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <climits>

#include "parameter.h"
#include "solution.h"
#include "problem.h"
#include "population.h"

class fa_algo {

public:

    Population bestSol;

private:

    Parameter parameter;

    Problem func;

    Population candidateSol; 
    Population recordSol;   
        
    int itr;

public:

    fa_algo();
    fa_algo(Parameter);
    ~fa_algo();
    
    void setBF();

    void initial();
    void candidate(double);


private:

};

#endif
