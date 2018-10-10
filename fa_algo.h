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

    vector<Solution> bestSol;

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
    vector<Solution> recordSol;
    
public:

    fa_algo();
    fa_algo(Parameter);
    ~fa_algo();

    void setBF();
    
    void FNDSorting(vector<Solution> &, size_t);
        bool isDominate(Solution &, Solution &);

    void initial();
    void candidate(double);
        void moveFF(int, int);
        void moveRand(int);
        
        double gusDistribution();
            void UNIFORM(double *uni);
            
        void CDS(vector<Solution> &,int);
            static bool compareF1(Solution &, Solution &);
            static bool compareF2(Solution &, Solution &);
            
        double solutionDistance(Solution &, Solution &);
        
        static bool compareLV (Solution &, Solution &);
        static bool compareCDS (Solution &, Solution &);
        
    void checkInit();


private:

};

#endif
