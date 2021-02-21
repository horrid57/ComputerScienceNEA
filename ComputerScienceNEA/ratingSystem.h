#pragma once

#include <iostream>
#include <glicko.h>
#include <fstream>
#include <string>

class GlickoRating {
public:

    float rating = FLT_MAX;
    float deviation = FLT_MAX;
    float opponentRating = FLT_MAX;

    bool loadFromFile(std::string filename = "rating.txt") {
        bool didFileExist = false;

        std::fstream file(filename);

        if (file.is_open()) {
            didFileExist = true;
            std::cout << "File Exists \n";

            // FILE FORMAT:
            // -------
            // rating \n
            // float 
            // EOF
            // -------

            std::string data[2];
            int i = 0;
            while (std::getline(file, data[i])) {
                i++;
            };
            rating = std::stof(data[0]);
            deviation = std::stof(data[1]);

            std::cout << rating << " " << deviation << "\n";
        }
        else {
            std::cout << "File Doesn't Exist \n";
            rating = 0.5;
            deviation = 200;
        }

        file.close();
        return didFileExist;
    }

    void setOpponentRating(float rating) {
        opponentRating = rating;
    }

    float getPlayerRating() {
        return rating;
    }

    void calculateRating(bool gameWon) {
        Glicko::Rating player(rating * 3000, deviation);
        Glicko::Rating opponent(opponentRating * 3000, 50);
        player.Update(opponent, gameWon ? 1 : 0);
        player.Apply();
        rating = player.Rating1() / 3000;

        if (rating > 1) {
            rating = 1;
        }
        if (rating < 0) {
            rating = 0;
        }

        std::cout << rating << "\n";
    }

    void writeRatingToFile(std::string filename = "rating.txt") {
        std::fstream file(filename, std::ios_base::trunc | std::ios_base::out | std::ios_base::in);   // trunc clears the file
        file << std::to_string(rating) + "\n" + std::to_string(deviation);
        file.close();
    }
};
