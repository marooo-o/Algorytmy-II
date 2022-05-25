# Algorytmy-II
**Projekt na przedmiot Algorytny II**

Jakub Hoderny

- ustalenie wejścia z podziałem na karczmy, skrzyżowania,
  pola, browary, drogi i jęczmień
- przygotowanie przykładowego wejścia/wyjścia w celu
  obrazowania poprawności działania programu
- przygotowanie graficznej interpretacji grafu ważonego
  w celu zwizaulizowania przykładowego wejścia
- zaprogramowanie funkcji w programie, które odpowiadają
  za funkcjonalność algorytmów (ford-fulkerson, brute-force,
  dodawanie przepustowości)
- przygotowanie pełnej dokumentacji

---------------------------------------------------------

Oliwer Mroczkowski

- przygotowanie struktur, ich zależności i funkcji w nich występujących,
  koniecznych do poprawnego działania programu
- skontruowanie programu głównego projektu (main)
- zaprogramowanie odpowiedniego wejścia wraz z walidacją
  wpisywanych liczb/obiektów
- zaprogramowanie funkcji w programie, które odpowiadają
  za funkcjonalność algorytmów (bfs, konstruowanie grafu)
- przygotowanie dowodu działania algorytmów

---------------------------------------------------------

Olivier Sokołowski

- wczytanie danych
- otoczka wypukła
- znajdowanie granic królestwa
- przynależność punktu do wielokąta
- przydział pól do ćwiartek

---------------------------------------------------------

Adam Rudlicki

- projektowanie wejscia dla algorytmu minimalnego kosztu
- wczytywanie danych z pliku
- algorytm najtańszej śieżki
- max flow min cost



##Paragraf I

*OBSŁUGA*

    -Wejście wklejamy do pliku input.txt
    -Uruchamiamy a.exe
    -Wynik programu zostanie wyświetlony w terminalu

*INPUT*

    W pierwszej linijce wejścia muszą znajdować się 3 oddzielone spacjami liczby: sumaryczna liczba obiektów (karczm, skrzyżowań, pól, browarów), liczba dróg, i liczba jęczmieńa jaką produkują pola.
    Niech n = liczba obiektów. Następne n linijek opisuje obiekty. Pierwszy znak oddzielony od reszty linijki spacją wyznacza rodzaj i-tego obiektu, gdzie i to numer linijki (od 1 do n).
    Jeśli pierwszy znak to
        • f: opisujemy pole, kolejne 2 liczby to x i y tego pola na mapie.
        • i: opisujemy skrzyżowanie, kolejne 2 liczby to x i y tego skrzyżowania
        • t: opisujemy karczmę, kolejne 2 liczby to x i y, a 3 liczba to ilość piwa, jaką może sprzedać karczma
        • b: opisujemy browar, kolejne 2 liczby to x i y, a 3 liczba to ilość jęczmienia, jaką karczma jest w stanie przerobić na piwo.

    Niech m = liczba dróg. Kolejne m linijek opisuje każdą z dróg. Opis składa się z 4 liczb oddzielonych spacjami: 1 i 2 liczba to numery obiektów, które łączy droga. 
    Następne dwie liczby to przepustowość jęczmienia przez drogę (ile może przez drogę przechodzić piwa) i przepustowość piwa.
 
*PRZYKŁAD*

```
Input:
6 6 7
f 1 2
f 2 2
i 3 3
b 4 3 4
b 4 5 8
t 5 4 12
1 3 6 2
2 3 7 2
3 4 6 10
3 5 7 10
4 6 0 6
5 6 0 5

Out:
11
```

![](https://i.imgur.com/HcW058Y.png)

*TESTOWANIE*

    By włączyć testowanie programu, należy skompilować go z flagą "-DTEST".
    Wykonanie go włączy sprawdzanie randomizowanych przykładów, dopóki program nie zostanie zakończony.

*DOWÓD*

    Opisany świat można reprezentować jako graf,
    którego wierzchołki to pola, browary, karczmy lub skrzyżowania, a krawędzie to ścieżki pomiędzy tymi wierzchołkami.
    Na każdej krawędzi mamy zdefiniowane, dwa parametry - przepustowość zboża i przepustowość piwa. 


    Problem można przedstawić jako problem maksymalnego przepływu.
    Do czynienia mamy jednak ze dwoma przepływami - w jednym przepływa zboże, a drugim piwo.
    Możemy więc podwoić graf, tak że nowy graf ma dwie warstwy z zduplikowanymi wierzchołkami i krawędziami. 
    Jedna z tych warstw będzie służyła przedstawieniu przepływu piwa, a druga przepływowi zboża, w związku z tym,
    w jednej z nich na krawędziach wagami (/przepustowościami) będą przepustowości zboża a w drugiej piwa. 
    Także wiemy, że w browarze można przerobić daną ilość x zboża na x piwa. Oznacza to, że w takim grafie,
    istnieje krawędź pomiędzy obydwoma wierzchołkami odpowiednimi danemu browarowi, której przepustowość to x.
    Do browaru wpłynie maksymalnie x zboża, całe zboże jakie wpłynie zostanie przetworzone na piwo, 
    czyli przepłynie do drugiego grafu tą krawędzią i będzie wypływać z browaru jako zboże. 

    Do naszego grafu brakuje dodać tylko dwa sztuczne wierzchołki - źródło i odpływ.
    Chcemy, żeby z każdego pola mogło wypływać limit zboża, gdzie limit to limit produkcji każdego z pól. 
    Jest to równoznaczne ze stworzeniem krawędzi źródło - pole o przepustowości limit. 
    Tworzymy, więc takie krawędzie dla każdego pola i analogicznie od każdej karczmy prowadzimy krawędź do odpływu.
    Po zaaplikowaniu dowolnego algorytmu maksymalnego przepływu na tak skonstruowanym grafie dostajemy odpowiedź.

    Powyższy graf zostanie przekształcony w graf przepływowy o następującym kształcie:
![](https://i.imgur.com/86bkVAI.png)

    Kod stosuje algorytm Forda-Fulkersona lub algorytm push-relabel by znaleźć odpowiedź.
