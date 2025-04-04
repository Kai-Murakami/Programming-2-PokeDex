# include <fstream>
# include "PokemonB.h"
using namespace std;

// constructor, it just passes the generation number inorder to be used to open the text file
Pokemon::Pokemon (string Entered_generation){
    generation = Entered_generation;
    filename = "Generation" + Entered_generation + ".txt";
}

// import data from text file to vectors 
// Import data from text file to vectors using pointers
void Pokemon::import_from_file() {
    ifstream input;
    input.open(filename); // Open the file

    if (input.fail()) { // Check if the file failed to open
        cout << "File does not exist" << endl;
        cout << "Exit program" << endl;
        return;
    }

    
    // Pointers for temporary pokemon storage
    string* Index = new string;
    string* Name = new string;
    string* Type_1 = new string;
    string* Type_2 = new string;
    string* Extra_numbers = new string;

    // Reads data from the text file
    while (!input.eof()) {
        getline(input, *Index, ',');
        vector_index.push_back(*Index);

        getline(input, *Name, ',');
        vector_name.push_back(*Name);

        getline(input, *Type_1, ',');
        vector_Type_1.push_back(*Type_1);

        getline(input, *Type_2, ',');
        vector_Type_2.push_back(*Type_2);

        getline(input, *Extra_numbers);
        vector_Extra_numbers.push_back(*Extra_numbers);
    }
    // deleting the allocated memory to free space
    delete Index;
    delete Name;
    delete Type_1;
    delete Type_2;
    delete Extra_numbers;

    input.close();
    cout << "Data imported successfully." << endl;
}

// the below function finds the specified pokemon and outputs them
void Pokemon::find_pokemon(string Entered_name){
    bool found = false;

    int i;
for (i = 0; i < vector_name.size()-1; ++i){

    if (vector_name.at(i) == Entered_name){
       found = true;
   
   
       if((vector_Type_2.at(i).size()) > 1){
       cout << "Pokemon " << Entered_name << " has two types: its type 1 is " << vector_Type_1.at(i) << " and its type 2 is " << vector_Type_2.at(i) << "." << endl;
     }
     else {
       cout << "Pokemon " << Entered_name << " has only one type 1, and its type 1 is: " << vector_Type_1.at(i) << "." << endl;
     }
   }
   }

   if(!found){
    cout << "Pokemon with the name " << Entered_name << " could not be found in my main library of pokemon's" << endl;
}
}

// this one outputs all the pokemons in the generation 
void Pokemon::filter_by_generation(string generation_u_want_to_filter){
    int i = 0;
    while (i < vector_index.size()-1 ){
        cout << vector_name.at(i) << endl;
        i++;
    }

}


