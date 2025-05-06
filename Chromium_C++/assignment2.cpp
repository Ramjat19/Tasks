#include <iostream>
#include <functional>

namespace base {
// Dummy implementation for DoNothing
template <typename... Args>
auto DoNothing() {
    return [](Args&&...) {};
}
}

// Example class
class MyClass {
public:
    MyClass(int value) : value_(value) {}

    // 1. Replace a short, called-once helper with a lambda
    int ComputeSquare(int x) {
        auto square = [](int n) { return n * n; };
        return square(x);
    }

    // 2. Replace a short, bound-once helper with a lambda
    void UseBoundLambda(int y) {
        auto multiplyByValue = [this](int n) { return n * value_; };
        std::cout << "Result: " << multiplyByValue(y) << std::endl;
    }

    // 3. Replace a do-nothing function with base::DoNothing()
    void RegisterCallback() {
        auto callback = base::DoNothing<>();
        callback();
    }

    // 4. Five simple accessor methods marked const
    int GetValue() const { return value_; }
    int GetDoubleValue() const { return value_ * 2; }
    bool IsPositive() const { return value_ > 0; }
    bool IsZero() const { return value_ == 0; }
    bool IsNegative() const { return value_ < 0; }

    // 5. Const-correct method returning a pointer
    const int* GetValuePtr() const { return &value_; }

private:
    int value_;
};

// 6. Compile-time constants
constexpr int kMaxItems = 100;
constexpr double kPi = 3.1415926535;
constexpr char kNewLine = '\n';
constexpr bool kFeatureEnabled = true;
constexpr const char* kAppName = "AssignmentApp";

int main() {
    MyClass obj(5);

    int square = obj.ComputeSquare(4);
    std::cout << "Square: " << square << std::endl;

    obj.UseBoundLambda(3);
    obj.RegisterCallback();

    std::cout << "Value: " << obj.GetValue() << std::endl;
    std::cout << "Double Value: " << obj.GetDoubleValue() << std::endl;
    std::cout << "Is Positive: " << obj.IsPositive() << std::endl;
    std::cout << "Is Zero: " << obj.IsZero() << std::endl;
    std::cout << "Is Negative: " << obj.IsNegative() << std::endl;

    const int* ptr = obj.GetValuePtr();
    std::cout << "Pointer Value: " << *ptr << std::endl;

    std::cout << "Max Items: " << kMaxItems << kNewLine;
    std::cout << "App Name: " << kAppName << std::endl;

    return 0;
}
