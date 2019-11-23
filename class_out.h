#pragma once

#include <iostream>
#include <list>

#include "user_types.h"

class out_base {
public:
    virtual ~out_base() = default;
    virtual void write(cmd_list_t str) = 0;
};

class report;

class log_out : out_base {
public:
    log_out(report * rp);
    void write(cmd_list_t val) override {
        std::cout << "log: " << __FUNCTION__ << ": ";
        for(const auto & el : val)
         std::cout << el << " ";
        std::cout << std::endl;
    }
};

class write_out : out_base {
public:
    write_out(report * rp);
    void write(cmd_list_t val) override {
        std::cout << "file: " << __FUNCTION__ << ": " << std::endl;
        for(const auto & el : val)
            std::cout << el << std::endl;
        std::cout << "end of file" << std::endl;
    }
};

class report {
    std::list<out_base *> subs;
public:
    void subscribe(out_base * ptr) {
        subs.push_back(ptr);
    }
    void notify_all(cmd_list_t val) {
        for(auto & el : subs) {
            el->write(val);
        }
    }
};

log_out::log_out(report * rp) {
    rp->subscribe(this);
}

write_out::write_out(report * rp) {
    rp->subscribe(this);
}
