public class printReciept {
    String breakLine;
    String nameBudget;
    String items;
    String total;

    public printReciept(Customer c, Shop s) {

            // returns string to print out Reciept in the same format as other two programs
        
            breakLine = "--------------------\n";
            nameBudget = "CUSTOMER NAME: " + c.getName() + " \nCUSTOMER BUDGET: EUR" + c.getBudget() + "\n";
           
            for (ProductStock ps : c.getShoppingList()) {
                items += "PRODUCT NAME: " + ps.getName() + " \nQUANTITY OF PRODUCT:" + ps.getQuantity() + "\n";
                items += "AT EUR" + ps.getCost() + "PER ITEM\n";
                items += "           = EUR" + ps.getCost()*ps.getQuantity() + "\n";
                items += breakLine;
            }
            total = "TOTAL COST TO " + c.getName() + " IS EUR" + s.getCost();
        
    }

    public String getReciept() {
        return breakLine + nameBudget + breakLine + items + total;
    }

    public static void main(String[] args) {
		
		// james.getShoppingList().get(2).getName()
		// System.out.println(james);
	}
}
