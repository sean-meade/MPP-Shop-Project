import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Shop {

	private double cash;
	private ArrayList<ProductStock> stock;
	double costToCustomer;

	public Shop(String fileName) {
		stock = new ArrayList<>();
		List<String> lines = Collections.emptyList();
		try {
			lines = Files.readAllLines(Paths.get(fileName), StandardCharsets.UTF_8);
			cash = Double.parseDouble(lines.get(0));
			// i am removing at index 0 as it is the only one treated differently
			lines.remove(0);
			for (String line : lines) {
				String[] arr = line.split(",");
				String name = arr[0];
				double price = Double.parseDouble(arr[1]);
				int quantity = Integer.parseInt(arr[2].trim());
				Product p = new Product(name, price);
				ProductStock s = new ProductStock(p, quantity);
				stock.add(s);
			}
		}

		catch (IOException e) {
			System.out.println("The program could not find the CSV file with the shop information in it");
			e.printStackTrace();
			System.exit(-1);
		}
	}
	
	public ProductStock find(String name){
		for(ProductStock ps : stock){
			if (name.equalsIgnoreCase(ps.getName())){
				return ps;
			}
		}
		return null;
	}

	public ArrayList<ProductStock> getStock() {
		return stock;
	}
	
	// Process the order to check for faults
	public void processOrder(Customer c){
		// look through the customer order
		for(ProductStock ps : c.getShoppingList()){
			ProductStock shopPS = find(ps.getName());
			// System.out.println(shopPS);
			if (shopPS != null) {
				
				// retreive the unit price
				double unitPrice = shopPS.getUnitPrice();
				// set the price on the product held by customer
				if (shopPS.getQuantity() >= ps.getQuantity()) {
					ps.getProduct().setPrice(unitPrice);
				} else {
					System.out.println("We don't have enough " + ps.getName() + " in stock for your order.");
				}
				
				// this way we can use the ps method to calc cost;
				// System.out.println("The cost of " + ps.getName() + " will be " + ps.getCost());
				// Calculate Cost to customer
				costToCustomer += ps.getCost();
			} else {
				System.out.println("Sorry we do not stock " + ps.getName() + ".\n");
			}
		}
		// Check if customer has enough to process order
		if (costToCustomer > c.getBudget()){
			System.out.println("Sorry you seem to have insufficient funds for this order.");
		} else {
			System.out.println("The cost to " + c.getName() + " is " + costToCustomer);
		}
	}

	// Couldn't figure out inheretence for Java to there is a lot of repeated code
	public void processCustomOrder(CustomCustomer c){
		
		// look through the customer order
		for(ProductStock ps : c.getShoppingList()){
			ProductStock shopPS = find(ps.getName());
			// System.out.println(shopPS);
			if (shopPS != null) {
				
				// retreive the unit price
				double unitPrice = shopPS.getUnitPrice();
				// set the price on the product held by customer
				if (shopPS.getQuantity() >= ps.getQuantity()) {
					ps.getProduct().setPrice(unitPrice);
				} else {
					System.out.println("We don't have enough " + ps.getName() + "in stock for your order.");
				}
				
				// this way we can use the ps method to calc cost;
				// System.out.println("The cost of " + ps.getName() + " will be " + ps.getCost());
				costToCustomer += ps.getCost();
			} else {
				System.out.println("Sorry we do not stock " + ps.getName() + ".\n");
			}
		}
		if (costToCustomer > c.getBudget()){
			System.out.println("Sorry you seem to have insufficient funds for this order.");
		} else {
		System.out.println("The cost to " + c.getName() + " is " + costToCustomer);
		}
	}
	public double getCost() {
		return costToCustomer;
	}

	public double getCash() {
		return cash;
	}

	@Override
	public String toString() {
		return "Shop [cash=" + cash + ", stock=" + stock + "]";
	}

	public static void main(String[] args) {
		Shop shop = new Shop("../stock.csv");
		ChooseOrderType orderType = new ChooseOrderType(shop);

	}

}
