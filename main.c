#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macros
#define MAX_BUSES 5
#define MAX_SEATS 10
#define NAME_LENGTH 30
#define GENDER_LENGTH 10
#define FOOD_LENGTH 50
#define LOCATION_LENGTH 50
#define USERNAME_LENGTH 20
#define PASSWORD_LENGTH 20
#define PAYMENT_METHOD_LENGTH 20

// Enum to represent seat status
enum SeatStatus {
    AVAILABLE,
    BOOKED
};

// Structure to represent a reservation
struct Reservation {
    char passengerName[NAME_LENGTH];
    char gender[GENDER_LENGTH];
    int seatNumber;
    int busNumber;
    char selectedFood[FOOD_LENGTH];
    char timeOfDay[20]; // Added field for time of day
    char paymentMethod[PAYMENT_METHOD_LENGTH];
};

// Structure to represent bus information
struct BusInfo {
    char startLocation[LOCATION_LENGTH];
    char endLocation[LOCATION_LENGTH];
    enum SeatStatus seatStatus[MAX_SEATS];
};

// Structure to represent user information
struct UserInfo {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
};

// Function prototypes
void displayMenu();
void initializeBuses(struct BusInfo busInfo[MAX_BUSES]);
void showAvailableSeats(struct BusInfo busInfo[MAX_BUSES]);
void showAvailableFoods();
void signUp(struct UserInfo* userInfo);
int login(struct UserInfo* userInfo);
void makeReservation(struct BusInfo busInfo[MAX_BUSES], struct Reservation** reservations, int* reservationCount);
void displayReservations(struct Reservation* reservations, int reservationCount, struct BusInfo busInfo[MAX_BUSES]);

int main() {
    // Get user sign-up information
    struct UserInfo userInfo;
    signUp(&userInfo);

    // Arrays to represent reservations
    struct Reservation* reservations = NULL;
    int reservationCount = 0;

    // Bus information
    struct BusInfo busInfo[MAX_BUSES] = {
        {"Karur", "Trichy"},
        {"Karur", "Chennai"},
        {"Karur", "Coimbatore"},
        {"Karur", "Vadapalani"},
        {"Karur", "Goa"}
    };

    // Initialize buses
    initializeBuses(busInfo);

    // Login
    if (!login(&userInfo)) {
        printf("Login failed. Exiting the program.\n");
        return 1;
    }

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showAvailableSeats(busInfo);
                break;
            case 2:
                makeReservation(busInfo, &reservations, &reservationCount);
                break;
            case 3:
                displayReservations(reservations, reservationCount, busInfo);
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    // Free dynamically allocated memory
    free(reservations);

    return 0;
}

void displayMenu() {
    printf("\n----- Bus Reservation System Menu -----\n");
    printf("1. Show available seats\n");
    printf("2. Make a reservation\n");
    printf("3. Display reservations\n");
    printf("4. Exit\n");
}

void initializeBuses(struct BusInfo busInfo[MAX_BUSES]) {
    // Initialize seat status for each bus
    for (int i = 0; i < MAX_BUSES; ++i) {
        for (int j = 0; j < MAX_SEATS; ++j) {
            busInfo[i].seatStatus[j] = AVAILABLE;
        }
    }
}

void showAvailableSeats(struct BusInfo busInfo[MAX_BUSES]) {
    printf("\n----- Available Seats -----\n");
    for (int i = 0; i < MAX_BUSES; ++i) {
        printf("Bus %d (%s to %s):\n", i + 1, busInfo[i].startLocation, busInfo[i].endLocation);
        for (int j = 0; j < MAX_SEATS; ++j) {
            printf("%d. %s\t", j + 1, busInfo[i].seatStatus[j] == AVAILABLE ? "Available" : "Booked");
        }
        printf("\n");
    }
    // Show available foods
    showAvailableFoods();
}

void showAvailableFoods() {
    printf("\n----- Available Foods -----\n");
    printf("Morning:\n");
    printf("1. Sandwich\n");
    printf("2. Cereal\n");

    printf("\nAfternoon:\n");
    printf("3. Pizza\n");
    printf("4. Salad\n");

    printf("\nNight:\n");
    printf("5. Spaghetti\n");
    printf("6. Soup\n");
    // Add more food items as needed
}

void signUp(struct UserInfo* userInfo) {
    printf("\n----- Sign Up -----\n");
    printf("Enter username: ");
    scanf("%s", userInfo->username);

    printf("Enter password: ");
    scanf("%s", userInfo->password);
}

int login(struct UserInfo* userInfo) {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];

    printf("\n----- Login -----\n");
    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    // Check if entered username and password match the sign-up information
    if (strcmp(username, userInfo->username) == 0 && strcmp(password, userInfo->password) == 0) {
        printf("Login successful.\n");
        return 1;
    } else {
        printf("Login failed.\n");
        return 0;
    }
}

void makeReservation(struct BusInfo busInfo[MAX_BUSES], struct Reservation** reservations, int* reservationCount) {
    // Allocate memory for the reservation
    *reservations = (struct Reservation*)realloc(*reservations, (*reservationCount + 1) * sizeof(struct Reservation));

    if (*reservations == NULL) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // Get user input for reservation
    printf("\nEnter gender (Male/Female/Other): ");
    scanf("%s", (*reservations)[*reservationCount].gender); // Added line for gender
    printf("Enter passenger name: ");
    scanf("%s", (*reservations)[*reservationCount].passengerName);

    // Display available buses
    printf("\nAvailable Buses:\n");
    for (int i = 0; i < MAX_BUSES; ++i) {
        printf("Bus %d (%s to %s):\n", i + 1, busInfo[i].startLocation, busInfo[i].endLocation);
        for (int j = 0; j < MAX_SEATS; ++j) {
            printf("%d. %s\t", j + 1, busInfo[i].seatStatus[j] == AVAILABLE ? "Available" : "Booked");
        }
        printf("\n");
    }

    // Get user input for bus number
    printf("Enter bus number: ");
    scanf("%d", &(*reservations)[*reservationCount].busNumber);

    // Check if the selected bus number is valid
    if ((*reservations)[*reservationCount].busNumber < 1 || (*reservations)[*reservationCount].busNumber > MAX_BUSES) {
        printf("Invalid bus number. Please try again.\n");
        return;
    }

    // Display available seats for the selected bus
    printf("\nAvailable Seats for Bus %d (%s to %s): ", (*reservations)[*reservationCount].busNumber, busInfo[(*reservations)[*reservationCount].busNumber - 1].startLocation, busInfo[(*reservations)[*reservationCount].busNumber - 1].endLocation);
    for (int j = 0; j < MAX_SEATS; ++j) {
        printf("%d. %s\t", j + 1, busInfo[(*reservations)[*reservationCount].busNumber - 1].seatStatus[j] == AVAILABLE ? "Available" : "Booked");
    }
    printf("\n");

    // Get user input for seat number
    printf("Enter seat number: ");
    scanf("%d", &(*reservations)[*reservationCount].seatNumber);

    // Check if the selected seat number is valid
    if ((*reservations)[*reservationCount].seatNumber < 1 || (*reservations)[*reservationCount].seatNumber > MAX_SEATS || busInfo[(*reservations)[*reservationCount].busNumber - 1].seatStatus[(*reservations)[*reservationCount].seatNumber - 1] == BOOKED) {
        printf("Invalid seat number or seat already reserved. Please try again.\n");
        return;
    }

    // Reserve the seat
    busInfo[(*reservations)[*reservationCount].busNumber - 1].seatStatus[(*reservations)[*reservationCount].seatNumber - 1] = BOOKED;

    // Get user input for selected food
    printf("Select food (enter the corresponding number): ");
    int foodChoice;
    scanf("%d", &foodChoice);
    switch (foodChoice) {
        case 1:
            strcpy((*reservations)[*reservationCount].selectedFood, "Sandwich");
            strcpy((*reservations)[*reservationCount].timeOfDay, "Morning");
            break;
        case 2:
            strcpy((*reservations)[*reservationCount].selectedFood, "Cereal");
            strcpy((*reservations)[*reservationCount].timeOfDay, "Morning");
            break;
        case 3:
            strcpy((*reservations)[*reservationCount].selectedFood, "Pizza");
            strcpy((*reservations)[*reservationCount].timeOfDay, "Afternoon");
            break;
        case 4:
            strcpy((*reservations)[*reservationCount].selectedFood, "Salad");
            strcpy((*reservations)[*reservationCount].timeOfDay, "Afternoon");
            break;
        case 5:
            strcpy((*reservations)[*reservationCount].selectedFood, "Spaghetti");
            strcpy((*reservations)[*reservationCount].timeOfDay, "Night");
            break;
        case 6:
            strcpy((*reservations)[*reservationCount].selectedFood, "Soup");
            strcpy((*reservations)[*reservationCount].timeOfDay, "Night");
            break;
        default:
            strcpy((*reservations)[*reservationCount].selectedFood, "Unknown");
            strcpy((*reservations)[*reservationCount].timeOfDay, "Unknown");
            break;
    }

    // Get user input for payment method
    printf("\nSelect payment method:\n");
    printf("1. Online\n");
    printf("2. Offline\n");
    printf("Enter your choice: ");
    int paymentChoice;
    scanf("%d", &paymentChoice);

    if (paymentChoice == 1) {
        // For online payments, display additional options
        printf("Select online payment method (1. Paytm / 2. GPay / 3. PhonePe): ");
        int onlinePaymentChoice;
        scanf("%d", &onlinePaymentChoice);

        switch (onlinePaymentChoice) {
            case 1:
                printf("Payment successful via Paytm.\n");
                break;
            case 2:
                printf("Payment successful via GPay.\n");
                break;
            case 3:
                printf("Payment successful via PhonePe.\n");
                break;
            default:
                printf("Invalid online payment method. Payment failed.\n");
                break;
        }
    } else {
        printf("Payment successful.\n");
    }

    printf("Reservation successful.\n");

    (*reservationCount)++;
}

void displayReservations(struct Reservation* reservations, int reservationCount, struct BusInfo busInfo[MAX_BUSES]) {
    printf("\n----- Reservations -----\n");
    printf("Passenger Name\tGender\tBus Number\tSeat Number\tSelected Food\tTime of Day\tPayment Method\n");

    for (int i = 0; i < reservationCount; ++i) {
        printf("%s\t\t%s\t\t%d\t\t%d\t\t%s\t\t%s\t\t%s\n",
               reservations[i].passengerName,
               reservations[i].gender,
               reservations[i].busNumber,
               reservations[i].seatNumber,
               reservations[i].selectedFood,
               reservations[i].timeOfDay,
               reservations[i].paymentMethod);
    }
}

