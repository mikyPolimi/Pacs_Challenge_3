
// idea: ogni matrice local_U include anche riga sopra e sotto e ad ogni iterazione si aggiornano la prima e l'ultima riga

// vedi pacs examples parallel simpson


#include <iostream>
#include <vector>
#include <mpi.h>
#include "writeVTK.hpp"
#include <fstream>
#include "json.hpp"

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);

  MPI_Comm mpi_comm = MPI_COMM_WORLD;

  int rank;
  MPI_Comm_rank(mpi_comm, &rank);

  int size;
  MPI_Comm_size(mpi_comm, &size);

if(rank==0){
      // Opening the file with data.
      // Read from a file
      std::ifstream ifile("data.json");//open file
      using json=nlohmann::json;// to make life easier
      json j1;// create a json object
      ifile >>j1;//load the file in the json object
      ifile.close();// close file
      // Extract data. you need to use get<type> to select the type
      // Alternatively, you may use the utility value
      auto a = j1["a"].get<double>();// get data from json object
      auto b = j1["b"].get<double>();
      auto n = j1["n"].get<unsigned int>();
        int NX, NY;
        NX = 50;
        NY = 30;

  double hx, hy;
  hx = 1.0/ (NX+1);
  hy = 1.0/ (NY+1);

  std::vector<std::vector<double>> exacSol;

  double x,y;
  auto  fun = [](const double & x, const double & y){ return x*y;};

  for (int i = 0; i < NX+1; i++) {
    std::vector<double> row;
    x = i*hx;
    for (int j = 0; j < NY+1; j++) {
      y = j*hy;
      row.push_back(fun(x, y));
    }
    exacSol.push_back(row);
  }

    generateVTKFile("solution.vtk", exacSol, NX,NY, hx, hy);


    MPI_Finalize();
}

  return 0;
}