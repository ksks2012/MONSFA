#include "parameter.h"
#include "fa_algo.h"
#include <fstream>
#include <unistd.h>

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
        
        fa.checkInit();
    
        while(itr < ITERATION) {
                              
            fa.candidate(itr);
                
            ++itr;
        
            //cout << setprecision(16) << itr << " " << fa.bestSol.fitness << endl;
            
            if(parameter.RTG) {
            
                fstream fout;
                fout.open("output.dat", ios::out);
                
                for(int i = 0; i < parameter.NDS; ++i) 
                    fout << fa.bestSol[i].fitness[0] << " " << fa.bestSol[i].fitness[1] << endl;
                
                fout.close();
            
                FILE *fp = popen("gnuplot point.gp", "r"); 
                if(fp) {
                    usleep(parameter.NDS * 150);
                }           
                pclose(fp);

            }

        }

        //cout << setprecision(16) << fa.bestSol.fitness << endl;
        //fa.bestSol.printData();
        
        fstream fout;
        fout.open("output.dat", ios::out);
        
        for(int i = 0; i < parameter.NDS; ++i) 
            fout << fa.bestSol[i].fitness[0] << " " << fa.bestSol[i].fitness[1] << endl;
        
        fout.close();
        ++run;
    
    }
    
}
