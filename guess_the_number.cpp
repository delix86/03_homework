#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <random>
#include <map>

int random_number(int &max_value);
int random_number2(int &max_value); // <random> from C++ 11
int write_highScore(std::string high_scores_filename, std::string user_name, int attempts_count);
// TASK #4
int write_highScoreMin(std::string high_scores_filename, std::string user_name, int attempts_count);
int read_highScore(std::string high_scores_filename);
int read_highScoreMin(std::string high_scores_filename); // TASK #3
int gues_Number(int &attempts_count, const int &target_value);

int main(int argc, char **argv)
{
    int max_value{100};
    const std::string high_scores_filename = "high_scores.txt";
    int target_value{0};
    bool not_win = true;
    std::string user_name;
    int attempts_count{0};
    
    std::string arg1_value{};
    int arg2_value{0};

    // argc - it is a count of arguments
    // But there is some detail - OS always pass one system argument - the name of the executable
    // So, is the application was executed without arguments at all, argc will be still == 1
    switch (argc)
    {
    case 1:
        std::cout << "We have one argument!" << std::endl;
        std::cout << "argv[0] = " << argv[0] << std::endl;

        // Ask about name
        std::cout << "Hi! Enter your name, please:" << std::endl;
        std::cin >> user_name;

        target_value = random_number(max_value);
        gues_Number(attempts_count, target_value);
        // write_highScore(high_scores_filename, user_name, attempts_count);
        write_highScoreMin(high_scores_filename, user_name, attempts_count);
        // read_highScore(high_scores_filename);
        read_highScoreMin(high_scores_filename);
        break;
    case 2:
        // TASK #2
        std::cout << "We have two arguments!" << std::endl;
        std::cout << "argv[0] = " << argv[0] << std::endl;
        std::cout << "argv[1] = " << argv[1] << std::endl;
        arg1_value = argv[1];
        if (arg1_value == "-table")
        {
            // read_highScore(high_scores_filename);
            read_highScoreMin(high_scores_filename);
        }
        break;
    case 3:
        std::cout << "We have two arguments!" << std::endl;
        std::cout << "argv[0] = " << argv[0] << std::endl;
        std::cout << "argv[1] = " << argv[1] << std::endl;
        std::cout << "argv[2] = " << argv[2] << std::endl;

        // Ask about name
        std::cout << "Hi! Enter your name, please:" << std::endl;
        std::cin >> user_name;

        arg1_value = argv[1];
        // TASK #1
        if (arg1_value == "-max")
        {
            arg2_value = std::stoi(argv[2]);
            std::cout << "The '" << arg1_value << "' value = " << arg2_value << std::endl;
            max_value = arg2_value;
            target_value = random_number2(max_value);
            gues_Number(attempts_count, target_value);
            // write_highScore(high_scores_filename, user_name, attempts_count);
            write_highScoreMin(high_scores_filename, user_name, attempts_count);
            // read_highScore(high_scores_filename);
            read_highScoreMin(high_scores_filename);
            break;
        }
        // TASK #5
        if (arg1_value == "-level")
        {
            arg2_value = std::stoi(argv[2]);
            std::cout << "The '" << arg1_value << "' value = " << arg2_value << std::endl;
            if (arg2_value == 1)
                max_value = 10;
            if (arg2_value == 2)
                max_value = 50;
            if (arg2_value == 3)
                max_value = 100;
            target_value = random_number2(max_value);
            gues_Number(attempts_count, target_value);
            // write_highScore(high_scores_filename, user_name, attempts_count);
            write_highScoreMin(high_scores_filename, user_name, attempts_count);
            // read_highScore(high_scores_filename);
            read_highScoreMin(high_scores_filename);
            break;
        }
        break;
    }
    return 0;
}

int random_number(int &max_value)
{
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    int random_value = std::rand() % max_value;
    return random_value;
}

int random_number2(int &max_value)
{
    std::random_device rd;                   // used to seed the default_random_engine
    std::default_random_engine engine{rd()}; // rd() produces a seed
    std::uniform_int_distribution<> randomNum{1, max_value};
    const int random_num{randomNum(engine)};
    return random_num;
}

// Write new high score by apppend to the end of the records table
int write_highScore(std::string high_scores_filename, std::string user_name, int attempts_count)
{
    // We should open the output file in the append mode - we don't want
    // to erase previous results.
    std::ofstream out_file{high_scores_filename, std::ios_base::app};
    if (!out_file.is_open())
    {
        std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
        return -1;
    }

    // Append new results to the table:
    out_file << user_name << ' ';
    out_file << attempts_count;
    out_file << std::endl;
    return 0;
}

// Write new high score to the user in records table
int write_highScoreMin(std::string high_scores_filename, std::string user_name, int attempts_count)
{
    std::string line;

    // open input file
    std::ifstream in_file{high_scores_filename};
    if (!in_file.is_open())
    {
        std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
        return -1;
    }

    // now open temp output file
    std::ofstream out_file{"outfile.txt", std::ios_base::app};

    int min_user_score{attempts_count}; // min score for curren user

    std::string temp_name;
    int temp_score;
    while (!in_file.eof())
    {
        if (in_file.fail())
        {
            break;
        }

        // Read the username first
        in_file >> temp_name;
        // Read the high score next
        in_file >> temp_score;
        // Ignore the end of line symbol
        in_file.ignore();

        if (in_file.eof())
        {
            break;
        }

        if (temp_name != user_name && temp_name != "")
        {
            out_file << temp_name << ' ';
            out_file << temp_score;
            out_file << std::endl;
        }

        if (temp_name == user_name && temp_score < min_user_score)
        {
            min_user_score = temp_score;
        }
    }

    out_file << user_name << ' ';
    out_file << min_user_score;
    out_file << std::endl;

    in_file.close();
    out_file.close();

    // delete the original file
    const char *file_name = high_scores_filename.c_str();
    remove(file_name);

    // rename old to new
    rename("outfile.txt", file_name);

    return 0;
}

// Read the high score file and print all results
int read_highScore(std::string high_scores_filename)
{
    std::ifstream in_file{high_scores_filename};
    if (!in_file.is_open())
    {
        std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
        return -1;
    }

    std::cout << "High scores table:" << std::endl;

    std::string username;
    int high_score = 0;
    while (true)
    {
        // Read the username first
        in_file >> username;
        // Read the high score next
        in_file >> high_score;
        // Ignore the end of line symbol
        in_file.ignore();

        if (in_file.fail())
        {
            break;
        }

        // Print the information to the screen
        std::cout << username << '\t' << high_score << std::endl;
    }
    std::cout << "--------------------" << std::endl;
    return 0;
}

// TASK #3
// Read the high score file and print all results
int read_highScoreMin(std::string high_scores_filename)
{
    std::ifstream in_file{high_scores_filename};
    if (!in_file.is_open())
    {
        std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
        return -1;
    }

    std::string username;
    int high_score = 0;
    std::map<std::string, int> map_name_score;

    while (true)
    {
        // Read the username first
        in_file >> username;
        // Read the high score next
        in_file >> high_score;
        // Ignore the end of line symbol
        in_file.ignore();

        if (in_file.fail())
        {
            break;
        }

        // add "name" and "score" to map
        if (map_name_score.count(username) == 0)
        {
            map_name_score.insert(std::pair<std::string, int>(username, high_score));
        }
        else if (map_name_score.count(username) == 1)
        {
            if (map_name_score[username] > high_score) // check if min
            {
                map_name_score[username] = high_score;
            }
        }
    }

    // print map_name_score
    std::cout << "--------------------" << std::endl;
    std::cout << "Min trys table:" << std::endl;
    std::map<std::string, int>::iterator it = map_name_score.begin();
    while (it != map_name_score.end())
    {
        std::cout << it->first << " : " << it->second << std::endl;
        it++;
    }
    std::cout << "--------------------" << std::endl;
    return 0;
}

// gues number
int gues_Number(int &attempts_count, const int &target_value)
{
    int current_value{0};
    std::cout << "Enter your guess:" << std::endl;
    do
    {
        attempts_count++;
        std::cin >> current_value;

        if (current_value < target_value)
        {
            std::cout << "greater than " << current_value << std::endl;
        }
        else if (current_value > target_value)
        {
            std::cout << "less than " << current_value << std::endl;
        }
        else
        {
            std::cout << "you win!" << std::endl;
            break;
        }

    } while (true);

    return 0;
}