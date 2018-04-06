//
// Created by conor on 3/21/2018.
//

#include "atr2.h"
#include "atr2func.h"
#include "filelib.h"
#include "arena.h"
#include <QEventLoop>

atr2::atr2(atr2var* avtemp, arena* parent) {
    av = avtemp;
    atr2a = parent;
}

atr2::atr2(atr2var* avtemp, arena* parent, QEventLoop* loopy) {
    av = avtemp;
    atr2a = parent;
    //loop = loopy;
}

std::string atr2::operand(int n, int m) {
    std::string s;
    s = n;

    switch (m & 7) {
        case 1: s = "@" + s; break;
        case 2: s = ":" + s; break;
        case 3: s = "$" + s; break;
        case 4: s = "!" + s; break;
        default: s = n;
    }

    if ((m & 8) > 0) {
        s = "[" + s + "]";
    }

    return s;
}

std::string atr2::mnemonic(int n, int m)  {
    std::string s;
    s = n;

    if (m == 0) {
        switch (n) {
            case 0: s = "NOP"; break;
            case 1: s = "ADD"; break;
            case 2: s = "SUB"; break;
            case 3: s = "OR"; break;
            case 4: s = "AND"; break;
            case 5: s = "XOR"; break;
            case 6: s = "NOT"; break;
            case 7: s = "MPY"; break;
            case 8: s = "DIV"; break;
            case 9: s = "MOD"; break;
            case 10: s = "RET"; break;
            case 11: s = "CALL"; break;
            case 12: s = "JMP"; break;
            case 13: s = "JLS"; break;
            case 14: s = "JGR"; break;
            case 15: s = "JNE"; break;
            case 16: s = "JE"; break;
            case 17: s = "SWAP"; break;
            case 18: s = "DO"; break;
            case 19: s = "LOOP"; break;
            case 20: s = "CMP"; break;
            case 21: s = "TEST"; break;
            case 22: s = "MOV"; break;
            case 23: s = "LOC"; break;
            case 24: s = "GET"; break;
            case 25: s = "PUT"; break;
            case 26: s = "INT"; break;
            case 27: s = "IPO"; break;
            case 28: s = "OPO"; break;
            case 29: s = "DELAY"; break;
            case 30: s = "PUSH"; break;
            case 31: s = "POP"; break;
            case 32: s = "ERR"; break;
            case 33: s = "INC"; break;
            case 34: s = "DEC"; break;
            case 35: s = "SHL"; break;
            case 36: s = "SHR"; break;
            case 37: s = "ROL"; break;
            case 38: s = "ROR"; break;
            case 39: s = "JZ"; break;
            case 40: s = "JNZ"; break;
            case 41: s = "JGE"; break;
            case 42: s = "JLE"; break;
            case 43: s = "SAL"; break;
            case 44: s = "SAR"; break;
            case 45: s = "NEG"; break;
            case 46: s = "JTL"; break;
            default: s = "XXX";
        }
    } else {
        s = operand(n,m);
    }

    return s;
}

void atr2::log_error(int n, int i, std::string ov) {
    int j, k;
    std::string s;

    if (!av->logging_errors) {
        return;
    }
    switch(i) {
        case 1:
            s = "Stack full - Too many CALLs?";
            break;
        case 2:
            s = "Label not found. Hmmm.";
            break;
        case 3:
            s = "Can't assign value - Tisk tisk.";
            break;
        case 4:
            s = "Illegal memory reference";
            break;
        case 5:
            s = "Stack empty - Too many RETs?";
            break;
        case 6:
            s = "Illegal instruction. How bizarre.";
            break;
        case 7:
            s = "Return out of range - Woops!";
            break;
        case 8:
            s = "Divide by zero";
            break;
        case 9:
            s = "Unresolved !label. WTF?";
            break;
        case 10:
            s = "Invalid Interrupt Call";
            break;
        case 11:
            s = "Invalid Port Access";
            break;
        case 12:
            s = "Com Queue empty";
            break;
        case 13:
            s = "No mine-layer, silly.";
            break;
        case 14:
            s = "No mines left";
            break;
        case 15:
            s = "No shield installed - Arm the photon torpedoes instead. :-)";
            break;
        case 16:
            s = "Invalid Microcode in instruction.";
            break;
        default:
            s = "Unkown error";
            break;
    }
    av->robot[n].errorlog << "<" << i << "> " << s << " (Line #" << av->robot[n].ip << ") [Cycle: " << av->game_cycle << ", Match: "
                         << av->played << "/" << av->matches << "]" << std::endl;
    av->robot[n].errorlog << " " << mnemonic(av->robot[n].code[av->robot[n].ip].op[0], av->robot[n].code[av->robot[n].ip].op[3] & 15) << " "
                         << operand(av->robot[n].code[av->robot[n].ip].op[1], (av->robot[n].code[av->robot[n].ip].op[3] >> 4) & 15) << ", "
                         << operand(av->robot[n].code[av->robot[n].ip].op[2], (av->robot[n].code[av->robot[n].ip].op[3] >> 8) & 15);
    if (!ov.empty()) {
        av->robot[n].errorlog << "    (Values: " << ov << ")" << std::endl;
    } else {
        av->robot[n].errorlog << std::endl;
    }
    av->robot[n].errorlog << " AX=" << atr2func::addrear(atr2func::cstr(av->robot[n].ram[65]) + ",", 7);
    av->robot[n].errorlog << " BX=" << atr2func::addrear(atr2func::cstr(av->robot[n].ram[66]) + ",", 7);
    av->robot[n].errorlog << " CX=" << atr2func::addrear(atr2func::cstr(av->robot[n].ram[67]) + ",", 7);
    av->robot[n].errorlog << " DX=" << atr2func::addrear(atr2func::cstr(av->robot[n].ram[68]) + ",", 7);
    av->robot[n].errorlog << " EX=" << atr2func::addrear(atr2func::cstr(av->robot[n].ram[69]) + ",", 7);
    av->robot[n].errorlog << " FX=" << atr2func::addrear(atr2func::cstr(av->robot[n].ram[70]) + ",", 7);
    av->robot[n].errorlog << " Flags=" << av->robot[n].ram[64] << std::endl;
    av->robot[n].errorlog << " AX=" << atr2func::addrear(atr2func::hex(av->robot[n].ram[65]) + ",", 7);
    av->robot[n].errorlog << " BX=" << atr2func::addrear(atr2func::hex(av->robot[n].ram[66]) + ",", 7);
    av->robot[n].errorlog << " CX=" << atr2func::addrear(atr2func::hex(av->robot[n].ram[67]) + ",", 7);
    av->robot[n].errorlog << " DX=" << atr2func::addrear(atr2func::hex(av->robot[n].ram[68]) + ",", 7);
    av->robot[n].errorlog << " EX=" << atr2func::addrear(atr2func::hex(av->robot[n].ram[69]) + ",", 7);
    av->robot[n].errorlog << " FX=" << atr2func::addrear(atr2func::hex(av->robot[n].ram[70]) + ",", 7);
    av->robot[n].errorlog << " Flags=" << atr2func::hex(av->robot[n].ram[64]) << std::endl;
    av->robot[n].errorlog << std::endl;
}

int atr2::max_shown() {
    switch(av->stats_mode) {
        case 1:
            return 12;
        case 2:
            return 32;
        default:
            return 6;
    }
}

void atr2::update_armor(int n) {

}

void atr2::update_heat(int n) {

}

void atr2::robot_error(int n, int i, std::string ov) {
    if (av->logging_errors) {
        log_error(n, i, ov);
        av->robot[n].error_count++;
    }
}

void atr2::update_lives(int n) {

}

void atr2::prog_error(int n, std::string ss) {
    std::string s;

    //graph_mode(false);
    //textcolor(15); turns text white?
    std::cout << "Error #" << n << ": ";

    switch(n) {
        case 0:
            std::cout << "User error.";
            break;
        case 1:
            std::cout << "Invalid :label - \"" << ss << "\", silly mortal.";
            break;
        case 2:
            std::cout << "Undefined identifier - \"" << ss << "\". A typo perhaps?";
            break;
        case 3:
            std::cout << "Memory access out of range - \"" << ss << "\"";
            break;
        case 4:
            std::cout << "Not enough robots for combat. Maybe we should just drive in circles.";
            break;
        case 5:
            std::cout << "Robot names and settings must be specified. An empty arena is no fun.";
            break;
        case 6:
            std::cout << "Config file not found - \"" << ss << "\"";
            break;
        case 7:
            std::cout << "Cannot access a config file from a config file - \"" << ss << "\"";
            break;
        case 8:
            std::cout << "Robot not found \"" << ss << "\". Perhaps you mistyped it?";
            break;
        case 9:
            std::cout << "Insufficient RAM to load robot: \"" << ss << "\"... This is not good.";
            break;
        case 10:
            std::cout << "Too many robots! We can only handle " << atr2var::max_robots << "! Blah.. limits are limits.";
            break;
        case 11:
            std::cout << "You already have a perfectly good #def for \"" << ss << "\", silly.";
            break;
        case 12:
            std::cout << "Variable name too long! (Max: " << atr2var::max_var_len << ") \"" << ss << "\"";
            break;
        case 13:
            std::cout << "!Label already defined \"" << ss << "\", silly.";
            break;
        case 14:
            std::cout << "Too many variables! (Var Limit: " << atr2var::max_vars << ")";
            break;
        case 15:
            std::cout << "Too many !labels! (!Label Limit: " << atr2var::max_labels << ")";
            break;
        case 16:
            std::cout << "Robot program too long! Boldly we simplify, simplify along... " << ss;
            break;
        case 17:
            std::cout << "!Label missing error. !Label #" << ss << ".";
            break;
        case 18:
            std::cout << "!Label out of range: " << ss;
            break;
        case 19:
            std::cout << "!Label not found. " << ss;
            break;
        case 20:
            std::cout << "Invalid config option: \"" << ss << "\". Inventing a new device?";
            break;
        case 21:
            std::cout << "Robot is attempting to cheat; Too many config points (" << ss << ")";
            break;
        case 22:
            std::cout << "Insufficient data in data statement: \"" << ss << "\"";
            break;
        case 23:
            std::cout << "Too many asterisks: \"" << ss << "\"";
            break;
        case 24:
            std::cout << "Invalid step count: \"" << ss << "\". 1-9 are valid conditions.";
            break;
        case 25:
            std::cout << "\"" << ss << "\"";
            break;
        default:
            std::cout << ss;
    }
    std::cout << std::endl;
    exit(n);
}

void atr2::print_code(int n, int p) {
    int i;
    std::cout << atr2func::hex(p) << ": ";
    for (i = 0; i <= atr2var::max_op; i++) {
        std::cout << atr2func::zero_pad(av->robot[n].code[p].op[i], 5) << " ";
    }
    std::cout << " = ";
    for (i = 0; i <= atr2var::max_op; i++) {
        std::cout << atr2func::hex(av->robot[n].code[p].op[i]) << "h " << "\n\n";
    }
}

void atr2::parse1(int n, int p, atr2var::parsetype s) {
    int i, j, k, opcode, microcode;
    bool found, indirect;
    std::string ss;

    //with av->robot[n]^ do
    for (i = 0; i <= (atr2var::max_op - 1); i++) {
        k = 0;
        found = false;
        opcode = 0;
        microcode = 0;
        s[i] = atr2func::btrim(atr2func::ucase(s[i]));
        //DEBUG_CONOR
        //std::cout << "s[" << i << "] = " << s[i] << std::endl;
        indirect = false;

        /*
         * Microcode:
         *      0 = instruction, number, constant
         *      1 = variable, memory access
         *      2 = :label
         *      3 = !label (unresolved)
         *      4 = !label (resolved)
         *      8h mask = indirect addressing (enclosed in [])
         */

        //If std::string is empty (figure out how to access struct array properly
        if (s[i].empty()) {
            opcode = 0;
            microcode = 0;
            found = true;
        }

        if ((atr2func::lstr(s[i], 1)[0] == '[') && (atr2func::rstr(s[i], 1)[0] == ']')) {
            s[i] = atr2func::lstr(atr2func::rstr(s[i], (int)s[i].length() - 1), (int)s[i].length() - 2);
            indirect = true;
        }

        //!labels
        if(!found && s[i][0]=='!') {
            ss = s[i];
            ss = atr2func::btrim(atr2func::rstr(ss, (int)ss.length()-1));
            if (av->numlabels > 0) {
                for (j = 1; j <= av->numlabels; j++) {
                    if (ss.compare(av->labelname[j]) == 0) {
                        found = true;
                        if (av->labelnum[j] >= 0) {
                            opcode = av->labelnum[j];
                            microcode = 4;
                            //resolved label
                        } else {
                            opcode = j;
                            microcode = 3;
                            //unresolved label
                        }
                    }
                }
            }
            if (!found) {
                av->numlabels++;
                if (av->numlabels > atr2var::max_labels) {
                    exit(15);
                } else {
                    av->labelname[av->numlabels] = ss;
                    av->labelnum[av->numlabels] = -1;
                    opcode = av->numlabels;
                    microcode = 3; //unresolved !label
                    found = true;
                }
            }
        }

        ///variables
        if (av->numvars > 0 && !found) {
            for (j = 1; j <= av->numvars; j++) {
                if (s[i].compare(av->varname[j]) == 0) {
                    opcode = av->varloc[j];
                    microcode = 1; //variable
                    found = true;
                }
            }
        }

        ///instructions
        if (s[i] == "NOP"     ) { opcode = 0; found = true; } else
        if (s[i] == "ADD"     ) { opcode = 1; found = true; } else
        if (s[i] == "SUB"     ) { opcode = 2; found = true; } else
        if (s[i] == "OR"      ) { opcode = 3; found = true; } else
        if (s[i] == "AND"     ) { opcode = 4; found = true; } else
        if (s[i] == "XOR"     ) { opcode = 5; found = true; } else
        if (s[i] == "NOT"     ) { opcode = 6; found = true; } else
        if (s[i] == "MPY"     ) { opcode = 7; found = true; } else
        if (s[i] == "DIV"     ) { opcode = 8; found = true; } else
        if (s[i] == "MOD"     ) { opcode = 9; found = true; } else
        if (s[i] == "RET"     ) { opcode = 10; found = true; } else
        if (s[i] == "RETURN"  ) { opcode = 10; found = true; } else
        if (s[i] == "GSB"     ) { opcode = 11; found = true; } else
        if (s[i] == "GOSUB"   ) { opcode = 11; found = true; } else
        if (s[i] == "CALL"    ) { opcode = 11; found = true; } else
        if (s[i] == "JMP"     ) { opcode = 12; found = true; } else
        if (s[i] == "JUMP"    ) { opcode = 12; found = true; } else
        if (s[i] == "GOTO"    ) { opcode = 12; found = true; } else
        if (s[i] == "JLS"     ) { opcode = 13; found = true; } else
        if (s[i] == "JB"      ) { opcode = 13; found = true; } else
        if (s[i] == "JGR"     ) { opcode = 14; found = true; } else
        if (s[i] == "JA"      ) { opcode = 14; found = true; } else
        if (s[i] == "JNE"     ) { opcode = 15; found = true; } else
        if (s[i] == "JEQ"     ) { opcode = 16; found = true; } else
        if (s[i] == "JE"      ) { opcode = 16; found = true; } else
        if (s[i] == "XCHG"    ) { opcode = 17; found = true; } else
        if (s[i] == "SWAP"    ) { opcode = 17; found = true; } else
        if (s[i] == "DO"      ) { opcode = 18; found = true; } else
        if (s[i] == "LOOP"    ) { opcode = 19; found = true; } else
        if (s[i] == "CMP"     ) { opcode = 20; found = true; } else
        if (s[i] == "TEST"    ) { opcode = 21; found = true; } else
        if (s[i] == "SET"     ) { opcode = 22; found = true; } else
        if (s[i] == "MOV"     ) { opcode = 22; found = true; } else
        if (s[i] == "LOC"     ) { opcode = 23; found = true; } else
        if (s[i] == "ADDR"    ) { opcode = 23; found = true; } else
        if (s[i] == "GET"     ) { opcode = 24; found = true; } else
        if (s[i] == "PUT"     ) { opcode = 25; found = true; } else
        if (s[i] == "INT"     ) { opcode = 26; found = true; } else
        if (s[i] == "IPO"     ) { opcode = 27; found = true; } else
        if (s[i] == "IN"      ) { opcode = 27; found = true; } else
        if (s[i] == "OPO"     ) { opcode = 28; found = true; } else
        if (s[i] == "OUT"     ) { opcode = 28; found = true; } else
        if (s[i] == "DEL"     ) { opcode = 29; found = true; } else
        if (s[i] == "DELAY"   ) { opcode = 29; found = true; } else
        if (s[i] == "PUSH"    ) { opcode = 30; found = true; } else
        if (s[i] == "POP"     ) { opcode = 31; found = true; } else
        if (s[i] == "ERR"     ) { opcode = 32; found = true; } else
        if (s[i] == "ERROR"   ) { opcode = 32; found = true; } else
        if (s[i] == "INC"     ) { opcode = 33; found = true; } else
        if (s[i] == "DEC"     ) { opcode = 34; found = true; } else
        if (s[i] == "SHL"     ) { opcode = 35; found = true; } else
        if (s[i] == "SHR"     ) { opcode = 36; found = true; } else
        if (s[i] == "ROL"     ) { opcode = 37; found = true; } else
        if (s[i] == "ROR"     ) { opcode = 38; found = true; } else
        if (s[i] == "JZ"      ) { opcode = 39; found = true; } else
        if (s[i] == "JNZ"     ) { opcode = 40; found = true; } else
        if (s[i] == "JAE"     ) { opcode = 41; found = true; } else
        if (s[i] == "JGE"     ) { opcode = 41; found = true; } else
        if (s[i] == "JLE"     ) { opcode = 42; found = true; } else
        if (s[i] == "JBE"     ) { opcode = 42; found = true; } else
        if (s[i] == "SAL"     ) { opcode = 43; found = true; } else
        if (s[i] == "SAR"     ) { opcode = 44; found = true; } else
        if (s[i] == "NEG"     ) { opcode = 45; found = true; } else
        if (s[i] == "JTL"     ) { opcode = 46; found = true; } else

            ///registers
        if (s[i] == "COLCNT"  ) { opcode = 8; microcode = 1; found = true; } else
        if (s[i] == "METERS"  ) { opcode = 9; microcode = 1; found = true; } else
        if (s[i] == "COMBASE" ) { opcode = 10; microcode = 1; found = true; } else
        if (s[i] == "COMEND"  ) { opcode = 11; microcode = 1; found = true; } else
        if (s[i] == "FLAGS"   ) { opcode = 64; microcode = 1; found = true; } else
        if (s[i] == "AX"      ) { opcode = 65; microcode = 1; found = true; } else
        if (s[i] == "BX"      ) { opcode = 66; microcode = 1; found = true; } else
        if (s[i] == "CX"      ) { opcode = 67; microcode = 1; found = true; } else
        if (s[i] == "DX"      ) { opcode = 68; microcode = 1; found = true; } else
        if (s[i] == "EX"      ) { opcode = 69; microcode = 1; found = true; } else
        if (s[i] == "FX"      ) { opcode = 70; microcode = 1; found = true; } else
        if (s[i] == "SP"      ) { opcode = 71; microcode = 1; found = true; } else

            ///constants
        if (s[i] == "MAXINT"    ) { opcode = 32767;  microcode = 0; found = true; } else
        if (s[i] == "MININT"    ) { opcode = -32768; microcode = 0; found = true; } else
        if (s[i] == "P_SPEDOMETER"  ) { opcode = 1; microcode = 0; found = true; } else
        if (s[i] == "P_HEAT"        ) { opcode = 2; microcode = 0; found = true; } else
        if (s[i] == "P_COMPASS"     ) { opcode = 3; microcode = 0; found = true; } else
        if (s[i] == "P_TANGLE"      ) { opcode = 4; microcode = 0; found = true; } else
        if (s[i] == "P_TURRET_OFS"  ) { opcode = 4; microcode = 0; found = true; } else
        if (s[i] == "P_THEADING"    ) { opcode = 5; microcode = 0; found = true; } else
        if (s[i] == "P_TURRET_ABS"  ) { opcode = 5; microcode = 0; found = true; } else
        if (s[i] == "P_ARMOR"       ) { opcode = 6; microcode = 0; found = true; } else
        if (s[i] == "P_DAMAGE"      ) { opcode = 6; microcode = 0; found = true; } else
        if (s[i] == "P_SCAN"        ) { opcode = 7; microcode = 0; found = true; } else
        if (s[i] == "P_ACCURACY"    ) { opcode = 8; microcode = 0; found = true; } else
        if (s[i] == "P_RADAR"       ) { opcode = 9; microcode = 0; found = true; } else
        if (s[i] == "P_RANDOM"      ) { opcode = 10; microcode = 0; found = true; } else
        if (s[i] == "P_RAND"        ) { opcode = 10; microcode = 0; found = true; } else
        if (s[i] == "P_THROTTLE"    ) { opcode = 11; microcode = 0; found = true; } else
        if (s[i] == "P_TROTATE"     ) { opcode = 12; microcode = 0; found = true; } else
        if (s[i] == "P_OFS_TURRET"  ) { opcode = 12; microcode = 0; found = true; } else
        if (s[i] == "P_TAIM"        ) { opcode = 13; microcode = 0; found = true; } else
        if (s[i] == "P_ABS_TURRET"  ) { opcode = 13; microcode = 0; found = true; } else
        if (s[i] == "P_STEERING"    ) { opcode = 14; microcode = 0; found = true; } else
        if (s[i] == "P_WEAP"        ) { opcode = 15; microcode = 0; found = true; } else
        if (s[i] == "P_WEAPON"      ) { opcode = 15; microcode = 0; found = true; } else
        if (s[i] == "P_FIRE"        ) { opcode = 15; microcode = 0; found = true; } else
        if (s[i] == "P_SONAR"       ) { opcode = 16; microcode = 0; found = true; } else
        if (s[i] == "P_ARC"         ) { opcode = 17; microcode = 0; found = true; } else
        if (s[i] == "P_SCANARC"     ) { opcode = 17; microcode = 0; found = true; } else
        if (s[i] == "P_OVERBURN"    ) { opcode = 18; microcode = 0; found = true; } else
        if (s[i] == "P_TRANSPONDER" ) { opcode = 19; microcode = 0; found = true; } else
        if (s[i] == "P_SHUTDOWN"    ) { opcode = 20; microcode = 0; found = true; } else
        if (s[i] == "P_CHANNEL"     ) { opcode = 21; microcode = 0; found = true; } else
        if (s[i] == "P_MINELAYER"   ) { opcode = 22; microcode = 0; found = true; } else
        if (s[i] == "P_MINETRIGGER" ) { opcode = 23; microcode = 0; found = true; } else
        if (s[i] == "P_SHIELD"      ) { opcode = 24; microcode = 0; found = true; } else
        if (s[i] == "P_SHIELDS"     ) { opcode = 24; microcode = 0; found = true; } else
        if (s[i] == "I_DESTRUCT"    ) { opcode = 0; microcode = 0; found = true; } else
        if (s[i] == "I_RESET"       ) { opcode = 1; microcode = 0; found = true; } else
        if (s[i] == "I_LOCATE"      ) { opcode = 2; microcode = 0; found = true; } else
        if (s[i] == "I_KEEPSHIFT"   ) { opcode = 3; microcode = 0; found = true; } else
        if (s[i] == "I_OVERBURN"    ) { opcode = 4; microcode = 0; found = true; } else
        if (s[i] == "I_ID"          ) { opcode = 5; microcode = 0; found = true; } else
        if (s[i] == "I_TIMER"       ) { opcode = 6; microcode = 0; found = true; } else
        if (s[i] == "I_ANGLE"       ) { opcode = 7; microcode = 0; found = true; } else
        if (s[i] == "I_TID"         ) { opcode = 8; microcode = 0; found = true; } else
        if (s[i] == "I_TARGETID"    ) { opcode = 8; microcode = 0; found = true; } else
        if (s[i] == "I_TINFO"       ) { opcode = 9; microcode = 0; found = true; } else
        if (s[i] == "I_TARGETINFO"  ) { opcode = 9; microcode = 0; found = true; } else
        if (s[i] == "I_GINFO"       ) { opcode = 10; microcode = 0; found = true; } else
        if (s[i] == "I_GAMEINFO"    ) { opcode = 10; microcode = 0; found = true; } else
        if (s[i] == "I_RINFO"       ) { opcode = 11; microcode = 0; found = true; } else
        if (s[i] == "I_ROBOTINFO"   ) { opcode = 11; microcode = 0; found = true; } else
        if (s[i] == "I_COLLISIONS"  ) { opcode = 12; microcode = 0; found = true; } else
        if (s[i] == "I_RESETCOLCNT" ) { opcode = 13; microcode = 0; found = true; } else
        if (s[i] == "I_TRANSMIT"    ) { opcode = 14; microcode = 0; found = true; } else
        if (s[i] == "I_RECEIVE"     ) { opcode = 15; microcode = 0; found = true; } else
        if (s[i] == "I_DATAREADY"   ) { opcode = 16; microcode = 0; found = true; } else
        if (s[i] == "I_CLEARCOM"    ) { opcode = 17; microcode = 0; found = true; } else
        if (s[i] == "I_KILLS"       ) { opcode = 18; microcode = 0; found = true; } else
        if (s[i] == "I_DEATHS"      ) { opcode = 18; microcode = 0; found = true; } else
        if (s[i] == "I_CLEARMETERS" ) { opcode = 19; microcode = 0; found = true; }


        ///memory addresses
        if ((!found) && (s[i].compare(0, 1, "@") == 0) && isdigit(s[i][1]) ) {
            opcode = atr2func::str2int(atr2func::rstr(s[i], s[i].length() - 1));
            if ((opcode < 0) || (opcode > (atr2var::max_ram + 1) + (((atr2var::max_code + 1) << 3) - 1))) {
                prog_error(3, s[i]);
            }
            microcode = 1;
            found = true;
        }

        ///numbers
        if ((!found) && (isdigit(s[i][0]) || (s[i][0] == '-'))) {
            opcode = atr2func::str2int(s[i]);
            found = true;
        }

        if (found) {
            av->robot[n].code[p].op[i] = opcode;
            if (indirect) {
                microcode = microcode | 8;
            }
            av->robot[n].code[p].op[atr2var::max_op] = av->robot[n].code[p].op[atr2var::max_op] | (microcode << (i * 4));
            //DEBUG_CONOR
            //std::cout << "robot #" << n << ", opcode being set to " << av->robot[n].code[p].op[i] << ", microcode being set to " << av->robot[n].code[p].op[atr2var::max_op] << std::endl;
        } else if (!s[i].empty()) {
            prog_error(2, s[i]);
        }
    }

    if (atr2var::show_code) {
        print_code(n, p);
    }
    if (atr2var::compile_by_line) {
        //readkey;
    }
}

void atr2::check_plen(int plen) {
    if (plen > av->maxcode) {
        //std::ostringstream streamtemp;
        //streamtemp << "\nMaximum program length exceeded, (Limit: " << av->maxcode+1 << " compiled lines)";
        prog_error(16, "Maximum program length exceeded.");
    }

}

void atr2::compile(int n, std::string filename) {
    atr2var::parsetype pp;
    std::string s, s1, s2, s3, orig_s, msg;
    int i, j, k, l, linecount, mask, locktype;
    std::string ss[atr2var::max_op];
    char c, lc;
    std::ifstream f;
    bool robotdone = false;

    av->lock_code = "";
    av->lock_pos = 0;
    locktype = 0;
    av->lock_dat = 0;

    if (!filelib::exist(filename)) {
        prog_error(8, filename);
    }
    //textcolor(robot_color(n));
    std::cout << "Compiling robot #" << n+1 << ": " << filename << std::endl;

    av->robot[n].is_locked = false;
    av->numvars = 0;
    av->numlabels = 0;
    for (k = 0; k < atr2var::max_code; k++) {
        for (i = 0; i <= atr2var::max_op; i++) {
            av->robot[n].code[k].op[i] = 0;
        }
    }
    av->robot[n].plen = 0;
    //assign(f, filename);
    f.open(filename);
    //reset(f);
    s = "";
    linecount = 0;

    while(getline(f, s) && (robotdone == false)) { //(not eof(f)) and (s != "#END)
        //readln(f,s);
        linecount++;
        if (locktype < 3) {
            av->lock_pos = 0;
        }
        if (!av->lock_code.empty()) {
            for (i = 1; i < (int)s.length(); i++) {
                av->lock_pos++;
                if (av->lock_pos > (int)av->lock_code.length()) {
                    av->lock_pos = 1;
                }
                switch(locktype) {
                    case 3:
                        s[i] = (char)(((int)s[i] - 1) ^ ((int)av->lock_code[av->lock_pos] ^ av->lock_dat));
                        break;
                    case 2:
                        //s[i] = char(ord(s[i]) xor (ord(av->lock_code[av->lock_pos]) xor 1));
                        s[i] = (char)(((int)s[i]) ^ ((int)av->lock_code[av->lock_pos] ^ 1));
                        break;
                    default:
                        //s[i] = char(ord(s[i]) xor ord(av->lock_code[av->lock_pos]));
                        s[i] = (char)(((int)s[i]) ^ ((int)av->lock_code[av->lock_pos]));
                }
                av->lock_dat = (int)s[i] & 15;
            }
        }
        s = atr2func::btrim(s);
        orig_s = s;
        for (i = 0; i < (int)s.length(); i++) {
            if (((int)(s[i]) <= 32) || ((int)(s[i]) >= 128) || s[i] == ',') { //s[i] in [#0..#32,',',#128..#255]
                s.replace(i, 1, " ");
            }
        }
        if (av->show_source && (av->lock_code.empty() || atr2var::debugging_compiler)) {
            std::cout << atr2func::zero_pad(linecount, 3) << ":" << atr2func::zero_pad(av->robot[n].plen, 3) << " " << s << std::endl;
        }
        if (atr2var::debugging_compiler) {
            //if ((int)av->robot[n].readkey == 27) {
            //    exit(0);
            //}
        }
        k = 0;
        for (i = (int)s.length() - 1; i >= 0; i--) {
            if (s[i] == ';') {
                k = i;
            }
        }
        if(k > 0) {
            s = atr2func::lstr(s, k-1);
        }
        s = atr2func::btrim(atr2func::ucase(s));
        for (i = 0; i <= atr2var::max_op; i++) {
            pp[i].clear();
        }
        if (((int)s.length() > 0) && (s[0] != ';')) {
            if (s[0] == '#') {          //Compiler directives
                s1 = atr2func::ucase(atr2func::btrim(atr2func::rstr(s, s.length() - 1)));
                msg = atr2func::btrim(atr2func::rstr(orig_s, orig_s.length() - 5));

                if (s1 == "END") {
                    robotdone = true;
                }

                k = 0;
                for (i = 0; i < s1.length(); i++) {
                    if ((k == 0) && (s1[i] == ' ')) {
                        k = i;
                    }
                }
                k--;
                if (k > 1) {
                    s2 = atr2func::lstr(s1, k + 1);
                    s3 = atr2func::ucase(atr2func::btrim(atr2func::rstr(s1, s1.length() - k - 1)));

                    //DEBUG CONOR
                    //std::cout << "s2=" << s2 << ", s3=" << s3 << std::endl;
                    k = 0;
                    if (av->numvars > 0) {
                        for (i = 0; i < av->numvars; i++) {
                            if (s3.compare(av->varname[i]) == 0) {
                                k = i;
                            }
                        }
                    }
                    if ((s2 == "DEF") && (av->numvars < atr2var::max_vars)) {
                        if ((int)s3.length() > atr2var::max_var_len) {
                            prog_error(12, s3);
                        } else {
                            if (k > 0) {
                                prog_error(11, s3);
                            } else {
                                av->numvars++;
                                if (av->numvars > atr2var::max_vars) {
                                    prog_error(14, "");
                                } else {
                                    av->varname[av->numvars] = s3;
                                    av->varloc[av->numvars]  = 127 + av->numvars;
                                }
                            }
                        }
                    } else if (atr2func::lstr(s2, 4) == "LOCK") {
                        av->robot[n].is_locked = true; //this robot is locked
                        if ((int)s2.length() > 4) {
                            locktype = atr2func::value(atr2func::rstr(s2, s2.length() - 4));
                        }
                        av->lock_code = atr2func::btrim(atr2func::ucase(s3));
                        std::cout << "Robot is of LOCKed format from this point forward. [" << locktype << "]";
                        for (i = 0; i < (int)av->lock_code.length(); i++) {
                            av->lock_code[i] = (char)((int)av->lock_code[i] - 65);
                        }
                    } else if (s2 == "MSG") {
                        av->robot[n].name = msg;
                    } else if (s2 == "TIME") {
                        av->robot[n].robot_time_limit = atr2func::value(s3);
                        if (av->robot[n].robot_time_limit < 0) {
                            av->robot[n].robot_time_limit = 0;
                        }
                    } else if (s2 == "CONFIG") {
                        if (atr2func::lstr(s3, 8) == "SCANNER=") {
                            av->robot[n].config.scanner = atr2func::value(atr2func::rstr(s3, s3.length() - 8));
                        } else if (atr2func::lstr(s3, 7) == "SHIELD=") {
                            av->robot[n].config.shield = atr2func::value(atr2func::rstr(s3, s3.length() - 7));
                        } else if (atr2func::lstr(s3, 7) == "WEAPON=") {
                            av->robot[n].config.weapon = atr2func::value(atr2func::rstr(s3, s3.length() - 7));
                        } else if (atr2func::lstr(s3, 6) == "ARMOR=") {
                            av->robot[n].config.armor = atr2func::value(atr2func::rstr(s3, s3.length() - 6));
                        } else if (atr2func::lstr(s3, 7) == "ENGINE=") {
                            av->robot[n].config.engine = atr2func::value(atr2func::rstr(s3, s3.length() - 7));
                        } else if (atr2func::lstr(s3, 10) == "HEATSINKS=") {
                            av->robot[n].config.heatsinks = atr2func::value(atr2func::rstr(s3, s3.length() - 10));
                        } else if (atr2func::lstr(s3, 6) == "MINES=") {
                            av->robot[n].config.mines = atr2func::value(atr2func::rstr(s3, s3.length() - 7));
                        } else {
                            prog_error(20, s3);
                        }

                        if (av->robot[n].config.scanner < 0) {
                            av->robot[n].config.scanner = 0;
                        }
                        if (av->robot[n].config.scanner > 5) {
                            av->robot[n].config.scanner = 5;
                        }
                        if (av->robot[n].config.shield < 0) {
                            av->robot[n].config.shield = 0;
                        }
                        if (av->robot[n].config.shield > 5) {
                            av->robot[n].config.shield = 5;
                        }
                        if (av->robot[n].config.weapon < 0) {
                            av->robot[n].config.weapon = 0;
                        }
                        if (av->robot[n].config.weapon > 5) {
                            av->robot[n].config.weapon = 5;
                        }
                        if (av->robot[n].config.armor < 0) {
                            av->robot[n].config.armor = 0;
                        }
                        if (av->robot[n].config.armor > 5) {
                            av->robot[n].config.armor = 5;
                        }
                        if (av->robot[n].config.engine < 0) {
                            av->robot[n].config.engine = 0;
                        }
                        if (av->robot[n].config.engine > 5) {
                            av->robot[n].config.engine = 5;
                        }
                        if (av->robot[n].config.heatsinks < 0) {
                            av->robot[n].config.heatsinks = 0;
                        }
                        if (av->robot[n].config.heatsinks > 5) {
                            av->robot[n].config.heatsinks = 5;
                        }
                        if (av->robot[n].config.mines < 0) {
                            av->robot[n].config.mines = 0;
                        }
                        if (av->robot[n].config.mines > 5) {
                            av->robot[n].config.mines = 5;
                        }
                    } else {
                        std::cout << "Warning: unknown directive \"" << s2 << "\"" << std::endl;
                    }
                }
            } else if (s[0] == '*') {   //Inline Pre-Compiled Machine Code
                check_plen(av->robot[n].plen);
                for (i = 0; i <= atr2var::max_op; i++) {
                    pp[i].clear();
                }
                for (i = 2; i < (int)s.length(); i++) {
                    if (s[i] == '*') {
                        prog_error(22, s);
                    }
                }
                k = 0;
                i = 1;
                s1 = "";
                if ((int)s.length() > 2) {
                    prog_error(22, s);
                }
                while ((i < s.length()) && (k <= atr2var::max_op)) {
                    i++;
                    if ((((int)(s[i]) >= 33) && ((int)(s[i]) <= 41)) ||
                        (((int)(s[i]) >= 43) && ((int)(s[i]) <= 127))) {
                        pp[k] = pp[k] + s[i];
                    } else if ((((int)(s[i]) <= 32) || ((int)(s[i]) >= 128)) &&
                               ((((int)(s[i-1]) >= 33) && ((int)(s[i-1]) <= 41)) ||
                                (((int)(s[i-1]) >= 43) && ((int)(s[i-1]) <= 127)))) {
                        k++;
                    }
                }
                for (i = 0; i <= atr2var::max_op; i++) {
                    av->robot[n].code[av->robot[n].plen].op[i] = atr2func::str2int(pp[i]);
                }
                av->robot[n].plen++;
            } else if (s[0] == ':') {   //:labels
                check_plen(av->robot[n].plen);
                s1 = atr2func::rstr(s, s.length() - 1);
                for (i = 0; i < s1.length(); i++) {
                    if (!isdigit(s1[i])) {
                        prog_error(1, s);
                    }
                }
                av->robot[n].code[av->robot[n].plen].op[0] = atr2func::str2int(s1);
                av->robot[n].code[av->robot[n].plen].op[atr2var::max_op] = 2;
                //DEBUG_CONOR
                //std::cout << ":LABEL: " << s1 << ", op[0]=" << av->robot[n].code[av->robot[n].plen].op[0] << ", op[3]=" << av->robot[n].code[av->robot[n].plen].op[atr2var::max_op] << ", plen=" << av->robot[n].plen << std::endl;
                if (atr2var::show_code) {
                    print_code(n, av->robot[n].plen);
                }
                av->robot[n].plen++;
            } else if (s[0] == '!') {   //!labels
                check_plen(av->robot[n].plen);
                s1 = atr2func::btrim(atr2func::rstr(s, s.length() - 1));
                //DEBUG_CONOR
                //std::cout << "!LABEL: " << s1 << std::endl;
                k = 0;
                for (i = s1.length() - 1; i >= 0; i--) {
                    if ((s1.compare(i, 1, "\b") == 0) || (s1.compare(i, 1, "\t") == 0) ||
                        (s1.compare(i, 1, "\n") == 0) || (s1.compare(i, 1, ",") == 0) || (s1.compare(i, 1, "\r") == 0) ||
                        (s1.compare(i, 1, " ") == 0) || (s1.compare(i, 1, ";") == 0)) {
                        k = i;
                    }
                }
                if (k > 0) {
                    s1 = atr2func::lstr(s1, k - 1);
                }
                k = 0;
                for (i = 1; i <= av->numlabels; i++) {
                    if (av->labelname[i] == s1) {
                        if (av->labelnum[i] >= 0) {
                            prog_error(13, "\"!" + s1 + "\" (" + atr2func::cstr(av->labelnum[i]) + ")");
                        }
                        k = i;
                    }
                }
                if (k == 0) {
                    av->numlabels++;
                    if (av->numlabels > atr2var::max_labels) {
                        prog_error(15, "");
                    }
                    k = av->numlabels;
                }
                av->labelname[k] = s1;
                av->labelnum[k] = av->robot[n].plen;
            } else {                    //Instructions/Numbers
                check_plen(av->robot[n].plen);
                //parse instructions
                //remove comments
                k = 0;
                for (i = s1.length() - 1; i >= 0; i--) {
                    if (s[i] == ';') {
                        k = i;
                    }
                }
                if (k > 0) {
                    s = atr2func::lstr(s, k - 1);
                }
                //setup variables for parsing
                k = 0;
                for (j = 0; j <= atr2var::max_op; j++) {
                    pp[j].clear();
                }
                for (j = 0; j < s.length(); j++) {
                    c = s[j];
                    if (!((c == '\b') || (c == '\t') || (c == '\n') || (c == ',') || (c == '\r') ||
                          (c == ' ')) && (k <= atr2var::max_op)) {
                        pp[k] = pp[k] + c;
                    } else if (!((lc == '\b') || (lc == '\t') || (lc == '\n') || (lc == ',') || (lc == '\r') ||
                                 (lc == ' '))) {
                        k = k + 1;
                    }
                    lc = c;
                }
                parse1(n, av->robot[n].plen, pp);
                av->robot[n].plen++;
            }
        }
    }
    f.close();
    if (av->robot[n].plen <= av->maxcode) {
        for (i = 0; i <= atr2var::max_op; i++) {
            pp[i].clear();
            parse1(n, av->robot[n].plen, pp);
        }
    } else {
        av->robot[n].plen--;
    }

    //second pass, resolving !labels
    if (av->numlabels > 0) {
        for (i = 0; i < av->robot[n].plen; i++) {
            for (j = 0; j <= (atr2var::max_op - 1); j++) {
                if ((av->robot[n].code[i].op[atr2var::max_op] >> (j*4)) == 3) {
                    k = av->robot[n].code[i].op[j];
                    if ((k > 0) && (k <= av->numlabels)) {
                        l = av->labelnum[k];
                        if (l < 0) {
                            prog_error(19, "\"!" + av->labelname[k] + "\" (" + atr2func::cstr(l) + ")");
                        }
                        if ((l < 0) || (l > av->maxcode)) {
                            prog_error(18, "\"!" + av->labelname[k] + "\" (" + atr2func::cstr(l) + ")");
                        } else {
                            av->robot[n].code[i].op[j] = l;
                            mask = !(15 << (j*4));
                            av->robot[n].code[i].op[atr2var::max_op] = (av->robot[n].code[i].op[atr2var::max_op] & mask) | (4 << (j*4));
                            //resolved !label
                        }
                    } else {
                        prog_error(17, atr2func::cstr(k));
                    }
                }
            }
        }
    }
    //textcolor(7);
}

void atr2::robot_config(int n) {
    int i, j, k;

    switch (av->robot[n].config.scanner) {
        case 5:
            av->robot[n].scanrange = 1500;
            break;
        case 4:
            av->robot[n].scanrange = 1000;
            break;
        case 3:
            av->robot[n].scanrange = 700;
            break;
        case 2:
            av->robot[n].scanrange = 500;
            break;
        case 1:
            av->robot[n].scanrange = 350;
            break;
        default:
            av->robot[n].scanrange = 250;
    }

    switch (av->robot[n].config.weapon) {
        case 5:
            av->robot[n].shotstrength = 1.5;
            break;
        case 4:
            av->robot[n].shotstrength = 1.35;
            break;
        case 3:
            av->robot[n].shotstrength = 1.2;
            break;
        case 2:
            av->robot[n].shotstrength = 1.0;
            break;
        case 1:
            av->robot[n].shotstrength = 0.8;
            break;
        default:
            av->robot[n].shotstrength = 0.5;
    }

    switch (av->robot[n].config.armor) {
        case 5:
            av->robot[n].damageadj = 0.66;
            av->robot[n].speedadj  = 0.66;
            break;
        case 4:
            av->robot[n].damageadj = 0.77;
            av->robot[n].speedadj  = 0.75;
            break;
        case 3:
            av->robot[n].damageadj = 0.83;
            av->robot[n].speedadj  = 0.85;
            break;
        case 2:
            av->robot[n].damageadj = 1.0;
            av->robot[n].speedadj  = 1.0;
            break;
        case 1:
            av->robot[n].damageadj = 1.5;
            av->robot[n].speedadj  = 1.2;
            break;
        default:
            av->robot[n].damageadj = 2.0;
            av->robot[n].speedadj  = 1.33;
    }

    switch (av->robot[n].config.engine) {
        case 5:
            av->robot[n].speedadj = av->robot[n].speedadj * 1.5;
            break;
        case 4:
            av->robot[n].speedadj = av->robot[n].speedadj * 1.35;
            break;
        case 3:
            av->robot[n].speedadj = av->robot[n].speedadj * 1.2;
            break;
        case 2:
            av->robot[n].speedadj = av->robot[n].speedadj * 1.0;
            break;
        case 1:
            av->robot[n].speedadj = av->robot[n].speedadj * 0.8;
            break;
        default:
            av->robot[n].speedadj = av->robot[n].speedadj * 0.5;
    }

    switch (av->robot[n].config.mines) {
        case 5:
            av->robot[n].mines = 24;
            break;
        case 4:
            av->robot[n].mines = 16;
            break;
        case 3:
            av->robot[n].mines = 10;
            break;
        case 2:
            av->robot[n].mines = 6;
            break;
        case 1:
            av->robot[n].mines = 4;
            break;
        default:
            av->robot[n].mines = 2;
            av->robot[n].config.mines = 0;
    }

    av->robot[n].shields_up = false;
    if (av->robot[n].config.shield < 3 || av->robot[n].config.shield > 5) {
        av->robot[n].config.shield = 0;
    }
    if (av->robot[n].config.heatsinks < 0 || av->robot[n].config.heatsinks > 5) {
        av->robot[n].config.heatsinks = 0;
    }
}

void atr2::reset_software(int n) {
    int i;
    for(i = 0; i < atr2var::max_ram; i++) {
        av->robot[n].ram[i] = 0;
        av->robot[n].ram[71] = 768;
        av->robot[n].thd = av->robot[n].hd;
        av->robot[n].tspd = 0;
        av->robot[n].scanarc = 8;
        av->robot[n].shift = 0;
        av->robot[n].err = 0;
        av->robot[n].overburn = false;
        av->robot[n].keepshift = false;
        av->robot[n].ip = 0;
        av->robot[n].accuracy = 0;
        av->robot[n].meters = 0;
        av->robot[n].delay_left = 0;
        av->robot[n].time_left = 0;
        av->robot[n].shields_up = false;
    }
}

void atr2::reset_hardware(int n) {
    int i;
    double d, dd;

    for(i = 0; i < atr2var::max_robot_lines; i++) {
        av->robot[n].ltx[i] = 0;
        av->robot[n].tx[i] = 0;
        av->robot[n].lty[i] = 0;
        av->robot[n].ty[i] = 0;
    }
    do {
        av->robot[n].x = rand() % 1000;
        av->robot[n].y = rand() % 1000;
        dd = 1000;
        for(i = 0; i < av->num_robots; i++) {
            if(av->robot[i].x < 0) {
                av->robot[i].x = 0;
            }
            if(av->robot[i].x > 1000) {
                av->robot[i].x = 1000;
            }
            if(av->robot[i].y < 0) {
                av->robot[i].y = 0;
            }
            if(av->robot[i].y > 1000) {
                av->robot[i].y = 1000;
            }
            d = atr2func::distance(av->robot[n].x, av->robot[n].y, av->robot[i].x, av->robot[i].y);
            if((av->robot[i].armor > 0) && (i != n) && (d < dd)) {
                dd = d;
            }
        }
    } while (!(dd > 32));

    for (i = 0; i < atr2var::max_mines; i++) {
        av->robot[n].mine[i].x = -1;
        av->robot[n].mine[i].y = -1;
        av->robot[n].mine[i].yield = 0;
        av->robot[n].mine[i].detonate = false;
        av->robot[n].mine[i].detect = 0;
    }
    av->robot[n].lx = -1;
    av->robot[n].ly = -1;
    av->robot[n].hd = rand() % 256;
    av->robot[n].shift = 0;
    av->robot[n].lhd = av->robot[n].hd +1;
    av->robot[n].lshift = av->robot[n].shift + 1;
    av->robot[n].spd = 0;
    av->robot[n].speed = 0;
    av->robot[n].cooling = false;
    av->robot[n].armor = 100;
    av->robot[n].larmor = 0;
    av->robot[n].heat = 0;
    av->robot[n].lheat = 1;
    av->robot[n].match_shots = 0;
    av->robot[n].won = false;
    av->robot[n].last_damage = 0;
    av->robot[n].last_hit = 0;
    av->robot[n].transponder = n + 1;
    av->robot[n].meters = 0;
    av->robot[n].shutdown = 400;
    av->robot[n].shields_up = false;
    av->robot[n].channel = av->robot[n].transponder;
    av->robot[n].startkills = av->robot[n].kills;
    robot_config(n);
}

void atr2::init_robot(int n) {

    int i,j,k,l;

    av->robot[n].wins = 0;
    av->robot[n].trials = 0;
    av->robot[n].kills = 0;
    av->robot[n].deaths = 0;
    av->robot[n].shots_fired = 0;
    av->robot[n].match_shots = 0;
    av->robot[n].hits = 0;
    av->robot[n].damage_total = 0;
    av->robot[n].cycles_lived = 0;
    av->robot[n].error_count = 0;
    av->robot[n].plen = 0;
    av->robot[n].max_time = 0;
    av->robot[n].name = "";
    av->robot[n].fn = "";
    av->robot[n].speed = 0;
    av->robot[n].arc_count = 0;
    av->robot[n].sonar_count = 0;
    av->robot[n].robot_time_limit = 0;
    av->robot[n].scanrange = 1500;
    av->robot[n].shotstrength = 1;
    av->robot[n].damageadj = 1;
    av->robot[n].speedadj = 1;
    av->robot[n].mines = 0;

    av->robot[n].config.scanner = 5;
    av->robot[n].config.weapon = 2;
    av->robot[n].config.armor = 2;
    av->robot[n].config.engine = 2;
    av->robot[n].config.heatsinks = 1;
    av->robot[n].config.shield = 0;
    av->robot[n].config.mines = 0;

    for (i = 0; i < atr2var::max_ram; i++) {
        av->robot[n].ram[i] = 0;
    }

    av->robot[n].ram[71] = 768;

    for (i = 0; i < atr2var::max_code; i++) {
        for (k = 0; k <= atr2var::max_op; k++) {
            av->robot[n].code[i].op[k] = 0;
        }
    }
    reset_hardware(n);
    reset_software(n);
}

void atr2::create_robot(int n, std::string filename) {
    int i, j, k;

    //maxavail is no longer applicable to modern operating systems
    /*if(maxavail < sizeof(robot_rec)) {
        prog_error(9, atr2func::base_name(atr2func::no_path(filename)));
    }*/
    //Do we need to create with new?
    //new(av->robot[n]);
    init_robot(n);
    filename = atr2func::ucase(atr2func::btrim(filename));
    if (filename == filelib::base_name(filename)) {
        if (filename[0] == '?') {
            filename = filename + av->locked_ext;
        } else {
            filename = filename + av->robot_ext;
        }
    }
    if (filename[0] == '?') {
        filename = atr2func::rstr(filename, filename.length() - 1);
    }
    av->robot[n].fn = filelib::base_name(filelib::no_path(filename));
    compile(n, filename);
    robot_config(n);

    k = av->robot[n].config.scanner + av->robot[n].config.armor + av->robot[n].config.weapon + av->robot[n].config.engine +
        av->robot[n].config.heatsinks + av->robot[n].config.shield + av->robot[n].config.mines;
    if (k > atr2var::max_config_points) {
        //DEBUG CONOR
        //std::cout << av->robot[n].config.scanner << av->robot[n].config.armor << av->robot[n].config.weapon << av->robot[n].config.engine <<
        //     av->robot[n].config.heatsinks << av->robot[n].config.shield << av->robot[n].config.mines << std::endl;
        prog_error(21, atr2func::cstr(k) + "/" + atr2func::cstr(atr2var::max_config_points));
    }
}

void atr2::shutdown() {
    int i, j, k;

    // graph_mode(false);
    if (av->show_cnotice == true) {

        //   textcolor(3);
        std::cout << av->progname << " " << av->version << " ";
        std::cout << av->cnotice1 << "\n";
        std::cout << av->cnotice2 << "\n";
        std::cout << av->cnotice3 << "\n";
    }

    //textcolor(7);
    if (!av->registered) {
        //textcolor(4);
        std::cout << "Unregistered version";
    } else {
        std::cout << "Registered to: " << av->reg_name;
    }
    //textcolor(7);
    std::cout << "\n";
    if (av->logging_errors) {

        for (i = 0; i < av->num_robots; i++) {
            std::cout << "Robot error-log created: " << filelib::base_name(av->robot[i].fn) << "-" << std::to_string(i + 1) << ".ERR" << std::endl;
            av->robot[i].errorlog.close();
        }
    }
    exit(0);
}

void atr2::delete_compile_report(){
    //not done
    //if exist(main_filename+compile_ext) then
    //delete_file(main_filename+compile_ext);
}

void atr2::write_compile_report(){
    std::ofstream f;
    int i,j,k;

    f.open(av->main_filename + av->compile_ext);

    f << av->num_robots + 1 << "\n";

    for (i = 0; i < av->num_robots; i++){
        f << av->robot[i].fn << "\n";
    }

    f.close();
// textcolor(15);

    std::cout << "\nAll compiles successful!" << "\n\n";

    shutdown();
}

void atr2::parse_param(std::string s) {
    std::ofstream f;
    std::string fn, s1;
    bool found;

    found = false;
    s = atr2func::btrim(atr2func::ucase(s));

    if (s.empty()){
        exit(0);
    }

    if (s[0] == '#'){

        fn = atr2func::rstr(s,s.length()-1);
        if (fn == filelib::base_name(fn)){
            fn = fn + av->config_ext;
        }
        //   if not exist(fn) then prog_error(6,fn);
        //   assign(f,fn); reset(f);
        //   while not eof(f) do
        //     readln(f,s1);
        //     s1:=ucase(btrim(s1));
        //     if s1[1]='#' then prog_error(7,s1)
        //        else parse_param(s1);
        //    end;
        //   close(f);
        //   found:=true;
    }

    else if (s[0] == '/' || s[0] == '-' || s[0] == '=') {
        s1 = atr2func::rstr(s, s.length() - 1);
        if (s1[0] == 'X') {
            av->step_mode = atr2func::value(atr2func::rstr(s1, s1.length() - 1));
            found = true;
            if (av->step_mode == 0) {
                av->step_mode = 1;
            }
            if (av->step_mode < 1 || av->step_mode > 9) {
                prog_error(24, atr2func::rstr(s1, s1.length() - 1));
            }
        }

        if (s1[0] == 'D') {
            av->game_delay = atr2func::value(atr2func::rstr(s1, s1.length() - 1));
            found = true;
        }

        if (s1[0] == 'T') {
            av->time_slice = atr2func::value(atr2func::rstr(s1, s1.length() - 1));
            found = true;
        }

        if (s1[0] == 'L') {
            av->game_limit = atr2func::value(atr2func::rstr(s1, s1.length() - 1)) * 1000;
            found = true;
        }

        if (s1[0] == 'Q') {
            av->sound_on = false;
            found = true;
        }

        if (s1[0] == 'M') {
            av->matches = atr2func::value(atr2func::rstr(s1, s1.length() - 1));
            found = true;
        }

        if (s1[0] == 'S') {
            av->show_source = false;
            found = true;
        }

        if (s1[0] == 'G') {
            av->no_gfx = true;
            found = true;
        }

        if (s1[0] == 'R') {
            av->report = true;
            found = true;
            if (s1.length() > 1) {
                av->report_type = atr2func::value(atr2func::rstr(s1, s1.length() - 1));
            }
        }

        if (s1[0] == 'C') {
            av->compile_only = true;
            found = true;
        }

        if (s1[0] == '^') {
            av->show_cnotice = false;
            found = true;
        }

        if (s1[0] == 'A') {
            av->show_arcs = true;
            found = true;
        }

        if (s1[0] == 'W') {
            av->windoze = false;
            found = true;
        }

        if (s1[0] == '$') {
            av->debug_info = true;
            found = true;
        }

        if (s1[0] == '#') {
            av->maxcode = atr2func::value(atr2func::rstr(s1, s1.length() - 1)) - 1;
            found = true;
        }

        if (s1[0] == '!') {
            av->insane_missiles = true;
            if (s1.length() > 1) {
                av->insanity = atr2func::value(atr2func::rstr(s1, s1.length() - 1));
            }
            found = true;
        }

        if (s1[0] == '@') {
            av->old_shields = true;
            found = true;
        }

        if (s1[0] == 'E') {
            av->logging_errors = true;
            found = true;
        }

        if (av->insanity < 0) {
            av->insanity = 0;
        }

        if (av->insanity > 15) {
            av->insanity = 15;
        }
        
        //CONOR DEBUG
        if (s1[0] == 'I') {
            av->show_executions = true;
            found = true;
            if (s1.length() > 1) {
                av->select_robot_e = true;
                av->r_e = atr2func::value(atr2func::rstr(s1, s1.length() - 1));
            }
        }
        
    } else if (s[0] == ';'){
        found = true;
    } else if ((av->num_robots < atr2var::max_robots) && !s.empty()){
        av->num_robots++;
        create_robot(av->num_robots - 1, s); //originally create_robot(av->num_robots, s);
        found = true;
        if (av->num_robots == atr2var::max_robots){
            std::cout << "Maximum number of robots reached." << "\n";
        }
    } else {
        prog_error(10,"");
    }

    if (!found){
        prog_error(8,s);
    }
}

void atr2::init(int argc, std::string argv[]) {
    int i;

    if(atr2var::debugging_compiler || atr2var::compile_by_line || atr2var::show_code) {
        std::cout << "!!! Warning !!! Compiler Debugging enabled !!!" << std::endl;
        //flushkey;
        //readkey;
    }
    av->step_mode = 0; //stepping disabled
    av->logging_errors = true;
    av->stats_mode = 0;
    av->insane_missiles = false;
    av->insanity = 0;
    av->delay_per_sec = 0;
    av->windoze = true;
    av->graphix = true;
    av->no_gfx = false;
    av->sound_on = true;
    av->timing = true;
    av->matches = 1;
    av->played = 0;
    av->old_shields = false;
    av->quit = false;
    av->compile_only = false;
    av->show_arcs = false;
    av->debug_info = false;
    av->show_cnotice = true;
    av->show_source = true;
    av->report = false;
    av->kill_count = 0;
    av->maxcode = atr2var::max_code;
    atr2func::make_tables();
    srand (time(NULL)); //randomize;
    av->num_robots = 0; //originally -1
    av->game_limit = 100000;
    av->game_cycle = 0;
    av->game_delay = atr2var::default_delay;
    av->time_slice = atr2var::default_slice;
    for (i = 0; i < atr2var::max_missiles; i++) {
        av->missile[i].a = 0;
        av->missile[i].source = -1;
        av->missile[i].x = 0;
        av->missile[i].y = 0;
        av->missile[i].lx = 0;
        av->missile[i].ly = 0;
        av->missile[i].mult = 1;
    }
    av->registered = false;
    av->reg_name = "Unregistered";
    av->reg_num = 65535; //FFFF in hex
    //check_registration();
    //textcolor(3);
    std::cout << std::endl << av->progname << " " << av->version << " " << av->cnotice1 << std::endl << av->cnotice2 << std::endl;
    //textcolor(7);
    if (!av->registered) {
        //textcolor(4);
        std::cout << "Unregistered version" << std::endl;
    } else {
        std::cout << "Registered to: " << av->reg_name << std::endl;
    }
    //textcolor(7);
    std::cout << std::endl;

    delete_compile_report();
    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            parse_param(atr2func::btrim(atr2func::ucase(argv[i])));
        }
    } else {
        prog_error(5, "");
    }
    av->temp_mode = av->step_mode;
    if (av->logging_errors) {
        for (i = 0; i < av->num_robots; i++) {
            av->robot[i].errorlog.open(filelib::base_name(av->robot[i].fn) + "-" + std::to_string(i + 1) + ".ERR");
        }
    }
    if (av->compile_only) {
        write_compile_report();
    }
    if (av->num_robots < 1) {
        prog_error(4, "");
    }
    if (!av->no_gfx) {
        //graph_mode(true);
    }

    //fix ups
    if (av->matches > 100000) {
        av->matches = 100000;
    }
    if (av->matches < 1) {
        av->matches = 1;
    }
    if (av->game_delay > 1000) {
        av->game_delay = 1000;
    }
    if (av->game_delay < 0) {
        av->game_delay = 0;
    }
    if (av->time_slice > 100) {
        av->time_slice = 100;
    }
    if (av->time_slice < 1) {
        av->time_slice = 1;
    }
    if (av->game_limit < 0) {
        av->game_limit = 0;
    }
    if (av->game_limit > 100000) {
        av->game_limit = 100000;
    }
    if (av->maxcode < 1) {
        av->maxcode = 1;
    }
    if (av->maxcode > atr2var::max_code) {
        av->maxcode = atr2var::max_code;
    }

    //just to avoid floating pointers
    /*for (i = av->num_robots + 1; i < (atr2var::max_robots + 2); i++) {
        av->robot[i] = av->robot[0];
    }*/
    //av->robot[-1] = av->robot[0];
    //av->robot[-2] = av->robot[0];

    /*if (!av->graphix) {
        std::cout << "Freemem: " << memavail << std::endl << std::endl;
    }*/
}

void atr2::draw_robot(int n) {
    int i, t;
    double xx, yy;

    if(!((n >= 0) && (n <= av->num_robots))) {
        return;
    }

    if (av->robot[n].x > 1000) {
        av->robot[n].x = 1000;
    }
    if (av->robot[n].y > 1000) {
        av->robot[n].y = 1000;
    }
    if (av->robot[n].x < 0) {
        av->robot[n].x = 0;
    }
    if (av->robot[n].y < 0) {
        av->robot[n].y = 0;
    }

    //set up for draw
    xx = av->robot[n].x * atr2var::screen_scale + atr2var::screen_x;
    yy = av->robot[n].y * atr2var::screen_scale + atr2var::screen_y;
    av->robot[n].hd = (av->robot[n].hd + 1024) & 255;
    av->robot[n].tx[1] = (int)round(xx + atr2func::sint[av->robot[n].hd] * 5);
    av->robot[n].ty[1] = (int)round(yy - atr2func::cost[av->robot[n].hd] * 5);
    av->robot[n].tx[2] = (int)round(xx + atr2func::sint[(av->robot[n].hd + 104) & 255] * atr2var::robot_scale);
    av->robot[n].ty[2] = (int)round(yy - atr2func::cost[(av->robot[n].hd + 104) & 255] * atr2var::robot_scale);
    av->robot[n].tx[3] = (int)round(xx + atr2func::sint[(av->robot[n].hd + 152) & 255] * atr2var::robot_scale);
    av->robot[n].ty[3] = (int)round(yy - atr2func::cost[(av->robot[n].hd + 152) & 255] * atr2var::robot_scale);
    t = (av->robot[n].hd + (av->robot[n].shift & 255) + 1024) & 255;
    av->robot[n].tx[4] = (int)round(xx);
    av->robot[n].ty[4] = (int)round(yy);
    av->robot[n].tx[5] = (int)round(xx + atr2func::sint[t] * atr2var::robot_scale * 0.8);
    av->robot[n].ty[5] = (int)round(yy - atr2func::cost[t] * atr2var::robot_scale * 0.8);
    av->robot[n].tx[6] = (int)round(xx + atr2func::sint[(t + av->robot[n].scanarc + 1024) & 255] * av->robot[n].scanrange * atr2var::screen_scale);
    av->robot[n].ty[6] = (int)round(yy - atr2func::cost[(t + av->robot[n].scanarc + 1024) & 255] * av->robot[n].scanrange * atr2var::screen_scale);
    av->robot[n].tx[7] = (int)round(xx + atr2func::sint[(t - av->robot[n].scanarc + 1024) & 255] * av->robot[n].scanrange * atr2var::screen_scale);
    av->robot[n].ty[7] = (int)round(yy - atr2func::cost[(t - av->robot[n].scanarc + 1024) & 255] * av->robot[n].scanrange * atr2var::screen_scale);
    av->robot[n].startarc = (int)round(((256 - ((t + av->robot[n].scanarc + 1024) & 255)) / 256 * 360) + 90);
    av->robot[n].endarc = (int)round(((256 - ((t - av->robot[n].scanarc + 1024) & 255)) / 256 * 360) + 90);

    //DEBUG_CONOR
    /*std::cout << "robot[" << n << "]: ";

    for (int dtemp = 1; dtemp <= 7; dtemp++) {
        std::cout << "tx[" << dtemp << "]=" << av->robot[n].tx[dtemp] << ", ";
        std::cout << "ty[" << dtemp << "]=" << av->robot[n].ty[dtemp] << ", ";
    }

    std::cout << std::endl;*/

    if (av->graphix) {
        //main_viewport;
        //erase
        //setcolor(0);
        /*if (av->robot[n].lshields) {
            p.drawEllipse(av->robot[n].ltx[4], av->robot[n].lty[4], atr2var::robot_scale, atr2var::robot_scale);
        }
        if (av->robot[n].arc_count < 0) {
            p.drawLine(av->robot[n].ltx[4], av->robot[n].lty[4], av->robot[n].ltx[6], av->robot[n].lty[6]);
            p.drawLine(av->robot[n].ltx[4], av->robot[n].lty[4], av->robot[n].ltx[7], av->robot[n].lty[7]);
            if (av->robot[n].scanrange < 1500) {
                p.drawArc(av->robot[n].ltx[4], av->robot[n].lty[4], round(av->robot[n].scanrange * screen_scale), round(av->robot[n].scanrange * screen_scale), av->robot[n].lstartarc, av->robot[n].lendarc);
            }
        }
        if (av->robot[n].sonar_count > 0) {
            p.drawEllipse(av->robot[n].ltx[4], av->robot[n].lty[4], round(atr2var::max_sonar * screen_scale), round(atr2var::max_sonar * screen_scale));
        }
        if (av->robot[n].armor > 0) { //only erase body if still alive, that way we leave a "corpse" when dead
            p.drawLine(av->robot[n].ltx[1], av->robot[n].lty[1], av->robot[n].ltx[2], av->robot[n].lty[2]);
            p.drawLine(av->robot[n].ltx[2], av->robot[n].lty[2], av->robot[n].ltx[3], av->robot[n].lty[3]);
            p.drawLine(av->robot[n].ltx[3], av->robot[n].lty[3], av->robot[n].ltx[1], av->robot[n].lty[1]);
            p.drawLine(av->robot[n].ltx[4], av->robot[n].lty[4], av->robot[n].ltx[5], av->robot[n].lty[5]);
        }*/

    }

    if (av->robot[n].armor > 0) {
        if (av->robot[n].arc_count > 0) {
            av->robot[n].arc_count--;
        }
        if (av->robot[n].sonar_count > 0) {
            av->robot[n].sonar_count--;
        }
        if (av->graphix) {
            //setcolor(robot_color(n) & 7);
            /*if (av->robot[n].shields_up) {
                p.drawEllipse(av->robot[n].tx[4], av->robot[n].ty[4], atr2var::robot_scale, atr2var::robot_scale);
            }
            //setcolor(robot_color(n));
            p.drawLine(av->robot[n].tx[1], av->robot[n].ty[1], av->robot[n].tx[2], av->robot[n].ty[2]);
            p.drawLine(av->robot[n].tx[2], av->robot[n].ty[2], av->robot[n].tx[3], av->robot[n].ty[3]);
            p.drawLine(av->robot[n].tx[3], av->robot[n].ty[3], av->robot[n].tx[1], av->robot[n].ty[1]);
            //setcolor(7);
            p.drawLine(av->robot[n].tx[4], av->robot[n].ty[4], av->robot[n].tx[5], av->robot[n].ty[5]);
            //setcolor(8);
            if ((av->show_arcs) && (av->robot[n].arc_count > 0)) {
                p.drawLine(av->robot[n].tx[4], av->robot[n].ty[4], av->robot[n].tx[6], av->robot[n].ty[6]);
                p.drawLine(av->robot[n].tx[4], av->robot[n].ty[4], av->robot[n].tx[7], av->robot[n].ty[7]);
                if (av->robot[n].scanrange < 1500) {
                    p.drawArc(av->robot[n].tx[4], av->robot[n].ty[4], round(av->robot[n].scanrange * screen_scale), round(av->robot[n].scanrange * screen_scale), av->robot[n].startarc, av->robot[n].endarc);
                }
            }
            if ((av->show_arcs) && (av->robot[n].sonar_count > 0)) {
                p.drawEllipse(av->robot[n].tx[4], av->robot[n].ty[4], round(atr2var::max_sonar * screen_scale), round(atr2var::max_sonar * screen_scale));
            }*/
        }

        if (av->graphix) {
            //atr2a->update_vars(n, 1);
            atr2a->update_robot(n);
            //atr2a->update();
            //loop->exec();
            atr2func::time_delay(av->game_delay);
        }

        av->robot[n].lx = av->robot[n].x;
        av->robot[n].ly = av->robot[n].y;
        av->robot[n].lhd = av->robot[n].hd;
        av->robot[n].lshift = av->robot[n].shift;
        av->robot[n].lshields = av->robot[n].shields_up;
        for (i = 1; i < atr2var::max_robot_lines; i++) {
            av->robot[n].ltx[i] = av->robot[n].tx[i];
            av->robot[n].lty[i] = av->robot[n].ty[i];
        }
        av->robot[n].lstartarc = av->robot[n].startarc;
        av->robot[n].lendarc = av->robot[n].endarc;
    }
}

int atr2::get_from_ram(int n, int i, int j) {
    int k, l;

    if ((i < 0) || (i > (atr2var::max_ram + 1) + (((atr2var::max_code + 1) << 3) - 1))) {
        k = 0;
        robot_error(n, 4, atr2func::cstr(i));
    } else {
        if (i < atr2var::max_ram)
        {
            k = av->robot[n].ram[i];
        } else {
            l = i - atr2var::max_ram - 1;
            k = av->robot[n].code[l >> 2].op[l & 3] ;
        }
    }

    return k;
}

int atr2::get_val(int n, int c, int o) {
    int i, j, k, l;
    k = 0;

    j = (av->robot[n].code[c].op[atr2var::max_op] >> (4*o)) & 15;
    i = av->robot[n].code[c].op[o];
    if ((j & 7) == 1) {
        k = get_from_ram(n, i, j);
    } else {
        k = i;
    }
    if ((j & 8) > 0)  {
        k = get_from_ram(n, k, j);
    }
    return k;
}

void atr2::put_val(int n, int c, int o, int v) {
    int i, j, k;

    k = 0;
    i = 0;
    j = 0;

    j = (av->robot[n].code[c].op[atr2var::max_op] >> (4 * o)) & 15;
    i = av->robot[n].code[c].op[o];
    if ((j & 7) == 1) {
        if ((i < 0) || (i > atr2var::max_ram)) {
            robot_error(n, 4, atr2func::cstr(i));
        } else {
            if ((j & 8) > 0) {
                i = av->robot[n].ram[i];
                if ((i < 0) || (i > atr2var::max_ram)) {
                    robot_error(n, 4, atr2func::cstr(i));
                } else {
                    av->robot[n].ram[i] = v;
                }
            } else {
                av->robot[n].ram[i] = v;
            }
        }
    } else {
        robot_error(n, 3, "");
    }
}

void atr2::push(int n, int v) {
    if ((av->robot[n].ram[71] >= atr2var::stack_base) && (av->robot[n].ram[71] < (atr2var::stack_base + atr2var::stack_size))) {
        av->robot[n].ram[av->robot[n].ram[71]] = v;
        av->robot[n].ram[71] = av->robot[n].ram[71] + 1;
    } else {
        robot_error(n, 1, atr2func::cstr(av->robot[n].ram[71]));
    }
}

int atr2::pop(int n) {
    int k;

    if ((av->robot[n].ram[71] > atr2var::stack_base) && (av->robot[n].ram[71] <= (atr2var::stack_base + atr2var::stack_size))) {
        av->robot[n].ram[71] = av->robot[n].ram[71] - 1;
        k = av->robot[n].ram[av->robot[n].ram[71]];
    } else {
        robot_error(n, 5, atr2func::cstr(av->robot[n].ram[71]));
    }

    return k;
}

int atr2::find_label(int n, int l, int m) {
    int i, j, k;

    k = -1;
    if (m == 3) {
        robot_error(n, 9, "");
    } else if (m == 4) {
        k = l ;
    } else {
        for (i = av->robot[n].plen; i >= 0; i--) {
            j = av->robot[n].code[i].op[atr2var::max_op] & 15;
            if ((j == 2) && (av->robot[n].code[i].op[0] == l)) {
                k = i;
            }
        }
    }
    return k;
}

void atr2::init_mine(int n, int detectrange, int size) {
    int i,j,k;
    k = -1;

    for (i = 0; i < atr2var::max_mines; i++){
        if (((av->robot[n].mine[i].x < 0) || (av->robot[n].mine[i].x > 1000) || (av->robot[n].mine[i].y < 0) || (av->robot[n].mine[i].y > 1000) || (av->robot[n].mine[i].yield <= 0)) && (k < 0)) {
            k = i;
        }
    }

    if (k >= 0){
        av->robot[n].mine[k].x = av->robot[n].x;
        av->robot[n].mine[k].y = av->robot[n].y;
        av->robot[n].mine[k].detect = detectrange;
        av->robot[n].mine[k].yield = size;
        av->robot[n].mine[k].detonate = false;
        //click;
    }
}

int atr2::count_missiles(){
    int i,k;
    k = 0;

    for (i = 0; i < atr2var::max_missiles; i++){
        if (av->missile[i].a > 0){
            k++;
        }
    }
    return k;
}

void atr2::init_missile(double xx, double yy, double xxv, double yyv, int dir, int s, int blast, bool ob){
    int i, j, k;
    double m;
    bool sound;

    k = -1;
    //click();
    for (i = atr2var::max_missiles; i >= 0; i--){
        if (av->missile[i].a == 0){
            k = i;
        }
    }
    if (k >= 0){
        av->missile[k].source = s;
        av->missile[k].x = xx;
        av->missile[k].lx = av->missile[k].x;
        av->missile[k].y = yy;
        av->missile[k].ly = av->missile[k].y;
        av->missile[k].rad = 0;
        av->missile[k].lrad = 0;

        if (ob){
            av->missile[k].mult = 1.25;
        } else {
            av->missile[k].mult = 1;
        }
        if (blast > 0){
            av->missile[k].max_rad = blast;
            av->missile[k].a = 2;
        } else {
            if ((s >= 0) && (s <= av->num_robots)){
                av->missile[k].mult = av->missile[k].mult * (av->robot[s].shotstrength);
            }
            m = av->missile[k].mult;
            if (ob){
                m = m + 0.25;
            }
            av->missile[k].mspd = atr2var::missile_spd * av->missile[k].mult;
            if (av->insane_missiles){
                av->missile[k].mspd = 100 + (50 * av->insanity) * av->missile[k].mult;
            }
            if ((s >= 0) && (s <= av->num_robots)){
                av->robot[s].heat = av->robot[s].heat + (int)round(20*m);
                av->robot[s].shots_fired++;
                av->robot[s].match_shots++;
            }
            av->missile[k].a = 1;
            av->missile[k].hd = dir;
            av->missile[k].max_rad = av->mis_radius;
            /*if (av->debug_info){
                do {
                    std::cout << "\n" << atr2func::zero_pad(av->game_cycle, 5) << " F " << s << ": hd=" << av->missile[k].hd << "           " << "\n";
                } while (!keypressed);
                atr2func::FlushKey(); //still have to port FlushKey
            }*/
        }
    }

    // (*The following was to see if teh missile array is big enough*)
    //  {else
    //   begin
    //    sound:=av->sound_on;
    //    av->sound_on:=true;
    //    chirp;
    //    av->sound_on:=sound;
    //   end;
    // setfillstyle(1,0);
    // setcolor(robot_color(k));
    // bar(5,5,37,12);
    // outtextxy(5,5,cstr(count_missiles));}
}

void atr2::damage(int n, int d, bool physical){

    int i, k, h, dd;
    double m;

    if ((n < 0) || (n > av->num_robots) || (av->robot[n].armor <= 0)){
        return;
    }
    if (av->robot[n].config.shield < 3){
        av->robot[n].shields_up = false;
    }

    h = 0;
    if (av->robot[n].shields_up && !physical){
        dd = d;
        if ((av->old_shields) && (av->robot[n].config.shield >= 3)){
            d = 0;
            h = 0;
        } else {
            switch(av->robot[n].config.shield){
                case 3:
                    d = (int)round(dd*2/3);
                    if (d < 1){
                        d = 1;
                        h = (int)round(dd*2/3);
                    }
                    break;
                case 4:
                    h = (int)trunc(dd/2);
                    d = dd - h;
                    break;
                case 5:
                    d = (int)round(dd*1/3);
                    if (d < 1){
                        d = 1;
                    }
                    h = (int)round(dd*1/3);
                    if (h < 1){
                        h = 1;
                    }
                    break;
            }
        }
    }
    if (d < 0) {
        d = 0;
    }
    /*if (av->debug_info) {
        do {
            std::cout << "\n" << atr2func::zero_pad(av->game_cycle,5) << " D " << n << ": " << av->robot[n].armor << "-" << d << "=" << av->robot[n].armor - d << "           " << std::endl;
        } while (!keypressed);
        atr2func::FlushKey(); //still have to port FlushKey
    }*/
    if (d > 0){
        d = (int)round(d*av->robot[n].damageadj);
        if (d < 1){
            d = 1;
        }
    }
    av->robot[n].armor = av->robot[n].armor - d;
    av->robot[n].heat = av->robot[n].heat + h;
    av->robot[n].last_damage = 0;
    if (av->robot[n].armor <= 0){
        av->robot[n].armor = 0;
        update_armor(n);
        av->robot[n].heat = 500;
        update_heat(n);
        av->robot[n].armor = 0;
        av->kill_count++;
        av->robot[n].deaths++;
        update_lives(n);
        //     if av->graphix and av->timing then time_delay(10);
        draw_robot(n);
        av->robot[n].heat = 0;
        update_heat(n);
        init_missile(av->robot[n].x, av->robot[n].y, 0, 0, 0, n, av->blast_circle, false);
        if (av->robot[n].overburn){
            m = 1.3;
        } else {
            m = 1;
        }
        for (i = 0; i < av->num_robots; i++){
            if ((i != n) && (av->robot[i].armor > 0)){
                k = (int)round(atr2func::distance(av->robot[n].x,av->robot[n].y,av->robot[i].x,av->robot[i].y));
                if (k < atr2var::blast_radius){
                    damage(i,(int)round(abs(atr2var::blast_radius - k) * m), false);
                }
            }
        }
    }
}

int atr2::scan(int n) {
    double r, d, acc;
    int dir, range, i, j, k, l, nn, xx, yy, sign;

    nn = -1;
    range = atr2var::maxint;
    if(!((n >= 0) && (n <= av->num_robots))) {
        return 0;
    }

    if (av->robot[n].scanarc < 0) {
        av->robot[n].scanarc = 0;
    }
    av->robot[n].accuracy = 0;
    nn = -1;
    dir = (av->robot[n].shift + av->robot[n].hd) & 255;
    if (av->debug_info) {
        std::cout << "<SCAN Arc=" << av->robot[n].scanarc << ", Dir=" << dir << ">" << std::endl;
    }
    for (i = 0; i < av->num_robots; i++) {
        if ((i != n) && (av->robot[i].armor > 0)) {
            j = atr2func::find_anglei(av->robot[n].x, av->robot[n].y, av->robot[i].x, av->robot[i].y);
            d = atr2func::distance(av->robot[n].x, av->robot[n].y, av->robot[i].x, av->robot[i].y);
            k = (int)round(d);

            if ((k < range) && (k <= av->robot[n].scanrange) && ((abs(j - dir) <= abs(av->robot[n].scanarc)) || (abs(j - dir) >= 256 - abs(av->robot[n].scanarc)))) {
                dir = (dir + 1024) & 255;
                xx = (int)round(atr2func::sint[dir] * d + av->robot[n].x);
                yy = (int)round(-(atr2func::cost[dir]) * d + av->robot[n].y);
                r = atr2func::distance(xx, yy, av->robot[i].x, av->robot[i].y);
                if (av->debug_info) {
                    std::cout << "SCAN HIT! Scan X,Y: " << round(xx) << "," << round(yy) << " Robot X,Y: "
                         << round(av->robot[i].x) << "," << round(av->robot[i].y) << " Dist=" << round(r) << std::endl;
                } //repeat until keypressed; flushkey;
                if ((av->robot[n].scanarc > 0) || (r < atr2var::hit_range - 2)) {
                    range = k;
                    av->robot[n].accuracy = 0;
                    if (av->robot[n].scanarc > 0) {
                        j = (j + 1024) & 255;
                        dir = (dir + 1024) & 255;
                        if (j < dir) {
                            sign = -1;
                        }
                        if (j > dir) {
                            sign = 1;
                        }
                        if ((j > 190) && (dir < 66)) {
                            dir = dir + 256;
                            sign = -1;
                        }
                        if ((dir > 190) && (j < 66)) {
                            j = j + 256;
                            sign = 1;
                        }
                        acc = abs(j - dir) / av->robot[n].scanarc * 2;
                        if (sign < 0) {
                            av->robot[n].accuracy = (int)-abs(round(acc));
                        } else {
                            av->robot[n].accuracy = (int)abs(round(acc));
                        }
                        if (av->robot[n].accuracy > 2) {
                            av->robot[n].accuracy = 2;
                        }
                        if (av->robot[n].accuracy < -2) {
                            av->robot[n].accuracy = -2;
                        }
                    }
                    nn = i;
                    if (av->debug_info) {
                        std::cout << "\n" << atr2func::zero_pad(av->game_cycle, 5) << " S " << n << ": nn=" << nn << ", range="
                             << range << ", acc=" << av->robot[n].accuracy << "           " << std::endl;
                    } //repeat until keypressed; flushkey;
                }
            }
        }
    }

    if ((nn >= 0) && (nn <= av->num_robots)) {
        av->robot[n].ram[5] = av->robot[nn].transponder;
        av->robot[n].ram[6] = (av->robot[nn].hd - (av->robot[n].hd + av->robot[n].shift) + 1024) & 255;
        av->robot[n].ram[7] = av->robot[nn].spd;
        av->robot[n].ram[13] = (int)round(av->robot[nn].speed * 100);
    }

    return range;
}

void atr2::com_transmit(int n, int chan, int data) {
    int i, j, k;

    for (i = 0; i < av->num_robots; i++) {
        if ((av->robot[n].armor > 0) && (i != n) && (av->robot[n].channel == chan)) {
            if ((av->robot[n].ram[10] < 0) || (av->robot[n].ram[10] > atr2var::max_queue)) {
                av->robot[n].ram[10] = 0;
            }
            if ((av->robot[n].ram[11] < 0) || (av->robot[n].ram[11] > atr2var::max_queue)) {
                av->robot[n].ram[11] = 0;
            }
            av->robot[n].ram[av->robot[n].ram[11] + atr2var::com_queue] = data;
            av->robot[n].ram[11]++;
            if (av->robot[n].ram[11] > atr2var::max_queue) {
                av->robot[n].ram[11] = 0;
            }
            if (av->robot[n].ram[11] == av->robot[n].ram[10]) {
                av->robot[n].ram[10]++;
            }
            if (av->robot[n].ram[10] > atr2var::max_queue) {
                av->robot[n].ram[10] = 0;
            }
        }
    }
}

int atr2::com_receive(int n) {
    int i, j, k;

    k = 0;
    if (av->robot[n].ram[10] != av->robot[n].ram[11]) {
        if ((av->robot[n].ram[10] < 0) || (av->robot[n].ram[10] > atr2var::max_queue)) {
            av->robot[n].ram[10] = 0;
        }
        if ((av->robot[n].ram[11] < 0) || (av->robot[n].ram[11] > atr2var::max_queue)) {
            av->robot[n].ram[11] = 0;
        }
        k = av->robot[n].ram[av->robot[n].ram[10] + atr2var::com_queue];
        av->robot[n].ram[10]++;
        if (av->robot[n].ram[10] > atr2var::max_queue) {
            av->robot[n].ram[10] = 0;
        }
    } else {
        robot_error(n, 12, "");
    }

    return k;
}

int atr2::in_port(int n, int p, int &time_used) {
    int i, j, k, l, nn, v;
    int16_t randv = 0;
    //int v;

    v = 0;
    switch(p) {
        case 1:
            v = av->robot[n].spd;
            break;
        case 2:
            v = av->robot[n].heat;
            break;
        case 3:
            v = av->robot[n].hd;
            break;
        case 4:
            v = av->robot[n].shift;
            break;
        case 5:
            v = (av->robot[n].shift + av->robot[n].hd) & 255;
            break;
        case 6:
            v = av->robot[n].armor;
            break;
        case 7:
            v = scan(n);
            time_used++;
            if (av->show_arcs) {
                av->robot[n].arc_count = 2;
            }
            break;
        case 8:
            v = av->robot[n].accuracy;
            time_used++;
            break;
        case 9:
            nn = -1;
            time_used = time_used + 3;
            k = atr2var::maxint;
            for (i = 0; i < av->num_robots; i++) {
                j = (int)round(atr2func::distance(av->robot[n].x, av->robot[n].y, av->robot[i].x, av->robot[i].y));
                if ((n != i) && (j < k) && (av->robot[i].armor > 0)) {
                    k = j;
                    nn = i;
                }
            }
            v = k;
            if ((nn >= 0) && (nn <= av->num_robots)) {
                av->robot[n].ram[5] = av->robot[nn].transponder;
            }
            break;
        case 10:
            randv = ((rand() % 65535) << 1) ^ (rand() % 65535);
            v = (int)randv;
            break;
        case 16:
            nn = -1;
            if (av->show_arcs) {
                av->robot[n].sonar_count = 2;
            }
            time_used = time_used + 40;
            l = -1;
            k = atr2var::maxint;
            nn = -1;
            for (i = 0; i < av->num_robots; i++) {
                j = (int)round(atr2func::distance(av->robot[n].x, av->robot[n].y, av->robot[i].x, av->robot[i].y));
                if ((n != i) && (j < k) && (j < atr2var::max_sonar) && (av->robot[i].armor > 0)) {
                    k = j;
                    l = i;
                    nn = i;
                }
            }
            if (l >= 0) {
                v = (int)round(atr2func::find_angle(av->robot[n].x, av->robot[n].y, av->robot[l].x, av->robot[l].y) / atr2var::pi * 128 + 1024 + (rand() % 65) - 32) & 255;
            } else {
                v = atr2var::minint;
            }
            if ((nn >= 0) && (nn <= av->num_robots)) {
                av->robot[n].ram[5] = av->robot[nn].transponder;
            }
            break;
        case 17:
            v = av->robot[n].scanarc;
            break;
        case 18:
            if (av->robot[n].overburn) {
                v = 1;
            } else {
                v = 0;
            }
            break;
        case 19:
            v = av->robot[n].transponder;
            break;
        case 20:
            v = av->robot[n].shutdown;
            break;
        case 21:
            v = av->robot[n].channel;
            break;
        case 22:
            v = av->robot[n].mines;
            break;
        case 23:
            if (av->robot[n].config.mines >= 0) {
                k = 0;
                for (i = 0; i < atr2var::max_mines; i++) {
                    if ((av->robot[n].mine[i].x >= 0) && (av->robot[n].mine[i].x <= 1000) && (av->robot[n].mine[i].y >= 0) && (av->robot[n].mine[i].y <= 1000) && (av->robot[n].mine[i].yield > 0)) {
                        k++;
                    }
                }
                v = k;
            } else {
                v = 0;
            }
            break;
        case 24:
            if (av->robot[n].config.shield > 0) {
                if (av->robot[n].shields_up) {
                    v = 1;
                } else {
                    v = 0;
                }
            } else {
                v = 0;
                av->robot[n].shields_up = false;
            }
            break;
        default:
            robot_error(n, 11, atr2func::cstr(p));
    }

    return (int)v;
}

void atr2::out_port(int n, int p, int v, int &time_used) {
    int i;

    switch(p) {
        case 11:
            av->robot[n].tspd = v;
            break;
        case 12:
            av->robot[n].shift = (av->robot[n].shift + v + 1024) & 255;
            break;
        case 13:
            av->robot[n].shift = (v + 1024) & 255;
            break;
        case 14:
            av->robot[n].thd = (av->robot[n].thd + v + 1024) & 255;
            break;
        case 15:
            time_used = time_used + 3;
            if (v > 4) {
                v = 4;
            }
            if (v < -4) {
                v = -4;
            }
            init_missile(av->robot[n].x, av->robot[n].y, av->robot[n].xv, av->robot[n].yv, (av->robot[n].hd + av->robot[n].shift + v) & 255, n, 0, av->robot[n].overburn);
            break;
        case 17:
            av->robot[n].scanarc = v;
            break;
        case 18:
            if (v == 0) {
                av->robot[n].overburn = false;
            } else {
                av->robot[n].overburn = true;
            }
            break;
        case 19:
            av->robot[n].transponder = v;
            break;
        case 20:
            av->robot[n].shutdown = v;
            break;
        case 21:
            av->robot[n].channel = v;
            break;
        case 22:
            if (av->robot[n].config.mines >= 0) {
                if (av->robot[n].mines > 0) {
                    init_mine(n, v, atr2var::mine_blast);
                    av->robot[n].mines--;
                } else {
                    robot_error(n, 14, "");
                }
            } else {
                robot_error(n, 13, "");
            }
            break;
        case 23:
            if (av->robot[n].config.mines >= 0) {
                for (i = 0; i < atr2var::max_mines; i++) {
                    av->robot[n].mine[i].detonate = true;
                }
            } else {
                robot_error(n, 13, "");
            }
            break;
        case 24:
            if (av->robot[n].config.shield >= 3) {
                if (v == 0) {
                    av->robot[n].shields_up = false;
                } else {
                    av->robot[n].shields_up = true;
                }
            } else {
                av->robot[n].shields_up = false;
                robot_error(n, 15, "");
            }
            break;
        default:
            robot_error(n, 11, atr2func::cstr(p));
    }
    if (av->robot[n].scanarc > 64) {
        av->robot[n].scanarc = 64;
    }
    if (av->robot[n].scanarc < 0) {
        av->robot[n].scanarc = 0;
    }
}

void atr2::call_int(int n, int int_num, int &time_used) {
    int i, j, k;

    switch(int_num) {
        case 0:
            damage(n, 1000, true);
            break;
        case 1:
            reset_software(n);
            time_used = 10;
            break;
        case 2:
            time_used = 5;
            av->robot[n].ram[69] = (int)round(av->robot[n].x);
            av->robot[n].ram[70] = (int)round(av->robot[n].y);
            break;
        case 3:
            time_used = 2;
            if (av->robot[n].ram[65] == 0) {
                av->robot[n].keepshift = false;
            } else {
                av->robot[n].keepshift = true;
            }
            av->robot[n].ram[70] = av->robot[n].shift & 255;
            break;
        case 4:
            if (av->robot[n].ram[65] == 0) {
                av->robot[n].overburn = false;
            } else {
                av->robot[n].overburn = true;
            }
            break;
        case 5:
            time_used = 2;
            av->robot[n].ram[70] = av->robot[n].transponder;
            break;
        case 6:
            time_used = 2;
            av->robot[n].ram[69] = av->game_cycle >> 16;
            av->robot[n].ram[70] = av->game_cycle & 65535;
            break;
        case 7:
            j = av->robot[n].ram[69];
            k = av->robot[n].ram[70];
            if (j < 0) {
                j = 0;
            }
            if (j > 1000) {
                j = 1000;
            }
            if (k < 0) {
                k = 0;
            }
            if (k > 1000) {
                k = 1000;
            }
            av->robot[n].ram[65] = (int)round(atr2func::find_angle(round(av->robot[n].x), round(av->robot[n].y), j, k) / atr2var::pi * 128 + 256) & 255;
            time_used = 32;
            break;
        case 8:
            av->robot[n].ram[70] = av->robot[n].ram[5];
            time_used = 1;
            break;
        case 9:
            av->robot[n].ram[69] = av->robot[n].ram[6];
            av->robot[n].ram[70] = av->robot[n].ram[7];
            time_used = 2;
            break;
        case 10:
            k = 0;
            for (i = 0; i < av->num_robots; i++) {
                if (av->robot[n].armor > 0) {
                    k++;
                }
            }
            av->robot[n].ram[68] = k;
            av->robot[n].ram[69] = av->played;
            av->robot[n].ram[70] = av->matches;
            time_used = 4;
            break;
        case 11:
            av->robot[n].ram[68] = (int)round(av->robot[n].speed * 100);
            av->robot[n].ram[69] = av->robot[n].last_damage;
            av->robot[n].ram[70] = av->robot[n].last_hit;
            time_used = 5;
            break;
        case 12:
            av->robot[n].ram[70] = av->robot[n].ram[8];
            time_used = 1;
            break;
        case 13:
            av->robot[n].ram[8] = 0;
            time_used = 1;
            break;
        case 14:
            com_transmit(n, av->robot[n].channel, av->robot[n].ram[65]);
            time_used = 1;
            break;
        case 15:
            if (av->robot[n].ram[10] != av->robot[n].ram[11]) {
                av->robot[n].ram[70] = com_receive(n);
            } else {
                robot_error(n, 12, "");
            }
            time_used = 1;
            break;
        case 16:
            if (av->robot[n].ram[11] >= av->robot[n].ram[10]) {
                av->robot[n].ram[70] = av->robot[n].ram[11] - av->robot[n].ram[10];
            } else {
                av->robot[n].ram[70] = atr2var::max_queue + 1 - av->robot[n].ram[10] + av->robot[n].ram[11];
            }
            time_used = 1;
            break;
        case 17:
            av->robot[n].ram[10] = 0;
            av->robot[n].ram[11] = 0;
            time_used = 1;
        case 18:
            av->robot[n].ram[68] = av->robot[n].kills;
            av->robot[n].ram[69] = av->robot[n].kills - av->robot[n].startkills;
            av->robot[n].ram[70] = av->robot[n].deaths;
            time_used = 3;
            break;
        case 19:
            av->robot[n].ram[9] = 0;
            av->robot[n].meters = 0;
            break;
        default:
            robot_error(n, 10, atr2func::cstr(int_num));
    }
}

void atr2::jump(int n, int o, bool &inc_ip) {
    int i, j, k, l, loc;

    loc = find_label(n, get_val(n, av->robot[n].ip, o), av->robot[n].code[av->robot[n].ip].op[atr2var::max_op] >> (o * 4));
    if ((loc >= 0) && (loc <= av->robot[n].plen)) {
        inc_ip = false;
        av->robot[n].ip = loc;
    } else {
        robot_error(n, 2, atr2func::cstr(loc));
    }
}

bool atr2::gameover() {
    int n, i, j, k, l;

    if ((av->game_cycle >= av->game_limit) && (av->game_limit > 0)) {
        return true;
        exit(0);
    }
    if ((av->game_cycle & 31) == 0) {
        k = 0;
        for (n = 0; n < av->num_robots; n++) {
            if (av->robot[n].armor > 0) {
                k++;
            }
        }
        if (k <= 1) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool atr2::invalid_microcode(int n, int ip) {
    bool invalid;
    int i, j, k;

    invalid = false;
    for (i = 0; i <= 2; i++) {
        k = (av->robot[n].code[ip].op[atr2var::max_op] >> (i << 2)) & 7;
        if ((k != 1) && (k != 2) && (k != 3) && (k != 4)) {
            //invalid = true;
        }
    }
    return invalid;
}

void atr2::execute_instruction(int n) {
    int i, j, k, time_used, loc;
    bool inc_ip;
    char c;

    av->robot[n].ram[0] = av->robot[n].tspd;
    av->robot[n].ram[1] = av->robot[n].thd;
    av->robot[n].ram[2] = av->robot[n].shift;
    av->robot[n].ram[3] = av->robot[n].accuracy;

    time_used = 1;
    inc_ip = true;
    loc = 0;
    if ((av->robot[n].ip > av->robot[n].plen) || (av->robot[n].ip < 0)) {
        av->robot[n].ip = 0;
    }
    if (invalid_microcode(n, av->robot[n].ip)) {
        time_used = 1;
        robot_error(n, 16, atr2func::hex(av->robot[n].code[av->robot[n].ip].op[atr2var::max_op]));
    }

    if ((av->graphix) && (av->step_mode > 0) && (n == 0)) {
        //av->graphix stuff
    }
    
    //DEBUG CONOR
    if (av->show_executions) {
        if (((av->select_robot_e) && (av->r_e == n)) || (!av->select_robot_e)) {
            std::cout << "Robot #" << n << " (" << av->robot[n].fn << ") executing line " << av->robot[n].ip << ", op=" << get_val(n, av->robot[n].ip, 0) << ", "
                      << mnemonic(get_val(n, av->robot[n].ip, 0), 0) << " " << av->robot[n].code[av->robot[n].ip].op[1] << " " << av->robot[n].code[av->robot[n].ip].op[2] << std::endl;
        }
    }
    
    if(((av->robot[n].code[av->robot[n].ip].op[atr2var::max_op] & 7) != 0) && ((av->robot[n].code[av->robot[n].ip].op[atr2var::max_op] & 7) != 1)) {
        time_used = 0;
    } else {
        //DEBUG CONOR
        //std::cout << "   Robot #" << n << " executing instruction #" << get_val(n, av->robot[n].ip, 0) << ", "
        //<< mnemonic(get_val(n, av->robot[n].ip, 0), 0) << std::endl;
        switch (get_val(n, av->robot[n].ip, 0)) {
            case 0: //NOP
                av->executed++;
                break;
            case 1: //ADD
                put_val(n, av->robot[n].ip, 1, get_val(n, av->robot[n].ip, 1) + get_val(n, av->robot[n].ip, 2));
                av->executed++;
                break;
            case 2: //SUB
                put_val(n, av->robot[n].ip, 1, get_val(n, av->robot[n].ip, 1) - get_val(n, av->robot[n].ip, 2));
                av->executed++;
                break;
            case 3: //OR
                put_val(n, av->robot[n].ip, 1, get_val(n, av->robot[n].ip, 1) | get_val(n, av->robot[n].ip, 2));
                av->executed++;
                break;
            case 4: //AND
                put_val(n, av->robot[n].ip, 1, get_val(n, av->robot[n].ip, 1) & get_val(n, av->robot[n].ip, 2));
                av->executed++;
                break;
            case 5: //XOR
                put_val(n, av->robot[n].ip, 1, get_val(n, av->robot[n].ip, 1) ^ get_val(n, av->robot[n].ip, 2));
                av->executed++;
                break;
            case 6: //NOT
                put_val(n, av->robot[n].ip, 1, !get_val(n, av->robot[n].ip, 1));
                av->executed++;
                break;
            case 7: //MPY
                put_val(n, av->robot[n].ip, 1, get_val(n, av->robot[n].ip, 1) * get_val(n, av->robot[n].ip, 2));
                time_used = 10;
                av->executed++;
                break;
            case 8: //DIV
                j = get_val(n, av->robot[n].ip, 2);
                if (j != 0) {
                    put_val(n, av->robot[n].ip, 1, (int) (get_val(n, av->robot[n].ip, 1) / j));
                } else {
                    robot_error(n, 8, "");
                }
                time_used = 10;
                av->executed++;
                break;
            case 9: //MOD
                j = get_val(n, av->robot[n].ip, 2);
                if (j != 0) {
                    put_val(n, av->robot[n].ip, 1, get_val(n, av->robot[n].ip, 1) % j);
                } else {
                    robot_error(n, 8, "");
                }
                time_used = 10;
                av->executed++;
                break;
            case 10: //RET
                av->robot[n].ip = pop(n);
                if ((av->robot[n].ip < 0) || (av->robot[n].ip > av->robot[n].plen)) {
                    robot_error(n, 7, atr2func::cstr(av->robot[n].ip));
                }
                av->executed++;
                break;
            case 11: //GSB,CALL
                loc = find_label(n, get_val(n, av->robot[n].ip, 1), av->robot[n].code[av->robot[n].ip].op[atr2var::max_op] >> (1 * 4));
                if (loc >= 0) {
                    push(n, av->robot[n].ip);
                    inc_ip = false;
                    av->robot[n].ip = loc;
                } else {
                    robot_error(n, 2, atr2func::cstr(get_val(n, av->robot[n].ip, 1)));
                }
                av->executed++;
                break;
            case 12: //JMP
                jump(n, 1, inc_ip);
                av->executed++;
                break;
            case 13: //JLS,JB
                if ((av->robot[n].ram[64] & 2) > 0) {
                    jump(n, 1, inc_ip);
                }
                time_used = 0;
                av->executed++;
                break;
            case 14: //JGR,JA
                if ((av->robot[n].ram[64] & 4) > 0) {
                    jump(n, 1, inc_ip);
                }
                time_used = 0;
                av->executed++;
                break;
            case 15: //JNE
                if ((av->robot[n].ram[64] & 1) == 0) {
                    jump(n, 1, inc_ip);
                }
                time_used = 0;
                av->executed++;
                break;
            case 16: //JEQ,JE
                if ((av->robot[n].ram[64] & 1) > 0) {
                    jump(n, 1, inc_ip);
                }
                time_used = 0;
                av->executed++;
                break;
            case 17: //SWAP, XCHG
                av->robot[n].ram[4] = get_val(n, av->robot[n].ip, 1);
                put_val(n, av->robot[n].ip, 1, get_val(n, av->robot[n].ip, 2));
                put_val(n, av->robot[n].ip, 2, av->robot[n].ram[4]);
                time_used = 3;
                av->executed++;
                break;
            case 18: //DO
                av->robot[n].ram[67] = get_val(n, av->robot[n].ip, 1);
                av->executed++;
                break;
            case 19: //LOOP
                av->robot[n].ram[67]--;
                if (av->robot[n].ram[67] > 0) {
                    jump(n, 1, inc_ip);
                }
                av->executed++;
                break;
            case 20: //CMP
                k = get_val(n, av->robot[n].ip, 1) - get_val(n, av->robot[n].ip, 2);
                av->robot[n].ram[64] = av->robot[n].ram[64] & 65520;
                if (k == 0) {
                    av->robot[n].ram[64] = av->robot[n].ram[64] | 1;
                }
                if (k < 0) {
                    av->robot[n].ram[64] = av->robot[n].ram[64] | 2;
                }
                if (k > 0) {
                    av->robot[n].ram[64] = av->robot[n].ram[64] | 4;
                }
                if ((get_val(n, av->robot[n].ip, 2) == 0) && (k == 0)) {
                    av->robot[n].ram[64] = av->robot[n].ram[64] | 8;
                }
                av->executed++;
                break;
            case 21: //TEST
                k = get_val(n, av->robot[n].ip, 1) & get_val(n, av->robot[n].ip, 2);
                av->robot[n].ram[64] = av->robot[n].ram[64] & 65520;
                if (k == get_val(n, av->robot[n].ip, 2)) {
                    av->robot[n].ram[64] = av->robot[n].ram[64] | 1;
                }
                if (k == 0) {
                    av->robot[n].ram[64] = av->robot[n].ram[64] | 8;
                }
                av->executed++;
                break;
            case 22: //MOV, SET
                put_val(n, av->robot[n].ip, 1, get_val(n, av->robot[n].ip, 2));
                av->executed++;
                break;
            case 23: //LOC
                put_val(n, av->robot[n].ip, 1, av->robot[n].code[av->robot[n].ip].op[2]);
                time_used = 2;
                av->executed++;
                break;
            case 24: //GET
                k = get_val(n, av->robot[n].ip, 2);
                if ((k >= 0) && (k <= atr2var::max_ram)) {
                    put_val(n, av->robot[n].ip, 1, av->robot[n].ram[k]);
                } else if ((k > atr2var::max_ram) && (k <= ((atr2var::max_ram + 1) + (((atr2var::max_code + 1) << 3) - 1)))) {
                    j = k - atr2var::max_ram - 1;
                    put_val(n, av->robot[n].ip, 1, av->robot[n].code[j >> 2].op[j & 3]);
                } else {
                    robot_error(n, 4, atr2func::cstr(k));
                }
                time_used = 2;
                av->executed++;
                break;
            case 25: //PUT
                k = get_val(n, av->robot[n].ip, 2);
                if ((k >= 0) && (k <= atr2var::max_ram)) {
                    av->robot[n].ram[k] = get_val(n, av->robot[n].ip, 1);
                } else {
                    robot_error(n, 4, atr2func::cstr(k));
                }
                time_used = 2;
                av->executed++;
                break;
            case 26: //INT
                call_int(n, get_val(n, av->robot[n].ip, 1), time_used);
                av->executed++;
                break;
            case 27: //IPO,IN
                time_used = 4;
                put_val(n, av->robot[n].ip, 2, (int)in_port(n, get_val(n, av->robot[n].ip, 1), time_used));
                av->executed++;
                break;
            case 28: //OPO,OUT
                time_used = 4;
                out_port(n, get_val(n, av->robot[n].ip, 1), get_val(n, av->robot[n].ip, 2), time_used);
                av->executed++;
                break;
            case 29: //DEL,DELAY
                time_used = get_val(n, av->robot[n].ip, 1);
                av->executed++;
                break;
            case 30: //PUSH
                push(n, get_val(n, av->robot[n].ip, 1));
                av->executed++;
                break;
            case 31: //POP
                put_val(n, av->robot[n].ip, 1, pop(n));
                av->executed++;
                break;
            case 32: //ERR
                robot_error(n, get_val(n, av->robot[n].ip, 1), "");
                time_used = 0;
                av->executed++;
                break;
            case 33: //INC
                put_val(n, av->robot[n].ip, 1, get_val(n, av->robot[n].ip, 1) + 1);
                av->executed++;
                break;
            case 34: //DEC
                put_val(n, av->robot[n].ip, 1, get_val(n, av->robot[n].ip, 1) - 1);
                av->executed++;
                break;
            case 35: //SHL
                put_val(n, av->robot[n].ip, 1, get_val(n, av->robot[n].ip, 1) << get_val(n, av->robot[n].ip, 2));
                av->executed++;
                break;
            case 36: //SHR
                put_val(n, av->robot[n].ip, 1, get_val(n, av->robot[n].ip, 1) >> get_val(n, av->robot[n].ip, 2));
                av->executed++;
                break;
            case 37: //ROL
                put_val(n, av->robot[n].ip, 1, atr2func::rol(get_val(n, av->robot[n].ip, 1), get_val(n, av->robot[n].ip, 2)));
                av->executed++;
                break;
            case 38: //ROR
                put_val(n, av->robot[n].ip, 1, atr2func::ror(get_val(n, av->robot[n].ip, 1), get_val(n, av->robot[n].ip, 2)));
                av->executed++;
                break;
            case 39: //JZ
                time_used = 0;
                if ((av->robot[n].ram[64] & 8) > 0) {
                    jump(n, 1, inc_ip);
                }
                av->executed++;
                break;
            case 40: //JNZ
                time_used = 0;
                if ((av->robot[n].ram[64] & 8) == 0) {
                    jump(n, 1, inc_ip);
                }
                av->executed++;
                break;
            case 41: //JAE,JGE
                if (((av->robot[n].ram[64] & 1) > 0) || ((av->robot[n].ram[64] & 4) > 0)) {
                    jump(n, 1, inc_ip);
                }
                time_used = 0;
                av->executed++;
                break;
            case 42: //JBE,JLE
                if (((av->robot[n].ram[64] & 1) > 0) || ((av->robot[n].ram[64] & 2) > 0)) {
                    jump(n, 1, inc_ip);
                }
                time_used = 0;
                av->executed++;
                break;
            case 43: //SAL
                put_val(n, av->robot[n].ip, 1, atr2func::sal(get_val(n, av->robot[n].ip, 1), get_val(n, av->robot[n].ip, 2)));
                av->executed++;
                break;
            case 44: //SAR
                put_val(n, av->robot[n].ip, 1, atr2func::sar(get_val(n, av->robot[n].ip, 1), get_val(n, av->robot[n].ip, 2)));
                av->executed++;
                break;
            case 45: //NEG
                put_val(n, av->robot[n].ip, 1, 0 - get_val(n, av->robot[n].ip, 1));
                av->executed++;
                break;
            case 46: //JTL
                loc = get_val(n, av->robot[n].ip, 1);
                if ((loc >= 0) && (loc <= av->robot[n].plen)) {
                    inc_ip = false;
                    av->robot[n].ip = loc;
                } else {
                    robot_error(n, 2, atr2func::cstr(loc));
                }
                break;
            default:
                robot_error(n, 6, "");
                std::cout << "Error executing instruction!" << std::endl;
        }
    }

    av->robot[n].delay_left = av->robot[n].delay_left + time_used;
    if (inc_ip) {
        av->robot[n].ip++;
    }
    if ((av->graphix) && (n == 0) && (av->step_mode > 0)) {
        //update_debug_window();
    }
}

void atr2::do_robot(int n) {
    int i, j, k, l, tthd;
    double heat_mult, ttx, tty;

    if ((n < 0) || (n > av->num_robots)) {
        return;
    }

    if (av->robot[n].armor <= 0) {
        return;
    }

    //time slice
    av->robot[n].time_left = av->time_slice;
    if ((av->robot[n].time_left > av->robot[n].robot_time_limit) && (av->robot[n].robot_time_limit > 0)) {
        av->robot[n].time_left = av->robot[n].robot_time_limit;
    }
    if ((av->robot[n].time_left > av->robot[n].max_time) && (av->robot[n].max_time > 0)) {
        av->robot[n].time_left = av->robot[n].max_time;
    }
    av->executed = 0;

    //execute timeslice
    while ((av->robot[n].time_left > 0) && (!av->robot[n].cooling) && (av->executed < (20 + av->time_slice))) {
        if (av->robot[n].delay_left < 0) {
            av->robot[n].delay_left = 0;
        }
        if (av->robot[n].delay_left > 0) {
            av->robot[n].delay_left--;
            av->robot[n].time_left--;
        }
        if ((av->robot[n].time_left >= 0) && (av->robot[n].delay_left == 0)) {
            execute_instruction(n);
        }
        if (av->robot[n].heat >= av->robot[n].shutdown) {
            av->robot[n].cooling = true;
            av->robot[n].shields_up = false;
        }
        if (av->robot[n].heat >= 500) {
            damage(n, 1000, true);
        }
    }

    //fix up variables
    av->robot[n].thd = (av->robot[n].thd + 1024) & 255;
    av->robot[n].hd = (av->robot[n].hd + 1024) & 255;
    av->robot[n].shift = (av->robot[n].shift + 1024) & 255;
    if (av->robot[n].tspd < -75) {
        av->robot[n].tspd = -75;
    }
    if (av->robot[n].tspd > 100) {
        av->robot[n].tspd = 100;
    }
    if (av->robot[n].spd < -75) {
        av->robot[n].spd = -75;
    }
    if (av->robot[n].spd > 100) {
        av->robot[n].spd = 100;
    }
    if (av->robot[n].heat < 0) {
        av->robot[n].heat = 0;
    }
    if (av->robot[n].last_damage < atr2var::maxint) {
        av->robot[n].last_damage++;
    }
    if (av->robot[n].last_hit < atr2var::maxint) {
        av->robot[n].last_hit;
    }

    //update heat
    if (av->robot[n].shields_up && ((av->game_cycle & 3) == 0)) {
        av->robot[n].heat++;
    }
    if (!av->robot[n].shields_up) {
        if (av->robot[n].heat > 0) {
            switch(av->robot[n].config.heatsinks) {
                case 5:
                    if ((av->game_cycle & 1) == 0) {
                        av->robot[n].heat--;
                    }
                    break;
                case 4:
                    if ((av->game_cycle % 3) == 0) {
                        av->robot[n].heat--;
                    }
                    break;
                case 3:
                    if ((av->game_cycle & 3) == 0) {
                        av->robot[n].heat--;
                    }
                    break;
                case 2:
                    if ((av->game_cycle & 7) == 0) {
                        av->robot[n].heat--;
                    }
                    break;
                case 1:
                    break;
                default:
                    if ((av->game_cycle & 3) == 0) {
                        av->robot[n].heat++;
                    }
            }
        }
        if ((av->robot[n].overburn) && ((av->game_cycle % 3) == 0)) {
            av->robot[n].heat++;
        }
        if (av->robot[n].heat > 0) {
            av->robot[n].heat--;
        }
        if ((av->robot[n].heat > 0) && ((av->game_cycle & 7) == 0) && (abs(av->robot[n].tspd) <= 25)) {
            av->robot[n].heat--;
        }
        if ((av->robot[n].heat <= (av->robot[n].shutdown - 50)) || (av->robot[n].heat <= 0)) {
            av->robot[n].cooling = false;
        }
    }
    if (av->robot[n].cooling) {
        av->robot[n].tspd = 0;
    }
    heat_mult = 1;
    switch(av->robot[n].heat) {
        case 80 ... 99:
            heat_mult = 0.98;
            break;
        case 100 ... 149:
            heat_mult = 0.95;
            break;
        case 150 ... 199:
            heat_mult = 0.85;
            break;
        case 200 ... 249:
            heat_mult = 0.75;
            break;
        case 250 ... atr2var::maxint:
            heat_mult = 0.50;
            break;
    }
    if (av->robot[n].overburn) {
        heat_mult = heat_mult * 1.30;
    }
    if ((av->robot[n].heat >= 475) && ((av->game_cycle & 3) == 0)) {
        damage(n, 1, true);
    } else if ((av->robot[n].heat >= 450) && ((av->game_cycle & 7) == 0)) {
        damage(n, 1, true);
    } else if ((av->robot[n].heat >= 400) && ((av->game_cycle & 15) == 0)) {
        damage(n, 1, true);
    } else if ((av->robot[n].heat >= 350) && ((av->game_cycle & 31) == 0)) {
        damage(n, 1, true);
    } else if ((av->robot[n].heat >= 300) && ((av->game_cycle & 63) == 0)) {
        damage(n, 1, true);
    }

    //update robot in physical world
    //atr2var::acceleration
    if (abs(av->robot[n].spd - av->robot[n].tspd) <= atr2var::acceleration) {
        av->robot[n].spd = av->robot[n].tspd;
    } else {
        if (av->robot[n].tspd > av->robot[n].spd) {
            av->robot[n].spd = av->robot[n].spd + atr2var::acceleration;
        } else {
            av->robot[n].spd = av->robot[n].spd - atr2var::acceleration;
        }
    }

    //turning
    tthd = av->robot[n].hd + av->robot[n].shift;
    if ((abs(av->robot[n].hd - av->robot[n].thd) <= atr2var::turn_rate) || (abs(av->robot[n].hd - av->robot[n].thd >= (256-atr2var::turn_rate)))) {
        av->robot[n].hd = av->robot[n].thd;
    } else if (av->robot[n].hd != av->robot[n].thd) {
        k = 0;
        if (((av->robot[n].thd > av->robot[n].hd) && (abs(av->robot[n].hd - av->robot[n].thd) <= 128)) || ((av->robot[n].thd < av->robot[n].hd) && (abs(av->robot[n].hd - av->robot[n].thd) >= 128))) {
            k = 1;
        }
        if (k == 1) {
            av->robot[n].hd = (av->robot[n].hd + atr2var::turn_rate) & 255;
        } else {
            av->robot[n].hd = (av->robot[n].hd + 256 - atr2var::turn_rate) & 255;
        }
    }
    av->robot[n].hd = av->robot[n].hd & 255;
    if (av->robot[n].keepshift) {
        av->robot[n].shift = (tthd - av->robot[n].hd + 1024) & 255;
    }

    //moving
    av->robot[n].speed = av->robot[n].spd / 100 * (atr2var::max_vel * heat_mult * av->robot[n].speedadj);
    av->robot[n].xv = atr2func::sint[av->robot[n].hd] * av->robot[n].speed;
    av->robot[n].yv = -(atr2func::cost[av->robot[n].hd]) * av->robot[n].speed;
    if ((av->robot[n].hd == 0) || (av->robot[n].hd == 128)) {
        av->robot[n].xv = 0;
    }
    if ((av->robot[n].hd == 64) || (av->robot[n].hd == 192)) {
        av->robot[n].yv = 0;
    }
    if (av->robot[n].xv != 0) {
        ttx = av->robot[n].x + av->robot[n].xv;
    } else {
        ttx = av->robot[n].x;
    }
    if (av->robot[n].yv != 0) {
        tty = av->robot[n].y + av->robot[n].yv;
    } else {
        tty = av->robot[n].y;
    }
    if (ttx < 0) {
        ttx = 0;
    }
    if (tty < 0) {
        tty = 0;
    }
    if (ttx > 1000) {
        ttx = 1000;
    }
    if (tty > 1000) {
        tty = 1000;
    }
    av->robot[n].meters = av->robot[n].meters + atr2func::distance(av->robot[n].x, av->robot[n].y, ttx, tty);
    if (av->robot[n].meters >= atr2var::maxint) {
        av->robot[n].meters = av->robot[n].meters - atr2var::maxint;
    }
    av->robot[n].ram[9] = (int)trunc(av->robot[n].meters);
    av->robot[n].x = ttx;
    av->robot[n].y = tty;

    //draw robot
    if (av->robot[n].armor < 0) {
        av->robot[n].armor = 0;
    }
    if (av->robot[n].heat < 0) {
        av->robot[n].heat = 0;
    }
    if (av->graphix) {
        if (av->robot[n].armor != av->robot[n].larmor) {
            update_armor(n);
        }
        if ((int)(av->robot[n].heat / 5) != (int)(av->robot[n].lheat / 5)) {
            update_heat(n);
        }
        draw_robot(n);
    }
    av->robot[n].lheat = av->robot[n].heat;
    av->robot[n].larmor = av->robot[n].armor;

    //Cycle complete, inc counter
    av->robot[n].cycles_lived++;
}

void atr2::do_mine(int n, int m) {

}

void atr2::do_missile(int n) {
    double llx, lly, r, d, dir, xv, yv;
    int i, j, k, l, xx, yy, tx, ty, dd, dam;
    bool source_alive;

    if(av->missile[n].a == 0) {
        return;
    } else {
        if (av->missile[n].a == 1) {
            //Look for collision w/ wall
            if ((av->missile[n].x <- 20) || (av->missile[n].x > 1020) || (av->missile[n].y <- 20) || (av->missile[n].y > 1020)) {
                av->missile[n].a = 0;
            }

            //move missile
            llx = av->missile[n].lx;
            lly = av->missile[n].ly;
            av->missile[n].lx = av->missile[n].x;
            av->missile[n].ly = av->missile[n].y;
            if (av->missile[n].a > 0) {
                av->missile[n].hd = (av->missile[n].hd + 256) & 255;
                xv = atr2func::sint[av->missile[n].hd] * av->missile[n].mspd;
                yv = -(atr2func::cost[av->missile[n].hd]) * av->missile[n].mspd;
                av->missile[n].x = av->missile[n].x + xv;
                av->missile[n].y = av->missile[n].y + yv;
            }

            //look for hit on a robot
            k = -1;
            l = atr2var::maxint;
            for (i = 0; i < av->num_robots; i++) {
                if ((av->robot[i].armor > 0) && (i != av->missile[n].source)) {
                    d = atr2func::distance(av->missile[n].lx, av->missile[n].ly, av->robot[i].x, av->robot[i].y);
                    av->missile[n].hd = av->missile[n].hd & 255;
                    xx = (int)round(atr2func::sint[av->missile[n].hd] * d + av->missile[n].lx);
                    yy = (int)round(-(atr2func::cost[av->missile[n].hd]) * d + av->missile[n].ly);
                    r = atr2func::distance(xx, yy, av->robot[i].x, av->robot[i].y);
                    if ((d <= av->missile[n].mspd) && (r < atr2var::hit_range) && (round(d) <= l)) {
                        k = i;
                        l = (int)round(d);
                        dd = (int)round(r);
                        tx = xx;
                        ty = yy;
                    }
                }
            }
            if (k >= 0) { //hit a robot!
                av->missile[n].x = tx;
                av->missile[n].y = ty;
                av->missile[n].a = 2;
                av->missile[n].rad = 0;
                av->missile[n].lrad = 0;
                if ((av->missile[n].source >= 0) && (av->missile[n].source <= av->num_robots)) {
                    av->robot[av->missile[n].source].last_hit = 0;
                    av->robot[av->missile[n].source].hits++;
                }
                for (i = 0; i < av->num_robots; i++) {
                    dd = (int)round(atr2func::distance(av->missile[n].x, av->missile[n].y, av->robot[i].x, av->robot[i].y));
                    if (dd <= atr2var::hit_range) {
                        dam = (int)round(abs(atr2var::hit_range - dd) * av->missile[n].mult);
                        if (dam <= 0) {
                            dam = 1;
                        }
                        av->kill_count = 0;
                        if (av->robot[av->missile[n].source].armor > 0) {
                            source_alive = true;
                        } else {
                            source_alive = false;
                        }
                        damage(i, dam, false);
                        if (((av->missile[n].source >= 0) && (av->missile[n].source <= av->num_robots)) && (i != av->missile[n].source)) {
                            av->robot[av->missile[n].source].damage_total = av->robot[av->missile[n].source].damage_total + dam;
                        }
                        if ((av->kill_count > 0) && (source_alive) && (av->robot[av->missile[n].source].armor <= 0)) {
                            av->kill_count = av->kill_count - 1;
                        }
                        if (av->kill_count > 0) {
                            av->robot[av->missile[n].source].kills = av->robot[av->missile[n].source].kills + av->kill_count;
                            update_lives(av->missile[n].source);
                        }
                    }
                }
            }

            //draw missile
            if (av->graphix) {
                //atr2a->update_missile(llx, lly);
                //atr2a->update_vars(n, 2);
                atr2a->update_missile(n);
                //atr2a->update();
                //loop->exec();
                atr2func::time_delay(av->game_delay);
            }
        }

        if (av->missile[n].a == 2) {
            av->missile[n].lrad = av->missile[n].rad;
            av->missile[n].rad++;
            if (av->missile[n].rad > av->missile[n].max_rad) {
                av->missile[n].a = 0;
            }
            if (av->graphix) {
                //atr2a->update_vars(n, 2);
                atr2a->update_missile(n);
                //atr2a->update();
                //loop->exec();
                atr2func::time_delay(av->game_delay);
            }
        }
    }
}

std::string atr2::victor_string(int k, int n) {
    std::string s;

    s.clear();
    if (k == 1) {
        s = "Robot #" + atr2func::cstr(n+1) + " (" + av->robot[n].fn + ") wins!";
    }
    if (k == 0) {
        s = "Simultaneous destruction, match is a tie.";
    }
    if (k > 1) {
        s = "No clear victor, match is a tie.";
    }

    return s;
}

void atr2::show_statistics() {
    int i, j, k, n, sx, sy;

    if (!av->windoze) {
        return;
    }
    if (!av->graphix) {

    } else {
        //textcolor(15);
        std::cout << std::endl << atr2func::space(79) << std::endl;
        std::cout << "Match " << av->played << "/" << av->matches << " results:" << std::endl << std::endl;
        std::cout << "Robot            Scored   Wins  Matches  Armor  Kills  Deaths    Shots" << std::endl;
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        n = -1;
        k = 0;
        for (i = 0; i < av->num_robots; i++) {
            if ((av->robot[i].armor > 0) || (av->robot[i].won)) {
                k++;
                n = i;
            }
        }
        for (i = 0; i < av->num_robots; i++) {
            //textcolor(robotcolor(i));
            if ((k == 1) && (n == i)) {
                j = 1;
            } else {
                j = 0;
            }
            std::cout << atr2func::addfront(atr2func::cstr(i+1), 2) << " - " << atr2func::addrear(av->robot[i].fn, 15) << atr2func::cstr(j)
                 << atr2func::addfront(atr2func::cstr(av->robot[i].wins), 8) << atr2func::addfront(atr2func::cstr(av->robot[i].trials), 8)
                 << atr2func::addfront(atr2func::cstr(av->robot[i].armor) + "%", 9) << atr2func::addfront(atr2func::cstr(av->robot[i].kills), 7)
                 << atr2func::addfront(atr2func::cstr(av->robot[i].deaths), 8) << atr2func::addfront(atr2func::cstr(av->robot[i].match_shots), 9)
                 << std::endl;
        }
        //textcolor(15);
        std::cout << std::endl;
        std::cout << victor_string(k, n);
        std::cout << std::endl;
    }
}

void atr2::score_robots() {
    int n, i, j, k, l;

    k = 0;
    n = -1;

    for (i = 0; i < av->num_robots; i++) {
        av->robot[i].trials++;
        if (av->robot[i].armor > 0) {
            k++;
            n = i;
        }
    }

    if ((k == 1) && (n >= 0)) {
        av->robot[n].wins++;
        av->robot[n].won = true;
    }
}

void atr2::init_bout() {
    int i, j, k;

    av->game_cycle = 0;
    for (i = 0; i < atr2var::max_missiles; i++) {
        av->missile[i].a = 0;
        av->missile[i].source = -1;
        av->missile[i].x = 0;
        av->missile[i].y = 0;
        av->missile[i].lx = 0;
        av->missile[i].ly = 0;
        av->missile[i].mult = 1;
    }
    for (i = 0; i < av->num_robots; i++) {
        av->robot[i].mem_watch = 128;
        reset_hardware(i);
        reset_software(i);
    }
    if (av->graphix) {
        //setscreen();
    }
    if (av->graphix && (av->step_mode > 0)) {
        //init_debug_window();
    }
    if (!av->graphix) {
        //textcolor(7);
        //There is some commented "battle in progress" text here...
    }
}

void atr2::bout() {
    int i, j, k, n;
    char c;
    long timer;

    if(av->quit) {
        exit(0);
    }

    //atr2a->update_vars(0, 0);
    //atr2a->update();
    atr2func::time_delay(1);

    av->played++;
    init_bout();
    av->bout_over = false;

    if (av->step_mode == 0) {
        av->step_loop = false;
    } else {
        av->step_loop = true;
    }
    av->step_count = -1;
    if (av->graphix && (av->step_mode > 0)) {
        for (i = 0; i < av->num_robots; i++) {
            draw_robot(i);
        }
    }

    do {
        while (av->game_paused) {
            //wait until game not paused
            atr2func::time_delay(1);
        }

        av->game_cycle++;
        for (i = 0; i < av->num_robots; i++) {
            if (av->robot[i].armor > 0) {
                do_robot(i);
            }
        }
        //atr2a->clear_missiles();
        atr2a->update_missile(3000);
        for (i = 0; i < atr2var::max_missiles; i++) {
            if (av->missile[i].a > 0) {
                do_missile(i);
            }
        }
        for (i = 0; i < av->num_robots; i++) {
            for (k = 0; k < atr2var::max_mines; k++) {
                if (av->robot[i].mine[k].yield > 0) {
                    do_mine(i, k);
                }
            }
        }

        if (av->graphix && av->timing) {
            //atr2func::time_delay(av->game_delay);
        }

        /*if (keypressed) {
            c = upcase(readkey)
        } else {
            c = (char)255;
        }
        switch(c) {
            case 'X':
            case '+', '=':
            case '-', '_':
            case 'G':
            default:
                process_keypress(c);
        }*/

        //flushkey;
        if (av->game_delay < 0) {
            av->game_delay = 0;
        }
        if (av->game_delay > 100) {
            av->game_delay = 100;
        }

        /*switch(av->game_delay) {
            case 0 ... 1:
                k = 100;
            case 2 ... 5:
                k = 50;
            case 6 ... 10:
                k = 25;
            case 11 ... 25:
                k = 20;
            case 26 ... 40:
                k = 10;
            case 41 ... 70:
                k = 5;
            case 71 ... atr2var::maxint:
                k = 1;
            default:
                k = 10;
        }

        if (!av->graphix) {
            k = 100;
        }*/
        /*if (av->graphix) {
            if (((av->game_cycle % k) == 0) || (av->game_cycle == 10)) {
                update_cycle_window();
            } else {
                if (av->update_timer != mem[0:$46C] >> 1) {
                    update_cycle_window();
                }
                av->update_timer = mem[0:$46C] >> 1;
            }
        }*/
    } while(!(av->quit || gameover() || av->bout_over));

    //update_cycle_window();
    score_robots();
    show_statistics();
}

void atr2::write_report() {
    int i, j, k;
    std::ofstream f;

    f.open(av->main_filename + av->report_ext);

    f << av->num_robots + 1 << std::endl;
    for (i = 0; i < av->num_robots; i++) {
        switch(av->report_type) {
            case 2:
                f << av->robot[i].wins << " " << av->robot[i].trials << " " << av->robot[i].kills << " " << av->robot[i].deaths << " "
                  << av->robot[i].fn << " " << std::endl;
                break;
            case 3:
                f << av->robot[i].wins << " " << av->robot[i].trials << " " << av->robot[i].kills << " " << av->robot[i].deaths << " "
                  << av->robot[i].armor << " " << av->robot[i].heat << " " << av->robot[i].shots_fired << " " << av->robot[i].fn << " "
                  << std::endl;
                break;
            case 4:
                f << av->robot[i].wins << " " << av->robot[i].trials << " " << av->robot[i].kills << " " << av->robot[i].deaths << " "
                  << av->robot[i].armor << " " << av->robot[i].heat << " " << av->robot[i].shots_fired << " " << av->robot[i].hits << " "
                  << av->robot[i].damage_total << " " << av->robot[i].cycles_lived << " " << av->robot[i].error_count << " "
                  << av->robot[i].fn << " " << std::endl;
                break;
            default:
                f << av->robot[i].wins << " " << av->robot[i].trials << " " << av->robot[i].fn << " " << std::endl;
        }
    }
    f.close();
}

void atr2::begin_window() {

}
