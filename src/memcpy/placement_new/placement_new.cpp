#include <iostream>
#include <cstring>
#include <string>

// Minimal CString mock
struct CString {
    char* m_pchData;

    CString() : m_pchData(nullptr) {}

    CString(const char* str) {
        m_pchData = new char[strlen(str) + 1];
        strcpy(m_pchData, str);
    }

    // copy constructor — deep copy
    CString(const CString& src) {
        if (src.m_pchData) {
            m_pchData = new char[strlen(src.m_pchData) + 1];
            strcpy(m_pchData, src.m_pchData);
        }
        else {
            m_pchData = nullptr;
        }
    }

    // operator= — deep copy
    CString& operator=(const CString& src) {
        if (this != &src) {
            delete[] m_pchData;
            if (src.m_pchData) {
                m_pchData = new char[strlen(src.m_pchData) + 1];
                strcpy(m_pchData, src.m_pchData);
            }
            else {
                m_pchData = nullptr;
            }
        }
        return *this;
    }

    ~CString() {
        delete[] m_pchData;
        m_pchData = nullptr;
    }

    const char* GetBuffer() const { return m_pchData ? m_pchData : ""; }
};

void DestructElements(CString* p, int n) {
    for (int i = 0; i < n; ++i)
        p[i].~CString();
}

int main() {
    const int m_nSize = 3;

    // --- mock m_pData ---
    CString* m_pData = (CString*) new unsigned char[m_nSize * sizeof(CString)];
    /*for (int i = 0; i < m_nSize; ++i)
        ::new (&m_pData[i]) CString("hello\0world\0foobar" + i * 6);*/

    ::new (&m_pData[0]) CString("hello");
    ::new (&m_pData[1]) CString("world");
    ::new (&m_pData[2]) CString("foobar");

    std::cout << "=== Source m_pData ===\n";
    for (int i = 0; i < m_nSize; ++i)
        printf("  m_pData[%d] = \"%s\"  ptr=%p\n", i, m_pData[i].GetBuffer(), m_pData[i].m_pchData);

    // -------------------------------------------------------
    // S2: placement new
    // -------------------------------------------------------
    std::cout << "\n--- S2: placement new ---\n";

    CString* pNewData = (CString*) new unsigned char[m_nSize * sizeof(CString)];

    for (int i = 0; i < m_nSize; ++i)
        ::new (&pNewData[i]) CString(m_pData[i]);   // deep copy

    std::cout << "pNewData after placement new:\n";
    for (int i = 0; i < m_nSize; ++i)
        printf("  pNewData[%d] = \"%s\"  ptr=%p  src_ptr=%p  (same: %s)\n",
            i,
            pNewData[i].GetBuffer(),
            pNewData[i].m_pchData,
            m_pData[i].m_pchData,
            pNewData[i].m_pchData == m_pData[i].m_pchData ? "YES — BUG" : "no -> correct");

    DestructElements(pNewData, m_nSize);    // call ~CString on each
    delete[](unsigned char*) pNewData;
    std::cout << "  => Destructors called. All inner buffers freed. No leak.\n";

    // cleanup source
    DestructElements(m_pData, m_nSize);
    delete[](unsigned char*) m_pData;

    return 0;
}