#include <ncurses.h>
#include <list>
#include <string>
#include "Checkout.h"
#include "Warehouse.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <queue>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

using namespace std;

const int nCheckoutCount = 5;
Checkout Checkouts[nCheckoutCount];
int arrMillisToServeCustomer[nCheckoutCount] = { 0, 0, 0, 0, 0 };

Warehouse warehouse;

int nColsCount = 0;
int nRowsCount = 0;
int millisToAddNewCustomer = 0;

bool bCloseApp = false;

void DrawCheckouts();
void DrawWarehouse();
void* Draw(void*);
void* RandomizeCustomer(void*);
void* RunCheckout(void* checkoutIndex);
void* ReadKeyoard(void*);

pthread_mutex_t mutex;

int main()
{
    pthread_t drawThread, randCustomerThread, keyboardThread;
    pthread_t arrCheckoutThreads[nCheckoutCount];

    Checkouts[0] = Checkout("Kasa 1");
    Checkouts[1] = Checkout("Kasa 2");
    Checkouts[2] = Checkout("Kasa 3");
    Checkouts[3] = Checkout("Kasa 4");
    Checkouts[4] = Checkout("Kasa 5");

    initscr();
    getmaxyx(stdscr, nRowsCount, nColsCount);

    pthread_create(&drawThread, NULL, &Draw, NULL);
    pthread_create(&randCustomerThread, NULL, &RandomizeCustomer, NULL);
    pthread_create(&keyboardThread, NULL, &ReadKeyoard, NULL);

    for(int i = 0; i < nCheckoutCount; i++)
    {
        int * arg = new int;
        *arg = i;
        pthread_create(&arrCheckoutThreads[i], NULL, &RunCheckout, arg);
    }

    while(!bCloseApp) {}

    pthread_cancel(drawThread);
    pthread_cancel(randCustomerThread);
    pthread_cancel(keyboardThread);
    for(int i = 0; i < nCheckoutCount; i++)
    {
        pthread_cancel(arrCheckoutThreads[i]);
    }

    endwin();
    return 0;
}

void* ReadKeyoard(void*)
{
    while(true)
    {
        if(getch() == 27)
        {
            bCloseApp = true;
            break;
        }
    }
}

void* Draw(void*)
{
    while(true)
    {
        if(pthread_mutex_trylock(&mutex) == 0)
        {
            usleep(100000);
            clear();
            DrawCheckouts();
            DrawWarehouse();
            refresh();
            pthread_mutex_unlock(&mutex);
        }
    }
}

void DrawCheckouts()
{
    int nWidthPerCheckOut = (int)(nColsCount / 5) - 4;
    for(int i = 0; i < nCheckoutCount; i++)
    {
        mvprintw(0, i * nWidthPerCheckOut, Checkouts[i].Name.c_str());
        for(int y = 2; y < 7; y++)
        {
            mvprintw(y, i * nWidthPerCheckOut, "X");
            mvprintw(y, (i * nWidthPerCheckOut) + 5, "X");
        }

        for(int j = 0; j < Checkouts[i].Customers.size(); j++)
        {
            mvprintw(j + 2, (i * nWidthPerCheckOut) + 2, "*");
        }
    }
}

void DrawWarehouse()
{
    std::ostringstream objostringstream;
    objostringstream << warehouse.getCurrentTotalValue();
    string strTotal = "Stan magazynu: " + objostringstream.str() + " zl";
    int nStartX = nColsCount - strTotal.length();
    mvprintw(0, nStartX, strTotal.c_str());
}

void* RandomizeCustomer(void*)
{
    while(true)
    {
        if(pthread_mutex_trylock(&mutex) == 0)
        {
            if(millisToAddNewCustomer <= clock() / ( CLOCKS_PER_SEC / 1000 ))
            {
                millisToAddNewCustomer = (clock() / ( CLOCKS_PER_SEC / 1000 )) + ((1 + (rand() % 3)) * 1000);
                int minCustomersIndex = 0;
                for(int i = 1; i < nCheckoutCount; i++)
                {
                    if(Checkouts[i].Customers.size() < Checkouts[minCustomersIndex].Customers.size())
                    {
                        minCustomersIndex = i;
                    }
                }

                if(Checkouts[minCustomersIndex].Customers.empty())
                {
                    arrMillisToServeCustomer[minCustomersIndex] = (clock() / ( CLOCKS_PER_SEC / 1000 )) + ((8 + (rand() % 20)) * 1000);
                }

                Checkouts[minCustomersIndex].Customers.push(Customer(warehouse.getRandomProductsSetForCustomer()));
            }
            pthread_mutex_unlock(&mutex);
        }
    }
}

void* RunCheckout(void* checkoutIndex)
{
    while(true)
    {
        if(pthread_mutex_trylock(&mutex) == 0)
        {
            int nCheckoutIndex = *((int *) checkoutIndex);
            if(arrMillisToServeCustomer[nCheckoutIndex] <= clock() / ( CLOCKS_PER_SEC / 1000 ))
            {
                arrMillisToServeCustomer[nCheckoutIndex] = (clock() / ( CLOCKS_PER_SEC / 1000 )) + ((8 + (rand() % 20)) * 1000);
                if(!Checkouts[nCheckoutIndex].Customers.empty())
                {
                    Customer objCustomer = Checkouts[nCheckoutIndex].Customers.front();
                    warehouse.createTransaction(objCustomer.Products);
                    Checkouts[nCheckoutIndex].Customers.pop();
                }
            }
            pthread_mutex_unlock(&mutex);
        }
    }
}
