
#include <stdint.h>
#include <map>
#include <set>


namespace key_aware {
//
// StringView
//
class StringView {
public:
    StringView () noexcept = default;
    StringView (const StringView &) noexcept = default;
    StringView (const char * str) noexcept;
    inline StringView (const char * str, const int32_t length) noexcept :
        m_ptr(str),
        m_length(length)
    {
    }

    StringView & operator= (const StringView &) noexcept = default;
    
    inline const char * Ptr () const noexcept {
        return m_ptr;
    }

    inline int32_t Length () const noexcept {
        return m_length;
    }

    inline const char & operator[] (const int32_t index) const noexcept {
        return m_ptr[index];
    }

private:
    const char * m_ptr    = nullptr;
    int32_t      m_length = 0;
};


//
// Trie
// 
class Trie {
public:

    void Add (const StringView & str);

    void Search (const StringView & prefix, std::set<std::string> * output);

    inline int32_t GetCount () const { return m_count; }
    inline bool IsEmpty () const { return !m_count; }

private:
    struct Node {
        std::string            value;
        std::map<char, Node *> children;
    };

    Node    m_root;
    int32_t m_count = 0;
};


//
// API
//
int32_t Distance (const StringView & from, const StringView & to);

} // namespace key_aware