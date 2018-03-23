//
// Created by conor on 2/25/2018.
//
#include <iostream>
#include <cstdint>

#ifndef CS370_CYCLE1_FILELIB_H
#define CS370_CYCLE1_FILELIB_H

class filelib {
public:
    filelib();

    static bool exist(std::string thisfile);
    //bool valid(std::string thisfile);
    //std::string name_form(std::string name);
    //std::string exten(std::string name);
    static std::string base_name(std::string name);
    //std::string attribs(byte b);
    //std::string path(std::string fn);
    static std::string no_path(std::string fn);
    //long file_length(std::string fn);

private:
    const char
        null = 0,
        bell = 7,
        esc  = 27,
        f10  = 68; //original was $44?

    const uint8_t
        basex = 1,
        basey = 1,
        tempx = 1,
        tempy = 1,
        endx  = 24,
        endy  = 80;

    //registers regs;
    //uint16_t textattr;
    //std::string workstr;

};

#endif //CS370_CYCLE1_FILELIB_H
