//
// Copyright (c) 2020 Christian Mazakas (christian dot mazakas at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/LeonineKing1199/furi
//

#include <furi/parse_uri.hpp>
#include <furi/uri.hpp>

namespace x3 = boost::spirit::x3;

auto
furi::parse_uri(std::basic_string_view<char, std::char_traits<char>> const uri)
  -> furi::basic_uri_parts<char>
{
  auto parts = furi::basic_uri_parts<char>();
  if (furi::parse_complete(uri, parts)) { return parts; }

  parts = furi::basic_uri_parts<char>();
  if (furi::parse_authority(uri, parts)) { return parts; }

  return furi::basic_uri_parts<char>();
}

auto
furi::parse_complete(std::basic_string_view<char, std::char_traits<char>> const uri,
                     furi::basic_uri_parts<char>&                               parts) -> bool
{
  auto       iter = uri.begin();
  auto const end  = uri.end();

  auto old   = iter;
  auto match = false;

  match = x3::parse(iter, end, furi::uri::raw[furi::uri::scheme] >> ":", parts.scheme_);
  if (!match) { return false; }

  old = iter;

  match = x3::parse(
    iter, end, x3::lit("//") >> -(furi::uri::userinfo >> "@") >> furi::uri::raw[furi::uri::host],
    parts.host_);

  // if we have a valid host, check for the port and then the path-abempty portion of the
  // hier-part
  //
  if (match) {
    match = x3::parse(iter, end, -(":" >> furi::uri::raw[furi::uri::port]), parts.port_);
    if (!match) { return false; }

    match = x3::parse(iter, end, furi::uri::raw[furi::uri::path_abempty], parts.path_);
    if (!match) { return false; }
  }

  // TODO: find out if we can ever introduce these two path parsing portions without breaking the
  // authority form parser
  //
  // if (!match) {
  //   iter = old;
  //   x3::parse(iter, end, furi::uri::raw[furi::uri::path_absolute()], parts.path_);
  // }

  // if (!match) {
  //   iter  = old;
  //   match = x3::parse(iter, end, furi::uri::raw[furi::uri::path_rootless()], parts.path_);
  // }

  if (!match) {
    iter  = old;
    match = x3::parse(iter, end, furi::uri::raw[furi::uri::path_empty], parts.path_);
  }

  if (!match) { return false; }

  match = x3::parse(iter, end, -("?" >> furi::uri::raw[furi::uri::query]), parts.query_);
  if (!match) { return false; }

  match = x3::parse(iter, end, -("#" >> furi::uri::raw[furi::uri::fragment]), parts.fragment_);
  if (!match) { return false; }

  return iter == end;
}

auto
furi::parse_authority(std::basic_string_view<char, std::char_traits<char>> const uri,
                      furi::basic_uri_parts<char>&                               parts) -> bool
{
  auto       iter = uri.begin();
  auto const end  = uri.end();

  auto match = false;

  match = x3::parse(iter, end, -(furi::uri::userinfo >> "@") >> furi::uri::raw[furi::uri::host],
                    parts.host_);

  // if we have a valid host, check for the port and then the path-abempty portion of the
  // hier-part
  //
  if (match) {
    match = x3::parse(iter, end, -(":" >> furi::uri::raw[furi::uri::port]), parts.port_);
    if (!match) { return false; }

    match = x3::parse(iter, end, furi::uri::raw[furi::uri::path_abempty], parts.path_);
    if (!match) { return false; }
  }

  if (!match) { return false; }

  match = x3::parse(iter, end, -("?" >> furi::uri::raw[furi::uri::query]), parts.query_);
  if (!match) { return false; }

  match = x3::parse(iter, end, -("#" >> furi::uri::raw[furi::uri::fragment]), parts.fragment_);
  if (!match) { return false; }

  return iter == end;
}

auto
furi::parse_uri(std::basic_string_view<char32_t, std::char_traits<char32_t>> const uri)
  -> furi::basic_uri_parts<char32_t>
{
  auto parts = furi::basic_uri_parts<char32_t>();
  if (furi::parse_complete(uri, parts)) { return parts; }

  parts = furi::basic_uri_parts<char32_t>();
  if (furi::parse_authority(uri, parts)) { return parts; }

  return furi::basic_uri_parts<char32_t>();
}

auto
furi::parse_complete(std::basic_string_view<char32_t, std::char_traits<char32_t>> const uri,
                     furi::basic_uri_parts<char32_t>& parts) -> bool
{
  auto       iter = uri.begin();
  auto const end  = uri.end();

  auto old   = iter;
  auto match = false;

  match = x3::parse(iter, end, furi::uri::raw[furi::uri::unicode::scheme] >> x3::unicode::lit(U":"),
                    parts.scheme_);
  if (!match) { return false; }

  old = iter;

  match = x3::parse(iter, end,
                    x3::unicode::lit(U"//") >>
                      -(furi::uri::unicode::userinfo >> x3::unicode::lit(U"@")) >>
                      furi::uri::raw[furi::uri::unicode::host],
                    parts.host_);

  // if we have a valid host, check for the port and then the path-abempty portion of the
  // hier-part
  //
  if (match) {
    match =
      x3::parse(iter, end, -(x3::unicode::lit(U":") >> furi::uri::raw[furi::uri::unicode::port]),
                parts.port_);
    if (!match) { return false; }

    match = x3::parse(iter, end, furi::uri::raw[furi::uri::unicode::path_abempty], parts.path_);
    if (!match) { return false; }
  }

  // TODO: find out if we can ever introduce these two path parsing portions without breaking the
  // authority form parser
  //
  // if (!match) {
  //   iter = old;
  //   x3::parse(iter, end, furi::uri::raw[furi::uri::path_absolute()], parts.path_);
  // }

  // if (!match) {
  //   iter  = old;
  //   match = x3::parse(iter, end, furi::uri::raw[furi::uri::path_rootless()], parts.path_);
  // }

  if (!match) {
    iter  = old;
    match = x3::parse(iter, end, furi::uri::raw[furi::uri::unicode::path_empty], parts.path_);
  }

  if (!match) { return false; }

  match =
    x3::parse(iter, end, -(x3::unicode::lit(U"?") >> furi::uri::raw[furi::uri::unicode::query]),
              parts.query_);
  if (!match) { return false; }

  match =
    x3::parse(iter, end, -(x3::unicode::lit(U"#") >> furi::uri::raw[furi::uri::unicode::fragment]),
              parts.fragment_);

  if (!match) { return false; }

  return iter == end;
}

auto
furi::parse_authority(std::basic_string_view<char32_t, std::char_traits<char32_t>> const uri,
                      furi::basic_uri_parts<char32_t>& parts) -> bool
{
  auto       iter = uri.begin();
  auto const end  = uri.end();

  auto match = false;

  match = x3::parse(iter, end,
                    -(furi::uri::unicode::userinfo >> x3::unicode::lit(U"@")) >>
                      furi::uri::raw[furi::uri::unicode::host],
                    parts.host_);

  // if we have a valid host, check for the port and then the path-abempty portion of the
  // hier-part
  //
  if (match) {
    match =
      x3::parse(iter, end, -(x3::unicode::lit(U":") >> furi::uri::raw[furi::uri::unicode::port]),
                parts.port_);
    if (!match) { return false; }

    match = x3::parse(iter, end, furi::uri::raw[furi::uri::unicode::path_abempty], parts.path_);
    if (!match) { return false; }
  }

  if (!match) { return false; }

  match =
    x3::parse(iter, end, -(x3::unicode::lit(U"?") >> furi::uri::raw[furi::uri::unicode::query]),
              parts.query_);
  if (!match) { return false; }

  match =
    x3::parse(iter, end, -(x3::unicode::lit(U"#") >> furi::uri::raw[furi::uri::unicode::fragment]),
              parts.fragment_);

  if (!match) { return false; }

  return iter == end;
}
