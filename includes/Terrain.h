#ifndef TERRAIN_H
#define TERRAIN_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
enum TypeTerrain { SAFE_PATH, DANGER_PATH, OBSTRACLE };

using namespace std;

class Terrain {
private:
  int width;
  int height;
  vector<vector<TypeTerrain>> map;

  void generateMainPath();
  void generateAdditionalPaths();
  void addDangerZones();
  void addSafeAreas();
  void makeAreaSafe(int centerX, int centerY, int radius);
  void smoothTerrain();
  void fillRemainingTerrain();
  void adjustTerrainDistribution();

public:
  Terrain();
  Terrain(int w, int h);
  void generateTerrain();
  void showTerrain();
};

#endif // !TERRAIN_H
