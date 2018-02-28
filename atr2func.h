//
// Created by conor on 2/18/2018.
//
#include <iostream>

#ifndef CS370_CYCLE1_ATR2FUNC_H
#define CS370_CYCLE1_ATR2FUNC_H


class atr2func {
public:
    atr2func();

    static double sint[256], cost[256];

    //void textxy(int x, int y, std::string s);
    //void coltextxy(int x, int y, std::string s, byte c);
    //static char hexnum(uint8_t num); //Not used
    //static std::string hexb(uint8_t num); //Not used
    static std::string hex(int num);
    static double valuer(std::string i);
    static long value(std::string i);
    static std::string cstrr(double i);
    static std::string cstr(long i);
    static std::string zero_pad(long n, long l);
    static std::string zero_pads(std::string s, long l);
    static std::string addfront(std::string b, int l);
    static std::string addrear(std::string b, int l);
    static std::string ucase(std::string s);
    static std::string lcase(std::string s);
    static std::string space(uint8_t i);
    //std::string repchar(char c, byte i);
    static std::string ltrim(std::string s1);
    static std::string rtrim(std::string s1);
    static std::string btrim(std::string s1);
    static std::string lstr(std::string s1, int l);
    static std::string rstr(std::string s1, int l);
    //void FlushKey();
    //void calibrate_timing();
    //void time_delay(int n); //{n=milliseconds}
    //void check_registration();
    //int rol(int n, int k);
    //int ror(int n, int k);
    //int sal(int n, int k);
    //int sar(int n, int k);
    //void viewport(int x1, int y1, int x2, int y2);
    //void main_viewport();
    static void make_tables();
    //int robot_color(int n);
    //void box(int x1, int y1, int x2, int y2);
    //void hole(int x1, int y1, int x2, int y2);
    //void chirp();
    //void click();
    static int hex2int(std::string s);
    static int str2int(std::string s);
    static double distance(double x1, double y1, double x2, double y2);
    //double find_angle(double xx, double yy, double tx, double ty);
    //int find_anglei(double xx, double yy, double tx, double ty);
    //std::string bin(int n);
    //std::string decimal(int num, int length);

private:
    //long delay_per_sec;
    //bool registered, graphix, sound_on;
    //std::string reg_name;
    //word reg_num;
};


#endif //CS370_CYCLE1_ATR2FUNC_H
