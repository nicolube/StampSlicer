#include <formats/cbddlp/FormatCbddlp.hpp>
#include <cstring>

using namespace formats::cbddlp;

void FormatCbddlp::load(char *data, size_t length) {
    std::memcpy(&header, data, sizeof(cbddlp_file_head_t));
}