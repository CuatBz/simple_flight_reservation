#include <ctype.h>
#include <sys/stat.h>               //helps me check if file is created for the first time
#include <sys/types.h>              //helps store file size with off_t
#include "reservation.h"

//Function to find out file size
off_t fsize(const char *filename) {
    struct stat st; 

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1; 
}


//A reservation program for plane seats
int main (void)
{
    FILE * save_file;                           //save file pointer
    int size = sizeof(struct Seat);             //size of a Seat struct
    const char save_name[] = "flight.bin";      //save file name

    //Initialize struct array in case file does not exist yet
    struct Seat Plane [SEAT_COUNT] = {
        {"1LA", 0, "", ""},
        {"1LW", 0, "", ""},
        {"1RA", 0, "", ""},
        {"1RW", 0, "", ""},
        {"2LA", 0, "", ""},
        {"2LW", 0, "", ""},
        {"2RA", 0, "", ""},
        {"2RW", 0, "", ""},
        {"3LA", 0, "", ""},
        {"3LW", 0, "", ""},
        {"3RA", 0, "", ""},
        {"3RW", 0, "", ""}
    };

    //Load data from save file
    if ((save_file = fopen(save_name, "a+b")) == NULL)
    {
        printf("Can't open %s. Data cannot be read from file.\n", save_name);
    }

    else
    {
        off_t is_new_file = fsize(save_name);       //will affect behaviour if file is 0

        if (is_new_file > 0)
        {
            rewind(save_file);

            //Load saved file contents
            if (fread(&Plane, size, 12, save_file) == 12)
                printf("Data successfully loaded.\n\n");
        }

        fclose(save_file);
    }

    char opt;

    menu();
    scanf(" %c", &opt);
    opt = tolower(opt);
    while (opt != 'f')
    {
        switch (opt)
        {
        case 'a':
            show_empty_seats_num(Plane, SEAT_COUNT);            //shows number of empty seats
            break;
        
        case 'b':
            show_empty_seats(Plane, SEAT_COUNT);                //shows id of empty seats
            break;

        case 'c':
            alpha_sort_seats(Plane, SEAT_COUNT);                //sorts seats alphabetically
            break;

        case 'd':
            assign_seat(Plane, SEAT_COUNT);                     //assigns a person to a seat
            break;

        case 'e':
            unassign_seat(Plane, SEAT_COUNT);                   //unassigns a person from a seat
            break;

        case 'f':
            printf("\nThank you for using our program. Have a good day!\n");
            break;

        default:
            printf("\nInvalid option. Please try again.\n");
            break;
        }

        printf("\n");
        menu();
        scanf(" %c", &opt);
        opt = tolower(opt);
    }

    FILE * temp_file;
    const char temp_name[] = "temp.bin";

    //Write data to temporary file
    if ((temp_file = fopen(temp_name, "wb")) == NULL)
    {
        printf("Can't open %s. Data cannot be read from file.\n", temp_name);
    }

    else
    {
        if (fwrite(&Plane, size, 12, temp_file) == 12)
            printf("\nData successfully saved.\n");

        else
            printf("\nData could not be saved.\n");

        fclose(temp_file);
    }

    //Replace save file with temp file
    remove(save_name);
    rename(temp_name, save_name);

    return 0;
}