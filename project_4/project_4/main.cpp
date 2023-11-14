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

//Brandon's Test Cases
//int main() {
//    //reduplicate
//    string stuff[6] = {"mahi", " ", "cous", "", "tar", "mur"};
//    assert(reduplicate(stuff, 6) == 6);
//    assert(reduplicate(stuff, 3) == 3);
//    assert(reduplicate(stuff, 0) == 0);
//    assert(reduplicate(stuff, -10) == -1);
//    string reduplicateResult = "";
//    for(int i = 0; i < 6; i++) {
//        reduplicateResult += stuff[i];
//    }
//    assert(reduplicateResult == "mahimahimahimahi    couscouscouscoustartarmurmur");
//
//    //locate
//    string arr[4] = {"mahi", "mahi", "MAHI", ""};
//    assert(locate(arr, 4, "mahi") == 0);
//    assert(locate(arr, 4, "mAhI") == -1);
//    assert(locate(arr, 4, "MAHI") == 2);
//    assert(locate(arr, 4, "") == 3);
//    assert(locate(arr, 2, "MAHI") == -1);
//    assert(locate(arr, 0, "mahi") == -1);
//    assert(locate(arr, -10, "mahi") == -1);
//
//    //locationOfMax
//    string cand[6] = {"", "Donald", "Ron", "Ron", "Vivek", "nikki"};
//    assert(locationOfMax(cand, 6) == 5);
//    assert(locationOfMax(cand, 5) == 4);
//    assert(locationOfMax(cand, 4) == 2);
//    assert(locationOfMax(cand, 1) == 0);
//    assert(locationOfMax(cand, 0) == -1);
//    assert(locationOfMax(cand, -10) == -1);
//
//    //circleLeft
//    string running[5] = {"nikki", "donald", "asa", "tim", "ron"};
//    assert(circleLeft(running, 5, 1) == 1);
//    assert(circleLeft(running, 5, 0) == 0);
//    assert(circleLeft(running, 1, 0) == 0);
//    assert(circleLeft(running, 5, 5) == -1);
//    assert(circleLeft(running, 5, -10) == -1);
//    assert(circleLeft(running, -10, 0) == -1);
//    string circleLeftResult = "";
//    for(int i = 0; i < 5; i++) {
//        circleLeftResult += running[i];
//    }
//    assert(circleLeftResult == "asatimrondonaldnikki");
//
//    //enumerateRuns
//    string names[10] = {"", "chris", "doug", "tim", "tim", "vivek", "vivek", "vivek", "tim", "tim"};
//    assert(enumerateRuns(names, 10) == 6);
//    assert(enumerateRuns(names, 8) == 5);
//    assert(enumerateRuns(names, 1) == 1);
//    assert(enumerateRuns(names, 0) == 0);
//    assert(enumerateRuns(names, -10) == -1);
//
//    //flip
//    string folks[6] = {"donald", "tim", "", "chris", "nikki", "donald"};
//    assert(flip(folks, 6) == 6);
//    assert(flip(folks, 3) == 3);
//    assert(flip(folks, 1) == 1);
//    assert(flip(folks, 0) == 0);
//    assert(flip(folks, -10) == -1);
//    string flipResult = "";
//    for(int i = 0; i < 6; i++) {
//        flipResult += folks[i];
//    }
//    assert(flipResult == "chrisnikkidonaldtimdonald");
//
//    //locateDifference
//    string group1[6] = {"donald", "tim", "", "chris", "nikki", "donald"};
//    string group2[5] = {"donald", "tim", "donald", "", "chris"};
//    assert(locateDifference(group1, 6, group2, 5) == 2);
//    assert(locateDifference(group1, 2, group2, 3) == 2);
//    assert(locateDifference(group1, 3, group2, 2) == 2);
//    assert(locateDifference(group1, 2, group2, 2) == 2);
//    assert(locateDifference(group1, 0, group2, 2) == 0);
//    assert(locateDifference(group1, 2, group2, 0) == 0);
//    assert(locateDifference(group1, -10, group2, 2) == -1);
//    assert(locateDifference(group1, 2, group2, -10) == -1);
//
//    //subsequence
//    string names1[5] = {"nikki", "doug", "ron", "", "vivek"};
//    string names2[3] = {"ron", "", "vivek"};
//    string names3[2] = {"nikki", ""};
//    string names4[2] = {"nikki", ""};
//    assert(subsequence(names1, 5, names2, 3) == 2);
//    assert(subsequence(names1, 5, names3, 2) == -1);
//    assert(subsequence(names3, 2, names2, 3) == -1);
//    assert(subsequence(names1, 5, names2, 0) == 0);
//    assert(subsequence(names3, 2, names4, 2) == 0);
//    assert(subsequence(names1, 0, names2, 0) == 0);
//    assert(subsequence(names1, -10, names2, 0) == -1);
//    assert(subsequence(names1, 5, names2, -10) == -1);
//
//    //locateAny
//    string set1[5] = {"nikki", "ron", "tim", "ron", "doug"};
//    string set2[4] = {"donald", "doug", "vivek", "ron"};
//    string set3[2] = {"chris", "asa"};
//    assert(locateAny(set1, 5, set2, 4) == 1);
//    assert(locateAny(set1, 5, set3, 2) == -1);
//    assert(locateAny(set1, 0, set2, 2) == -1);
//    assert(locateAny(set1, 5, set2, 0) == -1);
//    assert(locateAny(set1, -10, set2, 2) == -1);
//    assert(locateAny(set1, 5, set2, -10) == -1);
//
//    //divide
//    string peeps1[6] = {"donald", "asa", "ron", "vivek", "chris", "nikki"};
//    string peeps2[4] = {"ron", "vivek", "asa", "tim"};
//    assert(divide(peeps1, 6, "doug") == 3);
//    assert(divide(peeps1, 6, "brandon") == 1);
//    assert(divide(peeps2, 4, "tim") == 2);
//    assert(divide(peeps1, 6, "zach") == 6);
//    assert(divide(peeps1, 6, "a") == 0);
//    assert(divide(peeps1, 6, "") == 0);
//    assert(divide(peeps1, 0, "doug") == 0);
//    assert(divide(peeps1, -10, "doug") == -1);
//
//    cout << "All test cases passed!" << endl;
//    return 0;
//}

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

//Divik's Test Cases
//int main() {
//    string a[7] = { "a",    "b",    "d",    "",    "v",    "c",    "q"};
//    assert(reduplicate(a, 4) == 4 && a[0] == "aa" && a[3] == "");
//    assert(reduplicate(a, 0) ==  0);
//    assert(reduplicate(a, -3) ==  -1);
//    string b[7] = { "a",    "b",    "d",    "",    "v",    "c",    "q"};
//    assert(locate(b, 7, "c") == 5);
//    assert(locate(b, 7, "d") == 2);
//    assert(locate(b, 2, "d") == -1);
//    assert(locate(b, 1, "a") == 0);
//    string c[7] = { "a",    "b",    "d",    "",    "v",    "v",    "q"};
//    assert(locationOfMax(c, 7) == 4);
//    assert(locationOfMax(c, 0) == -1);
//    assert(locationOfMax(c, -4) == -1);
//    string d[7] = { "a",    "b",    "d",    "",    "v",    "c",    "q"};
//    assert(circleLeft(d, 4, 1) == 1 && d[1] == "d" && d[3] == "b");
//    assert(circleLeft(d, 7, 1) == 1 && d[1] == "" && d[6] == "d");
//    string e[7] = { "a",    "b",    "d",    "",    "v",    "c",    "q" };
//    assert(circleLeft(e, 7, 2) == 2 && e[2] == "" && e[5] == "q");
//    assert(circleLeft(e, 7, -1) ==  -1);
//    assert(circleLeft(e, 0, 0) ==  -1);
//    string f[7] = { "a",    "b",    "b",    "b",    "v",    "v",    "q" };
//    assert(enumerateRuns(f, 7) == 4);
//    string g[7] = { "a",    "a",    "a",    "a",    "a",    "a",    "a" };
//    assert(enumerateRuns(g, 7) == 1);
//    assert(enumerateRuns(g, 0) == 0);
//    assert(enumerateRuns(g, -1) == -1);
//    string h[7] = { "a",    "b",    "d",    "",    "v",    "c",    "q"};
//    assert(flip(h, 3) == 3 && h[0] == "d" && h[2] == "a");
//    assert(flip(h, 0) == 0);
//    assert(flip(h, -1) == -1);
//    string folks[6] = { "donald", "tim", "", "chris", "nikki", "donald" };
//    string group[5] = { "donald", "tim", "donald", "", "chris" };
//    int r = locateDifference(folks, 6, group, 5);
//    int s = locateDifference(folks, 2, group, 1);
//    string names[10] = { "nikki", "ron", "tim", "vivek", "doug" };
//    string names1[10] = { "ron", "tim", "vivek" };
//    int aa = subsequence(names, 5, names1, 3);
//    string names2[10] = { "nikki", "vivek" };
//    int bb = subsequence(names, 4, names2, 2);
//    string name[10] = { "nikki", "ron", "tim", "vivek", "doug" };
//    string set1[10] = { "donald", "doug", "vivek", "ron" };
//    int cc = locateAny(name, 5, set1, 4);
//    string set2[10] = { "chris", "asa" };
//    int dd = locateAny(name, 5, set2, 2);
//    string cand[6] = { "donald", "asa", "ron", "vivek", "chris", "nikki" };
//    int ee = divide(cand, 6, "doug");
//    string cand2[4] = { "ron", "vivek", "asa", "tim" };
//    int ff = divide(cand2, 4, "tim");
//}

//Brayden's Test Cases
//int main() {
//    string test[6] = { "bob", "wow", "", " ", "ok!", "MM" };
//    assert(reduplicate(test, 6) == 6 && test[0] == "bobbob" && test[1] == "wowwow" && test[2] == "" && test[3] == "  " && test[4] == "ok!ok!" && test[5] == "MMMM");
//    assert(reduplicate(test, 0) == 0);
//    assert(reduplicate(test, -2) == -1);
//
//    string test1[6] = { "bob", "wow", "", " ", "ok!", "MM" };
//    assert(locate(test1, 6, "bob") == 0);
//    assert(locate(test1, 0, "bob") == -1);
//    assert(locate(test1, -2, "bob") == -1);
//    assert(locate(test1, 3, "ok!") == -1);
//    assert(locate(test1, 6, "Bob") == -1);
//    assert(locate(test1, 3, "wow") == 1);
//
//    string test2[7] = { "bob", "wow", "", " ", "ok!", "MM", "zz" };
//    assert(locationOfMax(test2, 6) == 1);
//    assert(locationOfMax(test2, 0) == -1);
//    assert(locationOfMax(test2, -2) == -1);
//    assert(locationOfMax(test2, 1) == 0);
//    assert(locationOfMax(test2, 7) == 6);
//
//    string test3[7] = { "bob", "wow", "", " ", "ok!", "MM", "zz" };
//    assert(circleLeft(test3, 7, 1) == 1 && test3[1] == "" && test3[6] == "wow");
//    string test4[7] = { "bob", "wow", "", " ", "ok!", "MM", "zz" };
//    assert(circleLeft(test4, 7, -2) == -1);
//    assert(circleLeft(test4, -2, 2) == -1);
//    assert(circleLeft(test4, 7, 6) == 6 && test2[6] == "zz");
//    assert(circleLeft(test4, 0, 0) == -1);
//
//    string test5[7] = { "bob", "wow", "", " ", "ok!", "MM", "zz" };
//    assert(enumerateRuns(test5, 7) == 7);
//    string test6[7] = { "bob", "wow", "wow", "wow", "ok!", "MM", "MM" };
//    assert(enumerateRuns(test6, -2) == -1);
//    assert(enumerateRuns(test6, 0) == 0);
//    assert(enumerateRuns(test6, 7) == 4);
//    assert(enumerateRuns(test6, 5) == 3);
//    string test7[7] = { "bob", "wow", "", " ", "ok!", "MM", "zz" };
//    assert(flip(test7, 7) == 7 && test7[0] == "zz" && test7[1] == "MM" && test7[2] == "ok!" && test7[3] == " " && test7[4] == "" && test7[5] == "wow" && test7[6] == "bob");
//    string test8[7] = { "bob", "wow", "", " ", "ok!", "MM", "zz" };
//    assert(flip(test8, -2) == -1);
//    assert(flip(test8, 0) == 0 && test8[0] == "bob" && test8[6] == "zz" && test8[3] == " ");
//    assert(flip(test8, 4) == 4 && test8[0] == " " && test8[3] == "bob" && test8[1] == "" && test8[2] == "wow" && test8[4] == "ok!" && test8[5] == "MM" && test8[6] == "zz");
//
//    string test9[7] = { "bob", "wow", "", " ", "ok!", "MM", "zz" };
//    string test10[7] = { "bob", "wow", "", " ", "ok!", "M", "zz" };
//    assert(locateDifference(test9, 7, test10, 7) == 5);
//    assert(locateDifference(test9, 7, test10, -2) == -1);
//    assert(locateDifference(test9, -2, test10, 0) == -1);
//    assert(locateDifference(test9, 7, test10, 0) == 0);
//    assert(locateDifference(test9, 7, test10, 3) == 3);
//    assert(locateDifference(test9, 4, test10, 4) == 4);
//
//    string test11[7] = { "bob", "wow", "", " ", "ok!", "MM", "zz" };
//    string test12[3] = { "", " ", "ok!"};
//    assert(subsequence(test11, 7, test12, 3) == 2);
//    assert(subsequence(test11, 4, test12, 3) == -1);
//    assert(subsequence(test11, 5, test12, 3) == 2);
//    assert(subsequence(test11, 5, test12, 0) == 0);
//    assert(subsequence(test11, 7, test12, -2) == -1);
//    assert(subsequence(test11, -1, test12, 3) == -1);
//    assert(subsequence(test11, 2, test12, 3) == -1);
//    assert(subsequence(test11, 0, test12, 3) == -1);
//
//    string test13[7] = { "bob", "wow", "", " ", "ok!", "MM", "zz" };
//    string test14[3] = { " ", "", "ok!"};
//    assert(locateAny(test13, 7, test14, 3) == 2);
//    assert(locateAny(test13, 3, test14, 2) == 2);
//    assert(locateAny(test13, -2, test14, 3) == -1);
//    assert(locateAny(test13, 3, test14, -2) == -1);
//    assert(locateAny(test13, 0, test14, 3) == -1);
//    assert(locateAny(test13, 7, test14, 0) == -1);
//    assert(locateAny(test13, 4, test14, 1) == 3);
//    assert(locateAny(test13, 2, test14, 3) == -1);
//    string test15[7] = { "a", "c", "d", "b", "e" };
//    assert(divide(test15, 5, "c") == 2);
//    string test16[7] = { "a", "c", "d", "b", "e" };
//    assert(divide(test16, 1, "c") == 1 && test16[0] == "a");
//    assert(divide(test15, -2, "c") == -1);
//    assert(divide(test15, 0, "c") == 0);
//}

//Emily's Test Cases
//int main() {
//    string c[4] = { "ma", "can", "tu", "do" };
//    assert(reduplicate(c, 4) == 4 && c[0] == "mama" && c[3] == "dodo");
//    assert(reduplicate(c, -2) == -1);
//    assert(reduplicate(c, 0) == 0);
//
//
//    string h[7] = { "nikki", "AsA", "asa", "asa", "", "chris", "donald" };
//    assert(locate(h, 7, "chris") == 5);
//    assert(locate(h, 7, "asa") == 2);
//    assert(locate(h, -2, "donald") == -1); // tests for negative n
//    assert(locate(h, 2, "asa") == -1); // target not within n
//    assert(locate(h, 0, "asa") == -1); // doesnt read anything so target not within n
//
//    string po[6] = { "asa", "bob", "asa", "", "chris", "chris"};
//    assert(locationOfMax(po, 5) == 4);
//    assert(locationOfMax(po, -2) == -1); // tests for negative n
//    assert(locationOfMax(po, 6) == 4); // first largest return if two of same element
//    assert(locationOfMax(po, 0) == -1); // checks if it reads anything
//
//
//    string g[4] = { "nikki", "ron", "chris", "tim" };
//    assert(circleLeft(g, 4, 1) == 1 && g[1] == "chris" && g[3] == "ron");
//    assert(circleLeft(g, -2, -2) == -1); // tests for negative n
//    assert(circleLeft(g, 4, 4) == -1); // tests for pos out of bound
//
//    string d[9] = { "chris", "doug", "tim", "tim", "vivek", "vivek", "vivek", "tim", "tim" };
//    assert(enumerateRuns(d, 9) == 5);
//    assert(enumerateRuns(d, 6) == 4);
//    assert(enumerateRuns(d, -6) == -1); // tests for negative n
//    assert(enumerateRuns(d, 0) == 0); // tests for not going through anything
//    assert(enumerateRuns(d, 1) == 1);
//
//    string ge[7] = { "nikki", "ron", "asa", "vivek", "", "chris", "donald" };
//    string gg[4] = { "nikki", "ron", "chris", "tim" };
//    assert(locateDifference(ge, 4, gg, 4) == 2);
//    assert(locateDifference(ge, 2, gg, 2) == 2);
//    assert(locateDifference(ge, 2, gg, -2) == -1); // tests for negative n
//
//
//    string f[3] = { "vivek", "asa", "tim" };
//    assert(flip(f, 3) == 3 && f[0] == "tim" && f[2] == "vivek");
//    assert(flip(f, -2) == -1); // tests for negative n
//    assert(flip(f, 0) == 0); // tests for 0
//
//    string e[5] = { "asa", "vivek", "", "chris"};
//    string gege[7] = { "nikki", "ron", "asa", "vivek", "", "chris", "donald" };
//    string ra[2] = { "nikki" , "poo" };
//    assert(subsequence(gege, 7, e, 4) == 2);
//    assert(subsequence(gege, -4, e, 4) == -1); // negative n1
//    assert(subsequence(gege, 4, e, -4) == -1); // negative n2
//    assert(subsequence(gege, 7, e, 0) == 0); // subsequence = 0
//    assert(subsequence(gege, 7, ra, 2) == -1); // tests if one string of subsequence matches but the rest doesn't
//    string bb[6] = { "a", "b", "c", "a", "b", "c" };
//    assert(subsequence(bb, 6, bb, 3) == 0); // tests for multiple subsequence in a1
//
//    string hh[7] = { "nikki", "AsA", "asa", "asa", "", "chris", "donald" };
//    string ff[3] = { "vivek", "asa", "tim" };
//    assert(locateAny(hh, 7, ff, 3) == 2);
//    assert(locateAny(gege, -4, e, 4) == -1); // negative n1
//    assert(locateAny(gege, 4, e, -4) == -1); // negative n2
//    assert(locateAny(hh, 7, ff, 1) == -1); // tests for case where a2 not in a1
//
//    string cand[6] = { "donald", "asa", "ron", "vivek", "chris", "nikki" };
//    assert(divide(cand, 6, "doug") == 3);
//    assert(divide(cand, -6, "doug") == -1); // negative n
//    assert(divide(cand, 2, "doug") == 2); // nothign less than doug
//
//    cout << "All tests succeeded" << endl;
//}

//Rachel's Test Cases
//int main() {
//    // reduplicate() test cases
//    string names[10] = {"Emilie", "Irene", "Lester", "Phoebe", "Aiden", "Rachel"};
//    assert(reduplicate(names, -7) == -1 && names[0] == "Emilie"); // n is negative
//    assert(reduplicate(names, 0) == 0 && names[0] == "Emilie"); // n is 0
//    assert(reduplicate(names, 2) == 2 && names[1] == "IreneIrene" && names[2] == "Lester"); // n is less than the total amount of elements
//    string stuff[6] = {"mahi", "bon", "cous", "", "tar", "mur"};
//    assert(reduplicate(stuff, 6) == 6 && stuff[0] == "mahimahi" && stuff[5] == "murmur"); // n is equal to the total amount of elements
//    string empty[0];
//    assert(reduplicate(empty, 0) == 0); // empty list
//
//    // locate() test cases
//    string names2[10] = {"Emilie", "Irene", "Lester", "Phoebe", "Aiden", "Rachel", "Emilie"};
//    assert(locate(names2, 7, "Brian") == -1); // target string is not included in the list
//    assert(locate(names2, 2, "Lester") == -1); // target string exists in the list but is not in the bounds of what we are interested in
//    assert(locate(names2, 3, "EMILIE") == -1); // testing case sensitivity
//    assert(locate(names2, 7, "Emilie") == 0); // target string exists twice in the array
//    assert(locate(names2, 0, "Emilie") == -1); // n is 0
//    assert(locate(names2, -5, "Rachel") == -1); // n is negative
//    assert(locate(empty, 0, "empty") == -1); // array is empty
//
//    // locationOfMax() test cases
//    string food[5] = {"sushi", "pasta", "pizza", "taco", "sandwhich"};
//    assert(locationOfMax(food, 0) == -1); // n is 0
//    assert(locationOfMax(food, -1) == -1); // n is negative
//    assert(locationOfMax(food, 1) == 0); // the greatest string is not in the bounds of what we are interested in
//    assert(locationOfMax(food, 5) == 3); // n is equal to the number of elements in the array
//    string drinks[4] = {"Boba",  "boba", "boba", "BOBA"};
//    assert(locationOfMax(drinks, 2) == 1); // lowercase should be greater than uppercase
//    assert(locationOfMax(drinks, 4) == 1); // more than one greatest string
//    string favColor[1] = {"pink"};
//    assert(locationOfMax(favColor, 1) == 0); // only one element in the array
//
//    // circleLeft() test cases
//    string colors[7] = {"jade", "red", "pink", "lavendar", "navy", "grey", "white"};
//    assert(circleLeft(colors, -1, 3) == -1); // n is negative
//    assert(circleLeft(colors, 0, 0) == -1); // n is 0 and pos is 0
//    assert(circleLeft(colors, 2, 4) == -1); // pos is greater than n
//    assert(circleLeft(colors, 7, 0) == 0 && colors[0] == "red" && colors[1] == "pink" && colors[2] == "lavendar" && colors[3] == "navy" && colors[4] == "grey" && colors[5] == "white" && colors[6] == "jade") ; // pos is 0
//    assert(circleLeft(colors, 4, -1) == -1); // position is negative
//    assert(circleLeft(colors, 5, 2) == 2 && colors[0] == "red" && colors[1] == "pink" && colors[2] == "navy" && colors[3] == "grey" && colors[4] == "lavendar" && colors[5] == "white" && colors[6] == "jade"); // n is less than the total number of elements
//    assert(circleLeft(colors, 3, 2) == 2 && colors[0] == "red" && colors[1] == "pink" && colors[2] == "navy" && colors[3] == "grey" && colors[4] == "lavendar" && colors[5] == "white" && colors[6] == "jade"); // pos is one less than n (shouldn't change anything)
//    assert(circleLeft(favColor, 1, 0) == 0 && favColor[0] == "pink"); // only one element in the array
//
//    // enumerateRuns() test cases
//    string brands[3] = {"Nike", "Nike", "Nike"};
//    assert(enumerateRuns(brands, 0) == 0); // n is 0
//    assert(enumerateRuns(brands, -1) == -1); // n is negative
//    assert(enumerateRuns(brands, 3) == 1); // one sequence
//    string brands2[5] = {"Nike", "Adidas", "Reebok", "Vans", "Puma"};
//    assert(enumerateRuns(brands2, 5) == 5); // no consecutive items
//    assert(enumerateRuns(empty, 0) == 0); // empty string
//    string brands3[10] = {"Nike", "nike", "Adidas", "Reebok", "Reebok", "Vans", "Vans", "Puma", "Reebok", "Vans"};
//    assert(enumerateRuns(brands3, 2) == 2); // checks for case sensitivity
//    assert(enumerateRuns(brands3, 4) == 4); // n is less than the total number of elements
//    assert(enumerateRuns(brands3, 10) == 8); // sequence containing consecutive items
//
//    // flip() test cases
//    string folks[6] = {"donald", "tim", "", "chris", "nikki", "donald"};
//    assert(flip(folks, -6) == -1); // n is negative
//    assert(flip(folks, 0) == 0); // n is zero
//    assert(flip(folks, 4) == 4 && folks[0] == "chris" && folks[1] == "" && folks[2] == "tim" && folks[3] == "donald" && folks[4] == "nikki" && folks[5] == "donald"); // n is less than all the elements in the array
//    assert(flip(brands2, 3) == 3 && brands2[0] == "Reebok" && brands2[1] == "Adidas" && brands2[2] == "Nike" && brands2[3] == "Vans" && brands2[4] == "Puma"); // n is odd
//    assert(flip(favColor, 1) == 1 && favColor[0] == "pink"); // array has only one element
//    string parents[2] = {"mom", "dad"};
//    assert(flip(parents, 1) == 1 && parents[0] == "mom" && parents[1] == "dad"); // n is 1 (nothing should change)
//    assert(flip(parents, 2) == 2 && parents[0] == "dad" && parents[1] == "mom"); // array with 2 elements
//
//    // locateDifference() test cases
//    string cities[5] = {"fremont", "milpitas", "cupertino", "sunnyvale", "saratoga"};
//    string cities2[4] = {"fremont", "milpitas", "sunnyvale", "sunnyvale"};
//    assert(locateDifference(cities, 1, cities2, -8) == - 1); // n1 is negative
//    assert(locateDifference(cities, -3, cities2, 2) == - 1); // n2 is negative
//    assert(locateDifference(cities, 0, cities2, 4) == 0); // n1 is zero
//    assert(locateDifference(cities, 2, cities2, 0) == 0); // n2 is zero
//    assert(locateDifference(cities, 2, cities2, 2) == 2); // no difference
//    assert(locateDifference(cities, 1, cities2, 2) == 1); // one of the arrays runs out
//    assert(locateDifference(cities, 5, cities2, 4) == 2); // n1 and n2 equal the total number of elements in the array
//
//    // subsequence() test cases
//    string countries[7] = {"New Zealand", "India", "Japan", "Canada", "China", "Japan", "Australia"};
//    string countries2[4] = {"Japan", "Canada", "China", "Japan"};
//    string countries3[3] = {"India", "Mexico", "New Zealand"};
//    assert(subsequence(countries, -1, countries2, 4) == -1); // n1 is negative
//    assert(subsequence(countries, 5, countries2, -2) == -1); // n2 is negative
//    assert(subsequence(countries, 0, countries2, 4) == -1); // n1 is 0
//    assert(subsequence(countries, 4, countries2, 0) == 0); // n2 is 0
//    assert(subsequence(countries, 0, countries2, 0) == 0); // n1 and n2 is 0
//    assert(subsequence(countries, 7, countries2, 4) == 2); // n1 and n2 equal the total number of elements in the array
//    assert(subsequence(countries, 1, countries3, 1) == -1); // subsequence is not in the bounds of what we are interested in
//    assert(subsequence(countries2, 4, countries3, 3) == -1); // subsequence doesn't exist
//
//    // locateAny() test cases
//    assert(locateAny(countries, 0, countries2, 4) == -1); // n1 is 0
//    assert(locateAny(countries, 5, countries2, 0) == -1); // n2 is 0
//    assert(locateAny(countries, -2, countries2, 4) == -1); // n1 is negative
//    assert(locateAny(countries, 5, countries2, -1) == -1); // n2 is negative
//    assert(locateAny(countries, 7, countries2, 4) == 2); // multiple elements in a2 that are in a1
//    assert(locateAny(countries2, 4, countries3, 3) == -1) ; // no elements in a2 that are in a1
//    assert(locateAny(countries2, 3, countries, 2) == -1); // elements in a2 exist in a1 but are located outside the bounds
//
//    // divide() test cases
//    string names3[6] = {"Emilie", "Irene", "Lester", "Phoebe", "Aiden", "Rachel"};
//    assert(divide(names3, -1, "") == -1); // n is negative
//    assert(divide(names3, 0, "Irene") == 0); // n is 0
//    assert(divide(names3, 4, "phoebe") == 4); // all elements are less than divider
//    string names4[6] = {"Emilie", "Irene", "Lester", "Phoebe", "Aiden", "Rachel"};
//    assert(divide(names4, 3, "Frank") == 1); // n is less than the total number of elements in the array
//    assert(names4[0] == "Emilie" && names4[1] == "Irene" && names4[2] == "Lester" && names4[3] == "Phoebe" && names4[4] == "Aiden" && names4[5] == "Rachel");
//    assert(divide(names4, 5, "Aiden") == 0); // divider is equal to one of the elements
//    string greetings[4] = {"hi", "hello", "bonjour", "hey"};
//    assert(divide(greetings, 4, "HI!") == 0); // all elements are greater than divider
//
//    // smallberg's test cases
//
//    string people[5] = { "donald", "vivek", "tim", "asa", "nikki" };
//    assert(locate(people, 3, "nikki") == -1);
//    string stuff2[6] = { "mahi", "bon", "cous", "", "tar", "mur" };
//    assert(reduplicate(stuff2, 6) == 6 && stuff[0] == "mahimahi" && stuff[1] == "bonbon" && stuff[2] == "couscous" && stuff[3] == "" && stuff[4] == "tartar" && stuff[5] == "murmur");
//    string cand[6] = { "donald", "asa", "ron", "vivek", "chris", "nikki"};
//    assert(locationOfMax(cand, 6) == 3);
//    string running[5] = { "nikki", "donald", "asa", "tim", "ron" };
//    assert(circleLeft(running, 5, 1) == 1 && running[0] == "nikki" && running[1] == "asa" && running[2] == "tim" && running[3] == "ron" && running[4] == "donald");
//    string d[9] = {"chris", "doug", "tim", "tim", "vivek", "vivek", "vivek", "tim", "tim"};
//    assert(enumerateRuns(d, 9) == 5);
//    string folks2[6] = { "donald", "tim", "", "chris", "nikki", "donald" };
//    assert(flip(folks2, 4) == 4 && folks2[0] == "chris" && folks2[1] == "" && folks2[3] == "donald" && folks2[4] == "nikki" && folks2[5] == "donald");
//    string folks3[6] = { "donald", "tim", "", "chris", "nikki", "donald" };
//    string group[5] = { "donald", "tim", "donald", "", "chris" };
//    assert(locateDifference(folks3, 6, group, 5) == 2);
//    assert(locateDifference(folks3, 2, group, 1) == 1);
//    string names5[10] = { "nikki", "ron", "tim", "vivek", "doug" };
//    string names6[10] = { "ron", "tim", "vivek" };
//    assert(subsequence(names5, 5, names6, 3) == 1);
//    string names7[10] = { "nikki", "vivek" };
//    assert(subsequence(names5, 4, names7, 2) == -1);
//    string names8[10] = { "nikki", "ron", "tim", "vivek", "doug" };
//    string set1[10] = { "donald", "doug", "vivek", "ron" };
//    assert(locateAny(names8, 5, set1, 4) == 1);
//    string set2[10] = { "chris", "asa" };
//    assert(locateAny(names8, 5, set2, 2) == -1);
//    string cand1[6] = { "donald", "asa", "ron", "vivek", "chris", "nikki" };
//    assert(divide(cand1, 6, "doug") == 3);
//    string cand2[4] = { "ron", "vivek", "asa", "tim" };
//    assert(divide(cand2, 4, "tim") == 2);
//}

//Alexis's Test Cases
//int main() {
//    string words[6] = {"happy", "sad", "angry", "pensive", "excited", "tired"};
//    
//    // reduplicate tests
//    assert(reduplicate(words, -2) == -1); // negative number returns a negative
//    assert(reduplicate(words, 4) == 4 && words[1] == "sadsad" && words[5] == "tired"); // when given an n less than size, edits the ones within range and doesn't edit the ones out of range and returns correct value
//    assert(reduplicate(words, 6) == 6 && words[0] == "happyhappyhappyhappy" && words[5] == "tiredtired"); // when n is equal to the size, it edits all values and returns correct value
//    assert(reduplicate(words, 0) == 0 && words[0] == "happyhappyhappyhappy"); // no error when n is 0, and doesn't edit anything
//    
//    // resetting words values
//    words[0] = "happy";
//    words[1] = "sad";
//    words[2] = "angry";
//    words[3] = "pensive";
//    words[4] = "excited";
//    words[5] = "tired";
//    
//    // locate tests
//    assert(locate(words, -1, "sad") == -1); // negative number returns -1
//    assert(locate(words, 0, "happy") == -1); // n = 0 returns -1
//    assert(locate(words, 6, "sad") == 1); // can find a value in the middle of the array
//    assert(locate(words, 6, "tired") == 5); // can find the last value in the array
//    assert(locate(words, 6, "grumpy") == -1); // if the value is not in the list, return -1
//    
//    // locationofMax tests
//    assert(locationOfMax(words, -1) == -1); // negative number returns -1
//    assert(locationOfMax(words, 0) == -1); // 0 returns -1
//    assert(locationOfMax(words, 3) == 1); // test case where n is less than the max size but greater than 0
//    assert(locationOfMax(words, 6) == 5); // test case where n is the max size
//    
//    // circleLeft tests
//    assert(circleLeft(words, -1, 2) == -1); // negative number returns -1
//    assert(circleLeft(words, 0, 0) == -1); // n is 0 so it should return -1
//    assert(circleLeft(words, 4, 1) == 1 && words[0] == "happy" && words[1] == "angry" && words[2] == "pensive" && words[3] == "sad"); // some circling
//    assert(circleLeft(words, 6, 5) == 5 && words[4] == "excited" && words[5] == "tired"); // circling where pos = n - 1
//    
//    // resetting words values
//    words[0] = "happy";
//    words[1] = "sad";
//    words[2] = "angry";
//    words[3] = "pensive";
//    words[4] = "excited";
//    words[5] = "tired";
//    
//    // enumerateRuns tests
//    assert(enumerateRuns(words, -1) == -1); // negative number returns -1
//    assert(enumerateRuns(words, 0) == 0); // n = 0 returns 0
//    assert(enumerateRuns(words, 1) == 1); // n = 1 returns 1
//    assert(enumerateRuns(words, 6) == 6); // all values of array are unique
//    words[1] = "happy";
//    assert(enumerateRuns(words, 6) == 5); // first two values are the same
//    words[4] = "tired";
//    assert(enumerateRuns(words, 6) == 4); // last two values are the same
//    for (int i = 0; i < 6; i++) words[i] = "happy";
//    assert(enumerateRuns(words, 6) == 1); // all values are the same, so it should return 1
//    
//    // resetting words values
//    words[0] = "happy";
//    words[1] = "sad";
//    words[2] = "angry";
//    words[3] = "pensive";
//    words[4] = "excited";
//    words[5] = "tired";
//    
//    // flip tests
//    assert(flip(words, -1) == -1); // negative number returns -1
//    assert(flip(words, 0) == 0 && words[0] == "happy" && words[3] == "pensive" && words[5] == "tired"); // n = 0 so it doesn't flip anything
//    assert(flip(words, 1) == 1 && words[0] == "happy" && words[1] == "sad" && words[5] == "tired"); // flips only first one, so the array basically stays the same
//    assert(flip(words, 4) == 4 && words[0] == "pensive" && words[1] == "angry" && words[2] == "sad" && words[3] == "happy"); // flips an even number of elements
//    assert(flip(words, 5) == 5 && words[0] == "excited" && words[1] == "happy" && words[2] == "sad" && words[3] == "angry" && words[4] == "pensive");
//    
//    // resetting words values
//    words[0] = "happy";
//    words[1] = "sad";
//    words[2] = "angry";
//    words[3] = "pensive";
//    words[4] = "excited";
//    words[5] = "tired";
//    
//    string words2[4] = {"happy", "sad", "angry", "pensive"};
//    
//    // locateDifference tests
//    assert(locateDifference(words, -5, words2, 2) == -1); // negative n1 returns -1
//    assert(locateDifference(words, 2, words2, -5) == -1); // negative n2 returns -1
//    assert(locateDifference(words, 2, words2, 4) == 2); // all elements are the same, and a1 runs out first
//    assert(locateDifference(words, 5, words2, 3) == 3); // all elements are the same, and a2 runs out first
//    words2[1] = "terrible";
//    assert(locateDifference(words, 6, words2, 4) == 1); // there is a different element in the range of both n1 and n2
//    
//    string words3[2] = {"sad", "angry"};
//    
//    // subsequence tests
//    assert(subsequence(words, -1, words3, 2) == -1); // negative n1 returns -1
//    assert(subsequence(words, 6, words3, -1) == -1); // negative n2 returns -1
//    assert(subsequence(words, 0, words3, 0) == 0);
//    assert(subsequence(words, 6, words3, 2) == 1); // there is a subsequence that starts in the middle of a1
//    words3[0] = "happy";
//    words3[1] = "sad";
//    assert(subsequence(words, 6, words3, 2) == 0); // there is a subsequence that starts at a1[0]
//    assert(subsequence(words, 1, words3, 2) == -1); // n1 is less than n2
//    words3[0] = "excited";
//    words3[1] = "tired";
//    assert(subsequence(words, 6, words3, 2) == 4); // there is a subsequence that is at the end of a1 but is still valid
//    words3[0] = "tired";
//    words3[1] = "grumpy";
//    assert(subsequence(words, 6, words3, 2) == -1); // there is no subsequence, but the start of a2 is the end of a1
//    words3[0] = "envious";
//    words3[1] = "grumpy";
//    assert(subsequence(words, 6, words3, 2) == -1); // there is no subsequence at all
//    string words4[1] = {"pensive"};
//    assert(subsequence(words, 6, words4, 1) == 3); // a2 is size 1 and there is a subsequence
//    words4[0] = "envious";
//    assert(subsequence(words, 6, words4, 1) == -1); // a2 is size 1 and there is no subsequence
//    
//    words3[0] = "emotive";
//    words3[1] = "pensive";
//    
//    // locateAny tests
//    assert(locateAny(words, -1, words3, 2) == -1); // negative n1 returns -1
//    assert(locateAny(words, 6, words3, -1) == -1); // negative n2 returns -1
//    assert(locateAny(words, 6, words3, 2) == 3); // there is a match
//    assert(locateAny(words, 3, words3, 2) == -1); // there is no match
//    
//    // divide tests
//    assert(divide(words, -1, words3[0]) == -1); // negative n returns -1
//    assert(divide(words, 0, words3[0]) == 0); // n of 0 returns 0
//    assert(divide(words, 6, words3[0]) == 1); // tests with the word 'emotive'
//    assert(divide(words, 6, words3[1]) == 3); // tests with the word 'pensive'
//}

//Jon's Test Cases
//int main() {
//    //Reduplicate tests
//    string a[5] = {"xx", "", "12xz", ".wje", "owifejwiosq[oj"};
//    string b[3] = {"", "", ""};
//    assert(reduplicate(a, 5) == 5); // reduplicate handles a regular positive
//    assert(reduplicate(b, 3) == 3); // reduplicate handles an array of empty strings correctly
//    assert(reduplicate(a, -32) == -1); //reduplicate handles a negative n call correctly
//    string c[0] = {};
//    assert(reduplicate(c, 0) == 0); //reduplicate handles a 0 n call correctly
//    
//    //Locate tests
//    assert(locate(a, 5, "") == 1); //locate handles a call with an empty string to search for correctly
//    assert(locate(b, 3, "a") == -1); //locate handles when the string being searched for does not exist within the array
//    string d[5] = {"cat", "dog", "", "elephant", "zebra"};
//    assert(locate(d, -2, "x") == -1); //locate handles a negative n passed into the function
//    assert(locate(d, 0, "x") == -1); //locate handles a value of zero for n
//    assert(locate(a, 5, "") == 1); //locate handles a call for a "" string
//    assert(locate(c, 0, "him") == -1); //locate handles an empty array correctly
//    assert(locate(d, 5, "dog") == 1); //locates string "dog" correctly
//    string e[1] = {"x"};
//    assert(locate(e, 1, "x") == 0); //locate handles a 1-item array correctly
//           
//    //locationOfMax tests
//    string f[4] = {"bob", "sam", "evan", "kyle"};
//    assert(locationOfMax(f, -2) == -1); //handles a negative n call
//    assert(locationOfMax(d, 5) == 4); //finds that "zebra" is the greatest string
//    assert(locationOfMax(b, 3) == 0); //handles an array of empty strings correctly
//    
//    //circleLeft tests
//    string g[7] = {"wade", "bumblebee", "xyz", "zane", "kate", "jon", "james"};
//    assert(circleLeft(f, 7, -3) == -1); //handles a negative pos correctly
//    assert(circleLeft(f, -7, 3) == -1); //handles a negative n correctly
//    assert(circleLeft(f, 7, 8) == -1); //handles when pos is greater than n correctly
//    assert(circleLeft(g, 7, 1) == 1); //handles when pos 1 needs to be "removed" correctly
//    
//    //enumerateRuns tests
//    string h[4] = {"axe", "axe", "pen", "operator"};
//    assert(enumerateRuns(h, 4) == 3); //handles an array of 3 sequences of one or more consecutive items
//    assert(enumerateRuns(h, 2) == 1); //handles an array of 2 identical items correctly
//    assert(enumerateRuns(h, -2) == -1); //handles a negative n call correctly
//    assert(enumerateRuns(h, 0) == 0); //handles a test where there are zero intersting items passed in through n
//    //flip tests
//    string i[5] = {"computer", "hat", "duck", "you", "me"};
//    assert(flip(i, -1) == -1); //handles as negative n call correctly
//    assert(flip(i, 5) == 5); //reverses the order of the array i and returns n
//    assert(flip(i, 1) == 1); //handles an array with one interesting value passed into it
//    assert(flip(i, 0) == 0); //handles an array with zero interesting values passed in
//    
//    //locateDifference tests
//    string j[5] = {"jon", "james", "payton", "wyatt", "colin"};
//    string k[5] = {"jon", "james", "payton", "wyatt", "colin"};
//
//    assert(locateDifference(j, -8, k, 5) == -1); //handles when n1 is negative correctly
//    assert(locateDifference(j, 5, k, -2) == -1); //handles when n2 is negative correctly
//    assert(locateDifference(j, 0, k, 5) == 0); //handles when n1 is zero correctly
//    assert(locateDifference(j, 3, k, 0) == 0); //handles when n2 is zero correctly
//    assert(locateDifference(j, 5, k, 5) == 5); //handles when two identical arrays are passed in
//    assert(locateDifference(j, 5, k, 4) == 4); //handles when 2 arrays are equal up to a point where one runs out correctly
//    
//    //subsequence tests
//    string l[3] = {"james", "payton", "wyatt"};
//    assert(subsequence(j, -2, l, 3) == -1); //handles when n1 is negative correctly
//    assert(subsequence(j, 5, l, -3) == -1); //handles when n2 is negative correctly
//    assert(subsequence(j, 0, l, 5) == -1); //handles when n1 is less than n2 correctly
//    assert(subsequence(j, 5, l, 0) == 0); //handles when n2 is zero correctly
//    assert(subsequence(j, 5, l, 3) == 1); //finds the start of the correct subsequence at position 1 correctly
//    
//    //locateAny tests
//    assert(locateAny(j, -1, l, 3) == -1); //handles when n1 is negative correctly
//    assert(locateAny(j, 5, l, -2) == -1); //handles when n2 is negative correctly
//    assert(locateAny(j, 5, l, 0) == -1); //handles when no element in l is equal to j
//    assert(locateAny(j, 5, l, 3) == 1); //handles when the first array has elements equal to the second array correctly
//    
//    //divide tests
//    assert(divide(j, -1, "fdo") == -1); //handles when n is negative correctly
//    assert(divide(j, 5, "adam") == 0); //handles when the string passed in is less than all the items in the array
//    assert(divide(j, 5, "zane") == 5); //handles when the string is greater than all items in array correctly
//    assert(divide(k, 5, "kate") == 3); //handles when the string is has some items that are greater and some items that are less than said string in the array.
//    cout << "All test cases Passed!" << endl;
//}

//Andrew's Test Cases:
//int main() {
//    // MARK: - reduplicate
//    
//    string stuff[6] = { "mahi", " ", "ha", "", "food", "apple" };
//    assert(reduplicate(stuff, 6) == 6); // duplicate everything
//    assert(reduplicate(stuff, 2) == 2); // duplicate first two elements
//    assert(reduplicate(stuff, 0) == 0); // duplicate nothing
//    assert(reduplicate(stuff, -5) == -1); // negative n
//    string reduplicateResult = "";
//    for(int i = 0; i < 6; i++) {
//        reduplicateResult += stuff[i];
//    }
//    
//    // "mahi" and " " x4, everything else x2
//    // duplicate empty space doesn't do anything
//    assert(reduplicateResult == "mahimahimahimahi    hahafoodfoodappleapple");
//    
//    
//    // MARK: - locate
//    
//    string locations[5] = { "california", "CA", "Paris", "pariS", "LA" };
//    assert(locate(locations, 5, "california") == 0); // first element
//    assert(locate(locations, 5, "CaliforniA") == -1); // different case, doesn't exist
//    assert(locate(locations, 5, "Paris") == 2); // third element
//    assert(locate(locations, 2, "Paris") == -1); // only checks up to "CA"
//    assert(locate(locations, 0, "california") == -1); // checks 0 elements
//    assert(locate(locations, -5, "california") == -1); // negative n
//    
//    
//    // MARK: - locationOfMax
//    
//    string cand0[6] = { "donald", "asa", "ron", "vivek", "chris", "nikki" };
//    assert(locationOfMax(cand0, 6) == 3); // "vivek" is last
//    assert(locationOfMax(cand0, 3) == 2); // "ron" is last when only looking at first 3 elements
//    assert(locationOfMax(cand0, 0) == -1); // should examine no elements, return -1
//    assert(locationOfMax(cand0, -1) == -1); // negative n
//    
//    string cand1[3] = { "Arthur", "Donald", "donald" };
//    assert(locationOfMax(cand1, 3) == 2); // case-sensitive - "donald" is greater than "Donald"
//    string cand2[4] = { "Arthur", "Donald", "donald", "donald" };
//    assert(locationOfMax(cand2, 3) == 2); // multiple of the same value, return position of first one
//    string cand3[3] = { "donald", "donald", "donald" };
//    assert(locationOfMax(cand3, 3) == 0); // everything is the same
//    
//    
//    // MARK: - circleLeft
//    
//    string running[5] = { "nikki", "donald", "asa", "tim", "ron" };
//    assert(circleLeft(running, 5, 1) == 1); // circle left starting at "donald", running is now: "nikki", "asa", "tim", "ron", "donald"
//    assert(circleLeft(running, 5, 0) == 0); // circle everything left, running is now: "asa", "tim", "ron", "donald", "nikki"
//    assert(circleLeft(running, 5, 0) == 0); // circle everything left again, running is now: "tim", "ron", "donald", "nikki", "asa"
//    assert(circleLeft(running, 1, 0) == 0); // circle first element by itself, running should be unchanged
//    assert(circleLeft(running, 5, 4) == 4); // circle last element by itself, running should be unchanged
//    assert(circleLeft(running, 5, 5) == -1); // out of bounds, running should be unchanged
//    assert(circleLeft(running, 5, -5) == -1); // negative pos
//    assert(circleLeft(running, -10, 0) == -1); // negative n
//    
//    string circleLeftResult = "";
//    for(int i = 0; i < 5; i++) {
//        circleLeftResult += running[i];
//    }
//    
//    // check array is "tim", "ron", "donald", "nikki", "asa"
//    assert(circleLeftResult == "timrondonaldnikkiasa");
//    
//    
//    // MARK: - enumerateRuns
//    
//    string people[10] = { "steve", "tim", "tim", "tim", "craig", "", "", "steve", "jony", "phil" };
//    assert(enumerateRuns(people, 10) == 7); // everything - should be 7 consecutive runs
//    assert(enumerateRuns(people, 7) == 4); // up to and including the second "" - should be 4 consecutive runs
//    assert(enumerateRuns(people, 6) == 4); // up to and including the first "" - should still be 4 consecutive runs
//    assert(enumerateRuns(people, 1) == 1); // the first element still counts as a consecutive run
//    assert(enumerateRuns(people, 0) == 0); // no elements, so no consecutive runs
//    assert(enumerateRuns(people, -5) == -1); // negative n
//    
//    
//    // MARK: - flip
//    
//    string symbols[8] = { "A", "B", "C", "", "-", "X", "Y", "Z" };
//    assert(flip(symbols, 8) == 8); // returns n, symbols is now "Z", "Y", "X", "-", "", "C", "B", "A"
//    assert(flip(symbols, 2) == 2); // flip "Z" and "Y", symbols is now "Y", "Z", "X", "-", "", "C", "B", "A"
//    assert(flip(symbols, 1) == 1); // flip "Z" by itself, symbols should be unchanged
//    assert(flip(symbols, 0) == 0); // flip no elements, symbols should be unchanged
//    assert(flip(symbols, -1) == -1); // negative n
//    
//    string flipResult = "";
//    for(int i = 0; i < 8; i++) {
//        flipResult += symbols[i];
//    }
//    
//    assert(flipResult == "YZX-CBA"); // "" character doesn't show up, but in the array it's there
//    assert(symbols[4] == ""); // see, it's there!
//    
//    
//    // MARK: - locateDifference
//    
//    string shoppingList[4] = { "eggs", "milk", "", "cheese" };
//    string shoppingListExtended[6] = { "eggs", "milk", "bananas", "", "cheese", "jam" };
//    assert(locateDifference(shoppingList, 4, shoppingListExtended, 6) == 2); // index 2 is the first difference
//    assert(locateDifference(shoppingList, 4, shoppingListExtended, 3) == 2); // same result even though comparing less elements
//    assert(locateDifference(shoppingListExtended, 3, shoppingList, 4) == 2); // parameter order shouldn't matter
//    assert(locateDifference(shoppingListExtended, 1, shoppingList, 2) == 1); // return the n that's smallest
//    assert(locateDifference(shoppingListExtended, 1, shoppingList, 1) == 1); // return the n that's smallest or equal to the other
//    assert(locateDifference(shoppingListExtended, 0, shoppingList, 1) == 0); // no elements compared, return smallest n
//    assert(locateDifference(shoppingListExtended, 0, shoppingList, 0) == 0); // no elements compared, return 0
//    assert(locateDifference(shoppingListExtended, -5, shoppingList, 4) == -1); // negative n1
//    assert(locateDifference(shoppingListExtended, 3, shoppingList, -5) == -1); // negative n2
//    
//    
//    // MARK: - subsequence
//    string names0[5] = { "smallberg", "", "nachenberg", "eggert", "branstetter" };
//    string names1[3] = { "nachenberg", "eggert", "branstetter" };
//    string names2[2] = { "nachenberg", "" };
//    string names3[2] = { "nachenberg", "" };
//    assert(subsequence(names0, 5, names1, 3) == 2); // index of "nachenberg" in names0
//    assert(subsequence(names0, 5, names2, 2) == -1); // doesn't contain all elements, so return -1
//    assert(subsequence(names2, 2, names0, 5) == -1); // names2 doesn't contains names0's elements
//    assert(subsequence(names0, 5, names2, 1) == 2); // if only looking for "nachenberg", it works
//    assert(subsequence(names0, 5, names1, 0) == 0); // consider sequence of 0 elements to be subsequence of any array
//    assert(subsequence(names0, 0, names1, 0) == 0); // ... even for one with no elements, return 0
//    assert(subsequence(names2, 2, names3, 2) == 0); // arrays are exactly the same, so return 0 (index where the match starts)
//    assert(subsequence(names3, 2, names2, 2) == 0); // should work when switched
//    assert(subsequence(names0, -5, names1, 3) == -1); // negative n1
//    assert(subsequence(names0, 5, names1, -5) == -1); // negative n2
//    
//    
//    // MARK: - locateAny
//    string set0[5] = { "paper", "pencil", "card", "phone", "water bottle" };
//    string set1[3] = { "pen", "eraser", "paper" };
//    string set2[2] = { "staple", "eraser" };
//    assert(locateAny(set0, 5, set1, 3) == 0); // set0 contains "paper" at index 0
//    assert(locateAny(set0, 5, set1, 2) == -1); // set0 doesn't contain "eraser" or "pen"
//    assert(locateAny(set0, 5, set2, 2) == -1); // set0 has none of set2's elements
//    assert(locateAny(set1, 3, set2, 2) == 1); // set1 contains "eraser" at index 1
//    assert(locateAny(set1, 0, set2, 2) == -1); // return -1 if not found (checked no elements in a1)
//    assert(locateAny(set0, -10, set1, 3) == -1); // negative n1
//    assert(locateAny(set0, 5, set1, -20) == -1); // negative n2
//    
//    
//    // MARK: - divide
//    
//    string candidates0[6] = { "donald", "asa", "ron", "vivek", "chris", "nikki" };
//    string candidates1[4] = { "ron", "vivek", "asa", "tim" };
//    
//    // first element after "doug" will be at index 3
//    // (first 3 elements should be "asa", "chris", "donald" in any order)
//    assert(divide(candidates0, 6, "doug") == 3);
//    
//    // first element after "bob" will be at index 1
//    // (first element should be "asa")
//    assert(divide(candidates0, 6, "bob") == 1);
//    assert(candidates0[0] == "asa"); // first element should be "asa"
//    
//    // "asa" should stay at index 0 because everything else is greater
//    assert(divide(candidates0, 6, "asa") == 0);
//    
//    // empty char has lower ASCII value than anything else
//    assert(divide(candidates0, 6, "") == 0);
//    assert(divide(candidates0, 6, " ") == 0);
//    
//    // return n if no elements < divider
//    assert(divide(candidates0, 6, "zzz") == 6);
//    
//    // first element >= "tim" (which is "tim") will be at index 2
//    assert(divide(candidates1, 4, "tim") == 2);
//    assert(candidates1[2] == "tim"); // "tim" should be here
//    
//    assert(divide(candidates1, 0, "tim") == 0); // leave the array unchanged because no elements compared
//    assert(divide(candidates1, -5, "tim") == -1); // negative n
//    
//    cout << "All test cases passed!" << endl;
//    return 0;
//}

//Jon's Test Cases
int main() {
    //Reduplicate tests
    string a[5] = {"xx", "", "12xz", ".wje", "owifejwiosq[oj"};
    string b[3] = {"", "", ""};
    assert(reduplicate(a, 5) == 5); // reduplicate handles a regular positive
    assert(reduplicate(b, 3) == 3); // reduplicate handles an array of empty strings correctly
    assert(reduplicate(a, -32) == -1); //reduplicate handles a negative n call correctly
    string c[0] = {};
    assert(reduplicate(c, 0) == 0); //reduplicate handles a 0 n call correctly
    
    //Locate tests
    assert(locate(a, 5, "") == 1); //locate handles a call with an empty string to search for correctly
    assert(locate(b, 3, "a") == -1); //locate handles when the string being searched for does not exist within the array
    string d[5] = {"cat", "dog", "", "elephant", "zebra"};
    assert(locate(d, -2, "x") == -1); //locate handles a negative n passed into the function
    assert(locate(d, 0, "x") == -1); //locate handles a value of zero for n
    assert(locate(a, 5, "") == 1); //locate handles a call for a "" string
    assert(locate(c, 0, "him") == -1); //locate handles an empty array correctly
    assert(locate(d, 5, "dog") == 1); //locates string "dog" correctly
    string e[1] = {"x"};
    assert(locate(e, 1, "x") == 0); //locate handles a 1-item array correctly
           
    //locationOfMax tests
    string f[4] = {"bob", "sam", "evan", "kyle"};
    assert(locationOfMax(f, -2) == -1); //handles a negative n call
    assert(locationOfMax(d, 5) == 4); //finds that "zebra" is the greatest string
    assert(locationOfMax(b, 3) == 0); //handles an array of empty strings correctly
    
    //circleLeft tests
    string g[7] = {"wade", "bumblebee", "xyz", "zane", "kate", "jon", "james"};
    assert(circleLeft(f, 7, -3) == -1); //handles a negative pos correctly
    assert(circleLeft(f, -7, 3) == -1); //handles a negative n correctly
    assert(circleLeft(f, 7, 8) == -1); //handles when pos is greater than n correctly
    assert(circleLeft(g, 7, 1) == 1); //handles when pos 1 needs to be "removed" correctly
    
    //enumerateRuns tests
    string h[4] = {"axe", "axe", "pen", "operator"};
    assert(enumerateRuns(h, 4) == 3); //handles an array of 3 sequences of one or more consecutive items
    assert(enumerateRuns(h, 2) == 1); //handles an array of 2 identical items correctly
    assert(enumerateRuns(h, -2) == -1); //handles a negative n call correctly
    assert(enumerateRuns(h, 0) == 0); //handles a test where there are zero intersting items passed in through n
    //flip tests
    string i[5] = {"computer", "hat", "duck", "you", "me"};
    assert(flip(i, -1) == -1); //handles as negative n call correctly
    assert(flip(i, 5) == 5); //reverses the order of the array i and returns n
    assert(flip(i, 1) == 1); //handles an array with one interesting value passed into it
    assert(flip(i, 0) == 0); //handles an array with zero interesting values passed in
    
    //locateDifference tests
    string j[5] = {"jon", "james", "payton", "wyatt", "colin"};
    string k[5] = {"jon", "james", "payton", "wyatt", "colin"};

    assert(locateDifference(j, -8, k, 5) == -1); //handles when n1 is negative correctly
    assert(locateDifference(j, 5, k, -2) == -1); //handles when n2 is negative correctly
    assert(locateDifference(j, 0, k, 5) == 0); //handles when n1 is zero correctly
    assert(locateDifference(j, 3, k, 0) == 0); //handles when n2 is zero correctly
    assert(locateDifference(j, 5, k, 5) == 5); //handles when two identical arrays are passed in
    assert(locateDifference(j, 5, k, 4) == 4); //handles when 2 arrays are equal up to a point where one runs out correctly
    
    //subsequence tests
    string l[3] = {"james", "payton", "wyatt"};
    assert(subsequence(j, -2, l, 3) == -1); //handles when n1 is negative correctly
    assert(subsequence(j, 5, l, -3) == -1); //handles when n2 is negative correctly
    assert(subsequence(j, 0, l, 5) == -1); //handles when n1 is less than n2 correctly
    assert(subsequence(j, 5, l, 0) == 0); //handles when n2 is zero correctly
    assert(subsequence(j, 5, l, 3) == 1); //finds the start of the correct subsequence at position 1 correctly
    
    //locateAny tests
    assert(locateAny(j, -1, l, 3) == -1); //handles when n1 is negative correctly
    assert(locateAny(j, 5, l, -2) == -1); //handles when n2 is negative correctly
    assert(locateAny(j, 5, l, 0) == -1); //handles when no element in l is equal to j
    assert(locateAny(j, 5, l, 3) == 1); //handles when the first array has elements equal to the second array correctly
    
    //divide tests
    assert(divide(j, -1, "fdo") == -1); //handles when n is negative correctly
    assert(divide(j, 5, "adam") == 0); //handles when the string passed in is less than all the items in the array
    assert(divide(j, 5, "zane") == 5); //handles when the string is greater than all items in array correctly
    assert(divide(k, 5, "kate") == 3); //handles when the string is has some items that are greater and some items that are less than said string in the array.
    cout << "All test cases Passed!" << endl;
}
