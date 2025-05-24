#include "Terrain.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

Terrain::Terrain() {
  srand(time(nullptr));
  width = 60;
  height = 30;
  map = vector<vector<TypeTerrain>>(height,
                                    vector<TypeTerrain>(width, OBSTRACLE));
  costTerrain = {{SAFE_PATH, 1}, {DANGER_PATH, 3}, {OBSTRACLE, 100}};
  generateTerrain();
}

Terrain::Terrain(int w, int h) : width(w), height(h) {
  srand(time(nullptr));
  map = vector<vector<TypeTerrain>>(height,
                                    vector<TypeTerrain>(width, OBSTRACLE));

  costTerrain = {{SAFE_PATH, 1}, {DANGER_PATH, 3}, {OBSTRACLE, 100}};
  generateTerrain();
}

void Terrain::generateTerrain() {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      map[i][j] = OBSTRACLE;
    }
  }

  generateMainPath();

  generateAdditionalPaths();

  fillRemainingTerrain();

  smoothTerrain();

  adjustTerrainDistribution();
}

void Terrain::generateMainPath() {
  int x = 0, y = 0;
  map[y][x] = SAFE_PATH;

  while (x < width - 1 || y < height - 1) {
    int direction = rand() % 10;

    if (x < width - 1 && (y >= height - 1 || direction < 6)) {
      x++;
    } else if (y < height - 1) {
      y++;
    }

    map[y][x] = SAFE_PATH;

    // Hacer el camino principal más ancho más frecuentemente
    if (rand() % 2 == 0) {   // 50% probabilidad (antes era 25%)
      makeAreaSafe(x, y, 2); // Radio mayor
    }
  }
}

void Terrain::generateAdditionalPaths() {
  int numPaths = 8 + rand() % 7; // 8-14 caminos adicionales (más que antes)

  for (int p = 0; p < numPaths; p++) {
    int startX = rand() % width;
    int startY = rand() % height;
    int length = 30 + rand() % 50; // Caminos de 30-80 celdas (más largos)

    int x = startX, y = startY;

    for (int i = 0; i < length && x >= 0 && x < width && y >= 0 && y < height;
         i++) {
      // 70% probabilidad de ser camino seguro (antes era 33%)
      if (rand() % 10 < 7) {
        map[y][x] = SAFE_PATH;
      }

      // Movimiento aleatorio
      int dir = rand() % 4;
      switch (dir) {
      case 0:
        x++;
        break; // Derecha
      case 1:
        x--;
        break; // Izquierda
      case 2:
        y++;
        break; // Abajo
      case 3:
        y--;
        break; // Arriba
      }

      // Mantener dentro de límites
      x = max(0, min(width - 1, x));
      y = max(0, min(height - 1, y));
    }
  }
}

void Terrain::fillRemainingTerrain() {
  // Llenar las celdas que siguen siendo obstáculos con la distribución deseada
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (map[i][j] == OBSTRACLE) {
        int probability = rand() % 100;

        if (probability < 60) {
          // 60% caminos seguros
          map[i][j] = SAFE_PATH;
        } else if (probability < 85) {
          // 25% caminos peligrosos (60 + 25 = 85)
          map[i][j] = DANGER_PATH;
        }
        // 15% permanecen como obstáculos (85-100)
      }
    }
  }
}

void Terrain::addDangerZones() {
  // Este método ahora se usa menos, ya que fillRemainingTerrain maneja la
  // distribución
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (map[i][j] == OBSTRACLE) {
        // Verificar si está cerca de un camino seguro
        bool nearSafePath = false;
        for (int di = -2; di <= 2 && !nearSafePath; di++) {
          for (int dj = -2; dj <= 2 && !nearSafePath; dj++) {
            int ni = i + di, nj = j + dj;
            if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
              if (map[ni][nj] == SAFE_PATH) {
                nearSafePath = true;
              }
            }
          }
        }

        // Reducir probabilidad para mantener la distribución deseada
        if (nearSafePath &&
            rand() % 5 == 0) { // 20% probabilidad (antes era 33%)
          map[i][j] = DANGER_PATH;
        }
      }
    }
  }
}

void Terrain::addSafeAreas() {
  int numAreas = 5 + rand() % 6; // 5-10 áreas seguras (más que antes)

  for (int a = 0; a < numAreas; a++) {
    int centerX = rand() % width;
    int centerY = rand() % height;
    int radius = 3 + rand() % 5; // Radio de 3-7 (más grande)

    makeAreaSafe(centerX, centerY, radius);
  }
}

void Terrain::makeAreaSafe(int centerX, int centerY, int radius) {
  for (int i = centerY - radius; i <= centerY + radius; i++) {
    for (int j = centerX - radius; j <= centerX + radius; j++) {
      if (i >= 0 && i < height && j >= 0 && j < width) {
        int distance =
            abs(i - centerY) + abs(j - centerX); // Distancia Manhattan
        if (distance <= radius) {
          // 80% probabilidad de ser seguro (antes era 50%)
          if (rand() % 10 < 8) {
            map[i][j] = SAFE_PATH;
          }
        }
      }
    }
  }
}

void Terrain::smoothTerrain() {
  vector<vector<TypeTerrain>> newMap = map;

  for (int i = 1; i < height - 1; i++) {
    for (int j = 1; j < width - 1; j++) {
      if (map[i][j] == OBSTRACLE) {
        // Contar vecinos seguros
        int safeNeighbors = 0;
        for (int di = -1; di <= 1; di++) {
          for (int dj = -1; dj <= 1; dj++) {
            if (map[i + di][j + dj] == SAFE_PATH) {
              safeNeighbors++;
            }
          }
        }

        // Si tiene muchos vecinos seguros, mayor probabilidad de ser camino
        // seguro
        if (safeNeighbors >= 3) {
          if (rand() % 10 < 7) { // 70% probabilidad de ser seguro
            newMap[i][j] = SAFE_PATH;
          } else if (rand() % 10 < 5) { // 30% probabilidad de ser peligroso
            newMap[i][j] = DANGER_PATH;
          }
        }
      }
    }
  }

  map = newMap;
}

void Terrain::adjustTerrainDistribution() {
  // Contar la distribución actual
  int totalCells = width * height;
  int safeCells = 0, dangerCells = 0, obstacleCells = 0;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      switch (map[i][j]) {
      case SAFE_PATH:
        safeCells++;
        break;
      case DANGER_PATH:
        dangerCells++;
        break;
      case OBSTRACLE:
        obstacleCells++;
        break;
      }
    }
  }

  // Calcular porcentajes objetivo
  int targetSafe = (int)(totalCells * 0.60);
  int targetDanger = (int)(totalCells * 0.25);
  int targetObstacle = totalCells - targetSafe - targetDanger;

  // Ajustar si es necesario
  vector<pair<int, int>> obstacles, dangers, safes;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      switch (map[i][j]) {
      case SAFE_PATH:
        safes.push_back({i, j});
        break;
      case DANGER_PATH:
        dangers.push_back({i, j});
        break;
      case OBSTRACLE:
        obstacles.push_back({i, j});
        break;
      }
    }
  }

  // Convertir exceso de obstáculos en caminos seguros
  while (obstacleCells > targetObstacle && safeCells < targetSafe &&
         !obstacles.empty()) {
    int idx = rand() % obstacles.size();
    int i = obstacles[idx].first, j = obstacles[idx].second;
    map[i][j] = SAFE_PATH;
    obstacles.erase(obstacles.begin() + idx);
    obstacleCells--;
    safeCells++;
  }

  // Convertir exceso de obstáculos en caminos peligrosos
  while (obstacleCells > targetObstacle && dangerCells < targetDanger &&
         !obstacles.empty()) {
    int idx = rand() % obstacles.size();
    int i = obstacles[idx].first, j = obstacles[idx].second;
    map[i][j] = DANGER_PATH;
    obstacles.erase(obstacles.begin() + idx);
    obstacleCells--;
    dangerCells++;
  }
}

void Terrain::showTerrain() {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      switch (map[i][j]) {
      case SAFE_PATH:
        cout << ". ";
        break;
      case DANGER_PATH:
        cout << "! ";
        break;
      case OBSTRACLE:
        cout << "# ";
        break;
      }
    }
    cout << endl;
  }
}

int Terrain::getWidth() const { return width; }

int Terrain::gertHeight() const { return height; }

TypeTerrain Terrain::getTerrainAt(int x, int y) const {
  if (x >= 0 && x < width && y >= 0 && y < height) {
    return map[y][x];
  }
  return OBSTRACLE;
}

int Terrain::getCost(TypeTerrain tt) { return costTerrain[tt]; }
