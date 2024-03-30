import java.io.IOException;

public class DebitAccount extends Account {
    String accountNo;
    double cashbackRate;
    DebitAccount(Customer customer, double amount) {
        super(amount);
        this.accountNo = generateAccountNO(customer.name, customer.surname, customer.id);
        this.cashbackRate = 0.05;
    }

    @Override
    String generateAccountNO(String name, String surname, int id) {
        return "TD-" + name.toLowerCase() + surname.toLowerCase() + id;
    }


    @Override
    double disburseAmount() { return 0; }
}
