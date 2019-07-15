#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>

class Serial{

public:
    
    Serial();
    Serial(const Serial &);
    ~Serial();
    Serial &operator=(const Serial &);
    
    std::vector<char> getVec() const;
    std::string str() const;
    void str(std::string); 

    int size() const;
    bool empty() const;
    
    void put(bool);
    void put(short);
    void put(int);
    void put(long);
    void put(char);
    void put(std::string);

    void get(bool &);
    void get(short &);
    void get(int &);
    void get(long &);
    void get(char &);
    void get(std::string &);
    
    Serial &operator+=(const bool &);
    Serial &operator+=(const int &);
    Serial &operator+=(const short &);
    Serial &operator+=(const long &);
    Serial &operator+=(const char &);
    Serial &operator+=(const std::string &);
    Serial &operator+=(const Serial &);
    
    Serial operator+(const bool) const;
    Serial operator+(const int) const;
    Serial operator+(const short) const;
    Serial operator+(const long) const;
    Serial operator+(const char) const;
    Serial operator+(const std::string) const;
    Serial operator+(const Serial &) const;
    
    bool operator==(const Serial &) const;
    bool operator!=(const Serial &) const;

private:
    
    std::vector<char> stringy;
    std::vector<char> thatsAInt(long long input, bool isNeg);
    long long int makeAnInt();
    
};

    std::ostream &operator<<(std::ostream &, const Serial &);

    Serial operator+(bool const, Serial const &);
    Serial operator+(int const, Serial const &);
    Serial operator+(short const, Serial const &);
    Serial operator+(long const, Serial const &);
    Serial operator+(char const, Serial const &);
    Serial operator+(std::string const, Serial const &);
    
    bool operator<<=(bool &i, Serial &s);
    int operator<<=(int &i, Serial &s);
    short operator<<=(short &i, Serial &s);
    long operator<<=(long &i, Serial &s);
    char operator<<=(char &i, Serial &s);
    std::string operator<<=(std::string &i, Serial &s);


#endif
