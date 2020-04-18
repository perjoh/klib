#include <catch.hpp>
#include <klib/fast_delegate.hpp>

class Proxy
{
public :
    void set_value(int value)
    {
        value_ = value;
    }

    int value() const
    {
        return value_;
    }

private :
    int value_{0};
};

TEST_CASE("Basic tests.", "[fast_delegate]")
{
    Proxy proxy;
    auto del = klib::Fast_delegate<void, int>::construct<Proxy, &Proxy::set_value>(&proxy);
    //auto del = klib::construct_delegate(&proxy, &Proxy::set_value);

    REQUIRE(proxy.value() == 0);
    del(1); 
    REQUIRE(proxy.value() == 1);
}
