from dataclasses import dataclass, field
from typing import List
import csv

@dataclass
class Product:
	name: str
	price: float = 0.0

@dataclass 
class ProductStock:
	product: Product
	quantity: int

@dataclass 
class Shop:
	cash: float = 0.0
	stock: List[ProductStock] = field(default_factory=list)

@dataclass
class Customer:
	name: str = ""
	budget: float = 0.0
	shopping_list: List[ProductStock] = field(default_factory=list)
	order_cost: float = 0.0

# writes to file the new quantities of the shop
def update_stock_file(c, s):
	with open('../stock.csv', 'w', newline='') as file:
		writer = csv.writer(file)
		cash = s.cash - c.order_cost
		writer.writerow([cash])
		for s_item in s.stock:
			finished_with_item = False
			for c_item in c.shopping_list:
				if (s_item.product.name.lower() == c_item.product.name.lower() and finished_with_item == False):
					writer.writerow([s_item.product.name, s_item.product.price, s_item.quantity-c_item.quantity])
					finished_with_item = True
				elif (finished_with_item == False):
					writer.writerow([s_item.product.name, s_item.product.price, s_item.quantity])
					finished_with_item = True

# prints the reciept like the other two programs
def print_reciept(c):
	print("--------------------")
	print(f"CUSTOMER NAME: {c.name} \nCUSTOMER BUDGET: €{c.budget}")
	print("--------------------")
	for i in c.shopping_list:
		print(f"PRODUCT NAME: {i.product.name} \nQUANTITY OF PRODUCT: {i.quantity}")
		print(f"AT €{i.product.price} PER ITEM")
		print(f"           = €{i.quantity * i.product.price}")
		print("--------------------")
	print(f"TOTAL COST TO {c.name} IS €{c.order_cost}")

# Creates the shop from the stock file
def create_and_stock_shop():
	s = Shop()
	with open('../stock.csv') as csv_file:
		csv_reader = csv.reader(csv_file, delimiter=',')
		first_row = next(csv_reader)
		s.cash = float(first_row[0])
		for row in csv_reader:
			p = Product(row[0], float(row[1]))
			ps = ProductStock(p, float(row[2]))
			s.stock.append(ps)
			#print(ps)
	return s

# Creates the customer from user input
def create_customer_manually(s):

	# Asks for name and budget
	name = input("What is your name: ")
	print(f"Hello {name}, welcome to my shop in Python.")
	print("")
	budget = float(input("What is your spending limit for this order: €"))
	c = Customer(name, budget)

	# Lists the items available in the shop only if we have 1 or more
	print("The items we have in stock are: ")
	for item in s.stock:
		if item.quantity > 0:
			print(f"- {item.product.name}")
	
	answer = "y"
	cost = 0

	# A loop that asks the user to ass items to their shopping list and throws appropriate errors
	while answer == "y":
		answer = input("Do you wish to add an item to your shopping list (y/n)?: ")

		if answer == "y":
			product = input("What item would you like to purchase: ")

			p = Product(product)
			finish_with_item = False
			for stock_item in s.stock:
				if product.lower() == stock_item.product.name.lower() and finish_with_item == False:
					p.price = stock_item.product.price

					
					quantity = int(input(f"How many of {product} would you like: "))
					cost = cost + stock_item.product.price * quantity

					ps = ProductStock(p, quantity)

					c.shopping_list.append(ps)
					finish_with_item = True
				
			if finish_with_item == False:
				print(f"We do not sell {product}")
				finish_with_item = True

		elif answer == "n":
			c.order_cost = 0.0

		else:
			print("Please try again.")

	c.order_cost = cost
	# Checks to see if the user has enough money
	if c.order_cost > c.budget: 
		print("Sorry there seems to be an error while processing your payment.\n")
		print("Please contact your bank if issue continues.\n")
	return c
	
# Creates user from file
def read_customer(file_path):
	with open(file_path) as csv_file:
		csv_reader = csv.reader(csv_file, delimiter=',')
		first_row = next(csv_reader)
		c = Customer(first_row[0], float(first_row[1]))
		for row in csv_reader:
			name = row[0]
			quantity = float(row[1])
			p = Product(name)
			ps = ProductStock(p, quantity)
			c.shopping_list.append(ps)

	cost = 0
	# checks to see if we have enough stock or if we even sell it
	for item in c.shopping_list:
		finished_with_item = False
		for stock_item in s.stock:
			if item.product.name.lower() == stock_item.product.name.lower():
				if finished_with_item == False and item.quantity <= stock_item.quantity:
					item.product.price = stock_item.product.price	
					item_cost = item.product.price * item.quantity
					finished_with_item = True
					cost = cost + item_cost
				else:
					print(f"We do not have enough {item.product.name} in stock to complete your order.")
					finished_with_item = True
				
		if finished_with_item == False:
			print(f"Sorry we do not sell {item.product.name}.")

	c.order_cost = cost

	return c

# Asks the user to choose between manual and file order
print("Type \"m\" for a manual order and \"c\" for csv file order")
type_of_order = input("Type of order: ")

s = create_and_stock_shop()

# runs which ever one is asked for
if type_of_order == "c":
	c = read_customer("../customer.csv")
	

elif type_of_order == "m":
	c = create_customer_manually(s)

else:
	print("Sorry did not recognize this type of order please try again.")

print_reciept(c)
update_stock_file(c, s)


