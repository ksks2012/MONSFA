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

class fa_algo {

public:

    Solution bestSol;

private:

    Parameter parameter;

    Solution localBest;
        
    // function lowerlimut upperlimut dimension
    vector <double> LL;
    vector <double> UL;
    
    int D;
    
    int itr;
    
    //solution
    vector<Solution> candidateSol;
    vector<Solution> tmpSol;
    
public:

    fa_algo();
    fa_algo(Parameter);
    ~fa_algo();

    void setBF();

    void initial();
    void candidate(double);
        void moveFF(int, int);
        double gusDistribution();
            void UNIFORM(double *uni);
            
    void checkInit();


private:

};

#endif
