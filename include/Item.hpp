#pragma once
#include <string>
#include <iostream>

class Item
{
	std::string _name;
	std::string _serialNumber;
	int _count;
	double _unitPrice;

public:
	Item(std::string name, std::string serialNumber, double unitPrice, int count = 1);
	//getters
	std::string getName() const;
	std::string getSerialNumber() const;
	int getCount() const;
	double getUnitPrice() const;
	//setters
	void setName(std::string);
	void setSerialNumber(std::string);
	void setCount(int);
	void setUnitPrice(double);

	double totalPrice() const;
	bool operator<(const Item& other) const;
	bool operator>(const Item& other) const;
	bool operator==(const Item& other) const;
};