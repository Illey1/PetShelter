#include "fish.h"

Fish::Fish(string water_type, string name, int ID, bool has_rabies, int days_with_rabies,
           Interested_Adopter* interestedadopter, long long adopterphonenum)
    : Pet(name, ID, has_rabies, days_with_rabies, interestedadopter, adopterphonenum) {
    this->water_type = water_type;
    setName(name);
    setID(ID);
    setRabies(has_rabies);
    setDaysWithRabies(days_with_rabies);
}

string Fish::get_animal_type() {
    return this->animal_type;
}

string Fish::get_water_type() {
    return this->water_type;
}

void Fish::action() {
    string actions[4] = { "swims", "eats algae", "hovers", "bolts around" };
    int random_action = rand() % 4;
    cout << getName() << " " << actions[random_action] << "!" << endl;
}

void Fish::printInfo() {
    cout << "Animal Type: " << animal_type << endl
         << "Water Type: " << water_type << endl;
    Pet::printInfo();
}

string Fish::get_extra_characteristic() {
    return this->water_type;
}