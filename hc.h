#include <iostream>
#include <vector>
#include <random>
using namespace std;

template <typename T>
using vec1D = vector<T>;


class HillClimbing{
    public:
        HillClimbing(int run, int iteration, int bits):total_run(run), total_iteration(iteration), total_bits(bits){
            random_device rd;
            random_generator.seed(rd());
            onemax_runbest.assign(total_run, 0);
            onemax_iterbest.assign(total_iteration + 1, 0);
        }

        void Alg_run(){
            for(int i = 0; i < total_run; ++i){
                Run_Reset();
                init();
                onemax_iterbest[0] += current_best;
                for(int j = 0; j < total_iteration; ++j){
                    vec1D<int> next = transition(solution);
                    int next_sum = evaluation(next);
                    determine(solution, one_sum, next, next_sum);
                    onemax_iterbest[j + 1] += current_best;
                }
                onemax_runbest[i] = current_best;
                // cout << current_best << endl;
            }


            for(size_t i = 0; i < onemax_iterbest.size(); ++i){
                cout << (double) onemax_iterbest[i] / total_run << endl;  
            }
        }

    private:
        int total_run;
        int total_iteration;
        int total_bits;
        vec1D<int> solution;
        int one_sum;
        int current_best;
        vec1D<int> onemax_runbest;
        vec1D<int> onemax_iterbest;
        mt19937_64 random_generator;

        int random_int(const int min, const int max){
            uniform_int_distribution<int> dis(min, max);
            return dis(random_generator);
        }
        double random_real(const double min, const double max){
            uniform_real_distribution<double> dis(min, max);
            return dis(random_generator);
        }
        void Run_Reset(){
            solution.assign(total_bits, 0);
            one_sum = 0;
            current_best = 0;
        }
        void init(){
            for(size_t i = 0; i < solution.size(); ++i){
                solution[i] = random_int(0, 1);
            }
            one_sum = evaluation(solution);
            if(one_sum >= current_best) current_best = one_sum;
        }
        int evaluation(const vec1D<int> &sol){
            int sum = 0;
            for(size_t i = 0; i < sol.size(); ++i){
                if(sol[i]){
                    ++sum;
                }
            }
            return sum;
        }
        vec1D<int> transition(const vec1D<int> &curr_sol){
            vec1D<int> next_solution = curr_sol;
            int rnd = random_int(0, total_bits - 1);
            if(next_solution[rnd]) next_solution[rnd] = 0;
            else next_solution[rnd] = 1;

            return next_solution;
        }
        void determine(vec1D<int> &curr_sol, int &curr_sum, vec1D<int> &next_sol, int &next_sum){
            if(next_sum >= curr_sum){
                curr_sum = next_sum;
                curr_sol = next_sol;

                if(next_sum > current_best) current_best = next_sum;
            }
        }
};