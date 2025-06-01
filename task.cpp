#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <fstream>
#include <sstream>
#include "List.h"
using namespace std;

class AdminPanel
{
    string username;
    string password;

public:
    AdminPanel() {};

    AdminPanel(string username, string password)
    {
        this->username = username;
        this->password = password;
    }

    string GetUsername() const
    {
        return username;
    }
    string GetPassword() const
    {
        return password;
    }

    DoubleLinkedList<AdminPanel> admins;

    bool SignInAdmin(const string &username, const string &password)
    {

        if (username == "admin" && password == "admin1234")
        {
            cout << "Welcome,Admin!" << endl;
            return true;
        }
        else
        {
            cout << "Admin not found" << endl;
            return false;
        }
    }
};

class User
{
    string username;
    string password;
    string mail;
    int age;

public:
    User()
    {
        this->username = "";
        this->password = "";
        this->mail = "";
        this->age = 0;
        count++;
    }

    User(string username, string password, string mail, int age)
    {
        SetUsername(username);
        SetPassword(password);
        SetMail(mail);
        SetAge(age);
    }

    string GetUsername() const
    {
        return username;
    }

    string GetPassword() const
    {
        return password;
    }

    string GetMail() const
    {
        return mail;
    }

    int GetAge() const
    {
        return age;
    }

    void SetUsername(string username)
    {
        if (username.length() >= 8)
        {
            this->username = username;
        }
        else
        {
            cout << "This username is too short,try again.." << endl;
        }
    }

    void SetPassword(string password)
    {
        if (password.length() >= 8)
        {
            this->password = password;
        }
        else
        {
            cout << "This password is too short,try again.." << endl;
        }
    }

    void SetMail(string mail)
    {
        int len = mail.length();
        if (mail.length() >= 10 && mail.substr(mail.length() - 10) == "@gmail.com")
        {
            this->mail = mail;
        }
        else
        {
            cout << "This mail is not true,try again.." << endl;
        }
    }

    void SetAge(int age)
    {
        if (age > 15)
        {
            cout << "Welcome" << endl;
        }
        else
        {
            cout << "Your age is not suitable fror registration.." << endl;
        }
    }

    DoubleLinkedList<User> users;
    static int count;

public:

void writeToFileuser(const string& filename, const string& username, const string& password, const string& email) {
    ofstream outFile(filename, ios::app);  
    if (!outFile.is_open()) {
        cout << "File can't opened!" << endl;
        return;
    }
    outFile << username << "," << password << "," << email << endl;  
    outFile.close(); 
    cout << "Information write to file successfully!" << endl;
}

void readFromFileuser(const string& filename) {
    ifstream inFile(filename); 
    if (!inFile.is_open()) {
        cout << "File can't opened!" << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {  
        stringstream ss(line);
        string username, password, email;
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, email, ',');
        cout << "Username: " << username << ", Password: " << password << ", Email: " << email << endl;
    }
    inFile.close();
}
    bool SignUpUser(string username, string password, string mail, int age)
    {
        int index = SearchUser(username, password, mail);
        if (index != -1)
        {
            cout << "This username or mail already exists.." << endl;
            return false;
        }
        else
        {
            User *user = new User(username, password, mail, age);
            users.AddEnd(*user);
            writeToFileuser("user_data.txt", username, password,mail);
            return true;
        }
    }
    bool SignInUser(string username, string password, string mail)
    {
        int index = SearchUser(username, password, mail);
        if (index == -1)
        {
            cout << "Welcome to our restaurant!" << endl;
            readFromFileuser("user_data.txt");
            return true;
        }
        else
        {
            cout << "This user not found.." << endl;
            return false;
        }
    }
    void ChangePassword(string username, string password, string mail)
    {
        int index = SearchUser(username, password, mail);
        if (index == -1)
        {
            cout << "This user not found.." << endl;
        }
        else
        {
            users[index].SetPassword(password);
        }
    }
    int SearchUser(string username, string password, string mail)
    {
        for (size_t i = 0; i < users.Size(); i++)
        {
            if (users[i].GetUsername() == username && users[i].GetPassword() == password && users[i].GetMail() == mail)
            {
                return i;
            }
        }
        return -1;
    }


    ~User()
    {
        count--;
    }
};

class Ingredient
{
    string ingredientname;
    float ingredientprice; // gramla
    float ingredientweight_instock;

public:
    Ingredient() {};

    ;
    Ingredient(string ingredientname, float ingredientprice, float ingredientweight_instock)
    {
        SetIngredientName(ingredientname);
        SetIngredientGram(ingredientweight_instock);
        SetIngredientPrice(ingredientprice);
    };

    string GetIngredientName() const
    {
        return ingredientname;
    }

    float GetIngredientGram() const
    {
        return ingredientweight_instock;
    }

    float GetIngredientPrice() const
    {
        return ingredientprice;
    }

    void SetIngredientName(string ingredientname)
    {
        if (ingredientname.length() >= 3)
        {
            this->ingredientname = ingredientname;
        }
        else
        {
            throw string("This ingredient not found");
        }
    }

    void SetIngredientGram(float ingredientweight_instock)
    {
        this->ingredientweight_instock = ingredientweight_instock;
    }

    void SetIngredientPrice(float ingredientprice)
    {
        this->ingredientprice = ingredientprice;
    }

    void StockManage(float weight)
    {
        if (ingredientweight_instock >= weight)
        {
            ingredientweight_instock -= weight;
        }
    }

    float CalculatePrice(float weight)
    {
        return weight * ingredientprice;
    }


    
    ~Ingredient()
    {
    }
};

class Food
{
    string foodname;
    string fooddescription;
    float foodprice;
    string foodingredient;

public:
    vector<Ingredient> ingredients;
    Food(string foodname, string fooddescription, float foodprice)
        : foodname(foodname), fooddescription(fooddescription), foodprice(foodprice)
    {
    }

    Food() {};

    Food(string foodname, string fooddescription, float foodprice, string foodingredient)
    {
        SetName(foodname);
        SetDescription(fooddescription);
        SetPrice(foodprice);
        SetFoodIngredient(foodingredient);
    }

    string GetFoodName() const
    {
        return foodname;
    }
    string GetFoodDescription() const
    {
        return fooddescription;
    }
    float GetFoodPrice() const
    {
        return foodprice;
    }
    string GetFoodIngredient() const
    {
        return foodingredient;
    }

    void SetName(string foodname)
    {
        this->foodname = foodname;
    }

    void SetDescription(string fooddescription)
    {
        if (fooddescription.length() >= 15)
        {
            this->fooddescription = fooddescription;
        }
        else
        {
            throw string("This description is short..");
        }
    }

    void SetPrice(float foodprice)
    {
        this->foodprice = foodprice;
    }
    void SetFoodIngredient(string foodingredient)
    {
        this->foodingredient = foodingredient;
    }

    void AddIngredientToDish(Ingredient &ingredient, float weight, int ingredientcount)
    {
        if (ingredient.GetIngredientGram() >= weight)
        {
            float ingredientPrice = ingredient.CalculatePrice(weight);
            foodprice += ingredientPrice;
            ingredients.push_back(ingredient);

            cout << "Ingredient added to your dish successfully" << endl;
        }
        else
        {
            cout << "We do not have enough of this ingredient in stock. Available: "
                 << ingredient.GetIngredientGram() << " grams." << endl;
        }

    }

    void ShowNewFood()
    {
        cout << "_________________________________________" << endl;
        cout << "Food name: " << foodname << endl;
        cout << "Food description: " << fooddescription << endl;
        cout << "Food price: " << foodprice << endl;
        cout << "Food ingredients: " << foodingredient << endl;
        cout << "____________________________________" << endl;
    }

    void writeToFileFood(const string& filename, const vector<Food>& foods) {
        ofstream outFile(filename, ios::app);
        if (!outFile.is_open()) {
            cout << "File can't opened!" << endl;
            return;
        }
    
        outFile << foodname << "," << fooddescription << "," << foodprice << endl << "," << foodingredient << endl;  // Fayla məlumat yazırıq
        outFile.close(); 
        cout << "Information write to file successfully!" << endl;
    }
    
    void readFromFileFood(const string& filename) {
        ifstream inFile(filename);  
        if (!inFile.is_open()) {
            cout << "File can't opened!" << endl;
            return;
        }
    
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string name, description;
            float price;
            getline(ss, name, ',');
            getline(ss, description, ',');
            ss >> price;
    
            cout << "Food Name: " << name << ", Description: " << description << ", Price: " << price << endl;
        }
    
        inFile.close();
    }

    ~Food()
    {
    }
};

class Budget
{
    float budget;  // restoranin budcesi
    float revenue; // gelir
    float expense; // xerc
public:
    Budget(float budget = 1000, float revenue = 0, float expense = 0)
    {
        this->budget = budget;
        this->revenue = revenue;
        this->expense = expense;
    }

    float GetBudget() const
    {
        return budget;
    }
    float GetRevenue() const
    {
        return revenue;
    }
    float GetExpense() const
    {
        return expense;
    }

    void SetBudget(float budget)
    {
        this->budget = budget;
    }
    void SetRevenue(float revenue)
    {
        this->revenue = revenue;
    }
    void SetExpense(float expense)
    {
        this->expense = expense;
    }

    void AddRevenue(float money)
    {
        if (money > 0)
        {
            revenue += money;
            budget += money;
        }
    }

    void AddExpense(float money)
    {
        if (money > 0 && money <= budget)
        {
            expense += money;
            budget -= money;
        }
        else
        {
            cout << "We don't have enough budget for expense" << endl;
        }
    }

    void CalculateBalance() const
    {
        float balance = revenue - expense;
        cout << "Balance: " << balance << "$" << endl;
    }

    void ShowStatic() const
    {
        cout << "Restaurant budget: " << budget << endl;
        cout << "Revenue: " << revenue << endl;
        cout << "Expense: " << expense << endl;
    }

    ~Budget()
    {
    }
};

class Restaurant
{
    string name;
    DoubleLinkedList<Food> menu;
    DoubleLinkedList<Ingredient> ingredients;

public:
    DoubleLinkedList<Food> &GetMenu()
    {
        return menu;
    }
    Restaurant() {};
    Restaurant(string name)
    {
        this->name = name;
    }

    void AddFood(string newfoodname, string fooddescription, float newfoodprice, string foodingredient)
    {
        int index = SearcFood(newfoodname);
        if (index == -1)
        {
            menu.AddEnd(Food(newfoodname, fooddescription, newfoodprice, foodingredient));
        }
        else
        {
            throw string("This food has already exist..");
        }
    }
    void DeleteFood(const string &name)
    {
        int index = SearcFood(name);
        if (index == -1)
        {
            throw string("This food does not exist..");
        }
        else
        {
            menu.DeleteIndex(index);
        }
    }
    int SearcFood(string name)
    {
        for (size_t i = 0; i < menu.Size(); i++)
        {
            if (menu[i].GetFoodName() == name)
            {
                return i;
            }
        }
        return -1;
    }
    void ChangeFoodName(string oldfoodname, string NewFoodName)
    {
        int index = SearcFood(oldfoodname);
        if (index != -1)
        {
            menu[index].SetName(NewFoodName);
        }
        else
        {
            throw string("This food does not exist..");
        }
    }

    void AddIngredienToStock(const Ingredient &ingredient)
    {
        ingredients.AddEnd(ingredient);
    }

    Ingredient *SearcIngredient(const string &name)
    {
        for (size_t i = 0; i < ingredients.Size(); i++)
        {
            if (ingredients[i].GetIngredientName() == name)
            {
                return &ingredients[i];
            }
        }
        return nullptr;
    }

    void ShowAllIngredients()
    {
        cout << "====== INGREDIENTS ======" << endl;
        cout << "Ingredients in stock " << endl
             << endl;
        for (size_t i = 0; i < ingredients.Size(); i++)
        {
            cout << "Ingredient Name: " << ingredients[i].GetIngredientName() << endl;
            cout << "Ingredient Price: " << ingredients[i].GetIngredientPrice() << " cent for gram " << endl;
            cout << "In stock we have " << ingredients[i].GetIngredientGram() << " gram " << endl;
            cout << "_________________________________________" << endl;
        }
    }

    void ShowMenu()
    {
        cout << "====== MENU ======" << endl;
        for (size_t i = 0; i < menu.Size(); i++)
        {
            menu[i].ShowNewFood();
        }
    }

    void DeleteIngredient(const string &name)
    {
        for (size_t i = 0; i < ingredients.Size(); ++i)
        {
            if (ingredients[i].GetIngredientName() == name)
            {
                ingredients.DeleteIndex(i);
                cout << "Ingredient deleted" << endl;
                return;
            }
        }
        cout << "Ingredient not found" << endl;
    }



    ~Restaurant()
    {
    }
};

class Cart
{
    vector<Food> items;
    vector<int> quantity;
    float totalPrice;
    float totalBudget = 1000;

public:
    void AddItem(const Food &food, int quantity2)
    { // sebete mehsul elave edir
        for (size_t i = 0; i < items.size(); i++)
        {
            if (items[i].GetFoodName() == food.GetFoodName())
            {
                quantity[i] += quantity2;
                totalPrice += food.GetFoodPrice() * quantity2;
                return;
            }
        }
        items.push_back(food);
        quantity.push_back(quantity2);
        totalPrice += food.GetFoodPrice() * quantity2;
    }

    void RemoveItem(string &foodname)
    { // sebetden mehsul sil
        for (size_t i = 0; i < items.size(); i++)
        {
            if (items[i].GetFoodName() == foodname)
            {
                totalPrice -= items[i].GetFoodPrice() * quantity[i];
                items.erase(items.begin() + i);
                quantity.erase(quantity.begin() + i);
                CalculateTotalPrice();
                return;
            }
        }
        cout << "Food not found in your cart" << endl;
    }

    void UpdateQuantity(const string &foodname, int newQuantity)
    {
        for (size_t i = 0; i < items.size(); i++)
        {
            if (items[i].GetFoodName() == foodname)
            {
                totalPrice -= items[i].GetFoodPrice() * quantity[i];
                quantity[i] = newQuantity;
                totalPrice += items[i].GetFoodPrice() * quantity[i];
                return;
            }
        }
        cout << "Food not found in your cart" << endl;
    }
    void CalculateTotalPrice()
    {
        totalPrice = 0;
        for (size_t i = 0; i < items.size(); i++)
        {
            totalPrice += items[i].GetFoodPrice() * quantity[i];
        }
    }
    void ShowCart()
    {
        cout << "Items in cart: " << endl;
        for (size_t i = 0; i < items.size(); i++)
        {
            cout << "Foodname: " << items[i].GetFoodName() << endl;
            cout << "Quantity: " << quantity[i] << endl;
            cout << "Food price: " << items[i].GetFoodPrice() << endl;
        }
        cout << "Total price: " << totalPrice << "$" << endl;
    }

    void ReduceBudget() {
        if (totalBudget >= totalPrice) {
            totalBudget -= totalPrice;
            cout << "Budget reduced by: " << totalPrice << ", New Budget: " << totalBudget << endl;
        } else {
            cout << "Not enough budget for these items!" << endl;
        }
    }
    
    void CleanCart()
    {
        items.clear();
        quantity.clear();
        totalPrice = 0;
    }

    void writeToFileCart(const string &filename)
    {
        ofstream outFile(filename, ios::app); // Open file in append mode
        if (!outFile.is_open())
        {
            cout << "File can't opened!" << endl;
            return;
        }

        for (size_t i = 0; i < items.size(); i++)
        {
            outFile << items[i].GetFoodName() << ","  
                    << items[i].GetFoodPrice() << "," 
                    << quantity[i] << "\n";      
        }
        outFile << "Total Price: " << totalPrice << "\n"; 
        outFile << "Remaining Budget: " << totalBudget << "\n";
        outFile.close();

        cout << "Information written to file successfully!" << endl;
    }


    void readFromFileCart(const string &filename)
    {
        ifstream inFile(filename);
        if (!inFile.is_open())
        {
            cout << "File can't opened!" << endl;
            return;
        }

        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string foodname;
            float foodprice;
            int qty;
            getline(ss, foodname, ',');
            ss >> foodprice;
            ss.ignore(); 
            ss >> qty;

            cout << "Food name: " << foodname << ", Price: " << foodprice << ", Quantity: " << qty << endl;
        }

        inFile.close();
    }
};

int User::count = 0;

int main()
{

    AdminPanel admin;
    User user;

    Budget budget;
    Cart cart;


    Restaurant restaurant;
    Ingredient *cheese = new Ingredient("cheese", 0.5, 4000);
    Ingredient *potato = new Ingredient("potato", 0.7, 5000);
    Ingredient *tomato = new Ingredient("tomato", 0.3, 2000);
    Ingredient *olive = new Ingredient("olive", 0.7, 2500);

    restaurant.AddIngredienToStock(*cheese);
    restaurant.AddIngredienToStock(*potato);
    restaurant.AddIngredienToStock(*tomato);
    restaurant.AddIngredienToStock(*olive);

    Food *pizza = new Food("pizza", "this pizza has three size", 20, "cheese,mashroom,tomato");
    Food *pasta = new Food("pasta", "add extra cheese for pasta", 15, "tomato,souse");
    Food *burger = new Food("burger", "this burger has two types", 12, "meat,cheese,greens");
    Food *salad = new Food("salad", "this salad has very healthy ingredients", 17, "chicken,olive,greens");

    restaurant.AddFood(pizza->GetFoodName(), pizza->GetFoodDescription(), pizza->GetFoodPrice(), pizza->GetFoodIngredient());
    restaurant.AddFood(pasta->GetFoodName(), pasta->GetFoodDescription(), pasta->GetFoodPrice(), pasta->GetFoodIngredient());
    restaurant.AddFood(burger->GetFoodName(), burger->GetFoodDescription(), burger->GetFoodPrice(), burger->GetFoodIngredient());
    restaurant.AddFood(salad->GetFoodName(), salad->GetFoodDescription(), salad->GetFoodPrice(), salad->GetFoodIngredient());

    while (true)
    {
        int choice;
        cout << "1. Admin panel or 2. User Panel: ";
        cin >> choice;
        if (choice == 1)
        {
            vector<Food> foods;
            cout << "Admin panel selected" << endl;

            string username;
            string password;

            cout << "Enter username: ";
            cin.ignore();
            getline(cin, username);

            cout << "Enter password: ";
            getline(cin, password);

            if (admin.SignInAdmin(username, password))
            {

                while (true)
                {

                    int choice;
                    cout << "1. Add new food" << endl;
                    cout << "2. Add new ingredient to food" << endl;
                    cout << "3. Add new ingredient to stock" << endl;
                    cout << "4. Delete ingredient" << endl;
                    cout << "5. Delete food" << endl;
                    cout << "6. Show Menu" << endl;
                    cout << "7. Show all ingredients" << endl;
                    cout << "8. Show static" << endl;
                    cout << "9. Exit" << endl;
                    cout << "Choose: ";
                    cin >> choice;
                    cin.ignore();
                    if (choice == 1)
                    {

                        string foodname;
                        cout << "Enter new food name: ";
                        getline(cin, foodname);

                        string fooddescription;
                        cout << "Enter food description: ";
                        getline(cin, fooddescription);

                        float foodprice;
                        cout << "Enter price: ";
                        cin >> foodprice;
                        cin.ignore();

                        string foodingredient;
                        cout << "Enter food ingredient: ";
                        getline(cin, foodingredient);

                        Food newfood(foodname, fooddescription, foodprice, foodingredient);
                        restaurant.AddFood(newfood.GetFoodName(), newfood.GetFoodDescription(), newfood.GetFoodPrice(), newfood.GetFoodIngredient());

                        newfood.ShowNewFood();

                        newfood.writeToFileFood("foods.txt",foods);
                        newfood.readFromFileFood("foods.txt");
                    }

                    if (choice == 2)
                    {

                        string ingredientname;
                        cout << "Enter ingredient name: ";
                        getline(cin, ingredientname);

                        float ingredientgram;
                        cout << "Enter ingredient gram: ";
                        cin >> ingredientgram;

                        float ingredientprice;
                        cout << "Enter price: ";
                        cin >> ingredientprice;

                        Ingredient newingredient(ingredientname, ingredientgram, ingredientprice);
                        restaurant.AddIngredienToStock(newingredient);

                        int ingredientcount;
                        cout << "Enter the count of ingredient which you want to add your food : ";
                        cin >> ingredientcount;
                        cin.ignore();

                        string foodname;
                        cout << "Enter the food name you want to add ingredient to: ";
                        getline(cin, foodname);

                        Food *food = nullptr;

                        if (food == nullptr)
                        {
                            cout << "Food not found in menu!" << endl;
                        }
                        for (size_t i = 0; i < ingredientcount; i++)
                        {
                            string ingredient_name;
                            cout << "Enter ingredient name: ";
                            cin >> ingredient_name;

                            Ingredient *findingredient = restaurant.SearcIngredient(ingredient_name);
                            if (findingredient == nullptr)
                            {
                                cout << "Sorry,but this ingredient not fount in stock,choose other ingredient.." << endl;
                            }
                            else
                            {
                                float weight;
                                cout << "Enter the weight of ingredient which you want to add: ";
                                cin >> weight;
                                void AddIngredientToDish(Ingredient & ingredient, float weight, int ingredientcount);
                            }
                        }
                    }

                    else if (choice == 3)
                    {
                        string new_ingredient_name;
                        cout << "Enter new ingredient name: ";
                        getline(cin, new_ingredient_name);

                        float new_ingredient_price;
                        cout << "Enter new ingredient price: ";
                        cin >> new_ingredient_price;

                        float new_ingredient_gram;
                        cout << "Enter new ingredient gram: ";
                        cin >> new_ingredient_gram;

                        try
                        {
                            Ingredient newIngredient(new_ingredient_name, new_ingredient_price, new_ingredient_gram);
                            restaurant.AddIngredienToStock(newIngredient);
                            cout << "New ingredient added successfully!" << endl;
                        }
                        catch (const string &ex)
                        {
                            cout << "Error" << ex << endl;
                        }
                    }

                    else if (choice == 4)
                    {
                        string deletename;
                        cout << "Enter ingredient name which you want to delete: ";
                        getline(cin, deletename);
                        restaurant.DeleteIngredient(deletename);
                        cout << "New version of ingredient list: " << endl;
                        restaurant.ShowAllIngredients();
                    }

                    else if (choice == 5)
                    {
                        string deletefood;
                        cout << "Enter food name which you want to delete: ";
                        getline(cin, deletefood);
                        restaurant.DeleteFood(deletefood);
                        cout << "New version of menu: " << endl;
                        restaurant.ShowMenu();
                    }

                    else if (choice == 6)
                    {
                        restaurant.ShowMenu();
                        
                    }
                    else if (choice == 7)
                    {
                        restaurant.ShowAllIngredients();
                    }

                    else if (choice == 9)
                    {
                        cout << "Exit from admin page!!" << endl;
                    }
                    else
                    {
                        cout << "Wrong input " << endl;
                    }
                }
            }
        }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        else if (choice == 2)
        {

            int userChoice;
            cout << "Hello user! Choose:  " << endl;
            cout << "1. Sign In or 2. Sign Up: ";
            cin >> userChoice;
            cin.ignore();

            if (userChoice == 1)
            {
                cout << "User Sign In: " << endl;
                string username, password, mail;
                cout << "Enter username: ";
                getline(cin, username);

                cout << "Enter password: ";
                getline(cin, password);

                cout << "Enter mail: ";
                getline(cin, mail);

                if (user.SignInUser(username, password, mail)){
                    while (true)
                    {
                        int choose;
                        cout << "1. Show menu " << endl;
                        cout << "2. Add to cart" << endl;
                        cout << "3. Remove from cart" << endl;
                        cout << "4. Make a payment " << endl;
                        cout << "5. Money now" << endl;
                        cout << "6. Show cart" << endl;
                        cout << "7. Exit" << endl;
                        cout << "Choose: " << endl;
                        cin >> choose;
                        cin.ignore();

                        if (choose == 1)
                        {
                            cout << "Menu" << endl;
                            restaurant.ShowMenu();
                        }
                        else if (choose == 2)
                        {

                            cout << "Menu:" << endl;
                            restaurant.ShowMenu();

                            string foodname;
                            cout << "Enter the foodname which you want to add your cart: ";
                            getline(cin, foodname);

                            int found_food = restaurant.SearcFood(foodname);
                            if (found_food == -1)
                            {
                                cout << "This food don't exist in our menyu: ";
                            }
                            else
                            {
                                int quantity;
                                cout << "Enter count of food which you want to add to your cart: ";
                                cin >> quantity;
                                cin.ignore();

                                int choose_extra_ingredient;
                                cout << "Do you want to add an extra ingredient? " << endl;
                                cout << "If you want choose 1 or if you don't want choose 2: " << endl;
                                cin >> choose_extra_ingredient;
                                cin.ignore();

                                if (choose_extra_ingredient == 1)
                                {
                                    string ingredient_name;
                                    cout << "Enter ingredient name: ";
                                    getline(cin, ingredient_name);

                                    float weight;
                                    cout << "Enter the weight of ingredient(with gram): ";
                                    cin >> weight;
                                    cin.ignore();

                                    Ingredient *ingredient = restaurant.SearcIngredient(ingredient_name);
                                    if (ingredient != nullptr)
                                    {
                                        Food &food = restaurant.GetMenu()[found_food];
                                        food.AddIngredientToDish(*ingredient, weight, quantity);
                                        cart.AddItem(food, quantity);
                                        cart.ShowCart();
                                        cout << "__________________________________________________________________________" << endl;

                                        cout << "Would you like to add something else? (1 for yes, 2 for no): " << endl;
                                        cout << "if you want choose 1 if you don't want choose 2: " << endl;

                                        int AddMore;
                                        cin >> AddMore;
                                        cin.ignore();

                                        if (AddMore == 2)
                                        {
                                            cout << "Exit..." << endl;
                                        }
                                        else if (AddMore == 1)
                                        {
                                            continue;
                                        }
                                        else
                                        {
                                            cout << "Wrong input..." << endl;
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        cout << "Ingredient not found!" << endl;
                                    }
                                }
                                else if (choose_extra_ingredient == 2)
                                {
                                    Food &food = restaurant.GetMenu()[found_food];
                                    cart.AddItem(food, quantity);

                                    cart.ShowCart();
                                    cout << "__________________________________________________________________________" << endl;

                                    cout << "Would you like to add something else? (1 for yes, 2 for no): " << endl;
                                    int AddMore;
                                    cin >> AddMore;
                                    cin.ignore();

                                    if (AddMore == 2)
                                    {
                                        cout << "Exit..." << endl;
                                    }
                                    else if (AddMore == 1)
                                    {
                                        continue;
                                    }
                                    else
                                    {
                                        cout << "Wrong input..." << endl;
                                        break;
                                    }
                                }
                                else
                                {
                                    cout << "Wrong input!" << endl;
                                }
                            }
                        }
                        else if (choose == 3)
                        {
                            cout << "Menu: " << endl;
                            restaurant.ShowMenu();

                            string foodname;
                            cout << "Enter the foodname which you want to remove from cart: ";
                            getline(cin, foodname);

                            int found_food = restaurant.SearcFood(foodname);
                            if (found_food == -1)
                            {
                                cout << "This food don't exist in our menyu: ";
                            }
                            else
                            {

                                Cart cart;
                                cart.RemoveItem(foodname);
                                cart.ShowCart();

                                cout << "Do you want to remove something else? " << endl;
                                cout << "If you want click 1 if you don't want click 2" << endl;
                                int removefood;
                                cin >> removefood;
                                cin.ignore();

                                if (removefood == 1)
                                {
                                    continue;
                                }
                                else if (removefood == 2)
                                {
                                    break;
                                }
                                else
                                {
                                    cout << "wrong input" << endl;
                                }
                            }
                        }
                        else if (choose == 4)
                        {
                            cart.ShowCart();
                        }
                        else if (choose == 5)
                        {
                            cart.ReduceBudget();
                            cart.readFromFileCart("cart_data.txt");
                            cart.writeToFileCart("cart_data.txt");
                        }
                        else if (choose == 6)
                        {
                            cart.ShowCart();
                        }
                        else if (choose == 7)
                        {
                            cout << "Exit from user page.." << endl;
                        }

                        else
                        {
                            cout << "Wrong input.." << endl;
                        }
                    }
                }
            }
            else if (userChoice == 2)
            {

                cout << " If you don't have an account Sign Up: " << endl;
                string username, password, mail;
                int age;
                cout << "Enter age: ";
                cin >> age;
                cin.ignore();

                cout << "Enter username: ";
                getline(cin, username);

                cout << "Enter password: ";
                getline(cin, password);

                cout << "Enter mail: ";
                getline(cin, mail);

                if (user.SignUpUser(username, password, mail, age))
                
                {
                    while (true)
                    {
                        int choose;
                        cout << "1. Show menu " << endl;
                        cout << "2. Add to cart" << endl;
                        cout << "3. Remove from cart" << endl;
                        cout << "4. Make a payment " << endl;
                        cout << "5. Money now" << endl;
                        cout << "6. Show cart" << endl;
                        cout << "7. Exit" << endl;
                        cout << "Choose: " << endl;
                        cin >> choose;
                        cin.ignore();

                        if (choose == 1)
                        {
                            cout << "Menu" << endl;
                            restaurant.ShowMenu();
                        }
                        else if (choose == 2)
                        {

                            cout << "Menu:" << endl;
                            restaurant.ShowMenu();

                            string foodname;
                            cout << "Enter the foodname which you want to add your cart: ";
                            getline(cin, foodname);

                            int found_food = restaurant.SearcFood(foodname);
                            if (found_food == -1)
                            {
                                cout << "This food don't exist in our menyu: ";
                            }
                            else
                            {
                                int quantity;
                                cout << "Enter count of food which you want to add to your cart: ";
                                cin >> quantity;
                                cin.ignore();

                                int choose_extra_ingredient;
                                cout << "Do you want to add an extra ingredient? " << endl;
                                cout << "If you want choose 1 or if you don't want choose 2: " << endl;
                                cin >> choose_extra_ingredient;
                                cin.ignore();

                                if (choose_extra_ingredient == 1)
                                {
                                    string ingredient_name;
                                    cout << "Enter ingredient name: ";
                                    getline(cin, ingredient_name);

                                    float weight;
                                    cout << "Enter the weight of ingredient(with gram): ";
                                    cin >> weight;
                                    cin.ignore();

                                    Ingredient *ingredient = restaurant.SearcIngredient(ingredient_name);
                                    if (ingredient != nullptr)
                                    {
                                        Food &food = restaurant.GetMenu()[found_food];
                                        food.AddIngredientToDish(*ingredient, weight, quantity);
                                        cart.AddItem(food, quantity);
                                        cart.ShowCart();
                                        cout << "__________________________________________________________________________" << endl;

                                        cout << "Would you like to add something else? (1 for yes, 2 for no): " << endl;
                                        cout << "if you want choose 1 if you don't want choose 2: " << endl;

                                        int AddMore;
                                        cin >> AddMore;
                                        cin.ignore();

                                        if (AddMore == 2)
                                        {
                                            cout << "Exit..." << endl;
                                        }
                                        else if (AddMore == 1)
                                        {
                                            continue;
                                        }
                                        else
                                        {
                                            cout << "Wrong input..." << endl;
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        cout << "Ingredient not found!" << endl;
                                    }
                                }
                                else if (choose_extra_ingredient == 2)
                                {
                                    Food &food = restaurant.GetMenu()[found_food];
                                    cart.AddItem(food, quantity);

                                    cart.ShowCart();
                                    cout << "__________________________________________________________________________" << endl;

                                    cout << "Would you like to add something else? (1 for yes, 2 for no): " << endl;
                                    int AddMore;
                                    cin >> AddMore;
                                    cin.ignore();

                                    if (AddMore == 2)
                                    {
                                        cout << "Exit..." << endl;
                                    }
                                    else if (AddMore == 1)
                                    {
                                        continue;
                                    }
                                    else
                                    {
                                        cout << "Wrong input..." << endl;
                                        break;
                                    }
                                }
                                else
                                {
                                    cout << "Wrong input!" << endl;
                                }
                            }
                        }
                        else if (choose == 3)
                        {
                            cout << "Menu: " << endl;
                            restaurant.ShowMenu();

                            string foodname;
                            cout << "Enter the foodname which you want to remove from cart: ";
                            getline(cin, foodname);

                            int found_food = restaurant.SearcFood(foodname);
                            if (found_food == -1)
                            {
                                cout << "This food don't exist in our menyu: ";
                            }
                            else
                            {

                                Cart cart;
                                cart.RemoveItem(foodname);
                                cart.ShowCart();

                                cout << "Do you want to remove something else? " << endl;
                                cout << "If you want click 1 if you don't want click 2" << endl;
                                int removefood;
                                cin >> removefood;
                                cin.ignore();

                                if (removefood == 1)
                                {
                                    continue;
                                }
                                else if (removefood == 2)
                                {
                                    break;
                                }
                                else
                                {
                                    cout << "wrong input" << endl;
                                }
                            }
                        }
                        else if (choose == 4)
                        {
                            cart.ShowCart();
                        }
                        else if (choose == 5)
                        {
                            cart.readFromFileCart("cart_data.txt");
                            cart.writeToFileCart("cart_data.txt");
                            cart.ReduceBudget();
                        }
                        else if (choose == 6 )
                        {
                            cart.ShowCart();
                        }
                        else if (choose == 7)
                        {
                            cout << "Exit from user page.." << endl;
                        }

                        else
                        {
                            cout << "Wrong input.." << endl;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
