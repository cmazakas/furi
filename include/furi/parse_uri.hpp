//
// Copyright (c) 2020 Christian Mazakas (christian dot mazakas at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/LeonineKing1199/furi
//

#ifndef FURI_PARSE_URI_HPP_
#define FURI_PARSE_URI_HPP_

#include <furi/uri_parts.hpp>

namespace furi
{
auto
parse_uri(std::basic_string_view<char, std::char_traits<char>> const uri) -> basic_uri_parts<char>;

auto
parse_complete(std::basic_string_view<char, std::char_traits<char>> const uri,
               basic_uri_parts<char>&                                     parts) -> bool;

auto
parse_authority(std::basic_string_view<char, std::char_traits<char>> const uri,
                basic_uri_parts<char>&                                     parts) -> bool;
auto
parse_uri(std::basic_string_view<char32_t, std::char_traits<char32_t>> const uri)
  -> basic_uri_parts<char32_t>;

auto
parse_complete(std::basic_string_view<char32_t, std::char_traits<char32_t>> const uri,
               basic_uri_parts<char32_t>&                                         parts) -> bool;

auto
parse_authority(std::basic_string_view<char32_t, std::char_traits<char32_t>> const uri,
                basic_uri_parts<char32_t>&                                         parts) -> bool;
} // namespace furi
#endif // FURI_PARSE_URI_HPP_
