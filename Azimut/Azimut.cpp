#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_set>

bool check_string (const std::string& first_string, const std::string& second_string)
{
    size_t first_index {0};
    size_t second_index {0};
    while (first_index < first_string.size() && second_index < second_string.size())
    {
        while (first_string[first_index] == ' ' || first_string[first_index] == '0')
        {
            first_index ++;
        }

        while (second_string[second_index] == ' ' || second_string[second_index] == '0')
        {
            second_index ++;
        }

        if (second_string[second_index] == first_string[first_index])
        {
            first_index ++;
            second_index ++;
        }
        else
        {
            std::cout << "It's not equial";
            return false;
        }
    }
    std::cout << "It's equial";
    return true;
}


std::string string_filter (const std::string & old_string)
{
    std::string new_string;
    //if (!old_string.empty())
    {
        for (auto char_element : old_string)
        {
            if (char_element != '0' && char_element != ' ' )
            {
                new_string.push_back(char_element);
            }
        }
    }
    return new_string;
}


// Упорядоченное множество - файл заполняется при обходе
void file_processing_us_search (std::string file_input, std::string file_output)
{
    std::ifstream in_1 (file_input);
    std::ofstream out_1 (file_output);
    std::unordered_set<std::string> my_set;

    if (in_1.is_open())
    {
        std::string buffer_string;
        while (getline(in_1, buffer_string))
        {
            // данную часть можно выделить в отдельную функцию, но потеря прозводительности будет около 10-15%
            std::string clean_string;
            for (auto char_element : buffer_string)
            {
                if (char_element != '0' && char_element != ' ' )
                {
                    clean_string.push_back(char_element);
                }
            }
            
            if (!my_set.count(clean_string))
            {
                my_set.insert(clean_string);
                out_1 << clean_string << std::endl;
            }
        }
    }
    in_1.close();
    out_1.close();
}


int main()
{
    std::thread th1 (file_processing_us_search, "1_in.txt", "1_out.txt");
    std::thread th2 (file_processing_us_search, "2_in.txt", "2_out.txt");
    
    th1.join();
    th2.join();
    
    return 0;
}
