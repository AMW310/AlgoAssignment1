// Assignment1Algo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::ifstream;
using std::ofstream;
using std::endl;
using namespace std;

struct Product {
    int id;
    std::string name;
    double price;
    std::string category;
    Product* next;
};

Product* ReadFile(const std::string& filename)
{
    std::ifstream inStream(filename);

    if (inStream.fail())
    {
        std::cout << "File open Failed. \n";
        exit(1);
        return nullptr;
    }
    
    Product* head = nullptr;
    Product* tail = nullptr;

    std::string line;
    while (std::getline(inStream, line))
    {
        //std::cout << line << std::endl;'

        std::istringstream ss(line);
        

        Product* newProduct = new Product();

        std::string idStr, name, priceStr, category;
        std::getline(ss >> std::ws, idStr, ',');
        std::getline(ss >> std::ws, name, ',');
        std::getline(ss >> std::ws, priceStr, ',');
        std::getline(ss >> std::ws, category, ',');

        newProduct->id = std::stoi(idStr);
        newProduct->name = name;
        newProduct->price = std::stod(priceStr);
        newProduct->category = category;
        newProduct->next = nullptr;

        if (head == nullptr)
        {
            head = newProduct;
            tail = newProduct;
        }
        else
        {
            tail->next = newProduct;
            tail = newProduct;
        }
    }

    inStream.close();
    return head;
}


void Print(Product* head)
{
    Product* current = head;
    while (current != nullptr)
    {
        std::cout << "ID: " << current->id << ", Name: " << current->name << ", Price: " << current->price << ", Category: " << current->category << std::endl;
        current = current->next;
    }
}

void FreeMemory(Product* head)
{
    Product* current = head;
    while (current != nullptr)
    {
        Product* temp = current;
        current = current->next;
        delete temp;
    }
}
void BubbleSort(Product*& head)
{
    if (head == nullptr || head->next == nullptr)
        return;

    bool swapped;
    Product* ptr1;
    Product* lptr = nullptr;

    do
    {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->price > ptr1->next->price)
            {
                std::swap(ptr1->price, ptr1->next->price);
                std::swap(ptr1->id, ptr1->next->id);
                std::swap(ptr1->name, ptr1->next->name);
                std::swap(ptr1->category, ptr1->next->category);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}


Product* InsertAtStart(Product* head, int id, const std::string& name, double price, const std::string category)
{
    Product* newProduct = new Product();
    newProduct->id = id;
    newProduct->name = name;
    newProduct->price = price;
    newProduct->category = category;
    newProduct->next = head;
    return newProduct;
}

Product* Search(Product* head, const std::string& name)
{
    Product* current = head;
    while (current != nullptr)
    {
        if (current->name == name)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void Update(Product* head, int id, const std::string& name, double price, const std::string& category)
{
    Product* current = head;
    while (current != nullptr)
    {
        if (current->id == id)
        {
            current->name = name;
            current->price = price;
            current->category = category;
            return;
        }
        current = current->next;
    }
    std::cout << "Product was not found" << std::endl;
}

void Delete(Product*& head, int id)
{
    Product* current = head;
    Product* prev = nullptr;

    while (current != nullptr && current->id != id)
    {
        prev = current;
        current = current->next;
    }

    if (current != nullptr)
    {
        if (current == nullptr)
        {
            head = current->next;
        }
        else
        {
            prev->next = current->next;
        }
        delete current;
        std::cout << "Product ID" << id << " was deleted." << std::endl;
    }
    else
    {
        std::cout << "Product ID" << id << " was not found." << std::endl;
    }
}

int main()
{
    Product* productList = ReadFile("productdata.txt");

    std::cout << "Product from file Before Bubble Sort" <<std::endl;
    Print(productList);
    std::cout << std::endl;

    BubbleSort(productList);

    std::cout << "Product from file After Bubble Sort" << std::endl;
    Print(productList);
    std::cout << std::endl;

    int pID;
    std::string inName;
    double inPrice;
    std::string inCategory;
    Product* found;

    cin.clear();
    cin.sync();

    //Make switch case for Operation to Perform

    std::cout << "Which Operation Would You Like to Perform:\n1. Insert\n2. Update\n3. Delete\n4. Search\n5. End Program\nEnter a Number: ";
    int choice;
    std::cin >> choice;


    switch (choice)
    {
        case 1:
            std::cout << "Insert New Product ID: ";
            std::cin >> pID;

            std::cout << "Insert New Product Name: " << std::endl;
            std::getline(cin >> std::ws, inName);

            std::cout << "Insert New Product Category: " << std::endl;
            std::getline(cin >> std::ws, inCategory);

            std::cout << "Insert New Product Price: " << std::endl;
            std::cin >> inPrice;

            productList = InsertAtStart(productList, pID, inName, inPrice, inCategory);
            std::cout << "After Inserting and Sorting:" << std::endl;
            BubbleSort(productList);
            Print(productList);
            std::cout << std::endl;
            break;
        case 2:
            std::cout << "Enter the ID: ";
            std::cin >> pID;

            std::cout << "Insert New Product Name: " << std::endl;
            std::getline(cin >> std::ws, inName);

            std::cout << "Insert New Product Category: " << std::endl;
            std::getline(cin >> std::ws, inCategory);

            std::cout << "Insert New Product Price: " << std::endl;
            std::cin >> inPrice;

            Update(productList, pID, inName, inPrice, inCategory);
            BubbleSort(productList);
            Print(productList);
            break;
        case 3:
            std::cout << "Enter the ID: ";
            std::cin >> pID;
            Delete(productList, pID);
            Print(productList);
            break;
        case 4:
            std::cout << "Product Name: ";
            std::getline(cin >> std::ws, inName);

            found = Search(productList, inName);
            if (found != nullptr) {
                std::cout << "Product found: " << "ID: " << found->id << ", Name: " << found->name
                    << ", Price: " << found->price << ", Category: " << found->category << std::endl;
            }
            else {
                std::cout << "Product not found." << std::endl;
            }

            break;
        case 5:
            std::cout << "Ending Program";

        default: std::cout << "None of the Options were chosen";
    }

    

    /* Update
    std::cout << "Enter the ID: ";
    int pID;
    std::cin >> pID;

    std::cout << "Insert New Product Name: " << std::endl;
    std::getline(cin >>std::ws, inName);

    std::cout << "Insert New Product Category: " << std::endl;
    std::getline(cin >> std::ws, inCategory);

    std::cout << "Insert New Product Price: " << std::endl;
    std::cin >> inPrice;

    Update(productList, pID, inName, inPrice, inCategory);
    BubbleSort(productList);
    Print(productList);
    */

    /* Search
    std::cout << "Product Name: ";
    std::getline(std::cin, inName);

    
    Product* found = Search(productList, inName);
    if (found != nullptr) {
        std::cout << "Product found: " << "ID: " << found->id << ", Name: " << found->name
            << ", Price: " << found->price << ", Category: " << found->category << std::endl;
    }
    else {
        std::cout << "Product not found." << std::endl;
    }
    */

    /* Insert
    std::cout << "Insert New Product Name: " << std::endl;
    std::getline(std::cin, inName);

    std::cout << "Insert New Product Category: " << std::endl;
    std::getline(std::cin, inCategory);

    std::cout << "Insert New Product Price: " << std::endl;
    std::cin >> inPrice;

    productList = InsertAtStart(productList, 12545, inName, inPrice, inCategory);
    std::cout << "After Inserting and Sorting:" << std::endl;
    BubbleSort(productList);
    Print(productList);
    std::cout << std::endl;
    */

    FreeMemory(productList);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
