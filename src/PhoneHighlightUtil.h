// Copyright [2019] <Malinovsky Rodion> (rodionmalino@gmail.com)
#include <string>
#include <vector>

namespace rms {

using HighlightRanges = std::vector<std::pair<size_t, size_t>>;
/**
 * @brief Converts collection of ranges to formatted string.
 *
 * @param highlightRanges Collection of ranges. Range follows next logic: [begin, end]. Indexes are zero based.
 * @return std::string String in the following format: "begin1-end1;begin2-end2...".
 */
std::string HighlightRangesToString(HighlightRanges const&);

} // namespace rms
