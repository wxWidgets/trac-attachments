/////////////////////////////////////////////////////////////////////////////
// Class to hold wxZipEntry's Extra and LocalExtra fields

class wxZipMemory
{
public:
    wxZipMemory() : m_data(NULL), m_size(0), m_capacity(0), m_ref(1) { }

    wxZipMemory *AddRef() { m_ref++; return this; }
    void Release() { if (--m_ref == 0) delete this; }

    char *GetData() const { return m_data; }
    size_t GetSize() const { return m_size; }
    size_t GetCapacity() const { return m_capacity; }

    wxZipMemory *Unique(size_t size);

private:
    ~wxZipMemory() { delete[] m_data; }

    char *m_data;
    size_t m_size;
    size_t m_capacity;
    int m_ref;
};


 	  	 
