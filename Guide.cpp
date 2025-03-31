#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Data structures
struct Location {
    string name, pokemonTypes, gymBadge, activities;
    int pokecenters, breedingCenters;
};

struct TypeWeakness {
    string type, weaknesses;
};

// Helper functions
bool containsSubstring(const string& str, const string& substr) {
    return str.find(substr) != string::npos;
}

string toLower(const string& str) {
    string result = str;
    for (char& c : result) c = tolower(c);
    return result;
}

// File loading functions
vector<Location> loadLocations(const string& filename) {
    vector<Location> locations;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return locations;
    }
    
    string line, temp;
    while (getline(file, line)) {
        stringstream ss(line);
        Location loc;
        getline(ss, loc.name, ',');
        getline(ss, loc.pokemonTypes, ',');
        getline(ss, loc.gymBadge, ',');
        getline(ss, loc.activities, ',');
        getline(ss, temp, ','); loc.pokecenters = stoi(temp);
        getline(ss, temp, ','); loc.breedingCenters = stoi(temp);
        locations.push_back(loc);
    }
    return locations;
}

vector<TypeWeakness> loadTypeWeaknesses(const string& filename) {
    vector<TypeWeakness> typeData = {{"fire", "water,ground,rock"}, {"water", "electric,grass"}, 
                                     {"grass", "fire,ice,poison,flying,bug"}, {"electric", "ground"}};
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Type data file not found. Using default type information." << endl;
        return typeData;
    }
    
    typeData.clear();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string type, weaknesses;
        getline(ss, type, ':');
        getline(ss, weaknesses, ':');
        typeData.push_back({type, weaknesses});
    }
    return typeData;
}

// Display and selection functions
void displayLocation(const Location& loc, const vector<TypeWeakness>& typeData, bool details = false) {
    if (!details) {
        cout << loc.name << " - Types: " << loc.pokemonTypes << endl;
        return;
    }
    
    cout << "\n===== " << loc.name << " =====" << endl
         << "Pokemon Types: " << loc.pokemonTypes << endl
         << "Gym Badge: " << loc.gymBadge << endl
         << "Activities: " << loc.activities << endl
         << "Number of Pokecenters: " << loc.pokecenters << endl
         << "Number of Breeding Centers: " << loc.breedingCenters << endl;
    
    // Safety warnings
    cout << "\n=== SAFETY WARNING ===" << endl;
    string allTypes = "", allWeaknesses = "";
    
    stringstream ss(loc.pokemonTypes);
    string type;
    while (getline(ss, type, '/')) {
        while (!type.empty() && isspace(type[0])) type.erase(0, 1);
        while (!type.empty() && isspace(type.back())) type.pop_back();
        
        for (const auto& weakness : typeData) {
            if (weakness.type == type) {
                if (!allTypes.empty()) allTypes += ", ";
                allTypes += type;
                if (!allWeaknesses.empty()) allWeaknesses += ", ";
                allWeaknesses += weakness.weaknesses;
                break;
            }
        }
    }
    
    if (!allTypes.empty()) {
        cout << "This area has many " << allTypes << " type Pokemon." << endl
             << "Be careful with " << allWeaknesses << " type Pokemon as they can be weak in this area." << endl;
    }
    cout << "Be on the lookout for wild Pokemon!" << endl;
    
    // Cost estimation
    int cost = 0;
    if (loc.gymBadge != "None") cost += 200;
    if (containsSubstring(loc.activities, "safari")) cost += 300;
    if (containsSubstring(loc.activities, "event")) cost += 250;
    cost += loc.pokecenters * 50;
    
    cout << "\nEstimated trip cost: " << cost << " PokeDollars" << endl;
    
    // Pokecenter info
    if (loc.pokecenters > 0) {
        cout << "There " << (loc.pokecenters == 1 ? "is " : "are ") << loc.pokecenters 
             << " Pokecenter" << (loc.pokecenters == 1 ? "" : "s") << " available." << endl;
    } else {
        cout << "Warning: No Pokecenters available in this area!" << endl;
    }
}

void displayAllLocations(const vector<Location>& locations) {
    cout << "\nAvailable locations:" << endl;
    for (size_t i = 0; i < locations.size(); i++) {
        cout << i+1 << ". ";
        displayLocation(locations[i], {});
    }
}

Location selectLocation(vector<Location>& locations, const vector<TypeWeakness>& typeData) {
    displayAllLocations(locations);
    if (locations.size() == 1) return locations[0];
    
    int choice;
    cout << "Enter the number of the location you'd like to visit: ";
    cin >> choice;
    
    if (choice >= 1 && choice <= static_cast<int>(locations.size())) {
        return locations[choice-1];
    }
    cout << "Invalid choice. Please try again." << endl;
    return {}; // Empty location
}

// Filter locations based on criteria
vector<Location> filterLocations(const vector<Location>& locations, int filterType, const string& criteria = "", int minPokecenters = 0, bool needsBreeding = false) {
    vector<Location> filtered;
    for (const auto& loc : locations) {
        bool match = false;
        switch (filterType) {
            case 1: match = containsSubstring(loc.pokemonTypes, criteria); break;
            case 2: match = containsSubstring(toLower(loc.gymBadge), toLower(criteria)); break;
            case 3: match = containsSubstring(loc.activities, criteria); break;
            case 4: match = (loc.pokecenters >= minPokecenters) && (!needsBreeding || loc.breedingCenters > 0); break;
            default: match = true; // Return all locations if no valid filter type
        }
        if (match) filtered.push_back(loc);
    }
    return filtered;
}

int main() {
    vector<Location> allLocations = loadLocations("pokemon_locations.txt");
    vector<TypeWeakness> typeData = loadTypeWeaknesses("pokemon_types.txt");
    vector<Location> filteredLocations = allLocations;
    
    cout << "Welcome to the Pokemon Destination Guide!" << endl;
    bool run = true;
    while (run == true){
        cout << "\nWhat would you like to do?" << endl
             << "1. Choose a specific place to go" << endl
             << "2. I'm not sure, help me decide" << endl
             << "3. View all available destinations" << endl
             << "4. Exit" << endl;
        
        int choice;
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        
        if (choice == 4) {
            cout << "Thank you for using the Pokemon Destination Guide. Goodbye!" << endl;
            run = false;
        }
        
        if (choice == 3) {
            displayAllLocations(filteredLocations);
            continue;
        }
        
        if (choice == 1) {
            Location selected = selectLocation(filteredLocations, typeData);
            if (!selected.name.empty()) {
                displayLocation(selected, typeData, true);
                break;
            }
            continue;
        }
        
        if (choice == 2) {
            cout << "\nWhat are you looking for?" << endl
                 << "1. Specific Pokemon types" << endl
                 << "2. Gym leagues/badges" << endl
                 << "3. Activities (safaris, special events)" << endl
                 << "4. Pokemon healthcare facilities" << endl;
            
            int filterChoice;
            cout << "Enter your choice (1-4): ";
            cin >> filterChoice;
            cin.ignore(); // Clear newline
            
            string criteria;
            int minPokecenters = 0;
            bool needsBreeding = false;
            
            if (filterChoice >= 1 && filterChoice <= 3) {
                string prompts[] = {"", "Pokemon type", "gym badge", "activity"};
                cout << "What " << prompts[filterChoice] << " are you looking for? ";
                getline(cin, criteria);
            } else if (filterChoice == 4) {
                char answer;
                cout << "Do you need a breeding center? (y/n): ";
                cin >> answer;
                needsBreeding = (answer == 'y' || answer == 'Y');
                cout << "Minimum number of Pokecenters needed: ";
                cin >> minPokecenters;
            } else {
                cout << "Invalid choice." << endl;
                continue;
            }
            
            filteredLocations = filterLocations(filteredLocations, filterChoice, criteria, minPokecenters, needsBreeding);
            
            if (filteredLocations.empty()) {
                cout << "No matching locations found. Let's try something else." << endl;
                filteredLocations = allLocations;
                continue;
            }
            
            cout << "Found " << filteredLocations.size() << " matching locations." << endl;
            
            if (filteredLocations.size() == 1) {
                displayLocation(filteredLocations[0], typeData, true);
                break;
            }
            
            Location selected = selectLocation(filteredLocations, typeData);
            if (!selected.name.empty()) {
                displayLocation(selected, typeData, true);
                break;
            }
        }
    }
    
    return 0;
}
