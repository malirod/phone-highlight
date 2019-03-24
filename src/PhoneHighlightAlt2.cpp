// Copyright [2019] <Malinovsky Rodion> (rodionmalino@gmail.com)
// Function implementation based on https://github.com/IvanPysmenni/Highlight (Ivan Pysmenni)
// Implementation has been adjusted to fit used interface with minimal changes in implementation itself.
#include "PhoneHighlightAlt2.h"

#include <algorithm>
#include <vector>

namespace {

std::vector<size_t> GetNonIgnoredIndexes(std::u32string const& inputString, std::u32string const& ignoredSymbols)
{
    std::vector<size_t> result;
    for (size_t i = 0u; i < inputString.size(); ++i) {
        if (ignoredSymbols.find(inputString[i]) == std::u32string::npos) {
            result.push_back(i);
        }
    }

    return result;
}

} // namespace

rms::HighlightRanges rms::GetPhoneHighlightAlt2(std::u32string const& phoneNumber, std::u32string const& searchString)
{
    HighlightRanges highlightRanges;

    if (phoneNumber.empty() || searchString.empty())
        return highlightRanges;

    static std::u32string const ignoredSymbols = U" ()/#.\u00A0";
    const auto nonIgnoredIndexes = GetNonIgnoredIndexes(phoneNumber, ignoredSymbols);
    auto phoneNumberWithoutIgnored = phoneNumber;

    phoneNumberWithoutIgnored.erase(
        std::remove_if(phoneNumberWithoutIgnored.begin(), phoneNumberWithoutIgnored.end(),
            [=](auto symbol) { return ignoredSymbols.find(symbol) != std::u32string::npos; }),
        phoneNumberWithoutIgnored.end());

    size_t found = 0u;
    while (found < phoneNumberWithoutIgnored.size() && ((found = phoneNumberWithoutIgnored.find(searchString, found)) != std::u32string::npos)) {
        highlightRanges.push_back(std::make_pair(nonIgnoredIndexes[found], nonIgnoredIndexes[found]));
        for (size_t i = 0u; i < searchString.size() - 1; ++i) {
            if (nonIgnoredIndexes[found + (i + 1)] - nonIgnoredIndexes[found + i] > 1) {
                highlightRanges.back().second = nonIgnoredIndexes[found + i];
                highlightRanges.push_back(std::make_pair(nonIgnoredIndexes[found + (i + 1)], nonIgnoredIndexes[found + (i + 1)]));

                continue;
            }
        }
        highlightRanges.back().second = nonIgnoredIndexes[found + (searchString.size() - 1)];

        found += searchString.size();
    }

    return highlightRanges;
}
