#include "sender_mvp.hpp"
#include "icontroller.hpp"
namespace pikachu{

void SenderMvp::SendEvent(std::tr1::shared_ptr<IController> a_controller,const std::tr1::shared_ptr<EventBase> a_event)
{
    a_controller->GetEvent(a_event);  
}

}//pikachu