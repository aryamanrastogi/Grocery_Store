#pragma once
#define MAX_ITEMS_IN_SALE 10
#define NUM_CATS 7

struct Stocks
{
    int ID;
    int soldby;
    double price;
    int category;
};

struct StockRecord
{
    struct Stocks items;
    char categoryName[15];
    char name[22];
	int quantity;
    int quantityLeft;
};

struct SalesRecord
{
	struct StockRecord records;
	double amount;
	int purchaseTotal;
	double amountocalculatetaxon;
};

void centreText(int repNo, char character, char string[]);
int readStockItems(struct StockRecord storeStock[], int size, int zeroOrone);
int categoryToName(struct StockRecord storeStock[], int size);
void printStockReport(struct StockRecord storeStock[], int size);
int readSale(struct StockRecord storeStock[], int size, struct SalesRecord saleItems[]);
int printSalesReport(struct StockRecord storeStock[], struct SalesRecord saleItems[], int size);
void getTopSellers(struct StockRecord storeStock[], int numStockItems, struct SalesRecord topSellers[], int number, int cat);
void printTopSellers(struct StockRecord storeStock[], struct SalesRecord topSellers[], int number, int cat);
