#include "FSerial.h"
#include <sstream>
#include <fstream>

using namespace std;

IFSerial::IFSerial(const std::string s){
    stream.open(s);
    if (stream.good()){
        eof2 = false;
        state = true;
        while(stream.good()){
            char c = stream.get();
//         cout << dec << int(c) << '\n';
            stringy.push_back(c);
        }
    }
    else{
        eof2 = true;
        state = false;
    }
}
    
IFSerial::~IFSerial(){}
    
    
//     IFSerial >> bool
IFSerial &operator>>(IFSerial &s, bool &b){
    if (s.fail()){
        return s;
    }
    if (s.stringy[0] == -1){
        s.eof(true);
        s.fail(false);
        return s;
    }
    if (s.stringy[0] != 't' && s.stringy[0] != 'f'){
        throw ("Incorrect tag - Not a bool"s);
    }
    else if (s.stringy[0] == 't'){
        b = true;
//         cout << s.stringy[0] << "\n";
        s.stringy.erase(s.stringy.begin());
    }
    else if (s.stringy[0] == 'f'){
        b = false;
        s.stringy.erase(s.stringy.begin());
    }
    return s;
}

//     IFSerial >> int
IFSerial &operator>>(IFSerial &s, int &i){
    if (s.fail()){
        return s;
    }
    if (s.stringy[0] == -1){
        s.eof(true);
        s.fail(false);
        return s;
    }
    if (s.stringy[0] != 'i'){throw ("Incorrect tag - Not a int"s);}
    s.stringy.erase(s.stringy.begin());
    long long int ans = makeAnInt(s);
    i = int(ans);
    return s;
}

//     IFSerial >> short
IFSerial &operator>>(IFSerial &s, short &ss){
    if (s.fail()){
        return s;
    }
    if (s.stringy[0] == -1){
        s.eof(true);
        s.fail(false);
        return s;
    }
    if (s.stringy[0] != 's'){throw ("Incorrect tag - Not a short"s);}
    s.stringy.erase(s.stringy.begin());
    long long int ans = makeAnInt(s);
    ss = short(ans);
    return s;
}

//     IFSerial >> long
IFSerial &operator>>(IFSerial &s, long &l){
    if (s.fail()){
        return s;
    }
    if (s.stringy[0] == -1){
        s.eof(true);
        s.fail(false);
        return s;
    }
    if (s.stringy[0] != 'l'){throw ("Incorrect tag - Not a long"s);}
    s.stringy.erase(s.stringy.begin());
    long long int ans = makeAnInt(s);
//     cout << ans;
    l = long(ans);
    return s;
}

//     IFSerial >> char
IFSerial &operator>>(IFSerial &s, char &c){
    if (s.fail()){
        return s;
    }
    if (s.stringy[0] == -1){
        s.eof(true);
        s.fail(false);
        return s;
    }
    if (s.stringy[0] != 'c'){throw ("Incorrect tag - Not a char"s);}
    else {
    s.stringy.erase(s.stringy.begin());
    c = s.stringy[0];
    s.stringy.erase(s.stringy.begin());
    }
    return s;
}

//     IFSerial >> std::string
IFSerial &operator>>(IFSerial &s, std::string &S){
    if (s.fail()){
        return s;
    }
    if (s.stringy[0] == -1){
        s.eof(true);
        s.fail(false);
        return s;
    }
    S = "";
    if (s.stringy[0] != 'S'){throw ("Incorrect tag - Not a string"s);}
    else{
    s.stringy.erase(s.stringy.begin());
    if (s.stringy[0] == '\x10'){s.stringy.erase(s.stringy.begin());}
    char count = s.stringy[0];
    while (count != 0){
        s.stringy.erase(s.stringy.begin());
        S += s.stringy[0];
        count--;
    }
    s.stringy.erase(s.stringy.begin());
    }
    return s;
}

//     IFSerial.eof()
bool IFSerial::eof() const{
    return eof2;
}

void IFSerial::eof(const bool b){
    eof2 = b;
}

//     IFSerial.fail()
bool IFSerial::fail() const{
    return !state;
}

void IFSerial::fail(const bool b){
    state = b;
}

vector<char> thatsAInt(long long input, bool isNeg) {
    vector<char> output;
    vector<char>::iterator it;
    ostringstream ss;
    string space = " ";
//     int count = 0;
    //cout << input;
//     if (isNeg == 1){
//         input = ~input;
//         input = input + 1;
//     }
    if (input > -7 && input < 8){                                          //2^3
        if (isNeg != true){
        input = 0x0f & input;
        }
        long long int j = (input & 0xff);
        //cout << j << '\n';
        
        char l = j;
        output.insert(it, l);
        it = output.begin();
    }
    else if (input >= -512 && input < 512){                                    //2^11
        //cout << "made it \n";
        input  = 0x1000 | input ;
        while(input != 0 && input != -1){
            long long int j = (input & 0xff);
        //    cout << j << '\n';
            char l = j;
            output.insert(it, l);     
            input = input >> 8;
            it = output.begin();
        }
        if (isNeg == true && input == -1){
           output.insert(it, '\x1f');
           it = output.begin();
       }
        
        //output.insert(0, space);
    }
    else if (input >= -65536 && input < 65536){                                //2^19
        //cout << "made it \n";
        input  = 0x200000 | input ;
        while(input != 0 && input != -1){
            long long int j = (input & 0xff);
            //cout << j << '\n';
            char l = j;
            output.insert(it, l);     
            input = input >> 8;
            it = output.begin();
        }
        if (isNeg == true && input == -1){
            output.insert(it, '\x2f');
            it = output.begin();
       }
        //output.insert(0, space);
    }
    else if (input >= -16777216 && input < 16777216){                          //2^27
        //cout << "made it \n";
        input  = 0x30000000 | input ;
        while(input != 0 && input != -1){
            long long int j = (input & 0xff);
            //cout << j << '\n';
            char l = j;
            output.insert(it, l);     
            input = input >> 8;
            it = output.begin();
        }
        if (isNeg == true && input == -1){
           output.insert(it, '\x3f');
           it = output.begin();
       }
        //output.insert(0, space);
    }
    else if (input >= -4294967296 && input < 4294967296){                      //2^35
            //cout << "made it \n";
        input  = 0x4000000000 | input ;
        while(input != 0 && input != -1){
            long long int j = (input & 0xff);
            //cout << j << '\n';
            char l = j;
            output.insert(it, l);     
            input = input >> 8;
            it = output.begin();
        }
        if (isNeg == true && input == -1){
           output.insert(it, '\x4f');
           it = output.begin();
       }
//         //output.insert(0, space);
//         
    }
    else if (input >= -1099511627776 && input < 1099511627776){                      //2^43
            //cout << "made it \n";
        input  = 0x500000000000 | input ;
        while(input != 0 && input != -1){
            long long int j = (input & 0xff);
            //cout << j << '\n';
            char l = j;
            output.insert(it, l);     
            input = input >> 8;
            it = output.begin();
        }
        if (isNeg == true && input == -1){
           output.insert(it, '\x5f');
           it = output.begin();
       }
//         //output.insert(0, space);
//         
    }
    else if (input >= -281474976710656 && input < 281474976710656){                      //2^51
            //cout << "made it \n";
        input  = 0x60000000000000 | input ;
        while(input != 0 && input != -1){
            long long int j = (input & 0xff);
            //cout << j << '\n';
            char l = j;
            output.insert(it, l);     
            input = input >> 8;
            it = output.begin();
        }
        if (isNeg == true && input == -1){
           output.insert(it, '\x6f');
           it = output.begin();
       }
//         //output.insert(0, space);
//         
    }
    else if (input >= -72057594037927936 && input < 72057594037927936){                      //2^59
            //cout << "made it \n";
        input  = 0x7000000000000000 | input ;
        while(input != 0 && input != -1){
            long long int j = (input & 0xff);
            //cout << j << '\n';
            char l = j;
            output.insert(it, l);     
            input = input >> 8;
            it = output.begin();
        }
        if (input == -1 && input == -1){
           output.insert(it, '\x7f');
           it = output.begin();
       }
    }
       else{                      //2^67
            //cout << "made it \n";
        long long int mask = 0x8000000000000000;
        while(input != 0 && input != -1){
            long long int j = (input & 0xff);
           // cout << input << '\n';
          //  cout << j << '\n';
            char l = j;
            output.insert(it, l);     
            input = input >> 8;
            input = mask | input;
            mask = mask >> 8;
            it = output.begin();
        }
        if (isNeg == true && input == -1){
           output.insert(it, '\x8f');
           it = output.begin();
       }
//         //output.insert(0, space);
//         
    }
    return output;
}


//OFSerial
    
OFSerial::OFSerial(const std::string s){
    stream.open(s);
    if (stream.good()){
        state = true;
    }
    else{
        state = false;
    }
}

OFSerial::~OFSerial(){}

//     OFSerial >> bool
OFSerial &operator<<(OFSerial &s, const bool b){
    if (s.fail()){
        return s;
    }
    if (b == true) s.stream << 't';
    else if (b == false) s.stream << 'f';
    return s;
    
}

//     OFSerial >> int
OFSerial &operator<<(OFSerial &s, const int i){
    if (s.fail()){
        return s;
    }
    s.stream << 'i';
    int isNeg = false;
    if (i < 0) isNeg = true;
    vector<char> ans = thatsAInt(i,isNeg);
    for(auto u: ans){
         s.stream << char(u);
    }
    return s;
}
    
//     OFSerial >> short
OFSerial &operator<<(OFSerial &s, const short ss){
    if (s.fail()){
        return s;
    }
    s.stream << 's';
    int isNeg = false;
    if (ss < 0) isNeg = true;
    vector<char> ans = thatsAInt(ss,isNeg);
    for(auto i: ans){
         s.stream << char(i);
    }
    return s;
}
//     OFSerial >> long
OFSerial &operator<<(OFSerial &s, const long l){
    if (s.fail()){
        return s;
    }
    s.stream << 'l';
    int isNeg = false;
    if (l < 0) isNeg = true;
    vector<char> ans = thatsAInt(l,isNeg);
    for(auto i: ans){
         s.stream << char(i);
    }
    return s;
}
//     OFSerial >> char
OFSerial &operator<<(OFSerial &s, const char c){
    if (s.fail()){
        return s;
    }
    s.stream << 'c';
    s.stream << c;
    return s;
}
//     OFSerial >> std::string
OFSerial &operator<<(OFSerial &s, const std::string S){
    if (s.fail()){
        return s;
    }
    s.stream << 'S';
    vector<char> ans = thatsAInt(S.length(),false);
    for (auto i: ans){
        s.stream << char (i);
    }
    
    for (const auto& i : S) {
        s.stream << char(i);
    }
    return s;
}

//     OFSerial.fail()
bool OFSerial::fail() const{
    return !state;
}
 long long int makeAnInt(IFSerial &s){
    char shiftIt = s.stringy[0];
//     cout << +s.stringy[0];
    s.stringy.erase(s.stringy.begin());
     long shiftLit = long(shiftIt);
//     cout << shiftLit << '\n';
    if (shiftLit > 15){
//         cout << shiftLit << "\n";
        int count = shiftLit & 0xf0;
        shiftLit = shiftLit & 0x0f;
//         int shit = shiftLit;
//         cout << shiftLit << '\n';
        while(count > 15){
//             cout << count << "\n";
            count = count - 16;
            shiftIt = s.stringy[0];
//              cout << s.stringy[0];
            s.stringy.erase(s.stringy.begin());
            short temp = short(shiftIt);
//             cout << +shiftIt<< "\n";
//             cout << temp <<"\n";
            shiftLit <<= 8;
            temp = temp & 0x00ff;
//             cout << shiftLit <<"\n";

//             cout << temp << '\n';
            shiftLit |= temp;
//             cout << shiftLit << "\n";
        }
            
        
    }
    
    return shiftLit; 
}
