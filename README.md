# Algorytmy-II
**Projekt na przedmiot Algorytny II**

## Paragraf III

### *OBSŁUGA*

    -Punkty graniczne każdej ćwiartki zebrane na polecenie Samwise umieszczamy w pliku input.txt
    -Współrzędne pól w królestwie umieszczamy w piliku fields.txt
    -Kompilujemy program przy pomocy polecenia g++ main.cpp
    -Uruchamiamy propram wpisując w konsole ./a.out
    -Otrzymujemy w konsoli granice każdej ćwiartki oraz pól przynależących do niej
    
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
10
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
 ### *Pole 1*
![pole 3](https://user-images.githubusercontent.com/82097861/170314182-bb0b2a8f-8cfe-41a2-b3ca-998608a47bb8.png)

### *Pole 2*
![pole 2 -p](https://user-images.githubusercontent.com/82097861/170314641-ac1cc41c-d978-4a79-9c19-b1d17206c715.png)


