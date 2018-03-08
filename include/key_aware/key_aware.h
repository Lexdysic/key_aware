
#include <stdint.h>
#include <string_view>


namespace key_aware {

void Init ();
void Shutdown ();

int32_t Distance (const std::string_view & from, const std::string_view & to);

} // namespace key_aware