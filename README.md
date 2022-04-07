# Algorytmy-II
**Projekt na przedmiot Algorytny II**

##Paragraf I

*OBSŁUGA*

    -Wejście wklejamy do pliku input.txt
    -Uruchamiamy main.exe
    -Wynik programu pojawi się w pliku output.txt

*INPUT I OUTPUT*

    Założona jest poprawność wejścia
    W pierwszym wierszu mamy podane p, b, k, d (0 <= p, b, k, d, s) oznaczające kolejno liczbę pól, browarów, karczm, dróg, skrzyżowań.
    Każda kategoria jest numerowana od 1 do ilosci obiektów.
    Kolejne p wierszy oznacza liczbę produkcji zboża kolejnych pól.
    Następne b wierszy oznacza moce przerobowe kolejnych browarów.
    Ostatnie d wierszy jest formatu (pp, pz, ob1, ob2, id1, id2) oznaczające kolejno:
    maksymalną przepustowość piwa, maksymalną przepustowość zboża, kategorię obiektu pierwszego, kategorię obiektu drugiego,
    id obiektu pierwszego, id obiektu drugiego. (0 <= pp, pz) (ob1, ob2 = {p, b, k, d, s}) (0 < id1 < ob1, 0 < id2 < ob2)
 
*PRZYKŁAD*

```
Input:
2 1 3 7 1
10
2
4
0 0 p p 1 2
1 2 p b 1 1
3 5 b p 1 2
2 0 b s 1 1
1 0 s k 1 2
0 1 s k 1 3
1 1 k s 1 1

Out:
2
```

![](https://i.imgur.com/MPVHWMj.png)