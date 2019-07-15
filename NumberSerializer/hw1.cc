/*
Assign: hw1
Created By: Elijah Harris (830654455)
*/
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
using namespace std;


string recurse(int input){
        stringstream ss;
        if (input < 0){
        input = ~input;
        
        }
        if ((input == 0)){                                              //basecase
            return ss.str();
        }
        ss << " " << hex << setw(2) << setfill('0') << (input & 0xff);  //gets first number
        input = input >> 8;                                             //shifts over to next
        string heyo = recurse(input);                                   //starts adding at the last number 
        heyo += ss.str();                                               //and adds to the next one until completed
        //cout << "String length: " << heyo.length();
        return heyo;
}



int main(int argc, char *argv[])
{
    char ogNum[100];
    int actNum;
    while(cin >> ogNum){                                                //takes in number
        istringstream ss(ogNum);
        if(!(ss >> actNum)){                                            //if not an int error out
			cerr << "Invalid Entry: " << ogNum << '\n';
			exit (EXIT_FAILURE);
		}
		cout << actNum << ":";                                          //adds ogNum to beginning of cout
        string unSeri = recurse(actNum);
        //cout << unSeri.length();//makes number serialized
        
        if(unSeri.length() == 12){
            if(unSeri.at(1) == '0'){
                unSeri.replace(unSeri.begin()+1,unSeri.begin()+2,"3");
                cout << unSeri << '\n';
                }
                else{
                unSeri.insert(0," 40");
                cout << unSeri << '\n';
                }
            
        } 
        if(unSeri.length() == 9){
            if(unSeri.at(1) == '0'){
                unSeri.replace(unSeri.begin()+1,unSeri.begin()+2,"2");
                cout << unSeri << '\n';
                }
                else{
                unSeri.insert(0," 30");
                cout << unSeri << '\n';
                }
            
        } 
        if(unSeri.length() == 6){
            if(unSeri.at(1) == '0'){
                unSeri.replace(unSeri.begin()+1,unSeri.begin()+2,"1");
                cout << unSeri << '\n';
                }
                else{
                unSeri.insert(0," 20");
                cout << unSeri << '\n';
                }
            
        } 
        if(unSeri.length() == 3){
            if(unSeri.at(1) == '0'){
            cout << unSeri << '\n';
            
            }
            else{
            unSeri.insert(0," 10");
            cout << unSeri << '\n';
        }
            
        }
            
    }
        
    
}


