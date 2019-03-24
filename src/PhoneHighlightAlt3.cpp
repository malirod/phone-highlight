// Copyright [2019] <Stanislavyk Yaroslav> (stl.ros@outlook.com)
#include "PhoneHighlightAlt3.h"

#include <cstdint>

namespace {

struct Context {
    std::u32string const& phoneNumber;
    std::u32string const& searchString;
    uint32_t& searchStringPos;
    bool& matchingStarted;
    rms::HighlightRanges::value_type& range;
    rms::HighlightRanges& highlightRanges;
};

void CollectRange(Context const& context)
{
    context.matchingStarted = false;
    context.highlightRanges.push_back(context.range);
}

void ClearFoundRanges(Context const& context, uint32_t& phoneNumberPos)
{
    if (!context.highlightRanges.empty() && context.searchStringPos > 0) {
        phoneNumberPos = context.highlightRanges[0].first;
        context.highlightRanges.clear();
    }

    context.matchingStarted = false;
    context.searchStringPos = 0;
    context.range = {};
}

bool SymbolIgnored(char32_t const symbol, std::u32string const& ignoredSymbols)
{
    return ignoredSymbols.find(symbol) != std::u32string::npos;
}

bool SymbolMatched(Context const& context, uint32_t const phoneNumberPos)
{
    if (context.phoneNumber[phoneNumberPos] == context.searchString[context.searchStringPos]) {
        if (!context.matchingStarted) {
            context.matchingStarted = true;
            context.range.first = phoneNumberPos;
        }

        context.range.second = phoneNumberPos;
        ++context.searchStringPos;

        auto const isLastSymbol = (phoneNumberPos + 1u >= context.phoneNumber.size());
        if (isLastSymbol) {
            CollectRange(context);
        }
        return true;
    }
    return false;
}

} // namespace

rms::HighlightRanges rms::GetPhoneHighlightAlt3(std::u32string const& phoneNumber, std::u32string const& searchString)
{
    if (phoneNumber.empty() || searchString.empty())
        return rms::HighlightRanges();

    static std::u32string const ignoredChars = U" ()/#.\u00A0";

    HighlightRanges highlightRanges;
    rms::HighlightRanges::value_type range;

    uint32_t searchStringPos = 0;
    auto matchingStarted = false;
    auto context = Context { phoneNumber, searchString, searchStringPos, matchingStarted, range, highlightRanges };

    for (uint32_t phoneNumberPos = 0; phoneNumberPos < phoneNumber.size(); ++phoneNumberPos) {
        if (searchStringPos >= searchString.size()) {
            CollectRange(context);
            searchStringPos = 0;
        }

        if (SymbolIgnored(phoneNumber.at(phoneNumberPos), ignoredChars)) {
            if (matchingStarted) {
                CollectRange(context);
            }
            continue;
        }

        if (SymbolMatched(context, phoneNumberPos)) {
            continue;
        }

        ClearFoundRanges(context, phoneNumberPos);
    }

    return highlightRanges;
}
