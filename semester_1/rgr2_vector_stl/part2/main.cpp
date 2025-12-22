#include "time_utility.h"
#include "train.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

bool ParseHHMM(const std::string& s, size_t& hh, size_t& mm) {
    const size_t pos = s.find(':');
    if (pos == std::string::npos) {
        return false;
    }
    const std::string sh = s.substr(0, pos);
    const std::string sm = s.substr(pos + 1);
    if (sh.empty() || sm.empty()) {
        return false;
    }

    for (char ch : sh) {
        if (ch < '0' || ch > '9')
            return false;
    }
    for (char ch : sm) {
        if (ch < '0' || ch > '9')
            return false;
    }

    try {
        hh = static_cast<size_t>(std::stoul(sh));
        mm = static_cast<size_t>(std::stoul(sm));
    } catch (...) {
        return false;
    }

    if (hh > time_utility::MAX_HOUR_NUMBER_PER_DAY || mm > time_utility::MAX_MINUTE_NUMBER_PER_HOUR) {
        return false;
    }
    return true;
}

std::time_t ReadTimeToken(const std::string& token) {
    size_t hh = 0;
    size_t mm = 0;
    if (!ParseHHMM(token, hh, mm)) {
        throw std::runtime_error("Bad time token: " + token);
    }
    return time_utility::SetTime(hh, mm);
}

TrainType IntToTrainType(int x) {
    if (x < 0 || x > 4) {
        throw std::runtime_error("Bad train type");
    }
    return static_cast<TrainType>(x);
}

std::vector<Train> ReadTrains(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open file: " + path);
    }

    std::vector<Train> trains;

    TrainId id = 0;
    int type_int = 0;
    std::string destination;
    std::string departure_token;
    std::string travel_token;

    while (in >> id >> type_int >> destination >> departure_token >> travel_token) {
        TrainType type = IntToTrainType(type_int);
        std::time_t departure_time = ReadTimeToken(departure_token);
        std::time_t travelling_time = ReadTimeToken(travel_token);
        trains.emplace_back(id, type, destination, departure_time, travelling_time);
    }

    return trains;
}

void PrintTrains(const std::vector<Train>& trains) {
    for (const Train& tr : trains) {
        std::cout << tr << '\n';
    }
}

int main() {
    using namespace time_utility;

    try {
        std::string path;
        std::cout << "File path: ";
        std::getline(std::cin, path);

        std::vector<Train> trains = ReadTrains(path);

        std::sort(trains.begin(), trains.end(), 
            [](const Train& a, const Train& b) {
                return a.GetDispatchTime() < b.GetDispatchTime();});

        std::cout << "Sorted by departure time:\n";
        PrintTrains(trains);

        std::string start_token;
        std::string end_token;
        std::cout << "Time range start: ";
        std::cin >> start_token;
        std::cout << "Time range end: ";
        std::cin >> end_token;

        std::time_t t_start = ReadTimeToken(start_token);
        std::time_t t_end = ReadTimeToken(end_token);
        if (t_start > t_end) {
            std::swap(t_start, t_end);
        }

        std::vector<Train> in_range;
        for (const Train& tr : trains) {
            const std::time_t t = tr.GetDispatchTime();
            if (t >= t_start && t <= t_end) {
                in_range.push_back(tr);
            }
        }

        std::cout << "In time range:\n";
        PrintTrains(in_range);

        std::string destination;
        std::cout << "Destination: ";
        std::cin >> destination;

        std::vector<Train> to_dest;
        for (const Train& tr : trains) {
            if (tr.HasDestination(destination)) {
                to_dest.push_back(tr);
            }
        }

        std::cout << "To destination:\n";
        PrintTrains(to_dest);

        std::string destination2;
        int type_int = 0;
        std::cout << "Destination: ";
        std::cin >> destination2;
        std::cout << "Type: ";
        std::cin >> type_int;

        TrainType type = IntToTrainType(type_int);

        std::vector<Train> to_dest_and_type;
        for (const Train& tr : trains) {
            if (tr.HasDestination(destination2) && tr.GetType() == type) {
                to_dest_and_type.push_back(tr);
            }
        }

        std::cout << "To destination and type:\n";
        PrintTrains(to_dest_and_type);

        std::string destination3;
        std::cout << "Destination (to find fastest): ";
        std::cin >> destination3;

        bool found = false;
        Train best;

        for (const Train& tr : trains) {
            if (!tr.HasDestination(destination3)) {
                continue;
            }
            if (!found || tr.GetTravellingMinutes() < best.GetTravellingMinutes()) {
                best = tr;
                found = true;
            }
        }

        std::cout << "Fastest to destination:\n";
        if (found) {
            std::cout << best << '\n';
        } else {
            std::cout << "No trains\n";
        }

        return 0;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
        return 0;
    }
}
