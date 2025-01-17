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
typedef pair<Fraction, unsigned int>   Monomial    ;
typedef vector <Monomial>  Polynomial  ;

int fromCharToInt(char a);
long long findGCD(long long a, long long b);
int absValue(int num);
Fraction inputFraction();
Fraction simplifyFraction(long long numerator, long long denominator);
long long parseInteger(const char* str, int index);
Monomial inputMonomial(unsigned int power);
Polynomial inputPolynomial();
void printPolynomial(const Polynomial& polynomial);
//void manageOptions();
void addPolynomials(const Polynomial& polynomial1, const Polynomial& polynomial2);
Fraction addFractions(const Fraction& f1, const Fraction& f2);
void subtractPolynomials(const Polynomial& polynomial1, const Polynomial& polynomial2);
Fraction subtractFractions(const Fraction& f1, const Fraction& f2);
void multiplyPolynomials(const Polynomial& polynomial1, const Polynomial& polynomial2);
Fraction multiplyPolynomial(const Fraction& f1, const Fraction& f2);


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

Fraction addFractions(const Fraction& f1, const Fraction& f2) {
    long long numerator1 = f1.first;
    long long denominator1 = f1.second;
    long long numerator2 = f2.first;
    long long denominator2 = f2.second;

    long long commonDenominator = denominator1 * denominator2;
    long long newNumerator = numerator1 * denominator2 + numerator2 * denominator1;
   
    return simplifyFraction(newNumerator, commonDenominator);
}

Fraction subtractFractions(const Fraction& f1, const Fraction& f2){
    long long numerator1 = f1.first;
    long long denominator1 = f1.second;
    long long numerator2 = f2.first;
    long long denominator2 = f2.second;

    long long commonDenominator = denominator1 * denominator2;
    long long newNumerator = numerator1 * denominator2 - numerator2 * denominator1;
    return simplifyFraction(newNumerator, commonDenominator);
}

Fraction multiplyFractions(const Fraction& f1, const Fraction& f2) {
    long long numerator = f1.first * f2.first;
    long long denominator = f1.second * f2.second;
    return simplifyFraction(numerator, denominator);
}
void multiplyPolynomials(const Polynomial& polynomial1, const Polynomial& polynomial2) {
    Polynomial result;

    // Multiply each monomial from p1 with each monomial from p2
    for (size_t i = 0; i < polynomial1.size(); ++i) {
        for (size_t j = 0; j < polynomial2.size(); ++j) {
            // Get the monomials
            Monomial monomial1 = polynomial1[i];
            Monomial monomial2 = polynomial2[j];

            // Multiply coefficients (fractions)
            Fraction newCoefficient = multiplyFractions(monomial1.first, monomial2.first);
            // Add exponents
            unsigned int newExponent = monomial1.second + monomial2.second;

            // Check if a term with the same exponent already exists in the result
            bool found = false;
            for (size_t k = 0; k < result.size(); ++k) {
                if (result[k].second == newExponent) {
                    // Add coefficients
                    result[k].first = addFractions(result[k].first, newCoefficient);
                    found = true;
                    break;
                }
            }

            // If no term with the same exponent exists, add a new term
            if (!found) {
                result.push_back({newCoefficient, newExponent});
            }
        }
    }

    printPolynomial(result);
}

   
void subtractPolynomials(const Polynomial& poly1, const Polynomial& poly2) {
    Polynomial result;
    unsigned int i = 0, j = 0;

    
    while (i < poly1.size() || j < poly2.size()) {
        if (i < poly1.size() && (j >= poly2.size() || poly1[i].second > poly2[j].second)) {
            // If polynomial1 has a term with a higher power, add it directly to the result
            result.push_back(poly1[i]);
            i++;
        } 
        else if (j < poly2.size() && (i >= poly1.size() || poly2[j].second > poly1[i].second)) {
            // If polynomial2 has a term with a higher power, add it as a negative to the result
            Fraction negCoefficient = Fraction(-poly2[j].first.first, poly2[j].first.second);
            result.push_back(Monomial(negCoefficient, poly2[j].second));
            j++;
        } 
        else { 
            // If both polynomials have terms with the same power, subtract their coefficients
            Fraction newCoefficient = subtractFractions(poly1[i].first, poly2[j].first);
            if (newCoefficient.first != 0) { // Skip zero coefficients
                result.push_back(Monomial(newCoefficient, poly1[i].second));
            }
            i++;
            j++;
        }
    }
        printPolynomial(result);
    
}
void addPolynomials(const Polynomial& polynomial1, const Polynomial& polynomial2) {
    Polynomial result;
    unsigned int i = 0, j = 0;
    
    
    while (i < polynomial1.size() || j < polynomial2.size()) {
        if (i < polynomial1.size() && (j >= polynomial2.size() || polynomial1[i].second > polynomial2[j].second)) {
            // If polynomial1 has a term with a higher power, add it directly to the result
            result.push_back(polynomial1[i]);
            i++;
        } 
        else if (j < polynomial2.size() && (i >= polynomial1.size() || polynomial2[j].second > polynomial1[i].second)) {
            // If polynomial2 has a term with a higher power, add it directly to the result
            result.push_back(polynomial2[j]);
            j++;
        } 
        else { 
            // If both polynomials have terms with the same power, add their coefficients
            Fraction newCoefficient = addFractions(polynomial1[i].first, polynomial2[j].first);
            result.push_back(Monomial(newCoefficient, polynomial1[i].second));
            i++;
            j++;
        }
    }
    
    printPolynomial(result);
}
// void manageOptions() {
//     unsigned int option = 0;
    
//     cout << "Enter your option here>> ";
//     cin >> option;

//     switch(option) {
//         case 1: {
//             cout << "Enter Polynomial P(x): \n" << endl;
//             Polynomial polynomial1 = inputPolynomial();
//             printPolynomial(polynomial1);

//             cout<<endl;

//             cout << "Enter Polynomial Q(x): " << endl;
//             Polynomial polynomial2 = inputPolynomial();
//             printPolynomial( polynomial2);


//             cout << "P(x) + Q(x): ";
//             addPolynomials(polynomial1, polynomial2);
            
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
    
    char input[50];
    cin >> input;

    long long numerator = 0, denominator = 1;
    int index = 0;

    // Parse the numerator
    numerator = parseInteger(input, index);
    index++;
    // Check for '/'
    if (input[index] == '/') {
        index++; // Skip the '/'
        // Parse the denominator
        denominator = parseInteger(input, index);
    }

    
    return simplifyFraction(numerator, denominator);

}

Monomial inputMonomial(unsigned int power){
    
    Fraction coefficient = inputFraction();

    return {coefficient, power};

}

Polynomial inputPolynomial() {
    Polynomial polynomial;
    
    unsigned int power;
    cout << "Enter degree of your Polynomial: " << endl;
    cin >> power;

    for (int i = power; i >= 0; i--){
        cout << "Enter coefficient before x^" << i << ">>  ";
        Monomial monomial = inputMonomial(i);
        polynomial.push_back(monomial);
    }
    return polynomial;
}


void printPolynomial(const Polynomial& polynomial) {
    
    int n = polynomial.size();
    for (unsigned int i = 0; i < n; i++) {
        
        // Access the Monomial
        Monomial monomial = polynomial[i];
        
        // Access the Fraction and degree
        Fraction fraction = monomial.first;
        unsigned int degree = monomial.second;

        if( fraction.first < 0 || fraction.second < 0 ) {
            cout << " - ";
        }
        else if (i > 0 && fraction.first > 0) {
            cout << " + ";
        }
        // Print the Fraction (numerator/denominator)
        cout << absValue(fraction.first);
        if(fraction.second != 1){
            cout << "/" << fraction.second;
        }
        // Print the degree (x^degree)
        if (degree > 0) {
            std::cout << "x^" << degree;
            
        }
        
    }

    // End the line after printing the polynomial
    cout << endl;
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
    cout<<"p"<<endl;
    Polynomial p=inputPolynomial();
    
    cout<<"t"<<endl;
    Polynomial t= inputPolynomial(); 
     
     cout<<endl;
     multiplyPolynomials(p,t);
}