#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ComputeHGCALTime.h"
#include "TRandom3.h"

using namespace std;

float cellRad = 0.563 + 0.001; ///0.001 is the delta
float minE_time = 15; ///15 mips

float speed_light = 29.9792; ///cm/ns


//bool debugL2_ = true;
bool debugL2_ = false;

class HGCTBAlgoFastTime {

public :
  virtual ~HGCTBAlgoFastTime() {}
  void   Init(std::vector<float>& rechit_energy, std::vector<unsigned int>& rechit_layer,
	      std::vector<short int>& rechit_iu, std::vector<short int>& rechit_iv,
	      std::vector<float>& rechit_x,      std::vector<float>& rechit_y,
	      std::vector<float>& rechit_time_mc, std::vector<float>& rechit_time_mc_firstHit,
	      std::vector<float>& rechit_time_mc_lastHit, std::vector<float>& rechit_z,
	      float cut, unsigned int maxLayer, std::vector<unsigned int> &rechit_module);
  float GetTime(int layer, int extend);
  float GetTimeSmeared(int layer, int extend);
  float SmearTime(float energy, int moduleId);

private :
  bool  debug=false;  
  vector< vector<float> > layer_rechit_en; 
  vector< vector<short int> > layer_rechit_u; 
  vector< vector<short int> > layer_rechit_v; 
  vector< vector<float> > layer_rechit_x; 
  vector< vector<float> > layer_rechit_y;
  vector< vector<float> > layer_rechit_z; 
  vector< vector<float> > layer_rechit_time;
  vector< vector<float> > layer_rechit_timeSmeared;
};

void HGCTBAlgoFastTime::Init(std::vector<float>& rechit_energy, std::vector<unsigned int>& rechit_layer,
			     std::vector<short int>& rechit_iu, std::vector<short int>& rechit_iv,
			     std::vector<float>& rechit_x, std::vector<float>& rechit_y,
			     std::vector<float>& rechit_time_mc, std::vector<float>& rechit_time_mc_firstHit,
			     std::vector<float>& rechit_time_mc_lastHit, std::vector<float>& rechit_z,
			     float cut, unsigned int maxLayer, std::vector<unsigned int> &rechit_module){

  if(debug) std::cout << " Init " << std::endl;
  
  layer_rechit_en.clear();  
  layer_rechit_u.clear();   
  layer_rechit_v.clear();
  layer_rechit_x.clear();   
  layer_rechit_y.clear();
  layer_rechit_z.clear();
  layer_rechit_time.clear();
  layer_rechit_timeSmeared.clear();

  layer_rechit_en.resize(maxLayer);  
  layer_rechit_u.resize(maxLayer);   
  layer_rechit_v.resize(maxLayer);
  layer_rechit_x.resize(maxLayer);   
  layer_rechit_y.resize(maxLayer);
  layer_rechit_z.resize(maxLayer);
  layer_rechit_time.resize(maxLayer);
  layer_rechit_timeSmeared.resize(maxLayer);

  TRandom3 * ran = new TRandom3();
  ran->SetSeed(0);

  unsigned int totLayerHits = rechit_energy.size();
  if(debug) std::cout << " nHits = " << totLayerHits << std::endl;    

  for (unsigned int irechit=0; irechit < totLayerHits; ++irechit){
    
    int moduleId = rechit_module[irechit]; 
    //set to 15MIP
    float GeVToMip = 1. / (85.5e-6);
    if(moduleId == 144 || moduleId == 145 || moduleId == 146 || moduleId == 147) GeVToMip = 1. / (57e-6);
    float nMip = rechit_energy[irechit] * GeVToMip;
    if(nMip < cut) continue;
    
    unsigned int layer = rechit_layer[irechit];
    if(layer > maxLayer) continue;

    //compute TOF time
    float timeHit = rechit_time_mc[irechit];
    if(rechit_time_mc[irechit] < rechit_time_mc_firstHit[irechit]) timeHit = rechit_time_mc_firstHit[irechit];
    float dist3Dhit = sqrt(pow(rechit_x[irechit], 2) + pow(rechit_y[irechit], 2) + pow(rechit_z[irechit], 2));
    float tofHit = dist3Dhit/speed_light;
    float timeOffset = 110; //ns = 33m
    if(debug)  std::cout << " dist3Dhit = " << dist3Dhit << " tof = " << tofHit << " timeHit = " << timeHit 
			 << " timeOffset = " << timeOffset << std::endl;
    timeHit = timeHit - tofHit - timeOffset; 

    float smearing = SmearTime(nMip, moduleId);
    float timeHitSmeared = ran->Gaus(timeHit, smearing);
    if(debug) std::cout << " timeHit  = " << timeHit << " timeHitSmeared = " << timeHitSmeared << " energy " <<rechit_energy[irechit] << std::endl;

    if(debug) std::cout << " layer = " << layer << std::endl;

    layer_rechit_en[layer-1].push_back(rechit_energy[irechit]);
    layer_rechit_u[layer-1].push_back(rechit_iu[irechit]);
    layer_rechit_v[layer-1].push_back(rechit_iv[irechit]);
    layer_rechit_x[layer-1].push_back(rechit_x[irechit]);
    layer_rechit_y[layer-1].push_back(rechit_y[irechit]);
    layer_rechit_z[layer-1].push_back(rechit_z[irechit]);
    layer_rechit_time[layer-1].push_back(timeHit);
    layer_rechit_timeSmeared[layer-1].push_back(timeHitSmeared);
  } // rechit loop

  if(debug) {
    for(auto ij : layer_rechit_en)    
      std::cout << " survived nHits = " << ij.size() << std::endl;
  }

  if(debug) std::cout << " fine main loop " << std::endl;
}


// energy weighted time
float HGCTBAlgoFastTime::GetTime(int layer, int extend){
  if(debug) std::cout << " hello in GetTime " << std::endl;
  if(debug) std::cout << " GetTime(int layer = " << layer << std::endl;

  float maxX;
  float maxY;
  float maxE = 0.;

  unsigned int startLayer = layer;
  unsigned int endLayer = layer+1;
  if(layer == -1){
    startLayer = 1;
    endLayer = 30;
  }

  if(debug)  std::cout << " startLayer = " << startLayer << " endLayer = " << endLayer << std::endl;

  for(unsigned int ij = startLayer; ij<endLayer; ++ij){

    unsigned int size = layer_rechit_en[ij-1].size();
    if(debug) std::cout << " size = " << size << std::endl;
    for(unsigned int iR=0; iR<size; ++iR){
      float en = layer_rechit_en[ij-1][iR];

      if(en > maxE){
	maxX = layer_rechit_x[ij-1][iR];
	maxY = layer_rechit_y[ij-1][iR];
	maxE = en;
      }
    }
  }

  if(debug) std::cout << " >>> maxX = " << maxX << " maxY = " << maxY << " maxE = " << maxE << std::endl;

  std::vector<float> times;
  std::vector<float> energies;
  for(unsigned int ij = startLayer; ij<endLayer; ++ij){

    unsigned int size = layer_rechit_en[ij-1].size();
    for(unsigned int iR=0; iR<size; ++iR){
      float x = layer_rechit_x[ij-1][iR];
      float y = layer_rechit_y[ij-1][iR];

      float rad = sqrt( pow(x-maxX, 2) + pow(y-maxY, 2) );
      if(rad > (2*extend+1)*cellRad ) continue;

      float en = layer_rechit_en[ij-1][iR];
      float time = layer_rechit_time[ij-1][iR];
      times.push_back(time);
      energies.push_back(en);
    }
  }

  if(debug) std::cout << " in getTime size = " << times.size()  << std::endl;
  
  if(times.size() >= 3){
    float averageTime = hgcaltime::fixSizeHighestDensity(times, energies);
    return(averageTime);
  }
  else {
    if(debug) std::cout << " no Time layer = " << layer << std::endl;
    return -99.;
  }
}

////
// energy weighted time smeared
float HGCTBAlgoFastTime::GetTimeSmeared(int layer, int extend){
  if(debug) std::cout << " hello in GetTimeSmeared " << std::endl;
  if(debug) std::cout << " GetTimeS layer = " << layer << std::endl;

  float maxX;
  float maxY;
  float maxE = 0.;

  unsigned int startLayer = layer;
  unsigned int endLayer = layer+1;
  if(layer == -1){
    startLayer = 1;
    endLayer = 30;
  }

  if(debug)  std::cout << " startLayer = " << startLayer << " endLayer = " << endLayer << std::endl;

  for(unsigned int ij = startLayer; ij<endLayer; ++ij){

    unsigned int size = layer_rechit_en[ij-1].size();
    if(debug) std::cout << " size = " << size << std::endl;
    for(unsigned int iR=0; iR<size; ++iR){
      float en = layer_rechit_en[ij-1][iR];

      if(en > maxE){
	maxX = layer_rechit_x[ij-1][iR];
	maxY = layer_rechit_y[ij-1][iR];
	maxE = en;
      }
    }
  }

  if(debug) std::cout << " >>> maxX = " << maxX << " maxY = " << maxY << " maxE = " << maxE << std::endl;

  std::vector<float> times;
  std::vector<float> energies;
  for(unsigned int ij = startLayer; ij<endLayer; ++ij){

    unsigned int size = layer_rechit_en[ij-1].size();
    for(unsigned int iR=0; iR<size; ++iR){
      float x = layer_rechit_x[ij-1][iR];
      float y = layer_rechit_y[ij-1][iR];

      float rad = sqrt( pow(x-maxX, 2) + pow(y-maxY, 2) );
      if(rad > (2*extend+1)*cellRad ) continue;

      float en = layer_rechit_en[ij-1][iR];
      float time = layer_rechit_timeSmeared[ij-1][iR];
      times.push_back(time);
      energies.push_back(en);
    }
  }

  if(debug) std::cout << " in getTime size = " << times.size()  << std::endl;

  if(times.size() >= 3){
    float averageTime = hgcaltime::fixSizeHighestDensity(times, energies);
    return(averageTime);
  }
  else {
    if(debug) std::cout << " no Time layer = " << layer << std::endl;
    return -99.;
  }
}


//
float HGCTBAlgoFastTime::SmearTime(float energy, int moduleId){

  if(debug) std::cout << " in SmearTime " << std::endl;
  float stoc_smear_time_300 =  15.5;
  float stoc_smear_time_200 =  10.24;
  float stoc_smear_time = -1;
  float const_smear_time = 0.05; //ns
  
  if(debug) std::cout << " module id = " << moduleId << std::endl;

  if (moduleId == 144 || moduleId == 145 || moduleId == 146 || moduleId == 147){
    stoc_smear_time = stoc_smear_time_200;      
  }  
  else{
    stoc_smear_time = stoc_smear_time_300;
  }


  float smear_time = sqrt( pow(stoc_smear_time/energy, 2) + pow(const_smear_time, 2) );
  return smear_time;
}
