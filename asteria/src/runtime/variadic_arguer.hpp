// This file is part of Asteria.
// Copyleft 2018 - 2019, LH_Mouse. All wrongs reserved.

#ifndef ASTERIA_RUNTIME_VARIADIC_ARGUER_HPP_
#define ASTERIA_RUNTIME_VARIADIC_ARGUER_HPP_

#include "../fwd.hpp"
#include "abstract_function.hpp"
#include "reference.hpp"
#include "../syntax/source_location.hpp"

namespace Asteria {

class Variadic_Arguer : public Abstract_Function
  {
  private:
    Source_Location m_sloc;
    PreHashed_String m_name;
    CoW_Vector<Reference> m_vargs;

  public:
    Variadic_Arguer(const Source_Location &sloc, const PreHashed_String &name)
      : m_sloc(sloc), m_name(name), m_vargs()
      {
      }
    Variadic_Arguer(const Variadic_Arguer &other, CoW_Vector<Reference> &&vargs)
      : m_sloc(other.m_sloc), m_name(other.m_name), m_vargs(std::move(vargs))
      {
      }

  public:
    const Source_Location & get_location() const noexcept
      {
        return this->m_sloc;
      }
    const PreHashed_String & get_name() const noexcept
      {
        return this->m_name;
      }
    std::size_t get_varg_size() const noexcept
      {
        return this->m_vargs.size();
      }
    const Reference & get_varg(std::size_t index) const
      {
        return this->m_vargs.at(index);
      }

    void describe(std::ostream &os) const override;
    void invoke(Reference &self_io, Global_Context &global, CoW_Vector<Reference> &&args) const override;
    void enumerate_variables(const Abstract_Variable_Callback &callback) const override;
  };

}

#endif
