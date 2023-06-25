#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

// Function to check if a number is prime
bool isPrime(int num) {
    if (num <= 1)
        return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

// Function to compute the modular exponentiation
int modExp(int base, int exponent, int modulus) {
    int result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

// Function to calculate the modular inverse using the Extended Euclidean Algorithm
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;
    return x1;
}

int main() {
    // Step 1: Choose two distinct prime numbers
    int p, q;
    std::cout << "Enter the value of p (prime number): ";
    std::cin >> p;
    std::cout << "Enter the value of q (prime number): ";
    std::cin >> q;

    // Check if p and q are prime
    if (!isPrime(p) || !isPrime(q)) {
        std::cout << "p and q must be prime numbers." << std::endl;
        return 0;
    }

    // Step 2: Compute n = p * q
    int n = p * q;

    // Step 3: Compute φ(n) = (p - 1) * (q - 1)
    int phiN = (p - 1) * (q - 1);

    // Step 4: Choose an encryption key e (1 < e < φ(n)) such that gcd(e, φ(n)) = 1
    int e;
    std::cout << "Enter the value of e (encryption key): ";
    std::cin >> e;

    // Check if e and phiN are coprime
    if (e <= 1 || e >= phiN || std::__gcd(e, phiN) != 1) {
        std::cout << "e must be greater than 1 and coprime with phi(n)." << std::endl;
        return 0;
    }

    // Step 5: Compute the decryption key d
    int d = modInverse(e, phiN);

    std::cout << "Public Key: (e = " << e << ", n = " << n << ")" << std::endl;
    std::cout << "Private Key: (d = " << d << ", n = " << n << ")" << std::endl;

    // Encryption
    std::string plaintext;
    std::cout << "Enter the plaintext message: ";
    std::cin.ignore();
    std::getline(std::cin, plaintext);

    std::string ciphertext = "";
    for (char c : plaintext) {
        int numericValue = static_cast<int>(c);
        int encryptedValue = modExp(numericValue, e, n);
        ciphertext += std::to_string(encryptedValue) + " ";
    }
    std::cout << "Encrypted Message (Ciphertext): " << ciphertext << std::endl;

    // Decryption
    std::string decryptedText = "";
    std::istringstream iss(ciphertext);
    std::string token;
    while (iss >> token) {
        int encryptedValue = std::stoi(token);
        int decryptedValue = modExp(encryptedValue, d, n);
        char decryptedChar = static_cast<char>(decryptedValue);
        decryptedText += decryptedChar;
    }
    std::cout << "Decrypted Message (Plaintext): " << decryptedText << std::endl;

    return 0;
}