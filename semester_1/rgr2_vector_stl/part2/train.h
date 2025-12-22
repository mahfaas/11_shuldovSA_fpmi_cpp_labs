#pragma once

#include <cstddef>
#include <ctime>
#include <iomanip>
#include <ostream>
#include <string>
#include "time_utility.h"

using TrainId = size_t;
using namespace time_utility;

enum class TrainType { PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED };

class Train {
private:
    TrainId id_;
    TrainType type_;
    std::string destination_;
    std::time_t dispatch_time_;
    std::time_t travelling_time_;

public:
    Train()
        : id_(0),
          type_(TrainType::PASSENGER),
          destination_(),
          dispatch_time_(SetTime(0, 0)),
          travelling_time_(SetTime(0, 0)) {
    }

    Train(TrainId id, TrainType type, const std::string& destination, std::time_t dispatch_time, std::time_t travelling_time)
        : id_(id),
          type_(type),
          destination_(destination),
          dispatch_time_(dispatch_time),
          travelling_time_(travelling_time) {
    }

    TrainId GetId() const {
        return id_;
    }
    TrainType GetType() const {
        return type_;
    }
    const std::string& GetDestination() const {
        return destination_;
    }
    std::time_t GetDispatchTime() const {
        return dispatch_time_;
    }
    std::time_t GetTravellingTime() const {
        return travelling_time_;
    }

    bool HasDestination(const std::string& destination) const {
        return destination_ == destination;
    }

    size_t GetTravellingMinutes() const {
        const std::tm* lt = std::localtime(&travelling_time_);
        return static_cast<size_t>(lt->tm_hour) * 60ULL + static_cast<size_t>(lt->tm_min);
    }

    bool operator<(const Train& other) const {
        return dispatch_time_ < other.dispatch_time_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Train& tr) {
        const std::tm* dep = std::localtime(&tr.dispatch_time_);
        const std::tm* travel = std::localtime(&tr.travelling_time_);

        os << tr.id_ << ' ' << static_cast<int>(tr.type_) << ' ' << tr.destination_ << ' ';

        os << std::setw(2) << std::setfill('0') << dep->tm_hour << ":" << std::setw(2) << std::setfill('0') << dep->tm_min << ' ';

        os << std::setw(2) << std::setfill('0') << travel->tm_hour << ":" << std::setw(2) << std::setfill('0') << travel->tm_min;

        return os;
    }
};
