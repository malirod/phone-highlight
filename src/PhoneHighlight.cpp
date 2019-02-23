// Copyright [2019] <Malinovsky Rodion> (rodionmalino@gmail.com)
#include "PhoneHighlight.h"

#include "UtfUtils.h"

#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>

std::string rms::HighlightRangesToString(HighlightRanges const& highlightRanges)
{
    using boost::adaptors::transformed;
    using boost::algorithm::join;
    auto RangeToString = [](auto const& range) {
        return std::to_string(range.first) + "-" + std::to_string(range.second);
    };

    return join(highlightRanges | transformed(RangeToString), ";");
}

std::string rms::GetPhoneHighlight(std::string const& phoneNumber, std::string const& searchString)
{
    using boost::adaptors::filtered;

    static std::u32string const ignoredChars = U" ()/#.\u00A0";

    auto const IsValidChar = [](char32_t const charToCheck) {
        return ignoredChars.find_first_of(charToCheck) == std::u32string::npos;
    };

    if (phoneNumber.empty() || searchString.empty())
        return "";

    auto const phoneNumberUtf32 = UTF8ToUTF32(phoneNumber);
    auto const searchStringUtf32 = UTF8ToUTF32(searchString);

    HighlightRanges highlightRanges;

    auto filteredRange = boost::make_iterator_range(phoneNumberUtf32 | filtered(IsValidChar));
    auto itFoundPattern = boost::range::search(filteredRange, searchStringUtf32);
    auto const endOfFilteredRange = filteredRange.end();

    while (itFoundPattern != endOfFilteredRange) {
        // Found match which might contain ignored chars
        // Calculate indexes of [begin; end) and prepare for next iteration
        auto tokenBeginIdx = itFoundPattern.base() - phoneNumberUtf32.begin();
        auto const searchStringUtf32Size = searchStringUtf32.size();
        // Advance begin iterator for next search loop. Iteration is done within match range [begin, end]
        // At thesame time split matched range into sub-ranges: if distance between two indexes
        // in is greater than 1 then some ignored chars are in-between.
        for (size_t idx = 1u; idx < searchStringUtf32Size; ++idx) {
            auto const prevItFoundPattern = itFoundPattern++;
            auto const nextItemIdx = itFoundPattern.base() - phoneNumberUtf32.begin();
            auto const prevItemIdx = prevItFoundPattern.base() - phoneNumberUtf32.begin();

            if (nextItemIdx - prevItemIdx > 1) {
                // Found sub-range
                highlightRanges.push_back(std::make_pair(tokenBeginIdx, prevItemIdx));
                tokenBeginIdx = nextItemIdx;
            }
        }
        auto tokenEndIdx = itFoundPattern.base() - phoneNumberUtf32.begin();
        highlightRanges.push_back(std::make_pair(tokenBeginIdx, tokenEndIdx));
        // position iterator on the element next after last element in the match range
        ++itFoundPattern;
        filteredRange = boost::make_iterator_range(itFoundPattern, filteredRange.end());

        itFoundPattern = boost::range::search(filteredRange, searchStringUtf32);
    }
    return HighlightRangesToString(highlightRanges);
}
