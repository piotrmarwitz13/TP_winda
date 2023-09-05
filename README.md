# TP Projekt - Piotr Marwitz

## Opis działania projektu:
Projekt polegał na zaprojektowaniu windy, która optymalnie porusza się między piętrami, przyjmując i odkładając pasażerów pomiędzy piętrami. Projekt jest wykonany w WIN32 API, z pomocą GDI+.
Każdy obiekt jest podzielony na osobny plik .h.

Użyte został algorytm SCAN do sortowania requestów windy i Erase-Idiom do usuwania wybranych elementów wektora.
framework.h zawiera większość stałych do ew. konfiguracji programu.
## Ogólne działanie windy
Winda działa na sposób “stanowy”, czyli zależnie od określonego stanu windy inaczej się zachowuje. Te stany to:

* WINDA_IDLE - stan początkowy windy, używany tylko gdy nie ma żadnych pasażerów na ekranie i wszystkie requesty zostały spełnione.
* WINDA_RUCH - stan, w którym winda porusza siebie i pasażerów w środku pomiędzy piętrami.
* WINDA_DRZWI - stan pośredni, służący głównie do otwierania i zamykania drzwi, lecz także do usuwania requestów gdy drzwi są już zamknięte.
* WINDA_STOP - stan, w którym winda odbiera a także oddaje pasażerów na odpowiednie piętro, usuwając tych którzy spełnili całą swoją podróż.

Każdy stan ma odpowiednią metodę windy przypisaną do siebie.

