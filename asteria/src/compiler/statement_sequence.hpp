// This file is part of Asteria.
// Copyleft 2018 - 2020, LH_Mouse. All wrongs reserved.

#ifndef ASTERIA_COMPILER_STATEMENT_SEQUENCE_HPP_
#define ASTERIA_COMPILER_STATEMENT_SEQUENCE_HPP_

#include "../fwd.hpp"
#include "statement.hpp"

namespace Asteria {

class Statement_Sequence
  {
  private:
    Compiler_Options m_opts;
    cow_vector<Statement> m_stmts;

  public:
    explicit constexpr Statement_Sequence(const Compiler_Options& opts) noexcept
      : m_opts(opts)
      { }

  public:
    // These are accessors and modifiers of options for parsing.
    const Compiler_Options& get_options() const noexcept
      { return this->m_opts;  }

    Compiler_Options& open_options() noexcept
      { return this->m_opts;  }

    Statement_Sequence& set_options(const Compiler_Options& opts) noexcept
      { return this->m_opts = opts, *this;  }

    // These are accessors to the statements in this sequence.
    // Note that the sequence cannot be modified.
    bool empty() const noexcept
      { return this->m_stmts.size();  }

    Statement_Sequence& clear() noexcept
      { return this->m_stmts.clear(), *this;  }

    size_t size() const noexcept
      { return this->m_stmts.size();  }

    const Statement& at(size_t index) const
      { return this->m_stmts.at(index);  }

    operator const cow_vector<Statement>& () const noexcept
      { return this->m_stmts;  }

    // This function parses tokens from the input stream and fills statements into `*this`.
    // The contents of `*this` are destroyed prior to any further operation.
    // This function throws a `Parser_Error` upon failure.
    Statement_Sequence& reload(Token_Stream& tstrm);
  };

}  // namespace Asteria

#endif
