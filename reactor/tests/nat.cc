#define ELLE_TEST_MODULE nat
#include <elle/test.hh>

#include <reactor/network/nat.hh>
#include <reactor/scheduler.hh>
#include <reactor/network/resolve.hh>

#include <elle/print.hh>

using namespace reactor;
using namespace reactor::network;

//BOOST_AUTO_TEST_CASE(hole)
//{
//  Scheduler sched;
//
//  auto test_fn = [&]
//  {
//    reactor::nat::NAT n{sched};
//
//    auto hole = n.punch("punch.api.infinit.io", 9999, 8345);
//    BOOST_CHECK_NE(hole.public_endpoint().port(), 0);
//  };
//  Thread t(sched, "test", test_fn);
//  sched.run();
//}
//
//#if defined(REACTOR_HAVE_STUN)
//BOOST_AUTO_TEST_CASE(breach)
//{
//  Scheduler sched;
//
//  auto test_fn = [&]
//  {
//    reactor::nat::NAT n{sched};
//
//    auto host = reactor::network::resolve_udp(sched, "punch.api.infinit.io",
//                                              std::to_string(3478));
//    auto breach = n.map(host);
//    elle::print(breach.mapped_endpoint());
//    elle::print(breach.local_endpoint());
//    elle::print(breach.nat_behavior());
//  };
//  Thread t(sched, "test", test_fn);
//  sched.run();
//}
//#endif
