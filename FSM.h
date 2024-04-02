#include <iostream>
#include <vector>
#include <string>
#include <queue>

class FSM {
public:
    FSM(std::string a);
    ~FSM() = default;
    bool is_end();
    std::pair<std::vector<int>, int> getNode();
private:
    std::string str_;
    int state = 0;
    int ind = 0;
};
