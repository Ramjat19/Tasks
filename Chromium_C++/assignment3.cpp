#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <memory>
#include <variant>

// Function: copying from const ref => pass by value
std::string AppendSuffix(std::string name) {
    return name + "_suffix";
}

// Small types passed by value
bool IsPositive(int x) {
    return x > 0;
}

bool IsZero(int x) {
    return x == 0;
}

bool IsNegative(int x) {
    return x < 0;
}

int Increment(int x) {
    return x + 1;
}

bool IsEven(int x) {
    return x % 2 == 0;
}

// Scoped object simulation
class ScopedBoolReset {
public:
    ScopedBoolReset(bool& flag) : flag_(flag) {
        flag_ = false;
    }
    ~ScopedBoolReset() {
        flag_ = true;
    }

private:
    bool& flag_;
};

void ScopedExample() {
    bool flag = true;
    {
        ScopedBoolReset resetter(flag);
        std::cout << "Inside scope, flag = " << flag << std::endl;
    }
    std::cout << "After scope, flag = " << flag << std::endl;
}

// Simulate fixed map
const std::map<int, std::string> kStatusMessages = {
    {0, "OK"},
    {1, "Error"},
    {2, "Unknown"}
};

const std::map<std::string, int> kColors = {
    {"red", 1},
    {"green", 2},
    {"blue", 3}
};

// Rewrite class to use std::variant
class Result {
public:
    using VariantType = std::variant<int, std::string>;

    explicit Result(int value) : result_(value) {}
    explicit Result(std::string text) : result_(std::move(text)) {}

    void Print() const {
        if (std::holds_alternative<int>(result_)) {
            std::cout << "Integer result: " << std::get<int>(result_) << std::endl;
        } else {
            std::cout << "String result: " << std::get<std::string>(result_) << std::endl;
        }
    }

private:
    VariantType result_;
};

int main() {
    // Smart pointer instead of base::MakeRefCounted
    auto obj = std::make_shared<int>(10);
    std::cout << "Shared value: " << *obj << std::endl;

    // Scoped example
    ScopedExample();

    // Using "fixed" maps
    int status = 1;
    std::cout << "Status message: " << kStatusMessages.at(status) << std::endl;

    auto color = kColors.find("green");
    if (color != kColors.end()) {
        std::cout << "Color value: " << color->second << std::endl;
    }

    // Using variant class
    Result r1(42);
    Result r2("Success");
    r1.Print();
    r2.Print();

    // Replacing loops with algorithms
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // find_if
    auto it = std::find_if(numbers.begin(), numbers.end(), [](int x) { return x > 3; });
    if (it != numbers.end()) {
        std::cout << "First number > 3: " << *it << std::endl;
    }

    // all_of
    bool allPositive = std::all_of(numbers.begin(), numbers.end(), [](int x) { return x > 0; });
    std::cout << "All numbers positive: " << allPositive << std::endl;

    // algorithm calls
    bool anyEven = std::any_of(numbers.begin(), numbers.end(), IsEven);
    std::cout << "Any number even: " << anyEven << std::endl;

    bool noneNegative = std::none_of(numbers.begin(), numbers.end(), IsNegative);
    std::cout << "No negative numbers: " << noneNegative << std::endl;

    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "Sum of numbers: " << sum << std::endl;

    auto maxIt = std::max_element(numbers.begin(), numbers.end());
    if (maxIt != numbers.end()) {
        std::cout << "Maximum number: " << *maxIt << std::endl;
    }

    auto minIt = std::min_element(numbers.begin(), numbers.end());
    if (minIt != numbers.end()) {
        std::cout << "Minimum number: " << *minIt << std::endl;
    }

    return 0;
}
