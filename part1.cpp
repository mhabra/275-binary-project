#include <cassert>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

int toBinary(int num, bool print);
int binSubtract(int binNum1, int binNum2, bool print);
pair<int, int> binDivision(int binNum1, int binNum2, bool print);
int getChoice();
bool getPrint();
void doMath(int choice);
void tests();
void printWelcomeMessage();

int main() {
    printWelcomeMessage();
    int choice = getChoice();
    doMath(choice);
    return 0;
}

// takes a POSITIVE decimal integer and converts it to binary using
int toBinary(int num, bool print) {
    int og = num;
    if (print) {
        cout << "Converting " << og << " to binary: \n\n";
    }

    string binNum = "";

    if (num == 0) {
        binNum = "0";
    }

    while (num != 0) {
        int rem = num % 2;
        binNum.insert(0, to_string(rem));
        if (print) {
            cout << num << " NOT EQUAL to 0 \n";
            cout << "Remainder = " << num << " mod 2 = " << rem << "\n";
            cout << "New quotient = " << num << " div 2 = " << num / 2 << "\n\n";
        }
        num /= 2;
    }

    if (print) {
        cout << og << " in binary is " << binNum << "\n\n\n";
    }
    return (stoi(binNum));
}

// takes in two binary numbers and subtracts binNum2 from binNum1
// requires binNum1 > binNum2
int binSubtract(int binNum1, int binNum2, bool print) {
    int borrow = 0;
    string strNum1 = to_string(binNum1);
    string strNum2 = to_string(binNum2);
    while (strNum1.length() != strNum2.length()) {
        strNum2.insert(0, "0");
    }
    int size = to_string(binNum1).length();
    string diff = "";

    if (print) {
        cout << strNum1 << " - \n" << strNum2 << endl << endl;
    }
    for (int i = size; i > 0; i--) {
        string dig1(1, strNum1.at(i - 1));
        string dig2(1, strNum2.at(i - 1));

        if (stoi(dig1) >= (stoi(dig2) + borrow)) {
            int digit = stoi(dig1) - stoi(dig2) - borrow;

            if (print) {
                cout << "Right now borrow is: " << borrow << endl;
                cout << dig1 << " >= (" << dig2 << " + " << borrow << ")\n";
                cout << "Thus digit of answer is: " << stoi(dig1) << " - " << stoi(dig2)
                     << " - " << borrow << " =    " << digit << endl;
                cout << "Borrow becomes 0\n\n";
            }
            borrow = 0;
            diff.insert(0, to_string(digit));

        } else {
            if (print) {
                cout << "Right now borrow is: " << borrow << endl;
                cout << dig1 << " < (" << dig2 << " + " << borrow << ")\n";
            }
            int digit = stoi(dig1) + 2 - stoi(dig2) - borrow;

            if (print) {
                cout << "Thus digit of answer is: " << stoi(dig1) << " + 2 - "
                     << stoi(dig2) << " - " << borrow << " =    " << digit << endl;
                cout << "Borrow becomes 1\n\n";
            }
            borrow = 1;
            diff.insert(0, to_string(digit));
        }
    }

    if (print) {
        cout << strNum1 << " - " << strNum2
             << " in binary will be all of the digits: " << diff << endl
             << endl;
    }
    return (stoi(diff));
}

// returns pair that is quotient (div) and remainder (mod) of binNum 1 / binNum2
// first is div, second is mod
// uses repeated subtraction
pair<int, int> binDivision(int binNum1, int binNum2, bool print) {
    int quotient = 0;
    int ogbinNum1 = binNum1;

    if (print) {
        cout << "Dividing " << binNum1 << " by " << binNum2
             << " using repeated subtraction:" << endl;
    }

    while (binNum1 >= binNum2) {
        int old = binNum1;  // needed for line 94 to print out the og binNum1
        binNum1 = binSubtract(binNum1, binNum2, print);

        ++quotient;
        if (print) {
            cout << "Having subtracted " << quotient << " times: \n";
            cout << old << " - " << binNum2 << " = " << binNum1;
            if (binNum1 >= binNum2) {
                cout << " is greater than " << binNum2 << ", so we subtract again" << endl
                     << endl;
            } else {
                cout << " is less than " << binNum2
                     << ". We do not subtract again. This makes " << binNum1
                     << " our remainder (mod).\n";
            }
        }
    }

    int binQuotient = toBinary(quotient, false);  // converts quotient to binary
    int remainder = binNum1;

    if (print) {
        cout << "We subtracted " << quotient << " times. Thus, our binary quotient is "
             << binQuotient;
        cout << "\n\nThe div (quotient) of " << ogbinNum1 << " / " << binNum2
             << " in binary is " << binQuotient << endl;
        cout << "The mod (remainder) is " << remainder << endl;
    }

    pair<int, int> divMod(binQuotient, remainder);

    return divMod;
}

// prints welcome message
void printWelcomeMessage() {
    cout << "1. Run main program (input decimal numbers, which are converted to binary, "
            "and then divided)\n2. Convert number into binary\n3. Subtract two "
            "binary numbers\n4. Divide (find div and mod) of two binary numbers\n\n";
}

void tests() {
    assert(toBinary(17, false) != 1);
    assert(toBinary(17, false) == 10001);
    assert(toBinary(23, false) == 10111);
    assert(toBinary(11, false) == 1011);
    assert(binSubtract(1, 1, false) == 0);
    assert(binSubtract(111, 1, false) == 110);
    assert(binSubtract(1, 1, false) == 0);
    assert(binSubtract(11101, 11011, false) == 10);
}

// gets choice of user from welcome message
int getChoice() {
    cout << "Enter choice: ";
    int choice;
    cin >> choice;
    cout << endl;
    return choice;
}

// asks user if he wants to print steps and returns true if yes and false if no
bool getPrint() {
    cout << "Do you wish to print steps? Enter 'y' for yes or 'n' for no: ";
    bool print;
    char choice;
    cin >> choice;

    if (choice == 'y') {
        print = true;
    } else {
        print = false;
    }

    return print;
}

// gets numerical input for each choice and print choice and passes that input to
// appropriate math function
void doMath(int choice) {
    if (choice == 1) {
        int num1;
        cout << "Running main program:\nEnter first number (dividend): ";
        cin >> num1;
        int num2;
        cout << "Enter second number (divisor): ";
        cin >> num2;

        bool print = getPrint();

        int binDividend = toBinary(num1, print);

        int binDivisor = toBinary(num2, print);

        pair<int, int> divMod = binDivision(binDividend, binDivisor, print);

        if (!print) {
        cout << "Div is " << divMod.first << " and mod is " << divMod.second;

        }

        return;
    }

    if (choice == 2) {
        cout << "Enter number to convert to binary: ";
        int convertNum;
        cin >> convertNum;
        bool print = getPrint();
        int answer = toBinary(convertNum, print);
        cout << "Answer is " << answer;
    }

    else if (choice == 3) {
        cout << "Enter the binary minuend: ";
        int minuend;
        cin >> minuend;

        cout << "Enter the binary subtrahend: ";
        int subtrahend;
        cin >> subtrahend;
        bool print = getPrint();
        int answer = binSubtract(minuend, subtrahend, print);
        cout << "Answer is " << answer;

    }

    else {
        cout << "Enter the binary dividend: ";
        int dividend;
        cin >> dividend;

        cout << "Enter the binary divisior: ";
        int divisior;
        cin >> divisior;
        bool print = getPrint();
        pair<int, int> divMod = binDivision(dividend, divisior, print);

        cout << "Div is " << divMod.first << " and mod is " << divMod.second;
    }
    return;
}
