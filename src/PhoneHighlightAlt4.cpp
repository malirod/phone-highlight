// Copyright [2019] <Malinovsky Rodion> (rodionmalino@gmail.com)
#include "PhoneHighlightAlt4.h"

#include <range/v3/algorithm/search.hpp>
#include <range/v3/iterator_range.hpp>
#include <range/v3/view/filter.hpp>

rms::HighlightRanges rms::GetPhoneHighlightAlt4(std::u32string const& phoneNumber, std::u32string const& searchString)
{
    static std::u32string const ignoredChars = U" ()/#.\u00A0";

    auto const IsValidChar = [](char32_t const charToCheck) {
        return ignoredChars.find(charToCheck) == std::u32string::npos;
    };

    HighlightRanges highlightRanges;

    if (phoneNumber.empty() || searchString.empty())
        return highlightRanges;

    auto filteredRange = phoneNumber | ranges::v3::view::filter(IsValidChar);
    auto itFoundPattern = ranges::v3::search(filteredRange, searchString);
    auto const endOfFilteredRange = filteredRange.end();

    while (itFoundPattern != endOfFilteredRange) {
        // Found match which might contain ignored chars
        // Calculate indexes of [begin; end) and prepare for next iteration
        auto tokenBeginIdx = itFoundPattern.base() - phoneNumber.begin();
        auto const searchStringUtf32Size = searchString.size();
        // Advance begin iterator for next search loop. Iteration is done within match range [begin, end]
        // At the same time split matched range into sub-ranges: if distance between two indexes
        // in is greater than 1 then some ignored chars are in-between.
        for (size_t idx = 1u; idx < searchStringUtf32Size; ++idx) {
            auto const prevItFoundPattern = itFoundPattern++;
            auto const nextItemIdx = itFoundPattern.base() - phoneNumber.begin();
            auto const prevItemIdx = prevItFoundPattern.base() - phoneNumber.begin();

            if (nextItemIdx - prevItemIdx > 1) {
                // Found sub-range
                highlightRanges.push_back(std::make_pair(tokenBeginIdx, prevItemIdx));
                tokenBeginIdx = nextItemIdx;
            }
        }
        auto tokenEndIdx = itFoundPattern.base() - phoneNumber.begin();
        highlightRanges.push_back(std::make_pair(tokenBeginIdx, tokenEndIdx));
        // position iterator on the element next after last element in the match range
        ++itFoundPattern;
        auto const nextFilteredRange = ranges::v3::make_iterator_range(itFoundPattern, filteredRange.end());

        itFoundPattern = ranges::v3::search(nextFilteredRange, searchString);
    }
    return highlightRanges;
}
