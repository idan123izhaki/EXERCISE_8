#include "Item.hpp"

//constructor
Item::Item(std::string name, std::string serialNumber, double unitPrice, int count)
 : _name(name), _serialNumber(serialNumber)
{
	this->setUnitPrice(unitPrice);
	this->setCount(count);
}


//getters
std::string Item::getName() const { return this->_name; }
std::string Item::getSerialNumber() const { return this->_serialNumber; }
int Item::getCount() const { return this->_count; }
double Item::getUnitPrice() const { return this->_unitPrice; }
//setters
void Item::setName(std::string newName) { this->_name = newName; }
void Item::setSerialNumber(std::string newSerialNumber)
{
	this->_serialNumber = newSerialNumber.substr(0, 5);
}
void Item::setCount(int count)
{
	this->_count = (count > 1) ? count : 1;
}
void Item::setUnitPrice(double newUnitPrice)
{
	this->_unitPrice = (newUnitPrice > 0) ? newUnitPrice : -1;

}

double Item::totalPrice() const
{
	return _count * _unitPrice;
}


bool Item::operator<(const Item& other) const
{
	return (this->getSerialNumber() < other.getSerialNumber());
}

bool Item::operator>(const Item& other) const
{
	return (this->getSerialNumber() > other.getSerialNumber());
}
bool Item::operator== (const Item& other) const
{
	return (this->getSerialNumber() == other.getSerialNumber());
}
