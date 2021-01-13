#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

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

struct notAvailableList {
		char *item;
		int index;
	};

// function to update the stock after order 
void updateStockFile(struct Customer c, struct Shop s){
	FILE *fp;

	fp=fopen("../stock.csv","w+");

	double cash = s.cash - c.orderCost;



	fprintf(fp,"%f", cash);

	// loops through shop and customer items 
	for (int x = 0; x < s.index; x++){
		bool finished_with_item = false;

		for (int q = 0; q < c.index ; q++){
			
			char *sItemName = s.stock[x].product.name;

			char *item = c.shoppingList[q].product.name;

			// This loop will reduce string to lowercase for both so a user can 
			// input bread, Bread or BrEaD and all will be accepted
			if (strlen(item) == strlen(sItemName)) {	
				for(int y=0;y<=strlen(sItemName);y++){
					if(sItemName[y]>=65&&sItemName[y]<=90)
						sItemName[y]=sItemName[y]+32;
					if(item[y]>=65&&item[y]<=90)
						item[y]=item[y]+32;
				}
			}

			// If item was order it will remove the right amount otherwise it will just leave it the same
			if (strcmp(item, sItemName) == 0 && c.shoppingList[q].product.price != 0 && finished_with_item == false) {
				fprintf(fp,"\n%s,%f,%d",s.stock[x].product.name,s.stock[x].product.price,s.stock[x].quantity - c.shoppingList[q].quantity);
				finished_with_item = true;
			} else if (finished_with_item == false){
				fprintf(fp,"\n%s,%f,%d",s.stock[x].product.name,s.stock[x].product.price,s.stock[x].quantity);
				finished_with_item = true;
			}

		}
	}
		fclose(fp);

	}

// Processes order
struct Customer processOrder(struct Shop s, struct Customer c)
{

	int itemInList = 1;

	// Checks to see if user has enough in budget
	if(c.orderCost > c.budget){
		
		// throw error
		printf("Sorry there seems to be an error while processing your payment.\n");
		printf("Please contact your bank if issue continues.\n");
		exit(0);
	}

	double cost = 0;
	double itemCost = 0;

	
	struct ProductStock orderItem;

	// Checks to see if we have enough stock or even have item and calculates cost of order
	for(int i = 0; i < c.index; i++)
	{
		struct Product product;
		
		int count;
		count = 0;
		char *item = c.shoppingList[i].product.name;
		for (int j = 0; j < s.index; j++){
			char *sItemName = s.stock[j].product.name;

			if (strlen(item) == strlen(sItemName)) {	
				for(int y=0;y<=strlen(sItemName);y++){
					if(sItemName[y]>=65&&sItemName[y]<=90)
						sItemName[y]=sItemName[y]+32;
					if(item[y]>=65&&item[y]<=90)
						item[y]=item[y]+32;
				}
			}
			if (strcmp(item, sItemName) != 0){
				count = count + 1;
				if (count >= s.index){
					printf("Sorry we do not sell %s.\n", c.shoppingList[i].product.name);
					itemInList = 0;
				}			
			} else if (strcmp(c.shoppingList[i].product.name, s.stock[j].product.name) == 0){
					if ( c.shoppingList[i].quantity > s.stock[j].quantity) {
						printf("Sorry we don't have enough %s in stock to fullfil your order.\n", s.stock[j].product.name);
					}
				 	if (c.shoppingList[i].quantity < s.stock[j].quantity) {
						 
					double itemPrice = s.stock[j].product.price;
					c.shoppingList[i].product.price = itemPrice;
					itemCost = itemPrice * c.shoppingList[i].quantity;
					
					cost = cost + itemCost;
					
				}
			}
			
		}
		
	}

	c.orderCost = cost;

	return c;

}

// Prints the receipt like other two programs
void printReciept(struct Customer c) {
	double totalCost;
	printf("--------------------\n");
	printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: €%.2f\n", c.name, c.budget);
	printf("--------------------\n");
	for(int i = 0; i < c.index; i++) {
		printf("PRODUCT NAME: %s \nQUANTITY OF PRODUCT: %d\n", c.shoppingList[i].product.name, c.shoppingList[i].quantity);
		printf("AT %.2f PER ITEM\n", c.shoppingList[i].product.price);
		double itemCost = c.shoppingList[i].quantity * c.shoppingList[i].product.price;
		printf("           = €%.2f\n", itemCost);
		printf("--------------------\n");
		
	}
	printf("TOTAL COST TO %s IS €%.2f", c.name, c.orderCost);
}

// Craetes the shop from the file
struct Shop createAndStockShop()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
	size_t read;

    fp = fopen("../stock.csv", "r");
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

	fclose(fp);
	
	return shop;
}

// Takes in information from user for order
struct Customer createCustomerAndOrderManually(struct Shop shop)
{
	 
	char inputName[30];
	char inputBudget[10];
	// char *item;
	char inputQuantity[5];
	char *ptr;
	char inputItem[30];

	// Asks for relevant information
	printf("What is your name: ");
	fgets(inputName, 30, stdin);

	char *nameHolder = strtok(inputName, "\n");

	char *name = malloc(sizeof(char) * 50);
	strcpy(name, nameHolder);

	printf("Hello %s, welcome to my shop in C.\n\n", name);

	printf("What is your spending limit for this order: €");
	fgets(inputBudget, 10, stdin);
	printf("\n");

	double budget;

   	budget = strtod(inputBudget, &ptr);

	struct Customer currentCustomer = { name, budget };
	
	char inputAnswer[10];

	// Lists the items in stock
	printf("The items we have in stock are: \n");
	
	for (int j = 0; j < shop.index; j++){
		if (shop.stock[j].quantity > 0){
			printf("- %s\n", shop.stock[j].product.name);
			}
		}

	struct Product product;
	struct ProductStock orderItem;

	int answer = 1;
	char *yesNo;
	double cost;

	// Allows the user to add items to their order and throws error messages
	// from to many ordered ect.
	do	{
		printf("Do you wish to add an item to your shopping list (y/n)?: ");
		fgets(inputAnswer, 3, stdin);
		yesNo = strtok(inputAnswer, "\n");

		if (strcmp(yesNo, "y") == 0) {
			printf("What item would you like to purchase: ");
			fgets(inputItem, 30, stdin); 
			// printf("%s", inputItem);

			char *itemHolder = strtok(inputItem, "\n");
			// printf("%s", item);
			char *item = malloc(sizeof(char) * 50);
			strcpy(item, itemHolder);

			int count = 0;
			for (int x = 0; x < shop.index; x++){

			char *sItemName = shop.stock[x].product.name;

			// Again same chunk of code as above to allow the user to only need the spelling right
			// not upper or lower case
			if (strlen(item) == strlen(sItemName)) {	
				for(int y=0;y<=strlen(sItemName);y++){
					if(sItemName[y]>=65&&sItemName[y]<=90)
						sItemName[y]=sItemName[y]+32;
					if(item[y]>=65&&item[y]<=90)
						item[y]=item[y]+32;
				}
			}

			if (strcmp(item, sItemName) == 0) {
				printf("How many of %s would you like: ", item);

				fgets(inputQuantity, 5, stdin);

				int quantity = atoi(inputQuantity);
				double itemPrice;
			
				product.name = item;
				
				orderItem.product = product;
				orderItem.quantity = quantity;
				
				if (quantity <= shop.stock[x].quantity){
					orderItem.product.price = shop.stock[x].product.price;
					currentCustomer.shoppingList[currentCustomer.index++] = orderItem;
					itemPrice = quantity * shop.stock[x].product.price;
				} else {
					printf( "We do not have enough %s to fill your order.\n", item);
					
				}

			cost = cost + itemPrice;
			} // if name in stock
			else if (strcmp(item, sItemName) != 0) {
				count = count + 1;
				
			}
			if (count >= shop.index) {
				printf("We do not stock %s.\n", item);
			}				 
			} // for every item in shop x

		} // if yes

		else if (strcmp(yesNo, "n") == 0) {
			currentCustomer.orderCost = cost;
			answer = 0;
		} // if no
		
		else {
				printf("Please type y or n.\n");
			}

		

		
	} while ( answer == 1);

	// checks budget to see if they have enough to fill order
	if(currentCustomer.orderCost > currentCustomer.budget){
		// throw error
		printf("Sorry there seems to be an error while processing your payment.\n");
		printf("Please contact your bank if issue continues.\n");
		exit(0);
	}
		
	return currentCustomer;

}

// creates order from csv file
struct Customer createCustomerAndOrder(struct Shop s)
{

	FILE * fp;
    char * line = NULL;
    size_t len = 0;
	size_t read;

    fp = fopen("../customer.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

	read = getline(&line, &len, fp);

	char *n = strtok(line, ",");
	char *b = strtok(NULL, ",");

	char *name = malloc(sizeof(char) * 50);
	strcpy(name, n);

	double budget = atof(b);

	struct Customer currentCustomer = { name, budget };

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

	

	fclose(fp);

	return processOrder(s, currentCustomer);;
}

// Starting function to ask user what kind of order they want to make
// and runs the appropriate functions
int main(void) 
{
	struct Shop shop = createAndStockShop();
	
	char typeOfOrder[6];
	
	printf("Type \"m\" for a manual order and \"c\" for csv file order \n");
	printf("Type of order: ");
	scanf("%[^\n]%*c", &typeOfOrder);
	printf("\n");
	
	if(strcmp(typeOfOrder, "c") == 0){
		struct Customer customer = createCustomerAndOrder(shop);
		printReciept(customer);
		updateStockFile(customer, shop);
	} else if(strcmp(typeOfOrder, "m") == 0){
		struct Customer customer = createCustomerAndOrderManually(shop);
		printReciept(customer);
		updateStockFile(customer, shop);
	} else {
		printf("Sorry did not recognize this type of order please try again.");
	}
    return 0;
}