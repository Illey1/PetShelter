#ifndef INTERESTEDADOPTER_H
#define INTERESTEDADOPTER_H

#include <string>

using namespace std;

class Interested_Adopter {
public:
    Interested_Adopter();
    Interested_Adopter(string name, long long phone_number);

    void set_name(string name);
    void set_phone_number(long long phone_number);

    string get_name();
    long long get_phone_number();

private:
    string name;
    long long phone_number;
};

#endif // INTERESTEDADOPTER_H