#pragma once
#include <string>
#include <set>
#include "Item.hpp"

class Customer
{
	std::string _name;
	std::set<Item> _items;

public:
	//constructor
	Customer(std::string);
	//getters
	std::string getName() const;
	std::set<Item>& getItems();
	//setters
	void setName(std::string);

	double totalSum() const;

	friend std::ostream& operator<< (std::ostream&, const Customer&);
};