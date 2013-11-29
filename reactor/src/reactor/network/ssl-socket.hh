#ifndef INFINIT_REACTOR_NETWORK_SSL_SOCKET_HH
# define INFINIT_REACTOR_NETWORK_SSL_SOCKET_HH

# include <reactor/network/socket.hh>

# include <reactor/scheduler.hh>
# include <reactor/network/resolve.hh>

# include <boost/asio.hpp>
# include <boost/asio/ssl.hpp>

namespace reactor
{
  namespace network
  {
    class SSLCertif
    {
    public:
      SSLCertif();
      SSLCertif(const SSLCertif& other);
      SSLCertif(std::string const& pem,
                std::string const& dhfile,
                boost::asio::ssl::context::method meth =
                  boost::asio::ssl::context::sslv23);

      void
      release();

    private:
      ELLE_ATTRIBUTE_R(boost::asio::ssl::context*, ctx);
    };

    class SSLSocket: public StreamSocket<
      boost::asio::ssl::stream<boost::asio::ip::tcp::socket>,
      boost::asio::ip::tcp::socket::endpoint_type>
    {
    public:
      typedef boost::asio::ssl::context SSLContext;
      typedef StreamSocket<boost::asio::ssl::stream<
        boost::asio::ip::tcp::socket>,
        boost::asio::ip::tcp::socket::endpoint_type> Super;
      typedef SSLSocket Self;

    public:
      SSLSocket(const std::string& hostname,
                const std::string& port,
                SSLCertif& cert,
                DurationOpt timeout = DurationOpt());
      SSLSocket(reactor::Scheduler& sched,
                const std::string& hostname,
                const std::string& port,
                SSLCertif& cert,
                DurationOpt timeout = DurationOpt());
      SSLSocket(reactor::Scheduler& sched,
                boost::asio::ip::tcp::endpoint const& endpoint,
                SSLCertif& cert,
                DurationOpt timeout = DurationOpt());
      ~SSLSocket();

      void
      handshake(boost::asio::ssl::stream<
        boost::asio::ip::tcp::socket>::handshake_type type =
          boost::asio::ssl::stream<
          boost::asio::ip::tcp::socket>::handshake_type::client);

    private:
      SSLSocket(Scheduler& sched,
                std::unique_ptr<boost::asio::ssl::stream<
                  boost::asio::ip::tcp::socket>> socket,
                boost::asio::ip::tcp::socket::endpoint_type const& peer);

    private:
      boost::asio::ip::tcp::socket&
      asio_socket();

      friend class SSLServer;
      friend class SSLAccept;

    private:
      ELLE_ATTRIBUTE(SSLCertif, cert);
    };
  }
}

#endif // !INFINIT_REACTOR_NETWORK_SSL_SOCKET_HH