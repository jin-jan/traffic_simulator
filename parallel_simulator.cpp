#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_FILE_NAME 100

void helpOutput(void)
{
    std::cout << "parallel traffic analyzer\n"
                 "USAGE: sta [OPTIONS]\n"
                 "OPTIONS:\n"
                 "-f FILE    read csv file\n"
                 "-c CARS    number of cars\n"
                 "-t ITER    number of iterations or simulation time\n"
                 "-h         Display the help information\n" << std::endl;
}

void defaultConfig(void)
{
    std::cout << "Default configuration:\n"
                 "    file name:  simulation_2500_1800.csv\n"
                 "    number of cars:                 2500\n"
                 "    number of iterations:           1800s\n"
                <<  std::endl;
    exit(EXIT_FAILURE);
}


void grep_car(char *file_name, int num_cars){
    int i;
    char grep_cmd[MAX_FILE_NAME];

    #pragma omp parallel for private(i,grep_cmd) shared(file_name)
    for(i=0; i < num_cars; ++i){
        sprintf(grep_cmd, "grep -E \"^%d,\" %s > car_%d.csv", i, file_name, i);
        system(grep_cmd);
    }
}


void get_reduction(int iter_time){
    int i, j;
    FILE *fp;
    char file_name[] = "car";
    char file_ext[] = ".csv";
    char str[MAX_FILE_NAME];

    #pragma omp parallel for
        for(i=0; i<iter_time; i++){
            sprintf(str, "%s%d%s",file_name, i, file_ext);
            fp = fopen(str, "r");
        }
    fclose(fp);
}


void get_dev(float* a, float* b, int size)
{
    int i;
    float sum = 0;

    #pragma omp parallel shared(size,a,b) private(i)
    {
    #pragma omp for reduction(+:sum)
    for(i=0; i < size; ++i)
        sum += a[i] * b[i];
    }
}

int main(int argc, char **argv){
    int opt;
    double start, end;
    double time_spent_grep;
    double time_spent_mv;
    double time_spent_reduction;
    double time_spent_noredution;
    int num_cars = 2500;
    int iter_time;
    char *file_name = NULL;

    while ((opt = getopt(argc, argv, "hf:c:t:")) !=  -1)
    {
        switch (opt)
        {
            case 'h':
                helpOutput();
                defaultConfig();
                break;
            case 'f':
                file_name = optarg;
                break;
            case 'c':
                num_cars = atoi(optarg);
                break;
            case 't':
                iter_time = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-f] [-c] [-t] [-h]",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    //omp_set_dynamic(0);
    //omp_set_num_threads(1000);

    printf("filename:");
    start = omp_get_wtime();
    grep_car(file_name, num_cars);
    end = omp_get_wtime();
    time_spent_grep = end - start;

    printf("time_spent_grep: %.16g\n", time_spent_grep);
 //   printf("time_spent_reduction:   %.16g\n", time_spent_reduction);

    return 0;
}
