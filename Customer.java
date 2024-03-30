import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Customer {
    int id;
    String name, surname;
    List<Account> accounts;
    List<String> accountTypes;

    Customer(String name, String surname) {
        this.name = name;
        this.surname = surname;
        Functionality.idGenerator(this);
        accountTypes = new ArrayList<>();
        accounts = new ArrayList<>();
        Functionality.cardOrderQuerying(this);
    }

    static void selectCustomer() {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Options:");
        System.out.println(" :: Existing customer login (0)");
        System.out.println(" :: New customer registration (1)");
        System.out.print("> ");
        int choice = scanner.nextInt();

        if (choice == 1) {
            String[] customerInfo = Functionality.customerRegistration();
            Customer customer = new Customer(customerInfo[0], customerInfo[1]);

            System.out.print("Do you want to save your information provided? (yes '1', no '0') : ");
            int choosing = scanner.nextInt();

            Functionality.generateSavingProcess(choosing, Functionality.importedData(customer));
            Functionality.generateCredentials(customer);

        } else if (choice == 0) {

            System.out.println("Please, enter your credentials: ");
            System.out.print("> Forename: ");
            String forename = scanner.nextLine();
            System.out.print("\n> Family name");
            String familyName = scanner.nextLine();

            Customer existingCustomer = new Customer(forename, familyName);

            System.out.print("Login: ");
            String login = scanner.nextLine();
            System.out.print("\nPassword: ");
            String password = scanner.nextLine();

            if (!(Functionality.checkAccountInfo(existingCustomer, login, password))) {
                selectCustomer();
            }
        }
    }
}

