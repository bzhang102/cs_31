#include <iostream>
#include <tgmath.h>

using namespace std;

int main(int argc, const char * argv[]) {
    //initialize variables
    string id;
    double overstatement;
    string location;
    
    string ans;
    double fine = 0.0;
    
    //take user input
    cout << "Identification: ";
    getline(cin, id);
    
    cout << "Overstated amount (in millions): ";
    cin >> overstatement;
    cin.ignore(10000, '\n');
    
    cout << "Location: ";
    getline(cin, location);
    
    cout << "---" << endl;
    
    //check for and handle invalid inputs
    if (id.length() == 0) {
        cout << "You must enter a property identification." << endl;
        return 1;

    } else if (overstatement <= 0) {
        cout << "The overstated amount must be positive." << endl;
        return 1;
        
    } else if (location.length() == 0) {
        cout << "You must enter a location." << endl;
        return 1;
        
    //compute fine
    } else {
        if (overstatement > 60.0) {
            fine += 60.0 * 0.1111;
            overstatement -= 60.0;
            
            double rate = 0.153;
            if (location == "florida" || location == "new york") {
                rate = 0.18;
            }
            
            if(overstatement > 90.0) {
                //if overstatement is > $90 million
                fine += 90.0 * rate;
                overstatement -= 90.0;
                
                fine += overstatement * 0.21;
                
            } else {
                //if overstatement is > $60.0 million and <= $90.0 million
                fine += overstatement * rate;
            }
        
        } else {
            //if overstatement is <= $60.0 million
            fine += overstatement * 0.1111;
        }
        
        //print fine statement to three decimal places
        cout << "The fine for " << id << " is $" << round(fine * 1000.0) / 1000.0 << " million." << endl;
    }
    
    return 0;
}
