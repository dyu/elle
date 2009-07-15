//
// ---------- header ----------------------------------------------------------
//
// project       elle
//
// license       GPL
//
// file          /home/mycure/infinit/elle/test/archive/Referee.hh
//
// created       julien quintard   [tue jan 27 16:56:46 2009]
// updated       julien quintard   [fri feb  6 21:04:00 2009]
//

#ifndef ELLE_TEST_ARCHIVE_REFEREE_HH
#define ELLE_TEST_ARCHIVE_REFEREE_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/archive/Archive.hh>

#include <list>

namespace elle
{
  using namespace core;
  using namespace misc;
  using namespace archive;

  namespace test
  {

//
// ---------- structures ------------------------------------------------------
//

    struct Element
    {
      Archive::Type	type;
      void*		data;
      Natural32		size;
    };

//
// ---------- classes ---------------------------------------------------------
//

    class Referee
    {
    public:
      //
      // methods
      //
      static Status	Push(const Archive::Type,
			     const void*,
			     const Natural32);
      static Status	Pop(Archive::Type&,
			    void*&,
			    Natural32&);

      //
      // attributes
      //
      static std::list<Element*>	list;
    };

  }
}

#endif
