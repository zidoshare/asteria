// This file is part of Asteria.
// Copyleft 2018 - 2019, LH_Mouse. All wrongs reserved.

#ifndef ASTERIA_RUNTIME_ANALYTIC_CONTEXT_HPP_
#define ASTERIA_RUNTIME_ANALYTIC_CONTEXT_HPP_

#include "../fwd.hpp"
#include "abstract_context.hpp"

namespace Asteria {

class Analytic_Context : public Abstract_Context
  {
  private:
    const Abstract_Context *const m_parent_opt;

  public:
    // An analytic context can be created on another analytic or executive context.
    explicit Analytic_Context(const Abstract_Context *parent_opt) noexcept
      : m_parent_opt(parent_opt)
      {
      }
    ~Analytic_Context() override;

  public:
    bool is_analytic() const noexcept override
      {
        return true;
      }
    const Abstract_Context * get_parent_opt() const noexcept override
      {
        return this->m_parent_opt;
      }

    void prepare_function_parameters(const Cow_Vector<PreHashed_String> &params);
  };

}  // namespace Asteria

#endif
