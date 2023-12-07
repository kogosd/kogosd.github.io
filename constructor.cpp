#include <iostream>
#include <string>
#include <utility>

class MyClass {
public:
    MyClass(int intValue, double doubleValue, const std::string& stringValue)
        : intMember(intValue), doubleMember(doubleValue), stringMember(stringValue) {}

    // Constructor that takes arguments in any order
    template<typename... Args>
    MyClass(Args&&... args) {
        initialize(std::forward<Args>(args)...);
    }

    void printValues() const {
        std::cout << "Integer: " << intMember << std::endl;
        std::cout << "Double: " << doubleMember << std::endl;
        std::cout << "String: " << stringMember << std::endl;
    }

private:
    int intMember;
    double doubleMember;
    std::string stringMember;

    // Helper function for perfect forwarding
    template<typename T, typename... Args>
    void initialize(T&& value, Args&&... args) {
        setMember(std::forward<T>(value));
        initialize(std::forward<Args>(args)...);
    }

    // Base case to end the recursion
    void initialize() {}

    // Set member values based on the type of the argument
    void setMember(int value) { intMember = value; }
    void setMember(double value) { doubleMember = value; }
    void setMember(const std::string& value) { stringMember = value; }
};

int main() {
    // Example usage
    MyClass obj1(42, 3.14, "Hello");
    obj1.printValues();

    std::cout << "\n";

    // Arguments provided in different order
    MyClass obj2("World", 3.14, 42);
    obj2.printValues();

    return 0;
}
