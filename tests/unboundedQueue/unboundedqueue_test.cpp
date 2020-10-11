#include "mu_test.h"
#include <sstream>
#include "unbounded_waitablequeue.hpp"
#include "producer.hpp"
#include "consumer.hpp"
#include "thread.hpp"
#include "atomicvalue.hpp"
#include "cat.hpp"

using namespace experis;
using namespace test;


void Eneque(UnboundedWaitableQueue <Cat>& a_ubq,size_t a_size)
{
    for(size_t i=0; i<a_size;++i){
        std::stringstream ss;
        ss << "felix" << i+1;
        Cat c(ss.str());
        a_ubq.Enqueue(c);
    }
}

void Dequeue(UnboundedWaitableQueue <Cat>& a_ubq,size_t a_size,bool &a_res)
{
    for(size_t i=0; i<a_size;++i){
        std::stringstream ss;
        ss << "felix" << i+1;
        Cat c;
        a_ubq.Dequeue(c);
        if(c.GetName()!= ss.str()){
            a_res = false;
            return;
        }
    }
    a_res = true;
}

UNIT(nothreads_1M_enequeue_1M_dequeue)

    UnboundedWaitableQueue <Cat> ub;
    const size_t size = 1000000;
    Eneque(ub,size);
    ASSERT_EQUAL(ub.Occupancy(),size);
    ASSERT_THAT(!ub.IsEmpty());
    bool a=false;
    Dequeue(ub,size,a);
    ASSERT_THAT(a);
    ASSERT_THAT(ub.IsEmpty());

END_UNIT

UNIT(Producer1_consumer1_1M)
    AtomicValue<size_t> a(0);
    const size_t size =1000000;
    std::tr1::shared_ptr< UnboundedWaitableQueue <std::pair<Cat, size_t> > > unboundedqueue(new  UnboundedWaitableQueue<std::pair<Cat, size_t> >());
    std::tr1::shared_ptr< common::Runable> producer1(new Producer(unboundedqueue,0,size,a));
    std::queue<std::pair<Cat, size_t> > queueconsumer;
    std::tr1::shared_ptr< common::Runable> consumer1(new Consumer(unboundedqueue,size,a,queueconsumer));
    
    
     Thread tr1(producer1);
     Thread tr2(consumer1);
   
   	tr1.Join();		    
   	tr2.Join();    
	ASSERT_EQUAL(unboundedqueue->Occupancy(),0);
    for(size_t i=0; i<size;++i){
        std::stringstream ss;
        ss<< "felix" << i+1;
        std::pair<Cat,size_t> p = queueconsumer.front();
        ASSERT_EQUAL(p.first.GetName(),ss.str());       
        ASSERT_EQUAL(p.second,i+1);
        queueconsumer.pop();
    }
    
END_UNIT

bool CheckSorted(std::queue<std::pair<Cat, size_t> >& queue)
{
    size_t size = queue.size();
    size_t compre = 0;
    for(size_t i=0; i<size;++i){
        std::pair<Cat, size_t> front = queue.front();
        //std::cout<<front.second<<" "<<front.first.GetName()<<std::endl;
        if(front.second < compre){
            return false;
        }
        queue.pop();
        compre = front.second;
    }
    return true;
}
UNIT(N_Producer_N_consumern_1M_each)
    AtomicValue<size_t> a(0);
    size_t start = 0;
    size_t end = 1000000;
    const size_t gap =1000000;
    const size_t nconsumers = 3;
    const size_t nproducers = 5;
    std::vector<std::tr1::shared_ptr< common::Runable> > vecproducers;
    std::vector<std::tr1::shared_ptr< common::Runable> > vecconsumers;
    std::tr1::shared_ptr< UnboundedWaitableQueue <std::pair<Cat, size_t> > > unboundedqueue(new  UnboundedWaitableQueue<std::pair<Cat, size_t> >());
    std::queue<std::pair<Cat, size_t> > queueconsumer[nconsumers];
    std::vector<std::tr1::shared_ptr<Thread> > threads;
    
    for(size_t i=0;i<nproducers;++i){
        vecproducers.push_back(std::tr1::shared_ptr<common::Runable>(new Producer(unboundedqueue,start,end,a)));
        threads.push_back(std::tr1::shared_ptr<Thread>(new Thread(vecproducers[i])));
        start+=gap;
        end+=gap;
    }
    
    for(size_t i=0;i<nconsumers;++i){
        vecconsumers.push_back(std::tr1::shared_ptr<common::Runable>(new Consumer(unboundedqueue,gap,a,queueconsumer[i])));
        threads.push_back(std::tr1::shared_ptr<Thread>(new Thread(vecconsumers[i])));
    }
    for(size_t i=0;i<threads.size();++i){
        threads[i]->Join();
    }
    
   	ASSERT_EQUAL(unboundedqueue->Occupancy(),gap*2);
    
    for(size_t i=0; i<1;++i){
        if(CheckSorted(queueconsumer[i])){
           ASSERT_PASS(); 
        }
        else{
            ASSERT_FAIL("no fifo!");
        }
    }
END_UNIT

TEST_SUITE(unboundded queue mu test)
TEST(nothreads_1M_enequeue_1M_dequeue)
TEST(Producer1_consumer1_1M)
//TEST(N_Producer_N_consumern_1M_each)need to find dbetter test  
END_SUITE
