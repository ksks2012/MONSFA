#include "parameter.h"
#include "fa_algo.h"


int main(int argc, char** argv) {

    const int RUN_TIME = atoi(argv[1]);

    const int ITERATION = atoi(argv[2]);

    Parameter parameter(argv);

    int run = 0;

    while(run < RUN_TIME) {
    
        int itr = 0;
        
        fa_algo fa(parameter);
        
        fa.setBF();
        
        fa.initial();
            
        while(itr < ITERATION) {
                              
            fa.candidate((itr) / ITERATION);
                
            ++itr;
        
            //cout << setprecision(16) << itr << " " << fa.bestSol.fitness << endl;
            

            if(parameter.RTG) {
                        
                fa.bestSol.gnuplot();

            }

        }

        //cout << setprecision(16) << fa.bestSol.fitness << endl;
        fa.bestSol.printData();
        
        ++run;
    
    }
    
}
