#include <memory>
#include <boost/shared_ptr.hpp>
class testc
{
public:
    testc()
    {
        a = 0;
    }
int a;
};

class future_impl
{
public:
    bool set_result(std::auto_ptr<testc> zone)
    {
        zone = zone;
    }
    std::auto_ptr<testc> zone_;
};

class future
{
public:
    future(boost::shared_ptr<future_impl> impl)
      :future_imp_(impl)
    {
    }
    void set_result(std::auto_ptr<testc> zone)
    {
        future_imp_->set_result(zone);
    }
    boost::shared_ptr<future_impl> future_imp_;
};

int main()
{
std::auto_ptr<testc> t;
t.reset();
t.reset(new testc);
boost::shared_ptr<testc> t2(t.release());
boost::shared_ptr<future_impl> sf(new future_impl);
future f(sf);
f.set_result(t);
{
std::auto_ptr<testc> t2(new testc);
f.set_result(t2);
t2.reset();
}

}
