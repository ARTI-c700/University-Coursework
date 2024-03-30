import java.io.IOException;

public class CreditAccount extends Account {
    String accountNo;
    double interestAmount;
    double interestRate;

    CreditAccount (Customer customer, double amount) {
        super(amount);
        this.accountNo = generateAccountNO(customer.name, customer.surname, customer.id);
        this.interestAmount = 0;
        this.interestRate = 0;
    }

    @Override
    String generateAccountNO(String name, String surname, int id) {
        return "TC-" + name.toLowerCase() + surname.toLowerCase() + id;
    }

    @Override
    double disburseAmount() { return 0; }

}
