#ifndef WAREHOUSEPRODUCT_H
#define WAREHOUSEPRODUCT_H

#include "Product.h"

class WarehouseProduct : public Product
{
    public:
        WarehouseProduct(int nID, string strName, double dPrice, int nQuantity) : Product(nID, strName, dPrice)
        {
            this->Quantity = nQuantity;
        }
        WarehouseProduct(WarehouseProduct objWarehouseProduct, int nQuantity) : Product(objWarehouseProduct.ID, objWarehouseProduct.Name, objWarehouseProduct.Price)
        {
            this->Quantity = nQuantity;
        }

        int Quantity;

        ~WarehouseProduct();
};

#endif // WAREHOUSEPRODUCT_H
