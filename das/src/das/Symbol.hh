#pragma once

#include <string>

namespace das
{
  class Symbol
  {};

  template <typename S>
  class SpecificSymbol
    : public Symbol
  {
  public:
    template <typename E, typename P>
    struct Effective
    {
      using Type = E;
      using Formal = S;
      using Passing = P;
      Type value;

      template <typename OE, typename OP>
      Effective(Effective<OE, OP>&& e)
        : value(std::forward<OP>(e.value))
      {}

      Effective(Effective const& e)
        : value(e.value)
      {}

      Effective(Passing v)
        : value(std::forward<Passing>(v))
      {}

      static inline
      std::string
      name()
      {
        return S::name();
      }
    };

    template <typename E>
    Effective<E, E&&>
    operator =(E&& v) const
    {
      return Effective<E, E&&>{std::forward<E>(v)};
    }
  };
}

#include <das/Symbol.hxx>
