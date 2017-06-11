#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <list>
#include "WarehouseProduct.h"

class Warehouse
{
    public:
        Warehouse() { this->setDefaultProducts(); }
        ~Warehouse() { }
        list<WarehouseProduct> Products;
        double getCurrentTotalValue();
        list<WarehouseProduct> getRandomProductsSetForCustomer();
        void createTransaction(list<WarehouseProduct> listWarehouseProduct);
    private:
        void setDefaultProducts();
};

#endif // WAREHOUSE_H
