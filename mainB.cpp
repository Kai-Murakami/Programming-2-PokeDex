# include "PokemonB.h"
# include "PokemonB.cpp"

int main(){

// declartion of some variables to be used here in the main file
string Entered_generation;
string Entered_name;
string generation_u_want_to_filter;
int Entered_choice;


// This part will always be executed because it opens the text files
cout << "Enter the generation number: " << endl;
cin >> Entered_generation;
Pokemon Pokemon(Entered_generation);

// This code as well will always be executed because it retrives data from the text file to vectors
Pokemon.import_from_file();


// the below text is asking the user what he/she wants to do with the data,
// either to search for specific pokemon or ouput all pokemon in a specified generation 

cout << "Please choose from the menu below what you like to do with Pokemon data " << endl<<endl;
cout << "If you want to search specific Pokemon press 1." << endl<< endl;
cout << "If you want to filter and output the whole pokemon in a specific generation press 2." << endl;
// it recives the choice 
cin >> Entered_choice;

// based on the user's choice it proceds here 
if (Entered_choice == 1){
cout << "Enter the specific pokimon's name: "<< endl;
cin >> Entered_name;
Pokemon.find_pokemon(Entered_name);   // this function will search/find the specific pokemon
}

else if(Entered_choice == 2){
cout << "Please Enter the generation number: " << endl;
cin >> generation_u_want_to_filter;
Pokemon.filter_by_generation(generation_u_want_to_filter); // this function will output all the pokemon's from the chosen generation 
}



return 0;

}