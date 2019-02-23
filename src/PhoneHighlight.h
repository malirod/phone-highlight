// Copyright [2019] <Malinovsky Rodion> (rodionmalino@gmail.com)

#include <string>
#include <vector>

namespace rms {

using HighlightRanges = std::vector<std::pair<uint32_t, uint32_t>>;
/**
 * @brief Converts collection of ranges to formatted string.
 *
 * @param highlightRanges Collection of ranges. Range follows next logic: [begin, end]. Indexes are zero based.
 * @return std::string String in the following format: "begin1-end1;begin2-end2...".
 */
std::string HighlightRangesToString(HighlightRanges const&);

/**
 * @brief Get the Phone Highlight object. Indexes are zero based. Range is [begin, end] where begin and end are first
 * and the last elements of the match range.
 *
 * @param phoneNumber Phone number as UTF8 string in which highlights are searched. List of ignored symbols: space, no-break space, "(",")","/", "#", ".". 
 * @param searchString UTF8 encoded search pattern to search.
 * @return std::string formatted string with list of indexes for highlights. Format: "begin1-end1;begin2-end2..."
 */
std::string GetPhoneHighlight(std::string const& phoneNumber, std::string const& searchString);

} // namespace rms
