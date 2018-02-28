#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include "atr2func.h"
#include "filelib.h"

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
    maxint          = 32768,
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

struct op_rec {
    int op[max_op];
};

typedef op_rec prog_type[max_code];

struct config_rec {
    int scanner, weapon, armor, engine, heatsinks, shield, mines;
};

struct mine_rec {
    double x, y;
    int detect, yield;
    bool detonate;
};

struct robot_rec {
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
    string name;
    string fn;
    bool shields_up, lshields, overburn, keepshift, cooling, won;
    prog_type code;
    int ram[max_ram];
    mine_rec mine[max_mines];
    ofstream errorlog;
};

typedef std::string parsetype[max_op];

//typedef &robot_rec robot_ptr;

struct missile_rec {
    double x, y, lx, ly, mult, mspd;
    int source, a, hd, rad, lrad, max_rad;
};



///Function declarations
string operand(int n, int m);
string mnemonic(int n, int m);
void log_error(int n, int i, string ov);
int max_shown();
//bool graph_check(int n);
//void robot_graph(int n);
void update_armor(int n);                       //Not done
void update_heat(int n); //Not done
void robot_error(int n, int i, string ov);      //Not done
//void update_lives(int n);
//void update_cycle_window();
//void setscreen();
//void graph_mode(bool on);
void prog_error(int n, string ss);
void print_code(int n, int p);
void parse1(int n, int p, parsetype s);
void check_plen(int plen);
void compile(int n, string filename);
void robot_config(int n);
void reset_software(int n);
void reset_hardware(int n);
void init_robot(int n);
void create_robot(int n, string filename);
void shutdown();
void delete_compile_report();                   //Skipped
void write_compile_report();
void parse_param(string s);
void init(int argc, char* argv[]);
void draw_robot(int n);                         //Not done
int get_from_ram(int n, int i, int j);          //Not done
int get_val(int n, int c, int o);
void put_val(int n, int c, int o, int v);
void push(int n, int v);
int pop(int n);
int find_label(int n, int l, int m);
void init_mine(int n, int detectrange, int size);
int count_missiles();
void init_missile(double xx, double yy, double xxv, double yyv, int dir, int s, int blast, bool ob);
void damage(int n, int d, bool physical);       //Not done
//int scan(int n);
//void com_transmit(int n, int chan, int data);
//int com_receive(int n);
//int in_port(int n, int p, int time_used); //time_used has var label?
//void out_port(int n, int p, int v, int time_used); //time_used has var label?
//void call_int(int n, int int_num, int time_used); //time_used has var label?
void jump(int n, int o, bool inc_ip); //inc_ip has var label?
//void update_debug_bars();
//void update_debug_system();
//void update_debug_registers();
//void update_debug_flags();
//void update_debug_memory();
//void update_debug_code();
//void update_debug_window();
//void init_debug_window();
//void close_debug_window();
bool gameover();
//void toggle_graphix();
bool invalid_microcode(int n, int ip);
//void process_keypress(char c);
void execute_instruction(int n);
void do_robot(int n);
void do_mine(int n, int m);                     //Not done
void do_missile(int n);                         //Not done
string victor_string(int k, int n);
void show_statistics();
//void score_robots();
void init_bout();
void bout();
//void write_report();
void begin_window();                            //Not done




//Robot variables
int num_robots;
//robot_ptr robot[max_robots + 4];
robot_rec robot[max_robots + 4];
missile_rec missile[max_missiles];

//Compiler variables
ifstream f;
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
bool old_shields, insane_missiles, debug_info, windoze, no_gfx, logging_errors,
    timinig, show_arcs;
int game_delay, time_slice, insanity, update_timer, max_gx, max_gy, stats_mode;
long game_limit, game_cycle, matches, played, executed;

//General settings
bool quit, report, show_cnotice;
int kill_count, report_type;




//Custom global variables (most from init() function)
bool registered, sound_on, graphix, timing;
string reg_name;
int delay_per_sec, reg_num;


int main(int argc, char *argv[]) {
    init(argc, argv);

    int i, j, k, l, n, w;

    if(graphix) {
        begin_window();
    }
    if(matches > 0) {
        for (i = 0; i < matches; i++) {
            bout();
        }
    }
    if(!graphix) {
        cout << endl;
    }
    if(quit) {
        exit(0);
    }
    if(matches > 1) {
        cout << endl << endl;
        //graph_mode(false);
        //textcolor(15);
        cout << "Bout complete! (" << matches << " matches" << endl;
        k = 0;
        w = 0;
        for (i = 0; i < num_robots; i++) {
            if (robot[i].wins == w) {
                k++;
            }
            if (robot[i].wins > w) {
                k = 1;
                n = i;
                w = robot[i].wins;
            }
        }
        cout << "Robot           Wins  Matches  Kills  Deaths    Shots" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        for (i = 0; i < num_robots; i++) {
            //textcolor(robot_color(i));
            cout << atr2func::addfront(atr2func::cstr(i+1), 2) << " - " << atr2func::addrear(robot[i].fn, 8)
                    << atr2func::addfront(atr2func::cstr(robot[i].wins), 7) << atr2func::addfront(atr2func::cstr(robot[i].trials), 8)
                    << atr2func::addfront(atr2func::cstr(robot[i].kills), 8) << atr2func::addfront(atr2func::cstr(robot[i].deaths), 8)
                    << atr2func::addfront(atr2func::cstr(robot[i].shots_fired), 9) << endl;
        }
        //textcolor(15);
        cout << endl;
        if (k == 1) {
            cout << "Robot #" << n + 1 << " (" << robot[n].fn << ") wins the bout! (score: " << w << "/" << matches << ")" << endl;
        } else {
            cout << "There is no clear victor!" << endl;
        }
        cout << endl;
    } else if (graphix) {
        //graph_mode(false);
        //show_statistics();
    }
    if (report) {
        //write_report();
    }

    shutdown();

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

void log_error(int n, int i, string ov) {
    int j, k;
    string s;

    if (!logging_errors) {
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
    robot[n].errorlog << "<" << i << "> " << s << " (Line #" << robot[n].ip << ") [Cycle: " << game_cycle << ", Match: "
                      << played << "/" << matches << "]" << endl;
    robot[n].errorlog << " " << mnemonic(robot[n].code[robot[n].ip].op[0], robot[n].code[robot[n].ip].op[3] & 15) << " "
                      << operand(robot[n].code[robot[n].ip].op[1], (robot[n].code[robot[n].ip].op[3] >> 4) & 15) << ", "
                      << operand(robot[n].code[robot[n].ip].op[2], (robot[n].code[robot[n].ip].op[3] >> 8) & 15);
    if (!ov.empty()) {
        robot[n].errorlog << "    (Values: " << ov << ")" << endl;
    } else {
        robot[n].errorlog << endl;
    }
    robot[n].errorlog << " AX=" << atr2func::addrear(atr2func::cstr(robot[n].ram[65]) + ",", 7);
    robot[n].errorlog << " BX=" << atr2func::addrear(atr2func::cstr(robot[n].ram[66]) + ",", 7);
    robot[n].errorlog << " CX=" << atr2func::addrear(atr2func::cstr(robot[n].ram[67]) + ",", 7);
    robot[n].errorlog << " DX=" << atr2func::addrear(atr2func::cstr(robot[n].ram[68]) + ",", 7);
    robot[n].errorlog << " EX=" << atr2func::addrear(atr2func::cstr(robot[n].ram[69]) + ",", 7);
    robot[n].errorlog << " FX=" << atr2func::addrear(atr2func::cstr(robot[n].ram[70]) + ",", 7);
    robot[n].errorlog << " Flags=" << robot[n].ram[64] << endl;
    robot[n].errorlog << " AX=" << atr2func::addrear(atr2func::hex(robot[n].ram[65]) + ",", 7);
    robot[n].errorlog << " BX=" << atr2func::addrear(atr2func::hex(robot[n].ram[66]) + ",", 7);
    robot[n].errorlog << " CX=" << atr2func::addrear(atr2func::hex(robot[n].ram[67]) + ",", 7);
    robot[n].errorlog << " DX=" << atr2func::addrear(atr2func::hex(robot[n].ram[68]) + ",", 7);
    robot[n].errorlog << " EX=" << atr2func::addrear(atr2func::hex(robot[n].ram[69]) + ",", 7);
    robot[n].errorlog << " FX=" << atr2func::addrear(atr2func::hex(robot[n].ram[70]) + ",", 7);
    robot[n].errorlog << " Flags=" << atr2func::hex(robot[n].ram[64]) << endl;
    robot[n].errorlog << endl;
}

int max_shown() {
    switch(stats_mode) {
        case 1:
            return 12;
        case 2:
            return 32;
        default:
            return 6;
    }
}

void update_armor(int n) {

}

void update_heat(int n) {

}

void robot_error(int n, int i, string ov) {

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
    cout << atr2func::hex(p) << ": ";
    for (i = 0; i < max_op; i++) {
        cout << atr2func::zero_pad(robot[n].code[p].op[i], 5) << " ";
    }
    cout << " = ";
    for (i = 0; i < max_op; i++) {
        cout << atr2func::hex(robot[n].code[p].op[i]) << "h " << "\n\n";
    }
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
                opcode = atr2func::str2int(s[i]);
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
    parsetype pp;
    string s, s1, s2, s3, orig_s, msg;
    int i, j, k, l, linecount, mask, locktype;
    string ss[max_op];
    char c, lc;

    lock_code = "";
    lock_pos = 0;
    locktype = 0;
    lock_dat = 0;

    if (!filelib::exist(filename)) {
        prog_error(8, filename);
    }
    //textcolor(robot_color(n));
    cout << "Compiling robot #" << n+1 << ": " << filename << endl;

    robot[n].is_locked = false;
    numvars = 0;
    numlabels = 0;
    for (k = 0; k < max_code; k++) {
        for (i = 0; i < max_op; i++) {
            robot[n].code[k].op[i] = 0;
        }
    }
    robot[n].plen = 0;
    //assign(f, filename);
    //reset(f);
    s = "";
    linecount = 0;

    while(1) { //(not eof(f)) and (s != "#END)
        //readln(f,s);
        linecount++;
        if (locktype < 3) {
            lock_pos = 0;
        }
        if (!lock_code.empty()) {
            for (i = 1; i < (int)s.length(); i++) {
                lock_pos++;
                if (lock_pos > (int)lock_code.length()) {
                    lock_pos = 1;
                }
                switch(locktype) {
                    case 3:
                        //s[i] = char((ord(s[i])-1) xor (ord(lock_code[lock_pos]) xor lock_dat));
                    case 2:
                        //s[i] = char(ord(s[i]) xor (ord(lock_code[lock_pos]) xor 1));
                    default:
                        exit(0);
                        //s[i] = char(ord(s[i]) xor ord(lock_code[lock_pos]));
                }
                lock_dat = (int)s[i] & 15;
            }
        }
        //s = btrim(s);
        orig_s = s;
        for (i = 1; i < (int)s.length(); i++) {
            if (((int)(s[i]) <= 32) || ((int)(s[i]) >= 128) || s[i] == ',') { //s[i] in [#0..#32,',',#128..#255]
                s.replace(i, 1, " ");
            }
        }
        if (show_source && ((lock_code.empty() || debugging_compiler))) {
            //cout << zero_pad(linecount, 3) << ":" << zero_pad(plen, 3) << " " << s << endl;
        }
        if (debugging_compiler) {
            //if ((int)robot[n].readkey == 27) {
            //    exit(0);
            //}
        }
        k = 0;
        for (i = (int)s.length(); i > 0; i--) {
            if (s[i] == ';') {
                k = i;
            }
        }
        if(k > 0) {
            s = atr2func::lstr(s, k-1);
        }
        s = atr2func::btrim(atr2func::ucase(s));
        for (i = 0; i < max_op; i++) {
            pp[i].clear();
        }
        if (((int)s.length() > 0) && (s[0] != ';')) {
            if (s[0] == '#') {          //Compiler directives
                s1 = atr2func::ucase(atr2func::btrim(atr2func::rstr(s, s.length() - 1)));
                msg = atr2func::btrim(atr2func::rstr(orig_s, orig_s.length() - 5));
                k = 0;
                for (i = 0; i < s1.length(); i++) {
                    if ((k == 0) && (s1[i] == ' ')) {
                        k = i;
                    }
                }
                k--;
                if (k > 1) {
                    s2 = atr2func::lstr(s1, k);
                    s3 = atr2func::ucase(atr2func::btrim(atr2func::rstr(s1, s1.length() - k)));
                    k = 0;
                    if (numvars > 0) {
                        for (i = 0; i < numvars; i++) {
                            if (s3.compare(varname[i]) == 0) {
                                k = i;
                            }
                        }
                    }
                    if ((s2 == "DEF") && (numvars < max_vars)) {
                        if ((int)s3.length() > max_var_len) {
                            prog_error(12, s3);
                        } else {
                            if (k > 0) {
                                prog_error(11, s3);
                            } else {
                                numvars++;
                                if (numvars > max_vars) {
                                    prog_error(14, "");
                                } else {
                                    varname[numvars] = s3;
                                    varloc[numvars]  = 127 + numvars;
                                }
                            }
                        }
                    } else if (atr2func::lstr(s2, 4) == "LOCK") {
                        robot[n].is_locked = true; //this robot is locked
                        if ((int)s2.length() > 4) {
                            locktype = atr2func::value(atr2func::rstr(s2, s2.length() - 4));
                        }
                        lock_code = atr2func::btrim(atr2func::ucase(s3));
                        cout << "Robot is of LOCKed format from this point forward. [" << locktype << "]";
                        for (i = 0; i < (int)lock_code.length(); i++) {
                            lock_code[i] = (char)((int)lock_code[i] - 65);
                        }
                    } else if (s2 == "MSG") {
                        robot[n].name = msg;
                    } else if (s2 == "TIME") {
                        robot[n].robot_time_limit = atr2func::value(s3);
                        if (robot[n].robot_time_limit < 0) {
                            robot[n].robot_time_limit = 0;
                        }
                    } else if (s2 == "CONFIG") {
                        if (atr2func::lstr(s3, 8) == "SCANNER=") {
                            robot[n].config.scanner = atr2func::value(atr2func::rstr(s3, s3.length() - 8));
                        } else if (atr2func::lstr(s3, 7) == "SHIELD=") {
                            robot[n].config.shield = atr2func::value(atr2func::rstr(s3, s3.length() - 7));
                        } else if (atr2func::lstr(s3, 7) == "WEAPON=") {
                            robot[n].config.shield = atr2func::value(atr2func::rstr(s3, s3.length() - 7));
                        } else if (atr2func::lstr(s3, 6) == "ARMOR=") {
                            robot[n].config.shield = atr2func::value(atr2func::rstr(s3, s3.length() - 6));
                        } else if (atr2func::lstr(s3, 7) == "ENGINE=") {
                            robot[n].config.shield = atr2func::value(atr2func::rstr(s3, s3.length() - 7));
                        } else if (atr2func::lstr(s3, 10) == "HEATSINKS=") {
                            robot[n].config.shield = atr2func::value(atr2func::rstr(s3, s3.length() - 10));
                        } else if (atr2func::lstr(s3, 6) == "MINES=") {
                            robot[n].config.shield = atr2func::value(atr2func::rstr(s3, s3.length() - 7));
                        } else {
                            prog_error(20, s3);
                        }

                        if (robot[n].config.scanner < 0) {
                            robot[n].config.scanner = 0;
                        }
                        if (robot[n].config.scanner > 5) {
                            robot[n].config.scanner = 5;
                        }
                        if (robot[n].config.shield < 0) {
                            robot[n].config.shield = 0;
                        }
                        if (robot[n].config.shield > 5) {
                            robot[n].config.shield = 5;
                        }
                        if (robot[n].config.weapon < 0) {
                            robot[n].config.weapon = 0;
                        }
                        if (robot[n].config.weapon > 5) {
                            robot[n].config.weapon = 5;
                        }
                        if (robot[n].config.armor < 0) {
                            robot[n].config.armor = 0;
                        }
                        if (robot[n].config.armor > 5) {
                            robot[n].config.armor = 5;
                        }
                        if (robot[n].config.engine < 0) {
                            robot[n].config.engine = 0;
                        }
                        if (robot[n].config.engine > 5) {
                            robot[n].config.engine = 5;
                        }
                        if (robot[n].config.heatsinks < 0) {
                            robot[n].config.heatsinks = 0;
                        }
                        if (robot[n].config.heatsinks > 5) {
                            robot[n].config.heatsinks = 5;
                        }
                        if (robot[n].config.mines < 0) {
                            robot[n].config.mines = 0;
                        }
                        if (robot[n].config.mines > 5) {
                            robot[n].config.mines = 5;
                        }
                    } else {
                        cout << "Warning: unknown directive \"" << s2 << "\"" << endl;
                    }
                }
            } else if (s[0] == '*') {   //Inline Pre-Compiled Machine Code
                check_plen(robot[n].plen);
                for (i = 0; i < max_op; i++) {
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
                while (i < s.length() && k <= max_op) {
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
                for (i = 0; i < max_op; i++) {
                    robot[n].code[robot[n].plen].op[i] = atr2func::str2int(pp[i]);
                }
                robot[n].plen++;
            } else if (s[0] == ':') {   //:labels
                check_plen(robot[n].plen);
                s1 = atr2func::rstr(s, s.length() - 1);
                for (i = 0; i < s1.length(); i++) {
                    if (!isdigit(s1[i])) {
                        prog_error(1, s);
                    }
                }
                robot[n].code[robot[n].plen].op[0] = atr2func::str2int(s1);
                robot[n].code[robot[n].plen].op[max_op] = 2;
                if (show_code) {
                    print_code(n, robot[n].plen);
                }
                robot[n].plen++;
            } else if (s[0] == '!') {   //!labels
                check_plen(robot[n].plen);
                s1 = atr2func::btrim(atr2func::rstr(s, s.length() - 1));
                k = 0;
                for (i = s1.length(); i >= 0; i--) {
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
                for (i = 0; i < numlabels; i++) {
                    if (labelname[i] == s1) {
                        if (labelnum[i] >= 0) {
                            prog_error(13, "\"!" + s1 + "\" (" + atr2func::cstr(labelnum[i]) + ")");
                        }
                        k = i;
                    }
                }
                if (k == 0) {
                    numlabels++;
                    if (numlabels > max_labels) {
                        prog_error(15, "");
                    }
                    k = numlabels;
                }
                labelname[k] = s1;
                labelnum[k] = robot[n].plen;
            } else {                    //Instructions/Numbers
                check_plen(robot[n].plen);
                //parse instructions
                //remove comments
                k = 0;
                for (i = s1.length(); i >= 0; i--) {
                    if (s[i] == ';') {
                        k = i;
                    }
                }
                if (k > 0) {
                    s = atr2func::lstr(s, k - 1);
                }
                //setup variables for parsing
                k = 0;
                for (j = 0; j > max_op; j++) {
                    pp[j].clear();
                }
                for (j = 0; j > s.length(); j++) {
                    c = s[j];
                    if (!((c == '\b') || (c == '\t') || (c == '\n') || (c == ',') || (c == '\r') ||
                          (c == ' ')) && (k <= max_op)) {
                        pp[k] = pp[k] + c;
                    } else if (!((lc == '\b') || (lc == '\t') || (lc == '\n') || (lc == ',') || (lc == '\r') ||
                                 (lc == ' '))) {
                        k = k + 1;
                    }
                    lc = c;
                }
                parse1(n, robot[n].plen, pp);
                robot[n].plen++;
            }
        }
    }
    f.close();
    if (robot[n].plen <= maxcode) {
        for (i = 0; i < max_op; i++) {
            pp[i].clear();
            parse1(n, robot[n].plen, pp);
        }
    } else {
        robot[n].plen--;
    }

    if (numlabels > 0) {
        for (i = 0; i < robot[n].plen; i++) {
            for (j = 0; j < (max_op - 1); j++) {
                if ((robot[n].code[i].op[max_op] >> (j*4)) == 3) {
                    k = robot[n].code[i].op[j];
                    if ((k > 0) && (k <= numlabels)) {
                        l = labelnum[k];
                        if (l < 0) {
                            prog_error(19, "\"!" + labelname[k] + "\" (" + atr2func::cstr(l) + ")");
                        }
                        if ((l < 0) || (l > maxcode)) {
                            prog_error(18, "\"!" + labelname[k] + "\" (" + atr2func::cstr(l) + ")");
                        } else {
                            robot[n].code[i].op[j] = l;
                            mask = !(15 << (j*4));
                            robot[n].code[i].op[max_op] = (robot[n].code[i].op[max_op] & mask) | (4 << (j*4));
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

void init_robot(int n) {

    int i,j,k,l;

    robot[n].wins = 0;
    robot[n].trials = 0;
    robot[n].kills = 0;
    robot[n].deaths = 0;
    robot[n].shots_fired = 0;
    robot[n].match_shots = 0;
    robot[n].hits = 0;
    robot[n].damage_total = 0;
    robot[n].cycles_lived = 0;
    robot[n].error_count = 0;
    robot[n].plen = 0;
    robot[n].max_time = 0;
    robot[n].name = "";
    robot[n].fn = "";
    robot[n].speed = 0;
    robot[n].arc_count = 0;
    robot[n].sonar_count = 0;
    robot[n].robot_time_limit = 0;
    robot[n].scanrange = 1500;
    robot[n].shotstrength = 1;
    robot[n].damageadj = 1;
    robot[n].speedadj = 1;
    robot[n].mines = 0;

    robot[n].config.scanner = 5;
    robot[n].config.weapon = 2;
    robot[n].config.armor = 2;
    robot[n].config.engine = 2;
    robot[n].config.heatsinks = 1;
    robot[n].config.shield = 0;
    robot[n].config.mines = 0;

    for (i = 0; i < max_ram; i++) {
        robot[n].ram[i] = 0;
    }

    robot[n].ram[71] = 768;

    for (i = 0; i < max_code; i++) {
        for (k = 0; k < max_op; k++) {
            robot[n].code[i].op[k] = 0;
        }
    }
   reset_hardware(n);
   reset_software(n);
}

void create_robot(int n, string filename) {
    int i, j, k;

    //maxavail is no longer applicable to modern operating systems
    /*if(maxavail < sizeof(robot_rec)) {
        prog_error(9, atr2func::base_name(atr2func::no_path(filename)));
    }*/
    //Do we need to create with new?
    //new(robot[n]);
    init_robot(n);
    filename = atr2func::ucase(atr2func::btrim(filename));
    if (filename == filelib::base_name(filename)) {
        if (filename[0] == '?') {
            filename = filename + locked_ext;
        } else {
            filename = filename + robot_ext;
        }
    }
    if (filename[0] == '?') {
        filename = atr2func::rstr(filename, filename.length() - 1);
    }
    robot[n].fn = filelib::base_name(filelib::no_path(filename));
    compile(n, filename);
    robot_config(n);

    k = robot[n].config.scanner + robot[n].config.armor + robot[n].config.weapon + robot[n].config.engine +
            robot[n].config.heatsinks + robot[n].config.shield + robot[n].config.mines;
    if (k > max_config_points) {
        prog_error(21, atr2func::cstr(k) + "/" + atr2func::cstr(max_config_points));
    }
}

void shutdown() {
    int i, j, k;

    // graph_mode(false);
    if (show_cnotice = true) {

    //   textcolor(3);
        cout << progname << " " << version << " ";
        cout << cnotice1 << "\n";
        cout << cnotice2 << "\n";
        cout << cnotice3 << "\n";
    }

    //textcolor(7);
    if (!registered) {
        //textcolor(4);
        cout << "Unregistered version";
    } else {
        cout << "Registered to: " << reg_name;
    }
    //textcolor(7);
    cout << "\n";
    if (logging_errors = true) {

        for (i = 0; i < num_robots; i++) {
            cout << "Robot error-log created: " << filelib::base_name(robot[i].fn) << ".ERR";
            robot[i].errorlog.close();
        }
    }
    exit(0);
}

void delete_compile_report(){
    //not done
    //if exist(main_filename+compile_ext) then
    //delete_file(main_filename+compile_ext);
}

void write_compile_report(){
    ofstream f;
    int i,j,k;

    f.open(main_filename+compile_ext);

    f << num_robots + 1 << "\n";

    for (i = 0; i < num_robots; i++){
        f << robot[i].fn << "\n";
    }

    f.close();
// textcolor(15);

    cout << "\nAll compiles successful!" << "\n\n";

    shutdown();
}

void parse_param(string s) {
    ofstream f;
    string fn, s1;
    bool found;

    found = false;
    s = atr2func::btrim(atr2func::ucase(s));

    if (s.empty()){
        exit(0);
    }

    if (s[0] == '#'){

        fn = atr2func::rstr(s,s.length()-1);
        if (fn == filelib::base_name(fn)){
            fn = fn + config_ext;
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
            step_mode = atr2func::value(atr2func::rstr(s1, s1.length() - 1));
            found = true;
            if (step_mode == 0) {
                step_mode = 1;
            }
            if (step_mode < 1 || step_mode > 9) {
                prog_error(24, atr2func::rstr(s1, s1.length() - 1));
            }
        }

        if (s1[0] == 'D') {
            game_delay = atr2func::value(atr2func::rstr(s1, s1.length() - 1));
            found = true;
        }

        if (s1[0] == 'T') {
            time_slice = atr2func::value(atr2func::rstr(s1, s1.length() - 1));
            found = true;
        }

        if (s1[0] == 'L') {
            game_limit = atr2func::value(atr2func::rstr(s1, s1.length() - 1)) * 1000;
            found = true;
        }

        if (s1[0] == 'Q') {
            sound_on = false;
            found = true;
        }

        if (s1[0] == 'M') {
            matches = atr2func::value(atr2func::rstr(s1, s1.length() - 1));
            found = true;
        }

        if (s1[0] == 'S') {
            show_source = false;
            found = true;
        }

        if (s1[0] == 'G') {
            no_gfx = true;
            found = true;
        }

        if (s1[0] == 'R') {
            report = true;
            found = true;
            if (s1.length() > 1) {
                report_type = atr2func::value(atr2func::rstr(s1, s1.length() - 1));
            }
        }

        if (s1[0] == 'C') {
            compile_only = true;
            found = true;
        }

        if (s1[0] == '^') {
            show_cnotice = false;
            found = true;
        }

        if (s1[0] == 'A') {
            show_arcs = true;
            found = true;
        }

        if (s1[0] == 'W') {
            windoze = false;
            found = true;
        }

        if (s1[0] == '$') {
            debug_info = true;
            found = true;
        }

        if (s1[0] == '#') {
            maxcode = atr2func::value(atr2func::rstr(s1, s1.length() - 1)) - 1;
            found = true;
        }

        if (s1[0] == '!') {
            insane_missiles = true;
            if (s1.length() > 1) {
                insanity = atr2func::value(atr2func::rstr(s1, s1.length() - 1));
            }
            found = true;
        }

        if (s1[0] == '@') {
            old_shields = true;
            found = true;
        }

        if (s1[0] == 'E') {
            logging_errors = true;
            found = true;
        }

        if (insanity < 0) {
            insanity = 0;
        }

        if (insanity > 15) {
            insanity = 15;
        }
    } else if (s[0] == ';'){
        found = true;
    } else if (num_robots < max_robots && s != ""){
        num_robots++;
        create_robot(num_robots,s);
        found = true;
        if (num_robots == max_robots){
            cout << "Maximum number of robots reached." << "\n";
        }
    } else {
        prog_error(10,"");
    }

    if (!found){
        prog_error(8,s);
    }
}

void init(int argc, char *argv[]) {
    int i;

    if(debugging_compiler || compile_by_line || show_code) {
        cout << "!!! Warning !!! Compiler Debugging enabled !!!" << endl;
        //flushkey;
        //readkey;
    }
    step_mode = 0; //stepping disabled
    logging_errors = false;
    stats_mode = 0;
    insane_missiles = false;
    insanity = 0;
    delay_per_sec = 0;
    windoze = true;
    graphix = false;
    no_gfx = false;
    sound_on = true;
    timing = true;
    matches = 1;
    played = 0;
    old_shields = false;
    quit = false;
    compile_only = false;
    show_arcs = false;
    debug_info = false;
    show_cnotice = true;
    show_source = true;
    report = false;
    kill_count = 0;
    maxcode = max_code;
    atr2func::make_tables;
    //randomize;
    num_robots = -1;
    game_limit = 100000;
    game_cycle = 0;
    game_delay = default_delay;
    time_slice = default_slice;
    for (i = 0; i < max_missiles; i++) {
        missile[i].a = 0;
        missile[i].source = -1;
        missile[i].x = 0;
        missile[i].y = 0;
        missile[i].lx = 0;
        missile[i].ly = 0;
        missile[i].mult = 1;
    }
    registered = false;
    reg_name = "Unregistered";
    reg_num = 65535; //FFFF in hex
    //check_registration();
    //textcolor(3);
    cout << endl << progname << " " << version << " " << cnotice1 << endl << cnotice2 << endl;
    //textcolor(7);
    if (!registered) {
        //textcolor(4);
        cout << "Unregistered version" << endl;
    } else {
        cout << "Registered to: " << reg_name << endl;
    }
    //textcolor(7);
    cout << endl;

    delete_compile_report();
    if (argc > 1) {
        for (i = 1; i <= argc; i++) {
            parse_param(atr2func::btrim(atr2func::ucase(argv[i])));
        }
    } else {
        prog_error(5, "");
    }
    temp_mode = step_mode;
    if (logging_errors) {
        for (i = 0; i < num_robots; i++) {
            robot[i].errorlog.open(filelib::base_name(robot[i].fn) + ".ERR");
        }
    }
    if (compile_only) {
        write_compile_report();
    }
    if (num_robots < 1) {
        prog_error(4, "");
    }
    if (!no_gfx) {
        //graph_mode(true);
    }

    //fix ups
    if (matches > 100000) {
        matches = 100000;
    }
    if (matches < 1) {
        matches = 1;
    }
    if (game_delay > 1000) {
        game_delay = 1000;
    }
    if (game_delay < 0) {
        game_delay = 0;
    }
    if (time_slice > 100) {
        time_slice = 100;
    }
    if (time_slice < 1) {
        time_slice = 1;
    }
    if (game_limit < 0) {
        game_limit = 0;
    }
    if (game_limit > 100000) {
        game_limit = 100000;
    }
    if (maxcode < 1) {
        maxcode = 1;
    }
    if (maxcode > max_code) {
        maxcode = max_code;
    }

    //just to avoid floating pointers
    /*for (i = num_robots + 1; i < (max_robots + 2); i++) {
        robot[i] = robot[0];
    }*/
    //robot[-1] = robot[0];
    //robot[-2] = robot[0];

    /*if (!graphix) {
        cout << "Freemem: " << memavail << endl << endl;
    }*/
}

void draw_robot(int n) {

}

int get_from_ram(int n, int i, int j) {
    return 0;
}

int get_val(int n, int c, int o) {
    int i, j, k, l;
    k = 0;

    j = (robot[n].code[c].op[max_op] >> (4*o)) & 15;
    i = robot[n].code[c].op[o];
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

void put_val(int n, int c, int o, int v) {
    int i, j, k;

    k = 0;
    i = 0;
    j = 0;

    j = (robot[n].code[c].op[max_op] >> (4 * o)) & 15;
    i = robot[n].code[c].op[o];
    if ((j & 7) == 1) {
        if ((i < 0) || (i > max_ram)) {
            robot_error(n, 4, atr2func::cstr(i));
        } else {
            if ((j & 8) > 0) {
                i = robot[n].ram[i];
                if ((i < 0) || (i > max_ram)) {
                    robot_error(n, 4, atr2func::cstr(i));
                } else {
                    robot[n].ram[i] = v;
                }
            }
        }
    } else {
        robot[n].ram[i] = v;
    }
    robot_error(n, 3, "");
}

void push(int n, int v) {
    if ((robot[n].ram[71] >= stack_base) && (robot[n].ram[71] < (stack_base + stack_size))) {
        robot[n].ram[71] = v;
        robot[n].ram[71] = robot[n].ram[71] + 1;
    } else {
        robot_error(n, 1, atr2func::cstr(robot[n].ram[71]));
    }
}

int pop(int n) {
    int k;

    if ((robot[n].ram[71] > stack_base) && (robot[n].ram[71] <= (stack_base + stack_size))) {
        robot[n].ram[71] = robot[n].ram[71] - 1;
        k = robot[n].ram[robot[n].ram[71]];
    } else {
        robot_error(n, 5, atr2func::cstr(robot[n].ram[71]));
    }

    return k;
}

int find_label(int n, int l, int m) {
    int i, j, k;

    k = -1;
    if (m == 3) {
        robot_error(n, 9, "");
    } else if (m == 4) {
        k = l ;
    } else {
        for (i = robot[n].plen; i >= 0; i--) {
            j = robot[n].code[i].op[max_op] & 15;
            if ((j == 2) && (robot[n].code[i].op[0] == l)) {
                k = i;
            }
        }
    }
    return k;
}

void init_mine(int n, int detectrange, int size) {
    int i,j,k;
    k = -1;

    for (i = 0; i < max_mines; i++){
        if (((robot[n].mine[i].x < 0) || (robot[n].mine[i].x > 1000) || (robot[n].mine[i].y < 0) || (robot[n].mine[i].y > 1000) || (robot[n].mine[i].yield <= 0)) && (k < 0)) {
            k = i;
        }
    }

    if (k >= 0){
        robot[n].mine[k].x = robot[n].x;
        robot[n].mine[k].y = robot[n].y;
        robot[n].mine[k].detect = detectrange;
        robot[n].mine[k].yield = size;
        robot[n].mine[k].detonate = false;
        //click;
    }
}

int count_missiles(){
    int i,k;
    k = 0;

    for (i = 0; i < max_missiles; i++){
        if (missile[i].a > 0){
            k++;
        }
    }
    return k;
}

void init_missile(double xx,double yy,double xxv,double yyv,int dir,int s,int blast,bool ob){
    int i, j, k;
    double m;
    bool sound;

    k = -1;
    //click();
    for (i = max_missiles; i >= 0; i--){
        if (missile[i].a == 0){
            k = i;
        }
    }
    if (k >= 0){
        missile[k].source = s;
        missile[k].x = xx;
        missile[k].lx = missile[k].x;
        missile[k].y = yy;
        missile[k].ly = missile[k].y;
        missile[k].rad = 0;
        missile[k].lrad = 0;

        if (ob){
            missile[k].mult = 1.25;
        } else {
            missile[k].mult = 1;
        }
        if (blast > 0){
            missile[k].max_rad = blast;
            missile[k].a = 2;
        } else {
            if ((s >= 0) && (s <= num_robots)){
                missile[k].mult = missile[k].mult * (robot[s].shotstrength);
            }
            m = missile[k].mult;
            if (ob){
                m = m + 0.25;
            }
            missile[k].mspd = missile_spd * missile[k].mult;
            if (insane_missiles){
                missile[k].mspd = 100 + (50 * insanity) * missile[k].mult;
            }
            if ((s >= 0) && (s <= num_robots)){
                robot[s].heat = robot[s].heat + (int)round(20*m);
                robot[s].shots_fired++;
                robot[s].match_shots++;
            }
            missile[k].a = 1;
            missile[k].hd = dir;
            missile[k].max_rad = mis_radius;
            /*if (debug_info){
                do {
                    cout << "\n" << atr2func::zero_pad(game_cycle, 5) << " F " << s << ": hd=" << missile[k].hd << "           " << "\n";
                } while (!keypressed);
                atr2func::FlushKey(); //still have to port FlushKey
            }*/
        }
    }

    // (*The following was to see if teh missile array is big enough*)
    //  {else
    //   begin
    //    sound:=sound_on;
    //    sound_on:=true;
    //    chirp;
    //    sound_on:=sound;
    //   end;
    // setfillstyle(1,0);
    // setcolor(robot_color(k));
    // bar(5,5,37,12);
    // outtextxy(5,5,cstr(count_missiles));}
}

void damage(int n, int d, bool physical) {

}

void jump(int n, int o, bool inc_ip) {
    int i, j, k, l, loc;

    loc = find_label(n, get_val(n, robot[n].ip, o), robot[n].code[robot[n].ip].op[max_op] >> (o * 4));
    if ((loc >= 0) && (loc <= robot[n].plen)) {
        inc_ip = false;
        robot[n].ip = loc;
    } else {
        robot_error(n, 2, atr2func::cstr(loc));
    }
}

bool gameover() {
    int n, i, j, k, l;

    if ((game_cycle >= game_limit) && (game_limit > 0)) {
        return true;
        exit(0);
    }
    if ((game_cycle & 31) == 0) {
        k = 0;
        for (n = 0; n < num_robots; n++) {
            if (robot[n].armor > 0) {
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

bool invalid_microcode(int n, int ip) {
    bool invalid;
    int i, j, k;

    invalid = false;
    for (i = 0; i <= 2; i++) {
        k = (robot[n].code[ip].op[max_op] >> (i << 2)) & 7;
        if ((k != 1) && (k != 2) && (k != 3) && (k != 4)) {
            invalid = true;
        }
    }
    return invalid;
}

void execute_instruction(int n) {
    int i, j, k, time_used, loc;
    bool inc_ip;
    char c;

    robot[n].ram[0] = robot[n].tspd;
    robot[n].ram[1] = robot[n].thd;
    robot[n].ram[2] = robot[n].shift;
    robot[n].ram[3] = robot[n].accuracy;

    time_used = 1;
    inc_ip = true;
    loc = 0;
    if ((robot[n].ip > robot[n].plen) || (robot[n].ip < 0)) {
        robot[n].ip = 0;
    }
    if (invalid_microcode(n, robot[n].ip)) {
        time_used = 1;
        robot_error(n, 16, atr2func::hex(robot[n].code[robot[n].ip].op[max_op]));
    }

    if ((graphix) && (step_mode > 0) && (n == 0)) {
        //graphix stuff
    }

    if(((robot[n].code[robot[n].ip].op[max_op] & 7) == 0) || ((robot[n].code[robot[n].ip].op[max_op] & 7) == 1)) {
        time_used = 0;
    } else {
        switch (get_val(n, robot[n].ip, 0)) {
            case 0: //NOP
                executed++;
                break;
            case 1: //ADD
                put_val(n, robot[n].ip, 1, get_val(n, robot[n].ip, 1) + get_val(n, robot[n].ip, 2));
                executed++;
                break;
            case 2: //SUB
                put_val(n, robot[n].ip, 1, get_val(n, robot[n].ip, 1) - get_val(n, robot[n].ip, 2));
                executed++;
                break;
            case 3: //OR
                put_val(n, robot[n].ip, 1, get_val(n, robot[n].ip, 1) | get_val(n, robot[n].ip, 2));
                executed++;
                break;
            case 4: //AND
                put_val(n, robot[n].ip, 1, get_val(n, robot[n].ip, 1) & get_val(n, robot[n].ip, 2));
                executed++;
                break;
            case 5: //XOR
                put_val(n, robot[n].ip, 1, get_val(n, robot[n].ip, 1) ^ get_val(n, robot[n].ip, 2));
                executed++;
                break;
            case 6: //NOT
                put_val(n, robot[n].ip, 1, !get_val(n, robot[n].ip, 1));
                executed++;
                break;
            case 7: //MPY
                put_val(n, robot[n].ip, 1, get_val(n, robot[n].ip, 1) * get_val(n, robot[n].ip, 2));
                time_used = 10;
                executed++;
                break;
            case 8: //DIV
                j = get_val(n, robot[n].ip, 2);
                if (j != 0) {
                    put_val(n, robot[n].ip, 1, (int)(get_val(n, robot[n].ip, 1) / j));
                } else {
                    robot_error(n, 8, "");
                }
                time_used = 10;
                executed++;
                break;
            case 9: //MOD
                j = get_val(n, robot[n].ip, 2);
                if (j != 0) {
                    put_val(n, robot[n].ip, 1, get_val(n, robot[n].ip, 1) % j);
                } else {
                    robot_error(n, 8, "");
                }
                time_used = 10;
                executed++;
                break;
            case 10: //RET
                robot[n].ip = pop(n);
                if ((robot[n].ip < 0) || (robot[n].ip > robot[n].plen)) {
                    robot_error(n, 7, atr2func::cstr(robot[n].ip));
                }
                executed++;
                break;
            case 11: //GSB
                loc = find_label(n, get_val(n, robot[n].ip, 1), robot[n].code[robot[n].ip].op[max_op] >> (1*4));
                if (loc >= 0) {
                    push(n, robot[n].ip);
                    inc_ip = false;
                } else {
                    robot_error(n, 2, atr2func::cstr(get_val(n, robot[n].ip, 1)));
                }
                executed++;
                break;
            case 12: //JMP
                jump(n, 1, inc_ip);
                executed++;
                break;
            case 13: //JLS,JB
                if ((robot[n].ram[64] & 2) > 0) {
                    jump(n, 1, inc_ip);
                }
                time_used = 0;
                executed++;
                break;
            case 14: //JGR,JA
                if ((robot[n].ram[64] & 4) > 0) {
                    jump(n, 1, inc_ip);
                }
                time_used = 0;
                executed++;
                break;
            case 15: //JNE
                if ((robot[n].ram[64] & 1) == 0) {
                    jump(n, 1, inc_ip);
                }
                time_used = 0;
                executed++;
                break;
            case 16: //JEQ,JE
                if ((robot[n].ram[64] & 1) > 0) {
                    jump(n, 1, inc_ip);
                }
                time_used = 0;
                executed++;
                break;
            case 17: //SWAP, XCHG
                robot[n].ram[4] = get_val(n, robot[n].ip, 1);
                put_val(n, robot[n].ip, 1, get_val(n, robot[n].ip, 2));
                put_val(n, robot[n].ip, 2, robot[n].ram[4]);
                time_used = 3;
                executed++;
                break;
            case 18: //DO
                robot[n].ram[67] = get_val(n, robot[n].ip, 1);
                executed++;
                break;
            case 19: //LOOP
                robot[n].ram[67]--;
                if (robot[n].ram[67] > 0) {
                    jump(n, 1, inc_ip);
                }
                executed++;
                break;
            case 20: //CMP
                k = get_val(n, robot[n].ip, 1) - get_val(n, robot[n].ip, 2);
                robot[n].ram[64] = robot[n].ram[64] & 65520;
                if (k == 0) {
                    robot[n].ram[64] = robot[n].ram[64] | 1;
                }
                if (k < 0) {
                    robot[n].ram[64] = robot[n].ram[64] | 2;
                }
                if (k > 0) {
                    robot[n].ram[64] = robot[n].ram[64] | 4;
                }
                if ((get_val(n, robot[n].ip, 2) == 0) && (k == 0)) {
                    robot[n].ram[64] = robot[n].ram[64] | 8;
                }
                executed++;
                break;
            case 21: //TEST
                k = get_val(n, robot[n].ip, 1) & get_val(n, robot[n].ip, 2);
                robot[n].ram[64] = robot[n].ram[64] & 65520;
                if (k == get_val(n, robot[n].ip, 2)) {
                    robot[n].ram[64] = robot[n].ram[64] | 1;
                }
                if (k == 0) {
                    robot[n].ram[64] = robot[n].ram[64] | 8;
                }
                executed++;
                break;
            case 22: //MOV, SET
                put_val(n, robot[n].ip, 1, get_val(n, robot[n].ip, 2));
                executed++;
                break;
            case 23: //LOC
                put_val(n, robot[n].ip, 1, robot[n].code[robot[n].ip].op[2]);
                time_used = 2;
                executed++;
                break;
            case 24: //GET
                k = get_val(n, robot[n].ip, 2);
                if ((k >= 0) && (k <= max_ram)) {
                    put_val(n, robot[n].ip, 1, robot[n].ram[k]);
                } else if ((k > max_ram) && (k <= ((max_ram + 1) + (((max_code + 1) << 3) - 1)))) {
                    j = k - max_ram - 1;
                    put_val(n, robot[n].ip, 1, robot[n].code[j >> 2].op[j & 3]);
                } else {
                    robot_error(n, 4, atr2func::cstr(k));
                }
                time_used = 2;
                executed++;
                break;
        }
        robot[n].delay_left = robot[n].delay_left + time_used;
        if (inc_ip) {
            robot[n].ip++;
        }
        if ((graphix) && (n ==0) && (step_mode > 0)) {
            //update_debug_window();
        }
    }
}

void do_robot(int n) {
    int i, j, k, l, tthd;
    double heat_mult, ttx, tty;

    if ((n < 0) || (n > num_robots)) {
        return;
    }

    if (robot[n].armor <= 0) {
        return;
    }

    //time slice
    robot[n].time_left = time_slice;
    if ((robot[n].time_left > robot[n].robot_time_limit) && (robot[n].robot_time_limit > 0)) {
        robot[n].time_left = robot[n].robot_time_limit;
    }
    if ((robot[n].time_left > robot[n].max_time) && (robot[n].max_time > 0)) {
        robot[n].time_left = robot[n].max_time;
    }
    executed = 0;

    //execute timeslice
    while ((robot[n].time_left > 0) && (!robot[n].cooling) && (executed < (20 + time_slice))) {
        if (robot[n].delay_left < 0) {
            robot[n].delay_left = 0;
        }
        if (robot[n].delay_left > 0) {
            robot[n].delay_left--;
            robot[n].time_left--;
        }
        if ((robot[n].time_left >= 0) && (robot[n].delay_left == 0)) {
            execute_instruction(n);
        }
        if (robot[n].heat >= robot[n].shutdown) {
            robot[n].cooling = true;
            robot[n].shields_up = false;
        }
        if (robot[n].heat >= 500) {
            damage(n, 1000, true);
        }
    }

    //fix up variables
    robot[n].thd = (robot[n].thd + 1024) & 255;
    robot[n].hd = (robot[n].hd + 1024) & 255;
    robot[n].shift = (robot[n].shift + 1024) & 255;
    if (robot[n].tspd < -75) {
        robot[n].tspd = -75;
    }
    if (robot[n].tspd > 100) {
        robot[n].tspd = 100;
    }
    if (robot[n].spd < -75) {
        robot[n].spd = -75;
    }
    if (robot[n].spd > 100) {
        robot[n].spd = 100;
    }
    if (robot[n].heat < 0) {
        robot[n].heat = 0;
    }
    if (robot[n].last_damage < maxint) {
        robot[n].last_damage++;
    }
    if (robot[n].last_hit < maxint) {
        robot[n].last_hit;
    }

    //update heat
    if (robot[n].shields_up && ((game_cycle & 3) == 0)) {
        robot[n].heat++;
    }
    if (!robot[n].shields_up) {
        if (robot[n].heat > 0) {
            switch(robot[n].config.heatsinks) {
                case 5:
                    if ((game_cycle & 1) == 0) {
                        robot[n].heat--;
                    }
                    break;
                case 4:
                    if ((game_cycle % 3) == 0) {
                        robot[n].heat--;
                    }
                    break;
                case 3:
                    if ((game_cycle & 3) == 0) {
                        robot[n].heat--;
                    }
                    break;
                case 2:
                    if ((game_cycle & 7) == 0) {
                        robot[n].heat--;
                    }
                    break;
                case 1:
                    break;
                default:
                    if ((game_cycle & 3) == 0) {
                        robot[n].heat++;
                    }
            }
        }
        if ((robot[n].overburn) && ((game_cycle % 3) == 0)) {
            robot[n].heat++;
        }
        if (robot[n].heat > 0) {
            robot[n].heat--;
        }
        if ((robot[n].heat > 0) && ((game_cycle & 7) == 0) && (abs(robot[n].tspd) <= 25)) {
            robot[n].heat--;
        }
        if ((robot[n].heat <= (robot[n].shutdown - 50)) || (robot[n].heat <= 0)) {
            robot[n].cooling = false;
        }
    }
    if (robot[n].cooling) {
        robot[n].tspd = 0;
    }
    heat_mult = 1;
    switch(robot[n].heat) {
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
        case 250 ... maxint:
            heat_mult = 0.50;
            break;
    }
    if (robot[n].overburn) {
        heat_mult = heat_mult * 1.30;
    }
    if ((robot[n].heat >= 475) && ((game_cycle & 3) == 0)) {
        damage(n, 1, true);
    } else if ((robot[n].heat >= 450) && ((game_cycle & 7) == 0)) {
        damage(n, 1, true);
    } else if ((robot[n].heat >= 400) && ((game_cycle & 15) == 0)) {
        damage(n, 1, true);
    } else if ((robot[n].heat >= 350) && ((game_cycle & 31) == 0)) {
        damage(n, 1, true);
    } else if ((robot[n].heat >= 300) && ((game_cycle & 63) == 0)) {
        damage(n, 1, true);
    }

    //update robot in physical world
    //acceleration
    if (abs(robot[n].spd - robot[n].tspd) <= acceleration) {
        robot[n].spd = robot[n].tspd;
    } else {
        if (robot[n].tspd > robot[n].spd) {
            robot[n].spd = robot[n].spd + acceleration;
        } else {
            robot[n].spd = robot[n].spd - acceleration;
        }
    }

    //turning
    tthd = robot[n].hd + robot[n].shift;
    if ((abs(robot[n].hd - robot[n].thd) <= turn_rate) || (abs(robot[n].hd - robot[n].thd >= (256-turn_rate)))) {
        robot[n].hd = robot[n].thd;
    } else if (robot[n].hd != robot[n].thd) {
        k = 0;
        if (((robot[n].thd > robot[n].hd) && (abs(robot[n].hd - robot[n].thd) <= 128)) || ((robot[n].thd < robot[n].hd) && (abs(robot[n].hd - robot[n].thd) >= 128))) {
            k = 1;
        }
        if (k == 1) {
            robot[n].hd = (robot[n].hd + turn_rate) & 255;
        } else {
            robot[n].hd = (robot[n].hd + 256 - turn_rate) & 255;
        }
    }
    robot[n].hd = robot[n].hd & 255;
    if (robot[n].keepshift) {
        robot[n].shift = (tthd - robot[n].hd + 1024) & 255;
    }

    //moving
    robot[n].speed = robot[n].spd / 100 * (max_vel * heat_mult * robot[n].speedadj);
    robot[n].xv = atr2func::sint[robot[n].hd] * robot[n].speed;
    robot[n].yv = -(atr2func::cost[robot[n].hd]) * robot[n].speed;
    if ((robot[n].hd == 0) || (robot[n].hd == 128)) {
        robot[n].xv = 0;
    }
    if ((robot[n].hd == 64) || (robot[n].hd == 192)) {
        robot[n].yv = 0;
    }
    if (robot[n].xv != 0) {
        ttx = robot[n].x + robot[n].xv;
    } else {
        ttx = robot[n].x;
    }
    if (robot[n].yv != 0) {
        tty = robot[n].y + robot[n].yv;
    } else {
        tty = robot[n].y;
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
    robot[n].meters = robot[n].meters + atr2func::distance(robot[n].x, robot[n].y, ttx, tty);
    if (robot[n].meters >= maxint) {
        robot[n].meters = robot[n].meters - maxint;
    }
    robot[n].ram[9] = (int)trunc(robot[n].meters);
    robot[n].x = ttx;
    robot[n].y = tty;

    //draw robot
    if (robot[n].armor < 0) {
        robot[n].armor = 0;
    }
    if (robot[n].heat < 0) {
        robot[n].heat = 0;
    }
    if (graphix) {
        if (robot[n].armor != robot[n].larmor) {
            update_armor(n);
        }
        if ((int)(robot[n].heat / 5) != (int)(robot[n].lheat / 5)) {
            update_heat(n);
        }
        draw_robot(n);
    }
    robot[n].lheat = robot[n].heat;
    robot[n].larmor = robot[n].armor;

    //Cycle complete, inc counter
    robot[n].cycles_lived++;
}

void do_mine(int n, int m) {

}

void do_missile(int n) {

}

string victor_string(int k, int n) {
    string s;

    s.clear();
    if (k == 1) {
        s = "Robot #" + atr2func::cstr(n+1) + " (" + robot[n].fn + ") wins!";
    }
    if (k == 0) {
        s = "Simultaneous destruction, match is a tie.";
    }
    if (k > 1) {
        s = "No clear victor, match is a tie.";
    }

    return s;
}

void show_statistics() {
    int i, j, k, n, sx, sy;

    if (!windoze) {
        return;
    }
    if (graphix) {

    } else {
        //textcolor(15);
        cout << endl << atr2func::space(79) << endl;
        cout << "Match " << played << "/" << matches << " results:" << endl << endl;
        cout << "Robot            Scored   Wins  Matches  Armor  Kills  Deaths    Shots" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        n = -1;
        k = 0;
        for (i = 0; i < num_robots; i++) {
            if ((robot[i].armor > 0) || (robot[n].won)) {
                k++;
                n = i;
            }
        }
        for (i = 0; i < num_robots; i++) {
            //textcolor(robotcolor(i));
            if ((k == 1) && (n == i)) {
                j = 1;
            } else {
                j = 0;
            }
            cout << atr2func::addfront(atr2func::cstr(i+1), 2) << " - " << atr2func::addrear(robot[i].fn, 15) << atr2func::cstr(j)
                 << atr2func::addfront(atr2func::cstr(robot[i].wins), 8) << atr2func::addfront(atr2func::cstr(robot[i].trials), 8)
                 << atr2func::addfront(atr2func::cstr(robot[i].armor) + "%", 9) << atr2func::addfront(atr2func::cstr(robot[i].kills), 7)
                 << atr2func::addfront(atr2func::cstr(robot[i].deaths), 8) << atr2func::addfront(atr2func::cstr(robot[i].match_shots), 9)
                 << endl;
        }
        //textcolor(15);
        cout << endl;
        cout << victor_string(k, n);
        cout << endl;
    }
}

void init_bout() {
    int i, j, k;

    game_cycle = 0;
    for (i = 0; i < max_missiles; i++) {
        missile[i].a = 0;
        missile[i].source = -1;
        missile[i].x = 0;
        missile[i].y = 0;
        missile[i].lx = 0;
        missile[i].ly = 0;
        missile[i].mult = 1;
    }
    for (i = 0; i < num_robots; i++) {
        robot[i].mem_watch = 128;
        reset_hardware(i);
        reset_software(i);
    }
    if (graphix) {
        //setscreen();
    }
    if (graphix && (step_mode > 0)) {
        //init_debug_window();
    }
    if (!graphix) {
        //textcolor(7);
        //There is some commented "battle in progress" text here...
    }
}

void bout() {
    int i, j, k, n;
    char c;
    long timer;

    if(quit) {
        exit(0);
    }

    played++;
    init_bout();
    bout_over = false;

    if (step_mode == 0) {
        step_loop = false;
    } else {
        step_loop = true;
    }
    step_count = -1;
    if (graphix && (step_mode > 0)) {
        for (i = 0; i < num_robots; i++) {
            //draw_robot(i);
        }
    }

    do {
        game_cycle++;
        for (i = 0; i < num_robots; i++) {
            if (robot[i].armor > 0) {
                do_robot(i);
            }
        }
        for (i = 0; i < max_missiles; i++) {
            if (missile[i].a > 0) {
                do_missile(i);
            }
        }
        for (i = 0; i < num_robots; i++) {
            for (k = 0; k < max_mines; k++) {
                if (robot[i].mine[k].yield > 0) {
                    do_mine(i, k);
                }
            }
        }

        if (graphix && timing) {
            //time_delay(game_delay);
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
        if (game_delay < 0) {
            game_delay = 0;
        }
        if (game_delay > 100) {
            game_delay = 100;
        }

        switch(game_delay) {
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
            case 71 ... maxint:
                k = 1;
            default:
                k = 10;
        }

        if (!graphix) {
            k = 100;
        }
        /*if (graphix) {
            if (((game_cycle % k) == 0) || (game_cycle == 10)) {
                update_cycle_window();
            } else {
                if (update_timer != mem[0:$46C] >> 1) {
                    update_cycle_window();
                }
                update_timer = mem[0:$46C] >> 1;
            }
        }*/
    } while (!(quit || gameover() || bout_over));

    //update_cycle_window();
    //score_robots();
    //show_statistics();
}

void begin_window() {

}