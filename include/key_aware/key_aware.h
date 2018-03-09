
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
        m_length(strlen(str))
    {
    }

    StringView (const char * str, const size_t length) noexcept :
        m_ptr(str),
        m_length(length)
    {
    }

    StringView (const StringView &) noexcept = default;
    StringView & operator= (const StringView &) noexcept = default;

    size_t Length () const noexcept {
        return m_length;
    }

    const char * Ptr () const noexcept {
        return m_ptr;
    }

    const char & operator[] (const size_t index) const noexcept {
        return m_ptr[index];
    }

private:
    const char * m_ptr;
    size_t       m_length;
};

int32_t Distance (const StringView & from, const StringView & to);

} // namespace key_aware