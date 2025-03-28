#include<string>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
using namespace std;
class PokemonLibrary
{  
private:

    int id;
    string name;
    string type;
    int total;
    int hp;
    int atk; //attack
    int def;
    int spatk; //special attack
    int spdef; // special defense
    int speed;

public: 

        PokemonLibrary(string name2, string type2, int id2, int total2, int hp2, int atk2, int def2, int spatk2, int spdef2, int speed2)
    : name(name2), type(type2), id(id2), hp(hp2), atk(atk2), def(def2),spatk(spatk2), spdef(spdef2), speed(speed2)
{
    total = hp + atk + def + spatk + spdef + speed;
}
    string getName() const
{
    return name;
}
void setName(const string& newName)
{
    name = newName;
}
int getTotal() const
{
    return total;
}  
int getHp() const
{
    return hp;
}

int getAtk() const
{
    return atk;
}

int getDef() const
{
    return def;
}

int getSpatk() const
{
    return spatk;
}

int getSpdef() const
{
    return spdef;
}
string getType() const
{
    return type;
}
int getSpeed() const
{
    return speed;
}
int getID() const
{
    return id;
}
void setID(const int& newID)
{
    id = newID;
}
void setTotal(int newTotal)
{
    total = newTotal;
}

void setHp(int newHp)
{
    hp = newHp;
    total = hp + atk + def + spatk + spdef + speed;
}

void setAtk(int newAtk)
{
    atk = newAtk;
    total = hp + atk + def + spatk + spdef + speed;
}

void setDef(int newDef)
{
    def = newDef;
    total = hp + atk + def + spatk + spdef + speed;
}

void setSpatk(int newSpatk)
{
    spatk = newSpatk;
    total = hp + atk + def + spatk + spdef + speed;
}

void setSpdef(int newSpdef)
{
    spdef = newSpdef;
    total = hp + atk + def + spatk + spdef + speed;
}

void setSpeed(int newSpeed)
{
    speed = newSpeed;
    total = hp + atk + def + spatk + spdef + speed;
}
void setType(string newType)
{
    type = newType;
}

};

class Pokedex
{
    private:
        vector<PokemonLibrary> pokemons;
    public:
        void addPokemon(const PokemonLibrary& pokemon)
        {
            using namespace std::chrono;
            int newID = pokemon.getID();
        
            vector<PokemonLibrary>::iterator it = pokemons.begin();

            while(it != pokemons.end() && it->getID() < newID)
            {
                it++;
            }
            pokemons.insert(it,pokemon);
            std::this_thread::sleep_for(seconds(3));
        }
        void listPokemons() const
        {
            using namespace std::chrono;
            if (pokemons.size() == 0)
            {
                cout<<"\n\nCatch Pokemon to begin your Pokedex!\n\n";
                std::this_thread::sleep_for(seconds(3));
            }
      else{
            cout<<"\n===============================\n*** Personal Pokedex Library ***\n==============================="<<endl;
            for (int i = 0; i < pokemons.size(); i++)
            {
    
                cout<<"ID: "<<pokemons[i].getID()<<" | Name: "<<pokemons[i].getName()<<" | Type: "<<pokemons[i].getType()<<" | Total: "<<pokemons[i].getTotal()<<" | HP: "<<pokemons[i].getHp()<<" | Attack: "<<pokemons[i].getAtk()<<" | Defense: "<<pokemons[i].getDef()<<" | Special Attack: "<<pokemons[i].getSpatk()<<" | Special Defense: "<<pokemons[i].getSpdef()<<" | Speed: "<<pokemons[i].getSpeed()<<endl;
            }     
          }
        }
};
