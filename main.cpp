#include "hc.h"


int main(int argc, char* argv[]){
    int run = atoi(argv[1]);
    int iteration = atoi(argv[2]);
    int bits = atoi(argv[3]);

    HillClimbing alg(run, iteration, bits);
    alg.Alg_run();
}