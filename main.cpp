#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
using namespace std;

//Function prototypes
void foodFeedback(string name, int takeAway, char add);
bool searchFood(string name);
void loadFood(vector<string>&);
void outloadfood();
void loadCost(vector<int>&);
void menu();
void intro();
double costCounter(string food_choice);

const int owner_secretKey{1777};
vector<string> menu_List;
vector<int> costs;

int main() {
    string customerName;
    bool correct = false;
    char allow_modification;
    int owner_varification;
    string food_choice;
    int tE_option;
    char more_items;
    static int totalCost;
    int checker{1};

    //Ensure price is to 2dps
    cout << fixed << showpoint << setprecision(2);

    //Loading food from the FoodStore to the menu list
    loadFood(menu_List);
    //Loading costs from the FoodPrices text file
    loadCost(costs);

    intro();
    cin >> customerName;

    //Advanced owner options

    cout << "Only the restaurant owner can ";
    cout << "use this option!" << endl;

    cout << "Would You Want To Access These Advanced Options: ";
    cin >> allow_modification;
    while (allow_modification == 'y') {
        cout << "\nEnter The Security Pin: ";
        cin >> owner_varification;

        if (owner_varification == owner_secretKey) {
            break;
        }
        else if (owner_varification != owner_secretKey) {
            cout << "! Access Denied !" << endl;
            exit(0);
        }
    }

    //display the food menu
    cout << endl;
    menu();

    //Prompt customer to input item
    cout << "Dear " << customerName << " what do you want today?" << endl;
    cout << "ENTER FOOD: ";

    do {
        cin >> food_choice;

        totalCost = costCounter(food_choice);

        if (checker > 1) {
            totalCost = totalCost + costCounter(food_choice);
        }

        cout << "Would you wish to have it from here, or to take away?" << endl;
        cout << "1. HAVE IT FROM RESTAURANT"  << endl;
        cout << "2. TAKE AWAY" << endl;
        cout << "___";
        cin >> tE_option;
        if (tE_option < 1 || tE_option > 2 ) {
            cout << "Invalid input!" << endl;
            cout << "___";
            cin >> tE_option;
        }

        foodFeedback(food_choice, tE_option, allow_modification);

        cout << "Would you like to order more items(y/n)? ";
        cin >> more_items;
        if (more_items == 'y') {
            cout << "\nENTER ANOTHER ITEM" << endl;
            checker++;
        }
        

    } while(more_items == 'y');
   
    //Display receipt 
    cout << "\nDear " << customerName << ", below is your receipt" << endl;
    cout << setw(4) << "ITEMS BOUGHT: " << checker << endl;
    cout << setw(4) << "TOTAL PRICE: " << "Shs." << totalCost << endl;


    cout << "Thank you for your loyalty, come back next time." << endl;





    return 0;
}

void foodFeedback(string foodInput, int takeAway, char add) {
    bool food;
    string new_item;

    ofstream outputfile;
    outputfile.open("FoodStore.txt");
    //Refresh the foodStore to avoid item delation
    outloadfood();

    //Implements the searchFood function
    food = searchFood(foodInput);
    if (food) {
        if (takeAway == 2) {
            cout << foodInput << " has been added to your chart!" << endl; 
        }
        else if (takeAway == 1) {
            cout << foodInput << " is added to your table, bon apetite!" << endl;
        }
    }
    else if (!food) {
        if (owner_secretKey == 1777 && add == 'y') {
            cout << "Enter the item to add to the FoodStore " << endl;
            cin >> new_item;
            //Add item to the FoodStore file
            outputfile << new_item << endl;
            //Update the menu List at runtime
            loadFood(menu_List);
        }
        else {
            cout << "Sorry, item not on our FoodStore!" << endl;
        }

    }

}

bool searchFood(string name) {
    bool found = false;

    //Using the linear search algorithm to find food in the store
    for (int index = 0; index < menu_List.size(); index++ ) {
        if (!found) {
            if (menu_List[index] == name) {
                found = true;
            }
        }
    }
    return found;
}

void loadFood(vector<string>& menu_List) {
    string temp_foodStore;
    ifstream inputfile;
    inputfile.open("FoodStore.txt");

    //Adding items in the FoodStore to the food store
    while (inputfile) {
        inputfile >> temp_foodStore;
        menu_List.push_back(temp_foodStore);
    }

}
void loadCost(vector<int>& costs) {
    int temp_costStore;
    ifstream inputfile;
    inputfile.open("FoodPrices.txt");

    //Adding costs in the foodPrices to the costs vector
    while(inputfile) {
        inputfile >> temp_costStore;
        costs.push_back(temp_costStore);
    }
}

void intro() {
    cout << "DEAR CUSTOMER, WELCOME TO FAST RESTFOODS\n" << endl;
    cout << "Before we proceed, ";
    cout << "we would like to know your name." << endl;
    
    cout << "ENTER YOUR NAME: ";
}

double costCounter(string food_choice) {
    int costlocation;
    int keepPrice;
    ifstream food_inputfile;
    food_inputfile.open("FoodPrices.txt");

    for(int index = 0; index < menu_List.size(); index++) {
        if (menu_List[index] == food_choice) {
            costlocation = index;
        }
    }
    for (int index = 0; index < costs.size(); index++ ) {
        if(index == costlocation) {
            keepPrice = costs[index];
        }
    }
    return keepPrice;
}

void menu() {
    cout << setw(20) << "MENU" << endl;
    for (int index = 0; index < menu_List.size(); index++) {
        cout << setw(10) <<  menu_List[index];
        cout << setw(5) << ".............." << setw(5) << "Shs.";
        cout << costCounter(menu_List[index]) << endl;  
    }
}
void outloadfood() {
    string tempHold;
    ofstream loadout;
    loadout.open("FoodStore.txt");

    for(int index = 0; index < menu_List.size(); index++) {
        tempHold = menu_List[index];
        loadout << tempHold << endl;
    }
}