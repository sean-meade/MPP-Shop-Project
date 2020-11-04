#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Product {
	char* name;
	double price;
};

struct ProductStock {
	struct Product product;
	int quantity;
};

struct Shop {
	double cash;
	struct ProductStock stock[20];
	int index;
};

struct Customer {
	char* name;
	double budget;
	struct ProductStock shoppingList[10];
	int index;
	double orderCost;
};

// void printProduct(struct Product p)
// {
// 	printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);
// 	printf("-------------\n");
// }

// void printCustomer(struct Customer c)
// {
// 	printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", c.name, c.budget);
// 	printf("-------------\n");
// 	for(int i = 0; i < c.index; i++)
// 	{
// 		printProduct(c.shoppingList[i].product);
// 		printf("%s ORDERS %d OF ABOVE PRODUCT\n", c.name, c.shoppingList[i].quantity);
// 		double cost = c.shoppingList[i].quantity * c.shoppingList[i].product.price; 
// 		printf("The cost to %s will be €%.2f\n", c.name, cost);
// 	}
// }

struct Shop createAndStockShop()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
	size_t read;

    fp = fopen("stock.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

	read = getline(&line, &len, fp);
	double cash = atof(line);

	struct Shop shop = { cash };

	// printf("Shop has %.2f in cash\n", shop.cash);

    while ((read = getline(&line, &len, fp)) != -1) {
        
		char *n = strtok(line, ",");
		char *p = strtok(NULL, ",");
		char *q = strtok(NULL, ",");
		int quantity = atoi(q);
		double price = atof(p);
		char *name = malloc(sizeof(char) * 50);
		strcpy(name, n);
		struct Product product = { name, price };
		struct ProductStock stockItem = { product, quantity };
		shop.stock[shop.index++] = stockItem;
		// printf("NAME OF PRODUCT %s PRICE %.2f QUANTITY %d\n", name, price, quantity);
    }
	
	return shop;
}

struct Customer createCustomerAndOrder(struct Shop s)
{

	FILE * fp;
    char * line = NULL;
    size_t len = 0;
	size_t read;

    fp = fopen("customer.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

	read = getline(&line, &len, fp);

	char *n = strtok(line, ",");
	char *b = strtok(NULL, ",");

	char *name = malloc(sizeof(char) * 50);
	strcpy(name, n);

	double budget = atof(b);

	struct Customer currentCustomer = { name, budget };

	// printf("Customers name is %s and their budget is €%.2f\n", currentCustomer.name, currentCustomer.budget);

	while ((read = getline(&line, &len, fp)) != -1) {
		char *n = strtok(line, ",");
		char *q = strtok(NULL, ",");
		int quantity = atoi(q);
		char *name = malloc(sizeof(char) * 50);
		strcpy(name, n);
		struct Product product = { name };
		struct ProductStock orderItem = { product, quantity };
		currentCustomer.shoppingList[currentCustomer.index++] = orderItem;
	}

	// for(int i = 0; i < currentCustomer.index; i++)
	// {
	// 	printProduct(currentCustomer.shoppingList[i].product);
	// 	printf("%s ORDERS %d OF ABOVE PRODUCT\n", currentCustomer.name, currentCustomer.shoppingList[i].quantity);
	// 	double cost = currentCustomer.shoppingList[i].quantity * currentCustomer.shoppingList[i].product.price; 
	// 	printf("The cost to %s will be €%.2f\n", currentCustomer.name, cost);
	// }

	double cost = 0;
	double itemCost = 0;

	for(int i = 0; i < currentCustomer.index; i++)
	{
		for (int j = 0; j < s.index; j++){
			if (strcmp(currentCustomer.shoppingList[i].product.name, s.stock[j].product.name) == 0){
				double itemPrice = s.stock[j].product.price;
				currentCustomer.shoppingList[i].product.price = itemPrice;
				itemCost = itemPrice * currentCustomer.shoppingList[i].quantity;
			}	
		}
		cost = cost + itemCost;
	}

	currentCustomer.orderCost = cost;

	printf("%.2f", currentCustomer.orderCost);


	return currentCustomer;
}

void processOrder(struct Shop s, struct Customer c)
{
	
}

void printShop(struct Shop s)
{
	printf("Shop has %.2f in cash\n", s.cash);
	for (int i = 0; i < s.index; i++)
	{
		printf("The shop has %d of %s at €%.2f each\n", s.stock[i].quantity, s.stock[i].product.name, s.stock[i].product.price);
	}
}

int main(void) 
{
	struct Shop shop = createAndStockShop();
	createCustomerAndOrder(shop);
	//printShop(shop);
	
    return 0;
}