// This file is part of Asteria.
// Copyleft 2018 - 2019, LH_Mouse. All wrongs reserved.

#ifndef ASTERIA_COMPILER_PARSER_ERROR_HPP_
#define ASTERIA_COMPILER_PARSER_ERROR_HPP_

#include "../fwd.hpp"
#include <exception>

namespace Asteria {

class Parser_Error : public virtual std::exception
  {
  private:
    Parser_Status m_status;
    long m_line;
    size_t m_offset;
    size_t m_length;

    // Create a comprehensive string that is also human-readable.
    cow_string m_what;

  public:
    explicit Parser_Error(Parser_Status xstatus)
      :
        m_status(xstatus),
        m_line(-1), m_offset(0), m_length(0)
      {
        this->do_compose_message();
      }
    Parser_Error(Parser_Status xstatus, long xline, size_t xoffset, size_t xlength)
      :
        m_status(xstatus),
        m_line(xline), m_offset(xoffset), m_length(xlength)
      {
        this->do_compose_message();
      }
    ~Parser_Error() override;

  private:
    void do_compose_message();

  public:
    const char* what() const noexcept override
      {
        return this->m_what.c_str();
      }

    long line() const noexcept
      {
        return this->m_line;
      }
    size_t offset() const noexcept
      {
        return this->m_offset;
      }
    size_t length() const noexcept
      {
        return this->m_length;
      }
    Parser_Status status() const noexcept
      {
        return this->m_status;
      }
    const char* what_status() const noexcept
      {
        return describe_parser_status(this->m_status);
      }
  };

inline bool operator==(const Parser_Error& lhs, Parser_Status rhs) noexcept
  {
    return lhs.status() == rhs;
  }
inline bool operator!=(const Parser_Error& lhs, Parser_Status rhs) noexcept
  {
    return lhs.status() != rhs;
  }

inline bool operator==(Parser_Status lhs, const Parser_Error& rhs) noexcept
  {
    return lhs == rhs.status();
  }
inline bool operator!=(Parser_Status lhs, const Parser_Error& rhs) noexcept
  {
    return lhs != rhs.status();
  }

}  // namespace Asteria

#endif
