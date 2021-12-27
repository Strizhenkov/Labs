#include <stdio.h>

const int start_year = 1995;
const int start_month = 299;
const int start_day = 1;
const int start_hour = 0;
const int start_minute = 0;
const int start_second = 0;

const int finish_year = 1995;
const int finish_mouth = 299;
const int finish_day = 31;
const int finish_hour = 23;
const int finish_minute = 59;
const int finish_second = 59;

const int period = 10;

int check_year(int year) {
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        return 1;
    else
        return 0;
}

int get_months(int key, int feb_day) {
    switch(key) {
        case 281 : return 0;                                                   //Jan
        case 269 : return 31;                                                  //Feb
        case 288 : return 31+28+feb_day;                                       //Mar
        case 291 : return 31+28+31+feb_day;                                    //Apr
        case 295 : return 31+28+31+30+feb_day;                                 //May
        case 301 : return 31+28+31+30+31+feb_day;                              //Jun
        case 299 : return 31+28+31+30+31+30+feb_day;                           //Jul
        case 285 : return 31+28+31+30+31+30+31+feb_day;                        //Aug
        case 296 : return 31+28+31+30+31+30+31+31+feb_day;                     //Sep
        case 294 : return 31+28+31+30+31+30+31+31+30+feb_day;                  //Oct
        case 307 : return 31+28+31+30+31+30+31+31+30+31+feb_day;               //Nov
        case 268 : return 31+28+31+30+31+30+31+31+30+31+30+feb_day;            //Dec
    }
}

int main() {
    int count_days = 0;
    for (int j = start_year; j <= finish_year - 1; j++)
        count_days = count_days + 365 + check_year(j);
    count_days = count_days + get_months(finish_mouth, check_year(finish_year)) - get_months(start_month, check_year(start_year)) + finish_day;
    long int finish_time = ((count_days * 24 + finish_hour) * 60 + finish_minute) * 60 + finish_second;

    int array[100000000];
    FILE *file;
    file = fopen("logs.txt", "r");
    char str[256];
    int count = 0;
    while (fgets(str, 256, file) != NULL) {
        int key = 0;
        int i = -1;
        while (key != 2) {
            i++;
            if (str[i] == '"')
                key++;
        }
        if (str[i+2] == '5') {
            count++;
            printf("%s", str);
        }
        i = 0;
        while (str[i] != '[')
            i++;
        int current_year = (((str[i+8] - 48) * 10 + str[i+9] - 48) * 10 + str[i+10] - 48) * 10 + str[i + 11] - 48;
        int before_days = 0;
        for (int j = start_year; j <= current_year - 1; j++)
            before_days = before_days + 365 + check_year(j);
        int code_month = str[i+4] + str[i+5] + str[i+6];
        int days = (str[i+1] - 48) * 10 + str[i+2] - 48 - start_day + (get_months(code_month, check_year(current_year)) - get_months(start_month, check_year(start_year))) + before_days;
        int hours = (str[i+13] - 48) * 10 + str[i+14] - 48 - start_hour;
        int minutes = (str[i+16] - 48) * 10 + str[i+17] - 48 - start_minute;
        int seconds = (str[i+19] - 48) * 10 + str[i+20] - 48 - start_second;
        long int time = ((days * 24 + hours) * 60 + minutes) * 60 + seconds;
        if (time > 0)
            array[time]++;
    }

    int max = 0;
    for (int i = 0; i <= finish_time - period + 1; i++) {
        int sum = 0;
        for (int j = i; j <= i + period - 1; j++)
            sum = sum + array[j];
        if (sum > max)
            max = sum;
    }
    printf("%d\n", count);
    printf("%d", max);
    return 0;
}