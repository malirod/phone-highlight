// Copyright [2019] <Stanislavyk Yaroslav> (stl.ros@outlook.com)

#include "PhoneHighlightUtil.h"

#include <string>

namespace rms {

/**
 * @brief Get the Phone Highlight object. UTF32 version. Indexes are zero based. Range is [begin, end] where begin and end are first
 * and the last elements of the match range.
 *
 * @param phoneNumber Phone number as UTF32 string in which highlights are searched. List of ignored symbols: space, no-break space, "(",")","/", "#", ".". 
 * @param searchString UTF32 encoded search pattern to search.
 * @return HighlightRanges indexes for highlights. Format: "begin1-end1;begin2-end2..."
 */
HighlightRanges GetPhoneHighlightYS(std::u32string const& phoneNumber, std::u32string const& searchString);

} // namespace rms