#include <iostream>
#include <fstream>

using namespace std;

class Monkey{
    string name;
    int age;
    float tailLength;
    float weight;

public:

    string getName() const{
        return name;
    }

    bool operator<(const Monkey&o) const{
        return getName() < o.getName();
    }

    friend istream& operator>>(istream& in, Monkey &o);
    friend ostream& operator<<(ostream& out, const Monkey &o);
};

istream& operator>>(istream& in, Monkey &o){
    in >> o.name >> o.age >> o.tailLength >> o.weight;
    return in;
}
ostream& operator<<(ostream& out, const Monkey &o){
    out << o.name << " " << o.age << " " << o.tailLength << " " << o.weight;
    return out;
}

template<class T>
class SeqInput{
    ifstream f;
    T actual;
public:
    SeqInput(string fname){
        f.open(fname.c_str());
    }
    void init(){
        f >> actual;
    }
    T current() const{
        return actual;
    }
    void next(){
        f >> actual;
    }
    bool isEnd() const{
        return f.eof();
    }
};

template<class T>
class SeqOut{
public:
    virtual write(const T &v) = 0;
};

template<class T>
class SeqOutFile : public SeqOut<T>{
    ofstream f;
public:
    SeqOutFile(string fname){
        f.open(fname.c_str());
    }
    void write(const T &v){
        f << v << endl;
    }
};

template<class T>
class SeqOutConsole : public SeqOut<T>{
public:
    void write(const T &v){
        cout << v << endl;
    }
};

template<class T>
void intersect(SeqInput<T> &en1, SeqInput<T> &en2, SeqOut<T> &out){
    en1.init();
    en2.init();
    while(!en1.isEnd() && !en2.isEnd()){
        if(en1.current() < en2.current()){
            en1.next();
        }else if(en2.current() < en1.current()){
            en2.next();
        }else{ // en1.current() == en2.current()
            out.write(en1.current());
            en1.next();
            en2.next();
        }
    }
}

template<class T>
void unio(SeqInput<T> &en1, SeqInput<T> &en2, SeqOut<T> &out){
    en1.init();
    en2.init();
    while(!en1.isEnd() || !en2.isEnd()){
        if(en2.isEnd() ||
           (!en1.isEnd() &&en1.current() < en2.current() )
            ){

            out.write(en1.current());
            en1.next();
        }else if(en1.isEnd() ||
            (!en2.isEnd() && en2.current() < en1.current())
             ){
            out.write(en2.current());
            en2.next();
        }else{ // en1.current() == en2.current()
            out.write(en1.current());
            en1.next();
            en2.next();
        }
    }
}


int main()
{
    SeqInput<Monkey> en1("input.txt");
    SeqInput<Monkey> en2("input2.txt");
    SeqOutFile<Monkey> out("out.txt");
    SeqOutConsole<Monkey> out2;
    unio(en1,en2,out2);

    return 0;
}
