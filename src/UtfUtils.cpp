// Copyright [2019] <Malinovsky Rodion> (rodionmalino@gmail.com)
#include "UtfUtils.h"

#include <boost/locale.hpp>

std::u32string rms::UTF8ToUTF32(std::string const& input)
{
    return boost::locale::conv::utf_to_utf<char32_t>(input);
}

std::string rms::UTF32ToUTF8(std::u32string const& input)
{
    return boost::locale::conv::utf_to_utf<char>(input);
}
