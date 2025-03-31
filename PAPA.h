// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class AbilityData {
private:
    vector<string> pokemonList;
    string description;
    string strongAgainst;
    string weakAgainst;

public:
    void setDescription(const string& desc) { description = desc; }
    void setStrongAgainst(const string& strong) { strongAgainst = strong; }
    void setWeakAgainst(const string& weak) { weakAgainst = weak; }
    void addPokemon(const string& pokemon) { pokemonList.push_back(pokemon); }

    string getDescription() const { return description; }
    string getStrongAgainst() const { return strongAgainst; }
    string getWeakAgainst() const { return weakAgainst; }
    const vector<string>& getPokemonList() const { return pokemonList; }
};

class PokemonDatabase {
private:
    vector<pair<string, AbilityData> > abilities;

    string trim(const string& str) {
        size_t first = str.find_first_not_of(" \t");
        size_t last = str.find_last_not_of(" \t");
        return (first == string::npos) ? "" : str.substr(first, last - first + 1);
    }

    string toLowerCase(const string& str) {
        string lowerStr = str;
        for (char& ch : lowerStr) {
            if (ch >= 'A' && ch <= 'Z') {
                ch += ('a' - 'A');
            }
        }
        return lowerStr;
    }

    AbilityData* findAbility(const string& ability) {
        for (auto& pair : abilities) {
            if (pair.first == ability) {
                return &pair.second;
            }
        }
        return nullptr;
    }

public:
    PokemonDatabase(const string& filename) {
        loadFromFile(filename);
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error: Could not open file '" << filename << "'.\n";
            return;
        }

        string line, currentAbility;
        AbilityData abilityData;

        while (getline(file, line)) {
            line = trim(line);
            if (line.empty()) continue;

            size_t pos = line.find(':');
            if (pos != string::npos) {
                string key = trim(line.substr(0, pos));
                string value = trim(line.substr(pos + 1));

                if (key == "AbilityDescription") {
                    abilityData.setDescription(value);
                } else if (key == "StrongAgainst") {
                    abilityData.setStrongAgainst(value);
                } else if (key == "WeakAgainst") {
                    abilityData.setWeakAgainst(value);
                } else {
                    if (!currentAbility.empty()) {
                        abilities.emplace_back(currentAbility, abilityData);
                        abilityData = AbilityData();
                    }
                    currentAbility = toLowerCase(key);
                    istringstream ss(value);
                    string pokemon;

                    while (getline(ss, pokemon, ',')) {
                        abilityData.addPokemon(trim(pokemon));
                    }
                }
            }
        }

        if (!currentAbility.empty()) {
            abilities.emplace_back(currentAbility, abilityData);
        }
        file.close();
    }

    void displayAbilities() {
        cout << "\nAvailable Abilities:\n";
        for (const auto& pair : abilities) {
            cout << "- " << pair.first;
            if (!pair.second.getDescription().empty()) {
                cout << " -> " << pair.second.getDescription();
            }
            cout << endl;
        }
    }

    void displayPokemonByAbility(string ability) {
        ability = toLowerCase(trim(ability));
        AbilityData* data = findAbility(ability);

        if (data) {
            cout << "\nPokemon with ability '" << ability << "':\n";
            for (const auto& pokemon : data->getPokemonList()) {
                cout << "  - " << pokemon << endl;
            }
        } else {
            cout << "No Pokemon found with the ability '" << ability << "'.\n";
        }
    }

    void displayAbilityMatchups(string ability) {
        ability = toLowerCase(trim(ability));
        AbilityData* data = findAbility(ability);

        cout << "\nMatchups for ability '" << ability << "':\n";
        if (data) {
            cout << "  Strong Against: " << (data->getStrongAgainst().empty() ? "None" : data->getStrongAgainst()) << endl;
            cout << "  Weak Against: " << (data->getWeakAgainst().empty() ? "None" : data->getWeakAgainst()) << endl;
        } else {
            cout << "Ability not found.\n";
        }
    }
};
