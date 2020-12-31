import java.util.ArrayList;
import java.io.Console;


public class CustomCustomer {
	
	private String name;
	private double budget;
	private ArrayList<ProductStock> shoppingList;

	public CustomCustomer() {
		shoppingList = new ArrayList<>();
		Console console = System.console();

		if (console == null) {
			System.out.println("Console is not supported.");
			System.exit(1);
		}

		name = console.readLine("What is your name? ");
		String budgetString = console.readLine("What is your budget? ");
		budget = Integer.parseInt(budgetString);

		String createItem = "y";

		while (createItem.equals("y")) {
			String productName = console.readLine("What item would you like to purchase: ? ");
			String quantityString = console.readLine("How many of this item would you like: ");
			int quantity = Integer.parseInt(quantityString);
			Product p = new Product(productName, 0);
			ProductStock s = new ProductStock(p, quantity);
			shoppingList.add(s);

			createItem = console.readLine("Do you wish to continue (y/n)");
		}
		
	}
	
	public String getName() {
		return name;
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
		CustomCustomer james = new CustomCustomer();
		// james.getShoppingList().get(2).getName()
		System.out.println(james);
	}
}
