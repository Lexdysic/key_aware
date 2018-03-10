
#include <stdint.h>


namespace key_aware {

class StringView {
public:
    StringView () noexcept = default;
    StringView (const StringView &) noexcept = default;
    inline StringView (const char * str) noexcept;
    inline StringView (const char * str, const int32_t length) noexcept :
        m_ptr(str),
        m_length(length)
    {
    }

    StringView & operator= (const StringView &) noexcept = default;

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

int32_t Distance (const StringView & from, const StringView & to);

} // namespace key_aware