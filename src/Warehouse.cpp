#include "Warehouse.h"
#include <stdlib.h>
using namespace std;

// generowanie produktów w sklepie
void Warehouse::setDefaultProducts()
{
    this->Products.clear();
    this->Products.push_back(WarehouseProduct(1, "Ciastka", 9.99, 100));
    this->Products.push_back(WarehouseProduct(2, "Bułka", 0.29, 500));
    this->Products.push_back(WarehouseProduct(3, "Woda mineralna", 1.35, 200));
    this->Products.push_back(WarehouseProduct(4, "Szampon", 17.99, 100));
    this->Products.push_back(WarehouseProduct(5, "Jabłko", 0.99, 300));
    this->Products.push_back(WarehouseProduct(6, "Pomidor", 0.57, 300));
    this->Products.push_back(WarehouseProduct(7, "Mydło", 3.55, 400));
    this->Products.push_back(WarehouseProduct(8, "Chleb", 2.49, 700));
    this->Products.push_back(WarehouseProduct(9, "Gazeta", 1.99, 400));
    this->Products.push_back(WarehouseProduct(10, "Dezodorant", 14.99, 200));
}

// suma wartości wszystkich produktów w sklepie
double Warehouse::getCurrentTotalValue()
{
    double retValue = 0.0;
    for (list<WarehouseProduct>::const_iterator it = Products.begin(), end = Products.end(); it != end; ++it)
    {
        retValue += it->Quantity * it->Price;
    }
    return retValue;
}

// wylosowanie zestawu produktów dla klienta
list<WarehouseProduct> Warehouse::getRandomProductsSetForCustomer()
{
    int nProductsCount = 0;
    for (list<WarehouseProduct>::const_iterator it = Products.begin(), end = Products.end(); it != end; ++it)
    {
        if(it->Quantity > 0) nProductsCount++;
    }

    int nProductsCountToTake = 1 + (rand() % nProductsCount);
    list<int> listProductsIndexes;
    list<WarehouseProduct> listRetValue;
    for(int i = 0; i < nProductsCountToTake; i++)
    {
        int nProductIndex = -1;
        while(true)
        {
            nProductIndex = rand() % this->Products.size();
            bool bIsInList = false;
            for(list<int>::const_iterator it = listProductsIndexes.begin(), end = listProductsIndexes.end(); it != end; ++it)
            {
                if(*it == nProductIndex)
                {
                    bIsInList = true;
                    break;
                }
            }
            if(!bIsInList) break;
        }

        int nIndex = 0;
        for (list<WarehouseProduct>::const_iterator it = Products.begin(), end = Products.end(); it != end; ++it)
        {
            if(nIndex == nProductIndex)
            {
                if(it->Quantity > 0)
                {
                    int nQuantity = 1 + (rand() % 8);
                    listRetValue.push_back(WarehouseProduct(*it, nQuantity));
                }
                else i--;
                break;
            }
            nIndex++;
        }
    }

    return listRetValue;
}

// aktualizacja produktów w sklepie, nastepuje przy obsłużeniu klienta na kasie
void Warehouse::createTransaction(list<WarehouseProduct> listWarehouseProduct)
{
    for (list<WarehouseProduct>::const_iterator it = listWarehouseProduct.begin(), end = listWarehouseProduct.end(); it != end; ++it)
    {
        for (list<WarehouseProduct>::iterator inner = this->Products.begin(), end = this->Products.end(); inner != end; ++inner)
        {
            if(it->ID == inner->ID)
            {
                inner->Quantity -= it->Quantity;
                break;
            }
        }
    }
}






