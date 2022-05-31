# Algorytmy-II
**Projekt na przedmiot Algorytny II**

## Paragraf III

### *OBSŁUGA*

    -Punkty graniczne każdej ćwiartki zebrane na polecenie Samwise umieszczamy w pliku input.txt
    -Współrzędne pól w królestwie umieszczamy w piliku fields.txt
    -Kompilujemy program przy pomocy polecenia g++ main.cpp
    -Uruchamiamy propram wpisując w konsole ./a.out <argument> gdzie arugment oznacza:
                         1 - zapis w pliku pól należących do ćwiartek
                         2 - wyświetlenie w konsoli granic ćwiartek oraz pól do nich należących
    -Otrzymujemy w konsoli granice każdej ćwiartki oraz pola przynależących do niej
    
 ---------------------------------------------------------

### *INPUT*

W pierwszej linijce pliku input.txt umieszczamy ilość ćwiartek w naszym królestwie, następnie dla każdej ćwiartki trzeba podać ilość punktów granicznych, następnie podajemy punkty graniczne każdej z ćwiartek, w kolejności w jakiej podawaliśmy ilość punktów granicznych.
Następnie w pliku fields na samej górze podajemy ilość pól w całym pliku, następnie umieszczamy po prostu punkty w dowolnej kolejności, które zostaną przydzielone do odpowiednich ćwiartek. 

 ---------------------------------------------------------
### *PRZYKŁAD*

```
Input:
 2 <------- ilość ćwiartek królestwa
 8 <------- ilość punktów granicznych w pierwszej ćwiartce
 9 <------- ilość punktów granicznych w drugiej ćwiartce
-2 8 <----- punkty pierwszej ćwiartki
2 6
6 4
8 4
8 6
6 8
4 10
0 10
-6 2 <------ punkty drugiej ćwiartki
-4 1
-2 4
-2 6
-4 8
-6 8
-8 8
-8 6
-8 4

Fields: 
10 <------ ilość pól
0 8
2 8
4 8
4 6
6 6
-6 6
-3 6
-6 4
-4 4
-4 2


```
 ---------------------------------------------------------
 ### Podgląd wizualny podanych pól i ćwiartek
 
![pole 3](https://user-images.githubusercontent.com/82097861/170314182-bb0b2a8f-8cfe-41a2-b3ca-998608a47bb8.png) 
![pole 2 -p](https://user-images.githubusercontent.com/82097861/170314641-ac1cc41c-d978-4a79-9c19-b1d17206c715.png)

 ---------------------------------------------------------
 
 ### *OUTPUT*
 Wywołanie dla argumentu 1(zapis w pliku input2.txt)
 ```
 c1
0 8
2 8
4 8
4 6
6 6
c2
-6 6
-3 6
-6 4
-4 4
-4 2
 ```
 Wywołanie dla argumentu 2(wyświetlenie w konsoli ćwiartek oraz pół przynależących do nich)
 
 ```
granice cwiartki nr: 1
-2 8
6 4
8 4
8 6
4 10
0 10
pola wewnątrz cwiartki nr : 1
0 8
2 8
4 8
4 6
6 6

granice cwiartki nr: 2
-8 4
-6 2
-4 1
-2 4
-2 6
-4 8
-8 8
pola wewnątrz cwiartki nr : 2
-6 6
-3 6
-6 4
-4 4
-4 2

 ```
  ---------------------------------------------------------
  
 ### *Dowód*

   Problem podziału królestwa  można przedstawić jako poszukiwanie otoczki wypukłej, a przynależność do niej pól jako przynależność punktu do wielokąta, w tym wypadku wypukłego. Spośród zbioru punktów granicznych każdej ćwiartki, które rozkazał zebrać Samwise, wybieramy podzbiór, który tworzy najmniejszy wielokąt wypukły zawierający wszystkie punkty. W tym celu w rozwiązaniu został wykorzystany Algorytm Jarvisa, który polega na tym, aby znaleźć punktu p0 o najmniejszej współrzędnej y, jeśli takich jest kilka, bierzemy ten o najmniejszej współrzędnej x. Następnie bierzemy punkt s dowolny, różny od p0 i sprawdzamy czy po prawej stronie wektora p0-s leży jakiś punkt, jeśli tak to bierzemy go za s i powtarzamy to dla punktów, które nie są jeszcze w otoczce. 

   Podstawowym faktem z geometrii obliczeniowej na płaszczyźnie, który był niezbędny w rozwiązaniu problemu, jest fakt po której stronie wektora leży punkt, a więc jeśli mamy punkty p, q, r należy policzyć wyznacznik macierzy w 3x3 gdzie w 1 i 2 kolumnie wpisujemy pod sobą kolejno współrzędne punktów p,q,r a ostatnia kolumna jest uzupełniona jedynkami. 

   Wyznacznik większy od zera oznacza, że punkt r leży po lewej stronie wektora p->q, równy zero oznacza, że punkty są współlinowe, a mniejszy od zera, że punkt r leży po prawej stronie wektora p->q

   w celu określenia przynależności pola do ćwiartki został wykorzystany problem przynależności puntku do wielokąta wypukłego, założone zostało, że punkty leżące na granicy ćwiartki do niej NIE należą. Wykorzystany w rozwiązaniu algorytm polega, na wyznaczeniu półprostej o początku w sprawdzanym punkcie, oraz sprawdzaniu ile razy ta półprosta przecina boki wielokąta. Jeśli przecina parzystą ilość razy punkt leży na zewnątrz, w przeciwnym wypadku wewnątrz, dzięki wypukłości wielokąta, możliwe było uniknięcie wielu problemów z przynależnością punktu, jednym który pozotał był przypadek gdy półprosta przecinała złączenie dwóch boków wielokąta

![Zrzut ekranu 2022-05-25 o 19 49 22](https://user-images.githubusercontent.com/82097861/170329929-d0512a92-9c94-4999-b1b9-c47098822cf8.png)

   Problem został rozwiązany zaliczając jedynie przecięcie w górnej części odcinka, aby unikąć podwójego zliczania, działa to poprzez wybieranie maksimum na y z dwóch końców odcinka, dzięki takiemu udało się poradzić nawet z tak szczególnymi sytacjami jak widoczne na zdjęciu ponieżej. 
   
   ![Zrzut ekranu 2022-05-25 o 20 05 48](https://user-images.githubusercontent.com/82097861/170336560-47f5716a-e202-40f5-b5e0-04bc1ea0b431.png)

Została jeszcze kwestia przecinania odcinka i półprostej, półprosta w rozwiązaniu jest reprezentowana jako odcinek, wybieramy najdalej wysunięty na prawo x i do niego dodajemy dużą wartość, a y jest taki sam jak sprawdzanego punktu. A więc dwa odcinki p-q i r-s przecinają się gdy p i q leżą po przeciwnych stronach prostej r-s, a punkty r i s po przeciwnych stronach prostej p-q także det(p,q,r) różny od det(p, q, s) oraz det(r,s,p) różny od(det r,s,q). 
   
 ---------------------------------------------------------
 ### Uwagi
 
 Ćwiartki należy podawać tak aby były rozłączne, pola, które nie należą do żadnej ćwiartki są pomijane, pola leżące na granicach ćwiartek również. 
 
  ---------------------------------------------------------
  
  ### *Dokumentacja*
  
  Dokumentacja znajduję się w pliku main.cpp nad każdą metodą oraz klasą znajdują się komentarze opisujące co dana metoda robi, jakie przyjmuje parametry oraz co zostaje zwrócone
  
 ---------------------------------------------------------
    
  ### *Testy*
  
  W katalogu tests znajduje się plik main-kopia.cpp jest to kopia pliku main.cpp z katalogu głównego, która została zmienione jedynie o gotowe ścieżki do różnych danych testowych. W katalogach inputs oraz fields znajdują się dane do testowania z czego numerki przy ich nazwach odpowiadają sobie tzn. jeśli pola nazwyają się fields3.txt są testowane z input3.txt na szczęście użytkownik nie musi się o to martwić, ponieważ ścieżki do katalogów są ustawione na sztywno w main-kopia.cpp. 
   
### *OBSŁUGA*
    -Wchodzimy do katalogu tests
    -Kompilujemy program przy pomocy polecenia g++ main-kopia.cpp -o tests 
    -Uruchamiamy propram wpisując w konsole ./tests <argument> gdzie arugment oznacza:
                         1 - użycie danych testowych z plików input.txt oraz fields
                         3 - użycie danych testowych z plików input3.txt oraz fields3.txt
                         4 - użycie danych testowych z plików input4.txt oraz fields4.txt
    -Otrzymujemy w konsoli granice każdej ćwiartki oraz pola przynależących do niej, a w katalogu tests otrzymujemy plik input-tests.txt z polami należącymi do każdej ćwiartki rozdzielonych c<numer ćwiartki> np. c3 gdzie 3 to numer ćwiartki 
