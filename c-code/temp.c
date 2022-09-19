/******************************************************************************
  * @file           : temp.c
  * @brief          : temperature data collection
  ******************************************************************************
  * @attention
  *
  * Copyright (c) None
  * Use as you wish.
  *
  * To be tested: Make sure no double line break is added to newly created
  * temperature csv files.
  ******************************************************************************
*/

#include <stdio.h>
#include <time.h>

int read_config(FILE* fd){
	int t;
    fscanf(fd, "%d", &t);
	return t;
}

void read_temp(FILE* fd, double T){
    fd = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    fscanf(fd, "%lf", &T);
    T /= 1000;
    fclose(fd);
}

void sleep_ms(int milliseconds){
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

int main(){
    time_t T1 = time(NULL);
    struct tm tm = *localtime(&T1);

    int nanosleep(const struct timespec * req, struct timespec * rem);

    FILE *temperature;
    FILE *csvfile;
    FILE *config;
    double T;

    config = fopen("/var/www/data/config.txt", "r+");
    int lastday = read_config(config);

    if(tm.tm_hour == 00 && tm.tm_min == 00){

        switch(lastday){
            case 1:
            remove("/var/www/data/2_Temperatures.csv");
            csvfile = fopen("/var/www/data/2_Temperatures.csv", "w");
            fprintf(csvfile, "%02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
            lastday = 2;
            fseek(config, 0, SEEK_SET);
            fprintf(config, "2");
            break;

            case 2:
            remove("/var/www/data/3_Temperatures.csv");
            csvfile = fopen("/var/www/data/3_Temperatures.csv", "w");
            fprintf(csvfile, "%02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
            lastday = 3;
            fseek(config, 0, SEEK_SET);
            fprintf(config, "3");
            break;

            case 3:
            remove("/var/www/data/0_Temperatures.csv");
            csvfile = fopen("/var/www/data/0_Temperatures.csv", "w");
            fprintf(csvfile, "%02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
            lastday = 1;
            fseek(config, 0, SEEK_SET);
            fprintf(config, "1");
            break;
        }
        fclose(config);
    }

    switch(lastday){
        case 1:
        csvfile = fopen("/var/www/data/0_Temperatures.csv", "a");
        fprintf(csvfile, "%02d:%02d, %2.1f\n", tm.tm_hour, tm.tm_min, T);
        fclose(csvfile);
        break;

        case 2:
        csvfile = fopen("/var/www/data/2_Temperatures.csv", "a");
        fprintf(csvfile, "%02d:%02d, %2.1f\n", tm.tm_hour, tm.tm_min, T);
        fclose(csvfile);
        break;

        case 3:
        csvfile = fopen("/var/www/data/3_Temperatures.csv", "a");
        fprintf(csvfile, "%02d:%02d, %2.1f\n", tm.tm_hour, tm.tm_min, T);
        fclose(csvfile);
        break;
    }

    return 0;
}