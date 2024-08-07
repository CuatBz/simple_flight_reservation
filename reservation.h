#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_LEN 4
#define NAME_LEN 20
#define SEAT_COUNT 12

struct Seat {
    char id[ID_LEN];
    _Bool assigned;
    char fname [NAME_LEN];
    char lname [NAME_LEN];
};

void menu(void);
void clear_input (void);
void show_empty_seats_num (struct Seat Plane[], int seats);
void show_empty_seats (struct Seat Plane[], int seats);
void alpha_sort_seats (struct Seat Plane[], int seats);
void assign_seat (struct Seat Plane[], int seats);
void unassign_seat (struct Seat Plane[], int seats);