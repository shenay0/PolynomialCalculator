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
Polynomial subtractPolynomials(const Polynomial& polynomial1, const Polynomial& polynomial2);
Fraction subtractFractions(const Fraction& f1, const Fraction& f2);
void multiplyPolynomials(const Polynomial& polynomial1, const Polynomial& polynomial2);
Fraction multiplyPolynomial(const Fraction& f1, const Fraction& f2);
void multiplyByScalar(const Polynomial& polynomial1, const Fraction& scalar);
Fraction multiplyFractionByScalar(const Fraction& f1, const Fraction& scalar);
Fraction evaluatePolynomial(const Polynomial& polynomial, const Fraction& scalar);
Fraction powerFraction(const Fraction& fraction, unsigned int exp);
void printFraction(const Fraction& fraction);
pair<Polynomial, Polynomial> dividePolynomials(const Polynomial& dividend, const Polynomial& divisor);
Fraction divideFractions(const Fraction& f1, const Fraction& f2);

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
    else if( denominator == 0) {
        cout << "Denominator cannot be 0, defaulting it to 1" << endl;
        denominator = 1;
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
Fraction powerFraction(const Fraction& fraction, unsigned int exp) {
    long long numerator = 1;
    long long denominator = 1;

    for (unsigned int i = 0; i < exp; ++i) {
        numerator *= fraction.first;
        denominator *= fraction.second;
    }

    return simplifyFraction(numerator, denominator);
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

Fraction divideFractions(const Fraction& f1, const Fraction& f2) {
    long long numerator = f1.first * f2.second;
    long long denominator = f1.second * f2.first;
    return simplifyFraction(numerator, denominator);
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
Fraction multiplyFractionByScalar(const Fraction& f1, const Fraction& scalar){
    long long numerator = f1.first * scalar.first;
    long long denominator = f1.second * scalar.second;
    return {numerator, denominator};
}

pair<Polynomial, Polynomial> dividePolynomials(const Polynomial& dividend, const Polynomial& divisor) {
    Polynomial quotient;
    Polynomial remainder = dividend;

    while (!remainder.empty() && remainder[0].second >= divisor[0].second) {
        // Calculate the leading term of the quotient
        Fraction leadCoeff = divideFractions(remainder[0].first, divisor[0].first);
        unsigned int leadPower = remainder[0].second - divisor[0].second;
        Monomial leadTerm = {leadCoeff, leadPower};
        quotient.push_back(leadTerm);

        // Subtract the product of divisor and lead term from remainder
        Polynomial temp;
        for (size_t j = 0; j < divisor.size(); ++j) {
            const Monomial& monomial = divisor[j];
            Fraction coeff = multiplyFractions(monomial.first, leadCoeff);
            unsigned int power = monomial.second + leadPower;
            temp.push_back({coeff, power});
        }

        
        remainder = subtractPolynomials(remainder, temp);

        
    }

    return {quotient, remainder};
}


void generateVietaFormulas(const Polynomial& poly) {
    // Ensure the polynomial has enough terms
    if (poly.empty()) {
        cout << "Error: Polynomial is empty." << endl;
        return;
    }

    unsigned int degree = poly.size() - 1;  // Degree of the polynomial

    // Leading coefficient a_n
    Fraction a_n = poly[0].first;  // The first term corresponds to the highest degree (reversed order)

    cout << "Vieta's Formulas for the polynomial:" << endl;

    // Loop through terms to calculate Vieta's formulas
    for (unsigned int k = 1; k <= degree; ++k) {
        if (k <= degree) {
            Fraction a_k = poly[k].first;  
            Fraction term = divideFractions(
                {(((k + 1) % 2 == 0) ? -a_k.first : a_k.first), a_k.second},
                {a_n.first, a_n.second}
            );
            cout << "Sum  " << k << ": "<< term.first << "/" << term.second << endl;
        }
    }
}

Fraction evaluatePolynomial(const Polynomial& polynomial, const Fraction& scalar) {
    Fraction result = {0, 1}; // Initialize as zero 
    unsigned int n = polynomial.size();
    
    for (size_t i = 0; i < n; ++i) {
        const Fraction& coefficient = polynomial[i].first;
        unsigned int exponent = polynomial[i].second;

        // Compute scalar^exponent
        Fraction scalarPower = powerFraction(scalar, exponent);
        
        // Multiply the coefficient by scalar^exponent
         Fraction termValue = multiplyFractions(coefficient, scalarPower);

        // Add the term value to the result
        result = addFractions(result, termValue);
    }

    return result;
}

void multiplyByScalar (const Polynomial& polynomial, const Fraction& scalar) {
    Polynomial result;
    size_t n = polynomial.size();

    for( size_t i = 0; i < n; i++)  {
        // multiply i- monomial's coefficient by the scalar
        Fraction newCoefficient = multiplyFractions(polynomial[i].first, scalar);
        
        result.push_back({newCoefficient, polynomial[i].second});
    }

    printPolynomial(result);
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

   
Polynomial subtractPolynomials(const Polynomial& poly1, const Polynomial& poly2) {
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
        return result;
    
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
    cout << "P(x) + Q(x) = ";
    printPolynomial(result);
}
pair <Polynomial,Polynomial> inputTwoPolynomials() {
    cout << "Enter Polynomial P(x)>> \n";
    Polynomial polynomial1 = inputPolynomial();
    cout << "P(x)= ";
    printPolynomial(polynomial1);
    cout << endl;

    cout << "Enter Polynomial Q(x)>> \n";
    Polynomial polynomial2 = inputPolynomial();
    cout << "Q(x)= ";
    printPolynomial(polynomial2);
    cout << endl;
    return {polynomial1, polynomial2};
}
void manageOptions() {
    unsigned int option = 0;
    do {
    cout << endl;
    cout << "Enter your option here>> ";
    cin >> option;
    cout << endl;

    switch(option) {
        case 1: {
            pair <Polynomial,Polynomial> polynomials= inputTwoPolynomials();
            addPolynomials(polynomials.first,polynomials.second);
            break;
        }
        case 2:{
            pair <Polynomial,Polynomial> polynomials= inputTwoPolynomials();
            Polynomial poly = subtractPolynomials(polynomials.first,polynomials.second);
            cout << "P(x) - Q(x) = ";
            printPolynomial(poly);
            break; 
        }
        case 3: {
            pair <Polynomial,Polynomial> polynomials= inputTwoPolynomials();
            multiplyPolynomials(polynomials.first,polynomials.second);
            break;
        }
        case 4: {
            pair <Polynomial,Polynomial> polynomials= inputTwoPolynomials();
            Polynomial quotient = dividePolynomials(polynomials.first,polynomials.second).first;
            cout << "Quotient: ";
            printPolynomial(quotient);
            Polynomial reminder = dividePolynomials(polynomials.first,polynomials.second).second;
            cout << "Reminder: ";
            printPolynomial(reminder);
            break;
        }
        case 5: {
            cout << "Enter Polynomial P(x): ";
            Polynomial polynomial = inputPolynomial();
            cout << "P(x): ";
            printPolynomial(polynomial);
            cout << "Enter rational number>> " << endl;
            Fraction scalar = inputFraction();
            multiplyByScalar(polynomial, scalar);
            break;
        }
        case 6: {
            cout << "Enter Polynomial P(x): ";
            Polynomial polynomial = inputPolynomial();
            cout << "P(x): ";
            printPolynomial(polynomial);
            Fraction number = inputFraction();
            Fraction result = evaluatePolynomial(polynomial, number);
            cout << "P("; 
            printFraction(number);
            cout << ") = ";
            printFraction(result);
            break;
        }
        case 7: return;
        case 8: {
            cout << "Enter Polynomial P(x)" << endl;
            Polynomial polynomial = inputPolynomial();
            cout << endl;

            cout << "Vieta's Formulas for polynomial: P(x) = ";
            printPolynomial(polynomial);
            generateVietaFormulas(polynomial);

            break;
        }
        case 9: return;
        case 10: return;
        default:
        cout<<"Invalid option for functionality!"<<endl;
        return;
    }
    } while(option != 11);

}
Fraction inputFraction()  {
    
    char input[50];
    cin >> input;

    long long numerator = 0, denominator = 1;
    int index = 0;
    // Parse the numerator
    numerator = parseInteger(input, index);
    if (input[0] == '-') {
        index++;
    }
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
    bool firstTerm = true; // Used to format the first term correctly

    for (unsigned int i = 0; i < n; i++) {
        // Extract monomial
        const Monomial& monomial = polynomial[i];

        // Extract fraction (coefficient) and degree
        const Fraction& fraction = monomial.first;
        long long numerator = fraction.first;
        long long denominator = fraction.second;
        unsigned int degree = monomial.second;

        // Skip terms with a coefficient of 0
        if (numerator == 0) {
            continue;
        }

        // Handle signs and spacing properly
        if (!firstTerm) {
            if (numerator > 0) {
                cout << " + ";
            } else {
                cout << " - ";
            }
        } else {
            if (numerator < 0) {
                cout << "-";
            }
        }

        // Print absolute value of numerator
        bool isOne = (absValue(numerator) == 1 && denominator == 1);
        if(!isOne || degree == 0){
        cout << absValue(numerator);
        }
        // Print denominator only if it's not 1
        if (denominator != 1) {
            cout << "/" << denominator;
        }

        // Print variable and exponent
        if (degree > 0) {
            cout << "x";
            if (degree > 1) {
                cout << "^" << degree;
            }
        }

        firstTerm = false; // First term handled, format remaining correctly
    }

    // If all terms were 0, print just 0
    if (firstTerm) {
        cout << "0";
    }

    cout << endl;
}
 
void printFraction(const Fraction& fraction) {
    cout << fraction.first; // Print the numerator
    if (fraction.second != 1) { // Print the denominator only if it's not 1
        cout << "/" << fraction.second;
    }
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
    showInformation();
    manageOptions();
    
}