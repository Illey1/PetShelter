#ifndef PET_H
#define PET_H
#include <string>
#include <iostream>
#include "interestedadopter.h"

using namespace std;

class Pet {
public:
    Pet(string name, int ID, bool has_rabies, int days_with_rabies,
        Interested_Adopter* interestedadopter, long long adopterphonenum);
    virtual ~Pet();

    void setName(string name);
    void setID(int ID);
    void setDaysInShelter(int days_in_shelter);
    void setRabies(bool has_rabies);
    void setDaysWithRabies(int days);

    string getName() const;
    int getID() const;
    int getDaysInShelter() const;
    bool getRabiesStatus() const;
    int getDaysWithRabies() const;

    void nextDay();
    void contractRabies();
    void cureRabies();

    void add_adopter(Interested_Adopter adopter);
    void remove_adopter();
    Interested_Adopter* get_adopter();
    string get_adopter_name();
    long long get_adopter_phone_number();
    bool hasAdopter();

    virtual void printInfo();
    virtual void action() = 0;
    virtual string get_animal_type() = 0;
    virtual string get_extra_characteristic() = 0;

private:
    Interested_Adopter* interested_adopters;
    string name;
    int ID;
    int days_in_shelter;
    bool has_rabies;
    int days_with_rabies;
};

#endif // PET_H
