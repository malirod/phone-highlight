// Copyright [2019] <Malinovsky Rodion> (rodionmalino@gmail.com)
#include "UtfUtilsIcu.h"

#include <stdexcept>
#include <unicode/errorcode.h>
#include <unicode/unistr.h>
#include <vector>

std::u32string rms::UTF8ToUTF32ICU(std::string const& input)
{
    auto unicodeStr = icu::UnicodeString::fromUTF8(input);

    icu::ErrorCode errorCode;
    std::vector<UChar32> utf32(unicodeStr.length());
    unicodeStr.toUTF32(utf32.data(), utf32.size(), errorCode);
    if (errorCode.isFailure() != 0)
        throw std::runtime_error(std::string { "Failed to convert: " } + errorCode.errorName());

    return std::u32string { utf32.begin(), utf32.end() };
}
