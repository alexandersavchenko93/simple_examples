#include <vector>

enum class InstructionType
{
    kArrival,
    kWaypoint,
    kDeparture
};

class Object
{
public:
    Object(int offset, InstructionType type)
    {
        this->offset = offset;
        this->type = type;
    }
    
public:
    int offset;
    InstructionType type;
};

int main(int argc, const char * argv[]) {
    
    std::vector<Object> v;
    v.push_back(Object(4, InstructionType::kArrival));
    v.push_back(Object(2, InstructionType::kWaypoint));
    v.push_back(Object(5, InstructionType::kWaypoint));
    v.push_back(Object(15, InstructionType::kWaypoint));
    v.push_back(Object(67, InstructionType::kWaypoint));
    v.push_back(Object(3, InstructionType::kWaypoint));
    v.push_back(Object(8, InstructionType::kWaypoint));
    v.push_back(Object(1, InstructionType::kDeparture));
    
    auto cond = [](auto& lhs, auto& rhs)
    {
        return (lhs.type > rhs.type) || (lhs.offset < rhs.offset);
    };
    
    std::stable_sort(v.begin(), v.end(), cond);
    
    return 0;
}
