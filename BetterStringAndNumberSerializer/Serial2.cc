#include "Serial.h"
#include <sstream>

using namespace std;


//Constructor
Serial::Serial(){}

//Copy Constructor
Serial::Serial(const Serial &Seri){
    stringy = Seri.getVec();
}

//Destructor
Serial::~Serial() {}

//Assignment Operator
Serial &Serial::operator=(const Serial &Seri) {
        stringy = Seri.getVec();
        return *this;
}

//VecGetter
vector<char> Serial::getVec() const{
    vector<char> temp = this->stringy;
    return temp;
}

//Print string
string Serial::str() const {
    std::string str(stringy.begin(),stringy.end());
    return str;
}

//Set stirng
void Serial::str(std::string str) {
    vector<char> temp(str.begin(), str.end());
    stringy = temp;
}

//Size
int Serial::size() const {
    return stringy.size();
}

//Empty
bool Serial::empty() const {
    if (stringy.empty()) return true;
    else return false;
}

vector<char> Serial::thatsAInt(long long input, bool isNeg) {
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
        input = 0x0f & input;
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


void Serial::put(bool b){
    if (b == true) stringy.push_back('\x74');
    else if (b == false) stringy.push_back('\x66');
}

void Serial::put(short s){
    stringy.push_back('s');
    int isNeg = false;
    if (s < 0) isNeg = true;
    vector<char> ans = Serial::thatsAInt(s,isNeg);
    for(auto i: ans){
         stringy.push_back(char(i));}
}

void Serial::put(int i){
    stringy.push_back('i');
    int isNeg = false;
    if (i < 0) isNeg = true;
    vector<char> ans = Serial::thatsAInt(i,isNeg);
    for(auto u: ans){
         stringy.push_back(char(u));}   
}

void Serial::put(long l){
    stringy.push_back('l');
    int isNeg = false;
    if (l < 0) isNeg = true;
    vector<char> ans = Serial::thatsAInt(l,isNeg);
    for(auto i: ans){
         stringy.push_back(char(i));}
}
         
void Serial::put(char c){
    stringy.push_back('c');
    stringy.push_back(c);
}

void Serial::put(std::string S){
    stringy.push_back('S');
    vector<char> ans = Serial::thatsAInt(S.length(),false);
    for (auto i: ans){
        stringy.push_back(char(i));
    }
    
    for (const auto& i : S) {
        stringy.push_back(char(i));
    }
}

long long int Serial::makeAnInt(){
    char shiftIt = stringy[0];
//     cout << +stringy[0];
    stringy.erase(stringy.begin());
    long shiftLit = long(shiftIt);
//     cout << shiftLit << '\n';
    if (shiftLit > 15){
//         cout << shiftLit << "\n";
        int count = shiftLit & 0xf0;
        shiftLit = shiftLit & 0x0f;
        while(count > 15){
//             cout << count << "\n";
            count = count - 16;
            shiftIt = stringy[0];
//              cout << stringy[0];
            stringy.erase(stringy.begin());
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


void Serial::get(bool &b){
//     cout << stringy[0] << "\n";
    if (stringy[0] != 't' && stringy[0] != 'f') 
        {throw ("Incorrect tag - Not a bool"s);}
    else if (stringy[0] == 't'){
        b = true;
//         cout << stringy[0] << "\n";
        stringy.erase(stringy.begin());
    }
    else if (stringy[0] == 'f'){
        b = false;
        stringy.erase(stringy.begin());
    }
}


void Serial::get(short &s){
    if (stringy[0] != 's'){throw ("Incorrect tag - Not a short"s);}
    stringy.erase(stringy.begin());
    long long int ans = Serial::makeAnInt();
    s = short(ans);
}

void Serial::get(int &i){
//     std::string str(stringy.begin(),stringy.end());
//     cout << str << '\n';
    if (stringy[0] != 'i'){throw ("Incorrect tag - Not a int"s);}
    stringy.erase(stringy.begin());
    long long int ans = Serial::makeAnInt();
    i = int(ans);
}

void Serial::get(long &l){
    if (stringy[0] != 'l'){throw ("Incorrect tag - Not a long"s);}
    stringy.erase(stringy.begin());
    long long int ans = Serial::makeAnInt();
//     cout << ans;
    l = long(ans);
}

void Serial::get(char &c){
    //cout << "j";
    if (stringy[0] != 'c'){throw ("Incorrect tag - Not a char"s);}
    else {
    stringy.erase(stringy.begin());
    c = stringy[0];
    stringy.erase(stringy.begin());
    }
}

void Serial::get(std::string &S){
    S = "";
    if (stringy[0] != 'S'){throw ("Incorrect tag - Not a string"s);}
    else{
    stringy.erase(stringy.begin());
    if (stringy[0] == '\x10'){stringy.erase(stringy.begin());}
    char count = stringy[0];
    while (count != 0){
        stringy.erase(stringy.begin());
        S += stringy[0];
        count--;
    }
    stringy.erase(stringy.begin());
    }
}


//Output operator overrides

//<<
std::ostream &operator<<(std::ostream &stream, const Serial &val) {
    return stream << val.str();
}

//+=Bool
Serial &Serial::operator+=(const bool &rhs) {
    this->put(rhs);
    return *this;
}

//+=Int
Serial &Serial::operator+=(const int &rhs) {
    this->put(rhs);
    return *this;
}

//+=Short
Serial &Serial::operator+=(const short &rhs) {
    this->put(rhs);
    return *this;
}

//+=Long
Serial &Serial::operator+=(const long &rhs) {
    this->put(rhs);
    return *this;
}

//+=Char
Serial &Serial::operator+=(const char &rhs) {
    this->put(rhs);
    return *this;
}

//+=String
Serial &Serial::operator+=(const std::string &rhs) {
    this->put(rhs);
    return *this;
}

//+=Serial
Serial &Serial::operator+=(const Serial &rhs) {
    vector<char> temp = rhs.getVec();
    for (auto i : temp){
        stringy.push_back(i);
    }
    return *this;
}

//Serial + Bool
Serial Serial::operator+(const bool i) const{
    Serial temp = *this;
    temp.put(i);
    return temp;
}

//Serial + Int
Serial Serial::operator+(const int i) const{
    Serial temp = *this;
    temp.put(i);
    return temp;
}

//Serial + Short
Serial Serial::operator+(const short i) const{
    Serial temp = *this;
    temp.put(i);
    return temp;
}

//Serial + Long
Serial Serial::operator+(const long i) const{
    Serial temp = *this;
    temp.put(i);
    return temp;
}

//Serial + Char
Serial Serial::operator+(const char i) const{
    Serial temp = *this;
    temp.put(i);
    return temp;
}

//Serial + Sring
Serial Serial::operator+(const std::string i) const{
    Serial temp = *this;
    temp.put(i);
    return temp;
}

//Serial + Serial
Serial Serial::operator+(const Serial &i) const{
    std::string str1 = this->str();
    std::string str2 = i.str();
    str1 += str2;
    Serial ans;
    ans.str(str1);
    return ans;
}

//Bool + Serial
Serial operator+(bool const i, Serial const &s){
    Serial temp;
    temp.put(i);
    string tempI = temp.str();
    string tempS = s.str();
    tempI += tempS;
    temp.str(tempI);
    return temp;
}

//Int + Serial
Serial operator+(int const i, Serial const &s){
    Serial temp;
    temp.put(i);
    std::string tempI = temp.str();
    std::string tempS = s.str();
    tempI += tempS;
    temp.str(tempI);
    return temp;
}

//Short + Serial
Serial operator+(short const i, Serial const &s){
    Serial temp;
    temp.put(i);
    std::string tempI = temp.str();
    std::string tempS = s.str();
    tempI += tempS;
    temp.str(tempI);
    return temp;
}

//Long + Serial
Serial operator+(long const i, Serial const &s){
    Serial temp;
    temp.put(i);
    std::string tempI = temp.str();
    std::string tempS = s.str();
    tempI += tempS;
    temp.str(tempI);
    return temp;
}

//Char + Serial
Serial operator+(char const i, Serial const &s){
    Serial temp;
    temp.put(i);
    std::string tempI = temp.str();
    std::string tempS = s.str();
    tempI += tempS;
    temp.str(tempI);
    return temp;
}

//String + Serial
Serial operator+(std::string const i, Serial const &s){
    Serial temp;
    temp.put(i);
    std::string tempI = temp.str();
    std::string tempS = s.str();
    tempI += tempS;
    temp.str(tempI);
    return temp;
}

//Bool <<= Serial
bool operator<<=(bool &i, Serial &s){
//     try{
        s.get(i); 
//     }
//     catch (string s){
//         throw s;
//     }
    return i;
}

//Int <<= Serial
int operator<<=(int &i, Serial &s){
    try{
        s.get(i); 
    }
    catch (string s){
        throw s;
    }
    return i;
}

//Short <<= Serial
short operator<<=(short &i, Serial &s){
    try{
        s.get(i); 
    }
    catch (string s){
        throw s;
    }
    return i;
}

//Long <<= Serial
long operator<<=(long &i, Serial &s){
    try{
        s.get(i); 
    }
    catch (string s){
        throw s;
    }
    return i;
}

//Char <<= Serial
char operator<<=(char &i, Serial &s){
    try{
        s.get(i); 
    }
    catch (string s){
        throw s;
    }
    return i;
}

//String <<= Serial
std::string operator<<=(std::string &i, Serial &s){
    try{
        s.get(i); 
    }
    catch (string s){
        throw s;
    }
    return i;
}

//==
bool Serial::operator==(const Serial &rhs) const {
    if (rhs.str().compare(this->str()) == 0) return true;
    else return false;
}

//!=
bool Serial::operator!=(const Serial &rhs) const {
    // Let == do the real work.
    return !(*this == rhs);
}


