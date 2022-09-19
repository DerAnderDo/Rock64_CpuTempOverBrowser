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
#include <stdlib.h>
#include <time.h>

int read_config(FILE* filedescriptor){
	char* t;
	fseek(filedescriptor, 0, SEEK_SET);
	fread(&t, 1, 1, filedescriptor);
    //printf("config.txt: %c", t);
    int var = atoi(&t);
    //printf("config.txt: %d", var);
	return var;
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
    FILE *fpt;
    FILE *config;
    double T;

    temperature = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if(temperature == NULL)
        {
        printf("Can't measure the cpu temperature");
        }
        else
        {
        fscanf(temperature, "%lf", &T);
        T /= 1000;
        fclose(temperature);
    }

    config = fopen("/var/www/data/config.txt", "r+");
    int lastday = read_config(config);

    if(tm.tm_hour == 00 && tm.tm_min == 00){

        switch(lastday){
            case 1:
            remove("/var/www/data/2_Temperatures.csv");
            fpt = fopen("/var/www/data/2_Temperatures.csv", "w");
            fprintf(fpt, "%02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
            lastday = 2;
            fseek(config, 0, SEEK_SET);
            fprintf(config, "2");
            break;

            case 2:
            remove("/var/www/data/3_Temperatures.csv");
            fpt = fopen("/var/www/data/3_Temperatures.csv", "w");
            fprintf(fpt, "%02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
            lastday = 3;
            fseek(config, 0, SEEK_SET);
            fprintf(config, "3");
            break;

            case 3:
            remove("/var/www/data/0_Temperatures.csv");
            fpt = fopen("/var/www/data/0_Temperatures.csv", "w");
            fprintf(fpt, "%02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
            lastday = 1;
            fseek(config, 0, SEEK_SET);
            fprintf(config, "1");
            break;
        }
        fclose(config);
    }

    switch(lastday){
        case 1:
        fpt = fopen("/var/www/data/0_Temperatures.csv", "a");
        fprintf(fpt, "%02d:%02d, %2.1f\n", tm.tm_hour, tm.tm_min, T);
        fclose(fpt);
        break;

        case 2:
        fpt = fopen("/var/www/data/2_Temperatures.csv", "a");
        fprintf(fpt, "%02d:%02d, %2.1f\n", tm.tm_hour, tm.tm_min, T);
        fclose(fpt);
        break;

        case 3:
        fpt = fopen("/var/www/data/3_Temperatures.csv", "a");
        fprintf(fpt, "%02d:%02d, %2.1f\n", tm.tm_hour, tm.tm_min, T);
        fclose(fpt);
        break;
    }

    return 0;
}