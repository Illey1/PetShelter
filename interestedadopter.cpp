#include "interestedadopter.h"

Interested_Adopter::Interested_Adopter() {
    this->name = "";
    this->phone_number = 0;
}

Interested_Adopter::Interested_Adopter(string name, long long phone_number) {
    this->name = name;
    this->phone_number = phone_number;
}

void Interested_Adopter::set_name(string name) {
    this->name = name;
}

void Interested_Adopter::set_phone_number(long long phone_number) {
    this->phone_number = phone_number;
}

string Interested_Adopter::get_name() {
    return this->name;
}

long long Interested_Adopter::get_phone_number() {
    return this->phone_number;
}