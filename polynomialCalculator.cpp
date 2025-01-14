/** 
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Shenay Abdrahim
* @idnumber 3MI0600485
* @compiler GCC 
*
* < >
*
*/
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

typedef pair<long long, long long>    Fraction    ;
typedef pair<Fraction, unsigned int>     Monomial    ;
typedef pair<vector<Monomial>, unsigned int >  Polynomial  ;

int fromCharToInt(char a);
long long findGCD(long long a, long long b);
int absValue(int num);
Fraction inputFraction();
Fraction simplifyFraction(long long numerator, long long denominator);
long long parseInteger(const char* str, int index);
Monomial inputMonomial();
Polynomial inputPolynomial(int power);



// vector<pair<int, double>> inputPolynomial(){
//     vector<pair<int,double>> polynomial;
//     int degree;
//     double coefficient;

//     cout << "Enter the number of terms in the polynomial: ";
//     int numTerms;
//     cin >> numTerms;

//     for( int i = 0; i < numTerms; ++i){
//         cout << ""
//     }

// }
int fromCharToInt(char a) {
    return a - '0';
}
long long findGCD(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int absValue(int num) {
    if(num < 0)
        return -num;
    
        return num;
}
//Simplify the fraction
Fraction simplifyFraction(long long numerator, long long denominator) {
    long long gcd = findGCD(absValue(numerator), absValue(denominator));
    numerator /= gcd;
    denominator /= gcd;

    // Ensure the denominator is positive
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }

    return {numerator, denominator};
}


long long parseInteger(const char* str, int index) {
    long long result = 0;
    bool isNegative = false;

    // Check if the number is negative
    if (str[index] == '-') {
        isNegative = true;
        index++;
    }

    // Convert characters to digits
    while (str[index] >= '0' && str[index] <= '9') {
        result = result * 10 + fromCharToInt(str[index]);
        index++;
    }

    return isNegative ? -result : result;
}


void manageOptions() {
    unsigned int option = 0;
    
    cout << "Enter your option here>> ";
    cin >> option;
}
//     switch(option) {
//         case 1: {
//             Polynomial polynomial1 = inputPolynomial("P(x)");
//             printPolynomial("P(x)", polynomial1);

//             cout<<endl;

//             Polynomial polynomial2 = inputPolynomial("Q(x)");
//             printPolynomial("Q(x)", polynomial2);

//             printPolynomial("P(x) + Q(x)", additionalPolynomials(polynomial1, polynomial2));
            
//             return;
//         }
//         case 2: return; 
//         case 3: return;
//         case 4: return;
//         case 5: return;
//         case 6: return;
//         case 7: return;
//         case 8: {
//             Polynomial polynomial = inputPolynomial("P(x)");
//             cout << "Vieta's Formulas for polynomial: ";
//             printPolynomial("P(x)", polynomial);

//             cout << endl;

//             generateVieta(polynomial);

//             return;
//         }
//         case 9: return;
//         case 10: return;
//         case 11: return;
//         default:
//         cout<<"Invalid option for functionality!"<<endl;
//     }

// }
Fraction inputFraction()  {
    //cout << "Enter a fraction (format: numerator/denominator or just numerator): ";

    char input[50];
    cin >> input;

    long long numerator = 0, denominator = 1;
    int index = 0;

    // Parse the numerator
    numerator = parseInteger(input, index);

    // Check for '/'
    if (input[index] == '/') {
        index++; // Skip the '/'
        // Parse the denominator
        denominator = parseInteger(input, index);
    }

    // Simplify the fraction
    return simplifyFraction(numerator, denominator);

}
Monomial inputMonomial(){
    //cout << "Enter monomial coefficient (fractional form):\n";
    Fraction coefficient = inputFraction();

    unsigned int exponent;
    cout << "Enter exponent(non- negative integer): ";
    cin >> exponent;
    
    return {coefficient, exponent};

}
Polynomial inputPolynomial(int power) {
    Polynomial polynomial;

    for (int i = power; i >= 0; i--){
        cout << "Enter coefficient before x^" << i << ">>  ";
        Monomial monomial = inputMonomial();
        polynomial.first.push_back(monomial);
    }
    return polynomial;
}

// void printPolynomial(const Polynomial& polynomial) {

//     for (int i = polynomial.first.size() - 1; i >= 0; i--){

//         long long num = polynomial.first[i].first.first;
//     }
    

// }
void printPolynomial(const Polynomial& polynomial) {
    // Iterate over the monomials in reverse order
    for (unsigned int i = 0; i < polynomial.first.size(); i++) {
        // Access the Monomial
        Monomial monomial = polynomial.first[i];
        
        // Access the Fraction and degree
        Fraction fraction = monomial.first;
        unsigned int degree = monomial.second;

        // Print the Fraction (numerator/denominator)
        cout << fraction.first;
        if(fraction.second != 1)
            cout << "/" << fraction.second;
        
        // Print the degree (x^degree)
        if (degree > 0) {
            std::cout << "x^" << degree;
        }

        // Add a "+" between terms, except the last one
        if (i < polynomial.first.size()-1) {
            std::cout << " + ";
        }
    }

    // End the line after printing the polynomial
    std::cout << std::endl;
}
void showInformation() {
    cout << "Welcome to Polynomial Calculator - a mini"
         << "project intented to work with polynomials"; 
    cout << "with rational coefficients!\n";
    cout << "Choose one of the following functionalities:\n";
    cout << "1) Add polynomials\n";
    cout << "2) Substract polynomials\n";
    cout << "3) Multiply polynomials\n";
    cout << "4) Divide polynomials\n";
    cout << "5) Multiply polynomial by scalar\n";
    cout << "6) Find value of polynomial by scalar\n";
    cout << "7) Find GCD of two polynomials\n";
    cout << "8) Display Vieta's formulas for given polynomial\n";
    cout << "9) Represent a polynomial in powers of (x+a)\n";
    cout << "10) Factor polynomial and find its rational roots\n";
    cout << "11) Quit program\n"<<endl;
}
int main(){
    Polynomial p=inputPolynomial(5);
     printPolynomial(p);




    
}