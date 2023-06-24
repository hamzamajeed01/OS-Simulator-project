#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;

bool page_found(int temp, int arr[], bool second_chance[], int frames){
    int i;
    for (i = 0; i < frames; i++) {
       if (arr[i] == temp)  {
            second_chance[i] = true;
            return true;
        }
    } 
    return false;
}
int Replace_Page(int temp, int arr[],bool second_chance[], int frames, int index){
    while (true){
        if (!second_chance[index])  {
            arr[index] = temp; 
            return (index + 1) % frames;
        }
        second_chance[index] = false;
        index = (index + 1) % frames;
    }
}


void print(string reference_string, int frames){
    int index = 0;
    int len = 0;
    int pg_faults=0;
    int *arr=new int[frames];
    memset(arr, -1, sizeof(arr));
    bool *second_chance=new bool[frames];
    string str[100];
    string word = "";
    for (auto x : reference_string){
        if (x == ' '){
            str[len] = word;
            word = "";
            len++;
        }
        else{
            word = word + x;
        }
    }
    str[len] = word;
    len++;
    int i = 0;
    int temp = 0;
    for (i = 0; i < len; i++){
        temp = stoi(str[i]);
        if (!page_found(temp, arr, second_chance, frames)) {
            index = Replace_Page(temp, arr, second_chance, frames, index);
            pg_faults++;
        }
    }
    cout << "Total page faults = " << pg_faults << endl;
    float k = ((1.0*pg_faults) / (1.0*len))*100;
    cout << "Percentage of page faults = " << k << "%"<< endl;
}


int main()
{
    string str1 = "";
    int frames = 0;
    cout << "Enter string" << endl;
    getline(cin, str1);
    cout << "Enter Frame Number" << endl;
    cin >> frames;
   // str1 = "0 4 1 4 2 4 3 4 2 4 0 4 1 4 2 4 3 4";
   print(str1, frames);
    system("pause");
    return 0;
}