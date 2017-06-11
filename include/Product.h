#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
using namespace std;

class Product
{
    public:
        Product(int nID, string strName, double dPrice) : ID(nID), Name(strName), Price(dPrice) { };
        ~Product();
        int ID;
        string Name;
        public:
        double Price;
};

#endif // PRODUCT_H
