#include <catch/catch.hpp>

#include <key_aware/key_aware.h>

TEST_CASE("Simple Test", "[distance]") {
    CHECK(key_aware::Distance("filr", "file") == 1);
    CHECK(key_aware::Distance("filr", "film") == 2);
    CHECK(key_aware::Distance("filr", "fill") == 2);
}
