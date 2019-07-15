/*
Assign: hw2
Created By: Elijah Harris (830654455)
*/
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <limits.h>


using namespace std;


void reverseStr(string &str)
{
    int ey = str.length() - 2;
    int n = str.length();
    int r = 0;
    int k = 0;
    //cout << n;
    switch (n){
        case 9: 
        case 6:
        r = 1;
        break;
        case 15:
        case 12:
        r = 2;
        break;
        case 21:
        case 18:
        r = 3;
        break;
        case 27:
        case 24:
        r = 4;
        break;
        case 33:
        case 30:
        r = 5;
        break;
        case 39:
        case 36:
        r = 6;
        break;
        case 45:
        case 42:
        r = 7;
        break;
        case 51:
        case 48:
        r = 8;
        break;
    }
    int count = 0; 
    while(count < r){
        for (int j = 0; j < 2; j++){
            swap(str[k+1], str[ey]);
            ey++;
            k++;
        } 
        k = k + 2;
        ey = ey - 4;
        count++;
    }
}

string recurse(int input){
    stringstream ss;
    if (input == 0){
        return ss.str();
    }   
    ss << hex << setw(2) << setfill('0') << (input & 0xff) << " ";  //gets first number
    input = input >> 8;                                             //shifts over to next
    string heyo = recurse(input);                                   //starts adding at the last number 
    heyo += ss.str();                                               //and adds to the next one until completed
    //cout << "String length: " << heyo.length();
    return heyo;
}

string thatsAInt(long input, bool isNeg){
    string output;
    stringstream ss;
    string space = " ";
    
    if (isNeg == 1){
        input = ~input;
        input = input + 1;
    }
    if (input > -7 && input < 8){                                          //2^3
        input = 0x0f & input;
        ss << " " << hex << setw(2) << setfill('0') << (input & 0xff);  
        output += ss.str();
    }
    else if (input >= -2048 && input < 2048){                                    //2^11
        //cout << "made it \n";
        input  = 0x1000 | input ;
        
        while(input != 0 && input != -1){
            ss << " " << hex << setw(2) << setfill('0') << (input & 0xff);
            input = input >> 8;
        }
        output += ss.str();
        reverseStr(output);
        
        if (input == -1){
            output.insert(0, " 1f");
        }
        
        //output.insert(0, space);
    }
    else if (input >= -524288 && input < 524288){                                //2^19
        long maskish = 0x200000;
         //       cout <<input;

        input = maskish | input;
        //cout <<input;
        while(input != 0 && input != -1){
            ss << " " << hex << setw(2) << setfill('0') << (input & 0xff);
            //cout << input;
            input = input >> 8;
        }
        output += ss.str();
        reverseStr(output);
        //cout << "test";
        if (input == -1){
            output.insert(0, " 2f");
        }
        //output.insert(0, space);
    }
    else if (input >= -134217728 && input < 134217728){                          //2^27
        long maskish = 0x30000000;
        input = maskish | input;
        while(input != 0 && input != -1){
            ss << " " << hex << setw(2) << setfill('0') << (input & 0xff);
            input = input >> 8;
        }
        //cout << "test";
        output += ss.str();
        reverseStr(output);
        //output.insert(0, space);
    }
    else if (input >= -34359738368 && input < 34359738368){                      //2^35
        long maskish = 0x4000000000;
        input = maskish | input;
        while(input > 0){
            ss << " " << hex << setw(2) << setfill('0') << (input & 0xff);
            input = input >> 8;
        }
        output += ss.str();
        reverseStr(output);
        //output.insert(0, space);
        
    }
    return output;
}

void thatsAString(string input){
    cout << "53";
    long len = input.length();
    cout << thatsAInt(len, 0);
    recurse(len);
    for(int i = 0; i < len; i++){
        cout << " " << hex << setw(2) << setfill('0') << (input[i] & 0xff);
    }
    cout << "\n";
}




int main(int argc, char *argv[])
{
    if(argc == 1) {
        std::cerr << "Error " << argv[0] << ": no filename entered\n";    //check if any args
            return 0;
        }
    
    
    for(int i = 1; i < argc; i++) {  //for multiple files/args
        ifstream inFile(argv[i]);    
        if(!inFile.is_open()){       //test if file can be opened
            std::cerr << "Error " << argv[0] << ": couldn't open file - " << argv[i] << "\n";  
            return 0;
        }
        int count = 0;
        while(inFile.good()){
            char c = inFile.peek();
            
            //cout << c << "\n";
            if(c == 34){                                         //String
                inFile.get();
                char next = 0;
                string stringy;
                while(next != 34){
                    inFile.get(next);
                    stringy += next;
                    next = inFile.peek();
                }
                thatsAString(stringy);
                //    cout << c << ": quote\n";
            }
            else if(c == 32 || c == 9 || c == 10){               //Delimiter
            //    cout << ": space/newline\n";
            }
            else if(c == 39){                                    //Char
                inFile.get();
                inFile.get(c);
                cout << "63 " << hex << setw(2) << setfill('0') << (c & 0xff) << "\n";
                inFile.get();
            }
            else if((c > 47 && c < 58)|| c == 45){               //Integer
                char yeah[256] {};
                long int val;
                bool isNeg = false;
                if (c == 45){
                    isNeg = true;
                    inFile.get();
                    c = inFile.peek();
                }
                int i = 0;
                while(c > 47 && c < 58){ 
                    inFile.get(yeah[i]);
                    c = inFile.peek();
                    i++;
                    //cout << yeah[i];
                }
                i = 0;
                //cout << "\n";
                val = atol(yeah);
                if (val <= SHRT_MAX){
                    cout << "73";
                }
                else if (val <= INT_MAX){
                    cout << "69";
                }
                else{
                    cout << "6c";
                }
                cout << thatsAInt(val, isNeg) << "\n";
                
            }
            else if(inFile.eof()){
                return 0;
            }
            else{
                cout << hex << setw(2) << setfill('0') << (c & 0xff) << "\n";
                std::cerr << "Error " << argv[0] << ": invalid input\n";
                return 0;
            }
            inFile.get();
            
        }
        cout << count << "\n";
    }
}





































