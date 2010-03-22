//
// ---------- header ----------------------------------------------------------
//
// project       elle
//
// license       network
//
// file          /home/mycure/infinit/elle/network/Session.hh
//
// created       julien quintard   [fri mar  5 10:43:11 2010]
// updated       julien quintard   [sun mar 21 16:38:18 2010]
//

#ifndef ELLE_NETWORK_SESSION_HH
#define ELLE_NETWORK_SESSION_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/core/Core.hh>
#include <elle/misc/Misc.hh>
#include <elle/concurrency/Concurrency.hh>

#include <elle/network/Socket.hh>
#include <elle/network/Address.hh>

#include <elle/idiom/Open.hh>

namespace elle
{
  using namespace core;
  using namespace misc;
  using namespace concurrency;

  namespace network
  {

//
// ---------- classes ---------------------------------------------------------
//

    ///
    /// this class contains metadata related to an event such as the
    /// socket and sender's address for instance.
    ///
    class Session:
      public Dumpable
    {
    public:
      //
      // static methods
      //
      static Status	Assign(Session*);

      //
      // constructors & destructors
      //
      Session();

      //
      // methods
      //
      Status		Create(Socket*,
			       const Address&,
			       const Identifier&);

      //
      // interfaces
      //

      // dumpable
      Status		Dump(const Natural32 = 0) const;

      //
      // attributes
      //
      Socket*		socket;
      Address		address;
      Identifier	identifier;
    };

//
// ---------- extern ----------------------------------------------------------
//

    extern Session*		session;

  }
}

#endif
