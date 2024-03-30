import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Functionality {
    static Scanner scanner = new Scanner(System.in);
    static String customerDataBase = "C:/Users/user/Desktop/SE_Resources/Java_Backend/Files/Customer_Data.csv";
    static String credentialsDataBase = "C:/Users/user/Desktop/SE_Resources/Java_Backend/Files/Credentials.csv";

    public static String[] customerRegistration() {
        System.out.print("Generate an account: ");
        System.out.print("\n> Provide forename: ");
        String forename = scanner.next();
        System.out.print("> Provide family name: ");
        String familyName = scanner.next();

        return new String[]{forename, familyName};
    }

    static void generateSavingProcess(int choice, List<String[]> accountData) {
        if (choice == 1) {
            try (FileWriter writer = new FileWriter(customerDataBase, true)) {
                for (String[] rowData : accountData) {
                    writer.append(String.join(",", rowData));
                    writer.append("\n");
                }
            } catch (IOException e) {
                System.out.println("An error occurred while writing!");
            }

        } else if (choice == 0) {
            System.out.println("Returning to the previous operation...");
            Customer.selectCustomer();
        }
    }

    static List<String[]> importedData(Customer customer) {
        List<String[]> data = new ArrayList<>();
        String accountNO;
        double amount;

        for (int index = 0; index < customer.accountTypes.size(); index++) {

            if ((customer.accountTypes.get(index)).equals("debit")) {
                accountNO = ((DebitAccount) customer.accounts.get(index)).accountNo;
                amount = ((DebitAccount) customer.accounts.get(index)).amount;
                double cashBackRate = ((DebitAccount) customer.accounts.get(index)).cashbackRate;

                data.add(new String[]{""+ customer.id, customer.name, customer.surname, customer.accountTypes.get(index), accountNO, "" + amount, "" + cashBackRate});

            } else {
                accountNO = ((CreditAccount) customer.accounts.get(index)).accountNo;
                amount = ((CreditAccount) customer.accounts.get(index)).amount;
                double interestAmount = ((CreditAccount) customer.accounts.get(index)).interestAmount;
                double interestRate = ((CreditAccount) customer.accounts.get(index)).interestRate;

                data.add(new String[]{"" + customer.id, customer.name, customer.surname, customer.accountTypes.get(index), accountNO, "" + amount, "" + interestAmount, "" + interestRate});
            }
        }

        return data;
    }

    static void generateCredentials(Customer customer) {
        System.out.println("Generate credentials: ");
        System.out.print("> Provide a login: ");
        String login = scanner.next();

        System.out.print("> Provide a password: ");
        String password = scanner.next();

        System.out.print("Do you want to save your information provided? (yes '1', no '0'): ");
        int saved = scanner.nextInt();
        saveCredentials(customer, saved, login, password);
    }

    static void saveCredentials(Customer customer, int choosing, String login, String password) {
        if (choosing == 1) {
            try (FileWriter writer = new FileWriter(credentialsDataBase, true)) {
                String credential = customer.id + "," + customer.name + "," + customer.surname + "," + login + "," + password;
                writer.append(credential);
                writer.append("\n");

            } catch (IOException e) {
                System.out.println("An error occurred while checking");
            }

        } else if (choosing == 0) {
            System.out.println("Returning to the previous operation...");
            Customer.selectCustomer();
        }

    }

    static boolean checkAccountInfo(Customer customer, String login, String password) {
        // finding the user's name and surname from credentialsDataFile
        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(credentialsDataBase))) {
            String currentLine;
            do {
                currentLine = bufferedReader.readLine();
                if (currentLine == null) {
                    System.out.println("Account is not found. \nPlease, choose another account or create a new one");
                    return false;
                } else if (currentLine.split(",")[1].equals(customer.name) &&
                        currentLine.split(",")[2].equals(customer.surname)) break;

            } while (true);

            if (currentLine.split(",")[4].equals(login) &&
                    currentLine.split(",")[5].equals(password)) {
                System.out.println("Credentials provided is correct!");
                return true;

            } else return false;

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }


    private static int findLastIndex() {
        int lastPosition;
        try (BufferedReader reader = new BufferedReader(new FileReader(customerDataBase))) {
            String line;
            lastPosition = Integer.parseInt((reader.readLine()).split(",")[0]);

            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",");
                if (Integer.parseInt(parts[0]) > lastPosition) lastPosition = Integer.parseInt(parts[0]);
            }

        } catch (NullPointerException e) {
            lastPosition = 0;

        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        return lastPosition;
    }


    static void idGenerator(Customer customer) {
        int lastIndex = findLastIndex();
        customer.id = lastIndex + 1;
    }

    static Account accountOrdering(Customer customer) {
        System.out.print("Select Account (0 - debit card; 1 - credit card): ");
        int typeOfAccount = scanner.nextInt();

        if (typeOfAccount == 0) {
            customer.accountTypes.add("debit");
            System.out.print("> Enter balance for debit card: ");
            return new DebitAccount(customer, scanner.nextDouble());

        } else {
            customer.accountTypes.add("credit");
            System.out.print("> Enter required credit amount: ");
            return new CreditAccount(customer, scanner.nextDouble());
        }
    }

    static void cardOrderQuerying(Customer customer) {
        int count = 1;
        Scanner scanner = new Scanner(System.in);

        while (count != 0) {
            System.out.print("Do you have any card orderings (1-Yes, 0-No)?: ");
            count = scanner.nextInt();
            if (count == 1) {
                customer.accounts.add(Functionality.accountOrdering(customer));

            }

            else if (count != 0) {
                System.out.println("Please, enter the correct command option from: [0], [1]");
            }
        }
    }


}
