# include <iostream>
# include <iomanip>
# include <vector>
# include <string>
using namespace std;

# ifndef POKEMON_H
# define POKEMON_H


class Pokemon {
    public:
    Pokemon (string Entered_generation);       // constructor 
    void import_from_file();                  // imports data from file 
    void find_pokemon(string Entered_name);  // it finds pokemon from the imported data
    void filter_by_generation(string generation_u_want_to_filter);  // outputs all pokemons in the choosen generation 

    private:

    string generation;
    string filename;
  
    // declaring variables to be used with the vectors 
    string Index;
    string Name;
    string Type_1;
    string Type_2;
    string Extra_numbers;

    // the below are vectors were the data from the text file is gonna be stored temporarly
    vector<string> vector_index;
    vector<string> vector_name;
    vector<string> vector_Type_1;
    vector<string> vector_Type_2;
    vector<string> vector_Extra_numbers;
    
};

#endif