#include "task3j.h"

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <memory>

using namespace std;

Task3J::Task3J()
{

}

class Net;

class Device {
public:
    Device(int number, int k, const Net& net)
        : number_(number)
        , net_(net)
    {
        for (int i = 1; i <= k; ++i) {
            neededParts_.insert(i);
        }
    }

    void downloadPart(int i) {
        neededParts_.erase(i);
    }

    bool hasPart(int i) const {
        return neededParts_.count(i) == 0;
    }

    int number() const {
        return number_;
    }

    const set<int>& neededParts() const {
        return neededParts_;
    }

    bool isCompleted() const {
        return neededParts_.empty();
    }

    void selectPart() {
        if (isCompleted()){
            return;
        }
        const auto& partsCounts = net_.getRarestParts();
        for (auto& [count, partSet] : partsCounts) {
            for (int part : partSet) {
                if (!hasPart(part)) {
                    mostNeededPart_ = part;
                    return;
                }
            }
        }
    }

    void doRequest() {
        const set<shared_ptr<Device>>& devices = net_.getDevicesWithPart(mostNeededPart_);
        if (devices.size() > 1) {
            map<int, vector<shared_ptr<Device>>> dict; // partsCountOnDevice -> devices
            for (auto ptr : devices) {
                dict[ptr->get()->neededParts().size()].push_back(ptr);
            }
        }


    }

private:
    int number_;
    set<int> neededParts_;
    const Net& net_;
    int mostNeededPart_;
};

class Net {
public:
    Net(int n, int k)
        : partCount_(k)
    {
        devices_.reserve(n);
    }

    void addDevice(shared_ptr<Device> device) {
        refreshUpdates(device);
        devices_.push_back(device);
    }

    void doTimeSlot() {
        updateRarestPart();

        for (auto& device : devices_) {
            device->selectPart();
        }

        for (auto& device : devices_) {
            device->doRequest();
        }

    }

    const map<int, set<int>>& getRarestParts() const {
        return partsCounts_;
    }

    const set<shared_ptr<Device>>& getDevicesWithPart(int neededPart) {
        return updates_.at(neededPart);
    }

private:
    int partCount_;
    vector<shared_ptr<Device>> devices_;
    map<int, set<shared_ptr<Device>>> updates_; // parts -> set<Devices>
    map<int, set<int>> partsCounts_; // deviceCounts -> set<parts>

private:

    void updateRarestPart() {
        partsCounts_.clear();
        for (auto& [part, numbers] : updates_){
            partsCounts_[numbers.size()].insert(part);
        }
    }

    void refreshUpdates(shared_ptr<Device> device) {
        for (int i = 1; i <= partCount_; ++i) {
            if (device->hasPart(i)) {
                updates_[i].insert(device);
            }
        }
    }
};



Net createNet(int n, int k) {
    Net net = Net(n, k);
    shared_ptr device1 = make_shared<Device>(1, k, net);
    for (int i = 1; i <= k; ++i) {
        device1->downloadPart(k);
    }
    net.addDevice(device1);
    return net;
}

void Task3J::doTask()
{
    int n, k;
    cin >> n >> k;
    Net net = createNet(n, k);
    net.doTimeSlot();
}
