#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <apple2.h>
#include <peekpoke.h>

#include "globals.h"
#include "menu.h"
#include "apple2idiot.h"

unsigned char i = 0;
char pause_char;
char city[33];
char country_code[3];
char temperature[7];
char humidity[7];
char wind_speed[7];
char wind_direction[5];
char weather1[250];
char weather2[250];
unsigned int address_offset = 0;

void main(void)
{
    unsigned char key;
    clrscr();

    while (key != ASCII_5) {    // Last menu item should be Quit
        drawMenuBar();
        gotoxy(0,2);
        printf("Country: %s    City:%s", country_code, city);
        gotoxy(0,SIZE_Y-1);
        printf("Menu Selection:");
        cursor(1);
        key = toupper(cgetc());
        gotoxy(0,SIZE_Y-3);
        //printf("cgetc() -> \"%c\"", key);

        switch((int)key) {
        case ASCII_0:
            break;
        case ASCII_5:
            break;
        case ASCII_1:
            clrscr();
            drawMenuBar();
            gotoxy(0,SIZE_Y-1);
            printf("Enter Country Code:");
            fgets(country_code, sizeof country_code, stdin);
            strncpy(country_code, country_code, strlen(country_code));
            //country_code[strcspn(country_code, "\n")] = 0;
            write_string_to_ram(RAM_DATA_START_ADDRESS, country_code);
            write_byte(APPLE_COMMAND_ADDRESS, COMMAND_SET_COUNTRY);
            //printf("C:[%s]", country_code);
            //pause_char = cgetc();
            break;
        case ASCII_2:
            clrscr();
            drawMenuBar();
            gotoxy(0,SIZE_Y-1);
            printf("Enter City: ");
            fgets(city, sizeof city, stdin);
            city[strcspn(city, "\n")] = 0;
            write_string_to_ram(RAM_DATA_START_ADDRESS, city);
            write_byte(APPLE_COMMAND_ADDRESS, COMMAND_SET_CITY);
            //printf("C:[%s]", city);
            //pause_char = cgetc();
            break;
        case ASCII_3:
            clrscr();
            drawMenuBar();
            write_byte(APPLE_COMMAND_ADDRESS, COMMAND_FETCH_WEATHER);
            break;
        case ASCII_4:
            clrscr();
            drawMenuBar();
            address_offset = 0;
            read_string_from_ram(RAM_DATA_START_ADDRESS + address_offset, temperature, sizeof temperature-1);
            address_offset += strlen(temperature) + 1;
            read_string_from_ram(RAM_DATA_START_ADDRESS + address_offset, humidity, sizeof humidity-1);
            address_offset += strlen(humidity) + 1;
            read_string_from_ram(RAM_DATA_START_ADDRESS + address_offset, wind_speed, sizeof wind_speed-1);
            address_offset += strlen(wind_speed) + 1;
            read_string_from_ram(RAM_DATA_START_ADDRESS + address_offset, wind_direction, sizeof wind_direction-1);
            address_offset += strlen(wind_direction) + 1;
            read_string_from_ram(RAM_DATA_START_ADDRESS + address_offset, weather1, sizeof weather1-1);
            address_offset += strlen(weather1) + 1;
            read_string_from_ram(RAM_DATA_START_ADDRESS + address_offset, weather2, sizeof weather2-1);
            gotoxy(0,SIZE_Y-11);
            printf("%s (%s)\n", city, country_code);
            printf("-------------------------------------\n");
            printf("Temp:       %s K\n", temperature);
            printf("Humidity:   %s%%\n", humidity);
            printf("Wind Speed: %s m/s\n", wind_speed);
            printf("Wind Dir:   %s \n", wind_direction);
            printf("Summary:    %s, %s \n", weather1, weather2);
            printf("-------------------------------------\n");
            break;
        default:
            break;
        }

    }
}
