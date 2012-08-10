#ifndef ETOILE_AUTOMATON_RIGHTS_HH
# define ETOILE_AUTOMATON_RIGHTS_HH

# include <elle/types.hh>
# include <etoile/gear/fwd.hh>
# include <nucleus/neutron/fwd.hh>

namespace etoile
{
  namespace automaton
  {

    ///
    /// this class provides automata for computing the user's rights
    /// over a given object context.
    ///
    class Rights
    {
    public:
      //
      // static methods
      //
      static elle::Status       Determine(gear::Object&);
      static elle::Status       Recompute(gear::Object&);
      static elle::Status       Update(gear::Object&,
                                       const nucleus::neutron::Permissions&);

      // XXX
      static
      elle::Status
      Determine(gear::Group&);

      static elle::Status       Operate(gear::Object&,
                                        const gear::Operation&);
    };

  }
}

#endif
