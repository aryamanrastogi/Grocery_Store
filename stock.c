#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include"stock.h"

//int countp=0, countb=0, countm=0, countd=0;

void centreText(int repNo, char character, char string[])
{
	int i;
	repNo = repNo - strlen(string);
	for (i = 0; i < (repNo / 2); i++)
	{
		printf("%c", character);
	}
	printf("%s", string);
	for (i = 0; i < (repNo / 2); i++)
	{
		printf("%c", character);
	}
}

int readStockItems(struct StockRecord storeStock[], int size, int zeroOrone)
{
	int i = 0, numberOfRecords = 0, flag;

	if (zeroOrone == 0)
	{
		FILE* fp = NULL;
		fp = fopen("datafile.txt", "r");
		if (fp != NULL)
		{
			while (i < size && fscanf(fp, "%d,%d,%lf,%d,%20[^\n]", &storeStock[i].quantity, &storeStock[i].items.category, &storeStock[i].items.price, &storeStock[i].items.soldby, storeStock[i].name) != EOF && storeStock[i].quantity)
			{  
				storeStock[i].quantityLeft = storeStock[i].quantity;

				storeStock[i].items.ID = i + 1;
				
				printf("%d,", storeStock[i].quantity);
				printf("%d,", storeStock[i].items.category);
				printf("%.2lf,", storeStock[i].items.price);
				printf("%d,", storeStock[i].items.soldby);
				printf("%s", storeStock[i].name);
				printf("\n");

				numberOfRecords++;
				i++;
			}
			fclose(fp);
			fp = NULL;
		}
	}

	if (zeroOrone == 1)
	{
		for (i = 0; i < size; i++)
		{
			scanf("%d,%d,%lf,%d,%20[^\n]", &storeStock[i].quantity, &storeStock[i].items.category, &storeStock[i].items.price, &storeStock[i].items.soldby, storeStock[i].name);
			storeStock[i].items.ID = i+1 ;
			storeStock[i].quantityLeft = storeStock[i].quantity;
			
			if (storeStock[i].quantity == 0)
			{
				i = size;
				numberOfRecords--;
				/*storeStock[i].items.ID = numberOfRecords;*/
			}
			//****************************************************************************************
			else
			{
				while (storeStock[i].items.category > 7 || storeStock[i].items.category < 1)
				{
					printf("Invalid Category - Enter a number between 1 and 7: ");
					scanf("%d,%lf,%d,%20[^\n]", &storeStock[i].items.category, &storeStock[i].items.price, &storeStock[i].items.soldby, storeStock[i].name);
					/*printf("\n%d, %d, %lf, %d, %s", storeStock[i].quantity, storeStock[i].items.category, storeStock[i].items.price, storeStock[i].items.soldby, storeStock[i].name);*/
				}
				while (storeStock[i].items.soldby > 1 || storeStock[i].items.soldby < 0)
				{

					printf("Invalid soldByWeight - Enter a number between 0 and 1: ");
					scanf("%d,%20[^\n]", &storeStock[i].items.soldby, storeStock[i].name);
					
					/*printf("\n%d, %d, %lf, %d, %s", storeStock[i].quantity, storeStock[i].items.category, storeStock[i].items.price, storeStock[i].items.soldby, storeStock[i].name);*/
				}

			}
			//***************************************************************************************
			numberOfRecords++;
		}
	}
	return numberOfRecords;
}
//****************************************************************************************

	int categoryToName(struct StockRecord storeStock[], int size)
	{
		int i;
		for (i = 0; i < size; i++)
		{
			if (storeStock[i].items.category == 1)
			{
				strcpy(storeStock[i].categoryName, "produce");
			}
			else if (storeStock[i].items.category == 2)
			{
				strcpy(storeStock[i].categoryName, "bakery");
			}
			else if (storeStock[i].items.category == 3)
			{
				strcpy(storeStock[i].categoryName, "meat");
			}
			else if (storeStock[i].items.category == 4)
			{
				strcpy(storeStock[i].categoryName, "dairy");
			}
			else if (storeStock[i].items.category == 5)
			{
				strcpy(storeStock[i].categoryName, "baking");
			}
			else if (storeStock[i].items.category == 6)
			{
				strcpy(storeStock[i].categoryName, "house wires");
			}
			else if (storeStock[i].items.category == 7)
			{
				strcpy(storeStock[i].categoryName, "miscellaneous");
			}
	
		}
		return storeStock[i].categoryName;
	}

	//****************************************************************

	void printStockReport(struct StockRecord storeStock[], int size)
	{
		int i;
		categoryToName(storeStock, size);
		printf(" ID %30s %15s    Price  Quantity\n", "Product", "Category");
		for (i = 0; i < size; i++)
		{
			printf("%3d %30s %15s %8.2lf %9d\n", storeStock[i].items.ID, storeStock[i].name, storeStock[i].categoryName, storeStock[i].items.price, storeStock[i].quantityLeft);
		}
	}

	int readSale(struct StockRecord storeStock[], int size, struct SalesRecord saleItems[])
	{
		int flag = 1, i = 0, j;
		while (flag != 0)
		{
			saleItems[i].records.quantity = 0;
			saleItems[i].amount = 0.0;
			saleItems[i].amountocalculatetaxon = 0.0;
			//saleItems[i].namew[0] = '\0';
			saleItems[i].records.items.price = 0;

			printf("Enter a product ID to purchase, and the quantity (0 to stop): ");
			scanf("%d,%d", &saleItems[i].records.items.ID, &saleItems[i].records.quantity);
			
			while (saleItems[i].records.items.ID > size)
			{
				printf("Invalid Product - Enter a number between 0 and %d: ", size);
				scanf("%d,%d", &saleItems[i].records.items.ID, &saleItems[i].records.quantity);
			}
			while (saleItems[i].records.quantity > size)
			{
				printf("Invalid quantity - Enter a number between 0.10 and 100.00: ");
				scanf("%d,%d", &saleItems[i].records.items.ID, &saleItems[i].records.quantity);
			}

			if (saleItems[i].records.items.ID > 0)
			{
				for (j = 1; j <= saleItems[i].records.items.ID; j++)
				{
					if (saleItems[i].records.items.ID == j)
					{

						strcpy(saleItems[i].records.name, storeStock[j - 1].name);
						saleItems[i].records.items.price = storeStock[j - 1].items.price;
						strcpy(saleItems[i].records.categoryName, storeStock[j - 1].categoryName);

						while (storeStock[j - 1].quantity < saleItems[i].records.quantity)
						{
							saleItems[i].records.quantity--;
						}

						saleItems[i].amount = (saleItems[i].records.quantity * saleItems[i].records.items.price);
						
						storeStock[j - 1].quantityLeft = storeStock[j - 1].quantity - saleItems[i].records.quantity;
						
						if (!strcmp(saleItems[i].records.categoryName, "miscellaneous") || !strcmp(saleItems[i].records.categoryName, "house wires"))
						{
							saleItems[i].amountocalculatetaxon = saleItems[i].amount;				
						}
						j = saleItems[i].records.items.ID;
					}
				}
				i++;
			}
			else
			{
				flag = 0;
			}
		}
		return i;
	}

	int printSalesReport(struct StockRecord storeStock[], struct SalesRecord saleItems[], int size)
	{
		printf("\n");
		centreText(70, '*', " Groceries ");
		printf("\n");
		centreText(70, '=', "");
		printf("\n");
		int i;
		double purchaseTotal = 0, taxableamount = 0, tax, net;
		for (i = 0; i < size; i++)
		{
			printf("%32s  %6.2lf %6.2lf \n", saleItems[i].records.name, saleItems[i].records.items.price, saleItems[i].amount);
			purchaseTotal += saleItems[i].amount;
			
			taxableamount += saleItems[i].amountocalculatetaxon;
			
		}
		tax = taxableamount * .13;
		net = purchaseTotal + tax;
		printf("\n");
		printf("Purchase Total %32.2lf\n", purchaseTotal);
		printf("Tax %43.2llf\n", tax);
		printf("Total %41.2lf\n", net);
		printf("Thank you for shopping here!\n\n");
		return 1;
	}


	void getTopSellers(struct StockRecord storeStock[], int numStockItems, struct SalesRecord topSellers[], int number, int cat)
	{
		int i;

		//char a[30];
		//	strcpy(a, categoryToName(storeStock, cat));
		//	if (!strcmp(a, "produce"))
		//	{
		//		countp++;
		//	}
		//	else if (!strcmp(a, "bakery"))
		//	{
		//		countb++;
		//	}
		//	else if (!strcmp(a, "meat"))
		//	{
		//		countm++;
		//	}
		//	else if (!strcmp(a, "dairy"))
		//	{
		//		countd++;
		//	}
			
			int  j = 0, k = 0, m = 0, n = 0, h = 0;
			int flag = 1;
			struct StockRecord sort;

			for (i = 0; i < numStockItems && flag; i++)
			{

				if (storeStock[i].items.category == 3 && cat == 2)
				{

					for (j = i; h < number; j++)
					{
						h++;
						m = j;
						for (n = j + 1; j < n; j++);
						{
							if (storeStock[n].quantityLeft < storeStock[m].quantityLeft)
							{

								m = n;

							}
						}
						if (m != j)
						{
							sort = storeStock[j];
							storeStock[j] = storeStock[m];
							storeStock[m] = sort;
						}

					}
					flag = 0;
				}
			}
	}


	void printTopSellers(struct StockRecord storeStock[], struct SalesRecord topSellers[], int number, int cat)
	{
		
	
		int i = 0, j = 0, k = 0;
		int flag = 1;


		for (j = 0; j < 14 && flag; j++)
		{
			if (storeStock[j].items.category == 1 && cat == 0)
			{
				centreText(50, '=', " Top 3 sellers in produce ");
				printf("\n");
				printf("Rank                       Product   Sales\n");
				i = j;
				for (i = j; k < number; i++)
				{
					k++;
					printf("%d             ", k);
					if (storeStock[i].items.category == 1 && (storeStock[i].quantity - storeStock[i].quantityLeft != 0))
					{
						printf("%20s   ", storeStock[i].name);
						printf("%d.00\n", (storeStock[i].quantity - storeStock[i].quantityLeft));
					}
					else
					{
						printf("              <none>    ");
						printf("0.00\n");
					}

				}
				flag = 0;
			}
			if (storeStock[j].items.category == 2 && cat == 1)
			{
				centreText(50, '=', " Top 3 sellers in bakery ");
				printf("\n");
				printf("Rank                       Product   Sales\n");
				i = j;
				for (i = j; k < number; i++)
				{
					k++;
					printf("%d             ", k);
					if (storeStock[i].items.category == 2 && (storeStock[i].quantity - storeStock[i].quantityLeft != 0))
					{
						printf("%20s    ", storeStock[i].name);
						printf("%d.00\n", (storeStock[i].quantity - storeStock[i].quantityLeft));
					}
					else
					{
						printf("              <none>    ");
						printf("0.00\n");

					}

				}
				flag = 0;
			}
			if (storeStock[j].items.category == 3 && cat == 2)
			{
				centreText(50, '=', " Top 3 sellers in meat ");
				printf("\n");
				printf("Rank                       Product   Sales\n");
				i = j;
				for (i = j; k < number; i++)
				{
					k++;
					printf("%d             ", k);
					if (storeStock[i].items.category == 3 && (storeStock[i].quantity - storeStock[i].quantityLeft != 0))
					{
						printf("%20s    ", storeStock[i].name);
						printf("%d.00\n", (storeStock[i].quantity - storeStock[i].quantityLeft));
					}
					else
					{
						printf("              <none>    ");
						printf("0.00\n");

					}

				}
				flag = 0;
			}
			if (storeStock[j].items.category == 4 && cat == 3)
			{
				centreText(50, '=', " Top 3 sellers in dairy ", number);
				printf("\n");
				printf("Rank                       Product   Sales\n");
				i = j;
				for (i = j; k < number; i++)
				{
					k++;
					printf("%d             ", k);
					if (storeStock[i].items.category == 4 && (storeStock[i].quantity - storeStock[i].quantityLeft != 0))
					{
						printf("%20s    ", storeStock[i].name);
						printf("%d.00\n", (storeStock[i].quantity - storeStock[i].quantityLeft));
					}
					else
					{
						printf("              <none>    ");
						printf("0.00\n");

					}

				}
				flag = 0;
			}
			if (storeStock[j].items.category == 5 && cat == 4)
			{
				centreText(50, '=', " Top 3 sellers in baking ", number);
				printf("\n");
				printf("Rank                       Product   Sales\n");
				i = j;
				for (i = j; k < number; i++)
				{
					k++;
					printf("%d             ", k);
					if (storeStock[i].items.category == 5 && (storeStock[i].quantity - storeStock[i].quantityLeft != 0))
					{
						printf("%20s     ", storeStock[i].name);
						printf("%d.00\n", (storeStock[i].quantity - storeStock[i].quantityLeft));
					}
					else
					{
						printf("              <none>    ");
						printf("0.00\n");
					}

				}
				flag = 0;
			}
			if (storeStock[j].items.category == 6 && cat == 5)
			{
				centreText(50, '=', " Top 2 sellers in house wares ", number);
				printf("\n");
				printf("Rank                       Product   Sales\n");
				i = j;
				for (i = j; k < number; i++)
				{
					k++;
					printf("%d             ", k);
					if (storeStock[i].items.category == 6 && (storeStock[i].quantity - storeStock[i].quantityLeft != 0))
					{
						printf("%20s     ", storeStock[i].name);
						printf("%d.00\n", (storeStock[i].quantity - storeStock[i].quantityLeft));
					}
					else
					{
						printf("              <none>    ");
						printf("0.00\n");
					}

				}
				flag = 0;
			}
			if (storeStock[j].items.category == 7 && cat == 6)
			{
				centreText(50, '=', " Top 2 sellers in miscellaneous ", number);
				printf("\n");
				printf("Rank                       Product   Sales\n");
				i = j;
				for (i = j; k < number; i++)
				{
					k++;
					printf("%d             ", k);
					if (storeStock[i].items.category == 7 && (storeStock[i].quantity - storeStock[i].quantityLeft != 0))
					{
						printf("%20s     ", storeStock[i].name);
						printf("%d.00\n", (storeStock[i].quantity - storeStock[i].quantityLeft));
					}
					else
					{
						printf("              <none>    ");
						printf("0.00\n");
					}

				}
				flag = 0;
			}
		}
	
	
	}
