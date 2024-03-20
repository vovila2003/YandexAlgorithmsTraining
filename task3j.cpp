#include "task3j.h"

#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <memory>
#include <unordered_map>

using namespace std;

Task3J::Task3J()
{

}

class Device;

namespace Net {
const map<int, set<int>>& getRarestParts();
const set<Device *> &getDevicesWithPart(int neededPart);
void markDeviceIsCompleted(Device* device);
}

class Device {
public:
    Device(int number, int k)
        : number_(number)
        , mostNeededPart_(-1)
        , timeslots_(0)
        , deviceToTransmit_(nullptr)
    {
        for (int i = 1; i <= k; ++i) {
            neededParts_.insert(i);
        }
    }

    void downloadPart(int i, Device* sender = nullptr) {
        neededParts_.erase(i);
        if (sender) {
            ++importments_[sender];
        }
        if (isCompleted()) {
            Net::markDeviceIsCompleted(this);
        }
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

    void setupDevice(const vector<Device*>& devices) {
        for (auto device : devices) {
            if (device == this) {
                continue;
            }
            importments_[device] = 0;
        }
        timeslots_ = 0;
    }

    void selectPart() {
        if (isCompleted()){
            mostNeededPart_ = -1;
            return;
        }
        const auto& partsCounts = Net::getRarestParts();
        for (auto& [count, partSet] : partsCounts) {
            for (int part : partSet) {
                if (!hasPart(part)) {
                    mostNeededPart_ = part;
                    return;
                }
            }
        }
        mostNeededPart_ = -1;
    }

    void clearRequests() {
        requests_.clear();
        deviceToTransmit_ = nullptr;
    }

    void doRequest() {
        if (isCompleted()){
            return;
        }
        const set<Device*>& devices = Net::getDevicesWithPart(mostNeededPart_);
        map<int, set<int>> dict; // partsCountOnDevice -> deviceNumbers
        map<int, Device*> numberToDevice;
        for (auto ptr : devices) {
            if (ptr == this) {
                continue;
            }
            dict[ptr->neededParts().size()].insert(ptr->number());
            numberToDevice[ptr->number()] = ptr;
        }
        if (dict.empty()) {
            return;
        }
        int deviceNumberToRequest = *(dict.begin()->second.begin());
        Device* deviceToRequest = numberToDevice[deviceNumberToRequest];
        deviceToRequest->receiveRequest(mostNeededPart_, this);
    }

    void receiveRequest(int neededPart, Device* sender) {
        requests_[sender] = neededPart;
    }

    void selectRequestToDo() {
        map<size_t, vector<Device*>> valueToDevices;
        for (auto& [device, part] : requests_) {
            size_t value = importments_[device];
            valueToDevices[value].push_back(device);
        }
        vector<Device*>& mostImportantDevices = valueToDevices.rbegin()->second;
        map<int, vector<Device*>> partsCountToDevices;
        for (Device* device : mostImportantDevices) {
            int neededPartsCount = device->neededParts().size();
            partsCountToDevices[neededPartsCount].push_back(device);
        }
        vector<Device*>& devices = partsCountToDevices.begin()->second;
        map<int, Device*> numberDevices;
        for(Device* device : devices) {
            numberDevices[device->number()] = device;
        }

        deviceToTransmit_ = numberDevices.begin()->second;
    }

    void doWork() {

        tick();

        if (!deviceToTransmit_) {
            return;
        }

        int partToTransmit = requests_[deviceToTransmit_];

        assert(neededParts_.count(partToTransmit) == 0); //

        deviceToTransmit_->downloadPart(partToTransmit, this);
    }

private:
    int number_;
    set<int> neededParts_;
    int mostNeededPart_;
    int timeslots_;
    Device* deviceToTransmit_;
    unordered_map<Device*, int> requests_;
    unordered_map<Device*, size_t> importments_;

private:
    void tick() {
        if (isCompleted()) {
            return;
        }
        ++timeslots_;
    }

};

namespace Net {

namespace {

    int partCount_;
    vector<unique_ptr<Device>> devices_;
    map<int, set<Device*>> updates_; // parts -> set<Devices>
    map<int, set<int>> partsCounts_; // deviceCounts -> set<parts>
    set<Device*> devicesForDownloads_;

    void updateRarestPart() {
        partsCounts_.clear();
        for (auto& [part, numbers] : updates_){
            partsCounts_[numbers.size()].insert(part);
        }
    }

    void refreshUpdates(Device* device) {
        for (int i = 1; i <= partCount_; ++i) {
            if (device->hasPart(i)) {
                updates_[i].insert(device);
            }
        }
    }
}

    void setupDevices() {
        vector<Device*> devices;
        devices.reserve(devices_.size());
        for (size_t i = 0; i < devices_.size(); ++i) {
            devices.push_back(devices_.at(i).get());
        }
        for (size_t i = 0; i < devices.size(); ++i) {
            devices[i]->setupDevice(devices);
            if (!devices[i]->isCompleted()) {
                devicesForDownloads_.insert(devices[i]);
            }
        }
    }

    void markDeviceIsCompleted(Device* device) {
        devicesForDownloads_.erase(device);
    }

    bool isCompleded() {
        return devicesForDownloads_.empty();
    }

    void setUpdatePartCount(int count) {
        partCount_ = count;
    }

    void addDevice(unique_ptr<Device> device) {
        refreshUpdates(device.get());
        devices_.push_back(std::move(device));
    }

    void doTimeSlot() {
        updateRarestPart();

        for (auto& device : devices_) {
            device->selectPart();
        }

        for (auto& device : devices_) {
            device->clearRequests();
        }

        for (auto& device : devices_) {
            device->doRequest();
        }

        for (auto& device : devices_) {
            device->selectRequestToDo();
        }

        for (auto& device : devices_) {
            device->doWork();
        }

    }

    const map<int, set<int>>& getRarestParts() {
        return partsCounts_;
    }

    const set<Device*>& getDevicesWithPart(int neededPart) {
        return updates_.at(neededPart);
    }

    const vector<unique_ptr<Device>>& devices() {
        return devices_;
    }

};

void createNet(int n, int k) {
    Net::setUpdatePartCount(k);
    auto device1 = make_unique<Device>(1, k);
    for (int i = 1; i <= k; ++i) {
        device1->downloadPart(i);
    }
    Net::addDevice(std::move(device1));
    for (int i = 2; i <= n; ++i) {
        auto device = make_unique<Device>(i, k);
        Net::addDevice(std::move(device));
    }
    Net::setupDevices();
}

void Task3J::doTask()
{
    int n, k;
    cin >> n >> k;
    createNet(n, k);
    while(!Net::isCompleded()) {
        Net::doTimeSlot();
    }
    const vector<unique_ptr<Device>>& devices = Net::devices();
    // for ([])
}
