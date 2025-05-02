#include "pet.h"
#include "cat.h"
#include "fish.h"
#include <sstream>
#include <fstream>
/*
Name: Illeyan Atif
Date: 04/22/2025
Class: CS-116
Program name: Lab 2 Expanded Shelter
 */

void checkInventory(string filename, Pet* arr[], int& size);
Pet* longestTimeInShelter(Pet* arr[], int& size);
void updateInventory(string filename, Pet* arr[], int& size, int& maxSize);
void addPet(Pet* arr[], int& size, string name, int ID, string animal_type, bool has_rabies, int days_with_rabies, string characteristic, Interested_Adopter* interestedadopter, long long adopterphonenum);
void healthStatus(Pet* arr[], int& size);
void dailyCareTasks(Pet* arr[], int& size);
void displayMenu(Pet* arr[], string filename, int &size, int &maxSize);

/*
Entry point of the shelter management program.
Prompts the user to either load existing pet data from a file or start fresh by setting a maximum shelter size.
Allocates a dynamic array of Pet* pointers to hold Cat or Fish objects.
Advances the simulation by one day, applying updates to all pets (e.g., rabies progression, adoption checks).
Launches an interactive menu loop for user operations including adding pets, curing/infecting rabies, assigning adopters, and saving data.
Cleans up all dynamically allocated memory before exiting.
 */
int main() {
    srand (time(NULL));
    int size = 0;
    int maxSize = 0;
    string c;
    string filename;
    // Dynamically allocated pointer array of Pet* objects
    Pet** arr = nullptr;
    cout << "Greetings. This program allows you to store pet objects in a shelter and assign them adopters!" << endl <<
    "Would you like to continue?(Y/N)";
    cin >> c;
    while (true) {
        if (c == "y" || c == "Y") {
            string b;
            cout << "Is there current inventory?(Y/N)";
            cin >> b;
            if (b == "y" || b == "Y") {
                cout << "Please give filename: ";
                // File stores the first line as maxSize; then each line is one pet
                cin >> filename;
                ifstream ifs(filename);
                ifs >> maxSize;
                arr = new Pet*[maxSize]; // Allocate array of Pet pointers
                checkInventory(filename, arr, size);
                break;
            } else {
                cout << "What will be the max inventory? ";
                cin >> maxSize;
                arr = new Pet*[maxSize];
                break;
            }
        } else if (c == "n" || c == "N") {
            cout << "Goodbye!" << endl;
            return 0;
        } else {
            cout << "Invalid Input! Try again: ";
        }
    }

    for (int i = 0; i < size; i++) {
        arr[i]->nextDay();
    }
    dailyCareTasks(arr, size);
    healthStatus(arr, size);
    displayMenu(arr, filename, size, maxSize);
    // Final cleanup: delete all dynamically allocated Pet objects
    for (int i = 0; i < size; i++) {
        delete arr[i]; // Destructor is virtual, so derived class destructors are called
    }
    delete[] arr; // Delete array of Pet pointers
    return 0;
}


/*
Displays an interactive menu using a while loop and switch statement.
Allows user to view pets, add new pets, cure or infect pets with rabies,
assign adopters, save inventory to a file, or exit the program.
 */
void displayMenu(Pet* arr[], string filename, int &size, int &maxSize) {
    while (true) {
        int z;
        cout << "1. Load Shelter" << endl <<
                    "2. Add Pet" << endl << "3. Oldest Resident" << endl << "4. Cure" << endl <<
                           "5. Contract" << endl << "6. Assign Adopter" << endl << "7. Save" <<
                               endl << "8. Exit" << endl;
        cin >> z;
        switch (z) {
            case 1: {
                cout << "Current Shelter List: " << endl;
                if (size != 0) {
                    for (int i = 0; i < size; i++) {
                        cout << i+1 << ". " << arr[i]->getName() << endl;
                        arr[i]->printInfo();
                        cout << endl;
                    }
                } else {
                    cout << "Empty!" << endl;
                }
                break;
            }
            case 2: {
                if (size < maxSize) {
                    string newname;
                    int newid;
                    string newanimaltype;
                    string newrabiesstatus;
                    bool has_rabies = false;

                    cout << "Please Enter a name: ";
                    cin >> newname;

                    cout << "Please Enter an ID: ";
                    cin >> newid;

                    cout << "Please Enter an Animal Type (Cat/Fish): ";
                    cin >> newanimaltype;

                    string characteristic;
                    if (newanimaltype == "Cat") {
                        cout << "Hair type? ";
                        cin >> characteristic;
                    } else if (newanimaltype == "Fish") {
                        cout << "Water type? ";
                        cin >> characteristic;
                    } else {
                        //Validate animal type. If invalid, skip adding. Not needed but had
                        //an infinite loop with certain edge cases
                        cout << "Invalid animal type. Only 'Cat' or 'Fish' allowed." << endl;
                        break;
                    }

                    cout << "Does it have rabies? (Y/N): ";
                    cin >> newrabiesstatus;
                    if (newrabiesstatus == "Y" || newrabiesstatus == "y") {
                        has_rabies = true;
                    }

                    addPet(arr, size, newname, newid, newanimaltype, has_rabies, 0, characteristic, nullptr, 0);
                    string a;
                    cout << "Interested adopter? (Y/N): ";
                    cin  >> a;
                    if (a == "Y" || a == "y") {
                        string interestedadop;
                        long long phone;
                        cout << "Adopter name (first): ";
                        cin  >> interestedadop;
                        cout << "Adopter phone (ex:1234567890): ";
                        cin  >> phone;
                        arr[size-1]->add_adopter(Interested_Adopter(interestedadop,phone));
                    }
                } else {
                        cout << "Shelter is full!" << endl;
                    }
                    break;
                }
                case 3: {
                    cout << "The Pet that has been here the longest: " << endl;
                    longestTimeInShelter(arr, size)->printInfo();
                    break;
                }
                case 4: {
                    int toCure;
                    bool idFound = false;
                    cout << "Which pet would you like to cure?(ID Number): ";
                    cin >> toCure;
                    for (int i = 0; i < size; i++) {
                        if (arr[i]->getID() == toCure) {
                            arr[i]->cureRabies();
                            arr[i]->setDaysWithRabies(0);
                            idFound = true;
                        }
                    }
                    if (!idFound) {
                        cout << "No Match Found!" << endl;
                    }
                    break;
                }
                case 5: {
                    int toInfect;
                    bool idFound = false;
                    cout << "Which pet would you like to contract rabies?(ID Number): ";
                    cin >> toInfect;
                    for (int i = 0; i < size; i++) {
                        if (arr[i]->getID() == toInfect) {
                            arr[i]->contractRabies();
                            arr[i]->setDaysWithRabies(0);
                            idFound = true;
                        }
                    }
                    if (!idFound) {
                        cout << "No Match Found!" << endl;
                    }
                    break;
                }
                case 6: {
                int assignedPetID = 0;
                string nameOfAdopter;
                long long phoneOfAdopter = 0;
                cout << "Please enter the ID of the pet who is getting adopted: ";
                cin >> assignedPetID;
                cout << "Please enter the name of adopter (first): ";
                cin >> nameOfAdopter;
                cout << "Please enter their phone number: ";
                cin >> phoneOfAdopter;
                // Create adopter and assign to pet by ID. ID must exist.
                Interested_Adopter* newAdopter = new Interested_Adopter(nameOfAdopter, phoneOfAdopter);
                bool IDfound = false;
                for (int i = 0; i < size; i++) {
                    if (arr[i]->getID() == assignedPetID) {
                        // Deep copy made inside method
                        arr[i]->add_adopter(*newAdopter);
                        IDfound = true;
                        break;
                    }
                }
                if (IDfound == false) {
                    cout << "ID not found, please try again" << endl;
                }
                break;
                }
                case 7: {
                    if (filename == "") {
                        cout << "Please enter the name of the file you would like to create: ";
                        cin >> filename;
                    }
                    updateInventory(filename, arr, size, maxSize);
                    cout << "Updated!" << endl;
                    break;
                }
                case 8: {
                    cout << "Goodbye!";
                    return;
                }
            }
        }
    }


/*
Checks all pets for rabies status. If any pet has had rabies for 3+ days,
it is considered ded, printed out, deleted, and removed from the array.
Array is shifted after deletion and loop index is decremented to re-check.
 */
void healthStatus(Pet *arr[], int &size) {
    for (int i = 0; i < size; i++) {
        arr[i]->action();

        if (arr[i]->getDaysWithRabies() >= 3) {
            cout << arr[i]->getName() << " Died!" << endl;
            delete arr[i]; //delete pet
            for (int j = i; j < size - 1; j++) {
                arr[j] = arr[j + 1]; // Shift remaining pets left
            }
            size--; // One fewer pet
            i--; // Stay on same index since it now contains a new pet
            //same algorithm to delete pets reused without program
        }
    }
}

/*
Performs daily care checks for pets.
Cats need grooming every 2 days
Fish need tank cleaning every 3 days
All pets get a weekly checkup starting on day 7
Pets with adopters are adopted on day 10
Pets are automatically adopted by other shelters after 15 days
 */
void dailyCareTasks(Pet *arr[], int &size) {
    cout << "Daily Care Tasks:" << endl;
    for (int i = 0; i < size;i++) {
        Pet* p = arr[i];
        if (p->getDaysInShelter() % 2 == 0 && p->get_animal_type() == "Cat") {
            cout << p->getName() << " needs grooming!" << endl;
        }
        if (p->getDaysInShelter() % 3 == 0 && p->get_animal_type() == "Fish") {
            cout << p->getName() << " needs its tank cleaned!" << endl;
        }
        if (p->getDaysInShelter() >= 7 && p->getDaysInShelter() % 7 == 0) {
            cout << p->getName() << " needs a weekly checkup." << endl;
        }
        if (p->getDaysInShelter() >= 10 && p->get_adopter_name() != "") {
            // Adopter is contacted, then pet is removed
            cout << "Contacting Adopter: " << p->get_adopter_name() << endl <<
                "Phone Number: " << p->get_adopter_phone_number() << endl << "For: " << p->getName() << endl << endl;
            delete p;
            for (int j = i; j < size - 1; j++) {
                arr[j] = arr[j+1];
            }
            size--;
            i--;
            continue;
        }
        if (p->getDaysInShelter() >= 15) {
            cout << p->getName() << " has been adopted by another shelter!" << endl;
            delete p;
            for (int j = i; j < size - 1; j++) {
                arr[j] = arr[j+1];
            }
            size--;
            i--;
        }

    }
}



/*
Dynamically creates a new Cat or Fish and adds it to the Pet* array.
Increments the size after successful addition.
*/
void addPet(Pet* arr[], int& size, string name, int ID, string animal_type, bool has_rabies, int days_with_rabies, string characteristic, Interested_Adopter* interestedadopter, long long adopterphonenum) {
    if (animal_type == "Cat") {
        arr[size] = new Cat(characteristic, name, ID, has_rabies, days_with_rabies, interestedadopter, adopterphonenum);
    } else if (animal_type == "Fish") {
        arr[size] = new Fish(characteristic, name, ID, has_rabies, days_with_rabies, interestedadopter, adopterphonenum);
    }
    size++;
}


/*
Iterates to find pet with longest daysinshelter() data member.
 */
Pet* longestTimeInShelter(Pet* arr[], int& size) {
    Pet* mostDays = arr[0];
    for (int i = 0; i < size; i++) {
        if (arr[i]->getDaysInShelter() > mostDays->getDaysInShelter()) {
            mostDays = arr[i];
        }
    }
    return mostDays;
}


/*
Reads pet data from a file and dynamically creates Cat or Fish objects,
storing them in the Pet* array. Handles pets with and without adopters.
*/
void checkInventory(string filename, Pet* arr[], int& size) {
    ifstream ifs(filename);
    if (ifs.fail()) {
        cout << "Failed to open file" << endl;
        return;
    }

    int max;
    ifs >> max;
    string line;
    getline(ifs, line); //clear leftover newline

    while (size < max && getline(ifs, line)) {
        stringstream ss(line);
        string num_str, name, animalType, characteristic;
        int ID, daysShelter, daysRabies;
        bool rabies, hasAdopter;

        //name
        getline(ss, name, ',');

        //ID
        getline(ss, num_str, ',');
        ID = stoi(num_str);

        //days in shelter
        getline(ss, num_str, ',');
        daysShelter = stoi(num_str);

        // 4. rabies status
        getline(ss, num_str, ',');
        if (num_str == "true") {
            rabies = true;
        } else {
            rabies = false;
        }

        //days with rabies
        getline(ss, num_str, ',');
        daysRabies = stoi(num_str);

        //animal type (Cat or Fish)
        getline(ss, num_str, ',');
        animalType = num_str;

        //characteristic (hair type or water type)
        getline(ss, num_str, ',');
        characteristic = num_str;

        //has adopter?
        getline(ss, num_str, ',');
        if (num_str == "true") {
            hasAdopter = true;
        } else {
            hasAdopter = false;
        }

        string adopter_name = "";
        long long adopter_phone = 0;

        // Checks whether adopter info is present
        if (hasAdopter == true) {
            //adopter name
            getline(ss, adopter_name, ',');

            //adopter phone
            getline(ss, num_str, ',');
            if (num_str != "") {
                    adopter_phone = stoll(num_str);
            }
        } else {
            // consume the empty lines if not
            getline(ss, num_str, ',');
            getline(ss, num_str, ',');
        }

        if (animalType == "Cat") {
            if (hasAdopter) {
                Interested_Adopter* adopter = new Interested_Adopter(adopter_name, adopter_phone);
                arr[size] = new Cat(characteristic, name, ID, rabies, daysRabies, adopter, adopter_phone);
            } else {
                arr[size] = new Cat(characteristic, name, ID, rabies, daysRabies, nullptr, 0);
            }
        } else if (animalType == "Fish") {
            if (hasAdopter) {
                Interested_Adopter* adopter = new Interested_Adopter(adopter_name, adopter_phone);
                arr[size] = new Fish(characteristic, name, ID, rabies, daysRabies, adopter, adopter_phone);
            } else {
                arr[size] = new Fish(characteristic, name, ID, rabies, daysRabies, nullptr, 0);
            }
        }

        arr[size]->setDaysInShelter(daysShelter);
        size++;
    }
}


/*
Saves current pet data to file, including adopter info.
Uses readable true/false strings instead of 1/0 for rabies/adopter fields.
 */
void updateInventory(string filename, Pet *arr[], int &size, int &maxSize) {
    ofstream ofs(filename);
    ofs << maxSize << endl;
    string rabiesStatus, hasAdopter;
    for (int i = 0; i < size; i++) {
        if (arr[i]->getRabiesStatus() == true) {
            rabiesStatus = "true";
        } else {
            rabiesStatus = "false";
        }
        if (arr[i]->hasAdopter() == false) {
            hasAdopter = "false";
        } else {
            hasAdopter = "true";
        }
        ofs << arr[i]->getName() << "," << arr[i]->getID() << "," << arr[i]->getDaysInShelter()
            << "," << rabiesStatus << "," << arr[i]->getDaysWithRabies() << "," << arr[i]->get_animal_type() << "," <<
                arr[i]->get_extra_characteristic() << "," << hasAdopter << "," <<
                    arr[i]->get_adopter_name() << "," << arr[i]->get_adopter_phone_number() << endl;
    }
}