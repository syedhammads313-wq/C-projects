#include <iostream>
using namespace std;

class Person {
protected:
    string name;
    int    age;
public:
    Person(string n, int a) {
        name = n;
        age  = a;
    }
    // Pure Virtual Function
    virtual void displayRole() = 0;

    virtual void showInfo() {
        cout << "Name : " << name << endl;
        cout << "Age  : " << age  << endl;
    }
};

// ============================================================
// LEVEL 1: Employee extends Person
// ============================================================
class Employee : public Person {
protected:
    int   employeeID;
    float salary;
public:
    Employee(string n, int a, int id, float sal) : Person(n, a) {
        employeeID = id;
        salary     = sal;
    }
    virtual void displayRole() = 0;

    void showInfo() override {
        Person::showInfo();
        cout << "Emp ID : " << employeeID << endl;
        cout << "Salary : Rs. " << salary  << endl;
    }
};

// ============================================================
// LEVEL 2: Manager extends Employee
// ============================================================
class Manager : public Employee {
protected:
    string department;
public:
    Manager(string n, int a, int id, float sal, string dept)
        : Employee(n, a, id, sal) {
        department = dept;
    }
    void displayRole() override {
        cout << "Role       : Manager"     << endl;
        cout << "Department : " << department << endl;
    }
    void showInfo() override {
        Employee::showInfo();
        displayRole();
    }
};

// ============================================================
// LEVEL 3: HeadManager extends Manager (Multilevel)
// ============================================================
class HeadManager : public Manager {
protected:
    int totalBranches;
public:
    HeadManager(string n, int a, int id, float sal, string dept, int branches)
        : Manager(n, a, id, sal, dept) {
        totalBranches = branches;
    }
    void displayRole() override {
        cout << "Role          : Head Manager"       << endl;
        cout << "Department    : " << department     << endl;
        cout << "Branches Managed : " << totalBranches << endl;
    }
    void showInfo() override {
        Employee::showInfo();
        displayRole();
    }
};

// ============================================================
// MENU ITEM CLASS + Operator Overloading
// ============================================================
class MenuItem {
protected:
    string itemName;
    float  price;
    string category;
public:
    MenuItem(string n, float p, string cat) {
        itemName = n;
        price    = p;
        category = cat;
    }
    // Operator Overloading: + combines two items into a combo
    MenuItem operator+(MenuItem secondItem) {
        MenuItem combo("Combo: " + itemName + " & " + secondItem.itemName,
                        price + secondItem.price - 50,
                        "Combo Deal");
        return combo;
    }
    void displayItem() {
        cout << "Item     : " << itemName  << endl;
        cout << "Category : " << category  << endl;
        cout << "Price    : Rs. " << price << endl;
    }
};

// ============================================================
// ORDER CLASS + Operator Overloading
// ============================================================
class Order {
protected:
    int   orderID;
    int   tableNo;
    float totalAmount;
    int   itemCount;
public:
    Order(int id, int table, float amount, int count) {
        orderID     = id;
        tableNo     = table;
        totalAmount = amount;
        itemCount   = count;
    }
    // Operator Overloading: + merges two orders into one bill
    Order operator+(Order secondOrder) {
        Order mergedOrder(0,
                          tableNo,
                          totalAmount + secondOrder.totalAmount,
                          itemCount   + secondOrder.itemCount);
        return mergedOrder;
    }
    void displayOrder() {
        float tax   = totalAmount * 0.10;
        float grand = totalAmount + tax;
        cout << "Order ID     : " << orderID     << endl;
        cout << "Table No     : " << tableNo     << endl;
        cout << "Items Count  : " << itemCount   << endl;
        cout << "Total Amount : Rs. " << totalAmount << endl;
        cout << "Tax (10%)    : Rs. " << tax        << endl;
        cout << "Grand Total  : Rs. " << grand      << endl;
    }
};

// ============================================================
// MAIN FUNCTION
// ============================================================
int main() {

    cout << "==== Restaurant Management System ====" << endl;

    // --------------------------------------------------
    // MULTILEVEL INHERITANCE + POLYMORPHISM
    // --------------------------------------------------
    cout << "\n===== Staff Details =====" << endl;

    Manager    mgr ("Ali Hassan",   45, 101, 85000, "Operations");
    HeadManager hm ("Sara Malik",   50, 001, 120000, "Head Office", 5);
    Employee*  emp1 = &mgr;    // base class reference (polymorphism)
    Employee*  emp2 = &hm;

    cout << "\n--- Manager ---" << endl;
    emp1->showInfo();

    cout << "\n--- Head Manager ---" << endl;
    emp2->showInfo();

    // --------------------------------------------------
    // OPERATOR OVERLOADING: MenuItem + MenuItem = Combo
    // --------------------------------------------------
    cout << "\n===== Menu Combo Offer =====" << endl;

    MenuItem item1("Chicken Biryani", 350, "Main Course");
    MenuItem item2("Seekh Kabab",     450, "BBQ");
    MenuItem comboMeal = item1 + item2;

    cout << "''--- Item 1 ---" << endl;
    item1.displayItem();

    cout << "\n--- Item 2 ---" << endl;
    item2.displayItem();

    cout << "\n--- Combo Meal (Rs.50 Discount Applied) ---" << endl;
    comboMeal.displayItem();

    // --------------------------------------------------
    // OPERATOR OVERLOADING: Order + Order = Merged Bill
    // --------------------------------------------------
    cout << "\n===== Order Billing =====" << endl;

    Order order1(1001, 3, 1200, 4);
    Order order2(1002, 3,  900, 3);
    Order mergedOrder = order1 + order2;

    cout << "\n--- Order 1 ---" << endl;
    order1.displayOrder();

    cout << "\n--- Order 2 ---" << endl;
    order2.displayOrder();

    cout << "\n--- Merged Bill (Both Orders Combined) ---" << endl;
    mergedOrder.displayOrder();

    return 0;
}
