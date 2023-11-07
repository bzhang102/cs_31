#include <iostream>
#include <string>
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

int flip(string a[], int n) {
    if(n < 0) {
        return -1;
    }
    
    //declare outside loop to save space
    string temp;
    //swaps first half with second half
    for(int i = 0; i < n/2; i++) {
        temp = a[i];
        a[i] = a[n - i - 1];
        a[n - i - 1] = temp;
    }
    
    return n;
}

int locateDifference(const string a1[], int n1, const string a2[], int n2) {
    if(n1 < 0 || n2 < 0) {
        return -1;
    }
    
    //searches for differences up to lowest n
    for(int i = 0; i < n1 && i < n2; i++) {
        if(a1[i] != a2[i]) {
            return i;
        }
    }
    
    //returns lowest n
    if(n1 < n2) {
        return n1;
    }
    return n2;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
    if(n1 < 0 || n2 < 0 || n2 > n1) {
        return -1;
    }
    
    //declare outside loop to save space
    int i;
    //start index only needs to go up to n1 - n2
    for(int start = 0; start < n1 - n2 + 1; start++) {
        i = 0;
        for(; i < n2; i++) {
            if(a1[start + i] != a2[i]) {
                break;
            }
        }
        
        //if a contiguous subsequence is found, return start index
        if(i == n2) {
            return start;
        }
    }
    
    //no contiguous subsequence located
    return -1;
}

int locateAny(const string a1[], int n1, const string a2[], int n2) {
    if(n1 <= 0 || n2 <= 0) {
        return -1;
    }
    
    //nested for loops check each element of a1[] against each element in a2[]
    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < n2; j++) {
            if(a1[i] == a2[j]) {
                return i;
            }
        }
    }
    
    //no match found
    return -1;
}

int divide(string a[], int n, string divider) {
    if(n < 0) {
        return -1;
    }
    
    //count declared outside loop to save space
    int count;
    int i = 0;
    while(i < n) {
        count = 0;
        //loop through remaining elements to make sure none are less than divider
        while(a[i] >= divider) {
            if(count >= n - i) {
                //if divider is greater than all elements return n
                if(divider > a[i]) {
                    return n;
                }
                
                return i;
            }
            circleLeft(a, n, i);
            count++;
        }
        i++;
    }
    
    //divider is less than all elements and greater
    return i;
}

//Test Cases
int main() {
    //reduplicate
    string stuff[6] = {"mahi", " ", "cous", "", "tar", "mur"};
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
    string arr[4] = {"mahi", "mahi", "MAHI", ""};
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
    string running[5] = {"nikki", "donald", "asa", "tim", "ron"};
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
    string names[10] = {"", "chris", "doug", "tim", "tim", "vivek", "vivek", "vivek", "tim", "tim"};
    assert(enumerateRuns(names, 10) == 6);
    assert(enumerateRuns(names, 8) == 5);
    assert(enumerateRuns(names, 1) == 1);
    assert(enumerateRuns(names, 0) == 0);
    assert(enumerateRuns(names, -10) == -1);
    
    //flip
    string folks[6] = {"donald", "tim", "", "chris", "nikki", "donald"};
    assert(flip(folks, 6) == 6);
    assert(flip(folks, 3) == 3);
    assert(flip(folks, 1) == 1);
    assert(flip(folks, 0) == 0);
    assert(flip(folks, -10) == -1);
    string flipResult = "";
    for(int i = 0; i < 6; i++) {
        flipResult += folks[i];
    }
    assert(flipResult == "chrisnikkidonaldtimdonald");
    
    //locateDifference
    string group1[6] = {"donald", "tim", "", "chris", "nikki", "donald"};
    string group2[5] = {"donald", "tim", "donald", "", "chris"};
    assert(locateDifference(group1, 6, group2, 5) == 2);
    assert(locateDifference(group1, 2, group2, 3) == 2);
    assert(locateDifference(group1, 3, group2, 2) == 2);
    assert(locateDifference(group1, 2, group2, 2) == 2);
    assert(locateDifference(group1, 0, group2, 2) == 0);
    assert(locateDifference(group1, 2, group2, 0) == 0);
    assert(locateDifference(group1, -10, group2, 2) == -1);
    assert(locateDifference(group1, 2, group2, -10) == -1);
    
    //subsequence
    string names1[5] = {"nikki", "doug", "ron", "", "vivek"};
    string names2[3] = {"ron", "", "vivek"};
    string names3[2] = {"nikki", ""};
    string names4[2] = {"nikki", ""};
    assert(subsequence(names1, 5, names2, 3) == 2);
    assert(subsequence(names1, 5, names3, 2) == -1);
    assert(subsequence(names3, 2, names3, 3) == -1);
    assert(subsequence(names1, 5, names2, 0) == 0);
    assert(subsequence(names3, 2, names4, 2) == 0);
    assert(subsequence(names1, 0, names2, 0) == 0);
    assert(subsequence(names1, -10, names2, 0) == -1);
    assert(subsequence(names1, 5, names2, -10) == -1);
    
    //locateAny
    string set1[5] = {"nikki", "ron", "tim", "ron", "doug"};
    string set2[4] = {"donald", "doug", "vivek", "ron"};
    string set3[2] = {"chris", "asa"};
    assert(locateAny(set1, 5, set2, 4) == 1);
    assert(locateAny(set1, 5, set3, 2) == -1);
    assert(locateAny(set1, 0, set2, 2) == -1);
    assert(locateAny(set1, 5, set2, 0) == -1);
    assert(locateAny(set1, -10, set2, 2) == -1);
    assert(locateAny(set1, 5, set2, -10) == -1);
    
    //divide
    string peeps1[6] = {"donald", "asa", "ron", "vivek", "chris", "nikki"};
    string peeps2[4] = {"ron", "vivek", "asa", "tim"};
    assert(divide(peeps1, 6, "doug") == 3);
    assert(divide(peeps1, 6, "brandon") == 1);
    assert(divide(peeps2, 4, "tim") == 2);
    assert(divide(peeps1, 6, "zach") == 6);
    assert(divide(peeps1, 6, "a") == 0);
    assert(divide(peeps1, 6, "") == 0);
    assert(divide(peeps1, 0, "doug") == 0);
    assert(divide(peeps1, -10, "doug") == -1);
    
    cout << "All test cases passed!" << endl;
    return 0;
}

//Smallberg's Test Cases
//int main() {
//    string h[7] = { "nikki", "ron", "asa", "vivek", "", "chris", "donald" };
//    assert(locate(h, 7, "chris") == 5);
//    assert(locate(h, 7, "asa") == 2);
//    assert(locate(h, 2, "asa") == -1);
//    assert(locationOfMax(h, 7) == 3);
//    
//    string g[4] = { "nikki", "ron", "chris", "tim" };
//    assert(locateDifference(h, 4, g, 4) == 2);
//    assert(circleLeft(g, 4, 1) == 1 && g[1] == "chris" && g[3] == "ron");
//    
//    string c[4] = { "ma", "can", "tu", "do" };
//    assert(reduplicate(c, 4) == 4 && c[0] == "mama" && c[3] == "dodo");
//    
//    string e[4] = { "asa", "vivek", "", "chris" };
//    assert(subsequence(h, 7, e, 4) == 2);
//    
//    string d[5] = { "ron", "ron", "ron", "chris", "chris" };
//    assert(enumerateRuns(d, 5) == 2);
//    
//    string f[3] = { "vivek", "asa", "tim" };
//    assert(locateAny(h, 7, f, 3) == 2);
//    assert(flip(f, 3) == 3 && f[0] == "tim" && f[2] == "vivek");
//    
//    assert(divide(h, 7, "donald") == 3);
//    
//    cout << "All tests succeeded" << endl;
//}
