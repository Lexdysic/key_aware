
#include <stdint.h>
#include <string_view>

namespace key_aware {

class StringView {
public:
    StringView () noexcept :
        m_ptr(nullptr),
        m_length(0)
    {
    }

    StringView (const char * str) noexcept :
        m_ptr(str),
        m_length((int32_t)strlen(str))
    {
    }

    StringView (const char * str, const int32_t length) noexcept :
        m_ptr(str),
        m_length(length)
    {
    }

    StringView (const StringView &) noexcept = default;
    StringView & operator= (const StringView &) noexcept = default;

    int32_t Length () const noexcept {
        return m_length;
    }

    const char * Ptr () const noexcept {
        return m_ptr;
    }

    const char & operator[] (const int32_t index) const noexcept {
        return m_ptr[index];
    }

private:
    const char * m_ptr;
    int32_t      m_length;
};

int32_t Distance (const StringView & from, const StringView & to);

} // namespace key_aware