#include <iostream>
#include <string>
#include <vector>
class Student {
    public:
        std :: string get_name(){
            return name;
        };
        void set_name(std :: string student_name){
            name = student_name;
        };
        std :: vector<float> get_scores(){
            return scores;
        };
        void set_scores(std :: vector<float> student_scores){
            scores = student_scores;
            float res = 0;
            for (auto s: student_scores){
                res += s;
            };
            average = res / scores.size();
        };
        float get_average(){
            return average;
        }
    private:
        std :: string name;
        std :: vector<float> scores;
        float average;
};
