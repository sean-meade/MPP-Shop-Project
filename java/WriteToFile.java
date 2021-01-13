
import java.io.FileWriter;
import java.io.IOException;

public class WriteToFile {
    String cash;
    String qty;

    public WriteToFile(Shop s, Customer c) {
        // What cash is left after order
        cash = String.valueOf(s.getCash()-c.getCost());

        // write to the file
        FileWriter csvWriter = null;
        try {
            csvWriter = new FileWriter("../stock.csv");
            csvWriter.append(cash);
            csvWriter.write("\n");
            
            // Couldn't for the life of me find out how to access the values needed
            // to update quantity from shop. I think I'd make a variable somehow to hold
            // it if I was to do it again.
            for ( ProductStock stock : s.getStock()) {
                csvWriter.write(stock.getName());
                    csvWriter.write(",");
                    csvWriter.write(String.valueOf(stock.getUnitPrice()));
                    csvWriter.write(",");    
                    qty = Integer.toString(stock.getQuantity());
                    csvWriter.write(qty);
                    System.out.println(qty + "qty2\n");
                    
                    csvWriter.write("\n");

                // for (ProductStock item : c.getShoppingList()){
                    // if ((item.getName()).equalsIgnoreCase(stock.getName()) ){
                    // if (item.getQuantity() <= stock.getQuantity()){
                    //     int left = stock.getQuantity() - item.getQuantity();
                    //     String qty = Integer.toString(left);
                    //     System.out.println(qty);
                    //     csvWriter.write(qty);
                    // }} else {
                        // String qty2 = Integer.toString(stock.getQuantity());
                        // System.out.println(qty2 + "qty2\n");
                        // csvWriter.write(qty2);
                    //     break;
                    // }
                
                    
                }
                csvWriter.write("\n");
            } catch (Exception e) {
            e.printStackTrace();
        }finally {
			try {
				if (csvWriter != null) {
                    // Close file
					csvWriter.flush();
					csvWriter.close();					
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
    }

    
}
