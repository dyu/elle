#ifndef  ELLE_PRINTF_HXX
# define ELLE_PRINTF_HXX

# include <elle/assert.hh>
# include <elle/Exception.hh>
# include <elle/log.hh>
# include <elle/print.hh>

# include <cstddef>
# include <iostream>
# include <sstream>
# include <typeinfo>
# include <type_traits>
# include <boost/format.hpp>

namespace elle
{
  namespace detail
  {

    // Select the right feeder.
    // Feeder for "printable" objects.
    template<bool __b>
    struct FeedItSwissMotherFuckingCheese
    {
      template<size_t> struct Helper{};

      // Default overload :
      // - the dummy int parameter make call unambiguous
      // - the last parameter uses sfinae to fall into the fallback method
      //   when boost::format just don't work (nucleus::proton::Version
      //   with boost 1.49 in c++0x).
      template<typename T>
      static
      void
      feed_it(boost::format& fmt, T&& bvalue, int,
              Helper<sizeof(
                static_cast<boost::format&>(*((boost::format* const)0)) %
                static_cast<T const&>(*((T const* const)0)) )>* = 0)
      {
        fmt % std::forward<T>(bvalue);
      }

      // This is the fallback method using a classic stringstream, and
      // format a plain string instead of the value.
      template<typename T>
      static
      void
      feed_it(boost::format& fmt, T&& value, unsigned int)
      {
        std::stringstream ss;
        ss << std::forward<T>(value);
        fmt % ss.str();
      }
    };

    // Feeder for "non printable" objects.
    template <>
    struct FeedItSwissMotherFuckingCheese<false>
    {
      template <typename T>
      static
      void
      feed_it(boost::format& fmt, T&& value, int)
      {
        std::stringstream ss;
        ss << '<'<< typeid(T).name() << " instance at "
           << std::hex << static_cast<void const*>(&value) << '>';
        fmt % ss.str();
      }
    };

    inline
    void
    format_feed(boost::format&)
    {}

    // feed printable values
    template<typename T, typename... K>
    void
    format_feed(boost::format& fmt, T&& front, K&&... tail)
    {
      FeedItSwissMotherFuckingCheese<
        IsPrintable<std::ostream, T>::value
        >::feed_it(fmt, std::forward<T>(front), 42);
      format_feed(fmt, std::forward<K>(tail)...);
    }


    // XXX virer les const& et utiliser les bon traits
    template<typename F, typename... T>
    std::string
    format(F&& fmt, T&&... values)
    {
      boost::format boost_fmt{std::forward<F>(fmt)};
      format_feed(boost_fmt, std::forward<T>(values)...);
      try
      {
        return boost_fmt.str();
      }
      catch (boost::io::format_error const& e)
      {
        ELLE_LOG_COMPONENT("elle.printf");
        auto msg = elle::sprintf("format error with \"%s\": %s", fmt, e.what());
        ELLE_ERR("%s", msg);
        throw elle::Exception(msg);
      }
    }
  }


  template<typename F, typename... T>
  size_t
  fprintf(std::ostream& out, F&& fmt, T&&... values)
  {
    std::string res = elle::detail::format(std::forward<F>(fmt),
                                           std::forward<T>(values)...);
    out << res;
    return res.size();
  }

  template<typename F, typename... T>
  size_t printf(F&& fmt, T&&... values)
  {
    return fprintf(std::cout, std::forward<F>(fmt), std::forward<T>(values)...);
  }

  template<typename F, typename... T>
  std::string sprintf(F&& fmt, T&&... values)
  {
    return elle::detail::format(std::forward<F>(fmt),
                                std::forward<T>(values)...);
  }

}

#endif
