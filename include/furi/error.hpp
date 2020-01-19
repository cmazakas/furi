//
// Copyright (c) 2018-2019 Christian Mazakas (christian dot mazakas at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/LeonineKing1199/furi
//

#ifndef FURI_ERROR_HPP_
#define FURI_ERROR_HPP_

#include <boost/system/error_code.hpp>
#include <type_traits>

namespace furi
{
enum class error {
  // our pct-decoding function hit a consecutive percent sign which means it doesn't follow a valid
  // grammar for URIs
  //
  unexpected_pct = 1
};
}

namespace boost
{
namespace system
{
template <>
struct is_error_code_enum<::furi::error>
{
  static bool const value = true;
};

} // namespace system
} // namespace boost

namespace furi
{
namespace detail
{
class furi_error_category : public boost::system::error_category {
public:
  const char*
  name() const noexcept override
  {
    return "furi";
  }

  std::string
  message(int ev) const override
  {
    switch (static_cast<::furi::error>(ev)) {
      case ::furi::error::unexpected_pct: return "consecutive percent sign detected";

      default: return "furi default error";
    }
  }

  boost::system::error_condition
  default_error_condition(int ev) const noexcept override
  {
    return boost::system::error_condition{ev, *this};
  }

  bool
  equivalent(int ev, boost::system::error_condition const& condition) const noexcept override
  {
    return condition.value() == ev && &condition.category() == this;
  }

  bool
  equivalent(boost::system::error_code const& error, int ev) const noexcept override
  {
    return error.value() == ev && &error.category() == this;
  }
};
} // namespace detail

auto
make_error_code(::furi::error ev) -> boost::system::error_code
{
  static detail::furi_error_category const cat{};
  return boost::system::error_code{static_cast<std::underlying_type<::furi::error>::type>(ev), cat};
}

} // namespace furi

#endif // FURI_ERROR_HPP_
