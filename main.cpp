//
//  main.cpp
//  FinalProject
//
//  Created by Michael Montella on 4/24/16.
//  Copyright © 2016 Michael Montella. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include "statTree.h"

using namespace std;



int main(int argc, char * argv[]) {
    
    StatTree TreeStat;
    
    ifstream inFile;
    inFile.open(argv[1]);
    if (inFile.good()) {
        //cout << "Thou file twas opened with thy greatest of successes" << endl;
        string data;
        
        while(getline(inFile, data)) {
            stringstream ss(data);
            
            // Season
            string season;
            getline(ss, season, ',');
            // Points
            string points;
            getline(ss, points, ',');
            // Games
            string games;
            getline(ss, games, ',');
            // Games Started
            string gamesStarted;
            getline(ss, gamesStarted, ',');
            // Field Goal
            string fieldGoal;
            getline(ss, fieldGoal, ',');
            // 3 Point
            string threePoint;
            getline(ss, threePoint, ',');
            // 2 Point
            string twoPoint;
            getline(ss, twoPoint, ',');
            // Free Throw
            string freeThrow;
            getline(ss, freeThrow, ',');
            // Average Points
            string averagePoints;
            getline(ss, averagePoints, ',');
            
            TreeStat.addStatNode(season, stoi(points), stoi(games), stoi(gamesStarted), stod(fieldGoal), stod(threePoint), stod(twoPoint), stod(freeThrow), stod(averagePoints));
            
        }
    }
    
    int choice = 0;
    while (choice != 4) {
        TreeStat.printMenu();
        cin >> choice;
        
        if (choice == 1) {      // Calculate total points scored
            TreeStat.printTotalPoints();
        } else if (choice == 2) {
            string choice2;
            cin.ignore();
            
            cout << "What would you like to rank by?" << endl;
            cout << "1. Total points" << endl;
            cout << "2. Average Points per game" << endl;
            cout << "3. 3 Point percentage" << endl;
            
            getline(cin, choice2);
            if (stoi(choice2) == 1) {
                TreeStat.rankByPoints();
            } else if (stoi(choice2) == 2) {
                cout << endl;
                TreeStat.rankByAvgPoints();
                cout << endl;
            } else if (stoi(choice2) == 3) {
                TreeStat.rankByThreePoint();
            }
            
        } else if (choice == 3) {
            string year;
            string yearWithoutHyphen;
            bool pass = false;
            cin.ignore();
            while(!pass) {
                yearWithoutHyphen = "";
                pass = true;

                cout << "Which season would you like to look at?" << endl;
                cout << "Enter the last 2 digits of each year like this: 'yy-yy'  (i.e. for Kobe's first season, put '96-97'" << endl;
                cin.sync(); // Fixes false negative issue
                getline(cin, year);

                // Removing spaces from string
                year.erase(std::remove_if(year.begin(), year.end(), ::isspace), year.end());

                // Checking to see if third character is hypen
                if (year.at(2) != 45) {
                    pass = false;
                }

                // Making year without hyphen
                for (int i = 0; i < year.length(); i++) {
                    if (i != 2) // Ignoring assumed position without hyphen
                        yearWithoutHyphen += year.at(i); // New string won't include hyphen
                }
                // Checking if every digit in OG year (except hyphen) is a digit 0-9
                for (int i = 0; i < yearWithoutHyphen.length(); i++) {
                    if (!isdigit(yearWithoutHyphen.at(i))) {
                        pass = false;
                        break;
                    }
                }
                // Checking if year is 4 total characters
                if (yearWithoutHyphen.length() != 4)
                    pass = false;
            }
            TreeStat.printSeasonStats(year);
            
        } else if (choice == 4) {
            cout << "Goodbye" << endl;
        }
    }
}
