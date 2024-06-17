#include "sculptor.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

Sculptor::Sculptor(int _nx, int _ny, int _nz){
  nx = _nx; ny = _ny; nz = _nz;
  
  v = new Voxel **[nx];    // alocacao da matriz 3d
  
  for(int i = 0; i < nx; i++){
    v[i] = new Voxel*[ny];   // aloca memória para 'ny' ponteiros
    for (int j = 0; j < ny; j++) {
      v[i][j] = new Voxel[nz];
    }
  }
}

Sculptor::~Sculptor(){
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      delete[] v[i][j];
    }
     delete[] v[i];
  }
   delete[] v;
  }

void Sculptor::setColor(float r, float g, float b, float alpha){
  this->r = r; // componente correspondente à cor vermelha
  this->g = g; // componente correspondente à cor verde
  this->b = b; // componente correspondente à cor azul
  this->a = alpha; // componente correspondente à transparência
}

void Sculptor::putVoxel(int x, int y, int z){
  if(x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz){
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
    v[x][y][z].show = true; // o voxel é mostrado
  }
}

void Sculptor::cutVoxel(int x, int y, int z){
  if(x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz){
    v[x][y][z].show = false; // o voxel é ocultado
  }
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
  for(int i = x0; i <= x1; i++){
    for(int j = y0; j <= y1; j++){
      for(int k = z0; k <= z1; k++){
        putVoxel(i, j, k);
      }
    }
  }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
  for(int i = x0; i <= x1; i++){
    for(int j = y0; j <= y1; j++){
      for(int k = z0; k <= z1; k++){
        cutVoxel(i, j, k);
      }
    }
  }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
  for(int i = xcenter - radius; i <= xcenter + radius; i++){
    for(int j = ycenter - radius; j <= ycenter + radius; j++){
      for(int k = zcenter - radius; k <= zcenter + radius; k++){
        if (i >= 0 && i < nx && j >= 0 && j < ny && k >= 0 && k < nz) {
          if ((i - xcenter) * (i - xcenter) + (j - ycenter) * (j - ycenter) + (k - zcenter) * (k - zcenter) <= radius * radius){
            putVoxel(i, j, k);
          }
        }
      }
    }
  }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
  for(int i = xcenter - radius; i <= xcenter + radius; i++){
    for(int j = ycenter - radius; j <= ycenter + radius; j++){
      for(int k = zcenter - radius; k <= zcenter + radius; k++){
        if (i >= 0 && i < nx && j >= 0 && j < ny && k >= 0 && k < nz){
          if ((i - xcenter) * (i - xcenter) + (j - ycenter) * (j - ycenter) + (k - zcenter) * (k - zcenter) <= radius * radius) {
            cutVoxel(i, j, k);
          }
        }
      }
    }
  }
}

//void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){}

//void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){}

void Sculptor::writeOFF(const char* filename){
  std::ofstream fout;
  int nvoxels=0;
  fout.open(filename);
  if(!fout.is_open()){
    exit(1);
  }
  
  fout << "OFF\n";

  // Contar a quantidade de voxels ativos
  for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      for (int k = 0; k < nz; k++){
        if (v[i][j][k].show){
          nvoxels++;
        }
      }
    }
  }
  
  // conta quantos voxels estao marcados com show = true
  fout << nvoxels*8 << " " << nvoxels*6 << " " << 0 << std::endl;
  fout << std::fixed;
  fout << std::setprecision(1);
  
  // grava as coordenadas dos vertices dos cubos
  for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      for (int k = 0; k < nz; k++){
        if (v[i][j][k].show){
          fout << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
          fout << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
          fout << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
          fout << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
          fout << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
          fout << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
          fout << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
          fout << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
        }
      }
    }
  }
  
  // grava as faces dos cubos
  int voxel_index = 0;
  for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      for (int k = 0; k < nz; k++){
        if (v[i][j][k].show){
          int base_index = voxel_index * 8;
          
          fout << 4 << " " << base_index + 0 << " " << base_index + 3 << " " << base_index + 2 << " " << base_index + 1 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
          
          fout << 4 << " " << base_index + 4 << " " << base_index + 5 << " " << base_index + 6 << " " << base_index + 7 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
          
          fout << 4 << " " << base_index + 0 << " " << base_index + 1 << " " << base_index + 5 << " " << base_index + 4 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
          
          fout << 4 << " " << base_index + 0 << " " << base_index + 4 << " " << base_index + 7 << " " << base_index + 3 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
          
          fout << 4 << " " << base_index + 3 << " " << base_index + 7 << " " << base_index + 6 << " " << base_index + 2 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
          
          fout << 4 << " " << base_index + 1 << " " << base_index + 2 << " " << base_index + 6 << " " << base_index + 5 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;

          voxel_index++;
        }
      }
    }
  }
  fout.close();
}