#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define MAX_FILE_NAME 1000
#define MAX_LINE_SIZE 300
#define CARS 2500
#define SIMULATION_TIME 1800
#define FACTOR 36/1000

char results[CARS][MAX_LINE_SIZE];

void helpOutput(void)
{
    char header[] = "smart traffic analyzer\nUSAGE: sta [OPTIONS]\nOPTIONS:\n";
    char opt_f[] = "-f FILE    read csv file\n";
    char opt_c[] = "-c CARS    number of cars\n";
    char opt_t[] = "-t ITER    number of iterations or simulation time\n";
    char opt_h[] = "-h         Display the help information\n";
    char str[MAX_FILE_NAME];
    sprintf(str, "%s%d%s",
            header,
            opt_f,
            opt_c,
            opt_t,
            opt_h);

}

void defaultConfig(void)
{
    char header[] = "Default configuration:\n";
    char file_name[] = "    file name:  simulation_2500_1800.csv\n";
    char num_cars[] = "    number of cars:                 2500\n";
    char num_iter[] = "    number of iterations:           1800s\n";

    char str[MAX_FILE_NAME];
    sprintf(str, "%s%d%s",
            header,
            file_name,
            num_cars,
            num_iter);
    exit(EXIT_FAILURE);
}


void grep_car_serial(char *file_name, int num_cars){
    int i;
    char grep_cmd[MAX_FILE_NAME];
    printf("starting data segregation serial...\n");
    for(i=0; i < num_cars; ++i){
        sprintf(grep_cmd, "grep -E \"^%d,\" %s > car_%d.csv", i, file_name, i);
        system(grep_cmd);
    }
}

void grep_car_parallel(char *file_name, int num_cars){
    int i;
    char grep_cmd[MAX_FILE_NAME];

    double start_time = omp_get_wtime();
    printf("starting data segregation parallel...\n");
    #pragma omp parallel for private(i,grep_cmd) shared(file_name)
    for(i=0; i < num_cars; ++i){
        sprintf(grep_cmd, "grep -E \"^%d,\" %s > car_%d.csv", i, file_name, i);
        system(grep_cmd);
    }
    printf("data segregation complete total time: %f\n", omp_get_wtime()-start_time);
}


void do_analysis(){
    FILE *csv = NULL;
    char file_name[50];
    int i, j;

    char row[MAX_LINE_SIZE];
    int id;
    unsigned int lane;
    float position;
    float speed;
    float acceleration;
    unsigned int top_speed;
    unsigned int goal_distance;

    double result = 0;
    double square_result = 0;
    double start_time = omp_get_wtime();

    printf("starting data analysis...\n");
#pragma omp parallel for private(i,row,id,lane,position,speed,acceleration,top_speed,goal_distance,csv,file_name,j) reduction(+:result,square_result) shared(results)
    for(i=0; i<2500; i++){
        sprintf(file_name, "car_%d.csv", i);
        csv = fopen(file_name, "r");
        if(csv != NULL){
            j = 0;
            while(fgets(row, sizeof(row), csv) != NULL){
                sscanf(row, "%d, %d, %f, %f, %f, %d, %d", &id, &lane, &position, &speed, &acceleration, &top_speed, &goal_distance);
                result += speed;
                square_result += speed*speed;
                if (speed != 0.0)
                    j++;
            }
        }
        result = (result/j);
        square_result = square_result/j - result*result;
        square_result = pow(square_result, 0.5);
//        printf("id %d position %f average speed %f stdev %f top speed %d\n", id, position/100000, result*FACTOR, square_result*FACTOR, top_speed);
        sprintf(results[i], "%d, %f, %f, %f, %d", id, position/100000, result*FACTOR, square_result*FACTOR, top_speed*FACTOR);
        fclose(csv);
        result = 0;
        square_result = 0;
    }
    printf("data analysis complete total time: %f\n", omp_get_wtime()-start_time);

    FILE *output = NULL;
    output = fopen("analysis_output.csv", "w");
    fprintf(output, "id, position, average speed, standard deviation, top speed\n");
    for(i=0; i<2500; i++){
        fprintf(output, "%s\n", results[i]);
    }
    fclose(output);
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
    grep_car_serial(file_name, num_cars);
    end = omp_get_wtime();
    time_spent_grep = end - start;
    printf("time_spent_grep: %.16g\n", time_spent_grep);

    grep_car_parallel(file_name, num_cars);

    do_analysis();

    return 0;
}
