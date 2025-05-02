# Pet Shelter Management System 🐾

This is a C++ object-oriented project simulating a pet shelter system. It supports adding, managing, and adopting out pets (Cats and Fish), while handling 
real-world factors like rabies tracking, adopter assignments, and daily care routines.

---

## 🚀 Features

- Add pets (Cat or Fish) with detailed attributes
- Track rabies status and shelter days
- Assign interested adopters
- Simulate day-by-day shelter operations
- Automatically remove pets after adoption or death
- Save and load inventory from CSV-style files
- Input validation for user interaction

---

## 🧠 Object-Oriented Design

- **Base Class:** `Pet`
- **Derived Classes:** `Cat`, `Fish`
- **Composition:** `Interested_Adopter`
- **Core Manager:** Handles pets using a raw pointer array or vector (depending on version)

---

## 🛠️ Build Instructions

### 🔹 Using CMake
```bash
mkdir build
cd build
cmake ..
make
./PetShelter

