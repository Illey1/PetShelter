#include "cat.h"

Cat::Cat(string hair_type, string name, int ID, bool has_rabies, int days_with_rabies,
         Interested_Adopter* interestedadopter, long long adopterphonenum)
    : Pet(name, ID, has_rabies, days_with_rabies, interestedadopter, adopterphonenum) {
    this->hair_type = hair_type;
    setName(name);
    setID(ID);
    setRabies(has_rabies);
    setDaysWithRabies(days_with_rabies);
}

string Cat::get_hair_type() {
    return this->hair_type;
}

void Cat::action() {
    string actions[4] = { "purrs", "meows", "hacks up a hairball", "licks themself" };
    int random_action = rand() % 4;
    cout << getName() << " " << actions[random_action] << "." << endl;
}

string Cat::get_animal_type() {
    return this->animal_type;
}

void Cat::printInfo() {
    cout << "Animal Type: " << animal_type << endl
         << "Hair Type: " << hair_type << endl;
    Pet::printInfo();
}

string Cat::get_extra_characteristic() {
    return this->hair_type;
}