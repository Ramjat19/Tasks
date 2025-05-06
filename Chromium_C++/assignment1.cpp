#include <iostream>
#include <utility>
#include <cstring>

//------------------------------------------------------------------
// Fixing five DISALLOW_COPY_AND_ASSIGN()s
//--------------------------------------------------------------------  

class A {
  public:
    A() = default;
    ~A() = default;

    A(const A&) = delete; // Disallow copy constructor
    A& operator=(const A&) = delete; // Disallow copy assignment
};

class B {
  public:
    B() = default;
    ~B() = default;

    B(const B&) = delete; // Disallow copy constructor
    B& operator=(const B&) = delete; // Disallow copy assignment
};

class C {
  public:
    C() = default;
    ~C() = default;

    C(const C&) = delete; // Disallow copy constructor
    C& operator=(const C&) = delete; // Disallow copy assignment
};

class D {
  public:
    D() = default;
    ~D() = default;

    D(const D&) = delete; // Disallow copy constructor
    D& operator=(const D&) = delete; // Disallow copy assignment
};

class E {
  public:
    E() = default;
    ~E() = default;

    E(const E&) = delete; // Disallow copy constructor
    E& operator=(const E&) = delete; // Disallow copy assignment
};



//--------------------------------------------------------------------
// Fixing 5 constructors/destructors use "=default"
//--------------------------------------------------------------------

class F {
  public:
    F() = default; // Default constructor
    ~F() = default; // Default destructor
};
class G {
  public:
    G() = default; // Default constructor
    ~G() = default; // Default destructor
};
class H {
  public:
    H() = default; // Default constructor
    ~H() = default; // Default destructor
};
class I {
  public:
    I() = default; // Default constructor
    ~I() = default; // Default destructor
};
class J {
  public:
    J() = default; // Default constructor
    ~J() = default; // Default destructor
};


//--------------------------------------------------------------------
// Fixing 2 classes that define one of (construction, assignment) but not the other
//--------------------------------------------------------------------

class K {
  private:
    int* data;
    size_t size;
  
  public:
    K(size_t s = 10) : size(s) {
      data = new int[size]; // Allocate memory
      for(size_t i = 0; i < size; ++i) {
        data[i] = i; // Initialize data
      }
    }

    //copy constructor
    K(const K& other) : size(other.size) {
      data = new int[size]; // Allocate memory
      std::memcpy(data, other.data, size * sizeof(int)); // Copy data
    }

    // copy assignment
    K& operator=(const K& other) {
      if (this != &other){
        delete[] data; // Free existing memory
        size = other.size;
        data = new int[size]; // Allocate new memory
        std::memcpy(data, other.data, size * sizeof(int)); // Copy data
      }
      return *this; // Return the current object
    }

    ~K() {
      delete[] data; // Free allocated memory
    }

    void print() const {
      for(size_t i = 0; i < size; ++i) {
        std::cout << data[i] << " "; // Print data
      }
      std::cout << std::endl;
    }
};



//--------------------------------------------------------------------
// Adding movability to K class
//--------------------------------------------------------------------

class M {
  private:
    int* data;
    size_t size;
  
  public:
    M(size_t s = 10) : size(s) {
      data = new int[size]; // Allocate memory
      for(size_t i = 0; i < size; ++i) {
        data[i] = static_cast<int>(i); // Initialize data
      }
    }

    // Copy constructor
    M(const M& other) : size(other.size) {
      data = new int[size]; // Allocate memory
      std::memcpy(data, other.data, size * sizeof(int)); // Copy data
    }

    // Move constructor
    M(M&& other) noexcept : data(other.data), size(other.size) {
      other.data = nullptr; // Nullify the source pointer
      other.size = 0; // Reset the source size
    }

    // Copy assignment
    M& operator=(const M& other) {
      if (this != &other){
        delete[] data; // Free existing memory
        size = other.size;
        data = new int[size]; // Allocate new memory
        std::memcpy(data, other.data, size * sizeof(int)); // Copy data
      }
      return *this; // Return the current object
    }

    // Move assignment
    M& operator=(M&& other) noexcept {
      if (this != &other){
        delete[] data; // Free existing memory
        data = other.data; // Transfer ownership of the resource
        size = other.size;
        other.data = nullptr; // Nullify the source pointer
        other.size = 0; // Reset the source size
      }
      return *this; // Return the current object
    }

    ~M() {
      delete[] data; // Free allocated memory
    }

    void print() const {
      for(size_t i = 0; i < size; ++i) {
        std::cout << data[i] << " "; // Print data
      }
      std::cout << std::endl;
    }
};



int main(){
  // Test the classes
  A a1;
  B b1;
  C c1;
  D d1;
  E e1;

  F f1;
  G g1;
  H h1;
  I i1;
  J j1;

  std::cout<<"K: Copy constructor and assignment operator"<<std::endl;
  K k1(5);
  K k2 = k1; // Copy constructor
  k1.print();
  k2.print();
  K k3;
  k3 = k1; // Copy assignment
  k3.print(); 

  std::cout<<"M: Move constructor and assignment operator"<<std::endl;
  M m1(5);
  M m2 = std::move(m1); // Move constructor
  M m3;
  m3 = std::move(m2); // Move assignment
  m3.print(); // Print moved data
  m1.print(); // Print original data (should be empty)

  return 0;
}