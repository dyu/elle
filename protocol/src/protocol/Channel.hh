#ifndef INFINIT_PROTOCOL_CHANNEL_HH
# define INFINIT_PROTOCOL_CHANNEL_HH

# include <elle/Printable.hh>

# include <reactor/signal.hh>

# include <protocol/Stream.hh>
# include <protocol/fwd.hh>

namespace infinit
{
  namespace protocol
  {
    class Channel
      : public Stream
    {
    /*------.
    | Types |
    `------*/
    public:
      using Self = Channel;
      using Super = Stream;
      using Id = int;

    /*-------------.
    | Construction |
    `-------------*/
    public:
      Channel(ChanneledStream& backend);
      Channel(Channel&& source);
      ~Channel();
    private:
      Channel(ChanneledStream& backend, int id);

    /*--------.
    | Version |
    `--------*/
    public:
      ELLE_attribute_r(elle::Version, version, override);

    /*----------.
    | Printable |
    `----------*/
    public:
      void
      print(std::ostream& s) const override;

    /*----------.
    | Receiving |
    `----------*/
    public:
      elle::Buffer
      read() override;

    /*--------.
    | Sending |
    `--------*/
    protected:
      void
      _write(elle::Buffer const& packet) override;

    /*--------.
    | Details |
    `--------*/
    private:
      friend class ChanneledStream;
      ELLE_ATTRIBUTE(ChanneledStream&, backend);
      ELLE_ATTRIBUTE_R(Id, id);
      ELLE_ATTRIBUTE(std::list<elle::Buffer>, packets);
      ELLE_ATTRIBUTE(reactor::Signal, available);
    };
  }
}

#endif
