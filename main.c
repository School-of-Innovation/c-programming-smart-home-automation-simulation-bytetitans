#include <stdio.h>

// Function prototypes
void initializeSystem(int numRooms, int lights[], int temp[], int motion[], int locks[]);
void displayMenu();
void controlLights(int numRooms, int lights[]);
void readTemperature(int numRooms, int temp[]);
void detectMotion(int numRooms, int motion[], int *motionCounter, int locks[]);
void securitySystem(int numRooms, int locks[]);
void analyzeHouseStatus(int numRooms, int lights[], int temp[], int motion[], int locks[]);
void checkTemperatureAlert(int numRooms, int temp[]);
void checkEnergySavingMode(int numRooms, int lights[]);

int main() {
    int numRooms;
    printf("Enter number of rooms: ");
    scanf("%d", &numRooms);

    // Dynamic array allocation
    int lights[numRooms], temp[numRooms], motion[numRooms], locks[numRooms];

    // Motion counter for auto-lock feature
    int motionCounter = 0;

    // Initialize system
    initializeSystem(numRooms, lights, temp, motion, locks);

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                controlLights(numRooms, lights);
                checkEnergySavingMode(numRooms, lights);
                break;
            case 2:
                readTemperature(numRooms, temp);
                checkTemperatureAlert(numRooms, temp);
                break;
            case 3:
                detectMotion(numRooms, motion, &motionCounter, locks);
                break;
            case 4:
                securitySystem(numRooms, locks);
                break;
            case 5:
                analyzeHouseStatus(numRooms, lights, temp, motion, locks);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}

// Function to initialize the system with default values
void initializeSystem(int numRooms, int lights[], int temp[], int motion[], int locks[]) {
    for (int i = 0; i < numRooms; i++) {
        lights[i] = 0;   // All lights OFF
        temp[i] = 25;    // Default temperature
        motion[i] = 0;   // No motion detected
        locks[i] = 1;    // All doors locked
    }
    printf("\nSystem Initialized: Lights OFF, Doors Locked, No motion detected.\n");
}

// Function to display the menu
void displayMenu() {
    printf("\n===== Smart Home Menu =====\n");
    printf("1. Toggle Light\n");
    printf("2. Read Temperature\n");
    printf("3. Check Motion Sensor\n");
    printf("4. Lock/Unlock Security System\n");
    printf("5. House Status Summary\n");
    printf("6. Exit\n");
}

// Function to toggle lights ON/OFF
void controlLights(int numRooms, int lights[]) {
    int room;
    printf("Enter room number to toggle light (1-%d): ", numRooms);
    scanf("%d", &room);
    
    if (room >= 1 && room <= numRooms) {
        lights[room - 1] = !lights[room - 1];
        printf("Light in Room %d is now %s.\n", room, lights[room - 1] ? "ON" : "OFF");
    } else {
        printf("Invalid room number!\n");
    }
}

// Function to read and display temperature of a room
void readTemperature(int numRooms, int temp[]) {
    int room;
    printf("Enter room number to check temperature (1-%d): ", numRooms);
    scanf("%d", &room);

    if (room >= 1 && room <= numRooms) {
        printf("Room %d Temperature: %d°C\n", room, temp[room - 1]);
    } else {
        printf("Invalid room number!\n");
    }
}

// Function to detect motion and implement auto-lock
void detectMotion(int numRooms, int motion[], int *motionCounter, int locks[]) {
    int room;
    printf("Enter room number to check motion (1-%d): ", numRooms);
    scanf("%d", &room);

    if (room >= 1 && room <= numRooms) {
        motion[room - 1] = !motion[room - 1]; // Toggle motion detection
        printf("Motion in Room %d is now %s.\n", room, motion[room - 1] ? "Detected" : "Not Detected");

        if (motion[room - 1] == 1) {
            *motionCounter = 0; // Reset motion counter if motion is detected
        } else {
            (*motionCounter)++;
        }

        // Auto-lock feature: If no motion for 5 consecutive inputs, lock all doors
        if (*motionCounter >= 5) {
            for (int i = 0; i < numRooms; i++) {
                locks[i] = 1; // Lock all doors
            }
            printf("No motion detected for 5 inputs. Auto-lock activated!\n");
            *motionCounter = 0; // Reset counter
        }
    } else {
        printf("Invalid room number!\n");
    }
}

// Function to manually lock/unlock doors
void securitySystem(int numRooms, int locks[]) {
    int room;
    printf("Enter room number to toggle lock (1-%d): ", numRooms);
    scanf("%d", &room);

    if (room >= 1 && room <= numRooms) {
        locks[room - 1] = !locks[room - 1];
        printf("Room %d is now %s.\n", room, locks[room - 1] ? "Locked" : "Unlocked");
    } else {
        printf("Invalid room number!\n");
    }
}

// Function to analyze house status
void analyzeHouseStatus(int numRooms, int lights[], int temp[], int motion[], int locks[]) {
    printf("\nHouse Status:\n");
    for (int i = 0; i < numRooms; i++) {
        printf("Room %d: Light %s, Temp %d°C, %s, %s\n", 
               i + 1, 
               lights[i] ? "ON" : "OFF", 
               temp[i], 
               motion[i] ? "Motion Detected" : "No Motion",
               locks[i] ? "Locked" : "Unlocked");
    }
}

// Function to check temperature alerts
void checkTemperatureAlert(int numRooms, int temp[]) {
    for (int i = 0; i < numRooms; i++) {
        if (temp[i] > 30) {
            printf("⚠️ Warning: Room %d temperature is above 30°C! (Current: %d°C)\n", i + 1, temp[i]);
        }
    }
}

// Function to check energy-saving mode
void checkEnergySavingMode(int numRooms, int lights[]) {
    int allLightsOn = 1; // Assume all lights are ON
    for (int i = 0; i < numRooms; i++) {
        if (lights[i] == 0) {
            allLightsOn = 0; // Found a light that is OFF
            break;
        }
    }
    if (allLightsOn) {
        printf("🔋 Energy-Saving Mode: All lights are ON. Consider turning some OFF to save energy.\n");
    }
}
