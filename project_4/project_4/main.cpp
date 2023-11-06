#include <iostream>
#include <cassert>

using namespace std;

int reduplicate(string a[], int n) {
    if(n < 0) {
        return -1;
    }
    
    //append each string in a[] to itself
    for(int i = 0; i < n; i++) {
        a[i] = a[i] + a[i];
    }
    
    return n;
}

int locate(const string a[], int n, string target) {
    if(n < 0) {
        return -1;
    }
    
    //performs basic linear search
    for(int i = 0; i < n; i++) {
        if(a[i] == target) {
            return i;
        }
    }
    
    return -1;
}

int locationOfMax(const string a[], int n) {
    //accounts for no elements examined
    if(n <= 0) {
        return -1;
    }
    
    //assign defaults
    string max = a[0];
    int maxPos = 0;
    
    //continuously search for max
    for(int i = 0; i < n; i++) {
        if(a[i] > max) {
            maxPos = i;
            max = a[i];
        }
    }
    
    return maxPos;
}

//ASK: IS IT GUARANTEED THAT 0 <= POS <= N?
int circleLeft(string a[], int n, int pos) {
    //catches cases where pos is bad
    if(n < 0 || pos < 0 || pos > n - 1) {
        return -1;
    }
    
    //stores item at pos
    string temp = a[pos];
    //shifts all elements one to the left
    for(int i = pos; i < n - 1; i++) {
        a[i] = a[i + 1];
    }
    //moves stored item to end of known array
    a[n - 1] = temp;
    
    return pos;
}

int enumerateRuns(const string a[], int n) {
    if(n < 0) {
        return -1;
    }
    
    if(n == 0) {
        return 0;
    }
    
    //at this point n > 1
    int count = 1;
    string current = a[0];
    //count runs
    for(int i = 0; i < n; i++) {
        if(current != a[i]) {
            count++;
            current = a[i];
        }
    }
    
    return count;
}

int flip(string a[], int n);
int locateDifference(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int locateAny(const string a1[], int n1, const string a2[], int n2);
int divide(string a[], int n, string divider);

//Test Cases
int main() {
    //reduplicate
    string stuff[6] = { "mahi", " ", "cous", "", "tar", "mur" };
    assert(reduplicate(stuff, 6) == 6);
    assert(reduplicate(stuff, 3) == 3);
    assert(reduplicate(stuff, 0) == 0);
    assert(reduplicate(stuff, -10) == -1);
    string reduplicateResult = "";
    for(int i = 0; i < 6; i++) {
        reduplicateResult += stuff[i];
    }
    assert(reduplicateResult == "mahimahimahimahi    couscouscouscoustartarmurmur");
    
    //locate
    string arr[4] = { "mahi", "mahi", "MAHI", ""};
    assert(locate(arr, 4, "mahi") == 0);
    assert(locate(arr, 4, "mAhI") == -1);
    assert(locate(arr, 4, "MAHI") == 2);
    assert(locate(arr, 4, "") == 3);
    assert(locate(arr, 2, "MAHI") == -1);
    assert(locate(arr, 0, "mahi") == -1);
    assert(locate(arr, -10, "mahi") == -1);
    
    //locationOfMax
    string cand[6] = {"", "Donald", "Ron", "Ron", "Vivek", "nikki"};
    assert(locationOfMax(cand, 6) == 5);
    assert(locationOfMax(cand, 5) == 4);
    assert(locationOfMax(cand, 4) == 2);
    assert(locationOfMax(cand, 1) == 0);
    assert(locationOfMax(cand, 0) == -1);
    assert(locationOfMax(cand, -10) == -1);
    
    //circleLeft
    string running[5] = { "nikki", "donald", "asa", "tim", "ron"};
    assert(circleLeft(running, 5, 1) == 1);
    assert(circleLeft(running, 5, 0) == 0);
    assert(circleLeft(running, 1, 0) == 0);
    assert(circleLeft(running, 5, 5) == -1);
    assert(circleLeft(running, 5, -10) == -1);
    assert(circleLeft(running, -10, 0) == -1);
    string circleLeftResult = "";
    for(int i = 0; i < 5; i++) {
        circleLeftResult += running[i];
    }
    assert(circleLeftResult == "asatimrondonaldnikki");
    
    //enumerateRuns
    string names[9] = {"", "chris", "doug", "tim", "tim", "vivek", "vivek", "vivek", "tim", "tim"};
    assert(enumerateRuns(names, 10) == 6);
    assert(enumerateRuns(names, 8) == 5);
    assert(enumerateRuns(names, 1) == 1);
    assert(enumerateRuns(names, 0) == 0);
    assert(enumerateRuns(names, -10) == -1);
    
    return 0;
}
