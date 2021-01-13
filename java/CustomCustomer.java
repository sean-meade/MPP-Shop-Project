import java.util.ArrayList;
import java.io.Console;


public class CustomCustomer {
	
	private String name;
	private double budget;
	private ArrayList<ProductStock> shoppingList;
	private double cost;
	// String euro = "\u20ac";

	public CustomCustomer(Shop s) {

		shoppingList = new ArrayList<>();
		Console console = System.console();

		if (console == null) {
			System.out.println("Console is not supported.");
			System.exit(1);
		}

		// Ask for name and budget
		name = console.readLine("What is your name? ");
		String budgetString = console.readLine("What is your budget? EUR");
		budget = Integer.parseInt(budgetString);

		String createItem = "y";

		// While customers want to continue adding things to their shopping list
		while (createItem.equalsIgnoreCase("y")) {
			createItem = console.readLine("Do you wish to add an item to your shopping list (y/n)?: ");
			if (createItem.equalsIgnoreCase("n")) {
				break;
			}
			// If anything but y or n areentered it will remind user to use y/n
			if (!createItem.equalsIgnoreCase("n") && !createItem.equalsIgnoreCase("y")){
				System.out.println("Please choose yes or no (y/n)");
			}

			// Asks the user what item they want, checks if we have it and then gets the amount
			if (createItem.equalsIgnoreCase("y")) {
				String productName = console.readLine("What item would you like to purchase: ");
				
				for (ProductStock ps : s.getStock()) {
					if (productName.equalsIgnoreCase(ps.getName())){

						String quantityString = console.readLine("How many of this item would you like: ");
						int quantity = Integer.parseInt(quantityString);
						Product p = new Product(productName, 0);
						ProductStock sCustom = new ProductStock(p, quantity);
						shoppingList.add(sCustom);
						cost += quantity * ps.getUnitPrice();
					} else {
						System.out.println("We do not sell " + productName);
					}
					
				}
			}		
		}
	}
	
	public String getName() {
		return name;
	}

	public double getCost() {
		return cost;
	}

	public double getBudget() {
		return budget;
	}


	public ArrayList<ProductStock> getShoppingList() {
		return shoppingList;
	}

	@Override
	public String toString() {
		String ret = "Customer [name=" + name + ", budget=" + budget + ", shoppingList=\n";
		for (ProductStock productStock : shoppingList) {
			ret+= productStock.getName() + " Quantity: " + productStock.getQuantity() + "\n";
		}
		return ret + "]";
	}
	
	public static void main(String[] args) {
		
		// james.getShoppingList().get(2).getName()
		// System.out.println(james);
	}
}
