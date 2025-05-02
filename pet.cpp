#include "pet.h"

Pet::Pet(string name, int ID, bool has_rabies, int days_with_rabies,
         Interested_Adopter* interestedadopter, long long adopterphonenum) {
    this->name = name;
    this->ID = ID;
    this->has_rabies = has_rabies;
    this->days_in_shelter = 0;
    this->days_with_rabies = days_with_rabies;

    if (interestedadopter == nullptr) {
        interested_adopters = nullptr;
    } else {
        interested_adopters = new Interested_Adopter(*interestedadopter);
    }
}

Pet::~Pet() {
    delete interested_adopters;
}

void Pet::setName(string name) {
    this->name = name;
}

void Pet::setID(int ID) {
    this->ID = ID;
}

void Pet::setDaysInShelter(int days_in_shelter) {
    this->days_in_shelter = days_in_shelter;
}

void Pet::setRabies(bool has_rabies) {
    this->has_rabies = has_rabies;
}

void Pet::setDaysWithRabies(int days) {
    this->days_with_rabies = days;
}

string Pet::getName() const {
    return name;
}

int Pet::getID() const {
    return ID;
}

int Pet::getDaysInShelter() const {
    return days_in_shelter;
}

bool Pet::getRabiesStatus() const {
    return has_rabies;
}

int Pet::getDaysWithRabies() const {
    return days_with_rabies;
}

void Pet::nextDay() {
    days_in_shelter++;
    if (has_rabies) {
        days_with_rabies++;
    }
}

void Pet::contractRabies() {
    setRabies(true);
}

void Pet::cureRabies() {
    setRabies(false);
}
bool Pet::hasAdopter() {
    return interested_adopters != nullptr;
}

void Pet::add_adopter(Interested_Adopter adopter) {
    if (interested_adopters == nullptr) {
        interested_adopters = new Interested_Adopter(adopter.get_name(), adopter.get_phone_number());
    }
}

void Pet::remove_adopter() {
    if (interested_adopters != nullptr) {
        delete interested_adopters;
        interested_adopters = nullptr;
    }
}

Interested_Adopter* Pet::get_adopter() {
    return interested_adopters;
}

string Pet::get_adopter_name() {
    if (interested_adopters == nullptr) {
        return "";
    }
    return interested_adopters->get_name();
}

long long Pet::get_adopter_phone_number() {
    if (interested_adopters == nullptr) {
        return 0;
    }
    return interested_adopters->get_phone_number();
}

void Pet::printInfo() {
    cout << "Name: " << name << endl;
    cout << "ID: " << ID << endl;
    cout << "Days in shelter: " << days_in_shelter << endl;
    if (getRabiesStatus()) {
        cout << "This animal has had rabies for: " << days_with_rabies << " days." << endl;
    }
    if (interested_adopters != nullptr) {
        cout << "Interested Adopter: " << interested_adopters->get_name() << endl;
    }
}
