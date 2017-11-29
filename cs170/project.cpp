// g++ -O3 -std=c++11 project2.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct instance{
    //data[i] contains the value of the ith feature
    vector<float> data;
    float group;
};

struct search_wrapper{
    vector<instance*> entries; // holds all of the instances of data
    vector<int> features; // holds the current "state" of each feature
    vector<int> solution_features;
    float solution_accuracy;

    void load_data(ifstream &ifile){
        cout << "\nReading data...";

        string shold;
        while(getline(ifile, shold)){
            entries.push_back(new instance);

            istringstream in(shold.c_str());
            in >> entries[entries.size()-1]->group;
            while(in >> shold)
                entries[entries.size()-1]->data.push_back(stof(shold));
        }
    }

    // [0,1] normalizing
    void normalize_data(){
        cout << "Normalizing data...";

        int min, max;

        for(int i = 0; i < features.size(); i++){
            min = entries[0]->data[i];
            min = max;

            for(int j = 1; j < entries.size(); j++){
                if(entries[j]->data[i] > max)
                    max = entries[j]->data[i];

                if(entries[j]->data[i] < min)
                    min = entries[j]->data[i];
            }

            for(int j = 0; j < entries.size(); j++)
                entries[j]->data[i] = (entries[j]->data[i] - min)/(max - min);
        }
    }

    //find the distance between two instances
    float distance(instance* a, instance* b){
        float current_distance = 0;
        for(int i = 0; i < features.size(); i++){
            if(!contains_feature(i))
                continue;
            current_distance += (a->data[i]-b->data[i])*(a->data[i]-b->data[i]);
        }
        return current_distance;
    }

    //find the group of the nearest neighbor of an instance
    int nn_classifier(instance* current_instance){
        int i = 0;
        if(current_instance == entries[i])
            i++;

        int group = entries[i]->group;
        float min_distance = distance(current_instance, entries[i]);
        float current_distance;

        for(i = 0; i < entries.size(); i++){
            if(current_instance == entries[i])
                continue;

            current_distance = distance(current_instance, entries[i]);
            if(current_distance < min_distance){
                min_distance = current_distance;
                group = entries[i]->group;
            }
        }
        return group;
    }

    // calculates accuracy of analyzing a subset of features
    float loo_validator(){
        int count = 0;
        for(int i = 0; i < entries.size(); i++)
            if(nn_classifier(entries[i]) == entries[i]->group)
                count++;

        return static_cast<float>(count)/static_cast<float>(entries.size());
    }

    void insert_feature(int feature){
        features[feature] = 1;
    }

    bool contains_feature(int feature){
        if(features[feature] == 1)
            return true;
        return false;
    }

    void remove_feature(int feature){
        features[feature] = 0;
    }

    void list_features(){
        cout << "{ ";
        for(int i = 0; i < features.size(); i++)
            if(features[i] == 1)
                cout << i+1 << " ";
        cout << "}";
    }

    void list_solution_features(){
        cout << "{ ";
        for(int i = 0; i < solution_features.size(); i++)
            if(solution_features[i] == 1)
                cout << i+1 << " ";
        cout << "}";
    }

    void print_status(float accuracy){
        cout << "\tUsing feature(s) ";
        list_features();
        cout << " accuracy is ";
        cout << fixed << setprecision(1) << accuracy*100 << " percent\n";
    }

    void print_best(float max_accuracy){
        cout << "\nFeature set ";
        list_features();
        cout << " was best, accuracy is ";
        cout << fixed << setprecision(1) << max_accuracy*100 << " percent\n\n";
    }

    void print_solution(){
        cout << "Solution: Features ";
        list_solution_features();
        cout << " with an accuracy of ";
        cout << fixed << setprecision(1) << solution_accuracy*100 << " percent\n";
    }

    virtual void search() = 0;
};

struct forward_selection : public search_wrapper{
    forward_selection(ifstream &ifile){
        load_data(ifile);
        normalize_data();

        while(features.size() < entries[0]->data.size())
            features.push_back(0);
    }

    void search(){
        int max_feature;
        float max_accuracy;
        float accuracy;

        cout << "Beginning search.\n\n";

        for(int f = 0; f < features.size(); f++){
            max_accuracy = -1;
            for(int i = 0; i < features.size(); i++){
                if(contains_feature(i))
                    continue;

                insert_feature(i);

                // check leave-one-out accuarcy
                accuracy = loo_validator();
                if(accuracy > max_accuracy){
                    max_accuracy = accuracy;
                    max_feature = i;
                }

                print_status(accuracy);

                remove_feature(i);
            }
            insert_feature(max_feature);

            if(solution_accuracy < max_accuracy){
                solution_accuracy = max_accuracy;
                solution_features = features;
            }
            print_best(max_accuracy);
        }
        print_solution();
    }
};

struct backward_elimination : public search_wrapper{
    backward_elimination(ifstream &ifile){
        load_data(ifile);
        normalize_data();

        while(features.size() < entries[0]->data.size())
            features.push_back(1);
    }

    void search(){
        int max_feature;
        float max_accuracy;
        float accuracy;

        cout << "Beginning search.\n\n";

        // print default state
        cout << "Using all feature(s), accuracy is ";
        cout << fixed << setprecision(1) << loo_validator()*100 << " percent\n";

        for(int f = 1; f < features.size(); f++){
            max_accuracy = -1;
            for(int i = 0; i < features.size(); i++){
                if(!contains_feature(i))
                    continue;

                remove_feature(i);

                // check leave-one-out accuarcy
                accuracy = loo_validator();
                if(accuracy > max_accuracy){
                    max_accuracy = accuracy;
                    max_feature = i;
                }

                print_status(accuracy);

                insert_feature(i);
            }
            remove_feature(max_feature);

            if(solution_accuracy < max_accuracy){
                solution_accuracy = max_accuracy;
                solution_features = features;
            }
            print_best(max_accuracy);
        }
        print_solution();
    }
};

int main(){
    string file_name;
    ifstream ifile;
    int search_type;
    search_wrapper* algorithm;

    // get file name to test
    cout << "Type the name of the file to test: ";
    cin >> file_name;

    ifile.open(file_name.c_str());
    while(!(ifile.is_open())){
        cout << "Please enter a valid file name: ";
        cin >> file_name;
        ifile.open(file_name.c_str());
    }

    // get search algorithm to use
    cout << "\n1) Forward Selection\n";
    cout << "2) Backward Elimination\n\n";
    cout << "Type the number of the algorithm you want to run: ";
    cin >> search_type;

    while(search_type < 1 || search_type > 2){
        cout << "Please enter a valid choice: ";
        cin >> search_type;
    }

    // initialize selected algorithm
    if(search_type == 1)
        algorithm = new forward_selection(ifile);
    else
        algorithm = new backward_elimination(ifile);

    // search and destroy
    algorithm->search();

    return 0;
}
