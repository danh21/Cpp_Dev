#include <iostream>
#include "Header.h"

// ---- helpers ----
void printStatus(const char* label, const CFileStatus& s)
{
    std::cout << "\n--- " << label << " ---\n";
    std::cout << "  m_ctime    = " << s.m_ctime.GetTime() << "\n";
    std::cout << "  m_mtime    = " << s.m_mtime.GetTime() << "\n";
    std::cout << "  m_atime    = " << s.m_atime.GetTime() << "\n";
    std::cout << "  m_size     = " << s.m_size << "\n";
    std::cout << "  m_attribute= " << s.m_attribute << "\n";
    std::cout << "  m_szFullName[0] = " << (int)s.m_szFullName[0] << "\n";
}

void setMockData(CFileStatus& s)
{
    s.m_ctime = (time_t)1718000000;
    s.m_mtime = (time_t)1718000001;
    s.m_atime = (time_t)1718000002;
    s.m_size = 4096;
    s.m_attribute = 0x20;
    s.m_szFullName[0] = 'C';
    s.m_szFullName[1] = '\0';
}

int main()
{
    // -------------------------------------------------------
    // CASE 1: memset
    // -------------------------------------------------------
    std::cout << "\n========== CASE 1: memset ==========\n";
    {
        CFileStatus rStatus;
        setMockData(rStatus);
        printStatus("before reset", rStatus);

        std::cout << "\ncalling memset...\n";
        // NOTE: no CTime constructor called here — raw bytes only
        memset(&rStatus, 0, sizeof(CFileStatus));

        printStatus("after memset", rStatus);
        // m_time bytes are 0, but CTime() was never called ->  UB on method call
        // — safe here only because CTime has no vtable / non-trivial layout
    }

    // -------------------------------------------------------
    // CASE 2: rStatus = CFileStatus()
    // -------------------------------------------------------
    std::cout << "\n========== CASE 2: CFileStatus() ==========\n";
    {
        CFileStatus rStatus;
        setMockData(rStatus);
        printStatus("before reset", rStatus);

        std::cout << "\ncalling rStatus = CFileStatus() - watch constructors fire:\n";
        rStatus = CFileStatus();   // CTime() called for each CTime member

        printStatus("after CFileStatus()", rStatus);
    }

    return 0;
}