//Program to track personal expenses.  Keeping it simple.. type a category then type an amount and repeat that until you're ready for a sum with a list.  


// preprocessor directives for this application. 
#include <iostream>  
#include <stdexcept> // I'm focusing on this directive since this is the directive that is specific for error handling and gives access to a range of standard exception classes. 
#include <string>
#include <vector>  // vector directive is a dynamic container that is efficient for storage for multiple entries. 
#include <sstream> /* stringStream proivides a way to perform formatted input and output on strings. 
                      It's useful for converting between strings and other data types such as int, float numbers.*/

using namespace std; // contains all of the classes, functions and objects from the library which saves us from prefixing std::

// Function to display program instructions to the user. outside of the class since its not related to the expense tracker. 
void displayInstructions() // void non-return type function..
{
    cout << "Welcome to your own Personal Expense Tracker!" << endl;
    cout << "This program allows you to log your expenses, categorize them, and calculate total spending." << endl;
    cout << "It handles errors like non-numeric input and negative amounts.\n" << endl;
} // Close DI function

// Expense struct to store information about each expense category and amount. Keeps them organized in a structured manner...struct.
struct Expense 
{
    string category; // Attributes 
    double amount = 0.0; // amount initialized to 0.0
}; // close struct


 //ExpenseTracker base class to manage expenses and calculate totals.
 class ExpenseTracker 
 {
private:  // private encapsulation
    vector<Expense> expenses;  // Vector to store expenses

public: // public encapsulation
    // non-return Method to add an expense containing 2 string parameters that will accept the expense category and inputAmount
    void addExpense(const string& category, const string& inputAmount) /* we are using a string rather than an int with inputAmount
                                                                          for better control over validation the validation process
                                                                          and better ux.  No need to clear cin manually.. no need to
                                                                          manage input buffer */
    {
        double amount; // declaring variable double naming it amount
        stringstream ss(inputAmount); // declaring stringstream as ss and initializing with inputAmount. SS parses the code well..

        /* if conditional using "!" logical NOT operator to negate the boolean value that
           follows it.  It inverts the result since the conditionals are false we need this 
           operator to read our result in true so our exceptions execute*/ 
        if (!(ss >> amount)) /* the extractor operator ">>" reads from ss and converts the
                                input into a double then stores it in amount */
        {   
            // 1st exeption indicating to the user that it is a numeric type of input.
            throw invalid_argument("Error: Invalid input. Please enter a numeric value for the amount.");
        }

        // 2nd exeption: check if the amount is non-negative
        if (amount < 0) { // if amount is less than 0..
            throw out_of_range("Error: Expense amount cannot be negative.");
        }

    // Creating a new instance of the Expense struct and naming it expense
    Expense expense;
    expense.category = category; // expense.category is assigned the value of users input from category 
    expense.amount = amount;     // same concept for amount...
    expenses.push_back(expense);    /*Add both category and amount members the to expenses vector
                                    using the push_back member of the vector class.This function is used to
                                    add a new expense object to the end of the vector automatically resizing as needed. */

    // console out providing feedback to the user including the category and amount setting it up with clear written communication. 
    cout << "Added expense: " << expense.category << " - $" << expense.amount << endl; /* Added expense - $ strings added for clarity
                                                                                       this follows each iteration once an expense 
                                                                                       and amount is input by user */

    }

    // non-return constant function to calculate and display total spending. 
    void calculateTotal() const  
    {
        if (expenses.empty()) // if statement with a 3rd exception to prompt user to input an expense. 
        {   // error that follows if nothing is input into expenses.
            throw runtime_error("Error: No expenses recorded. Please add expenses before calculating the total.");
        }

        double total = 0; // variable double named total initialized to 0. 
        for (const Expense& expense : expenses) /* for loop that iterates over each constant referenced Expense. */
        {
            total = total + expense.amount;  /* addition assignment where we are updating the total value from the expense.amount
                                                to the existing value of total, then stores it in the cumulative total variable */
        }
        cout << "\nTotal spending: $" << total << endl;  /* Output beginning a new line with string literal Total spending: $ 
                                                            followed by total.  End line */
    }

    // Non-Return constant function to display all recorded expenses once user types done. 
    void displayExpenses() const 
    {
        if (expenses.empty()) // If statement to check if the user left the input field empty using the .empty function to check vector container.
        {
            cout << "No expenses recorded yet." << endl; // string output to the user letting them know to nothing has been recorded
            return; /* return statement exiting the function early since there isn't anything recorded.. takes it to the next function
                       which is tracker.calcualateTotal(), throws the exception and then finishes at return 0; */
                       
        }
        // newline escape sequence to provide a blank line to improve readability followed by Recorded Expenses string...endl.
        cout << "\nRecorded Expenses:" << endl; 
        for (size_t i = 0; i < expenses.size(); ++i) /* for loop to iterate each element in the expenses vector container using 
                                                        size_t becuase it can represent larger values than int, i initialized to 0 this 
                                                       is the starting index for accessing elements in expenses, condition check to 
                                                       see if   i < total number of expense entries,
                                                       the loop outputs category and amount from [i],
                                                       ++i increments by 1 to move to the next entry in the vector,
                                                      when i reaches expenses.size() the condition becomes false */
        {  
            cout << "- " << expenses[i].category << ": $" << expenses[i].amount << endl; /* output to the user holding both 
                            the category iterations and amounts input by the user.  Included are string literals to organize the 
                            presentation of the values given */
        }
    }
};

int main() // Main block responsible for executing the code
{
    // Display program instructions function
    displayInstructions();

    // Initialize the expense tracker here and we are naming it tracker...
    ExpenseTracker tracker;

    try // try block is used to wrap the code that might throw exceptions (the corresponding catch block handles it).
    {
        string category, amount; // declaring our string variables..

        // Infinite while loop to input expenses until the user decides to stop. 
        while (true) 
        {       // output to user beginning w/ a new line escape folloed by directions
            cout << "\nEnter an expense category (or type 'done' to finish): ";
            cin >> category;  // category input follows the string literal for the user to input....the program waits here for user.
            if (category == "done") break; /* if statement performing as an exit condition.. if user types done the loop breaks 
                                              and goes to the next function in this case displays expenses and calculates total */

            cout << "Enter the amount spent on " << category << ": $"; /* output string literal for user  to prompt user to type in 
                                                                        a category followed by amount.. */
            cin >> amount;  // amount input...
            tracker.addExpense(category, amount); /* addExpense part of the ExpenseTracker class..a new expense entry is created here
                                                    and stored within the trackers object's expenses vector. Both category and amount
                                                    are passed into addExpense method.  We have added an expense to tracker's internal
                                                    list of expenses by invoking this method.. */
        }

        // Display recorded expenses and calculate total
        tracker.displayExpenses();
        tracker.calculateTotal();
    }
    // Catch block corresponding to the try block with an invalid_argument exception for non-numeric inputs
    catch (const invalid_argument& e) /* The exception object is passed as a constant reference for efficiency.  The variable e serves
                                        as a reference to the exception object itself, allowing access to details about the exception
                                        for example the error itself via e.what (which follows) */
    {
        cout << e.what() << endl; /* Output the error message from e.what to the user.end line to begin a new line, flushing the 
                                     output buffer in addition to..  */
    }
    // Catch block with an out_of_range exception for negative amounts
    catch (const out_of_range& e) 
    {
        cout << e.what() << endl;
    }
    // Catch block with a runtime_error exception for calculating total with no expenses
    catch (const runtime_error& e)
    {
        cout << e.what() << endl;
    }

    cout << "\nGreat job on staying on top of your finances!" << endl; // Final message to the user ..

    return 0; // Successful termination of the program. 
}
