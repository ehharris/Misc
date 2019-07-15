#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class IFSerial{

public:
    
    IFSerial(const std::string);
    ~IFSerial();
    explicit operator bool() const{ return (state); };
//     IFSerial.eof()
    bool eof() const;
//     IFSerial.fail()
    bool fail() const;
    std::vector<char> stringy;
    void eof(const bool b);
    void fail(const bool b);
private:
    
    std::ifstream stream;
    bool state;
    bool eof2;
};

class OFSerial {

public:
    
    OFSerial(const std::string);
    ~OFSerial();
    explicit operator bool() const{ return (state); };

//     OFSerial.fail()
    bool fail() const;
    std::ofstream stream;

private:
    std::vector<char> stringy;
    
    bool state;
    bool eof2;
};
std::vector<char> thatsAInt(long long, bool);
long long int makeAnInt(IFSerial &);
//     IFSerial >> bool
    IFSerial &operator>>(IFSerial &, bool &);
//     IFSerial >> int
    IFSerial &operator>>(IFSerial &, int &);
//     IFSerial >> short
    IFSerial &operator>>(IFSerial &, short &);
//     IFSerial >> long
    IFSerial &operator>>(IFSerial &, long &);
//     IFSerial >> char
    IFSerial &operator>>(IFSerial &, char &);
//     IFSerial >> std::string
    IFSerial &operator>>(IFSerial &, std::string &);
    
    //     OFSerial >> bool
    OFSerial &operator<<(OFSerial &, const bool);
//     OFSerial >> int
    OFSerial &operator<<(OFSerial &, const int);
//     OFSerial >> short
    OFSerial &operator<<(OFSerial &, const short);
//     OFSerial >> long
    OFSerial &operator<<(OFSerial &, const long);
//     OFSerial >> char
    OFSerial &operator<<(OFSerial &, const char);
//     OFSerial >> std::string
    OFSerial &operator<<(OFSerial &, const std::string);
#endif
