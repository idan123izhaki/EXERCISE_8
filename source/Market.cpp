#include <iostream>
#include <map>
#include <vector>
#include <limits>
#include "Item.hpp"
#include "Customer.hpp"

void initList(std::vector<Item>&);
void printListItem(std::vector<Item>&);
void addItemsToList(Customer&, std::vector<Item>&);
void printCustomerList(const std::set<Item>);
void removeItemsFromList(Customer&, std::vector<Item>&);

int main()
{
	std::vector<Item> itemList;
	initList(itemList);
	std::map <std::string, Customer> abcCustomers;
	std::map <std::string, Customer>::iterator it;
	std::multimap<double, Customer, std::greater<double>> multimapSum;
	std::multimap <double, Customer, std::greater<double>>::iterator multiIt;
	int option, action;
	std::string name;
	bool whileFlag = true;
	//sets the exception state for the std::cin stream.
	std::cin.exceptions(std::ios_base::failbit);

	while (whileFlag)
	{
		try
		{
			std::cout << "Welcome to MagshiMart!"
				"\n1. to sign as customer and buy items"
				"\n2. to update existing customer's items"
				"\n3. to print the customer who pays the most"
				"\n4. to exit" << std::endl;
			std::cout << "Your choise: "; std::cin >> option;
			switch (option)
			{
			case 1:
				std::cout << "Please enter your name: "; std::cin >> name;
				it = abcCustomers.find(name);
				if (it != abcCustomers.end())
				{
					std::cout << "\nThere is a customer with this name!\n" << std::endl;
					break;
				}
				else
				{
					Customer* customerPtr = new Customer(name);
					std::cout << "\nWelcome " << name << " into our SuperMarket!";
					addItemsToList(*customerPtr, itemList);
					abcCustomers.insert({ name, *customerPtr });
				}
				break;

			case 2:
				std::cout << "Hello! please enter your name: "; std::cin >> name;
				it = abcCustomers.find(name);
				if (it == abcCustomers.end())
				{
					std::cout << "There is not customer with this name... try to register...\n" << std::endl;
					break;
				}
				else
				{
					std::cout << "\nHello " << name << "!\ngood to see you again.\nHere are all the items you have purchased:" << std::endl;
					printCustomerList(it->second.getItems());
					std::cout << "What action would you like to take?" << std::endl;
					std::cout << "1. Add items"
						"\n2. Remove items"
						"\n3. Back to menu\nYour choise: ";
					std::cin >> action;
					switch (action)
					{
					case 1:
						addItemsToList(it->second, itemList);
						std::cout << "" << abcCustomers.size();
						break;
					case 2:
						removeItemsFromList(it->second, itemList);
						break;
					case 3:
						std::cout << "\nReturns to the main menu...\n" << std::endl;
						break;
					default:
						std::cout << "Invalid input, returns to the main menu...\nPlease try again!\n" << std :: endl;
						break;
					}
				}
				break;
			case 3:
				multimapSum.clear();
				for (const auto& element : abcCustomers)
					multimapSum.insert({ element.second.totalSum(), element.second });
				//prints all the payments and customers
				multiIt = multimapSum.begin();
				for (; multiIt != multimapSum.end(); ++multiIt)
				{
					std::cout << "\nPayment amount: " << (*multiIt).first << "$\n";
					std::cout << (*multiIt).second << std::endl;
				}
				break;
			case 4:
				std::cout << "You have successfully logged out.\nhave a nice day!" << std::endl;
				whileFlag = false;
				break;
			default:
				std::cout << "Invalid input, please try again..." << std::endl;
			}
		}
		catch (...)
		{
			std::cerr << "An error occurred while reading input.\nPlease try again.\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
	}
	return 0;
}



void initList(std::vector<Item>& v)
{
	std::string itemName[] = { "Milk", "Cookies", "Chocolate", "Yogurt", "Cheese", "Butter", "Eggs", "Meat", "Tomato", "Apple" };
	std::string itemSerialNum[] = { "11110", "11111", "11112", "11113", "11114", "11115", "11116", "11117", "11118", "11119" };
	double itemPrice[] = { 4.59, 10.84, 5.90, 3.30, 17.80, 4.70, 20.90, 199.99, 0.20, 1.30 };
	for (int i = 0; i < 10; ++i)
	{
		Item item(itemName[i], itemSerialNum[i], itemPrice[i]);
		v.push_back(item);
	}
}

void printListItem(std::vector<Item>& v)
{
	std::cout << "\nThe items you can buy are: (0 to exit)" << std::endl;
	for (int i = 0; i < 10; ++i)
		std::cout << i + 1 << ". " << v[i].getName() << "    " << "price: " << v[i].getUnitPrice() << "$" << std::endl;
}

void addItemsToList(Customer& customer, std::vector<Item>& itemList)
{
	printListItem(itemList);
	std::cout << "What item would you like to buy? Input: ";
	int addItem = -1;
	std::cin >> addItem;
	while (addItem != 0)
	{
		if (addItem < 1 || addItem > 10)
		{
			std::cout << "There is no item with this number, please choose from the list!" << std::endl;
			std::cout << "What item would you like to buy? Input: ";
			std::cin >> addItem;
			continue;
		}
		std::set<Item>::iterator itemPtr = customer.getItems().find(itemList[addItem - 1]);
		if (itemPtr == customer.getItems().end())
			customer.getItems().insert(itemList[addItem - 1]);
		else
		{
			Item tempItem = *itemPtr;
			customer.getItems().erase(itemPtr);
			tempItem.setCount(tempItem.getCount() + 1);
			customer.getItems().insert(tempItem);
		}
		std::cout << "The item added successfully!" << std::endl;
		std::cout << "What item would you like to buy? Input: ";
		std::cin >> addItem;
	}
	std::cout << "End of purchase!\n" << std::endl;
}

void printCustomerList(const std::set<Item> purchaseList)
{
	for (const Item& i : purchaseList)
		std::cout << i.getCount() << " " << i.getName() << std::endl;
}

void removeItemsFromList(Customer& customer, std::vector<Item>& itemList)
{
	int removeItem = -1;
	printListItem(itemList);
	std::cout << "What item would you like to remove? Input: ";
	std::cin >> removeItem;
	while (removeItem != 0)
	{
		if (removeItem < 1 || removeItem > 10)
		{
			std::cout << "There is no item with this number, please choose from the list!" << std::endl;
			std::cout << "What item would you like to buy? Input: ";
			std::cin >> removeItem;
			continue;
		}
		std::set<Item>::iterator itemPtr = customer.getItems().find(itemList[removeItem - 1]);
		if (itemPtr == customer.getItems().end())
			std::cout << "You don't have this item. Please try another item you want to remove." << std::endl;
		else
		{
			Item tempItem = *itemPtr;
			customer.getItems().erase(itemPtr);
			if (tempItem.getCount() > 1)
			{
				tempItem.setCount(tempItem.getCount() - 1);
				customer.getItems().insert(tempItem);
			}
			std::cout << "The item removed successfully!\n" << std::endl;
		}
		std::cout << "What item would you like to remove? Input: ";
		std::cin >> removeItem;
	}
	std::cout << "End of removal!\n" << std::endl;
}
