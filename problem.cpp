#include "problem.h"

Problem::Problem() {

}

Problem::Problem(Parameter parameter) {

    this->parameter = parameter;
    
    switch(parameter.FUNC_NUM) {

        case 1:
            dimension = 1;
            LL = vector<double>(dimension, -1000);
            UL = vector<double>(dimension, 1000);
            
            break;
            
        case 2:
            dimension = 3;
            LL = vector<double>(dimension, -4);
            UL = vector<double>(dimension, 4);
            
            break;
        
        case 3:
        case 4:
        case 5:
            dimension = 30;
            LL = vector<double>(dimension, 0.0);
            UL = vector<double>(dimension, 1.0);
            
            break;
        
        case 6:
            dimension = 10;
            LL = vector<double>(dimension, -5.0);
            UL = vector<double>(dimension, 5.0);
            
            LL[0] = 0;
            UL[0] = 1;
            
            
            break;
            
        case 7:
            dimension = 10;
            LL = vector<double>(dimension, 0.0);
            UL = vector<double>(dimension, 1.0);
            
            break;
            
        default:
            cout << "unknown function" << endl;
            break;
    }

}

void Problem::calFitness(Solution &solution) {
    
    double g = 0;

    for(int i = 0; i < parameter.objectNum; ++i)
        solution.fitness[i] = 0;
    
    switch(parameter.FUNC_NUM) {
        
        case 1:

            for(int i = 0; i < dimension; ++i)
                solution.fitness[0] += pow(solution.location[i], 2.0);
            
            for(int i = 0; i < dimension; ++i)
                solution.fitness[1] += pow((solution.location[i] - 2), 2.0);
                       
            break;
            
        case 2:
            
            for(int i = 0; i < dimension; ++i)
                solution.fitness[0] += pow(solution.location[i] - (1.0 / sqrt(3)), 2.0);
                
            solution.fitness[0] = 1 - exp(-1 * solution.fitness[0]);
            
            for(int i = 0; i < dimension; ++i)
                solution.fitness[1] += pow(solution.location[i] + (1.0 / sqrt(3)), 2.0);
                
            solution.fitness[1] = 1 - exp(-1 * solution.fitness[1]);
                       
            break;
            
        case 3:
                
            solution.fitness[0] = solution.location[0];
                     
            for(int i = 1; i < dimension; ++i) {
                g += solution.location[i];
            }

            g = 1.0 + ((9.0 * g) / (dimension - 1.0));

            solution.fitness[1] = g * (1.0 - sqrt(solution.location[0] / g));
            
            break;
            
        case 4:
                
            solution.fitness[0] = solution.location[0];
                     
            for(int i = 1; i < dimension; ++i) {
                g += solution.location[i];
            }

            g = 1.0 + ((9.0 * g) / (dimension - 1.0));

            solution.fitness[1] = g * (1.0 - pow(solution.location[0] / g, 2.0));
            
            break;
            
        case 5:
                
            solution.fitness[0] = solution.location[0];
                     
            for(int i = 1; i < dimension; ++i) {
                g += solution.location[i];
            }

            g = 1.0 + ((9.0 * g) / (dimension - 1.0));

            solution.fitness[1] = g * (1.0 - sqrt(solution.location[0] / g)) - solution.location[0] / g * sin(10 * PI * solution.location[0]);
            
            break;
            
        case 6:
                
            solution.fitness[0] = solution.location[0];
                     
            for(int i = 1; i < dimension; ++i) {
                g += (solution.location[i] * solution.location[i] - 10 * cos(4 * PI * solution.location[i]));
            }

            g = 1.0 + (10 * (dimension - 1.0) + g);

            solution.fitness[1] = g * (1.0 - sqrt(solution.location[0] / g));
            
            break;
            
        case 7:
                
            solution.fitness[0] = 1 - exp(-4 * solution.location[0]) * pow(sin(6 * PI * solution.location[0]), 6.0);
                     
            for(int i = 1; i < dimension; ++i) {
                g += solution.location[i];
            }

            g = 1.0 + (9 * pow(g / (dimension - 1), 0.25));

            solution.fitness[1] = g * (1.0 - pow(solution.fitness[0] / g, 2.0));
            
            break;

        default:
            cout << "unknown function" << endl;
            break;
    }

    //NAN
    if(!(solution.fitness[0] == solution.fitness[0] && solution.fitness[1] == solution.fitness[1])) {
    
        cout << "NAN " << solution.fitness[0] << " " << solution.fitness[1] << " " << solution.location[0] << endl;
        fgetc(stdin);
    
    }


}


