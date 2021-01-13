import java.io.Console;

public class ChooseOrderType {
    
    public ChooseOrderType(Shop shop) {
        
		Console console = System.console();

		// Starts by asking the user if they want a manual or file order
		System.out.println("Type \"m\" for a manual order and \"c\" for csv file order");
		String typeOfOrder = console.readLine("Type of Order: ");
		// Then it calls the relevant functions to process orders
		if (typeOfOrder.equalsIgnoreCase("m")) {
			CustomCustomer c = new CustomCustomer(shop);
			shop.processCustomOrder(c);
			printCustomReciept pcr = new printCustomReciept(c, shop);
			System.out.println(pcr.getReciept());
			// WriteToFileCustom wtf = new WriteToFileCustom(shop, c);
		} else if (typeOfOrder.equalsIgnoreCase("c")) {
			Customer c = new Customer("../customer.csv", shop);
			shop.processOrder(c);
			printReciept pcr = new printReciept(c, shop);
			System.out.println(pcr.getReciept());
			WriteToFile wtf = new WriteToFile(shop, c);
		} else {
			System.out.println("Sorry did not recognize this type of order please try again.");
		}
    }

}
