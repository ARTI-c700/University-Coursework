public abstract class Account {
    double amount;

    Account(double amount) {
        this.amount = amount;
    }

    abstract String generateAccountNO(String name, String surname, int id);

    abstract double disburseAmount();

}
