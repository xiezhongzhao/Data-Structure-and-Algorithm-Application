//
// Created by ASUS on 2022/5/18.
//
#include <bits/stdc++.h>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
using namespace std;

struct CacheData{
    int id;
    string data;
};

queue<CacheData> Q;
const int MAX_CACHEDATA_LENGTH = 10;
mutex m;
condition_variable condConsumer;
condition_variable condProducer;
int ID = 1;

// consumer action
void ConsumerActor(){
    unique_lock<mutex> lockerConsumer(m);
    cout << "[" << this_thread::get_id() << "] get the lock" << endl;
    while(Q.empty()){
        cout << "the queue is empty, consumer sleep" << endl;
        cout << "[" << this_thread::get_id() << "] release the lock" << endl;
        //if the queue is empty, the consumer will stop
        condConsumer.wait(lockerConsumer);
        cout << "[" << this_thread::get_id() << "] get the lock again" << endl;
    }
    cout << "[" << this_thread::get_id() << "]";
    CacheData temp = Q.front();
    cout << "-ID: " << temp.id << "Data: " << temp.data << endl;
    Q.pop();
    condProducer.notify_one();
    cout << "[" << this_thread::get_id() << "] release the lock" << endl;
}

// producer action
void ProducerActor(){
    unique_lock<mutex> lockerProducer(m);
    cout << "[" << this_thread::get_id() << "] get the lock" << endl;
    while(Q.size() > MAX_CACHEDATA_LENGTH){
        cout << "if the queue is full, the producer will sleep" << endl;
        cout << "[" << this_thread::get_id() << "] release the lock" << endl;
        condProducer.wait(lockerProducer);
        cout << "[" << this_thread::get_id() << "] get the lock again" << endl;
    }
    cout << "[" << this_thread::get_id() << endl;
    CacheData temp;
    temp.id = ID++;
    temp.data = "********";
    cout << "+ID: " << temp.id << " Data: " << temp.data << endl;
    Q.push(temp);
    condConsumer.notify_one();
    cout << "[" << this_thread::get_id() << "] release the lock" << endl;
}

// consumer
void ConsumerTask(){
    while(1){
        ConsumerActor();
    }
}

// producer
void ProducerTask(){
    while(1){
        ProducerActor();
    }
}

// manage the thread func
void Dispatch(int ConsumerNum, int ProducerNum){
    vector<thread> thsC;
    for(int i=0; i<ConsumerNum; i++){
        thsC.push_back(thread(ConsumerTask));
    }

    vector<thread> thsP;
    for(int i=0; i<ProducerNum; i++){
        thsP.push_back(thread(ProducerTask));
    }

    for(int i=0; i<ConsumerNum; i++){
        if(thsC[i].joinable())
            thsC[i].join();
    }

    for(int i=0; i<ProducerNum; i++){
        if(thsP[i].joinable())
            thsP[i].join();
    }

}

int main(){
    // the num of consumers, the num of producer
    Dispatch(32, 16);
    return 0;
}





