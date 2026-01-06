#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <map>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<long long> memo;

// All function declarations
void mainMenu();
void clearScreen();

// Fibonacci Sequence functions
void fibonacciCalculator();
long long fibonacci_iterative(int n);
long long fibonacci_recursive(int n);
long long fibonacci_memoized(int n, vector<long long>& memo);
vector<long long> fibonacci_sequence(int n);

// Lucas Sequence functions
void lucasCalculator();
long long lucas_iterative(int n);
long long lucas_recursive(int n);
long long lucas_memoized(int n, vector<long long>& memo);
vector<long long> lucas_sequence(int n);

// Tower of Hanoi functions
void towerOfHanoi();
void tower_of_hanoi_recursive(int n, char from, char to, char aux, int& step);
void tower_of_hanoi_iterative(int n);
void display_towers(int n, const vector<stack<int>>& rods);

// Efficiency Calculator functions
int efficiencyCalculator();
void measureFibonacciTime();
void measureLucasTime();
void measureHanoiTime();

// Graph Visualizer functions
void graphVisualizer();
void printFibonacciGraph(int n);
void printLucasGraph(int n);
void printHanoiGraph(int n);

// Utility functions
void pressEnterToContinue();
void displayHeader(const string& title);

int main() {
    int input;
    do {
        clearScreen();
        mainMenu();
        cin >> input;

        switch(input) {
            case 0:
                cout << "Thank you for using Recursive Sequence Analyzer!" << endl;
                break;
            case 1:
                fibonacciCalculator();
                break;
            case 2:
                lucasCalculator();
                break;
            case 3:
                towerOfHanoi();
                break;
            case 4:
                efficiencyCalculator();
                break;
            case 5:
                graphVisualizer();
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                pressEnterToContinue();
                break;
        }
    } while(input != 0);
    
    return 0;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pressEnterToContinue() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void displayHeader(const string& title) {
    cout << "\n" << string(60, '=') << endl;
    cout << setw((60 + title.length()) / 2) << title << endl;
    cout << string(60, '=') << endl << endl;
}

void mainMenu() {
    cout << "\n" << string(50, '_') << endl;
    cout << "::::::::RECURSIVE SEQUENCE ANALYZER::::::::" << endl;
    cout << string(50, '_') << endl;
    cout << "Choose from the following menu:" << endl;
    cout << "1. Fibonacci Sequence Term Calculator" << endl;
    cout << "2. Lucas Sequence Term Calculator" << endl;
    cout << "3. Tower Of Hanoi Step Calculator" << endl;
    cout << "4. Time and Space Complexity Calculator" << endl;
    cout << "5. Visual Graphs" << endl;
    cout << "0. End Program" << endl;
    cout << "Enter your choice: ";
}

// ========== FIBONACCI CALCULATOR ==========
void fibonacciCalculator() {
    int choice;
    do {
        clearScreen();
        displayHeader("FIBONACCI SEQUENCE CALCULATOR");
        
        cout << "1. Calculate single term" << endl;
        cout << "2. Display sequence up to nth term" << endl;
        cout << "3. Compare iterative vs recursive vs memoized" << endl;
        cout << "0. Back to main menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        int n;
        cout << "Enter term position (starting from 0): ";
        cin >> n;
        
        if (n < 0) {
            cout << "Error: Position must be non-negative!" << endl;
            pressEnterToContinue();
            continue;
        }
        
        vector<long long> memo_vec(n + 1, -1);
        
        switch(choice) {
            case 1: {
                cout << "\nFibonacci(" << n << ") = " << fibonacci_iterative(n) << endl;
                pressEnterToContinue();
                break;
            }
            case 2: {
                vector<long long> seq = fibonacci_sequence(n);
                cout << "\nFibonacci sequence up to term " << n << ":" << endl;
                cout << string(30, '-') << endl;
                for (int i = 0; i <= n; i++) {
                    cout << "F(" << i << ") = " << seq[i] << endl;
                }
                pressEnterToContinue();
                break;
            }
            case 3: {
                if (n > 40) {
                    cout << "Warning: Recursive method will be slow for n > 40!" << endl;
                    cout << "Continue anyway? (1=Yes, 0=No): ";
                    int continue_choice;
                    cin >> continue_choice;
                    if (!continue_choice) break;
                }
                
                cout << "\n" << string(40, '-') << endl;
                cout << "COMPARISON OF METHODS" << endl;
                cout << string(40, '-') << endl;
                
                // Iterative
                cout << "Iterative method:" << endl;
                cout << "Fibonacci(" << n << ") = " << fibonacci_iterative(n) << endl;
                
                // Recursive (only if n is small)
                if (n <= 30) {
                    cout << "\nRecursive method:" << endl;
                    cout << "Fibonacci(" << n << ") = " << fibonacci_recursive(n) << endl;
                } else {
                    cout << "\nRecursive method: Skipped (too large for n > 30)" << endl;
                }
                
                // Memoized
                cout << "\nMemoized method:" << endl;
                cout << "Fibonacci(" << n << ") = " << fibonacci_memoized(n, memo_vec) << endl;
                
                cout << string(40, '-') << endl;
                pressEnterToContinue();
                break;
            }
            default:
                cout << "Invalid choice!" << endl;
                pressEnterToContinue();
        }
    } while(choice != 0);
}

long long fibonacci_iterative(int n) {
    if (n <= 1) return n;
    
    long long a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        long long next = a + b;
        a = b;
        b = next;
    }
    return b;
}

long long fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n-1) + fibonacci_recursive(n-2);
}

long long fibonacci_memoized(int n, vector<long long>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    
    memo[n] = fibonacci_memoized(n-1, memo) + fibonacci_memoized(n-2, memo);
    return memo[n];
}

vector<long long> fibonacci_sequence(int n) {
    vector<long long> sequence;
    if (n < 0) return sequence;
    
    sequence.push_back(0);
    if (n >= 1) sequence.push_back(1);
    
    for (int i = 2; i <= n; i++) {
        sequence.push_back(sequence[i-1] + sequence[i-2]);
    }
    
    return sequence;
}

// ========== LUCAS CALCULATOR ==========
void lucasCalculator() {
    int choice;
    do {
        clearScreen();
        displayHeader("LUCAS SEQUENCE CALCULATOR");
        
        cout << "1. Calculate single term" << endl;
        cout << "2. Display sequence up to nth term" << endl;
        cout << "3. Compare iterative vs recursive vs memoized" << endl;
        cout << "0. Back to main menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        int n;
        cout << "Enter term position (starting from 0): ";
        cin >> n;
        
        if (n < 0) {
            cout << "Error: Position must be non-negative!" << endl;
            pressEnterToContinue();
            continue;
        }
        
        vector<long long> memo_vec(n + 1, -1);
        
        switch(choice) {
            case 1: {
                cout << "\nLucas(" << n << ") = " << lucas_iterative(n) << endl;
                pressEnterToContinue();
                break;
            }
            case 2: {
                vector<long long> seq = lucas_sequence(n);
                cout << "\nLucas sequence up to term " << n << ":" << endl;
                cout << string(30, '-') << endl;
                for (int i = 0; i <= n; i++) {
                    cout << "L(" << i << ") = " << seq[i] << endl;
                }
                pressEnterToContinue();
                break;
            }
            case 3: {
                if (n > 40) {
                    cout << "Warning: Recursive method will be slow for n > 40!" << endl;
                    cout << "Continue anyway? (1=Yes, 0=No): ";
                    int continue_choice;
                    cin >> continue_choice;
                    if (!continue_choice) break;
                }
                
                cout << "\n" << string(40, '-') << endl;
                cout << "COMPARISON OF METHODS" << endl;
                cout << string(40, '-') << endl;
                
                // Iterative
                cout << "Iterative method:" << endl;
                cout << "Lucas(" << n << ") = " << lucas_iterative(n) << endl;
                
                // Recursive (only if n is small)
                if (n <= 30) {
                    cout << "\nRecursive method:" << endl;
                    cout << "Lucas(" << n << ") = " << lucas_recursive(n) << endl;
                } else {
                    cout << "\nRecursive method: Skipped (too large for n > 30)" << endl;
                }
                
                // Memoized
                cout << "\nMemoized method:" << endl;
                if (n >= 0) memo_vec[0] = 2;
                if (n >= 1) memo_vec[1] = 1;
                cout << "Lucas(" << n << ") = " << lucas_memoized(n, memo_vec) << endl;
                
                cout << string(40, '-') << endl;
                pressEnterToContinue();
                break;
            }
            default:
                cout << "Invalid choice!" << endl;
                pressEnterToContinue();
        }
    } while(choice != 0);
}

long long lucas_iterative(int n) {
    if (n < 0) return -1;
    if (n == 0) return 2;
    if (n == 1) return 1;
    
    long long a = 2, b = 1;
    for (int i = 2; i <= n; i++) {
        long long next = a + b;
        a = b;
        b = next;
    }
    return b;
}

long long lucas_recursive(int n) {
    if (n < 0) return -1;
    if (n == 0) return 2;
    if (n == 1) return 1;
    return lucas_recursive(n-1) + lucas_recursive(n-2);
}

long long lucas_memoized(int n, vector<long long>& memo) {
    if (n == 0) return 2;
    if (n == 1) return 1;
    if (memo[n] != -1) return memo[n];
    
    memo[n] = lucas_memoized(n-1, memo) + lucas_memoized(n-2, memo);
    return memo[n];
}

vector<long long> lucas_sequence(int n) {
    vector<long long> seq;
    if (n < 0) return seq;
    
    if (n >= 0) seq.push_back(2);
    if (n >= 1) seq.push_back(1);
    
    for (int i = 2; i <= n; i++) {
        seq.push_back(seq[i-1] + seq[i-2]);
    }
    return seq;
}

// ========== TOWER OF HANOI ==========
void towerOfHanoi() {
    clearScreen();
    displayHeader("TOWER OF HANOI CALCULATOR");
    
    int n;
    cout << "Enter number of disks (1-10 recommended): ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Number of disks must be positive!" << endl;
        pressEnterToContinue();
        return;
    }
    
    int choice;
    cout << "\nChoose solution method:" << endl;
    cout << "1. Recursive solution with steps" << endl;
    cout << "2. Iterative solution" << endl;
    cout << "3. Calculate minimum moves only" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    
    cout << "\nMinimum moves required: " << (pow(2, n) - 1) << endl;
    
    switch(choice) {
        case 1: {
            cout << "\nRecursive solution steps:" << endl;
            cout << string(50, '-') << endl;
            int step = 0;
            tower_of_hanoi_recursive(n, 'A', 'C', 'B', step);
            cout << string(50, '-') << endl;
            cout << "Total steps: " << step << endl;
            break;
        }
        case 2: {
            cout << "\nIterative solution steps:" << endl;
            cout << string(50, '-') << endl;
            tower_of_hanoi_iterative(n);
            break;
        }
        case 3: {
            cout << "\nMinimum moves calculation:" << endl;
            cout << "Formula: 2^n - 1 = " << (pow(2, n) - 1) << endl;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
    }
    
    pressEnterToContinue();
}

void tower_of_hanoi_recursive(int n, char from, char to, char aux, int& step) {
    if (n == 1) {
        step++;
        cout << "Step " << step << ": Move disk 1 from rod " 
             << from << " to rod " << to << endl;
        return;
    }
    
    tower_of_hanoi_recursive(n - 1, from, aux, to, step);
    step++;
    cout << "Step " << step << ": Move disk " << n 
         << " from rod " << from << " to rod " << to << endl;
    tower_of_hanoi_recursive(n - 1, aux, to, from, step);
}

void tower_of_hanoi_iterative(int n) {
    // Using mathematical pattern
    char s = 'A', d = 'C', a = 'B';
    
    // If odd number of disks, swap destination and auxiliary
    if (n % 2 == 1) {
        d = 'B';
        a = 'C';
    }
    
    long long total_moves = pow(2, n) - 1;
    
    for (int move = 1; move <= total_moves; move++) {
        if (move % 3 == 1) {
            cout << "Step " << move << ": Move disk from rod " 
                 << s << " to rod " << d << endl;
        } else if (move % 3 == 2) {
            cout << "Step " << move << ": Move disk from rod " 
                 << s << " to rod " << a << endl;
        } else {
            cout << "Step " << move << ": Move disk from rod " 
                 << a << " to rod " << d << endl;
        }
    }
    cout << "Total steps: " << total_moves << endl;
}

// ========== EFFICIENCY CALCULATOR ==========
int efficiencyCalculator() {
    clearScreen();
    displayHeader("TIME AND SPACE COMPLEXITY CALCULATOR");
    
    cout << "Available analyses:" << endl;
    cout << "1. Fibonacci sequence complexities" << endl;
    cout << "2. Lucas sequence complexities" << endl;
    cout << "3. Tower of Hanoi complexities" << endl;
    cout << "4. Compare all methods" << endl;
    cout << "Enter choice: ";
    
    int choice;
    cin >> choice;
    
    switch(choice) {
        case 1:
            measureFibonacciTime();
            break;
        case 2:
            measureLucasTime();
            break;
        case 3:
            measureHanoiTime();
            break;
        case 4: {
            cout << "\n" << string(60, '-') << endl;
            cout << "COMPARISON OF COMPLEXITIES" << endl;
            cout << string(60, '-') << endl;
            cout << setw(20) << "Algorithm" << setw(15) << "Time" << setw(15) << "Space" << endl;
            cout << string(60, '-') << endl;
            cout << setw(20) << "Fibonacci Iterative" << setw(15) << "O(n)" << setw(15) << "O(1)" << endl;
            cout << setw(20) << "Fibonacci Recursive" << setw(15) << "O(2^n)" << setw(15) << "O(n)" << endl;
            cout << setw(20) << "Fibonacci Memoized" << setw(15) << "O(n)" << setw(15) << "O(n)" << endl;
            cout << setw(20) << "Lucas Iterative" << setw(15) << "O(n)" << setw(15) << "O(1)" << endl;
            cout << setw(20) << "Lucas Recursive" << setw(15) << "O(2^n)" << setw(15) << "O(n)" << endl;
            cout << setw(20) << "Tower of Hanoi" << setw(15) << "O(2^n)" << setw(15) << "O(n)" << endl;
            cout << string(60, '-') << endl;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
    }
    
    pressEnterToContinue();
    return 0;
}

void measureFibonacciTime() {
    cout << "\nFibonacci Algorithm Complexities:" << endl;
    cout << string(50, '-') << endl;
    cout << "1. Iterative:" << endl;
    cout << "   Time: O(n)" << endl;
    cout << "   Space: O(1)" << endl;
    cout << "   Best for: Large n" << endl;
    
    cout << "\n2. Recursive:" << endl;
    cout << "   Time: O(2^n) (Exponential!)" << endl;
    cout << "   Space: O(n) (Call stack)" << endl;
    cout << "   Best for: Small n, educational purposes" << endl;
    
    cout << "\n3. Memoized:" << endl;
    cout << "   Time: O(n)" << endl;
    cout << "   Space: O(n)" << endl;
    cout << "   Best for: Multiple queries" << endl;
}

void measureLucasTime() {
    cout << "\nLucas Algorithm Complexities:" << endl;
    cout << string(50, '-') << endl;
    cout << "1. Iterative:" << endl;
    cout << "   Time: O(n)" << endl;
    cout << "   Space: O(1)" << endl;
    
    cout << "\n2. Recursive:" << endl;
    cout << "   Time: O(2^n)" << endl;
    cout << "   Space: O(n)" << endl;
    
    cout << "\n3. Memoized:" << endl;
    cout << "   Time: O(n)" << endl;
    cout << "   Space: O(n)" << endl;
}

void measureHanoiTime() {
    cout << "\nTower of Hanoi Complexities:" << endl;
    cout << string(50, '-') << endl;
    cout << "Time: O(2^n) (Exponential - must make 2^n-1 moves)" << endl;
    cout << "Space: O(n) (Recursive call stack)" << endl;
    cout << "\nThis is optimal - cannot be solved in fewer moves!" << endl;
}

// ========== GRAPH VISUALIZER ==========
void graphVisualizer() {
    clearScreen();
    displayHeader("VISUAL GRAPHS");
    
    cout << "Available graphs:" << endl;
    cout << "1. Fibonacci sequence growth" << endl;
    cout << "2. Lucas sequence growth" << endl;
    cout << "3. Tower of Hanoi moves growth" << endl;
    cout << "Enter choice: ";
    
    int choice, n;
    cin >> choice;
    
    if (choice != 4) {
        cout << "Enter number of terms (1-20): ";
        cin >> n;
        n = min(n, 20); // Limit for display
    }
    
    switch(choice) {
        case 1:
            printFibonacciGraph(n);
            break;
        case 2:
            printLucasGraph(n);
            break;
        case 3:
            printHanoiGraph(n);
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
    
    pressEnterToContinue();
}

void printFibonacciGraph(int n) {
    cout << "\nFibonacci Sequence Growth:" << endl;
    cout << "n  Value  Graph" << endl;
    cout << string(40, '-') << endl;
    
    for (int i = 0; i <= n; i++) {
        long long value = fibonacci_iterative(i);
        int bars = min(static_cast<int>(log2(value + 1)) * 2, 30);
        cout << setw(2) << i << "  " 
             << setw(6) << value << "  "
             << string(bars, '#') << endl;
    }
}

void printLucasGraph(int n) {
    cout << "\nLucas Sequence Growth:" << endl;
    cout << "n  Value  Graph" << endl;
    cout << string(40, '-') << endl;
    
    for (int i = 0; i <= n; i++) {
        long long value = lucas_iterative(i);
        int bars = min(static_cast<int>(log2(value + 1)) * 2, 30);
        cout << setw(2) << i << "  " 
             << setw(6) << value << "  "
             << string(bars, '#') << endl;
    }
}

void printHanoiGraph(int n) {
    cout << "\nTower of Hanoi Moves Growth:" << endl;
    cout << "Disks  Moves  Graph" << endl;
    cout << string(40, '-') << endl;
    
    for (int i = 1; i <= n; i++) {
        long long moves = pow(2, i) - 1;
        int bars = min(static_cast<int>(log2(moves + 1)), 30);
        cout << setw(5) << i << "  " 
             << setw(6) << moves << "  "
             << string(bars, '*') << endl;
    }
}