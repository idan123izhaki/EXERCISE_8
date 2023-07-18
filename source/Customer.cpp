#include <iostream>
#include "Customer.hpp"

Customer::Customer(std::string name)
	: _name(name), _items({}) {}

std::string Customer::getName() const { return this->_name; }
std::set<Item>& Customer::getItems() { return this->_items; }
void Customer::setName(std::string newName) { this->_name = newName; }

double Customer::totalSum() const
{
	double sumItems = 0.0;
	for (const auto& element : _items)
		sumItems += element.totalPrice();
	return sumItems;
}

std::ostream& operator<< (std::ostream& out, const Customer& c)
{
	out << "Name: " << c.getName() << std::endl;
	out << "All the customer items:" << std::endl;
	for (const Item& item : c._items)
	{
		out << "Item name: " << item.getName() << ", amount: " << item.getCount() << std::endl;
	}
	return out;
}