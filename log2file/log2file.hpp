#ifndef LOG2FILE_H
#define LOG2FILE_H

#include <fstream>
#include <mutex>

class Log2File
{
    public:
        Log2File(const std::string _dirpath, bool _overwirte);
        ~Log2File();
        bool writable();
        int reset(const std::string _name);
        bool test_exist(const std::string _name);
        int write(const std::string msg);
    protected:
        std::fstream fs;
        std::string dirPath;
        std::string name;
        bool can_overwrite;
    private:
        std::mutex mtxWrite; // beware of deadlock
};

std::string clock2logname();
#define WRITE2LOG(x, msg) (x).write((msg))
#endif
