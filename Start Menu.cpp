#include <iostream>
using namespace std;

void search() 
{
    cout << "\n[SEARCH]\n";
}

void abilitySearch() 
{
    cout << "\n[ABILITY SEARCH]\n";
}

void personalLibrary() 
{
    cout << "\n[PERSONAL LIBRARY]\n";
}

void map() 
{
    cout << "\n[MAP]\n";
}

void showMenu() 
{
    cout << "\n=== Pokedex ===" << endl;
    cout << "1. Search" << endl;
    cout << "2. Ability Search" << endl;
    cout << "3. Personal Library" << endl;
    cout << "4. Map" << endl;
    cout << "5. Exit" << endl;
}

int main() 
{
    int choice;
    bool running = true;
    
    while (running) 
	{
        showMenu();
        cin >> choice;
        
        switch (choice) 
		{
            case 1:
                search();
                break;
            case 2:
                abilitySearch();
                break;
            case 3:
                personalLibrary();
                break;
            case 4:
                map();
                break;
            case 5:
                cout << "\nExiting\n";
                running = false;
                break;
            default:
                cout << "\nInvalid option\n";
                break;
        }
    }
    
    return 0;
}
