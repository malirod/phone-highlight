// Copyright [2019] <Malinovsky Rodion> (rodionmalino@gmail.com)
#include "PhoneHighlightUtil.h"

#include <boost/algorithm/string.hpp>
#include <boost/range/adaptors.hpp>

std::string rms::HighlightRangesToString(HighlightRanges const& highlightRanges)
{
    using boost::adaptors::transformed;
    using boost::algorithm::join;
    auto RangeToString = [](auto const& range) {
        return std::to_string(range.first) + "-" + std::to_string(range.second);
    };

    return join(highlightRanges | transformed(RangeToString), ";");
}
