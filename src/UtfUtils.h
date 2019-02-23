// Copyright [2019] <Malinovsky Rodion> (rodionmalino@gmail.com)

#include <string>

namespace rms {

/**
 * @brief Converts UTF8 string to UTF32 string
 *
 * @param input UTF8 encoded string
 * @return std::u32string UTF32 encoded string
 */
std::u32string UTF8ToUTF32(std::string const& input);

/**
 * @brief Converts UTF32 string to UTF8 string
 *
 * @param input UTF32 encoded string
 * @return std::string UTF8 encoded string
 */
std::string UTF32ToUTF8(std::u32string const& input);

} // namespace rms
