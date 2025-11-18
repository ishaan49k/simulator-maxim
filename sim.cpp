#include <bits/stdc++.h>
using namespace std;



enum class Scenario {
    LowLatency,
    HighLatency,
    PartialLatency,
    Shutdown,
    Blackout
};




class provider{
    string name;
    Scenario currentstate;
    int disabletime;
};



struct Stats {
    int iptoken;
    int optoken;
    int latency;
    bool error;
};








class Simulator {
public:
    Simulator(Scenario scenario, int numProviders, int timeoutMs) {
        this->scenario     = scenario;
        this->numProviders = numProviders;
        this->timeoutMs    = timeoutMs;
    }


    // multiple provider simulation
    vector<Stats> simulate(){
        vector<Stats> results;
        results.reserve(numProviders);

        for (int i = 0; i < numProviders; i++) {
            results.push_back(simulateOne());
        }

        return results;
}



private:
    Scenario scenario;
    int numProviders;
    int timeoutMs;

    // simulate one provider for the selected scenario
    Stats simulateOne() {
        Stats st;
        st.iptoken = rand() % 100 + 1;
        st.optoken = rand() % 50 + 1;

        switch (scenario) {

            case Scenario::LowLatency:
                st.latency = rand() % 40 + 10;
                st.error = false;
                break;

            case Scenario::HighLatency:
                st.latency = rand() % 300 + 200;
                st.error = (st.latency > timeoutMs);
                break;

            case Scenario::PartialLatency:
                if (rand() % 2 == 0) {
                    st.latency = rand() % 50 + 20;
                    st.error = false;
                } else {
                    st.latency = rand() % 300 + 150;
                    st.error = (st.latency > timeoutMs);
                }
                break;

            case Scenario::Shutdown:
                st.latency = 0;
                st.error = true;
                break;

            case Scenario::Blackout:
                st.latency = timeoutMs + 300;
                st.error = true;
                break;
        }

        return st;
    }
};







int main() {
    srand(time(NULL));
    Simulator sim(Scenario::HighLatency, 5, 200);

    auto results = sim.simulate();

    for (int i = 0; i < results.size(); i++) {
        cout << "provider " << i+1 << ":" << endl;
        cout << "  ip token: " << results[i].iptoken << endl;
        cout << "  op token: " << results[i].optoken << endl;
        cout << "  latency: " << results[i].latency << " ms" << endl;
        cout << "  error: " << (results[i].error ? "Yes" : "No") << endl;
    }

    return 0;
}


