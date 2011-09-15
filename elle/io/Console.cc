//
// ---------- header ----------------------------------------------------------
//
// project       elle
//
// license       infinit
//
// file          /home/mycure/infinit/elle/io/Console.cc
//
// created       julien quintard   [sat jun 18 11:11:53 2011]
// updated       julien quintard   [sat jun 18 11:19:22 2011]
//

//
// ---------- includes --------------------------------------------------------
//

#include <elle/io/Console.hh>

#include <elle/standalone/Report.hh>
#include <elle/standalone/Maid.hh>

#include <elle/idiom/Close.hh>
# include <stdio.h>
# include <unistd.h>
//# if INFINIT_UNIX
#  include <readline/readline.h>
#  include <readline/history.h>
//# endif
#include <elle/idiom/Open.hh>

namespace elle
{
  using namespace standalone;

  namespace io
  {

//
// ---------- methods ---------------------------------------------------------
//

    ///
    /// this method retrieves the user's input from the console.
    ///
    Status		Console::Input(String&			text,
				       const String&		prompt,
				       const Console::Option	option)
    {
      enter();

      // retrieve the input depending on the option.
      switch (option)
	{
	case OptionPassword:
	  {
	    // retrieve the input and assign it.
	    text.assign(::readline(prompt.c_str()));

	    break;
	  }
	case OptionNone:
	default:
	  {
	    // retrieve the input and assign it.
	    text.assign(::readline(prompt.c_str()));

	    break;
	  }
	}

      leave();
    }

  }
}
