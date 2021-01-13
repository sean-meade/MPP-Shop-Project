import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;


public class Customer {
	
	private String name;
	private double budget;
	private ArrayList<ProductStock> shoppingList;
	private double cost;
	private int count;
	
	
	public Customer(String fileName, Shop s) {
		shoppingList = new ArrayList<>();
		List<String> lines = Collections.emptyList();
		try {
			lines = Files.readAllLines(Paths.get(fileName), StandardCharsets.UTF_8);
			String[] firstLine = lines.get(0).split(",");
			name = firstLine[0];
			budget = Double.parseDouble(firstLine[1]);
			// i am removing at index 0 as it is the only one treated differently
			lines.remove(0);
			for (String line : lines) {
				String[] arr = line.split(",");
				String productName = arr[0];
				count = 0;
				// Search shop stock for productName and get price and set instead of 0 in line 30
				for (ProductStock ps : s.getStock()) {
					count += 1;
					if (productName.equalsIgnoreCase(ps.getName())){	
					int quantity = Integer.parseInt(arr[1].trim());
					// int qtyLeft = ps.getQuantity() - quantity;
					
					Product p = new Product(productName, 0);
					ProductStock sFile = new ProductStock(p, quantity);
					shoppingList.add(sFile);
					if (quantity <= ps.getQuantity()){
						cost += quantity * ps.getUnitPrice();
					
					}
					
				}
				if (count > s.getStock().size()) {
					System.out.println("We do not sell " + productName);
				}
				}
			}
		}

		catch (IOException e) {
			// do something
			e.printStackTrace();
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
		// Customer james = new Customer("../customer.csv");
		// // james.getShoppingList().get(2).getName()
		//  System.out.println(james);
	}
}
