#include "log2file.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <thread>   //this_thread::sleep_for
#include <mutex>
#include <ctime>
#include <sstream>

using namespace std;
using namespace chrono;

Log2File::Log2File(const std::string _dirpath, bool _overwrite)
{
    can_overwrite = _overwrite;
    cout << __func__ << ":" << __LINE__ << endl;
    reset(clock2logname());
    cout << __func__ << ": lalala" << endl;
}

Log2File::~Log2File()
{
    fs.sync();
    fs.close();
}

bool Log2File::writable()
{
    unique_lock<mutex> lk(mtxWrite);
    return fs.good() ? fs.is_open() : false;
}

int Log2File::reset(const std::string _name)
{
    unique_lock<mutex> lk(mtxWrite);
    if(fs.is_open())
    {
        fs.sync();
        fs.close();
    }
    fs.open(_name, ios::out);
    name = _name;
}

bool Log2File::test_exist(const std::string _name)
{
    ifstream tmpfs(_name);
    return tmpfs.good();
}

int Log2File::write(const std::string msg)
{
    unique_lock<mutex> lk(mtxWrite);
    if(!fs.good())
        return -2;
    if(!fs.is_open())
        return -1;
    fs << setiosflags(ios::left) << setw(20);
    fs << duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count()/1000 << resetiosflags(ios::adjustfield) << msg << endl;
    return 0;
}

std::string clock2logname()
{
    time_t result = time(nullptr);
    auto lt = localtime(&result);
    stringstream ss;
    ss << lt->tm_mon+1 << "_";
    ss << lt->tm_mday << "_";
    ss << lt->tm_hour << "_";
    ss << lt->tm_min << "_";
    ss << lt->tm_sec << ".log";
    return ss.str();
}
#if 0
int main()
{
#if 0
    auto tp = steady_clock::now();
    cout << setiosflags(ios::left) << setw(20) << endl;
    cout << duration_cast<microseconds>(tp.time_since_epoch()).count() << "simple test" << endl;
    tp = steady_clock::now();
    this_thread::sleep_for(milliseconds(2000));
    cout << setiosflags(ios::left) << setw(20);
    cout << duration_cast<microseconds>(tp.time_since_epoch()).count() << "simple test" << endl;
#endif
    Log2File lg(".", false);
    cout << clock2logname() << endl;
    for(int i = 0; i < 10; i++)
    {
        int k = 0;
        cin >> k;
        lg.reset(to_string(k) + ".log");
        lg.write(to_string(k));
        lg.write(to_string(k));
        lg.write(to_string(k));
    }
    return 0;
}
#endif
