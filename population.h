#ifndef __POPULATION_H__
#define __POPULATION_H__

#include <math.h>
#include <algorithm>    // std::sort

#include "solution.h"
#include "problem.h"

using namespace std;

typedef bool (*Compare)(Solution &, Solution &) ;

class Population{

private:

    Parameter parameter;
    
    vector<Solution> sol;

    Problem func;

    vector<Compare> comparefunc;

    double alpha;

public:
    Population();
    Population(Parameter, int);
    
    void initial(Problem &);
    void genNewSol(double);

    
    void moveFF(int , int);
        double solutionDistance(int , int);
        double gusDistribution();
        void UNIFORM(double *);
    void moveRand(int);

    void copyPop(const Population &, int, int);
    void sortPopLV();
    void sortPopCDS();

    //MO strategy
    void FNDSorting(size_t);
        bool isDominate(int, int);
    void CDS(int);

    void initialCD();
    void checkInit();

    void gnuplot();
    void printData();

private:

    static bool compareF1(Solution &, Solution &);
    static bool compareF2(Solution &, Solution &);
                   
    static bool compareLV (Solution &, Solution &);
    static bool compareCDS (Solution &, Solution &);

};

#endif
