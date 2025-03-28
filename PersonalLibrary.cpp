#include <iostream>
#include <string>
#include <vector>
#include "PersonalLibrary.h"
using namespace std;
int main()
{
   int id;
    string personalname;
    string type;
    int total;
    int hp;
    int atk; 
    int def;
    int spatk;
    int spdef;
    int speed;
    char choice;
Pokedex pokedex;
cout<<"\n\n\n================================================\n*** Welcome to the Pokedex Personal Library! ***\n================================================"<<endl;
bool run = true;
while (run == true)
{
cout<<"-View Pokemon (V)\n-Add Pokemon(R)\n-Quit (Q)\n\nWhat would you like to do? ";
cin>>choice;
if (choice == 'V' || choice == 'v')
{
    pokedex.listPokemons();
    cout<<"\n";
}
else if (choice == 'R' || choice == 'r')
{ 
cout<<"\n=====================================\n    *** Pokedex Custom Entry *** \n=====================================\nFirst please enter your pokemon's ID: ";
cin>>id;
cout<<"Now Enter the name of your pokemon: ";
cin>>personalname;
cout<<"Now enter the type of your pokemon: ";
cin>>type;
cout<<"Now enter the HP of your pokemon: ";
cin>>hp;
cout<<"Now enter the Attack of your pokemon: ";
cin>>atk;
cout<<"Now enter the Defense of your pokemon: ";
cin>>def;
cout<<"Now enter the Special Attack of your pokemon: ";
cin>>spatk;
cout<<"Now enter the Special Defense of your pokemon: ";
cin>>spdef;
cout<<"Now enter the Speed of your pokemon: ";
cin>>speed;
cout<<"\nPokemon succesfully added!\n\n";
pokedex.addPokemon(PokemonLibrary(personalname, type, id, total, hp, atk, def, spatk, spdef, speed));
}

else if (choice == 'Q' || choice == 'q')
{
    cout<<"\n\n=========================================================\n*** Thank you for using the Pokedex Personal Library! ***\n=========================================================\n\nNow Exiting...\n"<<endl;
    run = false;
}
}
return 0;
}
