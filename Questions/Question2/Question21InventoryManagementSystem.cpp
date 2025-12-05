/* 
21. Inventory Management System (Classes, STL containers, file I/O)

Problem: Build a C++ program modeling a small store inventory. Design classes Product, Inventory, and Supplier.

Requirements / Features:
Product stores id, name, price, quantityInStock.
Supplier stores supplierId, name, contact.
Inventory maintains a collection of Product objects and maps productId -> supplierId. Use stl of your choice for collection.
Implement: add new product, update stock (restock), sell product (reduce stock, throw exception if insufficient), remove product.
Persist inventory to a file (inventory.txt) and load from it on startup.
Add method to list low-stock products below given threshold.
Use appropriate access specifiers and const-correctness.
Extra tasks: Implement operator overloading for << to print Product. Use exceptions for I/O errors and stock errors.

I/O: Add products, sell 3 units of product id 101, list low stock threshold=5.
Expected: appropriate messages, final product listing.
*/

//Inventory Management System
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>

// ---------------------- Product ----------------------
class Product {
private:
    int id;
    std::string name;
    double price;
    int quantityInStock;

public:
    Product() : id(0), name(""), price(0.0), quantityInStock(0) {}
    Product(int _id, const std::string& _name, double _price, int _qty)
        : id(_id), name(_name), price(_price), quantityInStock(_qty) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantityInStock; }

    void restock(int qty) {
        if(qty < 0) throw std::runtime_error("Cannot restock negative quantity");
        quantityInStock += qty;
    }

    void sell(int qty) {
        if(qty < 0) throw std::runtime_error("Cannot sell negative quantity");
        if(qty > quantityInStock) throw std::runtime_error("Insufficient stock for product " + std::to_string(id));
        quantityInStock -= qty;
    }

    friend std::ostream& operator<<(std::ostream& os, const Product& p) {
        os << "Product ID: " << p.id 
           << ", Name: " << p.name 
           << ", Price: $" << p.price 
           << ", Stock: " << p.quantityInStock;
        return os;
    }

    // Serialization for file I/O
    std::string serialize() const {
        return std::to_string(id) + ";" + name + ";" + std::to_string(price) + ";" + std::to_string(quantityInStock);
    }

    void deserialize(const std::string& line) {
        size_t pos = 0, prev = 0;
        std::vector<std::string> tokens;
        while ((pos = line.find(';', prev)) != std::string::npos) {
            tokens.push_back(line.substr(prev, pos - prev));
            prev = pos + 1;
        }
        tokens.push_back(line.substr(prev));

        if(tokens.size() != 4) throw std::runtime_error("Invalid product data: " + line);

        id = std::stoi(tokens[0]);
        name = tokens[1];
        price = std::stod(tokens[2]);
        quantityInStock = std::stoi(tokens[3]);
    }
};

// ---------------------- Supplier ----------------------
class Supplier {
private:
    int supplierId;
    std::string name;
    std::string contact;
public:
    Supplier() : supplierId(0), name(""), contact("") {}
    Supplier(int id, const std::string& n, const std::string& c) 
        : supplierId(id), name(n), contact(c) {}

    int getId() const { return supplierId; }
    std::string getName() const { return name; }
    std::string getContact() const { return contact; }
};

// ---------------------- Inventory ----------------------
class Inventory {
private:
    std::unordered_map<int, Product> products;      // productId -> Product
    std::unordered_map<int, int> productSupplier;   // productId -> supplierId
    std::string filename;

public:
    Inventory(const std::string& file = "inventory.txt") : filename(file) {
        loadFromFile();
    }

    void addProduct(const Product& p, int supplierId) {
        products[p.getId()] = p;
        productSupplier[p.getId()] = supplierId;
    }

    void restockProduct(int productId, int qty) {
        if(products.count(productId) == 0) throw std::runtime_error("Product not found");
        products[productId].restock(qty);
    }

    void sellProduct(int productId, int qty) {
        if(products.count(productId) == 0) throw std::runtime_error("Product not found");
        products[productId].sell(qty);
    }

    void removeProduct(int productId) {
        products.erase(productId);
        productSupplier.erase(productId);
    }

    void listLowStock(int threshold) const {
        std::cout << "Products with stock below " << threshold << ":\n";
        for(const auto& [id, prod] : products) {
            if(prod.getQuantity() < threshold)
                std::cout << prod << "\n";
        }
    }

    void printAll() const {
        std::cout << "Current Inventory:\n";
        for(const auto& [id, prod] : products) {
            std::cout << prod << "\n";
        }
    }

    void saveToFile() const {
        std::ofstream out(filename);
        if(!out) throw std::runtime_error("Cannot open file for writing: " + filename);
        for(const auto& [id, prod] : products) {
            out << prod.serialize() << ";" << productSupplier.at(id) << "\n";
        }
    }

    void loadFromFile() {
        std::ifstream in(filename);
        if(!in) return; // file may not exist initially

        std::string line;
        while(std::getline(in, line)) {
            if(line.empty()) continue;
            size_t lastSep = line.rfind(';');
            if(lastSep == std::string::npos) continue;
            std::string prodData = line.substr(0, lastSep);
            int supplierId = std::stoi(line.substr(lastSep + 1));

            Product p;
            p.deserialize(prodData);
            addProduct(p, supplierId);
        }
    }

    ~Inventory() {
        try { saveToFile(); } catch(...) {}
    }
};
int main() {
    Inventory inv;

    // Add some products
    inv.addProduct(Product(101,"Pen", 1.5, 10), 1);
    inv.addProduct(Product(102,"Notebook", 3.0, 2), 1);
    inv.addProduct(Product(103,"Eraser", 0.5, 4), 2);

    // Sell 3 units of product 101
    try {
        inv.sellProduct(101, 3);
        std::cout << "Sold 3 units of product 101\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
    }

    // List low stock products (threshold=5)
    inv.listLowStock(5);

    // Print full inventory
    inv.printAll();

    return 0;
}
/* 
Sold 3 units of product 101
Products with stock below 5:
Product ID: 102, Name: Notebook, Price: $3, Stock: 2
Product ID: 103, Name: Eraser, Price: $0.5, Stock: 4
Current Inventory:
Product ID: 101, Name: Pen, Price: $1.5, Stock: 7
Product ID: 102, Name: Notebook, Price: $3, Stock: 2
Product ID: 103, Name: Eraser, Price: $0.5, Stock: 4
*/