#include "reservation.h"

static char * s_gets(char * st, int n);
static int count_empty_seats (struct Seat Plane[], int seats);
static void init_ptrs (struct Seat ** arr_ptr, struct Seat Plane[], int seats);

static struct Seat * arr_ptr[SEAT_COUNT];      //used for sorting the struct

void show_empty_seats_num (struct Seat Plane[], int seats)
{
    printf("\nCurrently there are %d empty seats.\n", count_empty_seats(Plane, seats));
}

//Shows the empty seats on the plane
void show_empty_seats (struct Seat Plane[], int seats)
{
    if (count_empty_seats(Plane, seats) == 0)
    {
        printf("\nWe're sorry, we have no seats availabe currently.\n");
    }

    else
    {
        printf("\nCurrently the available seats are:\n\n");

        int count = 0;
        for (int i = 0; i < seats; i++)
        {
            if (Plane[i].assigned == 0)
            {
                count++;
                printf("Seat #%d: %s\n", count, Plane[i].id);
            }   
        }   
    }
}

//Sorts seats alphabetically
void alpha_sort_seats (struct Seat Plane[], int seats)
{
    init_ptrs(arr_ptr, Plane, SEAT_COUNT);  //iniatilizes the pointers for the struct pointer array

    char temp[ID_LEN];

    //Sorting algorithm
    for (int top = 0; top < seats - 1; top++)
    {
        for (int seek = top + 1; seek < seats; seek++)
        {
            if (strcmp(arr_ptr[top]->id, arr_ptr[seek]->id) > 0)
            {
                strcpy(temp, arr_ptr[top]->id);
                strcpy(arr_ptr[top]->id, arr_ptr[seek]->id);
                strcpy(arr_ptr[seek]->id, temp);
            }
        }
    }
    
    printf("\nThe seats in alphabetical order:\n\n");
    for (int j = 0; j < seats; j++)
        printf("Seat #%d: %s | %s %s\n", j + 1, arr_ptr[j]->id, arr_ptr[j]->fname, arr_ptr[j]->lname);
}

//Assigns a client to a seat
void assign_seat (struct Seat Plane[], int seats)
{
    if (count_empty_seats(Plane, seats) == 0)
    {
        printf("\nWe're sorry, we have no seats available right now.\n");
    }

    else
    {
        int count = 0;

        printf("\nAvailable seats:\n");
        for (int i = 0; i < seats; i++)
        {
            if (Plane[i].assigned == 0)
            {
                count++;
                printf("Seat #%d: %s\n", count, Plane[i].id);
            }
        }
        
        int choice = 0;
        printf("\nPlease enter the number to choose the seat you want:\n");
        while (scanf("%d", &choice) != 1 || choice < 1 || choice > count)
        {
            clear_input();
            printf("Please enter a valid seat number:\n");
        }
        clear_input();

        count = 0;
        int index;
        for (int k = 0; k < seats; k++)
        {
            if (Plane[k].assigned == 0)
                count++;
                
            if (count == choice)
            {
                Plane[k].assigned = 1;
                index = k;
                break;
            }
        }

        printf("\nYou will be assigned seat %s\n", Plane[index].id);

        printf("\nPlease enter your first name:\n");
        s_gets(Plane[index].fname, NAME_LEN);
        while (Plane[index].fname[0] == '\0')
        {
            printf("Please enter a valid name:\n");
            s_gets(Plane[index].fname, NAME_LEN);
        }

        printf("\nPlease enter your last name:\n");
        s_gets(Plane[index].lname, NAME_LEN);
        while (Plane[index].lname[0] == '\0')
        {
            printf("Please enter a valid name:\n");
            s_gets(Plane[index].lname, NAME_LEN);
        }

        printf("\n%s %s you have been assigned seat %s\n", Plane[index].fname, Plane[index].lname, Plane[index].id);
    }
}

//Removes assigned status from a seat
void unassign_seat (struct Seat Plane[], int seats)
{
    if (count_empty_seats(Plane, seats) == seats)
    {
        printf("\nNo seats have been assigned yet.\n");
    }

    else
    {
        int count = 0;

        printf("\nAssigned seats:\n");
        for (int i = 0; i < seats; i++)
        {
            if (Plane[i].assigned == 1)
            {
                count++;
                printf("Seat #%d: %s | %s %s\n", count, Plane[i].id, Plane[i].fname, Plane[i].lname);
            }
        }

        int choice = 0;
        printf("\nPlease enter the number to choose the seat you want to unassign:\n");
        while (scanf(" %d", &choice) != 1 || choice < 1 || choice > count)
        {
            clear_input();
            printf("Please enter a valid seat number:\n");
        }
        clear_input();

        count = 0;
        int index;
        for (int k = 0; k < seats; k++)
        {
            if (Plane[k].assigned == 1)
                count++;
                
            if (count == choice)
            {
                Plane[k].assigned = 0;
                index = k;
                break;
            }
        }

        printf("\n%s %s has been unassigned from seat %s\n", Plane[index].fname, Plane[index].lname, Plane[index].id);
        Plane[index].fname[0] = '\0';
        Plane[index].lname[0] = '\0';

    }
}

// initializes the pointers into the struct pointers array
static void init_ptrs (struct Seat ** arr_ptr, struct Seat Plane[], int seats)
{
    for (int i = 0; i < seats; i++)
        arr_ptr[i] = &Plane[i];
}

//Returns the amount of empty seats in the flight
static int count_empty_seats (struct Seat Plane[], int seats)
{
    int count = 0;

    for (int i = 0; i < seats; i++)
    {
        if (Plane[i].assigned == 0)
            count++;
    }
    
    return count;
}

void menu(void)
{
    printf("Colossus Airlines\n");
    printf("a) Show number of empty seats\n");
    printf("b) Show list of empty seats\n");
    printf("c) Show alphabetical list of seats\n");
    printf("d) Assign a customer to a seat\n");
    printf("e) Remove a seat assignment\n");
    printf("f) Exit\n");
    printf("Option: ");
}

//Clears input buffer
void clear_input (void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        continue;
}

//Replaces f_gets. Does not store '\n'
static char * s_gets(char * st, int n)
{
    char * ret_val;
    char * find;

    ret_val = fgets(st, n, stdin);

    if (ret_val)
    {
        find = strchr(st, '\n'); // look for newline

        if (find)       // if the address is not NULL,
            *find = '\0';       // place a null character there

        else
            while (getchar() != '\n')
                continue;               // dispose of rest of line
    }
    
    return ret_val;
}