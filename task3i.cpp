#include "task3i.h"

#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

Task3I::Task3I()
{

}

unordered_map<string, unordered_map<string, vector<int>>> teamScore;
unordered_map<string, unordered_map<string, vector<int>>> playerScore;
unordered_map<string, map<int, int>> playerTime;
unordered_map<string, int> teamFirst;
unordered_map<string, int> playersFirst;
unordered_map<string, set<string>> teamToPlayer;
unordered_map<string, string> playerToTeam;

pair<int, string> readGoals(const string& team, const string& rival, int goals) {
    string line;
    bool first = true;
    int firstTime = 100;
    string firstPlayer = "";
    unordered_map<string, int> playerGoalsOnMatch;
    for (int i = 0; i < goals; ++i) {
        getline(cin, line);
        size_t pos = line.find_first_of("1234567890");
        string player = line.substr(0, pos - 1);
        stringstream ss(line.substr(pos));
        int time;
        ss >> time;
        if (first){
            firstTime = time;
            firstPlayer = player;
            first = false;
        }
        if (time > 90) {
            time = 90;
        }
        ++playerGoalsOnMatch[player];
        ++playerTime[player][time];
        teamToPlayer[team].insert(player);
        playerToTeam[player] = team;
    }
    for (auto& [player, goals] : playerGoalsOnMatch) {
        playerScore[player][rival].push_back(goals);
    }
    return make_pair(firstTime, firstPlayer);
}

void readInfo(const string& line) {
    int st = 1;
    int pos = line.find("\"", st);
    string team1 = line.substr(1, pos - 1);
    st = line.find("\"", pos + 1);
    pos = line.find("\"", st + 1);
    string team2 = line.substr(st + 1, pos - st - 1);
    stringstream ss(line.substr(pos + 1));
    int goals1, goals2;
    char c;
    ss >> goals1 >> c >> goals2;
    teamScore[team1][team2].push_back(goals1);
    teamScore[team2][team1].push_back(goals2);
    auto [t1, p1] = readGoals(team1, team2, goals1);
    auto [t2, p2] = readGoals(team2, team1, goals2);
    if (t1 < t2) {
        ++teamFirst[team1];
        ++playersFirst[p1];
    } else if (t2 < t1) {
        ++teamFirst[team2];
        ++playersFirst[p2];
    }
}

int getTotalGoalsForTeam(const string& team) {
    int result = 0;
    for (auto& [rival, vec] : teamScore[team]) {
        for (auto score : vec) {
            result += score;
        }
    }
    return result;
}

string getTeamName(const string& line) {
    size_t st = line.find("\"", 0);
    size_t pos = line.find("\"", st + 1);
    string team = line.substr(st + 1, pos - st - 1);
    return team;
}

float getMeanGoalsPerGameForTeam(const string& team) {
    if (teamScore.count(team) == 0) {
        return 0;
    }

    int total = getTotalGoalsForTeam(team);
    int gamesCount = 0;
    for (auto& [r, vec] : teamScore[team]) {
        gamesCount += vec.size();
    }
    return float(total) / float(gamesCount);
}

int getTotalGoalsByPlayer(const string& player) {
    int result = 0;
    for (auto& [rival, vec] : playerScore[player]) {
        for (auto score : vec) {
            result += score;
        }
    }
    return result;
}

float getMeanGoalsPerGameByPlayer(const string& player) {
    if (playerToTeam.count(player) == 0) {
        return 0;
    }

    string team = playerToTeam[player];

    if (teamScore.count(team) == 0) {
        return 0;
    }

    int gamesCount = 0;
    for (auto& [r, vec] : teamScore[team]) {
        gamesCount += vec.size();
    }
    int total = getTotalGoalsByPlayer(player);
    return float(total) / float(gamesCount);
}

int getGoalsOnMinuteForPlayer(int minute, const string& player) {
    if (playerTime.count(player) == 0) {
        return 0;
    }
    if (playerTime[player].count(minute) == 0) {
        return 0;
    }
    return playerTime[player][minute];
}

int getGoalsOnFirstMinutesForPlayer(int minutes, const string& player) {
    if (playerTime.count(player) == 0) {
        return 0;
    }
    int result = 0;
    for (auto& [time, goals] : playerTime[player]) {
        if (time <= minutes) {
            result += goals;
        } else {
            break;
        }
    }
    return result;
}

int getGoalsOnLastMinutesForPlayer(int minutes, const string& player) {
    if (playerTime.count(player) == 0) {
        return 0;
    }
    int result = 0;
    for (auto it = playerTime[player].rbegin(); it != playerTime[player].rend(); ++it) {
        int time = it->first;
        if (time >= 91 - minutes) {
            result += it->second;
        } else {
            break;
        }
    }
    return result;
}

int getScoreOpensForPlayer(const string& player) {
    if (playersFirst.count(player) == 0) {
        return 0;
    }
    return playersFirst[player];
}

int getScoreOpensForTeam(const string& team) {
    if (teamFirst.count(team) == 0) {
        return 0;
    }
    return teamFirst[team];
}

void Task3I::doTask()
{
    string line;
    getline(cin, line);

    ofstream out("output.txt");

    while(!line.empty()) {
        if (line.find("Total goals for ") == 0) {
            string team = getTeamName(line);
            out << getTotalGoalsForTeam(team) << endl;
        } else if(line.find("Mean goals per game for ") == 0) {
            string team = getTeamName(line);
            out << setprecision(17) << getMeanGoalsPerGameForTeam(team) << endl;
        } else if(line.find("Total goals by ") == 0) {
            string player = line.substr(string("Total goals by ").length());
            out << getTotalGoalsByPlayer(player) << endl;
        } else if(line.find("Mean goals per game by ") == 0) {
            string player = line.substr(string("Mean goals per game by ").length());
            out << setprecision(17) << getMeanGoalsPerGameByPlayer(player) << endl;
        } else if(line.find("Goals on minute ") == 0) {
            size_t pos = line.find_first_of("1234567890");
            int minute;
            line = line.substr(pos);
            stringstream ss(line);
            ss >> minute;
            pos = line.find("by ");
            string player = line.substr(pos + string("by ").length());
            out << getGoalsOnMinuteForPlayer(minute, player) << endl;
        } else if(line.find("Goals on first ") == 0) {
            size_t pos = line.find_first_of("1234567890");
            int minutes;
            line = line.substr(pos);
            stringstream ss(line);
            ss >> minutes;
            pos = line.find("minutes by ");
            string player = line.substr(pos + string("minutes by ").length());
            out << getGoalsOnFirstMinutesForPlayer(minutes, player) << endl;
        } else if(line.find("Goals on last ") == 0) {
            size_t pos = line.find_first_of("1234567890");
            int minutes;
            line = line.substr(pos);
            stringstream ss(line);
            ss >> minutes;
            pos = line.find("minutes by ");
            string player = line.substr(pos + string("minutes by ").length());
            out << getGoalsOnLastMinutesForPlayer(minutes, player) << endl;
        } else if(line.find("Score opens by ") == 0) {
            size_t st = line.find("\"", 0);
            int result;
            if (st == string::npos) { // player
                string player = line.substr(string("Score opens by ").length());
                result = getScoreOpensForPlayer(player);
            } else {
                size_t pos = line.find("\"", st + 1);
                string team = line.substr(st + 1, pos - st - 1);
                result = getScoreOpensForTeam(team);
            }
            out << result << endl;
        } else if (line.at(0) == '"') {
            readInfo(line);
        }

        getline(cin, line);
    }
    out.close();
}
