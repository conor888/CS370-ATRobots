#include <iostream>
#include <cmath>
#include <cstring>
#include "atr2func.h"

using namespace std;

const string
    progname        = "AT-Robots",
    version         = "2.11",
    cnotice1        = "Copyright 1997-99, Ed T. Toton III",
    cnotice2        = "All Rights Reserved.",
    cnotice3        = "Copyright 2014, William \"Amos\" Confer",
    main_filename   = "ATR2",
    robot_ext       = ".AT2",
    locked_ext      = ".ATL",
    config_ext      = ".ATS",
    compile_ext     = ".CMP",
    report_ext      = ".REP";

const bool
    _T = true,
    _F = false,

    //debugging/compiler
    show_code           = _F,
    compile_by_line     = _F,
    debugging_compiler  = _F;

const double
        screen_scale = 0.46;

const int
    minint          = -32768,
    max_var_len     = 16,

    //robots
    max_robots      = 31,
    max_code        = 1023,
    max_op          = 3,
    stack_size      = 256,
    stack_base      = 768,
    max_ram         = 1023,
    max_vars        = 256,
    max_labels      = 256,
    acceleration    = 4,
    turn_rate       = 8,
    max_vel         = 4,
    max_missiles    = 1023,
    missile_spd     = 32,
    hit_range       = 14,
    blast_radius    = 25,
    crash_range     = 8,
    max_sonar       = 250,
    com_queue       = 512,
    max_queue       = 255,
    max_config_points=12,
    max_mines       = 63,
    mine_blast      = 35,

    //simulator & graphics
    //screen_scale   =0.46,
    screen_x        = 5,
    screen_y        = 5,
    robot_scale     = 06,
    default_delay   = 20,
    default_slice   = 05,
    mine_circle     = (int)trunc(mine_blast*screen_scale)+1,
    blast_circle    = (int)trunc(blast_radius*screen_scale)+1,
    mis_radius      = (int)trunc(hit_range/2)+1,
    max_robot_lines = 8;
    //Gray50 : FillPatternType = ($AA, $55, $AA, $55,
    //        $AA, $55, $AA, $55);

typedef struct op_rec {
    int op[max_op];
};

typedef op_rec prog_type[max_code];

typedef struct config_rec {
    int scanner, weapon, armor, engine, heatsinks, shield, mines;
};

typedef struct mine_rec {
    double x, y;
    int detect, yield;
    bool detonate;
};

typedef struct robot_rec {
    //FIFI
    bool is_locked;
    int mem_watch;

    double x, y, lx, ly, xv, yv, speed, shotstrength, damageadj, speedadj, meters;
    int hd, thd, lhd, spd, tspd, armor, larmor, heat, lheat, ip,
            plen, scanarc, accuracy, shift, err, delay_left, robot_time_limit,
            max_time, time_left, lshift, arc_count, sonar_count, scanrange,
            last_damage, last_hit, transponder, shutdown, channel,
            lendarc, endarc, lstartarc, startarc, mines;
    int tx[max_robot_lines], ltx[max_robot_lines], ty[max_robot_lines], lty[max_robot_lines];
    long wins,  trials, kills, deaths, startkills, shots_fired, match_shots,
            hits, damage_total, cycles_lived, error_count;
    config_rec config;
    string name[31];
    string fn[255];
    bool shields_up, lshields, overburn, keepshift, cooling, won;
    prog_type code;
    int ram[max_ram];
    mine_rec mine[max_mines];
    //text errorlog;
};

typedef std::string parsetype[max_op];

//typedef &robot_rec robot_ptr;

typedef struct missile_rec {
    double x, y, lx, ly, mult, mspd;
    int source, a, hd, rad, lrad, max_rad;
};



///Function declarations
string operand(int, int);
string mnemonic(int, int);
void prog_error(int, string);
void print_code(int, int);
void parse1(int, int, parsetype);
void check_plen(int);
void compile(int, string);
void robot_config(int);
void reset_software(int);
void reset_hardware(int n)



//Robot variables
int num_robots;
//robot_ptr robot[max_robots + 4];
robot_rec robot[max_robots + 4];
missile_rec missile[max_missiles];

//Compiler variables
//text f;
int numvars, numlabels, maxcode, lock_pos, lock_dat;
string varname[max_vars]; //[max_var_len]
int varloc[max_vars];
string labelname[max_vars]; //[max_var_len]
int labelnum[max_labels];
bool show_source, compile_only;
string lock_code;

//Simulator/graphics variables
//FIFI
bool bout_over;     //made global from procedure bout
int step_mode;      //0=off, for (0<step_mode<=9) = #of game cycles per step
int temp_mode;      //stores previous step_mode for return to step
int step_count;     //step counter used as break flag
bool step_loop;     //break flag for stepping
//bool show_debugger;       //flag for viewing debugger panel vs. robot stats
// /FIFI
bool old_shields, insans_missiles, debug_info, windoze, no_gfx, logging_errors,
    timinig, show_arcs;
int game_delay, time_slice, insanity, update_timer, max_gx, max_gy, stats_mode;
long game_limit, game_cycle, matches, played, executed;

//General settings
bool quit, report, show_cnotice;
int kill_count, report_type;



int main() {
    return 0;
}

string operand(int n, int m) {
    string s;
    s = n;

    switch (m & 7) {
        case 1: s = "@" + s;
        case 2: s = ":" + s;
        case 3: s = "$" + s;
        case 4: s = "!" + s;
        default: s = n;
    }

    if ((m & 8) > 0) {
        s = "[" + s + "]";
    }

    return s;
}

string mnemonic(int n, int m)  {
    string s;
    s = n;

    if (m == 0) {
        switch (n) {
            case 0: s = "NOP";
            case 1: s = "ADD";
            case 2: s = "SUB";
            case 3: s = "OR";
            case 4: s = "AND";
            case 5: s = "XOR";
            case 6: s = "NOT";
            case 7: s = "MPY";
            case 8: s = "DIV";
            case 9: s = "MOD";
            case 10: s = "RET";
            case 11: s = "CALL";
            case 12: s = "JMP";
            case 13: s = "JLS";
            case 14: s = "JGR";
            case 15: s = "JNE";
            case 16: s = "JE";
            case 17: s = "SWAP";
            case 18: s = "DO";
            case 19: s = "LOOP";
            case 20: s = "CMP";
            case 21: s = "TEST";
            case 22: s = "MOV";
            case 23: s = "LOC";
            case 24: s = "GET";
            case 25: s = "PUT";
            case 26: s = "INT";
            case 27: s = "IPO";
            case 28: s = "OPO";
            case 29: s = "DELAY";
            case 30: s = "PUSH";
            case 31: s = "POP";
            case 32: s = "ERR";
            case 33: s = "INC";
            case 34: s = "DEC";
            case 35: s = "SHL";
            case 36: s = "SHR";
            case 37: s = "ROL";
            case 38: s = "ROR";
            case 39: s = "JZ";
            case 40: s = "JNZ";
            case 41: s = "JGE";
            case 42: s = "JLE";
            case 43: s = "SAL";
            case 44: s = "SAR";
            case 45: s = "NEG";
            case 46: s = "JTL";
            default: s = "XXX";
        }
    } else {
        s = operand(n,m);
    }

    return s;
}

void prog_error(int n, string ss) {
    string s;

    //graph_mode(false);
    //textcolor(15); turns text white?
    cout << "Error #" << n << ": ";

    switch(n) {
        case 0:
            cout << "User error.";
        case 1:
            cout << "Invalid :label - \"" << ss << "\", silly mortal.";
        case 2:
            cout << "Undefined identifier - \"" << ss << "\". A typo perhaps?";
        case 3:
            cout << "Memory access out of range - \"" << ss << "\"";
        case 4:
            cout << "Not enough robots for combat. Maybe we should just drive in circles.";
        case 5:
            cout << "Robot names and settings must be specified. An empty arena is no fun.";
        case 6:
            cout << "Config file not found - \"" << ss << "\"";
        case 7:
            cout << "Cannot access a config file from a config file - \"" << ss << "\"";
        case 8:
            cout << "Robot not found \"" << ss << "\". Perhaps you mistyped it?";
        case 9:
            cout << "Insufficient RAM to load robot: \"" << ss << "\"... This is not good.";
        case 10:
            cout << "Too many robots! We can only handle " << max_robots + 1 << "! Blah.. limits are limits.";
        case 11:
            cout << "You already have a perfectly good #def for \"" << ss << "\", silly.";
        case 12:
            cout << "Variable name too long! (Max: " << max_var_len << ") \"" << ss << "\"";
        case 13:
            cout << "!Label already defined \"" << ss << "\", silly.";
        case 14:
            cout << "Too many variables! (Var Limit: " << max_vars << ")";
        case 15:
            cout << "Too many !labels! (!Label Limit: " << max_labels << ")";
        case 16:
            cout << "Robot program too long! Boldly we simplify, simplify along... " << ss;
        case 17:
            cout << "!Label missing error. !Label #" << ss << ".";
        case 18:
            cout << "!Label out of range: " << ss;
        case 19:
            cout << "!Label not found. " << ss;
        case 20:
            cout << "Invalid config option: \"" << ss << "\". Inventing a new device?";
        case 21:
            cout << "Robot is attempting to cheat; Too many config points (" << ss << ")";
        case 22:
            cout << "Insufficient data in data statement: \"" << ss << "\"";
        case 23:
            cout << "Too many asterisks: \"" << ss << "\"";
        case 24:
            cout << "Invalid step count: \"" << ss << "\". 1-9 are valid conditions.";
        case 25:
            cout << "\"" << ss << "\"";
        default:
            cout << ss;
    }
    cout << endl;
    exit(n);
}

void print_code(int n, int p) {
    int i;
    std::cout << std::hex << p << ": ";
    for (i = 0; max_op; i++) {
        cout << setfill("0") << setw(5) << robot[n]^.code[p].op[i] << " ";
    }
    cout << " = ";
    for (i = 0; max_op; i++) {
        std::cout << std::hex << robot[n]^.code[p].op[i] << "h" << "\n\n";
    //Not done
}

void parse1(int n, int p, parsetype s) {
    int i, j, k, opcode, microcode;
    bool found, indirect;
    string ss;

    //with robot[n]^ do
        for (i = 0; i < max_op-1; i++) {
            k = 0;
            found = false;
            opcode = 0;
            microcode = 0;
            //s[i] = btrim(ucase(s[i]));
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

            //If string is empty (figure out how to access struct array properly
            if (s[i].empty()) {
                opcode = 0;
                microcode = 0;
                found = true;
            }

            //!labels
            if(not found && s[i][0]=='!') {
                ss = s[i];
                //ss = btrim(rstr(ss,length(ss)-1));
                if (numlabels > 0) {
                    for (j = 1; j < numlabels; j++) {
                        if (ss.compare(labelname[j]) == 0) {
                            found = true;
                            if (labelnum[j] >= 0) {
                                opcode = labelnum[j];
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
                if (not found) {
                    numlabels++;
                    if (numlabels > max_labels) {
                        exit(15);
                    } else {
                        labelname[numlabels] = ss;
                        labelnum[numlabels] = -1;
                        opcode = numlabels;
                        microcode = 3; //unresolved !label
                        found = true;
                    }
                }
            }

            ///variables
            if (numvars > 0 && not found) {
                for (j = 1; j < numvars; j++) {
                    if (s[i].compare(varname[j]) == 0) {
                        opcode = varloc[j];
                        microcode = 1; //variable
                        found = true;
                    }
                }
            }

            ///instructions
            if (s[i] == "NOP"     ) { opcode = 0; found = true; }
            if (s[i] == "ADD"     ) { opcode = 1; found = true; }
            if (s[i] == "SUB"     ) { opcode = 2; found = true; }
            if (s[i] == "OR"      ) { opcode = 3; found = true; }
            if (s[i] == "AND"     ) { opcode = 4; found = true; }
            if (s[i] == "XOR"     ) { opcode = 5; found = true; }
            if (s[i] == "NOT"     ) { opcode = 6; found = true; }
            if (s[i] == "MPY"     ) { opcode = 7; found = true; }
            if (s[i] == "DIV"     ) { opcode = 8; found = true; }
            if (s[i] == "MOD"     ) { opcode = 9; found = true; }
            if (s[i] == "RET"     ) { opcode = 10; found = true; }
            if (s[i] == "RETURN"  ) { opcode = 10; found = true; }
            if (s[i] == "GSB"     ) { opcode = 11; found = true; }
            if (s[i] == "GOSUB"   ) { opcode = 11; found = true; }
            if (s[i] == "CALL"    ) { opcode = 11; found = true; }
            if (s[i] == "JMP"     ) { opcode = 12; found = true; }
            if (s[i] == "JUMP"    ) { opcode = 12; found = true; }
            if (s[i] == "GOTO"    ) { opcode = 12; found = true; }
            if (s[i] == "JLS"     ) { opcode = 13; found = true; }
            if (s[i] == "JB"      ) { opcode = 13; found = true; }
            if (s[i] == "JGR"     ) { opcode = 14; found = true; }
            if (s[i] == "JA"      ) { opcode = 14; found = true; }
            if (s[i] == "JNE"     ) { opcode = 15; found = true; }
            if (s[i] == "JEQ"     ) { opcode = 16; found = true; }
            if (s[i] == "JE"      ) { opcode = 16; found = true; }
            if (s[i] == "XCHG"    ) { opcode = 17; found = true; }
            if (s[i] == "SWAP"    ) { opcode = 17; found = true; }
            if (s[i] == "DO"      ) { opcode = 18; found = true; }
            if (s[i] == "LOOP"    ) { opcode = 19; found = true; }
            if (s[i] == "CMP"     ) { opcode = 20; found = true; }
            if (s[i] == "TEST"    ) { opcode = 21; found = true; }
            if (s[i] == "SET"     ) { opcode = 22; found = true; }
            if (s[i] == "MOV"     ) { opcode = 22; found = true; }
            if (s[i] == "LOC"     ) { opcode = 23; found = true; }
            if (s[i] == "ADDR"    ) { opcode = 23; found = true; }
            if (s[i] == "GET"     ) { opcode = 24; found = true; }
            if (s[i] == "PUT"     ) { opcode = 25; found = true; }
            if (s[i] == "INT"     ) { opcode = 26; found = true; }
            if (s[i] == "IPO"     ) { opcode = 27; found = true; }
            if (s[i] == "IN"      ) { opcode = 27; found = true; }
            if (s[i] == "OPO"     ) { opcode = 28; found = true; }
            if (s[i] == "OUT"     ) { opcode = 28; found = true; }
            if (s[i] == "DEL"     ) { opcode = 29; found = true; }
            if (s[i] == "DELAY"   ) { opcode = 29; found = true; }
            if (s[i] == "PUSH"    ) { opcode = 30; found = true; }
            if (s[i] == "POP"     ) { opcode = 31; found = true; }
            if (s[i] == "ERR"     ) { opcode = 32; found = true; }
            if (s[i] == "ERROR"   ) { opcode = 32; found = true; }
            if (s[i] == "INC"     ) { opcode = 33; found = true; }
            if (s[i] == "DEC"     ) { opcode = 34; found = true; }
            if (s[i] == "SHL"     ) { opcode = 35; found = true; }
            if (s[i] == "SHR"     ) { opcode = 36; found = true; }
            if (s[i] == "ROL"     ) { opcode = 37; found = true; }
            if (s[i] == "ROR"     ) { opcode = 38; found = true; }
            if (s[i] == "JZ"      ) { opcode = 39; found = true; }
            if (s[i] == "JNZ"     ) { opcode = 40; found = true; }
            if (s[i] == "JAE"     ) { opcode = 41; found = true; }
            if (s[i] == "JGE"     ) { opcode = 41; found = true; }
            if (s[i] == "JLE"     ) { opcode = 42; found = true; }
            if (s[i] == "JBE"     ) { opcode = 42; found = true; }
            if (s[i] == "SAL"     ) { opcode = 43; found = true; }
            if (s[i] == "SAR"     ) { opcode = 44; found = true; }
            if (s[i] == "NEG"     ) { opcode = 45; found = true; }
            if (s[i] == "JTL"     ) { opcode = 46; found = true; }

            ///registers
            if (s[i] == "COLCNT"  ) { opcode = 8; microcode = 01; found = true; }
            if (s[i] == "METERS"  ) { opcode = 9; microcode = 01; found = true; }
            if (s[i] == "COMBASE" ) { opcode = 10; microcode = 01; found = true; }
            if (s[i] == "COMEND"  ) { opcode = 11; microcode = 01; found = true; }
            if (s[i] == "FLAGS"   ) { opcode = 64; microcode = 01; found = true; }
            if (s[i] == "AX"      ) { opcode = 65; microcode = 01; found = true; }
            if (s[i] == "BX"      ) { opcode = 66; microcode = 01; found = true; }
            if (s[i] == "CX"      ) { opcode = 67; microcode = 01; found = true; }
            if (s[i] == "DX"      ) { opcode = 68; microcode = 01; found = true; }
            if (s[i] == "EX"      ) { opcode = 69; microcode = 01; found = true; }
            if (s[i] == "FX"      ) { opcode = 70; microcode = 01; found = true; }
            if (s[i] == "SP"      ) { opcode = 71; microcode = 01; found = true; }

            ///constants
            if (s[i] == "MAXINT"    ) { opcode = 32767;  microcode = 0; found = true; }
            if (s[i] == "MININT"    ) { opcode = -32768; microcode = 0; found = true; }
            if (s[i] == "P_SPEDOMETER"  ) { opcode = 1; microcode = 0; found = true; }
            if (s[i] == "P_HEAT"        ) { opcode = 2; microcode = 0; found = true; }
            if (s[i] == "P_COMPASS"     ) { opcode = 3; microcode = 0; found = true; }
            if (s[i] == "P_TANGLE"      ) { opcode = 4; microcode = 0; found = true; }
            if (s[i] == "P_TURRET_OFS"  ) { opcode = 4; microcode = 0; found = true; }
            if (s[i] == "P_THEADING"    ) { opcode = 5; microcode = 0; found = true; }
            if (s[i] == "P_TURRET_ABS"  ) { opcode = 5; microcode = 0; found = true; }
            if (s[i] == "P_ARMOR"       ) { opcode = 6; microcode = 0; found = true; }
            if (s[i] == "P_DAMAGE"      ) { opcode = 6; microcode = 0; found = true; }
            if (s[i] == "P_SCAN"        ) { opcode = 7; microcode = 0; found = true; }
            if (s[i] == "P_ACCURACY"    ) { opcode = 8; microcode = 0; found = true; }
            if (s[i] == "P_RADAR"       ) { opcode = 9; microcode = 0; found = true; }
            if (s[i] == "P_RANDOM"      ) { opcode = 10; microcode = 0; found = true; }
            if (s[i] == "P_RAND"        ) { opcode = 10; microcode = 0; found = true; }
            if (s[i] == "P_THROTTLE"    ) { opcode = 11; microcode = 0; found = true; }
            if (s[i] == "P_TROTATE"     ) { opcode = 12; microcode = 0; found = true; }
            if (s[i] == "P_OFS_TURRET"  ) { opcode = 12; microcode = 0; found = true; }
            if (s[i] == "P_TAIM"        ) { opcode = 13; microcode = 0; found = true; }
            if (s[i] == "P_ABS_TURRET"  ) { opcode = 13; microcode = 0; found = true; }
            if (s[i] == "P_STEERING"    ) { opcode = 14; microcode = 0; found = true; }
            if (s[i] == "P_WEAP"        ) { opcode = 15; microcode = 0; found = true; }
            if (s[i] == "P_WEAPON"      ) { opcode = 15; microcode = 0; found = true; }
            if (s[i] == "P_FIRE"        ) { opcode = 15; microcode = 0; found = true; }
            if (s[i] == "P_SONAR"       ) { opcode = 16; microcode = 0; found = true; }
            if (s[i] == "P_ARC"         ) { opcode = 17; microcode = 0; found = true; }
            if (s[i] == "P_SCANARC"     ) { opcode = 17; microcode = 0; found = true; }
            if (s[i] == "P_OVERBURN"    ) { opcode = 18; microcode = 0; found = true; }
            if (s[i] == "P_TRANSPONDER" ) { opcode = 19; microcode = 0; found = true; }
            if (s[i] == "P_SHUTDOWN"    ) { opcode = 20; microcode = 0; found = true; }
            if (s[i] == "P_CHANNEL"     ) { opcode = 21; microcode = 0; found = true; }
            if (s[i] == "P_MINELAYER"   ) { opcode = 22; microcode = 0; found = true; }
            if (s[i] == "P_MINETRIGGER" ) { opcode = 23; microcode = 0; found = true; }
            if (s[i] == "P_SHIELD"      ) { opcode = 24; microcode = 0; found = true; }
            if (s[i] == "P_SHIELDS"     ) { opcode = 24; microcode = 0; found = true; }
            if (s[i] == "I_DESTRUCT"    ) { opcode = 0; microcode = 0; found = true; }
            if (s[i] == "I_RESET"       ) { opcode = 1; microcode = 0; found = true; }
            if (s[i] == "I_LOCATE"      ) { opcode = 2; microcode = 0; found = true; }
            if (s[i] == "I_KEEPSHIFT"   ) { opcode = 3; microcode = 0; found = true; }
            if (s[i] == "I_OVERBURN"    ) { opcode = 4; microcode = 0; found = true; }
            if (s[i] == "I_ID"          ) { opcode = 5; microcode = 0; found = true; }
            if (s[i] == "I_TIMER"       ) { opcode = 6; microcode = 0; found = true; }
            if (s[i] == "I_ANGLE"       ) { opcode = 7; microcode = 0; found = true; }
            if (s[i] == "I_TID"         ) { opcode = 8; microcode = 0; found = true; }
            if (s[i] == "I_TARGETID"    ) { opcode = 8; microcode = 0; found = true; }
            if (s[i] == "I_TINFO"       ) { opcode = 9; microcode = 0; found = true; }
            if (s[i] == "I_TARGETINFO"  ) { opcode = 9; microcode = 0; found = true; }
            if (s[i] == "I_GINFO"       ) { opcode = 10; microcode = 0; found = true; }
            if (s[i] == "I_GAMEINFO"    ) { opcode = 10; microcode = 0; found = true; }
            if (s[i] == "I_RINFO"       ) { opcode = 11; microcode = 0; found = true; }
            if (s[i] == "I_ROBOTINFO"   ) { opcode = 11; microcode = 0; found = true; }
            if (s[i] == "I_COLLISIONS"  ) { opcode = 12; microcode = 0; found = true; }
            if (s[i] == "I_RESETCOLCNT" ) { opcode = 13; microcode = 0; found = true; }
            if (s[i] == "I_TRANSMIT"    ) { opcode = 14; microcode = 0; found = true; }
            if (s[i] == "I_RECEIVE"     ) { opcode = 15; microcode = 0; found = true; }
            if (s[i] == "I_DATAREADY"   ) { opcode = 16; microcode = 0; found = true; }
            if (s[i] == "I_CLEARCOM"    ) { opcode = 17; microcode = 0; found = true; }
            if (s[i] == "I_KILLS"       ) { opcode = 18; microcode = 0; found = true; }
            if (s[i] == "I_DEATHS"      ) { opcode = 18; microcode = 0; found = true; }
            if (s[i] == "I_CLEARMETERS" ) { opcode = 19; microcode = 0; found = true; }


            ///memory addresses
            if ((not found) && (s[i].compare(0, 1, "@") == 0) && isdigit(s[i][1]) ) {
                //opcode = str2int(rstr(s[i],length(s[i])-1));
                if ((opcode < 0) || (opcode > (max_ram + 1) + (((max_code + 1) << 3) - 1))) {
                    prog_error(3, s[i]);
                }
                microcode = 1;
                found = true;
            }

            ///numbers
            if ((not found) && (isdigit(s[i][0]) || s[i].compare(0, 1, "-"))) {
                opcode = stoi(s[i]);
                found = true;
            }

            if (found) {
                robot[n].code[p].op[i] = opcode;
                if (indirect) {
                    microcode = microcode | 8;
                }
                robot[n].code[p].op[max_op] = robot[n].code[p].op[max_op] | (microcode << (i * 4));
            } else if (!s[i].empty()) {
                prog_error(2, s[i]);
            }
        }

    if (show_code) {
        //print_code(n, p);
    }
    if (compile_by_line) {
        //readkey;
    }
}

void check_plen(int plen) {
    if (plen > maxcode) {
        //std::ostringstream streamtemp;
        //streamtemp << "\nMaximum program length exceeded, (Limit: " << maxcode+1 << " compiled lines)";
        prog_error(16, "Maximum program length exceeded.");
    }
}

void compile(int n, string filename) {
    //Not started
}

void robot_config(int n) {
    int i, j, k;

    switch (robot[n].config.scanner) {
        case 5:
            robot[n].scanrange = 1500;
        case 4:
            robot[n].scanrange = 1000;
        case 3:
            robot[n].scanrange = 700;
        case 2:
            robot[n].scanrange = 500;
        case 1:
            robot[n].scanrange = 350;
        default:
            robot[n].scanrange = 250;
    }

    switch (robot[n].config.weapon) {
        case 5:
            robot[n].shotstrength = 1.5;
        case 4:
            robot[n].shotstrength = 1.35;
        case 3:
            robot[n].shotstrength = 1.2;
        case 2:
            robot[n].shotstrength = 1.0;
        case 1:
            robot[n].shotstrength = 0.8;
        default:
            robot[n].shotstrength = 0.5;
    }

    switch (robot[n].config.armor) {
        case 5:
            robot[n].damageadj = 0.66;
            robot[n].speedadj  = 0.66;
        case 4:
            robot[n].damageadj = 0.77;
            robot[n].speedadj  = 0.75;
        case 3:
            robot[n].damageadj = 0.83;
            robot[n].speedadj  = 0.85;
        case 2:
            robot[n].damageadj = 1.0;
            robot[n].speedadj  = 1.0;
        case 1:
            robot[n].damageadj = 1.5;
            robot[n].speedadj  = 1.2;
        default:
            robot[n].damageadj = 2.0;
            robot[n].speedadj  = 1.33;
    }

    switch (robot[n].config.engine) {
        case 5:
            robot[n].speedadj = robot[n].speedadj * 1.5;
        case 4:
            robot[n].speedadj = robot[n].speedadj * 1.35;
        case 3:
            robot[n].speedadj = robot[n].speedadj * 1.2;
        case 2:
            robot[n].speedadj = robot[n].speedadj * 1.0;
        case 1:
            robot[n].speedadj = robot[n].speedadj * 0.8;
        default:
            robot[n].speedadj = robot[n].speedadj * 0.5;
    }

    switch (robot[n].config.mines) {
        case 5:
            robot[n].mines = 24;
        case 4:
            robot[n].mines = 16;
        case 3:
            robot[n].mines = 10;
        case 2:
            robot[n].mines = 6;
        case 1:
            robot[n].mines = 4;
        default:
            robot[n].mines = 2;
            robot[n].config.mines = 0;
    }

    robot[n].shields_up = false;
    if (robot[n].config.shield < 3 || robot[n].config.shield > 5) {
        robot[n].config.shield = 0;
    }
    if (robot[n].config.heatsinks < 0 || robot[n].config.heatsinks > 5) {
        robot[n].config.heatsinks = 0;
    }
}

void reset_software(int n) {
    int i;
    for(i = 0; i < max_ram; i++) {
        robot[n].ram[i] = 0;
        robot[n].ram[71] = 768;
        robot[n].thd = robot[n].hd;
        robot[n].tspd = 0;
        robot[n].scanarc = 8;
        robot[n].shift = 0;
        robot[n].err = 0;
        robot[n].overburn = false;
        robot[n].keepshift = false;
        robot[n].ip = 0;
        robot[n].accuracy = 0;
        robot[n].meters = 0;
        robot[n].delay_left = 0;
        robot[n].time_left = 0;
        robot[n].shields_up = false;
    }
}

void reset_hardware(int n) {
    int i;
    double d, dd;

    for(i = 0; i < max_robot_lines; i++) {
        robot[n].ltx[i] = 0;
        robot[n].tx[i] = 0;
        robot[n].lty[i] = 0;
        robot[n].ty[i] = 0;
    }
    do {
        robot[n].x = rand() % 1000;
        robot[n].y = rand() % 1000;
        dd = 1000;
        for(i = 0; i < num_robots; i++) {
            if(robot[i].x < 0) {
                robot[i].x = 0;
            }
            if(robot[i].x > 1000) {
                robot[i].x = 1000;
            }
            if(robot[i].y < 0) {
                robot[i].y = 0;
            }
            if(robot[i].y > 1000) {
                robot[i].y = 1000;
            }
            d = atr2func::distance(robot[n].x, robot[n].y, robot[i].x, robot[i].y);
            if((robot[i].armor > 0) && (i != n) && (d < dd)) {
                dd = d;
            }
        }
    } while (dd > 32);
}
