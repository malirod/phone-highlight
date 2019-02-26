// Copyright [2019] <Malinovsky Rodion> (rodionmalino@gmail.com)

#include <string>

namespace rms {

/**
 * @brief Converts UTF8 string to UTF32 string using ICU library.
 *
 * @param input UTF8 encoded string.
 * @return std::u32string UTF32 encoded string.
 */
std::u32string UTF8ToUTF32ICU(std::string const& input);

} // namespace rms
