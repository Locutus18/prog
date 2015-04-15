#Felsoroló

Ahogy az órák alatt nagyon sokszor az általánosítást vettük fókuszba, most is azt fogjuk. Nézzünk meg egy egyszerű alaptételt:

```c++
int sum(const vector<int> &v){
  int s = 0;
  for(int a=0;a<v.size();a++){
    s += v[a];
  }
  return s;
}
```

Az ```int``` típust template-el könnyedén kitujduk általánosítani, viszont ahhoz hogy igazán általánosak lehessünk, ahhoz azt is kikéne általánosítani, hogy milyen az az input. Most fixen vector lehet csak.
Most, hogy már tudunk osztályt csinálni készíthetünk egyet ami elfedi előlünk és általánosabban fogalmaz.

Egy felsoroló osztályt fogunk csinálni, ami a nevét nem meghazudtolva annyit csinál csak, hogy felsorol elemeket. De milyen elemeket? Ha templatet használunk bármilyet, anélkül egy fixet. 
Miért jó ez? Megtudjuk úgy csinálni a függvényeinket, hogy ne függjenek már szinte semmitől és akkor teljeskörűen feltudjuk őket újra használni.

Mit is várunk el egy ilyen felsoroló osztálytól? Alakítsuk át az összegzés függvényünket úgy, hogy valami felsorolóból jönnek az értékek mágikusan.

```c++
template<typename T>
int sum(Enumerator<T> &e){
  int s = 0;
  for(e.init();e.isEnd();e.next()){
    s += e.current();
  }
  return s;
}
```

Ez alapján már definiálhatjuk az osztályunkat:
```c++
//Az Enumerator osztály felelős azért, hogy egy elem sorozaton végigiteráljon. Egyszerre mindig csak egy elemre mutat ami a tagfüggvényekkel léptethető csak előre.
template<typename T>
class Enumerator{
public:
  //Inicializálja a felsorolót, az elejére áll az inputnak
  void init() = 0;
  //Jelzi, hogy vége-e van-e már az inputnak (Ha igen, akkor a current értéke ismeretlen)
  bool isEnd() = 0;
  //A következő felsorolandó elemre lép
  void next() = 0;
  
  //Visszaadja, hogy mi az aktuális elem amin a felsoroló áll
  T current() = 0;
};
```
De mit is jelent ez az ```= 0```? Arra jó, hogy meg tudunk adni függvényeket, amit majd a gyerekekben definiálni kell, így kötelezővé tehetjük, hogyha bárki csinál egy ilyen ```Enumeratort```, akkor a szükséges tagfüggvények létezni fognak. 

Ha szépen akarunk dolgozni akkor ebből az osztályból tudunk származtatni egy osztályt ami megvalósítja az eddigi függvényeket.

```c++
//Az Enumerator osztály felelős azért, hogy egy elem sorozaton végigiteráljon. Egyszerre mindig csak egy elemre mutat ami a tagfüggvényekkel léptethető csak előre.
template<typename T>
class VectorEnumerator : public Enumerator<T>{
private:
  vector<T> data;
  int pointer;
public:
  
  VectorEnumerator(const vector<int> &v){
    data.resize(v.size());
    for(int a=0;a<v.size();a++){
      data[a] = v[a];
    }
  }

  void init(){
    pointer = 0;
  }
  bool isEnd(){
    return pointer >= data.size();
  }
  void next(){
    pointer++;
  }
  T current(){
    return data[pointer];
  }
};
```

Ha ez az osztályunk kész van akkor máris használhatjuk az új szumma függvényünket sima int vektorra, mivel ez egy ```Enumerator``` úgy mint ahogy a ```ifstream``` is egy ```istream```. 
```c++

int main(){
  vector<int> v;
  cin >> v; //Ez a függvény ismert, már nagyon sokszor megírtuk.:)
  VectorEnumerator<int> ve(v);
  sum(ve);
}

```