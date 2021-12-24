struct BigNumber {
    float number; // Number
    char base; // Base of the number (10^n)

    BigNumber(float number, char base) {
        number = number;
        base = base;
    }
    
    // Operator Definitions
    BigNumber& operator+(const BigNumber& number2) {
        // Convert the other number to this base
        
    }

    BigNumber& operator/(const BigNumber &number2) {

    }

    // Destructor
    ~BigNumber() {
        delete this;
    }
};