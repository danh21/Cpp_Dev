#pragma once

#include <iostream>
#include <cstring>
#include <ctime>
#include <sys/stat.h>

// ---- Minimal CTime mock ----
class CTime
{
public:
    CTime() {
        std::cout << "  [CTime::CTime()] called, m_time = " << m_time << std::endl;
    }
    CTime(time_t t) : m_time(t) {
        std::cout << "  [CTime::CTime(time_t t)] called, m_time = " << m_time << std::endl;
    }

    const CTime& operator=(time_t t) {
        m_time = t;
        return *this;
    }

    time_t GetTime() const { return m_time; }

private:
    time_t m_time;
};

// ---- CFileStatusCD ----
struct CFileStatusCD
{
    CTime       m_ctime;
    CTime       m_mtime;
    CTime       m_atime;
    unsigned long m_size;
    unsigned int       m_attribute;
    char               m_szFullName[260];
};

typedef CFileStatusCD CFileStatus;