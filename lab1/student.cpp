#include "student.h"
int main(){
    std :: string name;
    std :: vector<float> scores;
    int n;
    std :: cout << "Введите имя студента" << std :: endl;
    std::getline(std::cin,name);
    std :: cout << "Введите количество оценок студента" << std :: endl;
    std :: cin >> n;
    std :: cout << "Введите оценки" << std :: endl;
    for (int i = 0; i < n;i++){
       float score; 
       std :: cin >> score;
       scores.push_back(score);
    };
    Student s;
    s.set_name(name);
    s.set_scores(scores);
    std :: cout << s.get_name() << std::endl;
    for (auto s:s.get_scores()){
        std::cout << s << ' ';
    }
    std::cout << '\n' << s.get_average() << std :: endl;
    return 0;
    
}
