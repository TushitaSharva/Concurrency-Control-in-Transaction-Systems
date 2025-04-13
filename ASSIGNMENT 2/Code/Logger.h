#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <chrono>

class Logger
{
public:
    int x = 0; // 1: mvto, 2: gc, 3: kmvto, 0: bto
    // Function to convert time_point to a formatted string
    std::string TIME(const std::chrono::high_resolution_clock::time_point& tp)
    {
        auto time_t = std::chrono::high_resolution_clock::to_time_t(tp);
        std::tm* tm = std::localtime(&time_t); // Convert to local time
        char buffer[100];
        std::strftime(buffer, sizeof(buffer), "%H:%M:%S", tm);
        return std::string(buffer);
    }

    template<typename... Args>
    void DEBUG(Args... args)
    {
        std::string filename = "debugs/";
        switch (x)
        {
        case 1:
            filename += "mvto-log.txt";
            break;
        case 2:
            filename += "mvto-gc-log.txt";
            break;
        case 3:
            filename += "k-mvto-log.txt";
            break;
        default:
            filename += "bto-log.txt";
        }
        std::ofstream debugfile(filename, std::ios::app);
        std::ostringstream oss;
        (oss << ... << args);  // Use fold expression to stream all arguments
        debugfile << oss.str() << "\n";
        debugfile.close();
    }

    template<typename... Args>
    void OUTPUT(Args... args)
    {
        std::string filename = "outputs/";
        switch (x)
        {
        case 1:
            filename += "mvto-log.txt";
            break;
        case 2:
            filename += "mvto-gc-log.txt";
            break;
        case 3:
            filename += "k-mvto-log.txt";
            break;
        default:
            filename += "bto-log.txt";
        }
        std::ofstream outputfile(filename, std::ios::app);
        std::ostringstream oss;
        (oss << ... << args);  // Stream all arguments
        outputfile << oss.str() << "\n";
        outputfile.close();
    }

    template<typename... Args>
    void DEBUGT(Args... args)
    {
        std::string filename = "debug/";
        switch (x)
        {
        case 1:
            filename += "mvto-log.txt";
            break;
        case 2:
            filename += "mvto-gc-log.txt";
            break;
        case 3:
            filename += "k-mvto-log.txt";
            break;
        default:
            filename += "bto-log.txt";
        }
        std::ofstream debugfile(filename, std::ios::app);
        std::ostringstream oss;
        (oss << ... << args);  // Use fold expression to stream all arguments
        debugfile << "[" << TIME(std::chrono::high_resolution_clock::now()) << "] " << oss.str() << "\n";
        debugfile.close();
    }

    template<typename... Args>
    void OUTPUTT(Args... args)
    {
        std::string filename = "outputs/";
        switch (x)
        {
        case 1:
            filename += "mvto-log.txt";
            break;
        case 2:
            filename += "mvto-gc-log.txt";
            break;
        case 3:
            filename += "k-mvto-log.txt";
            break;
        default:
            filename += "bto-log.txt";
        }
        std::ofstream outputfile(filename, std::ios::app);
        std::ostringstream oss;
        (oss << ... << args);  // Stream all arguments
        outputfile << "[" << TIME(std::chrono::high_resolution_clock::now()) << "] " << oss.str() << "\n";
        outputfile.close();
    }
};

#endif