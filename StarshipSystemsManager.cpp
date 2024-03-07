#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
#include <Windows.h>

using std::cout;
using std::string;
using std::to_string;
using namespace std::literals::chrono_literals;


// Define color escape codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

struct Starship {
    // Default target frame time (60 fps) 16.67ms per frame
    std::chrono::nanoseconds targetFrameTime{ 16667000 };

    // external power
    bool externalPower{ false };
    float externalPowerRate{ 5 };

    // Start Capacitors
    bool startCapacitors{ false };
    float startCapacitorsCharge{ 0 };
    float startCapacitorsMaxCapacity{ 10000 };

    // Helium Tank
    float heliumTankCollectionRate{ 1 };
    float heliumTank{ 0 };
    float heliumTankMaxCapacity{ 100000 };
    bool heliumTankChiller { false };

    // Helium3 Tank
    float helium3TankCollectionRate{ 1 };
    float helium3Tank{ 0 };
    float helium3TankMaxCapacity{ 100000 };
    bool helium3TankChiller{ false };

    // Deuterium Tank 1
    float deuteriumTank1CollectionRate{ 1 };
    float deuteriumTank1{ 0 };
    float deuteriumTank1MaxCapacity{ 100000 };
    bool deuteriumTank1Chiller{ false };

    // Deuterium Tank 2
    float deuteriumTank2CollectionRate{ 1 };
    float deuteriumTank2{ 0 };
    float deuteriumTank2MaxCapacity{ 100000 };
    bool deuteriumTank2Chiller{ false };

    // Fuel Collection System
    bool fuelCollecters{ false };
    float fuelTotal{ heliumTank + helium3Tank + deuteriumTank1 + deuteriumTank2 };
    float fuelTotalCapacity{ heliumTankMaxCapacity + helium3TankMaxCapacity + deuteriumTank1MaxCapacity + deuteriumTank2MaxCapacity };

    // Fusion Reactor
    bool magneticCoils{ false };
    bool reactorState{ false };
    bool reactorBusSupply{ false };

    // Batteries
    // Life Support
    // Shields
    // FTL Drive
    // Weapons
};

void updateSimulation(Starship& starship) {
    // Example: Charge capacitors if external power is online & less than max capacity
    if (starship.externalPower && starship.startCapacitorsCharge < starship.startCapacitorsMaxCapacity) {
        starship.startCapacitorsCharge += starship.externalPowerRate;
    }
    
    // Add more systems here
}

string progressBar(float current , float max) {
    float progress = current / max;
    // configurable bar width
    int barWidth = 30;
    string bar;
    bar += "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) bar += "=";
        else if (i == pos) bar += ">";
        else bar += " ";
    }
    bar += "] " + to_string(int(progress * 100.0)) + string("% ");
    return bar;
}

void menu(const Starship& starship) {
    string output;
    output += BLUE + string("*** STARSHIP SYSTEMS MANAGER ***\n\n");

    // External Power System
    if (starship.externalPower) {
        output += GREEN + string("[1] External Power [ONLINE] ") + std::to_string(static_cast<int>(starship.externalPowerRate * 60)) + "/sec\n";
    }
    else {
        output += RED + string("[1] External Power [OFFLINE] 0/sec \n");
    }

    // Start Capacitors System
    string capProgBar = progressBar(starship.startCapacitorsCharge, starship.startCapacitorsMaxCapacity);
    if (starship.startCapacitors) {
        output += GREEN + string("[2] Start Capacitors [ONLINE] ") + CYAN + capProgBar + "Charge: " + std::to_string(static_cast<int>(starship.startCapacitorsCharge)) +
            "/" + std::to_string(static_cast<int>(starship.startCapacitorsMaxCapacity)) + " \n";
    }
    else {
        output += RED + string("[2] Start Capacitors [OFFLINE] ") + CYAN + capProgBar + "Charge: " + std::to_string(static_cast<int>(starship.startCapacitorsCharge)) +
            "/" + std::to_string(static_cast<int>(starship.startCapacitorsMaxCapacity)) + " \n";
    }

    // Gas Collection System

    string fuelSummaryProgBar = progressBar(starship.fuelTotal, starship.fuelTotalCapacity);
    string heliumProgBar = progressBar(starship.heliumTank, starship.heliumTankMaxCapacity);
    string helium3ProgBar = progressBar(starship.helium3Tank, starship.helium3TankMaxCapacity);
    string deuteriumTank1ProgBar = progressBar(starship.deuteriumTank1, starship.deuteriumTank1MaxCapacity);
    string deuteriumTank2ProgBar = progressBar(starship.deuteriumTank2, starship.deuteriumTank2MaxCapacity);

    if (starship.fuelCollecters) {
        output += GREEN + string("[3] Fuel Collection Systems [ONLINE] ") + CYAN + fuelSummaryProgBar + string
    }

    // Add more systems here

    cout << output;
}

void handleInput(Starship& starship) {
    if (_kbhit()) { // Check if a key is pressed
        char choice = _getch(); // Read the key

        switch (choice) {
        case '1':
            starship.externalPower = !starship.externalPower;
            break;
        case '2':
            starship.startCapacitors = !starship.startCapacitors;
            break;
        default:
            break;
        }
    }
}

void ClearScreen()
{   
    COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

int main() {
    // Initialize Starting Conditions
    Starship starship;

    auto previousTime{ std::chrono::high_resolution_clock::now() };

    while (true) {

        updateSimulation(starship);

        handleInput(starship);

        ClearScreen();

        menu(starship);

        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = currentTime - previousTime;

        // Update time for the next loop
        previousTime = currentTime;

        // Sleep if needed to maintain desired frame rate
        if (elapsedTime < starship.targetFrameTime) {
            std::this_thread::sleep_for(starship.targetFrameTime - elapsedTime);
        }
    }
}


/*
*   standardize a way to change the frame time without effecting everything
*   change 1 value to propigate the change thoughout everything.
* 
*       Various starship to impliment
*   External power:
*   Tanks: helium (coolant), helium-3, and deuterium intake (fuels)
*   Coolant loops (storage tanks) for all to turn gas into liquid (affecting volumes)
*   Reactor coils, vacuum, power
*   Ship's batteries
*   Ship's electrical starship (shields, propulsion, FTL, weapons, lights)
*/