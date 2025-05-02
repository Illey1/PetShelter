#ifndef FISH_H
#define FISH_H
#include "pet.h"

class Fish : public Pet {
public:
    Fish(string water_type, string name, int ID, bool has_rabies, int days_with_rabies,
         Interested_Adopter* interestedadopter, long long adopterphonenum);

    string get_water_type();
    virtual string get_animal_type() override;
    virtual void action() override;
    virtual void printInfo() override;
    virtual string get_extra_characteristic() override;

private:
    string water_type;
    string animal_type = "Fish";
};

#endif // FISH_H