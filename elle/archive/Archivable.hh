//
// ---------- header ----------------------------------------------------------
//
// project       elle
//
// license       infinit (c)
//
// file          /home/mycure/infinit/elle/archive/Archivable.hh
//
// created       julien quintard   [tue jan 27 01:08:40 2009]
// updated       julien quintard   [sat mar 20 03:24:02 2010]
//

#ifndef ELLE_ARCHIVE_ARCHIVABLE_HH
#define ELLE_ARCHIVE_ARCHIVABLE_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/miscellaneous/Status.hh>

namespace elle
{
  using namespace miscellaneous;

  namespace archive
  {

//
// ---------- declarations ----------------------------------------------------
//

    ///
    /// this forward declares the Archive type.
    ///
    class Archive;

//
// ---------- class -----------------------------------------------------------
//

    ///
    /// this interface must be implemented for objects to be archived.
    ///
    class Archivable
    {
    public:
      //
      // methods
      //
      virtual Status	Serialize(Archive&) const;
      virtual Status	Extract(Archive&);
    };

  }
}

#endif
