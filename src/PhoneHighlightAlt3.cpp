// Copyright [2019] <Stanislavyk Yaroslav> (stl.ros@outlook.com)
#include "PhoneHighlightAlt3.h"

#include <cstdint>

rms::HighlightRanges rms::GetPhoneHighlightAlt3(std::u32string const& phoneNumber, std::u32string const& searchString)
{
    if (phoneNumber.empty() || searchString.empty())
        return rms::HighlightRanges();

    static std::u32string const ignoredSymbols = U" ()/#.\u00A0";

    HighlightRanges highlightRanges;
    rms::HighlightRanges::value_type range;

    size_t searchStringPos = 0u;
    auto matchingStarted = false;

    for (size_t phoneNumberPos = 0u; phoneNumberPos < phoneNumber.size(); ++phoneNumberPos) {
        // If all symbols from the search string were found but the phone number is not fully iterated yet
        // then collect the range and continue the processing
        if (searchStringPos >= searchString.size()) {
            matchingStarted = false;
            highlightRanges.push_back(range);
            searchStringPos = 0u;
        }

        // If the current symbol should be ignored
        if (ignoredSymbols.find(phoneNumber[phoneNumberPos]) != std::u32string::npos) {
            // If the previous symbols were matched then collect the range and continue the processing
            if (matchingStarted) {
                matchingStarted = false;
                highlightRanges.push_back(range);
            }
            continue;
        }

        // If the current symbol matched
        if (phoneNumber[phoneNumberPos] == searchString[searchStringPos]) {
            // If the start position of the current range was not found yet then setting it
            if (!matchingStarted) {
                matchingStarted = true;
                range.first = phoneNumberPos;
            }
            range.second = phoneNumberPos;
            ++searchStringPos;

            // If it is the last symbol in the phone number
            if (phoneNumberPos + 1u >= phoneNumber.size()) {
                matchingStarted = false;
                highlightRanges.push_back(range);
            }
            continue;
        }

        // If the current symbol shouldn't be ignored and doesn't match the current searched symbol

        // If we already found some ranges then start the processing from
        // the symbol which coming after the first matched symbol
        if (!highlightRanges.empty() && searchStringPos > 0u) {
            phoneNumberPos = highlightRanges[0u].first;
            highlightRanges.clear();
        }

        matchingStarted = false;
        searchStringPos = 0u;
    }

    return highlightRanges;
}
