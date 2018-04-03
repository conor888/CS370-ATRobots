//
// Created by conor on 3/21/2018.
//

#ifndef ATR2_H
#define ATR2_H

#include "atr2var.h"
#include "arena.h"
#include <QThread>
#include "atr2func.h"
#include <QEventLoop>
#include <QObject>

class arena;

class atr2 {
public:
    atr2(atr2var* avtemp, arena* parent);
    atr2(atr2var* avtemp, arena* parent, QEventLoop* loopy);

    std::string operand(int n, int m);
    std::string mnemonic(int n, int m);
    void log_error(int n, int i, std::string ov);
    int max_shown();
    //bool graph_check(int n);
    //void robot_graph(int n);
    void update_armor(int n);                       //Not done
    void update_heat(int n); //Not done
    void robot_error(int n, int i, std::string ov);      //Not done
    void update_lives(int n);                       //Not done
    //void update_cycle_window();
    //void setscreen();
    //void graph_mode(bool on);
    void prog_error(int n, std::string ss);
    void print_code(int n, int p);
    void parse1(int n, int p, atr2var::parsetype s);
    void check_plen(int plen);
    void compile(int n, std::string filename);
    void robot_config(int n);
    void reset_software(int n);
    void reset_hardware(int n);
    void init_robot(int n);
    void create_robot(int n, std::string filename);
    void shutdown();
    void delete_compile_report();                   //Skipped
    void write_compile_report();
    void parse_param(std::string s);
    void init(int argc, std::string argv[]);
    void draw_robot(int n);                         //Not done
    int get_from_ram(int n, int i, int j);
    int get_val(int n, int c, int o);
    void put_val(int n, int c, int o, int v);
    void push(int n, int v);
    int pop(int n);
    int find_label(int n, int l, int m);
    void init_mine(int n, int detectrange, int size);
    int count_missiles();
    void init_missile(double xx, double yy, double xxv, double yyv, int dir, int s, int blast, bool ob);
    void damage(int n, int d, bool physical);
    int scan(int n);
    void com_transmit(int n, int chan, int data);
    int com_receive(int n);
    int16_t in_port(int n, int p, int &time_used);
    void out_port(int n, int p, int v, int &time_used);
    void call_int(int n, int int_num, int &time_used);
    void jump(int n, int o, bool &inc_ip);
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
    void do_missile(int n);
    std::string victor_string(int k, int n);
    void show_statistics();
    void score_robots();
    void init_bout();
    void bout();
    void write_report();
    void begin_window();                            //Not done
    
private:
    atr2var *av;
    arena *atr2a;
    //QEventLoop *loop;
};

class WorkerThread : public QThread
{
Q_OBJECT
public:
    //QEventLoop *loop;

    WorkerThread(atr2var* avtemp, int argctemp, std::string argvtemp[], arena* parent) {
        av = avtemp;
        argc = argctemp;
        argv = argvtemp;
        atr2a = parent;

        //loop = new QEventLoop();

        //QObject::connect(parent, SIGNAL(donePainting()), loop, SLOT(quit()));
    }

    void run() override {
        //atr2 atr2(av, atr2a, loop);
        atr2 atr2(av, atr2a);

        atr2.init(argc, argv);

        int i, j, k, l, n, w;

        if(av->graphix) {
            atr2.begin_window();
        }
        if(av->matches > 0) {
            for (i = 0; i < av->matches; i++) {
                atr2.bout();
            }
        }
        if(!av->graphix) {
            std::cout << std::endl;
        }
        if(av->quit) {
            exit(0);
        }
        if(av->matches > 1) {
            std::cout << std::endl << std::endl;
            //graph_mode(false);
            //textcolor(15);
            std::cout << "Bout complete! (" << av->matches << " av.matches)" << std::endl;
            k = 0;
            w = 0;
            for (i = 0; i < av->num_robots; i++) {
                if (av->robot[i].wins == w) {
                    k++;
                }
                if (av->robot[i].wins > w) {
                    k = 1;
                    n = i;
                    w = av->robot[i].wins;
                }
            }
            std::cout << "Robot           Wins  Matches  Kills  Deaths    Shots" << std::endl;
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            for (i = 0; i < av->num_robots; i++) {
                //textcolor(robot_color(i));
                std::cout << atr2func::addfront(atr2func::cstr(i+1), 2) << " - " << atr2func::addrear(av->robot[i].fn, 8)
                          << atr2func::addfront(atr2func::cstr(av->robot[i].wins), 7) << atr2func::addfront(atr2func::cstr(av->robot[i].trials), 8)
                          << atr2func::addfront(atr2func::cstr(av->robot[i].kills), 8) << atr2func::addfront(atr2func::cstr(av->robot[i].deaths), 8)
                          << atr2func::addfront(atr2func::cstr(av->robot[i].shots_fired), 9) << std::endl;
            }
            //textcolor(15);
            std::cout << std::endl;
            if (k == 1) {
                std::cout << "Robot #" << n + 1 << " (" << av->robot[n].fn << ") wins the bout! (score: " << w << "/" << av->matches << ")" << std::endl;
            } else {
                std::cout << "There is no clear victor!" << std::endl;
            }
            std::cout << std::endl;
        } else if (av->graphix) {
            //graph_mode(false);
            //show_statistics();
        }
        if (av->report) {
            atr2.write_report();
        }

        atr2.shutdown();
        //emit resultReady(0);
    }
signals:
    //void resultReady(int r);
private:
    int argc;
    atr2var *av;
    arena *atr2a;
    std::string *argv;
};


#endif //ATR2_H
