#ifndef TERRAIN_H
#define TERRAIN_H

#include <unordered_map>
#include <vector>
enum TypeTerrain { SAFE_PATH, DANGER_PATH, OBSTRACLE };

using namespace std;

class Terrain {
private:
  int width;
  int height;
  vector<vector<TypeTerrain>> map;
  unordered_map<TypeTerrain, int> costTerrain;

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

  int getWidth() const;
  int getHeight() const;

  TypeTerrain getTerrainAt(int x, int y) const;
  int getCost(TypeTerrain tt);
};

#endif // !TERRAIN_H
